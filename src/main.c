#include <stdlib.h>
#include <stdio.h>
#include <string.h>


#include "acia.h"
#include "lcd.h"
//#include "bank.h"
//#include "wait.h"
//
//#include "utils.h"
#include "gameduino.h"
#include "wood_char.h"
#include "sprite.h"
//#include "copyshort.h"

#include "spi.h"
int i = 0;
int radek = 0;
int radek_lcd = 0;
char c;

void print_f(const char * s){
  GD_putstr(0,radek,s);
  ++radek;
  acia_put_newline();
  acia_puts(s);
  lcd_puts(s);
  lcd_put_newline();
}


void main(void) {
  //
  int y = 0;
  unsigned bg_colour;
  GD_Init();
//  lcd_init();
//GD_fill(RAM_PIC, 0, 0x1000);
//  GD_ascii();


//  bg_colour = RGB(0, 0, 0);
//  GD_wr16(BG_COLOR, bg_colour);

//GD_copy(RAM_CHR, Wood32_chr, 0x200);
//GD_copy(RAM_PAL, Wood32_pal, 0x100);

//  GD_copy(RAM_SPRIMG, staunton_img, sizeof(staunton_img));
//  GD_copy(RAM_SPRPAL, staunton_white, sizeof(staunton_white));

//  for (i = 0; i < 256; i++) {
//      unsigned int b = GD_rd16(RAM_SPRPAL + 2 * 512 + 2 * i);
//      GD_wr16(RAM_SPRPAL + 3 * 512 + 2 * i, b ^ 0x7fff);
//    }

//GD_sprite(char spr, int x, int y, char image, char palette, char rot, char jk)

//GD_sprite(0x0, 200, 200, 0x1, 0x0, 0x0,0x0);


  print_f("Ahoj Volove");
  print_f("No nazdar");
  //GD_putstr(0,10,"Ahoj Volove");
  //acia_put_newline();
  //acia_puts("ahoj volove");
  //spi_write_to(0x280E, 0x15);
  //spi_write_to(0x280F, 0xF0);
while(1)
{

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

  while(1){

    for (i =0;i<20;++i){
      GD_fill(RAM_PIC, 41+i, 0x0FFF);
    }

  }


}
