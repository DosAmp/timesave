; TIMEREST: restore date/time from file

IDEAL
MODEL tiny

DATASEG
INCLUDE "common.inc"

msgerrread	DB "Error reading from file"
		endl
msgerrcorr	DB "Saved time corrupt"
		endl
succmsg:
	MSuccMsg <"Time restored as">

CODESEG
P8086
ORG 100h

_start:	DispatchFilename
	DosCall DOS_OPEN_FILE, 0	; read only, exclusive mode
	jnc s1	; call succeeded?
	OpenErrExit
s1:	mov bx, ax
	mov cx, SIZE datetime
	mov dx, offset datetime
	DosCall DOS_READ_FROM_HANDLE
	jc @@f2		; call failed?
	cmp ax, SIZE datetime	; short read?
	je @@s2
@@f2:	ErrExit msgerrread
@@s2:	DosCall DOS_CLOSE_FILE
	jnc @@s3
	; if DOS fails to close the file, something is seriously wrong
	DosCall DOS_TERMINATE_EXE, 1
@@s3:	cmp [datetime.combined.signature], sigtext
	jne @@invalid	; signature does not match?
	mov cx, (SIZE datetime)/2	; number of words
	xor dx, dx
	mov si, offset datetime
@@cl:	lodsw
	add dx, ax
	loop @@cl
	jz @@valid	; all words have to add to zero
@@invalid:
	ErrExit msgerrcorr
@@valid:
	mov cx, [datetime.combined.year]
	mov dx, [datetime.combined.monthday]
	DosCall DOS_SET_DATE
	mov cx, [datetime.combined.hourminute]
	mov dx, [datetime.combined.secondfrac]
	DosCall DOS_SET_TIME
	FillDatePlaceholders
	mov dx, offset succmsg
	DosCall DOS_WRITE_STRING
	DosCall DOS_TERMINATE_EXE, 0

INCLUDE "decimal.inc"

END _start
