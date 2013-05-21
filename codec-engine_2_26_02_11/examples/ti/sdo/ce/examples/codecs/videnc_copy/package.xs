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
 *  ======== package.xs ========
 *
 */
function getLibs(prog)
{
    var name = "";

    var suffix = prog.build.target.findSuffix(this);
    if (suffix == null) {
        return ("");
    }

    /*
     * Note that we did a check in close() to ensure .useDMA is only set
     * if we have a library that supports it (e.g. C64P).
     */
    if (this.VIDENC_COPY.useDMA) {
        name = "lib/videnc_copy_dma.a" + suffix;
    } else {
        name = "lib/videnc_copy.a" + suffix;
    }

    /* return the library name: name.a<arch> */
    print("    will link with " + this.$name + ":" + name);

    return (name);
}


/*
 *  ======== Package.close ========
 *  Close this package; optionally (re)set other config parameters in the
 *  model
 */
function close()
{
//    print(this.$name + ".close() ...");
    var prog = Program;

    /*
     * If we're not on a 64, and .useDMA is set, we're "smart" and reset
     * the .useDMA to false, printing an appropriate warning.
     */
    if ((prog.build.target.suffix.match("64|674") == null) &&
        (this.VIDENC_COPY.useDMA)) {

        print("Warning.  The " + this.$name + " package doesn't have a " +
            "library which supports DMA for the " + prog.build.target.name +
            " target.  Setting .useDMA to \"false\".");
        this.VIDENC_COPY.useDMA = false;
    }

    /* If the .useDMA is false, clear the idma3Fxns config param. */
    if (!this.VIDENC_COPY.useDMA) {
        /* Unseal the readonly config param first.  Use $unseal with care. */
        this.VIDENC_COPY.$unseal("idma3Fxns");
        this.VIDENC_COPY.idma3Fxns = null;
        this.VIDENC_COPY.$seal("idma3Fxns");
    }
}
/*
 *  @(#) ti.sdo.ce.examples.codecs.videnc_copy; 1, 0, 0,262; 12-2-2010 21:23:14; /db/atree/library/trees/ce/ce-r11x/src/ xlibrary

 */

