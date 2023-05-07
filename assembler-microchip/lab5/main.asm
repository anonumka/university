.include "m32adef.inc"

.def E_ADR_H = r16	; ��� ��� �������� ��� �������� ����� ������ � EEPROM
.def E_ADR_L = r17	; � ��� ��� ��������
.def E_DATA = r18	; ���� ������� ����� ������������ ��� ������ EEPROM

.macro load_x
	ldi xl, low(@0) ;  X
	ldi xh, high(@0)
.endmacro

.macro load_y
	ldi yl, low(@0) ;  Y
	ldi yh, high(@0)
.endmacro

.macro load_z
	ldi zl, low(@0) ;  Z
	ldi zh, high(@0)
.endmacro

.macro E_WRITE		; ������ � EEPROM
	push E_ADR_H	; �������� � ����� ��������, ����� �� ���������
	push E_ADR_L
	push E_DATA
	mov E_ADR_H,@0	; ���������� ����� ��� ������ - ��� �����
	mov E_ADR_L,@1
	mov E_DATA,@2	; ���������� ������ - ��� � ��������
	rcall EEWrite	; � ������� ����� �� ������ � EEPROM
	pop E_DATA		; ����������� �������� ������ � ������
	pop E_ADR_L
	pop E_ADR_H
.endmacro

.macro E_READ		; ������� �� EEPROM
	push E_ADR_H	; ���������� ��������
	push E_ADR_L
	push E_DATA
	mov E_ADR_H,@0	; ������� ����� 
	mov E_ADR_L,@1
	rcall EERead	; � ����� �� ����� ������ ������
	mov @2,E_DATA	; �������� ��������� � �������
	pop E_DATA		; ��������������� ������ ��������
	pop E_ADR_L
	pop E_ADR_H
.endmacro

EEWrite:
	SBIC EECR,EEWE	    ; ������ ���� ���������� EEPROM
	RJMP EEWrite	    ; ��� ��� - EEWE ������ - ����
	
	OUT EEARH,E_ADR_H	; ��������� ������ EEROM
	OUT EEARL,E_ADR_L
	OUT EEDR,E_DATA	    ; �������� ������
	SBI EECR,EEMWE  	; ��������� ������
	SBI EECR,EEWE	    ; �������� ������
RET				        ; ����� �� ������������

EERead:
	SBIC EECR,EEWE	    ; ���� ����������
	RJMP EERead
	
	OUT EEARL, E_ADR_L	; ��������� �����
	OUT EEARH, E_ADR_H	; � EEPROM
	SBI EECR,EERE	    ; ������ ������
	IN E_DATA, EEDR	    ; ������� ���������
RET