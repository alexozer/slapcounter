# sLap Counter

The sLap Counter is an intelligent, personal poolside lap counter with smartphone integration.

## Installation

### Getting Ready - The Toolbox

#### OS X

Before starting, please make sure you have those installed:

*	[Arduino IDE 1.0.x](http://arduino.cc/en/main/software#toc2) - Download the app from the website
*	[Homebrew](http://mxcl.github.io/homebrew/) - Follow the instructions on their website
*	[Git](http://git-scm.com/) - use `brew install git` to install the latest version
*   [Teensyduino](https://www.pjrc.com/teensy/td_download.html) - follow the instructions for Arduino IDE 1.0.6

#### Linux

Before starting we need to install `git` and `arduino`:

```Bash
# First add the git-core ppa
$ sudo add-apt-repository ppa:git-core/ppa

# Update list
$ sudo apt-get update && sudo apt-get upgrade

# Install git 2.x.x and Arduino 1.0.x
$ sudo apt-get install git arduino
```

### Install `avr-gcc`, `binutils`, `avr-libc` and `avrdude`

#### OS X

```Bash
$ brew tap WeAreLeka/avr
$ brew install avr-libc
$ brew install avrdude
```

Check that everything has been installed properly by running `avr-gcc -v` and `avrdude -v`.

#### Linux

```Bash
$ sudo apt-get install gcc-avr binutils avr-libc avrdude
```

Make sure everything is up and running by running `avr-gcc -v` and `avrdude -v`.

### 2. Clone `slapcounter` repository from Github

Simply clone the repo:

```Bash
$ git clone https://github.com/alexozer/slapcounter
```

Initialize and update submodules:

```Bash
$ cd slapcounter
$ git submodule update --init --recursive
```

### Compile and upload code to your sLap Counter

Copy the appropriate Makefile to your project dir:

```Bash
# if you are on OS X
$ cp Makefile-OSX.mk src/Makefile

# or if you're running Linux
$ cp Makefile-Linux.mk src/Makefile
```

Then replace the PROJECT_DIR variable in the Makefile with the path of the project.
This can be obtained by running:

```Bash
$ pwd
```

Then compile and upload your code to the sLap Counter:

```Bash
$ cd src
$ make upload
```

### Updating sLap Counter software

```Bash
$ git pull
$ make upload
```
