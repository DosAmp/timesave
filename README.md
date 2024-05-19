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

As of v20240519, an alternative file name can be passed as a sole program argument.
Files created in this way are not marked hidden, unlike TIMESAVE.DAT in its default location.

## Structure of TIMESAVE.DAT

The save file consists of 6 little-endian words, resulting in a total of 12 bytes.

| Offset | Value                    | Remarks
|-------:|--------------------------|-------------------------------------------------
|      0 | Signature                | Always 0x5354 (`TS`)
|      2 | Checksum                 | all words including the checksum total to zero
|      4 | Year                     | full four-digit year, not 1980-based
|      6 | Month and day            | as passed in DX register of DOS date functions
|      8 | Hour and minute          | as passed in CX register of DOS time functions
|     10 | Seconds and centiseconds | as passed in DX register of DOS time functions

## Building

TimeSave is written using Borland Turbo Assembler 2.0. A suitable makefile is supplied. Type `make` to build the programs,
or `make -DDEBUG` to assemble and link with debug information suitable for Turbo Debugger.

It can be assembled using contemporary versions of Turbo Assembler, but debug information is not retained in COM programs during linking.

## Screenshot

![scrshot](https://github.com/DosAmp/timesave/assets/592891/73d54c76-0644-40f5-b653-384af2e87d3d)
