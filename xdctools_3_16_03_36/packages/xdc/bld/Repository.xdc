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
/*
 *  ======== Repository.xdc ========
 */
package xdc.bld;

/*!
 *  ======== Repository ========
 *  Model of a package repository
 */
metaonly module Repository {

    /*!
     *  ======== Attrs ========
     *  Optional attributes for a repository
     *
     *  @field(releases)  This array contains releases that will contain the
     *          repository.  Thus, a single repository can be part of any set 
     *          of releases.  Each repository is always added to the 
     *          package's "default release" in addition to any releases
     *          specified in the releases array.
     *
     *  @see #attrs
     */
    struct Attrs {
        Release.Instance releases[]; /*! releases that this rep is a part of */
    };

instance:
    /*!
     *  ======== create ========
     *  @_nodoc
     *  Instances should only be created via PackageContents.addRepository()
     */
    create();

    /*!
     *  ======== name ========
     *  The repository's directory name
     */
    config String name;

    /*!
     *  ======== attrs ========
     *  The repository's attributes
     */
    config Attrs attrs;

    /*!
     *  ======== addPackages ========
     *  Add specified package releases to this repository
     *
     *  @param(names) An array of strings naming package releases to be added
     *          to the repository.  Package releases are named as follows:
     *          @p(code)
     *              <pkgName>:<releaseName>
     *          @p
     *          where `<pkgName>` is the name of the package to add to the
     *          repository and `<releaseName>` is the name of one of that
     *          package's releases.  A package release name may be either the
     *          archive file name (relative to the package's base directory)
     *          of the release archive or the name used create the release in
     *          package named `<pkgName>`.
     *
     *          For example, if the package `ti.bios` had a release named
     *          `exports/ti_bios,src`, the following statements would add
     *          this release to the repository named `packages`:
     *          @p(code)
     *              var r = Pkg.addRepository("packages");
     *              r.addPackages(["ti.bios:exports/ti_bios,src"]);
     *          @p
     *
     *          Alternatively, one can specify the archive file name:
     *          @p(code)
     *              var r = Pkg.addRepository("packages");
     *              r.addPackages(["ti.bios:exports/ti_bios,src.tar"]);
     *          @p
     *
     *          It is possible to get a list of release archive names from a
     *          package via the
     *          `{@link xdc.bld.BuildEnvironment#getReleaseDescs()}`
     *          method.  For example, to get the physical archive name of the
     *          default release of the `ti.bios` package, the following loop
     *          can be added to a build script:
     *          @p(code)
     *              var archiveName;
     *              var rels = Build.getReleaseDescs('ti.bios');
     *              for (var j = 0; j < rels.length; j++) {
     *                  if (rels[j].label == "default") {
     *                      archiveName = rels[j].aname;
     *                      break;
     *                  }
     *              }
     *              // archiveName is now set to the file name of the ti.bios
     *              // default release archive (or undefined)
     *          @p
     *
     *  @see xdc.bld.BuildEnvironment#getReleaseDescs()
     */
    Void addPackages(String names[]);
}
/*
 *  @(#) xdc.bld; 1, 0, 2,238; 2-22-2010 10:33:32; /db/ztree/library/trees/xdc/xdc-u17x/src/packages/
 */

