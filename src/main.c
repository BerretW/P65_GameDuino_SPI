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
unsigned int i = 0;
char c;
void main(void) {
  GD_Init();
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
  GD_wr(i, c);
  acia_putc(c);

}

}
