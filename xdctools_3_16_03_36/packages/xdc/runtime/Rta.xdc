/*
 *  ======== Rta.xdc ========
 *
 *! Revision History
 *! ================
 *! 08-Sep-2009 cmcc    Created
 */
 
package xdc.runtime;

/*!
 *  ======== Rta ========
 *  The Rta module contains target and configuration code for providing RTA
 *  support.
 *
 *  The 'Command' enum defines the available control commands, and the
 *  'CommandPacket' structure defines the format of commands received from
 *  the host. 
 *
 *  All commands should send back a response, even if only to acknowledge
 *  receipt and completion of the command. The format of the response
 *  is defined by the 'ResponsePacket' structure.
 *
 *  The Rta_processCommand can be used to process commands received from a
 *  host to call the appropriate API. Alternatively, the individual APIs can
 *  be called if not all of the defined commands are used.
 */
module Rta {

    /*! Logged when the Agent receives a command */
    config Log.Event LD_cmdRcvd = {
        mask: Diags.USER2,
        msg: "LD_cmdRcvd: Received command: %d, arg0: 0x%x, arg1: 0x%x"
    };

    /*! Logged when a diags mask is changed */
    config Log.Event LD_writeMask = {
        mask: Diags.USER2,
        msg: "LD_writeMask: Mask addres: 0x%x, New mask value: 0x%x"
    };
    
    /*! Assert if logger id in control command is invalid. */
    config Assert.Id A_invalidLogger = {
        msg: "A_invalidLogger: The logger id %d is invalid."
    };
    
    /*! Error raised if Agent receives an invalid command. */
    config Error.Id E_badCommand  = {
        msg: "E_badCommand: Received invalid command, id: %d."
    };

    /*! Command ids */
    enum Command : Int {
        Command_READ_MASK = 0,	
        Command_WRITE_MASK = 1,	
        Command_LOGGER_OFF = 2,
        Command_LOGGER_ON = 3,
        Command_GET_CPU_SPEED = 4,
        Command_RESET_LOGGER = 5,
        Command_CHANGE_PERIOD = 6
    };
    
    /*! 
     * Structure of command received from host 
     * TODO - Either the types should be changed to 32-bits, or the packet
     * size information should be added to the RTA XML file.
     */
    struct CommandPacket {
        Command  cmdId;
        UArg     arg0;
        UArg     arg1;
    }

    /*! Structure of response packet sent back to host */
    struct ResponsePacket {
        Command  cmdId;
        UArg     resp0;
        UArg     resp1;
    }
    
    /*!
     *  ======== processCommand ========
     *  Executes a command packet and prepares the response packet.
     *  
     *  This API will execute the command specified by the command packet
     *  argument, and will store the response information in the response
     *  packet argument.
     *
     *  @param(cmd)    The CommandPacket to execute.
     *  @param(resp)   The ResponsePacket to populate with the response.
     */
    Void processCommand(CommandPacket *cmd, ResponsePacket *resp);
    
    /*!
     *  ======== acknowledgeCmd ========
     */
    Void acknowledgeCmd(ResponsePacket *resp);

    /*!
     *  ======== readMask ========
     */
    Void readMask(ResponsePacket *resp, UArg addr);
    
    /*!
     *  ======== writeMask ========
     */   
    Void writeMask(ResponsePacket *resp, UArg addr, UArg val);
    
    /*!
     *  ======== enableLog ========
     */
    Void enableLog(ResponsePacket *resp, UArg log);
    
    /*!
     *  ======== disableLog ========
     */
    Void disableLog(ResponsePacket *resp, UArg log);
    
    /*!
     *  ======== getCpuSpeed ========
     */
    Void getCpuSpeed(ResponsePacket *resp);
    
    /*!
     *  ======== resetLog ========
     */
    Void resetLog(ResponsePacket *resp, UArg log);
    
    /*!
     *  ======== changePeriod ========
     */
    Void changePeriod(ResponsePacket *resp, UArg period);

    /*!
     *  @_nodoc
     *  ======== genRta ========
     *  Generates the Rta XML file.
     */
    function genRta(outputFileName);

}
/*
 *  @(#) xdc.runtime; 2, 0, 0, 0,237; 2-22-2010 10:33:58; /db/ztree/library/trees/xdc/xdc-u17x/src/packages/
 */

