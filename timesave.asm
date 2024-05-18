; TIMESAVE: save date/time to file
; see comments for related code in TIMEREST.ASM

IDEAL
MODEL tiny

DATASEG
INCLUDE "common.inc"

msgerrwrite	DB "Error writing to file"
		endl
succmsg:
	MSuccMsg <"Time saved as">

CODESEG
P8086
ORG 100h

_start:	DosCall DOS_GET_DATE
	mov [datetime.combined.year], cx
	mov [datetime.combined.monthday], dx
	DosCall DOS_GET_TIME
	mov [datetime.combined.hourminute], cx
	mov [datetime.combined.secondfrac], dx
	mov cx, (SIZE datetime)/2
	xor dx, dx	; start with zero...
	mov si, offset datetime
@@cl:	lodsw
	sub dx, ax	; ...and subtract all words from it
	loop @@cl
	mov [datetime.combined.checksum], dx
	DosCall DOS_GET_DISK_DRIVE
	add al, "A"
	mov [filepath.drive], al
	mov cx, DOS_ATTR_HIDDEN	; keep it hidden
	mov dx, offset filepath
	DosCall DOS_CREATE_FILE
	jnc @@s1
	mov [filepath.terminator], 0dh
	ErrExit msgerropen
@@s1:	mov bx, ax
	mov cx, SIZE datetime
	mov dx, offset datetime
	DosCall DOS_WRITE_TO_HANDLE
	; HACK: structure is short enough, so no partial writes are assumed
	jnc @@s2
	ErrExit msgerrwrite
@@s2:	DosCall DOS_CLOSE_FILE
	jnc @@s3
	DosCall DOS_TERMINATE_EXE, 1
@@s3:	FillDatePlaceholders
	mov dx, offset succmsg
	DosCall DOS_WRITE_STRING
	DosCall DOS_TERMINATE_EXE, 0

INCLUDE "decimal.inc"

END _start
