#include "gameduino.h"
#include "spi.h"

void GD_Init(){
int i = 0;
GD_wr(J1_RESET, 1);
__wstart(RAM_SPR);            // Hide all sprites
for ( i = 0; i < 512; ++i) GD_xhide();
__end();
}

void GD_Begin(){
  spi_begin();
}

void GD_wr(unsigned addr, char v)
{
  __wstart(addr);
  spi_write(v);
  __end();
}

void __start(unsigned addr){
  GD_Begin();
  spi_write_16(addr);
}

void __wstart(unsigned addr) // start an SPI write transaction to addr
{
  __start(0x8000|addr);
}

void __end(){
  spi_end();
}


//sprites

void GD_xhide(){
  spi_write_16(400);
  spi_write_16(400);
}
