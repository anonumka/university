.dseg // указатель на сегмент данных
.def count	= r23 	; счетчик
.def count2	= r24 	; второй счетчик
.set sizeAB	= 8 	// размер массивов A и B

.org 0x60 // начальный адрес масивов
arr_a: .byte sizeAB // Выделяем sizeAB байт на массив А
arr_b: .byte sizeAB // Выделяем sizeAB байт на массив В

.org 0x75
arr_c: .byte sizeAB // Выделяем sizeС байт на массив С
.org 0x7e
min_el: .byte 1 	// выделим 1 байт под минимальный элемент
.org 0x7f
c_len: .byte 1

.cseg // указатель на сегмент кода
.org 0x00 rjmp Init
.include "main.asm"

Init:
ldi xl, low(RAMEND)
out SPL, xl
ldi xl, high(RAMEND)
out SPH, xl

	START:
	load_z arr_a
	load_y arr_b
	load_x arr_c

	ldi r21, 10 // переменная для заполнения массива А
	ldi count, sizeAB // Устанавливаем размер счетчика 
	MASA:
		E_WRITE zh, zl, r21 // сохранение r18 в масив А и инкремент указателя
		rcall incZ
		dec r21
		dec count
	brne MASA  // условия цикл заполнения массива А

	// заполнения масив В
	ldi r21, 5 // переменная для заполнения массива B
	ldi count, sizeAB // Устанавливаем размер счетчика
	MASB: // заполняем массив B
		E_WRITE yh, yl, r21
		call incY
		inc r21
		dec count
	brne MASB // условия цикл заполнения массива В

	// Заполним массив С разностью массивов А и В
	load_z arr_a
	ldi count, sizeAB

	ldi r25, 0
	FILL_ARR_C:
		load_y arr_b
		E_READ zh, zl, r19 // сохранение r18 в масив А и инкремент указателя
		rcall incZ; ld r19, z+ // a_current=z, z=z+1
		ldi count2, sizeAB // счетчик
		FILL_ARR_C2:
			E_READ yh, yl, r20 // сохранение r18 в масив А и инкремент указателя
			rcall incY; ld r19, z+ // a_current=z, z=z+1 ; ld r20, y+
			cp r19, r20
			breq EQUALS // if ai = bi, then EQUALS
			dec count2
			brne FILL_ARR_C2
			rjmp CHECK_TO_CONT
		EQUALS:
			E_WRITE xh, xl, r20
			call incX ; st x+,r20 // zi = any values (r18, r19)
			inc r25
		CHECK_TO_CONT:
			dec count
			brne FILL_ARR_C

		ldi xl, low(c_len)
		ldi xh, high(c_len)
		E_WRITE xh, xl, r25
		call incX ; st x+,r20 // zi = any values (r18, r19)
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
