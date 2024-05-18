; excerpt from Borland's DOS.INC include file
; contains only symbolic equates used in these programs

DOS_FUNCTION         = 021h ; DOS function call

DOS_WRITE_STRING     = 009h ; Display a '$' terminated string
DOS_GET_DISK_DRIVE   = 019h ; Get the current disk drive
DOS_GET_DATE         = 02Ah ; Get the DOS Date
DOS_SET_DATE         = 02Bh ; Set the DOS Date
DOS_GET_TIME         = 02Ch ; Get the DOS Time
DOS_SET_TIME         = 02Dh ; Set the DOS Time
DOS_CREATE_FILE      = 03Ch ; Create or truncate a file
DOS_OPEN_FILE        = 03Dh ; Open an existing file
DOS_CLOSE_FILE       = 03Eh ; Close a file
DOS_READ_FROM_HANDLE = 03Fh ; Read from DOS file handle
DOS_WRITE_TO_HANDLE  = 040h ; Write to File Handle
DOS_TERMINATE_EXE    = 04Ch ; Terminate program
