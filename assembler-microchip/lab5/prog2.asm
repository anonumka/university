.def count			= r19 ; счетчик
.def el_arr_c		= r20 ; текущий элемент массива C
.def count_c		= r21 ; длинна заполненой части массива C
.def min_el			= r22 
.set start_min		= 255

.dseg

.org 0x75
arr_c: .byte 8 ; arr_c = 8
.org 0x7f
c_len: .byte 1

.cseg
.org 0x00 rjmp Init
.include "main.asm"

Init:
	ldi xl, low(RAMEND)
	out SPL, xl
	ldi xl, high(RAMEND)
	out SPH, xl

	ldi xl, low(c_len)
	ldi xh, high(c_len)
	E_READ xh, xl, count_c

	load_z arr_c
	ldi min_el, start_min
	mov count, count_c

FIND_MIN:
	E_READ zh, zl, el_arr_c
	call incZ
	cp el_arr_c, min_el

	brsh next_num ; перейти если min_element >= el_arr_c
	mov min_el, el_arr_c

next_num:
	dec count
	brne FIND_MIN

; ¬ывод числа на светодиоды
ser r20
out DDRB, r20
com min_el
out PORTB, min_el

WAIT:	
	rjmp WAIT

incZ:
	clc
	inc r30
	brcc inczc
	inc r31
	inczc:
ret

incY:
	clc
	inc r28
	brcc incyc
	inc r29
	incyc:
ret

incX:
	clc
	inc r26
	brcc incxc
	inc r27
	incxc:
ret