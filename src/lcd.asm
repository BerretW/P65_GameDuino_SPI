.include "io.inc65"
.include "macros.inc65"

.zeropage

radek:			.res 1


.export _lcd_init
.export _lcd_putc
.export _lcd_puts
.export _lcd_w_reg
.export _lcd_put_newline

.zeropage
.importzp	tmp1, tmp2, tmp3, tmp4, ptr1, ptr2, ptr3, ptr4
.globalzp tmpstack



.code


_lcd_init:
LDA #%00000111
STA LCD_VIA_DDRB
LDA #%11111111
STA LCD_VIA_DDRA
LDA #%00111000 ;8-bitový mod
JSR _lcd_w_reg
LDA #%00001110	;Zapnuty display a kurzor
JSR _lcd_w_reg
LDA #%00000110	;Zapnuty display a kurzor
JSR _lcd_w_reg
LDA #%00000001	;Clear Display
JSR _lcd_w_reg
LDA #LCD_1LINE
STA radek
RTS

_lcd_put_newline:
                PHA
                LDA #radek
                CMP #LCD_1LINE
                BNE _radek2
_radek1:        LDA #LCD_2LINE
                STA radek
                JSR _lcd_w_reg
_radek2:        LDA #LCD_1LINE
                STA radek
                JSR _lcd_w_reg
                PLA
                RTS



_lcd_w_reg:		PHA
STA LCD_VIA_PORTA
LDA #0
STA LCD_VIA_PORTB
LDA #LCD_E
STA LCD_VIA_PORTB
JSR _delay
LDA #0
STA LCD_VIA_PORTB
PLA
RTS

_lcd_putc:		PHA
STA LCD_VIA_PORTA
LDA #LCD_RS
STA LCD_VIA_PORTB
LDA #(LCD_RS | LCD_E)
JSR _delay
STA LCD_VIA_PORTB
LDA #LCD_RS
STA LCD_VIA_PORTB
PLA
RTS

_lcd_puts:		phay
STA ptr1
STX ptr1 + 1
LDY #0
@next_char:		LDA (ptr1), y
BEQ @eos
JSR _lcd_putc
INY
BNE @next_char
@eos:			play
RTS



_delay:					LDX #$FF
_delay1:				DEX
    BNE _delay1
    RTS
