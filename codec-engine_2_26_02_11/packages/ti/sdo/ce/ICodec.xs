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
 *  ======== getCreationStackSize ========
 *  Default implementation of getCreationStackSize
 */
function getCreationStackSize(prog)
{
    /* use 128 integers for the creation stack */
    var size = 128 * prog.build.target.stdTypes.t_Int.size;

    print("Warning: " + this.$name
        + " did not supply a creation stack size; assuming "
        + size + " bytes is sufficient.");

    return (size);
}

/*
 *  ======== getDaramScratchSize ========
 *  Default implementation of getDaramScratchSize
 */
function getDaramScratchSize(prog)
{
    var size = 0;

    print("Warning: " + this.$name
        + " did not supply a max DARAM scratch size; assuming "
        + size + " bytes is sufficient.");

    return (size);
}

/*
 *  ======== getSaramScratchSize ========
 *  Default implementation of getSaramScratchSize
 */
function getSaramScratchSize(prog)
{
    var size = 0;

    print("Warning: " + this.$name
        + " did not supply a max SARAM scratch size; assuming "
        + size + " bytes is sufficient.");

    return (size);
}

/*
 *  ======== getStackSize ========
 *  Default implementation of getStackSize
 */
function getStackSize(prog)
{
    /* use 1024 integers for the stack */
    var size = 1024 * prog.build.target.stdTypes.t_Int.size;

    print("Warning: " + this.$name
        + " did not supply a stack size; assuming "
        + size + " bytes is sufficient.");

    return (size);
}

/*
 *  ======== getUUID ========
 */
function getUUID()
{
    if (this.uuid == null) {
        /* compute CRC32 as a 32-bit hash of the alg's unique name */
        var bytes = (new java.lang.String(this.$name)).getBytes();
        var crc = new java.util.zip.CRC32();
        crc.update(bytes, 0, bytes.length);
        var uuid = crc.getValue();

        this.$unseal("uuid");  /* should just remove "readonly" attr in .xdc */
        this.uuid = uuid;
        this.$seal("uuid");

        /* print("generated UUID for " + this.$name + ": " + uuid); */
    }

    return (this.uuid);
}
/*
 *  @(#) ti.sdo.ce; 1, 0, 6,432; 12-2-2010 21:19:08; /db/atree/library/trees/ce/ce-r11x/src/ xlibrary

 */

