#include "gameduino.h"
#include "spi.h"
char spr;


void GD_Init(){
int i = 0;
GD_wr(J1_RESET, 1);
__wstart(RAM_SPR);            // Hide sdfall sprites
for ( i = 0; i < 512; ++i) GD_xhide();
__end();

GD_fill(RAM_PIC, 0, 1024 * 4);  // Zero all character RAM
GD_fill(RAM_SPRPAL, 0, 2048);    // Sprite palletes black
GD_fill(RAM_SPRIMG, 0, 64 * 256);   // Clear all sprite data
GD_fill(VOICES, 0, 256);         // Silence
GD_fill(PALETTE16A, 0, 128);     // Black 16-, 4-palletes and COMM


  GD_wr16(SCROLL_X, 0);
  GD_wr16(SCROLL_Y, 0);
  GD_wr(JK_MODE, 0);
  GD_wr(SPR_DISABLE, 0);
  GD_wr(SPR_PAGE, 0);
  GD_wr(IOMODE, 0);
  GD_wr16(BG_COLOR, 0);
  GD_wr16(SAMPLE_L, 0);
  GD_wr16(SAMPLE_R, 0);
  GD_wr16(SCREENSHOT_Y, 0);
  GD_wr(MODULATOR, 64);
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

void GD_wr16(unsigned addr, unsigned v)
{
  __wstart(addr);
  spi_write_16(v);
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

void GD_fill(unsigned addr, char v, unsigned count)
{
  __wstart(addr);
  while (count--)
    spi_write(v);
  __end();
}

void GD_putstr(char x, char y, const char *s)
{
  __wstart((y << 6) + x);
  while (*s)
    spi_write(*s++);
  __end();
}

void GD_ascii()
{
  long i;

  for (i = 0x20; i < 0x80; ++i) {
    GD_setpal(4 * i + 0, TRANSPARENT);
    GD_setpal(4 * i + 3, RGB(255,255,255));
  }
  GD_fill(RAM_PIC, ' ', 4096);
}

void GD_setpal(char pal, unsigned rgb)
{
  GD_wr16(RAM_PAL + (pal << 1), rgb);
}

//sprites

void GD_xhide(){
  spi_write_16(400);
  spi_write_16(400);
  ++spr;
}
