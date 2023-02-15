/*  Pre-SVGAlib code by John D. Morelli:
       www.well.com/user/vanya/bill.html
   */

#include <stdlib.h>
#include <unistd.h>
#include <lug.h>
#include <lugfnts.h>
#include <vga.h>
#include <vgagl.h>
#include <vgamouse.h>

void move_cursor(int x, int y, int ox, int oy);
void draw_cursor(int x, int y);

char box[11 * 19 * 8];

int main(void)
{
   int key,
       i, r, g, b,
       bill_x, bill_y, button_x, button_y, x, y, ox, oy,
       button;

   byte *ptr;

   bitmap_hdr one,
              two,
              three,
              logo,
              button1,
              button2;

   vga_init();

   vga_setmousesupport(1);
   vga_setmode(G640x480x256);
   gl_setcontextvga(G640x480x256);
   gl_setrgbpalette();

   gl_setpalettecolor(253, 223, 223, 223); /* gray */
   gl_setpalettecolor(254, 0, 0, 0);       /* black */
   gl_setpalettecolor(255, 255, 255, 255); /* white */

   gl_clearscreen(255);

   read_gif_file("bill_1.gif", &one);
   read_gif_file("bill_2.gif", &two);
   read_gif_file("bill_3.gif", &three);
   read_gif_file("bill_logo.gif", &logo);
   read_gif_file("button_1.gif", &button1);
   read_gif_file("button_2.gif", &button2);

   for (i = 0, ptr = one.cmap; i < one.colors; i++)
   {
      r = (double)*ptr++;
      g = (double)*ptr++;
      b = (double)*ptr++;
      gl_setpalettecolor(i, r>>2, g>>2, b>>2);
   }

   bill_x = (640 / 2) - (one.xsize / 2);
   bill_y = (480 / 2) - (one.ysize / 2);
   gl_putbox(bill_x, bill_y, one.xsize, one.ysize, one.r);

   gl_putbox(30, 50, logo.xsize, logo.ysize, logo.r);

   button_x = (640 / 2) - (button1.xsize / 2);
   button_y = 350;
   gl_putbox(button_x, button_y, button1.xsize, button1.ysize, button1.r);

   gl_line(30, 0, 30, 30, 253);
   gl_hline(31, 30, 610, 253);
   gl_line(610, 31, 610, 479, 253);

   x = ox = 50;
   y = oy = 50;

   draw_cursor(x, y);

   while (((key = vga_getkey()) != 27) && (key != 81) && (key != 113))
   {
      mouse_update();
      x = mouse_getx();
      y = mouse_gety();
      button = mouse_getbutton();

      if ((x != ox) || (y != oy))
      {
         move_cursor(x, y, ox, oy);
         ox = x;
         oy = y;
      }

      if ((key == 10) || ((button & MOUSE_LEFTBUTTON) &&
          (x >= button_x) && (x <= (button_x + button1.xsize)) &&
          (y >= button_y) && (y <= (button_y + button1.ysize))))
      {
         gl_putbox(bill_x, bill_y, two.xsize, two.ysize, two.r);
         gl_putbox(button_x, button_y, button2.xsize, button2.ysize, button2.r);
         move_cursor(x, y, x, y);
         usleep(50000);         
         gl_putbox(bill_x, bill_y, three.xsize, three.ysize, three.r);         
         gl_putbox(button_x, button_y, button1.xsize, button1.ysize, button1.r);
         move_cursor(x, y, x, y);
      }
   }

   vga_setmode(TEXT);

   return 0;
}

void move_cursor(int x, int y, int ox, int oy)
{
   gl_putbox(ox, oy, 11, 19, box);
   gl_getbox(x, y, 11, 19, box);
   draw_cursor(x, y);
}

void draw_cursor(int x, int y)
{
   gl_getbox(x, y, 11, 19, box);

   gl_setpixel(x, y, 254);              /* line 1 */
   gl_hline(x, (y + 1), (x + 1), 254);  /* line 2 */
   gl_setpixel(x, (y + 2), 254);        /* line 3 */
   gl_setpixel((x + 1), (y + 2), 255);
   gl_setpixel((x + 2), (y + 2), 254);
   gl_setpixel(x, (y + 3), 254);        /* line 4 */
   gl_hline((x + 1), (y + 3), (x + 2), 255);
   gl_setpixel((x + 3), (y + 3), 254);
   gl_setpixel(x, (y + 4), 254);        /* line 5 */
   gl_hline((x + 1), (y + 4), (x + 3), 255);
   gl_setpixel((x + 4), (y + 4), 254);
   gl_setpixel(x, (y + 5), 254);        /* line 6 */
   gl_hline((x + 1), (y + 5), (x + 4), 255);
   gl_setpixel((x + 5), (y + 5), 254);
   gl_setpixel(x, (y + 6), 254);        /* line 7 */
   gl_hline((x + 1), (y + 6), (x + 5), 255);
   gl_setpixel((x + 6), (y + 6), 254);
   gl_setpixel(x, (y + 7), 254);        /* line 8 */
   gl_hline((x + 1), (y + 7), (x + 6), 255);
   gl_setpixel((x + 7), (y + 7), 254);
   gl_setpixel(x, (y + 8), 254);        /* line 9 */
   gl_hline((x + 1), (y + 8), (x + 7), 255);
   gl_setpixel((x + 8), (y + 8), 254);
   gl_setpixel(x, (y + 9), 254);        /* line 10 */
   gl_hline((x + 1), (y + 9), (x + 8), 255);
   gl_setpixel((x + 9), (y + 9), 254);
   gl_setpixel(x, (y + 10), 254);        /* line 11 */
   gl_hline((x + 1), (y + 10), (x + 5), 255);
   gl_hline((x + 6), (y + 10), (x + 10), 254);
   gl_setpixel(x, (y + 11), 254);       /* line 12 */
   gl_hline((x + 1), (y + 11), (x + 2), 255);
   gl_setpixel((x + 3), (y + 11), 254);
   gl_hline((x + 4), (y + 11), (x + 5), 255);
   gl_setpixel((x + 6), (y + 11), 254);
   gl_setpixel(x, (y + 12), 254);       /* line 13 */
   gl_setpixel((x + 1), (y + 12), 255);
   gl_setpixel((x + 2), (y + 12), 254);
   gl_setpixel((x + 4), (y + 12), 254);
   gl_hline((x + 5), (y + 12), (x + 6), 255);
   gl_setpixel((x + 7), (y + 12), 254);
   gl_hline(x, (y + 13), (x + 1), 254); /* line 14 */
   gl_setpixel((x + 4), (y + 13), 254);
   gl_hline((x + 5), (y + 13), (x + 6), 255);
   gl_setpixel((x + 7), (y + 13), 254);
   gl_setpixel(x, (y + 14), 254);       /* line 15 */
   gl_setpixel((x + 5), (y + 14), 254);
   gl_hline((x + 6), (y + 14), (x + 7), 255);
   gl_setpixel((x + 8), (y + 14), 254);
   gl_setpixel((x + 5), (y + 15), 254); /* line 16 */
   gl_hline((x + 6), (y + 15), (x + 7), 255);
   gl_setpixel((x + 8), (y + 15), 254);
   gl_setpixel((x + 6), (y + 16), 254); /* line 17 */
   gl_hline((x + 7), (y + 16), (x + 8), 255);
   gl_setpixel((x + 9), (y + 16), 254);
   gl_setpixel((x + 6), (y + 17), 254); /* line 18 */
   gl_hline((x + 7), (y + 17), (x + 8), 255);
   gl_setpixel((x + 9), (y + 17), 254);
   gl_hline((x + 7), (y + 18), (x + 8), 254); /* line 19 */
}
