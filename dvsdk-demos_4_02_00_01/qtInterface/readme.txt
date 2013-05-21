QT interface for DVSDK demos (GUI) project build instructions:

NOTE:  The following make variables may need to be set when building on
the command line:

    1.  PLATFORM  - This should be set to the platform you are interested
                    in (e.g. dm365)
    2.  EXEC_DIR  - This should point to the directory on your target file
                    system where the DVSDK demos are installed

For example, to build for the DM365, run the following:

qmake // Invoked this from the directory where the qtinterface.pro is found

To Build:
make PLATFORM=dm365

To Clean:
make PLATFORM=dm365 clean

To Export files:
make PLATFORM=dm365 EXEC_DIR=/home/user/targetfs/home/root/dm365/dvsdk-demos install
