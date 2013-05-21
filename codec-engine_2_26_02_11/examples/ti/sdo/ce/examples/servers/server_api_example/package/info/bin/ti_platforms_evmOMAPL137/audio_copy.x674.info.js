{
    "DSP memory map": [
        [
            "SDRAM",
            {
                "addr": 0xC2C00000,
                "type": "main",
                "size": 0x00300000,
            },
        ],
        [
            "RESET_VECTOR",
            {
                "addr": 0xC2F00000,
                "type": "reset",
                "size": 0x00001000,
            },
        ],
        [
            "DDRALGHEAP",
            {
                "addr": 0xC3000000,
                "type": "other",
                "size": 8,
            },
        ],
        [
            "DSPLINKMEM",
            {
                "addr": 0xC2F01000,
                "type": "link",
                "size": 0x000FF000,
            },
        ],
    ],
    "server algorithms": {
        "programName": "bin/ti_platforms_evmOMAPL137/audio_copy.x674",
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
