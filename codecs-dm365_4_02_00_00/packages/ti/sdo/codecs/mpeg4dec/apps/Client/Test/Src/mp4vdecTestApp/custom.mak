## THIS IS A GENERATED FILE -- DO NOT EDIT
.configuro: linker.cmd

linker.cmd: \
  package/cfg/mp4vdecTestApp_x470MV.o470MV \
  package/cfg/mp4vdecTestApp_x470MV.xdl
	$(SED) 's"^\"\(package/cfg/mp4vdecTestApp_x470MVcfg.cmd\)\"$""\"/db/swcoe_asp/DM360/Kaleido/dm360/mpeg4_decoder/Client/Test/Src/mp4vdecTestApp/\1\""' package/cfg/mp4vdecTestApp_x470MV.xdl > $@
