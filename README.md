# FreakQuincy

A project exploring sound synthesis in C++. Build using the QT graphical environment.
Mainly following along with [Computational Music Synthesis](https://cs.gmu.edu/~sean/book/synthesis/) by Sean Luke.

## Dependencies
### Qt
I am using the open source [Qt SDK](https://www.qt.io/download-qt-installer?hsCtaTracking=9f6a2170-a938-42df-a8e2-a9f0b1d6cdce%7C6cb0de4f-9bb5-4778-ab02-bfb62735f3e5) for the UI of the application.
I'm using version 5.12.

I'm also using qmake as part of the build process

### fftw3
For handling the calculation of fourier transforms I'm using the [FFTW](http://www.fftw.org/) library. 

### spdlog
For logging purposes I'm using the header-only library [spdlog](https://github.com/gabime/spdlog)
I used: `brew install spdlog`

### Apple Frameworks
CoreFoundation, CoreAudio, CoreMidi

### Bundled dependencies
I am additionally using [RtAudio](https://www.music.mcgill.ca/~gary/rtaudio/), [RtMidi](https://www.music.mcgill.ca/~gary/rtmidi/) and [QCustomPlot](https://www.qcustomplot.com/) but these are 
included in the include/ src/ directories of the project itself so don't need to be pre-installed. 

## Compiling
__For now only targetting macOS__: There are Core libraries and frameworks used as part of the build process and in RtAudio & RtMidi. Compilation for other platforms will not work :(

### Create a Makefile from the FreakQuincy.pro file
Running `qmake` should generate the Makefile. 

For debug builds append `CONFIG=debug`

### Create a build and run application
Run `make` will create `FreakQuincy.app` in either `bin/debug` or `bin/release` (depending on your config). 
From the command line this can then be run with, for e.g., `bin/release/FreakQuincy.app/Contents/MacOS/FreakQuincy`

