{
    "DSP memory map": [
        [
            "DDR2",
            {
                "addr": 0x8FA00000,
                "type": "main",
                "size": 0x00400000,
            },
        ],
        [
            "RESET_VECTOR",
            {
                "addr": 0x8FF00000,
                "type": "reset",
                "size": 128,
            },
        ],
        [
            "DDRALGHEAP",
            {
                "addr": 0x88000000,
                "type": "other",
                "size": 0x07A00000,
            },
        ],
        [
            "DSPLINKMEM",
            {
                "addr": 0x8FE00000,
                "type": "link",
                "size": 0x00100000,
            },
        ],
    ],
    "server algorithms": {
        "programName": "bin/ti_platforms_evmDM357/all.x64P",
        "algs": [
            {
                "mod": "ti.sdo.ce.examples.codecs.viddec_copy.VIDDEC_COPY",
                "pkg": "ti.sdo.ce.examples.codecs.viddec_copy",
                "rpcProtocolVersion": 3,
                "ialgFxns": "VIDDECCOPY_TI_VIDDECCOPY",
                "threadAttrs": {
                    "priority": 2,
                },
                "groupId": 0,
                "serverFxns": "VIDDEC_SKEL",
                "stubFxns": "VIDDEC_STUBS",
                "name": "viddec_copy",
                "pkgVersion": [
                    "1, 0, 0",
                ],
            },
            {
                "mod": "ti.sdo.ce.examples.codecs.videnc_copy.VIDENC_COPY",
                "pkg": "ti.sdo.ce.examples.codecs.videnc_copy",
                "rpcProtocolVersion": 3,
                "idma3Fxns": "VIDENCCOPY_TI_IDMA3",
                "ialgFxns": "VIDENCCOPY_TI_VIDENCCOPY",
                "threadAttrs": {
                    "priority": 2,
                },
                "groupId": 0,
                "serverFxns": "VIDENC_SKEL",
                "stubFxns": "VIDENC_STUBS",
                "name": "videnc_copy",
                "pkgVersion": [
                    "1, 0, 0",
                ],
            },
            {
                "mod": "ti.sdo.ce.examples.codecs.imgdec_copy.IMGDEC_COPY",
                "pkg": "ti.sdo.ce.examples.codecs.imgdec_copy",
                "rpcProtocolVersion": 3,
                "ialgFxns": "IMGDECCOPY_TI_IMGDECCOPY",
                "threadAttrs": {
                    "priority": 3,
                },
                "groupId": 1,
                "serverFxns": "IMGDEC_SKEL",
                "stubFxns": "IMGDEC_STUBS",
                "name": "imgdec_copy",
                "pkgVersion": [
                    "1, 0, 0",
                ],
            },
            {
                "mod": "ti.sdo.ce.examples.codecs.imgenc_copy.IMGENC_COPY",
                "pkg": "ti.sdo.ce.examples.codecs.imgenc_copy",
                "rpcProtocolVersion": 3,
                "ialgFxns": "IMGENCCOPY_TI_IMGENCCOPY",
                "threadAttrs": {
                    "priority": 3,
                },
                "groupId": 1,
                "serverFxns": "IMGENC_SKEL",
                "stubFxns": "IMGENC_STUBS",
                "name": "imgenc_copy",
                "pkgVersion": [
                    "1, 0, 0",
                ],
            },
            {
                "mod": "ti.sdo.ce.examples.codecs.auddec_copy.AUDDEC_COPY",
                "pkg": "ti.sdo.ce.examples.codecs.auddec_copy",
                "rpcProtocolVersion": 3,
                "ialgFxns": "AUDDECCOPY_TI_IAUDDECCOPY",
                "threadAttrs": {
                    "priority": 4,
                },
                "groupId": 2,
                "serverFxns": "AUDDEC_SKEL",
                "stubFxns": "AUDDEC_STUBS",
                "name": "auddec_copy",
                "pkgVersion": [
                    "1, 0, 0",
                ],
            },
            {
                "mod": "ti.sdo.ce.examples.codecs.audenc_copy.AUDENC_COPY",
                "pkg": "ti.sdo.ce.examples.codecs.audenc_copy",
                "rpcProtocolVersion": 3,
                "ialgFxns": "AUDENCCOPY_TI_AUDENCCOPY",
                "threadAttrs": {
                    "priority": 4,
                },
                "groupId": 2,
                "serverFxns": "AUDENC_SKEL",
                "stubFxns": "AUDENC_STUBS",
                "name": "audenc_copy",
                "pkgVersion": [
                    "1, 0, 0",
                ],
            },
            {
                "mod": "ti.sdo.ce.examples.codecs.sphenc_copy.SPHENC_COPY",
                "pkg": "ti.sdo.ce.examples.codecs.sphenc_copy",
                "rpcProtocolVersion": 3,
                "ialgFxns": "SPHENCCOPY_TI_SPHENCCOPY",
                "threadAttrs": {
                    "priority": 4,
                },
                "groupId": 2,
                "serverFxns": "SPHENC_SKEL",
                "stubFxns": "SPHENC_STUBS",
                "name": "sphenc_copy",
                "pkgVersion": [
                    "1, 0, 0",
                ],
            },
            {
                "mod": "ti.sdo.ce.examples.codecs.sphdec_copy.SPHDEC_COPY",
                "pkg": "ti.sdo.ce.examples.codecs.sphdec_copy",
                "rpcProtocolVersion": 3,
                "ialgFxns": "SPHDECCOPY_TI_SPHDECCOPY",
                "threadAttrs": {
                    "priority": 4,
                },
                "groupId": 2,
                "serverFxns": "SPHDEC_SKEL",
                "stubFxns": "SPHDEC_STUBS",
                "name": "sphdec_copy",
                "pkgVersion": [
                    "1, 0, 0",
                ],
            },
            {
                "mod": "ti.sdo.ce.examples.codecs.scale.SCALE_TI",
                "pkg": "ti.sdo.ce.examples.codecs.scale",
                "rpcProtocolVersion": 1,
                "ialgFxns": "SCALE_TI_SCALE",
                "threadAttrs": {
                    "priority": 2,
                },
                "serverFxns": "SCALE_SKEL",
                "stubFxns": "SCALE_STUBS",
                "name": "scale",
                "pkgVersion": [
                    "1, 0, 0",
                ],
            },
            {
                "mod": "ti.sdo.ce.examples.codecs.viddec2_copy.VIDDEC2_COPY",
                "pkg": "ti.sdo.ce.examples.codecs.viddec2_copy",
                "rpcProtocolVersion": 0,
                "ialgFxns": "VIDDEC2COPY_TI_IVIDDEC2COPY",
                "threadAttrs": {
                    "priority": 2,
                },
                "groupId": 0,
                "serverFxns": "VIDDEC2_SKEL",
                "stubFxns": "VIDDEC2_STUBS",
                "name": "viddec2_copy",
                "pkgVersion": [
                    "1, 0, 0",
                ],
            },
            {
                "mod": "ti.sdo.ce.examples.codecs.videnc1_copy.VIDENC1_COPY",
                "pkg": "ti.sdo.ce.examples.codecs.videnc1_copy",
                "rpcProtocolVersion": 0,
                "idma3Fxns": null,
                "ialgFxns": "VIDENC1COPY_TI_IVIDENC1COPY",
                "threadAttrs": {
                    "priority": 2,
                },
                "groupId": 0,
                "serverFxns": "VIDENC1_SKEL",
                "stubFxns": "VIDENC1_STUBS",
                "name": "videnc1_copy",
                "pkgVersion": [
                    "1, 0, 0",
                ],
            },
            {
                "mod": "ti.sdo.ce.examples.codecs.imgdec1_copy.IMGDEC1_COPY",
                "pkg": "ti.sdo.ce.examples.codecs.imgdec1_copy",
                "rpcProtocolVersion": 1,
                "ialgFxns": "IMGDEC1COPY_TI_IIMGDEC1COPY",
                "threadAttrs": {
                    "priority": 3,
                },
                "groupId": 1,
                "serverFxns": "IMGDEC1_SKEL",
                "stubFxns": "IMGDEC1_STUBS",
                "name": "imgdec1_copy",
                "pkgVersion": [
                    "1, 0, 0",
                ],
            },
            {
                "mod": "ti.sdo.ce.examples.codecs.imgenc1_copy.IMGENC1_COPY",
                "pkg": "ti.sdo.ce.examples.codecs.imgenc1_copy",
                "rpcProtocolVersion": 1,
                "ialgFxns": "IMGENC1COPY_TI_IIMGENC1COPY",
                "threadAttrs": {
                    "priority": 3,
                },
                "groupId": 1,
                "serverFxns": "IMGENC1_SKEL",
                "stubFxns": "IMGENC1_STUBS",
                "name": "imgenc1_copy",
                "pkgVersion": [
                    "1, 0, 0",
                ],
            },
            {
                "mod": "ti.sdo.ce.examples.codecs.sphdec1_copy.SPHDEC1_COPY",
                "pkg": "ti.sdo.ce.examples.codecs.sphdec1_copy",
                "rpcProtocolVersion": 0,
                "ialgFxns": "SPHDEC1COPY_TI_ISPHDEC1COPY",
                "threadAttrs": {
                    "priority": 4,
                },
                "groupId": 2,
                "serverFxns": "SPHDEC1_SKEL",
                "stubFxns": "SPHDEC1_STUBS",
                "name": "sphdec1_copy",
                "pkgVersion": [
                    "1, 0, 0",
                ],
            },
            {
                "mod": "ti.sdo.ce.examples.codecs.sphenc1_copy.SPHENC1_COPY",
                "pkg": "ti.sdo.ce.examples.codecs.sphenc1_copy",
                "rpcProtocolVersion": 0,
                "ialgFxns": "SPHENC1COPY_TI_ISPHENC1COPY",
                "threadAttrs": {
                    "priority": 4,
                },
                "groupId": 2,
                "serverFxns": "SPHENC1_SKEL",
                "stubFxns": "SPHENC1_STUBS",
                "name": "sphenc1_copy",
                "pkgVersion": [
                    "1, 0, 0",
                ],
            },
            {
                "mod": "ti.sdo.ce.examples.codecs.auddec1_copy.AUDDEC1_COPY",
                "pkg": "ti.sdo.ce.examples.codecs.auddec1_copy",
                "rpcProtocolVersion": 1,
                "ialgFxns": "AUDDEC1COPY_TI_IAUDDEC1COPY",
                "threadAttrs": {
                    "priority": 4,
                },
                "groupId": 2,
                "serverFxns": "AUDDEC1_SKEL",
                "stubFxns": "AUDDEC1_STUBS",
                "name": "auddec1_copy",
                "pkgVersion": [
                    "1, 0, 0",
                ],
            },
            {
                "mod": "ti.sdo.ce.examples.codecs.audenc1_copy.AUDENC1_COPY",
                "pkg": "ti.sdo.ce.examples.codecs.audenc1_copy",
                "rpcProtocolVersion": 1,
                "ialgFxns": "AUDENC1COPY_TI_IAUDENC1COPY",
                "threadAttrs": {
                    "priority": 4,
                },
                "groupId": 2,
                "serverFxns": "AUDENC1_SKEL",
                "stubFxns": "AUDENC1_STUBS",
                "name": "audenc1_copy",
                "pkgVersion": [
                    "1, 0, 0",
                ],
            },
            {
                "mod": "ti.sdo.ce.examples.codecs.g711.G711ENC",
                "pkg": "ti.sdo.ce.examples.codecs.g711",
                "rpcProtocolVersion": 0,
                "ialgFxns": "G711ENC_SUN_IG711ENC",
                "threadAttrs": {
                    "priority": 4,
                },
                "groupId": 2,
                "serverFxns": "SPHENC1_SKEL",
                "stubFxns": "SPHENC1_STUBS",
                "name": "g711enc",
                "pkgVersion": [
                    "1, 0, 0",
                ],
            },
            {
                "mod": "ti.sdo.ce.examples.codecs.g711.G711DEC",
                "pkg": "ti.sdo.ce.examples.codecs.g711",
                "rpcProtocolVersion": 0,
                "ialgFxns": "G711DEC_SUN_IG711DEC",
                "threadAttrs": {
                    "priority": 4,
                },
                "groupId": 2,
                "serverFxns": "SPHDEC1_SKEL",
                "stubFxns": "SPHDEC1_STUBS",
                "name": "g711dec",
                "pkgVersion": [
                    "1, 0, 0",
                ],
            },
            {
                "mod": "ti.sdo.ce.examples.codecs.vidtranscode_copy.VIDTRANSCODE_COPY",
                "pkg": "ti.sdo.ce.examples.codecs.vidtranscode_copy",
                "rpcProtocolVersion": 1,
                "ialgFxns": "VIDTRANSCODECOPY_TI_IVIDTRANSCODECOPY",
                "threadAttrs": {
                    "priority": 2,
                },
                "serverFxns": "VIDTRANSCODE_SKEL",
                "stubFxns": "VIDTRANSCODE_STUBS",
                "name": "vidtranscode_copy",
                "pkgVersion": [
                    "1, 0, 0",
                ],
            },
            {
                "mod": "ti.sdo.ce.examples.codecs.vidanalytics_copy.VIDANALYTICS_COPY",
                "pkg": "ti.sdo.ce.examples.codecs.vidanalytics_copy",
                "rpcProtocolVersion": 1,
                "ialgFxns": "VIDANALYTICSCOPY_TI_IVIDANALYTICSCOPY",
                "threadAttrs": {
                    "priority": 2,
                },
                "serverFxns": "VIDANALYTICS_SKEL",
                "stubFxns": "VIDANALYTICS_STUBS",
                "name": "vidanalytics_copy",
                "pkgVersion": [
                    "1, 0, 0",
                ],
            },
            {
                "mod": "ti.sdo.ce.examples.codecs.viddec1_copy.VIDDEC1_COPY",
                "pkg": "ti.sdo.ce.examples.codecs.viddec1_copy",
                "rpcProtocolVersion": 0,
                "ialgFxns": "VIDDEC1COPY_TI_IVIDDEC1COPY",
                "threadAttrs": {
                    "priority": 2,
                },
                "groupId": 0,
                "serverFxns": "VIDDEC1_SKEL",
                "stubFxns": "VIDDEC1_STUBS",
                "name": "viddec1_copy",
                "pkgVersion": [
                    "1, 0, 0",
                ],
            },
            {
                "mod": "ti.sdo.ce.examples.codecs.viddec2split_copy.VIDDEC2BACK_COPY",
                "pkg": "ti.sdo.ce.examples.codecs.viddec2split_copy",
                "rpcProtocolVersion": 0,
                "ialgFxns": "VIDDEC2BACKCOPY_TI_IVIDDEC2BACKCOPY",
                "threadAttrs": {
                    "priority": 2,
                },
                "groupId": 0,
                "serverFxns": "VIDDEC2BACK_SKEL",
                "stubFxns": "VIDDEC2BACK_STUBS",
                "name": "viddec2back_copy",
                "pkgVersion": [
                    "1, 0, 0",
                ],
            },
            {
                "mod": "ti.sdo.ce.examples.codecs.universal_copy.UNIVERSAL_COPY",
                "pkg": "ti.sdo.ce.examples.codecs.universal_copy",
                "rpcProtocolVersion": 1,
                "ialgFxns": "UNIVERSALCOPY_TI_IUNIVERSALCOPY",
                "threadAttrs": {
                    "priority": 2,
                },
                "serverFxns": "UNIVERSAL_SKEL",
                "stubFxns": "UNIVERSAL_STUBS",
                "name": "universal_copy",
                "pkgVersion": [
                    "1, 0, 0",
                ],
            },
        ],
    },
}
