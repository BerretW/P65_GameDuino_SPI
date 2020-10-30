del .\output\*.*

cd .\src
cc65 -t none -O --cpu 6502 main.c
cc65 -t none -O --cpu 6502 gameduino.c
ca65 --cpu 6502 main.s -o ..\output\main.o
ca65 --cpu 6502 gameduino.s -o ..\output\gameduino.o
ca65 --cpu 6502 spi.asm -o ..\output\spi.o
ca65 --cpu 6502 vectors.asm -o ..\output\vectors.o
ca65 --cpu 6502 acia.asm -o ..\output\acia.o
ca65 --cpu 6502 interrupts.asm -o ..\output\interrupts.o
ca65 --cpu 6502 lcd.asm -o ..\output\lcd.o

move *.s ..\output

cd ..\output

ld65 -C ..\config\APP_RAM_DISK.cfg -m main.map main.o spi.o lcd.o acia.o gameduino.o interrupts.o vectors.o ..\library\p65.lib -o ..\output\RAM.bin
