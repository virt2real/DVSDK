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
            "BUFMEM",
            {
                "addr": 0x10F0FB00,
                "type": "code",
                "size": 0x00000500,
                "gppAddr": 0x5CF0FB00,
            },
        ],
        [
            "L1DSRAM",
            {
                "addr": 0x10F04000,
                "type": "code",
                "size": 0x0000BB00,
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
                "size": 0x01000000,
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
        "programName": "bin/ti_platforms_evm2530/audio1_ires.x64P",
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
