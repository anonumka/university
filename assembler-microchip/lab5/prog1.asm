.dseg // ��������� �� ������� ������
.def count	= r23 	; �������
.def count2	= r24 	; ������ �������
.set sizeAB	= 8 	// ������ �������� A � B

.org 0x60 // ��������� ����� �������
arr_a: .byte sizeAB // �������� sizeAB ���� �� ������ �
arr_b: .byte sizeAB // �������� sizeAB ���� �� ������ �

.org 0x75
arr_c: .byte sizeAB // �������� size� ���� �� ������ �
.org 0x7e
min_el: .byte 1 	// ������� 1 ���� ��� ����������� �������
.org 0x7f
c_len: .byte 1

.cseg // ��������� �� ������� ����
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

	ldi r21, 10 // ���������� ��� ���������� ������� �
	ldi count, sizeAB // ������������� ������ �������� 
	MASA:
		E_WRITE zh, zl, r21 // ���������� r18 � ����� � � ��������� ���������
		rcall incZ
		dec r21
		dec count
	brne MASA  // ������� ���� ���������� ������� �

	// ���������� ����� �
	ldi r21, 5 // ���������� ��� ���������� ������� B
	ldi count, sizeAB // ������������� ������ ��������
	MASB: // ��������� ������ B
		E_WRITE yh, yl, r21
		call incY
		inc r21
		dec count
	brne MASB // ������� ���� ���������� ������� �

	// �������� ������ � ��������� �������� � � �
	load_z arr_a
	ldi count, sizeAB

	ldi r25, 0
	FILL_ARR_C:
		load_y arr_b
		E_READ zh, zl, r19 // ���������� r18 � ����� � � ��������� ���������
		rcall incZ; ld r19, z+ // a_current=z, z=z+1
		ldi count2, sizeAB // �������
		FILL_ARR_C2:
			E_READ yh, yl, r20 // ���������� r18 � ����� � � ��������� ���������
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
