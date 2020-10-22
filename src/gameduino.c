#include "gameduino.h"
#include "spi.h"


char spr;


void GD_Init(){
int i;
//spi_init();
GD_wr(J1_RESET, 1);
__wstart(RAM_SPR);            // Hide sdfall sprites
for ( i = 0; i < 0x200; ++i) GD_xhide();
__end();

GD_fill(RAM_PIC, 0, 0x0FFF);  // Zero all character RAM
GD_fill(RAM_SPRPAL, 0, 0x1FFF);    // Sprite palletes black
GD_fill(RAM_SPRIMG, 0, 0x3FFF);   // Clear all sprite data
GD_fill(VOICES, 0, 0x100);         // Silence
GD_fill(PALETTE16A, 0, 0x80);     // Black 16-, 4-palletes and COMM


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

char GD_rd(unsigned addr){
char r;
  __start(addr);
  r = spi_read(0);
  __end();
  return r;
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


unsigned char GD_rd16(unsigned addr){
  unsigned char r;

  __start(addr);
  r = spi_read(0);
  r |= (spi_read(0) << 8);
//  r = (c | spi_read << 8);
  __end();
  return r;
}

void __start(unsigned addr){
  spi_begin();
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

void GD_putchar(char x, char y, char c)
{
  __wstart((y << 6) + x);
    spi_write(c);
  __end();
}

void GD_sprite(char spr, int x, int y, char image, char palette, char rot, char jk)
{
  __wstart(RAM_SPR + (spr << 2));
  spi_write_16((palette << 4) | (rot << 1) | (x & 1));
  spi_write_16((jk << 7) | (image << 1) | (y & 1));
  __end();
}

/* Fixed ascii font, useful for debug */

#include "font8x8.h"
static char stretch[16] = {
  0x00, 0x03, 0x0c, 0x0f,
  0x30, 0x33, 0x3c, 0x3f,
  0xc0, 0xc3, 0xcc, 0xcf,
  0xf0, 0xf3, 0xfc, 0xff
};


void GD_ascii()
{
  int i = 0;
  for (i = 0; i < 768; ++i) {
    char b = font8x8[i];
    char h = stretch[b >> 4];
    char l = stretch[b & 0xf];
    GD_wr(0x1000 + (16 * ' ') + (2 * i), h);
    GD_wr(0x1000 + (16 * ' ') + (2 * i) + 1, l);
  }
  for (i = 0x20; i < 0x80; i++) {
    GD_setpal(4 * i + 0, TRANSPARENT);
    GD_setpal(4 * i + 3, RGB(255,255,255));
  }
  GD_fill(RAM_PIC, ' ', 4096);
}

void GD_copy(unsigned addr, char *src, int count)
{ int i = 0;
  __wstart(addr);
  while (--count) {
    spi_write(src[i]);
    ++i;
  }
  __end();
}

void GD_setpal(char pal, unsigned rgb)
{
  GD_wr16(RAM_PAL + (pal << 1), rgb);
}



//sprites

void GD_xhide(){
  spi_write_16(0x190);
  spi_write_16(0x190);
  ++spr;
}
