				.setcpu "6502"
				.include "zeropage.inc65"

				.import _acia_init
				.import _acia_putc
				.import _acia_getc
				.import _acia_puts



                .segment "VECTORS"

                .word   nmi
                .word   reset
                .word   irq


                .segment "CODE"


reset:           JMP main

nmi:             RTI

irq:             RTI

                .segment "STARTUP"
main:
				JSR popa

				JSR _acia_init


				JSR _SPI_Begin

				LDA #$80
				JSR _SPI_Write

				LDA #$0
				JSR _SPI_Write

				LDA _spi_write_data
				JSR _SPI_Write

				LDA #$F
				STA SPI_CSSEL

				LDA _spi_write_data
				JSR _acia_putc


				JSR _acia_getc
				STA _spi_write_data
				JMP main



_SPI_Begin:					PHA
										LDA #$7
										STA SPI_CSSEL
										;JSR _spi_delay
										PLA
										RTS


_SPI_End:						PHA
										LDA #$F
										STA SPI_CSSEL
										PLA
										RTS


_SPI_Write:         PHA
										LDA _spi_write_data
										STA SPI_DATA
										JSR _spi_delay
										PLA
                    RTS


_SPI_Read:					LDA SPI_DATA
										RTS

_spi_delay:					LDX #2
@_delay_1:					DEX
										BEQ @_delay_1
										RTS
