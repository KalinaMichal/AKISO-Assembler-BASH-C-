#include <stdio.h>
int main(void){
	int i=0;
	while (i<=255)
{

 printf("%c[38;5;%dm Hello World\n",0x1B,i);
i++;
}

  /*const char *const color = "\033[0;00;15m";
  const char *const normal = "\033[0m";

  printf("%sHello World%s\n", color, normal);*/
  return 0;
    }

