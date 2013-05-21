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

var dcs_imgarray = new Array;
var dcs_ptr = 0;
var dCurrent = new Date();
var DCS=new Object();
var WT=new Object();
var DCSext=new Object();

var dcsADDR = "63.96.161.95";
var dcsID = "";


if (dcsID == ""){
 var TagPath = dcsADDR;
} else {
 var TagPath = dcsADDR+"/"+dcsID;
}

function ParseQuery()
{
// an associative array for the query pairs to go in:
var Hash = new Array();

// check href first
if (document.location.href.indexOf("?") > 0) {

	// split the query string into an array of pairs:
	var Pairs = document.location.href.split('?')[1].split('&');
	// take each of those pairs...
	for (var i = 0; i < Pairs.length; i++)
	{
	// split it into an array of two...
	var OnePair = Pairs[i].split('=');
	// and use those values to create a new key/value pair
	// in our main array...
	Hash[OnePair[0]] = OnePair[1];
	}

}

return Hash;
}

function dcs_var(){
 WT.tz = dCurrent.getTimezoneOffset();
 WT.ul = navigator.appName=="Netscape" ? navigator.language : navigator.userLanguage;
 WT.cd = screen.colorDepth;
 WT.sr = screen.width+"x"+screen.height;
 WT.jo = navigator.javaEnabled() ? "Yes" : "No";
 WT.ti   = document.title;
 DCS.dcsdat = dCurrent.getTime();
 if ((window.document.referrer != "") && (window.document.referrer != "-")){
  if (!(navigator.appName == "Microsoft Internet Explorer" && parseInt(navigator.appVersion) < 4) ){
   DCS.dcsref = window.document.referrer;
  }
 }

 DCS.dcsuri = window.location.pathname;
 DCS.dcsqry = window.location.search;
 DCS.dcssip = window.location.hostname;

}

function A(N,V){
 return "&"+N+"="+escape(V);
}

function dcs_createImage(dcs_src)
{
 if (document.images){
  dcs_imgarray[dcs_ptr] = new Image;
  dcs_imgarray[dcs_ptr].src = dcs_src;
  dcs_ptr++;
 }
}

function dcsMeta(){
 var MRV="";
 var F=false;
 var myDocumentElements;
 if (document.all){
  F = true;
  myDocumentElements=document.all.tags("meta");
 }
 if (!F && document.documentElement){
  F = true;
  myDocumentElements=document.getElementsByTagName("meta");
 }
 if (F){
  for (var i=1; i<=myDocumentElements.length;i++){
   myMeta=myDocumentElements.item(i-1);
   if (myMeta.name.indexOf('WT.')==0){
    WT[myMeta.name.substring(3)]=myMeta.content;
   }
   if (myMeta.name.indexOf('DCSext.')==0){
    DCSext[myMeta.name.substring(7)]=myMeta.content;
   }
  }
 }
}

function dcs_TAG(TagImage){
 var P ="http"+(window.location.protocol.indexOf('https:')==0?'s':'')+"://"+TagImage+"/dcs.gif?";
 for (N in DCS){P+=A( N, DCS[N]);}
 for (N in WT){P+=A( "WT."+N, WT[N]);}
 for (N in DCSext){P+=A( N, DCSext[N]);}

 // alert(P);

 dcs_createImage(P);
}
// This is a sample of the function that would be called if you needed to re-run the script.
//function dcs_ReRun(URI,QRY){
// DCS.dcsuri = URI;
// DCS.dcsqry = QRY;
// dcs_TAG();
//}


// Arg #1 - always pass in "this"; current link object
// Arg #2 - WT report user ID; string object
// Arg #3 - link description; string object; standard format is "Fr: xxxx  To: xxxx"
// Arg #4 - campaign name; string object
function beaCTT(lu, id, ld, cn) {

	ll = location.pathname + location.search;

	if(ll.charAt(ll.length - 1) == '/') {

		ll = ll.slice(0, ll.length - 1);
	}

	if(location.hostname == lu.hostname) {

		lu = lu.pathname + lu.search;

		if(navigator.appName == 'Microsoft Internet Explorer') {

			lu = '/' + lu;
		}

	} else {

		lu = lu.href; 

		if(lu.charAt(lu.length - 1) == '/') {

			lu = lu.slice(0, lu.length - 1);
		}
	}

	DCS.dcssip  = "ctt.bea.com";
	DCS.dcsuri  = "/tracking.htm";

	DCS.dcsqry  = "?ct.id=" + (id ? escape(id) : escape("none")); // owner id
	DCS.dcsqry += "&ct.cn=" + (cn ? escape(cn) : escape("none")); // campaign name
	DCS.dcsqry += "&ct.ld=" + (ld ? escape(ld) : escape("none")); // link description
	DCS.dcsqry += "&ct.lu=" + (lu ? escape(lu) : escape("none")); // dest. link url 
	DCS.dcsqry += "&ct.ll=" + (ll ? escape(ll) : escape("none")); // link location

	dcs_TAG(TagPath);
}

function beaSCA(campaignName, stepNum) {

	DCS.dcssip  = "sca.d2d.bea.com";
	DCS.dcsuri  = "/";
	WT.si_n = campaignName;
	WT.si_x = stepNum;
	dcs_TAG(TagPath);
}

dcsMeta();
dcs_var();

