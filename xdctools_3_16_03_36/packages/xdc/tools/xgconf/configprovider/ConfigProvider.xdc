/*!
 *  ======== ConfigProvider ========
 *  Provides a ContentProvider that serves up
 *  the exported contents of an xdc configuration.
 *  This Module is experimental and subject to change.
 * 
 */
metaonly module ConfigProvider {

    /*! 
     *  Filter function operation modes. 
     */
    enum Ops {
        OP_GETVALUES,           /*! Get allowed value list. */
        OP_VALIDATE             /*! Validate choice and return js rval */
    };

    /*!
     * ======== CFGFILTERFXN ========
     * Config param value-filter function type definition
     * @params(operation)          Config operation type
     * @params(configParam)        Config param name
     * @params(value)              Value for set
     * @returns(results)           Depends on operation - string array on get, string on set
     */
    typedef any (*CFGFILTERFXN)(int, string, string);



instance:
    config Bool breakAfterUserScript = false;
     
    /*! 
     * instance creation function 
     * @params(fileName)        Config File name
     * @params(exeName)         Executable name
     * @params(pkgName)         Package name
     * @params(pkgRep)          Optional additional package repository path
     */
    create(string fileName, string exeName, string pkgName, string cfgScript);
    
    /*! Get the Configuration Model
     * 
     */
    any loadCfgModel();
    
    /*!
     * Run a function in the current configuration to get valid choices or set results
     * @params(mobjId)          Fully qualified model object id - including #nn if instance
     * @params(fxn)Name of function to invoke must match CFGFILTERFXN signature
     * @params(op)              Operation id - 0: get; 1: set - Ops enum
     * @params(cfgparam)        Configuration parameter whose information is requested
     * @params(value)           Selected value for set command - ignored if get
     * @returns(results)        Depends on operation - s/b string array on get and string on set
     */
    any runCFFxn(string mobjId, int modinst, string fxn, int op, string cfgparam, string value);

    /*!
     * Execute an XDCscript expression in the context of the
     * user's configuration script.
     */
    any eval(String expr);
    
    // Internal instance functions
    //---------------------------------------------------------------------------------

    
    /*! @_nodoc
     */
    any _getValidateResults();
    
          
}
