;.include "io.inc65"

;.import popa, popax
.importzp tmp1, tmp2,tmp3

;SPI registerss

SPI_DATA   = $CE00
SPI_CSSEL		=	$CE03
SPI_STATUS	=	$CE01
SPI_DIV     = $CE02
SPI_CS			= 7			;CS0 = 14, CS1=13, CS2=11, CS3=7

data = tmp1
adrH = tmp2
adrL = tmp3

;.export _spi_write_to
.export _spi_begin
.export _spi_end
.export _spi_write
.export _spi_write_16
.export _spi_read
.code



; void spi_write_to(char * buffer, char c)
; @in A (n) char to write
; @in popax (buffer) address in SPI

;_spi_write_to:      STA tmp1
;										JSR popax
;										STA tmp3
;										STX tmp2
;										LDA #$7
;										STA SPI_CSSEL
;										LDA tmp2
;										ADC #$80
;										JSR _spi_write
;										LDA tmp3
;										JSR _spi_write
;										LDA tmp1
;										JSR _spi_write
;										LDA #$F
;										STA SPI_CSSEL
;                    RTS

_spi_write:					STA SPI_DATA
										JSR spi_delay
										RTS

_spi_write_16:			STA adrL
										STX adrH
										LDA adrH
										JSR _spi_write
										LDA adrL
										JSR _spi_write
										RTS

_spi_read:					STA SPI_DATA
										LDA SPI_DATA
										RTS

_spi_begin:					LDA SPI_CS
										STA SPI_CSSEL
										JSR spi_delay
										RTS

_spi_end:						LDA #$F
										STA SPI_CSSEL
										JSR spi_delay
										JSR spi_delay
										JSR spi_delay
										RTS

spi_delay:					LDX #1
@_delay_1:					DEX
										BEQ @_delay_1
										RTS
