EASy68k Command Line simulator port for unix/Linux
==================================================

I starting on a port of Jack Crenshaw's "Let's build a Compiler" series and I wanted a way to run the generated assembly.

I found this [EASy68K-asm](https://github.com/rayarachelian/EASy68K-asm) which made the assembler a command line application.
This program would compile .X86 files into a .S86 file that the simulator could load and run. The problem is the Simulator
was a Win32 application. I've extracted all the simulator code and ported it to Linux as a command line application.
I cut out breakpoints since this just needs to run application and I also cut out a lot of the IO sutff such as graphics rendering
and sound. This could be added back by rending the graphics and sound to either separate `.bmp`/`.wav` files, or a combined video file.
This application is good enough for my needs so I stopped here.

It shouldn't be too much work to add that stuff back if you're willing to take a shot.
