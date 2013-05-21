How to Build Codec Engine Applications without the Configuration (RTSC) Step
============================================================================

When you build an application that makes Codec Engine API calls, 
you must at some point run the configuration ("RTSC") step in its build flow; 
the configuration step analyzes your application config (.cfg) file, and
generates some C code to be included in your application and some linker 
instructions that list Codec Engine and other package libraries that your 
application must be linked with. This step requires that you have the XDC 
("RTSC") tools and all Codec Engine packages on your system when you build.

The involving configuration step, however, does not have to be present in the 
end-user's build -- a typical case is when you want to produce a Codec 
Engine-using subsystem that is itself not the final executable, but is given 
to an end-user who then links it against his code to produce the final 
executable.

How to achieve that goal is the topic of this section. In short, you will run 
the configuration step on your Codec Engine-using subsystem and perform a 
*partial linking* of your subsystem with the Codec Engine libraries. 
The resulting object file will have all the configuration built in, 
and will hide all Codec Engine APIs -- exposing a different set of 
appropriate APIs on its own -- that can be simply linked with the 
end-users application without any special steps or tools.


The basis: "video_copy/dualcpu" example
---------------------------------------

You should be familiar with the Codec Engine's "video_copy/dualcpu" example,
which is the Arm-side client that uses example "copy" video codecs on the DSP. 
The configuration-less "video_copy/dualcpu-separate_config" example 
differs from the original "video_copy/dualcpu" only in the makefiles, 
and in that some function prototypes are formally extracted into a header file; 
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

                                           
The separation: "video_copy/dualcpu-separate_config" example
------------------------------------------------------------

The source files from the original "video_copy/dualcpu" example have been 
split in two directories: "configured_CE_subsystem" and "enduser_app". 
When we build files in "configured_CE_subsystem", we get a partially linked 
object file, that we later link against the files in "enduser_app."

For this example, the build flow is illustrated here:
        
                     configured_CE_subsystem/
                     +---------------------------------------+
                     |                                       |
   enduser_app/      |                       +-------------+ |    
   .---------.       | .-----------.    .--> | generated C | |    
   |  app.c  | ----> | |  ceapp.c  | ---+    +-------------+ |    
   `---------'       | `-----------'    |    +-------------+ |    
                     |                  `--> |   CE libs   | |    
                     |                       +-------------+ |
                     |                              I        |
                     | .-----------.                I        |
                     | | ceapp.cfg | ===>[CONFIG]===*        |
                     | `-----------'                         |
                     |                                       |
                     | configured_CE_subsystem.o             |
                     |                                       |
                     | (partially linked object file)        |
                     +---------------------------------------+    


The provider's CE-using subsystem
---------------------------------

Directory "configured_CE_subsystem" contains the original "ceapp.c" and 
"ceapp.cfg", plus the slightly modified "makefile" from the original example. 
The modification to the makefile is that instead of invoking the compiler 
to produce the executable, we invoke the linker directly and pass the "-r" 
option to create a partially linked executable, "configured_CE_subsystem.o". 

Also, API implemented in "ceapp.c" is now formally listed in a header file, 
"ceapp.h".


The end-user's client application
---------------------------------

Directory "enduser_app" now contains the original app.c file 
(modified for cleanliness to now include "ceapp.h" API prototypes instead of 
declaring them in app.c), and a simple makefile that compiles app.c 
and links it against the provider's configured_CE_subsystem.o object file.

The makefile shows is what the end-users build will look like -- note that it 
does not involve running the configuration steps, or in fact pointing to any 
of the Codec Engine code.


Remarks
-------

There are several notes to keep in mind regarding this technique:

1) For the CE-using subsystem, we do not create a *library* but a 
   partially linked object file. The object file is the most convenient 
   container for the subsystem code -- a single file (not counting the 
   header file) that the end user needs for his build. We know that 
   all the necessary Codec Engine library code will find its way 
   into the object file, and nothing else -- not the unused Codec 
   Engine functions, and not the C library functions like strcpy(). 
   (E.g., Codec Engine uses strcpy(), but because the library containing it 
   has not been provided at the partial link step, strcpy() will remain 
   an unresolved reference in configured_CE_subsystem.o, and be resolved 
   only when the final executable is linked. That way we do not get 
   duplicate code.)

2) End-user application should not call any Codec Engine APIs directly. 
   If you want to expose a Codec Engine API (say, Memory_contigAlloc) 
   in the CE-using subsystem, create a wrapper for the original CE function 
   and expose the wrapper.

3) Each partially linked object file is built for exactly one configuration. 
   If you need to build the subsystem for several configurations and let the 
   user decide which one to use (for example, one with a set of high-quality 
   codecs, one with a set of low-quality codecs, one with debugging/diagnostics,
   one without and so on), built a separate partially linked file for each 
   configuration.

