del .\output\*.*

cd .\src
cc65 -t none -O --cpu 65C02 main.c
cc65 -t none -O --cpu 65c02 gameduino.c
ca65 --cpu 65c02 main.s -o ..\output\main.o
ca65 --cpu 65c02 gameduino.s -o ..\output\gameduino.o
ca65 --cpu 65c02 spi.asm -o ..\output\spi.o
ca65 --cpu 65c02 vectors.asm -o ..\output\vectors.o
ca65 --cpu 65c02 acia.asm -o ..\output\acia.o
ca65 --cpu 65c02 interrupts.asm -o ..\output\interrupts.o
ca65 --cpu 65c02 lcd.asm -o ..\output\lcd.o
 
move *.s ..\output

cd ..\output

ld65 -C APP_RAM_DISK.cfg -m main.map main.o spi.o lcd.o acia.o gameduino.o interrupts.o vectors.o ..\library\p65.lib -o ..\output\RAM.bin

ld65 -C ..\config\appartus.cfg -m main.map main.o spi.o lcd.o acia.o gameduino.o interrupts.o vectors.o ..\library\p65.lib -o ..\output\ROM.bin
