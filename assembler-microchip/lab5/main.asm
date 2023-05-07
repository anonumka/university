.include "m32adef.inc"

.def E_ADR_H = r16	; это имя регистра для старшего байта адреса в EEPROM
.def E_ADR_L = r17	; а это для младшего
.def E_DATA = r18	; этот регистр будем использовать для данных EEPROM

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

.macro E_WRITE		; запись в EEPROM
	push E_ADR_H	; сохраним в стеке регистры, чтобы не испортить
	push E_ADR_L
	push E_DATA
	mov E_ADR_H,@0	; подготовим адрес для записи - это число
	mov E_ADR_L,@1
	mov E_DATA,@2	; подготовим данные - они в регистре
	rcall EEWrite	; и запишем число по адресу в EEPROM
	pop E_DATA		; восстановим регистры адреса и данных
	pop E_ADR_L
	pop E_ADR_H
.endmacro

.macro E_READ		; чтоение из EEPROM
	push E_ADR_H	; сохраняием регистры
	push E_ADR_L
	push E_DATA
	mov E_ADR_H,@0	; готовим адрес 
	mov E_ADR_L,@1
	rcall EERead	; и читам из этого адреса данные
	mov @2,E_DATA	; передаем результат в регистр
	pop E_DATA		; восстанавливаем старые регистры
	pop E_ADR_L
	pop E_ADR_H
.endmacro

EEWrite:
	SBIC EECR,EEWE	    ; анализ бита готовности EEPROM
	RJMP EEWrite	    ; нет еще - EEWE очищен - ждем
	
	OUT EEARH,E_ADR_H	; установка адреса EEROM
	OUT EEARL,E_ADR_L
	OUT EEDR,E_DATA	    ; загрузка данных
	SBI EECR,EEMWE  	; разрешить запись
	SBI EECR,EEWE	    ; записать данные
RET				        ; выход из подпрограммы

EERead:
	SBIC EECR,EEWE	    ; Ждем готовности
	RJMP EERead
	
	OUT EEARL, E_ADR_L	; загрузить адрес
	OUT EEARH, E_ADR_H	; в EEPROM
	SBI EECR,EERE	    ; начать чтение
	IN E_DATA, EEDR	    ; забрать результат
RET