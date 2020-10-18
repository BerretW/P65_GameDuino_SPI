#include <stdlib.h>
#include <stdio.h>


#include "acia.h"
//#include "bank.h"
//#include "wait.h"
//
//#include "utils.h"
#include "gameduino.h"

//#include "copyshort.h"

#include "spi.h"
int i = 0;
char c;

void main(void) {
  //
  int y;
  y = 0;
  //GD_Init();
  //GD_fill(RAM_PIC, 0, 0x0FFF);
  //GD_ascii();
  //GD_putstr(0,10,"Ahoj Volove");

  acia_puts("ahoj volove");
  //spi_write_to(0x280E, 0x15);
  //spi_write_to(0x280F, 0xF0);
while(1){
  c = acia_getc();

  if (c != 0x8) {
    ++i;
  } else {
    if (i > 0) {
    --i;
    }
  }
  if (i == 50){
    i = 0;
    ++y;
  }
  GD_putchar(i,y, c);

  //acia_putc(c);

}

}
