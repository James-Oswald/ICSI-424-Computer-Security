/*  vulp.c  */

#include <string.h>
#include <stdio.h>
#include <unistd.h>

int main(){
   char* fn = "/tmp/XYZ";
   char buffer[60];
   FILE*fp;
   scanf("%50s", buffer); /* get user input */
   if(!access(fn, W_OK)){
        fp = fopen(fn, "a+");
        fwrite("\n", sizeof(char), 1, fp);
        fwrite(buffer, sizeof(char), strlen(buffer), fp);
        fclose(fp);
   }
   else printf("No permission \n");
}