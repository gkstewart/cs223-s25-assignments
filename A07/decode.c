/*----------------------------------------------
 * Author: Gabby S.
 * Date: March 2025
 * Description: a program that reads in a PPM file and then outputs any message that might be stored in the least significant bits of each color.
 ---------------------------------------------*/
 #include <stdio.h>
 #include <stdlib.h>
 #include "read_ppm.h"
 
 int main(int argc, char** argv) {
     if (argc != 2) {
         printf("usage: decode <file.ppm>\n");
         return 0;
     }
 
     int width, height;
     struct ppm_pixel* pixels = read_ppm(argv[1], &width, &height);
     if (!pixels) {
         printf("Error: Unable to read file %s\n", argv[1]);
         return 1;
     }
 
     printf("Reading %s with width %d and height %d\n", argv[1], width, height);
     int max_chars = (width * height * 3) / 8;
     printf("Max number of characters in the image: %d\n", max_chars);
 
     unsigned char message[max_chars + 1]; 
     int bit_pos = 0;
     unsigned char current_char = 0;
     int char_index = 0;
 
     for (int i = 0; i < width * height * 3; i++) {
         current_char = (current_char << 1) | (pixels[i].red & 1);
         bit_pos++;
         if (bit_pos == 8) {
             if (current_char == '\0') break;
             message[char_index++] = current_char;
             bit_pos = 0;
             current_char = 0;
         }
     }
 
     message[char_index] = '\0'; 
     printf("%s\n", message);
 
     free(pixels);
     return 0;
 }
 

