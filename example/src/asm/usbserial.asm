.assume adl = 1
segment data
.def _usb_PrePower
.def _usb_Cleanup
.def _srl_InitDevice
.def _srl_ConfigSerial
.def _srl_GetLineCoding
.def _srl_Write
.def _receive

include 'host.inc'
include 'debug.inc'

;group of equates from mateo's msd driver
;as we are not including ti84pce.inc:
saveSScreen		:= $0D0EA1F ; 21945 bytes

usbbuf			:= saveSScreen
usbbuf2			:= saveSScreen + 2048

__frameset0		:= $000130
__ladd			:= $00019C
_PutC			:= $0207B8
_PutS			:= $0207C0
_DispHL_s		:= $0207BC
_DispHL			:= $021EE0
_NewLine		:= $0207F0
_usb_IsBusPowered	:= $0003CC
_usb_BusPowered		:= $0003E4
_usb_SelfPowered	:= $0003E8
_Delay10ms		:= $0003B4
_DelayTenTimesAms	:= $0003B8
_MemClear		:= $0210DC
_HomeUp			:= $020828
_ClrLCDFull		:= $020808

flags			:= $D00080
mpTmrCtrl		:= $0F20030
bTmr3Enable		:= 6

mathprintFlags		:= $0044
mathprintEnabled	:= 5

pUsbRange		:= $03000
mpUsbRange		:= $0E20000
usbCapLen		:= $0000
pUsbCapLen		:= pUsbRange + usbCapLen
mpUsbCapLen		:= mpUsbRange + usbCapLen
usbHciVer		:= 0002h
pUsbHciVer		:= pUsbRange + usbHciVer
mpUsbHciVer		:= mpUsbRange + usbHciVer
usbHcsParams		:= 0004h
pUsbHcsParams		:= pUsbRange + usbHcsParams
mpUsbHcsParams		:= mpUsbRange + usbHcsParams
usbHccParams		:= 0008h
pUsbHccParams		:= pUsbRange + usbHccParams
mpUsbHccParams		:= mpUsbRange + usbHccParams
usbCmd			:= 0010h
pUsbCmd			:= pUsbRange + usbCmd
mpUsbCmd		:= mpUsbRange + usbCmd
usbSts			:= 0014h
pUsbSts			:= pUsbRange + usbSts
mpUsbSts		:= mpUsbRange + usbSts
usbInt			:= 0018h
pUsbInt			:= pUsbRange + usbInt
mpUsbInt		:= mpUsbRange + usbInt
usbFrIdx		:= 001Ch
pUsbFrIdx		:= pUsbRange + usbFrIdx
mpUsbFrIdx		:= mpUsbRange + usbFrIdx
usbPeriodicListBase	:= 0024h
pUsbPeriodicListBase	:= pUsbRange + usbPeriodicListBase
mpUsbPeriodicListBase	:= mpUsbRange + usbPeriodicListBase
usbAsyncListAddr	:= 0028h
pUsbAsyncListAddr	:= pUsbRange + usbAsyncListAddr
mpUsbAsyncListAddr	:= mpUsbRange + usbAsyncListAddr
usbPortSC		:= 0030h
pUsbPortSC		:= pUsbRange + usbPortSC
mpUsbPortSC		:= mpUsbRange + usbPortSC
usbMisc			:= 0040h
pUsbMisc		:= pUsbRange + usbMisc
mpUsbMisc		:= mpUsbRange + usbMisc
usbOtgCsr		:= 0080h
pUsbOtgCsr		:= pUsbRange + usbOtgCsr
mpUsbOtgCsr		:= mpUsbRange + usbOtgCsr
usbOtgIsr		:= 0084h
pUsbOtgIsr		:= pUsbRange + usbOtgIsr
mpUsbOtgIsr		:= mpUsbRange + usbOtgIsr
usbOtgIer		:= 0088h
pUsbOtgIer		:= pUsbRange + usbOtgIer
mpUsbOtgIer		:= mpUsbRange + usbOtgIer
usbIsr			:= 00C0h
pUsbIsr			:= pUsbRange + usbIsr
mpUsbIsr		:= mpUsbRange + usbIsr
usbImr			:= 00C4h
pUsbImr			:= pUsbRange + usbImr
mpUsbImr		:= mpUsbRange + usbImr
usbDevCtrl		:= 0100h
pUsbDevCtrl		:= pUsbRange + usbDevCtrl
mpUsbDevCtrl		:= mpUsbRange + usbDevCtrl
usbDevAddr		:= 0104h
pUsbDevAddr		:= pUsbRange + usbDevAddr
mpUsbDevAddr		:= mpUsbRange + usbDevAddr
usbDevTest		:= 0108h
pUsbDevTest		:= pUsbRange + usbDevTest
mpUsbDevTest		:= mpUsbRange + usbDevTest
usbSofFnr		:= 010Ch
pUsbSofFnr		:= pUsbRange + usbSofFnr
mpUsbSofFnr		:= mpUsbRange + usbSofFnr
usbSofMtr		:= 0110h
pUsbSofMtr		:= pUsbRange + usbSofMtr
mpUsbSofMtr		:= mpUsbRange + usbSofMtr
usbPhyTmsr		:= 0114h
pUsbPhyTmsr		:= pUsbRange + usbPhyTmsr
mpUsbPhyTmsr		:= mpUsbRange + usbPhyTmsr
usbCxsr			:= 011Ch
pUsbCxsr		:= pUsbRange + usbCxsr
mpUsbCxsr		:= mpUsbRange + usbCxsr
usbCxFifo		:= 0120h
pUsbCxFifo		:= pUsbRange + usbCxFifo
mpUsbCxFifo		:= mpUsbRange + usbCxFifo
usbIdle			:= 0124h
pUsbIdle		:= pUsbRange + usbIdle
mpUsbIdle		:= mpUsbRange + usbIdle
usbGimr			:= 0130h
pUsbGimr		:= pUsbRange + usbGimr
mpUsbGimr		:= mpUsbRange + usbGimr
usbCxImr		:= 0134h
pUsbCxImr		:= pUsbRange + usbCxImr
mpUsbCxImr		:= mpUsbRange + usbCxImr
usbFifoRxImr		:= 0138h
pUsbFifoRxImr		:= pUsbRange + usbFifoRxImr
mpUsbFifoRxImr		:= mpUsbRange + usbFifoRxImr
usbFifoTxImr		:= 013Ah
pUsbFifoTxImr		:= pUsbRange + usbFifoTxImr
mpUsbFifoTxImr		:= mpUsbRange + usbFifoTxImr
usbDevImr		:= 013Ch
pUsbDevImr		:= pUsbRange + usbDevImr
mpUsbDevImr		:= mpUsbRange + usbDevImr
usbGisr			:= 0140h
pUsbGisr		:= pUsbRange + usbGisr
mpUsbGisr		:= mpUsbRange + usbGisr
usbCxIsr		:= 0144h
pUsbCxIsr		:= pUsbRange + usbCxIsr
mpUsbCxIsr		:= mpUsbRange + usbCxIsr
usbFifoRxIsr		:= 0148h
pUsbFifoRxIsr		:= pUsbRange + usbFifoRxIsr
mpUsbFifoRxIsr		:= mpUsbRange + usbFifoRxIsr
usbFifoTxIsr		:= 014Ah
pUsbFifoTxIsr		:= pUsbRange + usbFifoTxIsr
mpUsbFifoTxIsr		:= mpUsbRange + usbFifoTxIsr
usbDevIsr		:= 014Ch
pUsbDevIsr		:= pUsbRange + usbDevIsr
mpUsbDevIsr		:= mpUsbRange + usbDevIsr
usbRxZlp		:= 0150h
pUsbRxZlp		:= pUsbRange + usbRxZlp
mpUsbRxZlp		:= mpUsbRange + usbRxZlp
usbTxZlp		:= 0154h
pUsbTxZlp		:= pUsbRange + usbTxZlp
mpUsbTxZlp		:= mpUsbRange + usbTxZlp
usbIsoEasr		:= 0158h
pUsbIsoEasr		:= pUsbRange + usbIsoEasr
mpUsbIsoEasr		:= mpUsbRange + usbIsoEasr
usbIep1			:= 0160h
pUsbIep1		:= pUsbRange + usbIep1
mpUsbIep1		:= mpUsbRange + usbIep1
usbIep2			:= 0164h
pUsbIep2		:= pUsbRange + usbIep2
mpUsbIep2		:= mpUsbRange + usbIep2
usbIep3			:= 0168h
pUsbIep3		:= pUsbRange + usbIep3
mpUsbIep3		:= mpUsbRange + usbIep3
usbIep4			:= 016Ch
pUsbIep4		:= pUsbRange + usbIep4
mpUsbIep4		:= mpUsbRange + usbIep4
usbIep5			:= 0170h
pUsbIep5		:= pUsbRange + usbIep5
mpUsbIep5		:= mpUsbRange + usbIep5
usbIep6			:= 0174h
pUsbIep6		:= pUsbRange + usbIep6
mpUsbIep6		:= mpUsbRange + usbIep6
usbIep7			:= 0178h
pUsbIep7		:= pUsbRange + usbIep7
mpUsbIep7		:= mpUsbRange + usbIep7
usbIep8			:= 017Ch
pUsbIep8		:= pUsbRange + usbIep8
mpUsbIep8		:= mpUsbRange + usbIep8
usbOep1			:= 0180h
pUsbOep1		:= pUsbRange + usbOep1
mpUsbOep1		:= mpUsbRange + usbOep1
usbOep2			:= 0184h
pUsbOep2		:= pUsbRange + usbOep2
mpUsbOep2		:= mpUsbRange + usbOep2
usbOep3			:= 0188h
pUsbOep3		:= pUsbRange + usbOep3
mpUsbOep3		:= mpUsbRange + usbOep3
usbOep4			:= 018Ch
pUsbOep4		:= pUsbRange + usbOep4
mpUsbOep4		:= mpUsbRange + usbOep4
usbOep5			:= 0190h
pUsbOep5		:= pUsbRange + usbOep5
mpUsbOep5		:= mpUsbRange + usbOep5
usbOep6			:= 0194h
pUsbOep6		:= pUsbRange + usbOep6
mpUsbOep6		:= mpUsbRange + usbOep6
usbOep7			:= 0198h
pUsbOep7		:= pUsbRange + usbOep7
mpUsbOep7		:= mpUsbRange + usbOep7
usbOep8			:= 019Ch
pUsbOep8		:= pUsbRange + usbOep8
mpUsbOep8		:= mpUsbRange + usbOep8
usbEp1Map		:= 01A0h
pUsbEp1Map		:= pUsbRange + usbEp1Map
mpUsbEp1Map		:= mpUsbRange + usbEp1Map
usbEp2Map		:= 01A1h
pUsbEp2Map		:= pUsbRange + usbEp2Map
mpUsbEp2Map		:= mpUsbRange + usbEp2Map
usbEp3Map		:= 01A2h
pUsbEp3Map		:= pUsbRange + usbEp3Map
mpUsbEp3Map		:= mpUsbRange + usbEp3Map
usbEp4Map		:= 01A3h
pUsbEp4Map		:= pUsbRange + usbEp4Map
mpUsbEp4Map		:= mpUsbRange + usbEp4Map
usbEp5Map		:= 01A4h
pUsbEp5Map		:= pUsbRange + usbEp5Map
mpUsbEp5Map		:= mpUsbRange + usbEp5Map
usbEp6Map		:= 01A5h
pUsbEp6Map		:= pUsbRange + usbEp6Map
mpUsbEp6Map		:= mpUsbRange + usbEp6Map
usbEp7Map		:= 01A6h
pUsbEp7Map		:= pUsbRange + usbEp7Map
mpUsbEp7Map		:= mpUsbRange + usbEp7Map
usbEp8Map		:= 01A7h
pUsbEp8Map		:= pUsbRange + usbEp8Map
mpUsbEp8Map		:= mpUsbRange + usbEp8Map
usbFifo0Map		:= 01A8h
pUsbFifo0Map		:= pUsbRange + usbFifo0Map
mpUsbFifo0Map		:= mpUsbRange + usbFifo0Map
usbFifo1Map		:= 01A9h
pUsbFifo1Map		:= pUsbRange + usbFifo1Map
mpUsbFifo1Map		:= mpUsbRange + usbFifo1Map
usbFifo2Map		:= 01AAh
pUsbFifo2Map		:= pUsbRange + usbFifo2Map
mpUsbFifo2Map		:= mpUsbRange + usbFifo2Map
usbFifo3Map		:= 01ABh
pUsbFifo3Map		:= pUsbRange + usbFifo3Map
mpUsbFifo3Map		:= mpUsbRange + usbFifo3Map
usbFifo0Cfg		:= 01ACh
pUsbFifo0Cfg		:= pUsbRange + usbFifo0Cfg
mpUsbFifo0Cfg		:= mpUsbRange + usbFifo0Cfg
usbFifo1Cfg		:= 01ADh
pUsbFifo1Cfg		:= pUsbRange + usbFifo1Cfg
mpUsbFifo1Cfg		:= mpUsbRange + usbFifo1Cfg
usbFifo2Cfg		:= 01AEh
pUsbFifo2Cfg		:= pUsbRange + usbFifo2Cfg
mpUsbFifo2Cfg		:= mpUsbRange + usbFifo2Cfg
usbFifo3Cfg		:= 01AFh
pUsbFifo3Cfg		:= pUsbRange + usbFifo3Cfg
mpUsbFifo3Cfg		:= mpUsbRange + usbFifo3Cfg
usbFifo0Csr		:= 01B0h
pUsbFifo0Csr		:= pUsbRange + usbFifo0Csr
mpUsbFifo0Csr		:= mpUsbRange + usbFifo0Csr
usbFifo1Csr		:= 01B4h
pUsbFifo1Csr		:= pUsbRange + usbFifo1Csr
mpUsbFifo1Csr		:= mpUsbRange + usbFifo1Csr
usbFifo2Csr		:= 01B8h
pUsbFifo2Csr		:= pUsbRange + usbFifo2Csr
mpUsbFifo2Csr		:= mpUsbRange + usbFifo2Csr
usbFifo3Csr		:= 01BCh
pUsbFifo3Csr		:= pUsbRange + usbFifo3Csr
mpUsbFifo3Csr		:= mpUsbRange + usbFifo3Csr
usbDmaFifo		:= 01C0h
pUsbDmaFifo		:= pUsbRange + usbDmaFifo
mpUsbDmaFifo		:= mpUsbRange + usbDmaFifo
usbDmaCtrl		:= 01C8h
pUsbDmaCtrl		:= pUsbRange + usbDmaCtrl
mpUsbDmaCtrl		:= mpUsbRange + usbDmaCtrl
usbDmaLen		:= 01C9h
pUsbDmaLen		:= pUsbRange + usbDmaLen
mpUsbDmaLen		:= mpUsbRange + usbDmaLen
usbDmaAddr		:= 01CCh
pUsbDmaAddr		:= pUsbRange + usbDmaAddr
mpUsbDmaAddr		:= mpUsbRange + usbDmaAddr

reqTypeSetLnCoding	:= $20
reqTypeGetLnCoding	:= $21

_usb_PrePower:
	call	usbBusPower
	pop	de
	pop	hl ; time in ms
	push	hl
	push	de
	call pause
	ret

_usb_Cleanup:
	push	ix
	push	iy
	call	usbCleanup
	pop	iy
	pop	ix
	ret

; Input:
;  hl = ms
; Output:
;  bc = ?
;  af = ?
;  de = ?
; credit: PT_
pause:
	ld	c, 110
_PauseInnerLoop1:
	ld	b, 32
_PauseInnerLoop2:
	djnz	_PauseInnerLoop2
	dec	c
	jr	nz, _PauseInnerLoop1
	or	a, a
	ld	de, -1
	add	hl, de
	jr	c, pause
	ret

; will have to change this once hubs are supported
_srl_InitDevice:
	push	ix
	push	iy
	call    usbInit				; init usb
	call    devFirst
	ld	(device),iy			; use first device
	ld	hl,usbbuf			; get dev desc
	ld	de,reqDevDesc18
	call    setup
	ld      hl,usbbuf+18			; get langids
	ld      de,reqGetStrDesc
	call    setup
	ld      hl,usbbuf+18+2
	ld      de,reqGetStrDesc+4
	ldi
	ldi
	ld	iy,(device)			; get configuration descriptor
	xor     a,a
	call    getConfigDescTotalLength	; total length of config
	ld      (reqConfDesc+wLength),hl
	xor	a,a
	ld	de,usbbuf
	adc	hl,de
	ld	(config_end),hl
	ld      hl,usbbuf
	ld      de,reqConfDesc
	call    setup
	ld	iy,(device)			; select config
	ld      ix,usbbuf
	call	devSelectConfig
	call	useConfig
	ld	a,0
	adc	a,a
	pop	iy
	pop	ix
	ret

; Output:
;  nc = err
useConfig:
	ld	hl,usbbuf
findCscInterface: ;credit MateoC
	ld	a,4				; interface descriptor type
	call	getDescriptor
	ret	nc
	xor	a,a
	ld	de,0
	ld	e,(iy+0)
	adc	hl,de
	ld	a,(iy+0)			; bLength
	cp	a,9
	jr	c,findCscInterface		; ensure interface length >= 9
	ld	a,(iy+5)
	cp	a,10				; bInterfaceClass == 10
	jr	nz,findCscInterface
	ld	a,(iy+2)
	;call	debugStr
	;db	'interface: ',0
	;call	debugHexA
	;call	debugNewLine
	xor	a,a
	sbc	hl,de
findEndpoints: ; credit MateoC
	push	hl
	pop	iy
	ld	b,(iy+4)
	ld	c,0
	ld	de,0
findEndpointsLoop:
	ld	a,5				; endpoint descriptor type
	call	getDescriptor
	ret	nc
	ld	a,(iy+2)
	bit	7,a
	jr	z,endpointOut
	bit	0,c
	jr	nz,endpointSkip
	ld	(ep_in),a
	;call	debugStr
	;db	'in: ',0
	;call	debugHexA
	;call	debugNewLine
	push	bc
	ld	bc,0
	ld	b,(iy+5)
	ld	c,(iy+4)
	ld	(maxPacketSize),bc
	pop	bc
	set	0,c
	jr	endpointSkip
endpointOut:
	bit	1,c
	jr	nz,endpointSkip
	ld	(ep_out),a
	;call	debugStr
	;db	'out: ',0
	;call	debugHexA
	;call	debugNewLine
	set	1,c
endpointSkip:
	;call	debugStr
	;db	'val: ',0
	;call	debugHexBC
	;call	debugNewLine
	ld	e,(iy+0)
	add	hl,de
	djnz	findEndpointsLoop
	ld	a,c
	cp	a,3
	jr	nz,endpointFail
	;call	debugStr
	;db	'valid endpoints',0
	;call	debugNewLine
	scf
	ret
endpointFail:
	scf
	ccf
	ret

;credit: MateoC
; Input:
;  hl = ptr in config
;   a = type
; Output:
;  nc = not found
;   c = found
getDescriptor:
	push	de
	push	bc
	ld	de,0
config_end := $ - 3
	ld	bc,0
findDescriptor:
	or	a,a
	sbc	hl,de
	add	hl,de
	jr	nc,notFoundDescriptor
	push	hl
	pop	iy
	ld	c,(hl)				; length of descriptor
	cp	a,(iy+1)			; bDescriptorType == 4
	jr	z,foundDescriptor
	add	hl,bc
	jr	findDescriptor
foundDescriptor:
	scf
notFoundDescriptor:
	pop	bc
	pop	de
	ret

_srl_ConfigSerial:
	pop	de
	pop	hl
	push	hl
	push	de
	push	ix
	ld	iy,(device)
	ld	de,reqLineCoding
	call	controlDefaultTransfer
	pop	ix
	ret

_srl_GetLineCoding:
	pop	de
	pop	hl
	push	hl
	push	de
	push	ix
	ld	iy,(device)
	ld	de,reqGetLineCoding
	push	hl
	call	controlDefaultTransfer
	call	qhWait
	pop	hl
	pop	ix
	ret

_srl_Write:
	pop	hl
	pop	de ; buffer
	pop	bc ; length
	push	bc
	push	de
	push	hl
	push	ix
	ld	iy,(device)
	ld	a,0
	ep_out := $-1
	call	bulkTransfer
	pop	ix
	ret

_receive:
	pop	hl
	pop	de ; buffer
	push	de
	push	hl
	push	ix
	ld	iy,(device)
	ld	a,0
	ep_in := $-1
	ld	bc,64 ; make more general
	maxPacketSize := $-3
	call	bulkTransfer
	call	qhReap
	xor	a,a
	ld	hl,(maxPacketSize)
	sbc	hl,bc
	pop	ix
	ret
	

; Input:
;  de = req
;  hl = buf
setup:
	ld	iy,0
	device := $ - 3
	call    controlDefaultTransfer
	jp      qhWait


reqDevDesc18:
	db	$80,reqTypeGetDesc,0,descTypeDev,0,0,18,0
reqConfDesc:
	db	$80,reqTypeGetDesc,1,descTypeConf,0,0,0,0,0
reqGetStrDesc:
	db	$80,reqTypeGetDesc,0,descTypeStr,0,0,0,1,0
lineCodingLen	:= 7
reqLineCoding:
	db	$21,reqTypeSetLnCoding,0,0,0,0,lineCodingLen,0
reqGetLineCoding:
	db	$A1,reqTypeGetLnCoding,0,0,0,0,lineCodingLen,0
lineCoding:
	db	$80,$25,0,0,0,0,8
