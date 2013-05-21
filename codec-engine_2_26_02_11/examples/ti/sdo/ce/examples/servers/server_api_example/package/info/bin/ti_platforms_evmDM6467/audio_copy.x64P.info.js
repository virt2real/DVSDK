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
                "addr": 0x8F9FFFF8,
                "type": "other",
                "size": 8,
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
        "programName": "bin/ti_platforms_evmDM6467/audio_copy.x64P",
        "algs": [
            {
                "mod": "ti.sdo.ce.examples.codecs.auddec_copy.AUDDEC_COPY",
                "pkg": "ti.sdo.ce.examples.codecs.auddec_copy",
                "rpcProtocolVersion": 3,
                "ialgFxns": "AUDDECCOPY_TI_IAUDDECCOPY",
                "threadAttrs": {
                    "priority": 2,
                },
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
                    "priority": 2,
                },
                "serverFxns": "AUDENC_SKEL",
                "stubFxns": "AUDENC_STUBS",
                "name": "audenc_copy",
                "pkgVersion": [
                    "1, 0, 0",
                ],
            },
        ],
    },
}
