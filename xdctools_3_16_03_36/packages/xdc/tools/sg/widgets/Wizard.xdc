/* 
 *Copyright (c) 2008 Texas Instruments and others.
 *  All rights reserved. This program and the accompanying materials
 *  are made available under the terms of the Eclipse Public License v1.0
 *  which accompanies this distribution, and is available at
 *  http://www.eclipse.org/legal/epl-v10.html
 * 
 *  Contributors:
 *      Texas Instruments - initial implementation
 *
 * */
metaonly module Wizard inherits Widget {
    enum Status {
      FINISHED,
      CANCELED
    };

instance:
    config Any content;
    create(Any parent);

    Void activate(Int i);

    Status getStatus();
    Bool   isDone();
}
/*
 *  @(#) xdc.tools.sg.widgets; 1,0,0,147; 11-20-2009 13:28:14; /db/ztree/library/trees/xdctools/xdctools-d08x/src/
 */

