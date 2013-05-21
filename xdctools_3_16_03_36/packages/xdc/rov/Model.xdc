/* --COPYRIGHT--,EPL
 *  Copyright (c) 2008 Texas Instruments and others.
 *  All rights reserved. This program and the accompanying materials
 *  are made available under the terms of the Eclipse Public License v1.0
 *  which accompanies this distribution, and is available at
 *  http://www.eclipse.org/legal/epl-v10.html
 * 
 *  Contributors:
 *      Texas Instruments - initial implementation
 * 
 * --/COPYRIGHT--*/
/*!
 *  ======== Model ========
 *  The ROV Model is the core of ROV. The Model must be started in order to
 *  retrieve ROV views for any modules.
 *
 *  The Model provides a processCommand API which provides a way of interacting
 *  with the ROV core. It accepts String commands and returns results formatted
 *  in XML.
 *
 *  Because the results of processCommand are returned as XML, the Model has
 *  a compatibility key to ensure that the Model's client is compatible with
 *  the version of the XML being returned by the Model.
 */
metaonly module Model {

    /*!
     *  ======== xmlVers ========
     *  Model.start will throw an exception if the version parameter does not
     *  equal the Model's current version. The version number reflects the
     *  format of the XML returned by the Model's processCommand API. Whenever
     *  the format of the XML changes, the version number is bumped. This
     *  allows the Model to verify compatibility with it's client if the client
     *  includes an XML parser.
     */
    metaonly config Int xmlVers = 3;
    
    /*!
     *  ======== start ========
     *  Starts the ROV Model.
     *
     *  The ROV Model requires instances of an ISymbolTable, an IMemoryImage, 
     *  and an ICallBack. It also requires the ROV recap file, which can be
     *  located using the xdc.rov.Recap module.
     *
     *  @param(xmlVers) 
     *  Model.start will throw an exception if the version parameter does not
     *  equal the Model's current version. For clients which don't 
     *  programmatically parse the XML (the XML is just displayed to a human
     *  user), it is sufficient to just pass Model.xmlVers as this first 
     *  argument.
     *
     *  @param(recap) Capsule of the ROV recap file. Retrieve this with
     *  xdc.loadCapsule(recapFilePath)
     */
    Void start(Int xmlVers, String executable, Any recap, 
               ISymbolTable.Instance sym, Any mem, 
               ICallBack.Instance callBack);

    /*!
     *  ======== getISymbolTableInst ========
     */
    ISymbolTable.Instance getISymbolTableInst();

    /*!
     *  ======== getMemoryImageInst ========
     */
    function getMemoryImageInst();
    
    /*!
     *  ======== getICallBackInst ========
     */
    ICallBack.Instance getICallBackInst();
    
    /*!
     *  ======== getIOFReaderInst ========
     */
    function getIOFReaderInst();

    /*!
     *  ======== getModuleList ========
     *
     */
    Any getModuleList();
}
/*
 *  @(#) xdc.rov; 1, 0, 0,237; 2-22-2010 10:33:38; /db/ztree/library/trees/xdc/xdc-u17x/src/packages/
 */

