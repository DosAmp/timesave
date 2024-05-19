; Equates, structures, variables and macros common to both binaries
; should be included from DATASEG

INCLUDE "dos_.inc"
DOS_ATTR_HIDDEN = 2

; hurray for little endian
sigtext = "ST"

; Unfortunately the older version of the assembler does not allow unions
; inside structs, so we have to define a union of structs instead.
STRUC combinedtime
	signature	DW sigtext
	checksum	DW 0	; all words have to add to zero
	year		DW ?	; DOS_GET_DATE CX
	monthday	DW ?	; DOS_GET_DATE DX
	hourminute	DW ?	; DOS_GET_TIME CX
	secondfrac	DW ?	; DOS_GET_TIME DX
ENDS
STRUC splittime
	signature	DW ?	; only one part of a union can be
	checksum	DW ?	; initialized
	year		DW ?
	day		DB ?
	month		DB ?
	minute		DB ?
	hour		DB ?
	secondfrac	DB ?
	secondfull	DB ?
ENDS
UNION timespec
	combined	combinedtime <>
	split		splittime <>
ENDS

STRUC pathspec
	drive		DB ?	; set to current drive
	pathtail	DB ":\TIMESAVE.DAT"
	terminator	DB 0	; also CR in case of error message
ENDS

PSP_CMDLEN  = 80h
PSP_CMDLINE = 82h

isdefpath	DB 1
msgerropen	DB "Error opening file "
filepath	pathspec <>
		DB 0ah, "$"
datetime	timespec <>

; shortened lookup table of powers of 10 for decimal procedures
thousand	DW 1000
		DW 100
ten		DW 10
		DW 1

MACRO endl
	DB 0dh, 0ah, "$" ; CRLF + dollar terminator
ENDM
; construct success message with date placeholders for both binaries
MACRO MSuccMsg prefix
		DB prefix
		DB " "
succyear	DB 4 DUP(?)
		DB "-"
succmonth	DB 2 DUP(?)
		DB "-"
succday		DB 2 DUP(?)
		DB " "
succhour	DB 2 DUP(?)
		DB ":"
succminute	DB 2 DUP(?)
		DB ":"
succsecond	DB 2 DUP(?)
		endl
ENDM

; because we were not macro enough
MACRO DosCall func, minor
	IFNB <minor>
		mov ax, func * 256 + minor
	ELSE
		mov ah, func
	ENDIF
	int DOS_FUNCTION
ENDM

MACRO DispatchFilename
	LOCAL default, end
	xor ax, ax
	mov al, [byte PSP_CMDLEN]
	sub al, 1
	jle default
	mov si, offset msgerropen
	mov di, PSP_CMDLINE-(SIZE msgerropen)
	mov cx, SIZE msgerropen
	rep movsb
	add di, ax
	mov al, 0
	stosb
	mov ax, 240ah
	stosw
	mov [isdefpath], 0
	mov dx, PSP_CMDLINE
	jmp short end
default:
	DosCall DOS_GET_DISK_DRIVE
	add al, "A"	; returned drive is zero-based
	mov [filepath.drive], al
	mov dx, offset filepath
end:
ENDM

; print error message from label and exit
MACRO ErrExit msg
	mov dx, offset msg
	DosCall DOS_WRITE_STRING
	DosCall DOS_TERMINATE_EXE, 1
ENDM

MACRO OpenErrExit
	LOCAL default, notfound
	test [isdefpath], 1
	jnz default
	mov dx, PSP_CMDLINE-(SIZE msgerropen)
	; screw it, I don't care to remember filename length
	; for the error message
	mov di, dx
	mov al, 0
notfound:
	scasb
	jne notfound
	mov al, 0dh	; overwrite zero with CR
	dec di
	stosb
	DosCall DOS_WRITE_STRING
	DosCall DOS_TERMINATE_EXE, 1
default:
	mov [filepath.terminator], 0dh	; add CR to LF
	ErrExit msgerropen
ENDM

; moved from DECIMAL.INC for one-pass assembly
MACRO FillDatePlaceholders
	mov di, offset succyear
	mov ax, [datetime.split.year]
	call Store4Digits
	mov di, offset succmonth
	mov al, [datetime.split.month]
	call Store2Digits
	mov di, offset succday
	mov al, [datetime.split.day]
	call Store2Digits
	mov di, offset succhour
	mov al, [datetime.split.hour]
	call Store2Digits
	mov di, offset succminute
	mov al, [datetime.split.minute]
	call Store2Digits
	mov di, offset succsecond
	mov al, [datetime.split.secondfull]
	call Store2Digits
ENDM
