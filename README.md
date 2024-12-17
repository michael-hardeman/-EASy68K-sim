EASy68k Command Line simulator port for unix/Linux
==================================================

I was starting Jack Crenshaw's "Let's build a Compiler" series and I wanted a way to run the generated assembly so I could write some sanity tests.

I found this [EASy68K-asm](https://github.com/rayarachelian/EASy68K-asm) which would allow me to assemble the assembly, but I needed a bit more.
The simulator was still a Win32 application and I wanted a terminal based way to run the tests.
I've extracted all the simulator code and ported it to Linux as a terminal application.
I cut out breakpoints since this just needs to run the code and I also cut out a lot of the IO sutff such as graphics rendering
and sound. This could be added back by rending the graphics and sound to either separate `.bmp`/`.wav` files, or a combined video file.
This application is good enough for my needs so I stopped here.

It shouldn't be too much work to add that stuff back if you're willing to take a shot.

Building
--------

    make

Installing
----------

    sudo make install

Uninstall
---------

    sudo make uninstall

Usage
-----
asy68k cli 68000 simulator Version 331777 based on source code from http://www.easy68k.com/
Distributed under the GNU General Public Use License. The software is not warranted in any way. Use at your own risk.

Ported to the *nix CLI so it can be used in a Makefile workflow w/o WINE by Michael Hardeman December 2024

Usage:
   asy68ksim {options} file1.S68 {file2.S68} ... {fileN.S68}

(Options with "default:" are enabled, use --no-{option} to turn off, i.e. --no-list)
    --print-registers       default: log registers to stdout after program is run
    --{register}={value}             test register for the supplied value. exit with error code if test failed.
                                     Valid registers are D0-8, A0-8, PC, and SR

Running Tests
-------------
You can automate testing for example running:

    ./asy68ksim --no-print-registers --D0=65535 examples/neg1.S68

will execute successfully. but running:

    ./asy68ksim --no-print-registers --D0=65534 examples/neg1.S68

will cause the program to exit unsuccessfully with the message:

    D0 Test failed! Expected: 65534 Actual: 65535
