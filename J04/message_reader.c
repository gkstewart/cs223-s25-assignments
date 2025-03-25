//code jam 4 by Olivia and Gabby
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
struct metadata //struct meta data
{
float version;
unsigned int year;
unsigned int length;
};
void readbinfile(const char* filename){
  FILE *file = fopen(filename, "rb");
  if (!file) {
      perror("Error opening file");
      return;
  }
  char comment[256];
  fgets(comment,255,file);
struct metadata* store = malloc(sizeof(struct metadata));
fread((&store->version), sizeof(float),1, file );
fread((&store->year), sizeof(unsigned int), 1, file);
fread((&store->length), sizeof(unsigned int),1, file);
char* message = malloc(sizeof(char) * store->length); 
fread(message, sizeof(char), store->length, file);
printf("comment :%s \n",comment);
printf("version :%f \n", store->version);
printf("year : %d \n", store->year);
printf("length : %d \n", store->length);
printf("message : %s \n", message);
}
int main(int argc, char** argv){
readbinfile (argv[1]);
}