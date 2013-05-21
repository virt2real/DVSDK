/*
 *  ======== StateReader ========
 *  These APIs are all designed so that they will not re-read data that has already been read in.
 */

var symTable;
var strDec;
 
/*
 *  ======== instance$meta$init ========
 */
function instance$meta$init(inSymTable, inStrDec)
{
    symTable = inSymTable;
    strDec = inStrDec;
}
 
/* 
 *  ======== fetchModuleState ========
 *  Scans the given module's module state structure. If the structure has 
 *  already been scanned, this function returns immediately.
 */
function fetchModuleState(mod)
{   
    /* Return if the object has already been scanned. */
    if (mod.state) {
        return;
    }
    
    /* If the module does not have module state, return null. */
    if (!('Module_State' in mod.useMod)) {
        mod.state = null;
        mod.addr = "N/A";
        return;
    }
    
    /* Look up the Module state structure and fetch it. */
    mod.addr = $addr(symTable.getSymbolValue(mod.name.replace(/\./g, '_') + 
                                             '_Module__state__V'));
    var modState = strDec.fetchStruct(mod.useMod.Module_State,
                                      Number(mod.addr), true);
    
    /* Bind the state structure to the module as the state field */
    mod.state = modState;
}

/* 
 *  ======== fetchAllInstStates ========
 *  This function makes sure that all of the instance state structures for
 *  this module have been scanned in. It does not call any view$init functions.
 */
function fetchAllInstStates(mod)
{   
    /* Retrieves the addresses of all of the instance state structures. */
    fetchAllInstAddrs(mod);
    
    /* Fetch all of the static instance states. */
    for (var i = 0; i < mod.staticInstAddrs.length; i++) {
        fetchInstState(mod, mod.staticInstAddrs[i], i);
    }
    
    /* Fetch all of the dynamic instance states. */
    for (var i = 0; i < mod.dynInstAddrs.length; i++) {
        fetchInstState(mod, mod.dynInstAddrs[i], -1);
    }
}

/*
 *  ======== fetchAllInstAddrs ========
 *  Retrieves the addresses of all of the statically and dynamically created
 *  instances. These will be placed in mod.staticInstAddrs and 
 *  mod.dynInstAddrs.
 *
 *  TODO - fetchInstState had a check for null address for when there are no instances.
 *         Make sure this never adds "null" as an address. 
 */
function fetchAllInstAddrs(mod)
{
    // TODO - staticInstAddrs should be constant? But clear cache deletes mod, so this won't preserve them...
    /* Check if they have already been retrieved. */
    if (mod.readAllAddrs) {
        return;
    }
    
    var Types = xdc.module('xdc.runtime.Types');
    
    /* Retrieve the module header, which points to all of the intstances. */
    var modHdrSym = mod.name.replace(/\./g, '_') + '_Module__root__V';
    var modHdrAddr = symTable.getSymbolValue(modHdrSym);
    var modHdr = strDec.fetchStruct(Types.ModHdr, Number(modHdrAddr), true);

    /* Create an array of the addresses of all of the static instances. */
    mod.staticInstAddrs = new Array();
    
    /* Retrieve the static instance addresses, which are in an array. */
    if (modHdr.instArrBeg != 0) {
        for (var instAddr = modHdr.instArrBeg; 
             instAddr <= modHdr.instArrEnd; instAddr += modHdr.instSize) {
            mod.staticInstAddrs.$add(instAddr);
        }
    }

    /* Create an array of the addresses of all of the dynamic instances. */
    mod.dynInstAddrs = new Array();
    
    /* 
     * Create a temporary map of the addresses discovered to use for detecting
     * loops in the linked list.
     */
    var addrs = {};
    
    /* 
     * The module header is also part of a linked list of all of the
     * dynamically created instances. 
     */
    var instHdrAddr = modHdr.link.next;

    /* Loop over the list. */
    while (instHdrAddr != modHdrAddr) {
        
        /* Add the header address to the temporary map. */
        addrs[instHdrAddr] = true;
        
        /* The instance address is offset from the header. */
        var instAddr = Number(instHdrAddr) + Types.InstHdr.$sizeof();
        
        /* Add the instance's address. */
        mod.dynInstAddrs.$add(instAddr);
        
        /* 
         * Get the actual header struct and find the address of the
         * next header struct. 
         */
        var instHdr = strDec.fetchStruct(Types.InstHdr, Number(instHdrAddr), true);
        
        /* Get the address of the next instance header. */
        instHdrAddr = instHdr.link.next;
        
        /* If we've detected a loop in the instance queue throw an error. */
        if (instHdrAddr in addrs) {
            throw (new Error("Detected loop in instance queue at address " + instHdrAddr));
        }
    }
    
    mod.readAllAddrs = true;
}

/*
 *  ======== getKey ========
 *  Makes a key out of the instance's address for the module's 
 *  instMap.
 */
function getKey(addr)
{
    return ('0x' + Number(addr).toString(16));
}

/* 
 *  ======== fetchInstState ========
 *  This function scans in a single instance's state, and associates various
 *  metadata (used by the view$init functions) with the instance object.
 *  Returns the inst object for Program.scanHandle.
 *  This API is responsible for caching the retrieved instance states. If the 
 *  instance state at the given address has already been read in, it will not
 *  be read again.
 */
function fetchInstState(mod, instAddr, staticIndex)
{   
    /* 
     * Check to see if this instance has already been scanned.
     * Instances may be discovered through Program.scanInstanceView, or a call
     * to Program.scanHandle from a different module's view init code; so it's
     * possible that the instance has already been scanned.
     */
    var key = getKey(instAddr);
    if ((mod.instMap) && (key in mod.instMap)) {
        return (mod.instMap[key]);
    }
    
    /* 
     * If this module's instance state structure has a size field, fetch the
     * instance state structure. 
     */
    var obj;
    if ('$sizeof' in mod.useMod.Instance_State) {
        obj = strDec.fetchStruct(mod.useMod.Instance_State, 
                                 Number(instAddr), true);
    }
    /* Otherwise, this module has no real instance state (such as GateHwi). */
    else {
        /* TODO - Is this all right? Might it work to call fetchStruct anyway? */
        Program.debugPrint("xdc.rov.decoder: Module does not have instance state.");
        var temp = new mod.useMod.Instance_State;
        obj = {};

        obj.$addr = $addr(instAddr);
        obj.$type = temp.$type;
    }
    
    /* Create an instance descriptor for the instance. */
    var inst = getInstDesc(mod, obj, staticIndex);
            
    /* Return the inst for scanHandle */
    return (inst);
}

/*
 *  ======== getInstDesc ========
 *  Takes a decoded state structure and creates an ROVInstanceDesc for it. 
 *  Also retrieves the label for the instance.
 */
function getInstDesc(mod, obj, staticIndex)
{
    /* 
     * The instMap will map instance addresses to instance objects. 
     * It may already be present from a call to Program.scanHandle in a 
     * different module's view init code.
     */
    if (!mod.instMap) {
        mod.instMap = new Object();
    }
    
    /* Return immediately if this object has already been scanned. */
    var key = getKey(obj.$addr);
    if (key in mod.instMap) {
        return (mod.instMap[key]);
    }

    /* Create a new instance descriptor to represent the instance */    
    var inst = new Program.ROVInstanceDesc;

    /* Store the state structure and its address. */
    inst.state = obj;
    inst.addr = obj.$addr;
    
    /* Get the instance's label */
    obj.$label = getLabel(mod, obj, staticIndex);

    /* Add the instance to the module's list. */
    mod.instances.$add(inst);
    
    /* 
     * Add the instance to the map, so we can quickly check if it's
     * already been scanned.
     */
    mod.instMap[key] = inst;
    
    return (inst);
}

/*
 * ======== getLabel ========
 * Helper function called from getInstLabel to retrieve the label for the
 * given instance.
 */
function getLabel(mod, obj, staticIndex)
{
    /* Create the label for the instance. */
    var label = mod.name + "@" + Number(obj.$addr).toString(16);
    
    /* If this is a static instance, get the instance name from the capsule. */
    if (staticIndex != -1) {
        var givenName =
            Program.$modules[mod.name].$instances[staticIndex].instance.name;
        if (givenName != null) {
            label += (":" + givenName);
            return (label);
        }
    }    
    /* Otherwise, if this is a dynamically created instance, 
     * check if it has a name. */
    else if('__name' in obj) {
        /* If the __name field is null, no name was given. */
        if(Number(obj.__name) != 0) {
            try {
                var givenName =
                    xdc.module('xdc.runtime.Text').fetchAddr(Number(obj.__name));
            }
            catch (e) {
                if (e.message == "abort") {
                    throw (e);
                }
                /* 
                 * Need a way to report error to user. Just display
                 * error instead of name. 
                 */
                givenName = "Error retrieving given name at 0x" +
                            Number(obj.__name).toString(16) + ": " + 
                            e.toString();
            }
            label += ":" + givenName;
            return (label);
        }
    }
    
    return (label);
}

/*
 *  ======== fetchHandleState ========
 *  The fetchInstState API needs to know whether the given instance
 *  is static or dynamic. If we just have a handle to an instance, we first
 *  need to determine whether it is static or dynamic.
 */
function fetchHandleState(mod, instAddr)
{    
    /* 
     * Check if this is a static instance. If it is, we need to find its index
     * in the module header instance array so the decoder can retrieve the
     * instance name from the recap file.
     */
    fetchAllInstAddrs(mod);
    
    var staticIndex = -1;
    for (var i = 0; i < mod.staticInstAddrs.length; i++) {
        if (Number(instAddr) == Number(mod.staticInstAddrs[i])) {
            staticIndex = i;
            break;
        }
    }
        
    /* Fetch this individual instance's state, adding it to the module. */
    var inst = fetchInstState(mod, instAddr, staticIndex);

    return (inst);
}


/*
 *  @(#) xdc.rov; 1, 0, 0,237; 2-22-2010 10:33:39; /db/ztree/library/trees/xdc/xdc-u17x/src/packages/
 */

