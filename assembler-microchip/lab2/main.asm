;
; AssemblerApplication1.asm
;
; Created: 16.02.2023 11:34:53
; Author : 1
;


; Replace with your application code
start:
	.def count = r17 //счетчик
	.def count2 = r16 //второй счетчик
	.def count_crossing = r21 // количество совпадений
	.set sizeAB = 8 //размер массивов A, B и C
	.dseg //указатель на сегмент данных
	.org 0x60 //начальный адрес
	mas_a: .byte sizeAB
	mas_b: .byte sizeAB
	.org 0x75
	mas_c: .byte 8 //выделим под массив C 8 байт
	.org 0x7E
	min_el: .byte 1 //выделим 1 байт под минимальный элемент
	.cseg //указатель на сегмент кода
	//формируем регистровые пары
	ldi r30, low(mas_a) // Z
	ldi r31, high(mas_a)

	ldi r28, low(mas_b) // Y
	ldi r29, high(mas_b)

	ldi r26, low(mas_c) // X
	ldi r27, high(mas_c)

	ldi r18, 10 //переменная для заполнения массива А
	ldi count, sizeAB
	MASA: //заполняем массив A
		st z+, r18
		dec r18
		dec count
		brne MASA 

	ldi r19, 1
	clr count
	ldi count, sizeAB
	MASB: //заполняем массив B
		st y+, r19
		inc r19
		dec count
		brne MASB

	/* Заполнение массива C */
	ldi r30, low(mas_a) // Z, адрес массива А
	ldi r31, high(mas_a)

	ldi count, sizeAB // счетчик 
	ldi r20, 0 // if ai != bi then ci = 0
	ldi count_crossing,0 // count crossing

	FILL_ARR_C:
		ldi r28, low(mas_b) // Y
		ldi r29, high(mas_b)
		ld r18, z+
		ldi count2, sizeAB // счетчик
		FILL_ARR_C2:
			ld r19, y+
			cp r18,r19
			breq EQUALS // if ai = bi, then EQUALS
			dec count2
			brne FILL_ARR_C2
			st x+,r20 // zi = any values (r18, r19)
			inc count_crossing
			rjmp CHECK_TO_CONT
		EQUALS:
			st x+,r19 // zi = any values (r18, r19)
			rjmp CHECK_TO_CONT
		CHECK_TO_CONT:
			dec count
			brne FILL_ARR_C

	//Поиск минимального элемента
	ldi r26, low(mas_c)
	ldi r27, high(mas_c)
	ldi r20, 255
	ldi count, sizeAB
	sub count, count_crossing
	add r26, count_crossing
	Find_min:
		ld r18, x+
		cp r18, r20
		brsh nebol //перейти если r18 меньше r20
		mov r20, r18
		nebol:
		dec count
	brne Find_min
	sts min_el, r20
	nop

	//сортировка возрастание
	SORT:
	ldi r26, low(mas_c)
	ldi r27, high(mas_c)
	ldi r20, 0
	ldi count, sizeAB
	SORT2:
	ld r18, x+
	ld r19, x
	cp r19, r18
	brsh SWIP
	ldi r20, 1
	mov r22, r18
	st -x, r19
	ld r13, x+
	st x, r22
	SWIP:
	dec count
	brne SORT2
	cpi r20, 1
	breq SORT
	nop

