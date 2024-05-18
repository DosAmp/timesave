# hello, Unix!
AS = tasm
LD = tlink
!if $d(DEBUG)
ASFLAGS = /zi /w2 /l
LDFLAGS = /v /t
!else
ASFLAGS = /z /t
LDFLAGS = /t
!endif

.asm.obj:
	$(AS) $(ASFLAGS) $<

all:	timerest.com timesave.com
clean:
	-@del *.map
	-@del *.com
	-@del *.lst
	-@del *.obj

timerest.com: timerest.obj
	$(LD) $(LDFLAGS) $*,
timesave.com: timesave.obj
	$(LD) $(LDFLAGS) $*,
timerest.obj: timerest.asm common.inc dos_.inc
timesave.obj: timesave.asm common.inc dos_.inc
