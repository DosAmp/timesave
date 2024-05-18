# TimeSave

TimeSave lets you save and restore the current date and time under DOS.
It's designed for PCs that don't have a working real-time clock (like pre-ATs without an extension card) or an unreliable one.

The name is also a pun because it saves you time setting a sensible system time on boot.

## Usage

TimeSave consists of two programs:

* TIMESAVE.COM: saves the current date and time in a file called TIMESAVE.DAT in the root of the current drive
* TIMEREST.COM: sets the current date and time based on that file

It's a good idea to start TIMEREST.COM in your AUTOEXEC.BAT before anything that needs current timestamps.
TIMESAVE.COM can be started at any time, like at the end of a batch file after you've exited Windows.

## Building

TimeSave is written using Turbo Assembler. A suitable makefile is supplied. Type `make` to build the programs,
or `make -DDEBUG` to assemble and link with debug information suitable for Turbo Debugger.

## Screenshot

![scrshot](https://github.com/DosAmp/timesave/assets/592891/73d54c76-0644-40f5-b653-384af2e87d3d)
