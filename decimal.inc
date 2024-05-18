; modified procedures for converting and storing decimal numbers

; store number with 4 fixed digits (0000..9999)
PROC Store4Digits
	mov si, offset thousand
	jmp short _StoreDigits
ENDP

; store number with 2 fixed digits (00..99)
PROC Store2Digits
	; HACK: first call of _StoreDigits clears AH, no need to clear it
	mov si, offset ten
	; slide directly into _StoreDigits
ENDP

PROC _StoreDigits
	mov dx, ax
@@nextdigit:
	lodsw	; get next power of ten
	test al, 1	; faster than CMP for even bases
	jne @@lastdigit
	mov cl, 0
@@count:
	sub dx, ax	; does it go into DX one more time?
	jb @@countdone	; it does not
	inc cl
	jmp @@count
@@countdone:
	add dx, ax	; adjust for overshoot
	mov al, cl
	add al, 30h	; 0 -> "0" etc.
	stosb
	jmp @@nextdigit
@@lastdigit:
	mov al, dl	; take the last digit as is
	add al, 30h
	stosb
	ret
ENDP
