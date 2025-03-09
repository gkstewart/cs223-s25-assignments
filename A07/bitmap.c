/*----------------------------------------------
 * Author: Gabby Stewart
 * Date: March 2025
 * Description: This program reads a 64-bit unsigned integer, interprets it as an 8x8 1bpp sprite.
 ---------------------------------------------*/
 #include <stdio.h>

 int main() {
     unsigned long img;
     scanf(" %lx", &img);
     printf("Image (unsigned long): %lx\n", img);
 
     unsigned long mask = 0x1ul << 63; 
     
     for (int i = 0; i < 8; i++) { //rows
         for (int j = 0; j < 8; j++) { // columns
             if (img & (mask >> (i * 8 + j))) {
                 printf("@");
             } else {
                 printf(" ");
             }
         }
         printf("\n");
     }
     
     return 0;
 }
 
