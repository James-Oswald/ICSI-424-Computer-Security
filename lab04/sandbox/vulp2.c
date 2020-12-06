/*  vulp2.c  */

#include <string.h>
#include <stdio.h>
#include <unistd.h>

int main(){
   char* fn = "/tmp/XYZ";
   char buffer[60];
   FILE*fp;
   scanf("%50s", buffer); /* get user input */
   if(!access(fn, W_OK)){
        uid_t effuid = geteuid();
        uid_t realuid = getuid();
        seteuid(realuid);
        fp = fopen(fn, "a+");
        if((int)fp != -1){
              fwrite("\n", sizeof(char), 1, fp);
              fwrite(buffer, sizeof(char), strlen(buffer), fp);
              fclose(fp);
        }else{
              printf("No permission\n");
        }
        seteuid(effuid);
   }
   else 
        printf("No permission \n");
}