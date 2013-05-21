{
    "DSP memory map": [
        [
            "L4PER",
            {
                "addr": 0x49000000,
                "type": "other",
                "size": 0x00800000,
            },
        ],
        [
            "DDR2",
            {
                "addr": 0x82C00000,
                "type": "main",
                "size": 0x00300000,
            },
        ],
        [
            "L1DSRAM",
            {
                "addr": 0x10F04000,
                "type": "code",
                "size": 0x0000C000,
                "gppAddr": 0x5CF04000,
            },
        ],
        [
            "RESET_VECTOR",
            {
                "addr": 0x82F00000,
                "type": "reset",
                "size": 0x00001000,
            },
        ],
        [
            "DDRALGHEAP",
            {
                "addr": 0x83000000,
                "type": "other",
                "size": 0x00001000,
            },
        ],
        [
            "L4CORE",
            {
                "addr": 0x48000000,
                "type": "other",
                "size": 0x01000000,
            },
        ],
        [
            "DSPLINKMEM",
            {
                "addr": 0x82F01000,
                "type": "link",
                "size": 0x000FF000,
            },
        ],
        [
            "CMEM",
            {
                "addr": 0,
                "type": "other",
                "size": 0,
            },
        ],
    ],
    "server algorithms": {
        "programName": "bin/ti_platforms_evm2530/audio_copy.x64P",
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
