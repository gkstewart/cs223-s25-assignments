/*----------------------------------------------
 * Author: Gabby S.
 * Date: March 2025
 * Description: a program that reads in a PPM file and asks the user for a message to embed within it.
 ---------------------------------------------*/
 #include <stdio.h>
 #include <string.h>
 #include <stdlib.h>
 #include "read_ppm.h"
 #include "write_ppm.h"
 
 int main(int argc, char** argv) {
     if (argc != 2) {
         printf("usage: encode <file.ppm>\n");
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
 
     char message[max_chars + 1];
     printf("Enter a phrase: ");
     fgets(message, max_chars + 1, stdin);
     message[strcspn(message, "\n")] = '\0'; 
 
     int bit_pos = 0;
     for (int i = 0; i < strlen(message) + 1; i++) { 
         for (int j = 7; j >= 0; j--) {
             pixels[bit_pos].red = (pixels[bit_pos].red & ~1) | ((message[i] >> j) & 1);
             bit_pos++;
         }
     }
 
     char output_filename[256];
     snprintf(output_filename, sizeof(output_filename), "%s-encoded.ppm", argv[1]);
     printf("Writing file %s\n", output_filename);
     write_ppm(output_filename, pixels, width, height);
 
     free(pixels);
     return 0;
 }
 

