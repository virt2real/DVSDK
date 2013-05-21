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
var _infoJsObj = {};

var _infoJsFiles = {};

// [davor] the following code for converting JS objects to JSON and parsing
// JSON files is taken verbatim from json.org, except for marked modifications
// that prettify the output format so it is more readable. {
/*
    json.js
    2007-08-05

    Public Domain

    This file adds these methods to JavaScript:

        array.toJSONString()
        boolean.toJSONString()
        date.toJSONString()
        number.toJSONString()
        object.toJSONString()
        string.toJSONString()
            These methods produce a JSON text from a JavaScript value.
            It must not contain any cyclical references. Illegal values
            will be excluded.

            The default conversion for dates is to an ISO string. You can
            add a toJSONString method to any date object to get a different
            representation.

        string.parseJSON(filter)
            This method parses a JSON text to produce an object or
            array. It can throw a SyntaxError exception.

            The optional filter parameter is a function which can filter and
            transform the results. It receives each of the keys and values, and
            its return value is used instead of the original value. If it
            returns what it received, then structure is not modified. If it
            returns undefined then the member is deleted.

            Example:

            // Parse the text. If a key contains the string 'date' then
            // convert the value to a date.

            myData = text.parseJSON(function (key, value) {
                return key.indexOf('date') >= 0 ? new Date(value) : value;
            });

    It is expected that these methods will formally become part of the
    JavaScript Programming Language in the Fourth Edition of the
    ECMAScript standard in 2008.

    This file will break programs with improper for..in loops. See
    http://yuiblog.com/blog/2006/09/26/for-in-intrigue/

    This is a reference implementation. You are free to copy, modify, or
    redistribute.

    Use your own copy. It is extremely unwise to load untrusted third party
    code into your pages.
*/

/*jslint evil: true */

// Augment the basic prototypes if they have not already been augmented.
function augmentObjectPrototypeForJSON()
{
    if (Object.prototype.toJSONString) {
        return;
    }

    Array.prototype.toJSONString = function () {
        var a = [],     // The array holding the partial texts.
            i,          // Loop counter.
            l = this.length,
            v;          // The value to be stringified.


        // For each value in this array...

        for (i = 0; i < l; i += 1) {
            v = this[i];
            switch (typeof v) {
            case 'object':

                // Serialize a JavaScript object value. Ignore objects thats lack the
                // toJSONString method. Due to a specification error in ECMAScript,
                // typeof null is 'object', so watch out for that case.

                if (v) {
                    if (typeof v.toJSONString === 'function') {
                        a.push(v.toJSONString());
                    }
                } else {
                    a.push('null');
                }
                break;

            case 'string':
            case 'number':
            case 'boolean':
                a.push(v.toJSONString());

            // Values without a JSON representation are ignored.

            }
        }

        // Join all of the member texts together and wrap them in brackets.

        // [davor] commented out line below and replaced it with block that
        // prettifies the output
        // return '[' + a.join(',') + ']';
        var s = "[\n";
        for (var i = 0; i < a.length; i++) {
            var ai = "    " + a[i].replace( /\n/g, "\n    " );
            s += ai + ",\n";
        }
        s += "]";
        return s;
    };


    Boolean.prototype.toJSONString = function () {
        return String(this);
    };


    Date.prototype.toJSONString = function () {

        // Eventually, this method will be based on the date.toISOString method.

        function f(n) {

        // Format integers to have at least two digits.

            return n < 10 ? '0' + n : n;
        }

        return '"' + this.getUTCFullYear() + '-' +
                f(this.getUTCMonth() + 1) + '-' +
                f(this.getUTCDate()) + 'T' +
                f(this.getUTCHours()) + ': ' +
                f(this.getUTCMinutes()) + ': ' +
                f(this.getUTCSeconds()) + 'Z"';
    };


    Number.prototype.toJSONString = function () {

        // [davor] added toHex function
        function toHex(d) {
            var hD="0123456789ABCDEF";
            var h = "";
            for (var i=0;i<8;i++) {h=hD.substr(d&15,1)+h;d=d>>4}
            return "0x" + h;
        }

        // JSON numbers must be finite. Encode non-finite numbers as null.
        // [davor] replaced the format with hex if large
        // return isFinite(this) ? (toHex(this) : 'null';
        if (!isFinite(this)) {
            return 'null';
        }
        if ((this > 1000) || (this < -1000)) {
            return toHex(this);
        } else {
            return String(this);
        }
    };


    Object.prototype.toJSONString = function () {
        var a = [],     // The array holding the partial texts.
            k,          // The current key.
            v;          // The current value.

        // Iterate through all of the keys in the object, ignoring the proto chain
        // and keys that are not strings.

        for (k in this) {
            if (typeof k === 'string' &&
                    Object.prototype.hasOwnProperty.apply(this, [k])) {
                v = this[k];
                switch (typeof v) {
                case 'object':

                    // Serialize a JavaScript object value. Ignore objects that lack the
                    // toJSONString method. Due to a specification error in ECMAScript,
                    // typeof null is 'object', so watch out for that case.

                    if (v) {
                        if (typeof v.toJSONString === 'function') {
                            a.push(k.toJSONString() + ': ' + v.toJSONString());
                        }
                    } else {
                        a.push(k.toJSONString() + ': null');
                    }
                    break;

                case 'string':
                case 'number':
                case 'boolean':
                    a.push(k.toJSONString() + ': ' + v.toJSONString());

                // Values without a JSON representation are ignored.

                }
            }
        }

        // Join all of the member texts together and wrap them in braces.

        // [davor] commented out line below and replaced it with block that
        // prettifies the output
        //return '{' + a.join(',') + '}';
        var s = "{\n";
        for (var i = 0; i < a.length; i++) {
            var ai = "    " + a[i].replace( /\n/g, "\n    " );
            s += ai + ",\n";
        }
        s += "}";
        return s;
    };


    (function (s) {

        // Augment String.prototype. We do this in an immediate anonymous function to
        // avoid defining global variables.

        // m is a table of character substitutions.

        var m = {
            '\b': '\\b',
            '\t': '\\t',
            '\n': '\\n',
            '\f': '\\f',
            '\r': '\\r',
            '"' : '\\"',
            '\\': '\\\\'
        };


        s.parseJSON = function (filter) {
            var j;

            function walk(k, v) {
                var i;
                if (v && typeof v === 'object') {
                    for (i in v) {
                        if (Object.prototype.hasOwnProperty.apply(v, [i])) {
                            v[i] = walk(i, v[i]);
                        }
                    }
                }
                return filter(k, v);
            }


            // Parsing happens in three stages. In the first stage, we run the text against
            // a regular expression which looks for non-JSON characters. We are especially
            // concerned with '()' and 'new' because they can cause invocation, and '='
            // because it can cause mutation. But just to be safe, we will reject all
            // unexpected characters.

            // We split the first stage into 3 regexp operations in order to work around
            // crippling deficiencies in Safari's regexp engine. First we replace all
            // backslash pairs with '@' (a non-JSON character). Second we delete all of
            // the string literals. Third, we look to see if only JSON characters
            // remain. If so, then the text is safe for eval.
            if (/^[,:{}\[\]0-9.\-+Eaeflnr-u \n\r\t]*$/.test(this.
                    replace(/\\./g, '@').
                    replace(/"[^"\\\n\r]*"/g, ''))) {

                // In the second stage we use the eval function to compile the text into a
                // JavaScript structure. The '{' operator is subject to a syntactic ambiguity
                // in JavaScript: it can begin a block or an object literal. We wrap the text
                // in parens to eliminate the ambiguity.

                j = eval('(' + this + ')');

                // In the optional third stage, we recursively walk the new structure, passing
                // each name/value pair to a filter function for possible transformation.

                return typeof filter === 'function' ? walk('', j) : j;
            }

            // If the text is not JSON parseable, then a SyntaxError is thrown.

            throw new SyntaxError('parseJSON');
        };


        s.toJSONString = function () {

            // If the string contains no control characters, no quote characters, and no
            // backslash characters, then we can simply slap some quotes around it.
            // Otherwise we must also replace the offending characters with safe
            // sequences.

            if (/["\\\x00-\x1f]/.test(this)) {
                return '"' + this.replace(/[\x00-\x1f\\"]/g, function (a) {
                    var c = m[a];
                    if (c) {
                        return c;
                    }
                    c = a.charCodeAt();
                    return '\\u00' +
                        Math.floor(c / 16).toString(16) +
                        (c % 16).toString(16);
                }) + '"';
            }
            return '"' + this + '"';
        };
    })(String.prototype);
}
// } end json.org code [davor]


/*
 *  ======== deleteObjectPrototypeForJSON ========
 *  We call this when we're done JSON-ing. This way we can reuse the JSON code
 *  and not affect RTSC.
 */
function deleteObjectPrototypeForJSON()
{
    delete Array.prototype.toJSONString;
    delete Boolean.prototype.toJSONString;
    delete Date.prototype.toJSONString;
    delete Number.prototype.toJSONString;
    delete Object.prototype.toJSONString;
    delete String.prototype.toJSONstring;
}

/*
 *  ======== addObjectToProgramInfoFile ========
 */
function addObjectToProgramInfoFile( objName, obj )
{
    _infoJsObj[ objName ] = obj;

    // create a JSON string from the current _infoJsObj object
    augmentObjectPrototypeForJSON();
    var infoJsObjJSON = _infoJsObj.toJSONString();
    deleteObjectPrototypeForJSON();

    // write it immediately; that means we do a write every time someone adds
    // an object to program info file, but so what; this allows callers to be
    // in their validate() modules, plus there are very few calls to here
    var outFileName = "./package/info/" + Program.name + ".info.js";
    var outFile = java.io.File( outFileName );
    try {
        java.io.File( outFile.getParent() ).mkdirs();
        outFile["delete"]();
        var out = new java.io.BufferedWriter(
                      new java.io.FileWriter( outFileName ));
        out.write( infoJsObjJSON + "\n" );
        out.flush();
        out.close();
    } catch (e) {
        print( "Warning: failed to create .info.js file '" + outFileName + "'"+
               " for program '" + Program.name + "'. Reason: " + e );
    }
}


/*
 *  ======== validate ========
 */
function validate()
{
}

/*
 *  ======== parseInfoFile ========
 */
function parseInfoFile( infoJsFile )
{
    if (_infoJsFiles[ infoJsFile ] == undefined) {
        var inp = new java.io.BufferedReader(
                      new java.io.FileReader( infoJsFile));
        var line, jsonFileText = "";
        while (line = inp.readLine()) {
            jsonFileText += line + "";
        }

        if (0) {
            // parse applying filters etc.
            augmentObjectPrototypeForJSON();
            _infoJsFiles[ infoJsFile ] = jsonFileText.parseJSON();
            deleteObjectPrototypeForJSON();
        } else {
            _infoJsFiles[ infoJsFile ] = eval('(' + jsonFileText + ')');
        }
    }
    return _infoJsFiles[ infoJsFile ];
}
/*
 *  @(#) ti.sdo.ce.osal; 2, 0, 2,427; 12-2-2010 21:24:38; /db/atree/library/trees/ce/ce-r11x/src/ xlibrary

 */

