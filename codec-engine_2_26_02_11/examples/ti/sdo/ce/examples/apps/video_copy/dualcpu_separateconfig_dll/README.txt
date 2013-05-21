How to Build Codec Engine Applications as Dynamically Loaded Libraries (.so's)
==============================================================================

When you encapsulate your Codec Engine (CE) application into a Dynamically 
Loaded Library (DLL) i.e. a ".so" file, you give your users maximum independence
from your internal build. Not only they do not need XDC tools to build their 
executable, they don't even need your CE application DLL until they actually
want to run it.

The key to building a CE application DLL (from now on referred to simply as 
"DLL") is to build an application later on top of CE -- that does whatever
your CE application is supposed to do -- and expose a simple API of your choice
to that layer. Such an application you build as a .so file, which the user's
final application dynamically loads as needed.

The API you choose should use only basic data types or your data types in header 
files you provide, without relying on CE data types. The user who dynamically 
loads your DLL calls only the API of your layer, so his application never needs
to include any of the CE's (or its components') header files.

This text talks about technical details needed to achive that goal.

!!!!
NOTE: This example may not work properly with DspLink 1.40.05.p1 and eariler
      versions (see remarks below)


The basis: "video_copy/dualcpu" example
---------------------------------------

This example is a DLL-ified cousin of "apps/video_copy/dualcpu_separateconfig"
example, and like that example, it is also vased on the original
apps/video_copy/dualcpu" example. You should be familiar with that example,
which is the Arm-side client that uses example "copy" video codecs on the DSP. 
The DLL-using "video_copy/dualcpu_separateconfig_dll" example 
differs from the original "video_copy/dualcpu" only in the makefiles, 
and in that some DLL system calls are added to the simulated client's C code;
the rest -- including the C code and the .cfg configuration code -- 
is unchanged.

The original "video_copy/dualcpu" example has three source files:

   * ceapp.c: this video encoding-decoding module is the CE-using subsystem: 
     it provides an API for decoding and encoding video buffers, but in terms 
     of common data types (char *, int, etc.), i.e. this API does not rely on
     Codec Engine data types. This subsystem is implemented to call Codec Engine
     API primitives and to combine them, presenting a different "multimedia"
     interface. This module is the core of the configuration-free subsystem 
     that exemplifies what you want to provide to the end-users.

   * app.c: this file represents an end-user application: it calls 
     simplified video encode/decode APIs that the CE-using subsystem provides, 
     without knowing anything about Codec Engine APIs.

   * ceapp.cfg: this RTSC configuration file directs how Codec Engine components
     are used.

The ceapp.c and ceapp.cfg files go together; app.c is merely a client 
for ceapp.c. Along this line we will separate the code into the CE subsystem 
and the end-user portions.

Here is an API example: ceapp.c implements a video encode function with the 
following prototype:

    int ceapp_encodeBuf(char *inBuf,      int inBufSize,
                        char *encodedBuf, int encodedBufSize)

In its implementation, this function sets XDM video buffers, 
calls Codec Engine's VIDENC_process() and checks return status. 
All that is hidden from the client in app.c who calls this function 
to encode the buffer obtained directly from reading a file.

The flow is illustrated in this diagram (arrows show which code block
calls which):
   
                                              +-------------+            
    .---------.         .-----------.    .--> | generated C |
    |  app.c  | ------> |  ceapp.c  | ---+    +-------------+
    `---------'         `-----------'    |    +-------------+
                                         `--> |   CE libs   |
                                              +-------------+
                                                     I
                        .-----------.                I
                        | ceapp.cfg | ===>[CONFIG]===*       
                        `-----------'                     

                                           
The separation: "video_copy/dualcpu_separate_config_dll" example
----------------------------------------------------------------

The source files from the original "video_copy/dualcpu" example have been 
split in two directories: "configured_CE_subsystem" and "enduser_app". 
When we build files in "configured_CE_subsystem", we get a shared object (.so)
file, i.e. the DLL, that we later link dynamically load from the application
in "enduser_app."

For this example, the build flow is illustrated here:
        
                     configured_CE_subsystem/
                     +---------------------------------------+
                     |                                       |
   enduser_app/      |                       +-------------+ |    
   .---------.       | .-----------.    .--> | generated C | |    
   |  app.c  | - - > | |  ceapp.c  | ---+    +-------------+ |    
   `---------'       | `-----------'    |    +-------------+ |    
                     |                  `--> |   CE libs   | |    
                     |                       +-------------+ |
                     |                              I        |
                     | .-----------.                I        |
                     | | ceapp.cfg | ===>[CONFIG]===*        |
                     | `-----------'                         |
                     |                                       |
                     | configured_CE_subsystem.so            |
                     |                                       |
                     | (shared object file, i.e. DLL)        |
                     +---------------------------------------+    


The provider's CE-using subsystem
---------------------------------

Directory "configured_CE_subsystem" contains the original "ceapp.c" and 
"ceapp.cfg", plus the slightly modified "makefile" from the original example. 
The modification to the makefile is that instead of asking the compiler 
to produce the executable, we ask it instead to produce a ".so" file by
specifying the "-shared" option, and by compiling each C file with "-fPIC"
("produce position-independent code") option.

Also, API implemented in "ceapp.c" is now formally listed in a header file, 
"ceapp.h".

Note: the original "ceapp.c" ceapp_exit() function has been modified to include 
a call to CERuntime_exit() which uninitializes and cleans up the Codec Engine. 
In everything-linked-in executables this is not necessary as it is automatically
called during the process exit() call.


The end-user's client application
---------------------------------

Directory "enduser_app" now contains the original app.c file, modified to
load the .so file dynamically instead of expecting to be linked with the
CE-using subsystem statically.

The modification for loading the DLL is as follows:

1) The end-user .C file includes <dlfcn.h> system header file for using DLLs

2) All "CE-using subsystem"'s APIs are declared as function pointers of the
   appropriate type. For example, for this original API function, 

       int ceapp_encodeBuf(char *inBuf,      int inBufSize,
                           char *encodedBuf, int encodedBufSize)

   this pointer is declared:
   
        int   (*fxn_ceapp_encodeBuf)( 
                    char *inBuf,      int   inBufSize,
                    char *encodedBuf, int   encodedBufSize );

3) The .so file is opened with the dlopen() system call:

       ceappDllHandle = dlopen( dllName, RTLD_LAZY );

4) Each original API is found via the dlsym() system call; for example, the
   "ceapp_encodebuf" is found as
   
       fxn_ceapp_encodeBuf = dlsym( ceappDllHandle, "ceapp_encodeBuf" );

   The original ceapp_encodeBuf() API is available as a public symbol in the
   ".so", and we locate it with dlsym() knowing its name, ""ceapp_encodeBuf",
   and store it in our local function pointer.
   
   All other global functions and variables in the ".so" file are still
   available for use (by locating them via dlsym()), but CE-subsystem users 
   do not need to know about them.
   
5) In the main processing loop, we call each dynamic functions as if it were  
   a local function that we had a pointer to:
      
       status = (*fxn_ceapp_encodeBuf)(inBuf,      INFRAMESIZE,
                                       encodedBuf, ENCODEDFRAMESIZE);
   
6) When we are finished with using the CE subsystem, we close the DLL with
   
       dlclose( ceappDllHandle );   
   
   NOTE: currently this call is commented out as a segmentation fault occurs
   on the next dlopen() or exit(); the DSP is being released and Codec Engine
   cleaned up but some other resources possibly not. This is currently being
   examined.
       
The makefile shows is what the end-users build will look like -- note that it 
does not involve running the configuration steps, or in fact pointing to any 
of the Codec Engine code. The linker is invoked with the "dl" library, with the
"-ldl" switch.


Remarks
-------

There are several notes to keep in mind regarding this technique:

1) End-user application should not call any Codec Engine APIs directly. 
   If you want to expose a Codec Engine API (say, Memory_contigAlloc) 
   in the CE-using subsystem, create a wrapper for the original CE function 
   and expose the wrapper.

2) Each DLL (.so) is built for exactly one configuration. 
   If you need to build the subsystem for several configurations and let the 
   user decide which one to use (for example, one with a set of high-quality 
   codecs, one with a set of low-quality codecs, one with debugging/diagnostics,
   one without and so on), built a separate DLL (.so) for each configuration.

3) DspLink 1.40.05.p1 and eariler has a bug in the Arm-side user library code
   (file _notify.c, doing pthread_cancel instead of signaling the thread to
   exit) that sometimes causes the .so example to segfault. If your DspLink
   is of version 1.40.05.p1 or eariler, or if you do not know what your
   DspLink version is, please contact Codec Engine support team. With an
   unpatched version of DspLink, your program may appear to work but it can
   crash under certain circumstances when you call CERuntime_exit().
