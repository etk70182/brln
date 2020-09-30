<p style="text-align: center;">
  <h1 align="center">BRLN</h1>
  <h2 align="center">A Free Software Synthesizer</h2>
</p>

![](https://github.com/etk70182/brln/workflows/build/badge.svg)
[![Coverage Status](https://coveralls.io/repos/github/etk70182/brln/badge.svg?branch=feature_branch)](https://coveralls.io/github/etk70182/brln?branch=feature_branch)
[![License: GPL v3](https://img.shields.io/badge/License-GPLv3-blue.svg)](https://www.gnu.org/licenses/gpl-3.0)
[![Lines of Code](https://tokei.rs/b1/github/etk70182/brln)](https://github.com/Aaronepower/tokei)
[![GitHub issues](https://img.shields.io/github/issues/etk70182/brln.svg)](https://GitHub.com/etk70182/brln/issues/)
[![GitHub issues-closed](https://img.shields.io/github/issues-closed/etk70182/brln.svg)](https://GitHub.com/etk70182/brln/issues?q=is%3Aissue+is%3Aclosed)
[![Average time to resolve an issue](http://isitmaintained.com/badge/resolution/etk70182/brln.svg)](http://isitmaintained.com/project/etk70182/brln "Average time to resolve an issue")

### Introduction

_brln_ is a free software synthesizer published under the GPL v3 license. _brln_ is implemented in C++14 and makes use of several libraries and frameworks such as [libpd](https://github.com/libpd/libpd/), [pure-data](https://github.com/pure-data/pure-data/), and [rtaudio](https://github.com/thestk/rtaudio) for the audio generation, [Qt](https://www.qt.io/) for the graphical user interface, and [googletest](https://github.com/google/googletest) for unit testing. This project makes use of [CMake](https://cmake.org/) to insure a consistent development experience for developers on Windows, MacOS, and Linux for building, testing and packaging the software. Also, this project follows the [Google's C++ style guide](https://google.github.io/styleguide/cppguide.html).

![An image of the brln software synthesizer](/resources/images/screenshot.png?raw=true "Screenshot of BRLN")

_brln_ started at the beginning of 2020 and is therefore still a very young project. Nevertheless the foundation is set for developing a fun synthesizer. The first version _brln-0.1.0_ consists of an application with a graphical user interface showing a knob which can change the output frequency of its pure-data patch. Feel free to contribute to the project by making _pull requests_ e.g., _raising issues_ or even making your own fork of the project. The project is primarily a fun project for educational purpose.

### Building from Source

#### Prerequisites

In order to build from source you need to install some prerequisites on your machine such as [Qt](https://www.qt.io/) and potentially some audio libraries.

##### Install Qt

This project makes use of the Qt-framework so therefore you need to have Qt installed on your machine in order to build the project.

* Ubuntu

  ```
  sudo apt-get install qt5-default
  ```

* MacOS/Windows

  For installing Qt on your MacOS or Windows machine please go to the [Official Qt Download](https://www.qt.io/download).

##### Install ALSA/Jack on Ubuntu

```
sudo apt-get update -y
sudo apt-get install -y libjack-dev libasound2-dev
```

##### Install Jack on MacOS

```
brew install jack
```

#### Build the Project

After you have installed the prerequisites for your machine we can download the repository from the GitHub server and build it.

```
git clone https://github.com/etk70182/brln.git
```
Change the directory and make a new build directory in it so we can build out of source.

```
cd brln
mkdir build
cd build
```
As a next step configure the project depending on your machine, compiler, and build tool.

```
cmake ..
```
Afterwards compile it.
```
cmake --build .
```

### Author

- [André Schlinke](https://github.com/etk70182)

### Credits

- [Pure Data](http://msp.ucsd.edu/software.html) by Miller Puckette and others
- [libpd](http://libpd.cc) by the Peter Brinkmann, Dan Wilcox and others
- [RtAudio](https://github.com/thestk/rtaudio) by Gary P. Scavone and others
- [googletest](https://github.com/google/googletest) by Google LLC
- [Qt](https://www.qt.io/) by Digia
- [CMake](https://cmake.org/) by Andy Cedilnik, Bill Hoffman, Brad King, Ken Martin, Alexander Neundorf
