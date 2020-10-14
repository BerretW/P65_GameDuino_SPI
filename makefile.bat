del .\output\*.*
cd .\src
cc65 -t none -O --cpu 6502 main.c
ca65 --cpu 6502 main.s -o ..\output\main.o
ca65 --cpu 6502 spi.asm -o ..\output\spi.o
ca65 --cpu 6502 vectors.asm -o ..\output\vectors.o
ca65 --cpu 6502 acia.s -o ..\output\acia.o


cd ..\output
ld65 -C ..\config\APP_RAM_DISK.cfg -m main.map vectors.o main.o spi.o acia.o ..\library\p65.lib -o ..\output\RAM.bin
