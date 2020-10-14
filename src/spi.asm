.include "io.inc65"

.import popa, popax
.importzp tmp1, tmp2,tmp3

data = tmp1
adrH = tmp2
adrL = tmp3

.export _spi_write_to
.code



; void spi_write_to(char * buffer, char c)
; @in A (n) char to write
; @in popax (buffer) address in SPI

_spi_write_to:      STA tmp1
										JSR popax
										STA tmp3
										STX tmp2
										LDA #$7
										STA SPI_CSSEL
										LDA tmp2
										ADC #$80
										JSR spi_write
										LDA tmp3
										JSR spi_write
										LDA tmp1
										JSR spi_write
										LDA #$F
										STA SPI_CSSEL
                    RTS

spi_write:					STA SPI_DATA
										JSR spi_delay
										RTS

spi_begin:
										RTS

spi_end:						LDA #$F
										STA SPI_CSSEL
										RTS

spi_delay:					LDX #1
@_delay_1:					DEX
										BEQ @_delay_1
										RTS
