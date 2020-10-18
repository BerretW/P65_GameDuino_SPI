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
  int y = 0;
  //GD_Init();
  //GD_fill(RAM_PIC, 0, 0x1000);
  //GD_ascii();
  GD_putstr(0,10,"Ahoj Volove");

  acia_puts("ahoj volove");
  //spi_write_to(0x280E, 0x15);
  //spi_write_to(0x280F, 0xF0);
  while(1){

    for (i =0;i<20;++i){
      GD_fill(RAM_PIC, 41+i, 0x0FFF);
    }

  }
while(1){
  c = acia_getc();
  GD_putchar(i,y, c);
  acia_putc(c);
  if (c != 0x8) {
    ++i;
  } else {
    //c = 0x00;
    if (i > 0) {
    --i;
    GD_putchar(i,y, c);
    }
  }
  if (i == 50){
    i = 0;
    ++y;
  }


}

}
