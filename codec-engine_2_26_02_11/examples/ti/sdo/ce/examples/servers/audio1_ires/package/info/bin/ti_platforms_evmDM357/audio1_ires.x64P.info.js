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
        "programName": "bin/ti_platforms_evmDM357/audio1_ires.x64P",
        "algs": [
            {
                "mod": "ti.sdo.ce.examples.codecs.auddec1_ires.AUDDEC1_IRES",
                "pkg": "ti.sdo.ce.examples.codecs.auddec1_ires",
                "rpcProtocolVersion": 1,
                "iresFxns": "AUDDEC1_TI_IRES",
                "ialgFxns": "AUDDEC1_TI_AUDDECIRES",
                "threadAttrs": {
                    "priority": 2,
                },
                "serverFxns": "AUDDEC1_SKEL",
                "stubFxns": "AUDDEC1_STUBS",
                "name": "auddec1_ires",
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
                    "priority": 2,
                },
                "serverFxns": "AUDENC1_SKEL",
                "stubFxns": "AUDENC1_STUBS",
                "name": "audenc1_copy",
                "pkgVersion": [
                    "1, 0, 0",
                ],
            },
        ],
    },
}
