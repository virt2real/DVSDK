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
/*!
 *  ======== Gen ========
 *  Generate a package from a template
 *
 *  
 */
metaonly module Gen {
instance:
    /*!
     *  ======== create ========
     *  Create a generator
     *
     *  @param(output)  name of the output directory.  This name is an 
     *  absolute path prefix for all files generated.
     *
     */
    create(Template.Instance template, String output);

    /*!
     *  ======== gen ========
     *  Instantiate the template.
     *
     *  When any template file is expanded, its `this` pointer is set to an
     *  object with the the same properties are the instance config parameters
     *  of the `Template.Instance` used to create the generator plus the
     *  following properties:
     *  @p(dlist)
     *      - `output`
     *          the output parameter passed to the function use to create
     *          the generator.
     *
     *      - `outputPath`
     *          same as above but may be modified during template expansion
     *
     *      - `filePath`
     *          the directory in which the output file with be created
     *  @p
     */
    void gen();

    /*!
     *  ======== preserveModTime ========
     *  Preserve modification times
     *
     *  Only change timestamp on each file if content has changed.
     */
    config Bool preserveModTime = false;
}
/*
 *  @(#) xdc.tools.mkpkg; 1, 0, 1, 0,149; 11-20-2009 13:27:05; /db/ztree/library/trees/xdctools/xdctools-d08x/src/
 */

