;
; File generated by cc65 v 2.19 - Git 39df6f8
;
	.fopt		compiler,"cc65 v 2.19 - Git 39df6f8"
	.setcpu		"6502"
	.smart		on
	.autoimport	on
	.case		on
	.debuginfo	on
	.importzp	sp, sreg, regsave, regbank
	.importzp	tmp1, tmp2, tmp3, tmp4, ptr1, ptr2, ptr3, ptr4
	.macpack	longbranch
	.dbg		file, "vdc_control_label.c", 1565, 1543268877
	.dbg		file, "vdc_gui.h", 778, 1543280824
	.dbg		file, "F:\Software\Emulation\Commodore\Development\cc65\include/c128.h", 6518, 1645504250
	.dbg		file, "F:\Software\Emulation\Commodore\Development\cc65\include/_vic2.h", 10835, 1645504250
	.dbg		file, "F:\Software\Emulation\Commodore\Development\cc65\include/_sid.h", 3626, 1645504250
	.dbg		file, "F:\Software\Emulation\Commodore\Development\cc65\include/_vdc.h", 2827, 1645504250
	.dbg		file, "F:\Software\Emulation\Commodore\Development\cc65\include/_6526.h", 3962, 1645504249
	.dbg		file, "F:\Software\Emulation\Commodore\Development\cc65\include/peekpoke.h", 3108, 1645504251
	.dbg		file, "F:\Software\Emulation\Commodore\Development\cc65\include/string.h", 5187, 1645504251
	.dbg		file, "F:\Software\Emulation\Commodore\Development\cc65\include/stddef.h", 3057, 1645504251
	.dbg		file, "F:\Software\Emulation\Commodore\Development\cc65\include/stdio.h", 5920, 1645504251
	.dbg		file, "F:\Software\Emulation\Commodore\Development\cc65\include/stdarg.h", 2913, 1645504251
	.dbg		file, "F:\Software\Emulation\Commodore\Development\cc65\include/limits.h", 3580, 1645504251
	.dbg		file, "F:\Software\Emulation\Commodore\Development\cc65\include/stdlib.h", 5999, 1645504251
	.dbg		file, "F:\Software\Emulation\Commodore\Development\cc65\include/conio.h", 9026, 1645504250
	.dbg		file, "F:\Software\Emulation\Commodore\Development\cc65\include/target.h", 2992, 1645504251
	.dbg		file, "F:\Software\Emulation\Commodore\Development\cc65\include/cbm.h", 11892, 1645504250
	.dbg		file, "F:\Software\Emulation\Commodore\Development\cc65\include/cbm_filetype.h", 4949, 1645504250
	.dbg		file, "vdc_win.h", 1736, 1543282193
	.dbg		file, "vdc_core.h", 1814, 1543295196
	.dbg		file, "vdc_controls.h", 561, 1543268877
	.dbg		file, "vdc_menus.h", 527, 1543268877
	.dbg		file, "vdc_control_listbox.h", 1037, 1646425066
	.dbg		file, "vdc_control_textbox.h", 916, 1543268877
	.dbg		file, "vdc_control_label.h", 695, 1543268877
	.dbg		file, "vdc_control_button.h", 818, 1543268877
	.dbg		file, "vdc_control_checkbox.h", 815, 1543268877
	.dbg		sym, "malloc", "00", extern, "_malloc"
	.dbg		sym, "VDC_PetsciiToScreenCode", "00", extern, "_VDC_PetsciiToScreenCode"
	.dbg		sym, "VDC_RowColToAddress", "00", extern, "_VDC_RowColToAddress"
	.dbg		sym, "VDC_Poke", "00", extern, "_VDC_Poke"
	.dbg		sym, "CreateControl", "00", extern, "_CreateControl"
	.import		_malloc
	.import		_VDC_PetsciiToScreenCode
	.import		_VDC_RowColToAddress
	.import		_VDC_Poke
	.import		_CreateControl
	.export		_CreateLabel
	.export		__renderLabelHandler

; ---------------------------------------------------------------
; struct _LABEL *__near__ CreateLabel (struct Window *window, unsigned char *name, unsigned char x, unsigned char y, unsigned char *text)
; ---------------------------------------------------------------

.segment	"CODE"

.proc	_CreateLabel: near

	.dbg	func, "CreateLabel", "00", extern, "_CreateLabel"
	.dbg	sym, "window", "00", auto, 6
	.dbg	sym, "name", "00", auto, 4
	.dbg	sym, "x", "00", auto, 3
	.dbg	sym, "y", "00", auto, 2
	.dbg	sym, "text", "00", auto, 0
	.dbg	sym, "ctrl", "00", auto, -2
	.dbg	sym, "label", "00", auto, -4

.segment	"CODE"

	.dbg	line, "vdc_control_label.c", 14
	jsr     pushax
	.dbg	line, "vdc_control_label.c", 20
	jsr     decsp4
	ldy     #$0D
	jsr     pushwysp
	ldy     #$0D
	jsr     pushwysp
	ldy     #$0B
	lda     (sp),y
	jsr     pusha
	ldy     #$0B
	lda     (sp),y
	jsr     pusha
	ldx     #$00
	txa
	jsr     _CreateControl
	ldy     #$02
	jsr     staxysp
	.dbg	line, "vdc_control_label.c", 22
	cpx     #$00
	bne     L0005
	cmp     #$00
	beq     L0004
	.dbg	line, "vdc_control_label.c", 24
L0005:	ldx     #$00
	lda     #$04
	jsr     _malloc
	jsr     stax0sp
	.dbg	line, "vdc_control_label.c", 27
	ldy     #$03
	jsr     ldaxysp
	sta     ptr1
	stx     ptr1+1
	jsr     ldax0sp
	ldy     #$06
	sta     (ptr1),y
	iny
	txa
	sta     (ptr1),y
	.dbg	line, "vdc_control_label.c", 28
	jsr     ldax0sp
	sta     ptr1
	stx     ptr1+1
	ldy     #$03
	jsr     ldaxysp
	ldy     #$00
	sta     (ptr1),y
	iny
	txa
	sta     (ptr1),y
	.dbg	line, "vdc_control_label.c", 31
	ldy     #$03
	jsr     ldaxysp
	sta     ptr1
	stx     ptr1+1
	lda     #<(__renderLabelHandler)
	ldy     #$0F
	sta     (ptr1),y
	iny
	lda     #>(__renderLabelHandler)
	sta     (ptr1),y
	.dbg	line, "vdc_control_label.c", 32
	ldy     #$03
	jsr     ldaxysp
	sta     ptr1
	stx     ptr1+1
	lda     #$00
	ldy     #$11
	sta     (ptr1),y
	iny
	sta     (ptr1),y
	.dbg	line, "vdc_control_label.c", 35
	jsr     ldax0sp
	sta     ptr1
	stx     ptr1+1
	ldy     #$05
	jsr     ldaxysp
	ldy     #$02
	sta     (ptr1),y
	iny
	txa
	sta     (ptr1),y
	.dbg	line, "vdc_control_label.c", 37
	jsr     ldax0sp
	.dbg	line, "vdc_control_label.c", 41
L0004:	ldy     #$0C
	jmp     addysp

	.dbg	line
.endproc

; ---------------------------------------------------------------
; void __near__ _renderLabelHandler (struct Control *ctrl)
; ---------------------------------------------------------------

.segment	"CODE"

.proc	__renderLabelHandler: near

	.dbg	func, "_renderLabelHandler", "00", extern, "__renderLabelHandler"
	.dbg	sym, "ctrl", "00", auto, 0
	.dbg	sym, "label", "00", auto, -2
	.dbg	sym, "window", "00", auto, -4
	.dbg	sym, "c", "00", auto, -5
	.dbg	sym, "i", "00", auto, -7
	.dbg	sym, "addr", "00", auto, -9
	.dbg	sym, "maxAddr", "00", auto, -11

.segment	"CODE"

	.dbg	line, "vdc_control_label.c", 45
	jsr     pushax
	.dbg	line, "vdc_control_label.c", 46
	jsr     ldax0sp
	ldy     #$07
	jsr     pushwidx
	.dbg	line, "vdc_control_label.c", 47
	jsr     ldax0sp
	jsr     ldaxi
	ldy     #$09
	jsr     pushwidx
	.dbg	line, "vdc_control_label.c", 50
	jsr     decsp1
	jsr     push0
	.dbg	line, "vdc_control_label.c", 53
	ldy     #$04
	jsr     ldaxysp
	sta     ptr1
	stx     ptr1+1
	ldy     #$01
	lda     (ptr1),y
	sta     sreg
	ldy     #$08
	jsr     ldaxysp
	sta     ptr1
	stx     ptr1+1
	ldy     #$03
	ldx     #$00
	lda     (ptr1),y
	clc
	adc     sreg
	bcc     L0007
	inx
L0007:	jsr     pushax
	ldy     #$06
	jsr     ldaxysp
	sta     ptr1
	stx     ptr1+1
	ldy     #$00
	lda     (ptr1),y
	sta     sreg
	ldy     #$0A
	jsr     ldaxysp
	sta     ptr1
	stx     ptr1+1
	ldy     #$02
	ldx     #$00
	lda     (ptr1),y
	clc
	adc     sreg
	bcc     L0008
	inx
L0008:	jsr     _VDC_RowColToAddress
	jsr     pushax
	.dbg	line, "vdc_control_label.c", 56
	ldy     #$06
	jsr     ldaxysp
	sta     ptr1
	stx     ptr1+1
	ldy     #$01
	lda     (ptr1),y
	sta     sreg
	ldy     #$0A
	jsr     ldaxysp
	sta     ptr1
	stx     ptr1+1
	ldy     #$03
	ldx     #$00
	lda     (ptr1),y
	clc
	adc     sreg
	bcc     L0009
	inx
L0009:	jsr     pushax
	ldy     #$08
	jsr     ldaxysp
	sta     ptr1
	stx     ptr1+1
	ldy     #$00
	lda     (ptr1),y
	sta     sreg
	ldy     #$08
	jsr     ldaxysp
	sta     ptr1
	stx     ptr1+1
	ldy     #$02
	ldx     #$00
	lda     (ptr1),y
	clc
	adc     sreg
	bcc     L000A
	inx
L000A:	jsr     _VDC_RowColToAddress
	jsr     pushax
	.dbg	line, "vdc_control_label.c", 58
	ldy     #$08
	jsr     ldaxysp
	sta     ptr1
	stx     ptr1+1
	ldy     #$04
	lda     (ptr1),y
	beq     L0006
	.dbg	line, "vdc_control_label.c", 59
	ldx     #$00
	lda     #$01
	jsr     subeq0sp
	.dbg	line, "vdc_control_label.c", 62
	jmp     L0006
	.dbg	line, "vdc_control_label.c", 63
L0003:	ldy     #$03
	jsr     ldaxysp
	ldy     #$00
	cmp     (sp),y
	txa
	iny
	sbc     (sp),y
	bvc     L000B
	eor     #$80
L000B:	bpl     L0006
	.dbg	line, "vdc_control_label.c", 64
	ldy     #$05
	jsr     pushwysp
	ldy     #$04
	ldx     #$00
	lda     #$01
	jsr     addeqysp
	ldy     #$08
	ldx     #$00
	lda     (sp),y
	jsr     _VDC_PetsciiToScreenCode
	jsr     _VDC_Poke
	.dbg	line, "vdc_control_label.c", 62
L0006:	ldy     #$0A
	jsr     ldaxysp
	ldy     #$03
	jsr     ldaxidx
	sta     ptr1
	stx     ptr1+1
	ldy     #$05
	jsr     ldaxysp
	clc
	adc     ptr1
	sta     ptr1
	txa
	adc     ptr1+1
	sta     ptr1+1
	ldy     #$00
	lda     (ptr1),y
	ldy     #$06
	sta     (sp),y
	cmp     #$00
	jsr     boolne
	php
	ldy     #$04
	lda     #$01
	jsr     addeqysp
	plp
	bne     L0003
	.dbg	line, "vdc_control_label.c", 66
	ldy     #$0D
	jmp     addysp

	.dbg	line
.endproc

