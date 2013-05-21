%%{
    var qdmaParamBase = this.EDMA3BASE + 0x4000;
    var numQdma = this.getNumQDMA();

    var numGroups = 0;
    while (this.hasOwnProperty("NUMPARAMS_GROUP" + numGroups)) {
        numGroups++;
    }

    var iheap = this.INTERNALHEAP.heapLabel.name;
    var eheap = this.EXTERNALHEAP.heapLabel.name;

    // Don't want leading '_' in heap label.
    if (this.INTERNALHEAP.heapLabel.language == "C") {
        iheap = this.INTERNALHEAP.heapLabel.name.substr(1);
    }
    if (this.EXTERNALHEAP.heapLabel.language == "C") {
        eheap = this.EXTERNALHEAP.heapLabel.name.substr(1);
    }
    var idma3Internal = (this.IDMA3INTERNAL == true) ? "TRUE" : "FALSE";
    var allowUnshared = (this.ALLOWUNSHARED == true) ? "TRUE" : "FALSE";
    var scratchAllocFxn = (this.SCRATCHALLOCFXN == null) ? "NULL" :
        (this.SCRATCHALLOCFXN.language == "C") ?
            this.SCRATCHALLOCFXN.name.substr(1) : this.SCRATCHALLOCFXN.name;
    var scratchFreeFxn = (this.SCRATCHFREEFXN == null) ? "NULL" :
        (this.SCRATCHFREEFXN.language == "C") ?
            this.SCRATCHFREEFXN.name.substr(1) : this.SCRATCHFREEFXN.name;
%%}

%if (numQdma > 0) {

/* DMAN3 C source output */

#include <ti/sdo/fc/dman3/dman3.h>

%// Cannot have only one of SCRATCHALLOCFXN and SCRATCHFREEFXN be null
%if ((this.SCRATCHALLOCFXN != null) && (this.SCRATCHFREEFXN != null)) {
extern Bool `scratchAllocFxn`(IALG_Handle, Int, IALG_MemRec *, Int);
extern Void `scratchFreeFxn`(Int, Void *, Uns);
%}
 
%// Allocate DMAN3 QDMA CHANNELS array of size _nq (number of qdma
%// channels used by DMAN3)

%var chnlNdx = 0;
%var qdmaChnl = 0;
%
// Array of QDMA channels used by DMAN3
far Uns DMAN3_qdmaChannels[`numQdma`] = {
% for (var i = 0; i < this.MAXQDMACHANNELS; i++) {
%     var chan = "this.USEQDMA" + i;
%     if (eval(chan) == true) {
%         // Output the qdma channel number
    `i`,
%     }  
% }
};
%

// Mapping of the QDMA channels to Event Queues 
far Uns DMAN3_qdmaQueueMap[`numQdma`] =  {
%       for (var i = 0; i < numQdma; i++) {
%           var queue = "this.EVENTQUEUE_QDMA" + i;
            `eval(queue)`,		//Output the queue Number
%       }
    };
% 

// Mapping of the Event Queues to TCs 
far Uns DMAN3_queueTCMap[`this.MAXTCS`] =  {
    
%       for (var i = 0; i < this.MAXTCS; i++) {
%           var tc = "this.TCNUM_EVENTQUEUE" + i;
            `eval(tc)`,		//Output the TC number
%       }
};

// Priorities associated with the Event queues 
far Uns DMAN3_queuePri[`this.MAXTCS`] =  {
%       for (var i = 0; i < this.MAXTCS; i++) {
%           var pri = "this.PRIORITY_EVENTQUEUE" + i;
            `eval(pri)`,		/* `i` */
%       }
};

/*
 *  ======== DMAN3_PARAMS ========
 *  Default module configuration structure for DMAN3 implementation.
 *  It is set at design time by the system integrator to adjust the behaviour
 *  of the module to be optimal for its execution environment.
 */
DMAN3_Params DMAN3_PARAMS = {
    (Uns *)`utils.toHex(qdmaParamBase)`,	/* PaRam base address */
    `this.MAXPARAMENTRIES`,		/* Total number of PaRam entries */
    `this.PARAMBASEINDEX`,		/* Index of first PaRam for DMAN3 */
    `this.NUMPARAMENTRIES`,		/* # of PaRam entries for DMAN3 */
    `this.MAXQDMACHANNELS`,		/* # of hardware QDMA channels */
    `numQdma`,				/* # of QDMA channels used by DMAN3 */
    DMAN3_qdmaChannels,	/* Array of QDMA channels used by DMAN3 */
    `utils.toHex(this.TCC_FREEMASK_HIGH)`,	/* tccAllocationMaskH */
    `utils.toHex(this.TCC_FREEMASK_LOW)`,	/* tccAllocationMaskL */
%
%// Would like to initialize internal and external heaps with
%// DMAN3.INTERNALHEAP and DMAN3.EXTERNALHEAP, but we can't do it here.
%
    -1,			/* Internal heap id */
    0,			/* External heap id */

    /* Array of number of TCCs to be allocated for each group Id */
    {
% for (var i = 0; i < numGroups; i++) {
%     var nTccs = "this.NUMTCCS_GROUP" + i;
        `eval(nTccs)`,		/* `i` */
% }
    },
%

    /* Array of Number of PaRams to be allocated for each group Id */
    {
% for (var i = 0; i < numGroups; i++) {
%     var nPaRams = "this.NUMPARAMS_GROUP" + i;
        `eval(nPaRams)`,		/* `i` */
% }
    },
%
    `idma3Internal`,		/* Use internal memory for IDMA3 Objects */
    `scratchAllocFxn`,		/* Scratch allocation function */
    `scratchFreeFxn`,		/* Scratch free function */
    `this.NULLPARAMINDEX`,	/* Index of null PaRam */
    `this.MAXTCS`,          /* Number of TCs on the hardware */ 
    DMAN3_qdmaQueueMap,     /* Mapping of QDMA channels to event queues */
    DMAN3_queueTCMap,       /* Mapping of event queues to TCs */
    DMAN3_queuePri,          /* Priorities associated with the event queues */
    `allowUnshared`,	/* Allow unshared TCCs or PaRams to be granted */
};

%}

extern far Int `iheap`;
extern far Int `eheap`;

Bool DMAN3_initParams()
{
%if (numQdma > 0) {
    DMAN3_PARAMS.heapInternal = `iheap`;
    DMAN3_PARAMS.heapExternal = `eheap`;
%}
    return (TRUE);
}
