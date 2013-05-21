/* 
 * Copyright (c) 2010, Texas Instruments Incorporated
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * *  Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * *  Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * *  Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 * 
 */
/*
 *  ======== ladclient.h ========
 */

/**
 *  @file       ladclient.h
 *
 *  @brief      The Link Arbiter Daemon (LAD) communication interface.
 *              Provides wrapper functions to communicate with LAD, allowing
 *              a client to: establish a connection to LAD; request startup of 
 *              a DSP server executable; query DSP status; and release the DSP
 *              and disconnect from LAD.
 */
/**
 *  @defgroup   ti_dsplink_utils_ladclient     LAD Communication Interfaces
 */

#ifndef ti_dsplink_utils_ladclient_
#define ti_dsplink_utils_ladclient_

#ifdef __cplusplus
extern "C" {
#endif

/** @ingroup    ti_dsplink_utils_ladclient */
/*@{*/

/* limits */
#define LAD_MAXLENGTHIMAGENAME  512  /**< max size for DSP server path name */
#define LAD_MAXLENGTHCONFIGNAME 32   /**< max size Link config name */

/* LAD return codes */
typedef enum {
    LAD_SUCCESS = 0,            /**< success */
    LAD_FAILURE,                /**< general failure */
    LAD_INVALIDARG,             /**< invalid argument */
    LAD_ACCESSDENIED,           /**< the request was denied */
    LAD_ALREADYRUNNING,         /**< success; DSP was already running */
    LAD_STILLRUNNING,           /**< success; DSP still running */
    LAD_IOFAILURE,              /**< communication failure */
    LAD_NOTCONNECTED,           /**< not connected to LAD yet */
    LAD_INVALIDVERSION          /**< unsupported communication protocol */
} LAD_Status;

/* DSP states */                        
typedef enum {
    LAD_UNKNOWN = 0,            /**< state is unknown */
    LAD_SETUP,                  /**< setup state */
    LAD_LOADED,                 /**< loaded state */
    LAD_STARTED,                /**< running state */
    LAD_STOPPED,                /**< stopped state */
    LAD_IDLE,                   /**< idle state */
    LAD_RESET,                  /**< reset state */
    LAD_UNAVAILABLE             /**< state is unavailable */
} LAD_DspState;

typedef Uns LAD_ClientHandle;   /**< handle for communicating with LAD  */ 

typedef struct LAD_DspStatus {
    LAD_DspState dspState;                      /**< DSP state */
    Char linkConfigName[LAD_MAXLENGTHCONFIGNAME];    /**< Link config name */
    Int numClientsStarted;    /**< number clients who requested DSP startup */
    Char imageName[LAD_MAXLENGTHIMAGENAME];     /**< server executable name */
} LAD_DspStatus;


/*
 *  ======== LAD_connect ========
 */
/**
 *  @brief      Connect to LAD.
 *
 *  @param[out] handle    The new client handle, as defined by LAD.
 *
 *  @retval     LAD_SUCCESS    Success.
 *  @retval     LAD_INVALIDARG    The handle pointer is NULL.
 *  @retval     LAD_ACCESSDENIED    Returned on either of two conditions: this
 *              client is trying to establish a second active connection to 
 *              LAD, and the request is denied; or, the total number of 
 *              simultaneous client connections to LAD has been reached, and
 *              no more client handles are available.
 *  @retval     LAD_IOFAILURE    Unable to communicate with LAD, due to an
 *              OS-level I/O failure.  A full system reboot may be necessary.
 *  @retval     LAD_INVALIDVERSION    Unable to communicate with LAD due to a
 *              mismatch in the communication protocol between the client and 
 *              LAD.
 *
 *  @sa         LAD_disconnect().
 */
extern LAD_Status LAD_connect(LAD_ClientHandle * handle);

/*
 *  ======== LAD_disconnect ========
 */
/**
 *  @brief      Disconnect from LAD.
 *
 *  @param[in]  handle    The client handle, as returned from previous call to
 *              LAD_connect().
 *
 *  @retval     LAD_SUCCESS    Success.
 *  @retval     LAD_INVALIDARG    Invalid client handle.
 *  @retval     LAD_NOTCONNECTED    Not currently connected to LAD.
 *  @retval     LAD_STILLRUNNING    This client has previously started the DSP
 *              via a call to LAD_startupDsp, and must call LAD_releaseDsp
 *              before attempting to disconnect from LAD.
 *  @retval     LAD_IOFAILURE    Unable to communicate with LAD, due to an
 *              OS-level I/O failure, or timeout.  A full system reboot may be
 *              necessary.
 *
 *  @sa         LAD_connect().
 */
extern LAD_Status LAD_disconnect(LAD_ClientHandle handle);

/*
 *  ======== LAD_getDspStatus ========
 */
/**
 *  @brief      Get DSP status from LAD.
 *
 *  @param[in]  handle    The client handle, as returned from previous call to
 *              LAD_connect().
 *
 *  @param[in]  cpuId    The CPU for which status is to be returned.
 *
 *  @param[out] statusInfo    The DSP status structure to be filled in by LAD.
 *
 *  @retval     LAD_SUCCESS    Success.
 *  @retval     LAD_INVALIDARG    Invalid handle or statusInfo pointer.
 *  @retval     LAD_NOTCONNECTED    Not currently connected to LAD.
 *  @retval     LAD_FAILURE    Failure occurred when querying DSP state.
 *  @retval     LAD_IOFAILURE    Unable to communicate with LAD, due to an
 *              OS-level I/O failure.  A full system reboot may be necessary.
 *
 *  @sa         LAD_connect().
 */
extern LAD_Status LAD_getDspStatus(LAD_ClientHandle handle, Int cpuId, 
    LAD_DspStatus * statusInfo);

/*
 *  ======== LAD_releaseDsp ========
 */
/**
 *  @brief      Release control of the DSP.  This call is only appropriate if
 *              the client previously made a successful call to 
 *              LAD_startupDsp().
 *
 *  @param[in]  handle    The client handle, as returned from LAD_connect().
 *
 *  @retval     LAD_SUCCESS    Success, the DSP has been stopped.
 *  @retval     LAD_STILLRUNNING    Success, the DSP is continuing to run due
 *              to other client connection(s).
 *  @retval     LAD_INVALIDARG    Invalid client handle.
 *  @retval     LAD_NOTCONNECTED    Not currently connected to LAD.
 *  @retval     LAD_ACCESSDENIED    This client not allowed to stop the DSP
 *              because it didn't successfully start it.
 *  @retval     LAD_FAILURE    LAD was unable to stop and detach from the DSP.
 *  @retval     LAD_IOFAILURE    Unable to communicate with LAD, due to an
 *              OS-level I/O failure.  A full system reboot may be necessary.
 *
 *  @sa         LAD_startupDsp().
 */
extern LAD_Status LAD_releaseDsp(LAD_ClientHandle handle);

/*
 *  ======== LAD_startupDsp ========
 */
/**
 *  @brief      Load and start the DSP running.
 *
 *  @param[in]  handle    The client handle, as returned from LAD_connect().
 *  @param[in]  cpuId    The DSP to be loaded and started.
 *  @param[in]  linkConfigName    The pre-defined Link configuration known to 
 *              LAD.
 *  @param[in]  imageName    The name to the DSP server executable.  If an
 *              environment variable named "LAD_SERVERPATH" is defined,
 *              indicting a repository for server executable files, then this
 *              path will be pre-pended to the imageName to form the location
 *              of the DSP executable file; if "LAD_SERVERPATH" is not 
 *              defined, then imageName will be considered to be the full
 *              path name of the DSP executable file.
 *
 *  @retval     LAD_SUCCESS    Success, DSP has been started.
 *  @retval     LAD_ALREADYRUNNING    Success, the DSP was already running 
 *              with the same Link configuration and server executable.
 *  @retval     LAD_INVALIDARG    Invalid client handle, cpuId, or 
 *              linkConfigName.
 *  @retval     LAD_NOTCONNECTED    Not currently connected to LAD.
 *  @retval     LAD_ACCESSDENIED    LAD has refused the request because the DSP
 *              is already running, with a linkConfigName or imageName that
 *              does not match this request.
 *  @retval     LAD_FAILURE    LAD is unable to start the DSP.
 *  @retval     LAD_IOFAILURE    Unable to communicate with LAD, due to an
 *              OS-level I/O failure.  A full system reboot may be necessary.
 *
 *  @sa         LAD_releaseDsp().
 */
extern LAD_Status LAD_startupDsp(LAD_ClientHandle handle, Int cpuId, 
    String linkConfigName, String imageName);

/*@}*/  /* ingroup */

#ifdef __cplusplus
}
#endif

#endif
/*
 *  @(#) ti.dsplink.utils.ladclient; 1, 0, 0,239; 12-2-2010 21:18:40; /db/atree/library/trees/ce/ce-r11x/src/ xlibrary

 */

