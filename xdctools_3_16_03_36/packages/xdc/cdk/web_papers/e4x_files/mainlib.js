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
function trackClick(param) {
  imgName = param;
  document[imgName].src = siteurl+'images/common/nav_'+imgName+'.gif';
}	
/**/

/*
// This method modifies the url
function goTo(param1,param2) {
  url = param1;
  trackVar = param2;
  newUrl = url + '?from=' + trackVar;
  document.location.href = newUrl;
}
*/
function openWindow(path) {
   popupwin = window.open(path, "popupwin", "HEIGHT=635,WIDTH=670,status,scrollbars,resizable") 
}

function feedbackAgreementCheck() {
    // check if the "no" button is selected
    if (document._agreement.agreed[0].checked) {
        window.open("/techtrack/feedbackagreementwarning.jsp", "popupwin", "HEIGHT=335,WIDTH=670,status,scrollbars,resizable");
        return false;
    }
    document._agreement.submit();
}
