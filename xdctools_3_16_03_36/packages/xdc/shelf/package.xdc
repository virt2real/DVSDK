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
 *  ======== xdc.shelf ========
 *  Container for third party jars required by XDCtools
 *
 *  The following jars are part of this package:
 *  @p(html)
     <table border="1">
     <tr>
       <th>Jar</th>
       <th>Version</th>
       <th>License</th>
       <th>From</th>
       <th>Description</th>
     </tr>
     <tr>
       <td>js.jar</td>
       <td>1.6R6</td>
       <td><a href="./doc-files/rhino/MPL-1.1.txt">MPL 1.1</a> 
           (<a href="./doc-files/rhino/Rhino_License.htm">note</a>)</td>
       <td><a href="http://www.mozilla.org/rhino">
           http://www.mozilla.org/rhino</a></td>
       <td>Java implementation of JavaScript 1.5</td>
     </tr>
     <tr>
       <td>xbean.jar</td>
       <td>1.0.4</td>
       <td><a href="./doc-files/xmlbeans/LICENSE.txt">Apache 2.0</a>
           (<a href="./doc-files/xmlbeans/NOTICE.txt">note</a>)</td>
       <td><a href="http://svn.apache.org/repos/asf/xmlbeans/tags/1.0.4">
           http://svn.apache.org/repos/asf/xmlbeans/tags/1.0.4</a></td>
       <td>XML support for JavaScript's E4X capabilities</td>
     </tr>
     <tr>
       <td>jsr173_api.jar</td>
       <td>1.0.1</td>
       <td><a href="./doc-files/jsr173/ASF2.0.txt">Apache 2.0</a></td>
       <td><a href="http://dist.codehaus.org/stax">
           http://dist.codehaus.org/stax/distributions/stax-src-1.2.0.zip</a></td>
       <td>JSR173 support required by xmlbeans</td>
     </tr>
     <tr>
       <td>antlr.jar</td>
       <td>3.1.1</td>
       <td><a href="./doc-files/antlr/LICENSE.txt">BSD</a></td>
       <td><a href="http://www.antlr.org">http://www.antlr.org</a></td>
       <td>LR parser generator used to implement the RTSC IDL</td>
     </tr>
     <tr>
       <td>tar.jar</td>
       <td>2.5</td>
       <td>Public Domain</td>
       <td><a href="http://www.trustice.com/java/tar">
           http://www.trustice.com/java/tar</a></td>
       <td>tar file reader</td>
     </tr>
     </table> 

 *  @p
 *  In addition to the jars above, XDCtools requires the following
 *  third-party command line executables:
 *  @p(html)

     <table border="1">
     <tr>
       <th>Exe</th>
       <th>Version</th>
       <th>License</th>
       <th>From</th>
       <th>Description</th>
     </tr>
     <tr>
       <td>gmake</td>
       <td>3.81</td>
       <td><a href="./doc-files/gmake/COPYING">GPL v2</a></td>
       <td><a href="http://savannah.gnu.org/projects/make">
           http://savannah.gnu.org/projects/make</a></td>
       <td>command run by the `xdc` command to create and build packages</td>
     </tr>
     </table>
 *  @p
 *
 *  Although the following tools are not required, they are optionally shipped
 *  with XDCtools distributions to ensure consistent behavior across various
 *  development platforms.
 *  @p(html)
     <table border="1">
     <tr>
       <th>Exe</th>
       <th>Version</th>
       <th>License</th>
       <th>From</th>
       <th>Description</th>
     </tr>
     <tr>
       <td>zip, unzip</td>
       <td>2.3 and 5.50</td>
       <td><a href="./doc-files/zip/LICENSE.txt">info-zip</a></td>
       <td><a href="http://www.info-zip.org">http://www.info-zip.org</a></td>
       <td>command line utilities to zip and unzip package releases</td>
     </tr>
     <tr>
       <td>tar</td>
       <td>1.13</td>
       <td><a href="./doc-files/tar/COPYING">GPL v2</a></td>
       <td><a href="http://www.gnu.org/software/tar">
           http://www.gnu.org/software/tar</a></td>
       <td>command line utilities to archive package directories</td>
     </tr>
     <tr>
       <td>sh</td>
       <td>cygwin 1.5.25-15</td>
       <td><a href="./doc-files/cygwin/COPYING.txt">GPL v2</a></td>
       <td><a href="http://cygwin.com">http://cygwin.com</a></td>
       <td>(Windows only) korn shell compatible shell used by GNU make</td>
     </tr>
     </table>
 *  @p
 *  All other files that are part of XDCtools are licensed under either
 *  {@link ./doc-files/eclipse/epl-v10.html EPL v1.0} or dual-licensed under
 *  {@link ./doc-files/eclipse/edl-v10.html EDL v1.0}.
 */
package xdc.shelf [1, 0, 0] {
}
