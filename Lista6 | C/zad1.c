/*Lista 5 zadanie 1*/


#include <stdarg.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#define TRUE 1
#define FALSE 0
#define BUFFER_SIZE 1024

int power(int a, int b) {
  if (b == 0) {
    return 1;
  } else {
    return a * power(a, b-1);
  }
}


char * int_to_string(int number, int base) {
  int num_of_digits = 0;
  int number_copy;
  int isNegative = 0;  
  
  if (number < 0) {
    isNegative = 1;
    number *= (-1);
  }

  number_copy = number;

  while(number_copy > 0) {
    number_copy /= base;
    num_of_digits++;
  }

  number_copy = number;

  char *result = malloc((num_of_digits + 1 + isNegative) * sizeof(char));

  if (isNegative) {
    result[0] = '-';
  }

  if (base <= 10) {
    for(int i = (num_of_digits - 1 + isNegative); i >= isNegative; i--) {
      result[i] = number_copy%base + '0';
      number_copy /= base;
    }
  } else {
    char digits[] = {'A', 'B', 'C', 'D', 'E', 'F'};
    int digit;
    for(int i = (num_of_digits - 1 + isNegative); i >= isNegative; i--) {
      digit = number_copy%base;
      if (digit < 10) {
        result[i] = digit + '0';
      } else {
        result[i] = digits[digit%10];
      }
      number_copy /= base;
    }
  }

  result[num_of_digits + isNegative] = '\0';

  return result;
}

int string_to_int(char *string, int base) {
  int isNegative = 0;
  int num_of_digits = 0;
  int result = 0;

  if (string[0] == '-') {
    isNegative = 1;
  }

  int i = isNegative;

  while(string[i] != '\0' && string[i] != '\n') {
    num_of_digits++;
    i++;
  }
  
  for (int i = (num_of_digits - 1 + isNegative); i >= isNegative; i--) {
    if (string[i] >= 'A' && string[i] <= 'F') {
      result += (string[i] - 'A' + 10) * power(base, num_of_digits - i + isNegative - 1);
    } else {
      result += (string[i] - '0') * power(base, num_of_digits - i + isNegative - 1);
    }
  }

  return result * power(-1, isNegative);
}

/*
int myscanf(char* format, ... )
{
int dl = 0; //dlugosc mojej wiadomosci
int i=0;

if(format[0]== '%')
{
	switch(format[1]){
		case 's':{//dla stringa/char-a
        	char **strArg = (char**) (*(char**) p);
          	char *string = malloc(BUFFER_SIZE);
          	read(0, string, BUFFER_SIZE);
          
		//jesli string liczony od pew. miejsca jest rowny \n
          if (string[strlen(string) - 1] == '\n') {
            string[strlen(string) - 1] = '\0';
          }
          *strArg = string;
}
          p += sizeof(*strArg);
          break;
			
  p = NULL;

  return len;



}
*/




int myprintf2(const char * format, ... )
{
	int i=1;
	int dlugosc=strlen(format);
  	char *zmien = (char *) &format + sizeof format; //to je po to że gdy momy więcej niż 1 argument
		
	while(*format)
	{
		if(*format=='%')
		{
			format++;
			switch(*format)
			{
				case 's':
				{
					int *s= *((char **)zmien);	
					write(1, s, 3);
					format++;
          					break;
				}
        			case 'd': {//dziesietny
          			int *d = ((int *)zmien);
          			myprintf2("%s", int_to_string(*d, 10));
          			zmien += sizeof(int);
					format++;
         			 break;
        			}
        			case 'b': {//binarny
          			int *b = ((int *)zmien);
          			myprintf2("%s", int_to_string(*b, 2));
          			zmien += sizeof(int);
					format++;
         			 break;
        			}
        			case 'x': {//szesnastkowy
          			int *x = ((int *)zmien);
          			myprintf2("%s", int_to_string(*x, 16));
          			zmien += sizeof(int);
					format++;
         			 break;
        			}
			}
		
		}
		else if(*format=='\n')
		{
			write(1, "\n", 1);
			format++;
			format++;
		}
		else{
      		write(1, format, 1);
		format++;
		}
		i++;
	}
}


int myscanf(const char * format, ...) {
  int len = 0;;

  char *p = (char *) &format + sizeof format;

  while (*format) {
    if (*format == '%') {
      format++;
      switch(*format) {
        case 'x': {
          int *d = (int*)(*(int*)p);
          char *string = malloc(BUFFER_SIZE);
          read(0, string, BUFFER_SIZE);
          *d = string_to_int(string, 16);
          p += sizeof(int*);
          break;
        }
        case 'd': {
          int *d = (int*)(*(int*)p);
          char *string = malloc(BUFFER_SIZE);
          read(0, string, BUFFER_SIZE);
          *d = string_to_int(string, 10);
          p += sizeof(int*);
          break;
        }
        case 's': {
          char *string = malloc(BUFFER_SIZE);
          read(0, string, BUFFER_SIZE);
          
          if (string[strlen(string) - 1] == '\n') {
            string[strlen(string) - 1] = '\0';
          }
          break;
        }
        case 'b': {
          int *d = (int*)(*(int*)p);
          char *string = malloc(BUFFER_SIZE);
          read(0, string, BUFFER_SIZE);
          *d = string_to_int(string, 2);
          p += sizeof(int*);
          break;
        }
      }
      format++;
    } else {
      format++;
    }
  }

  p = NULL;

  return len;
}




int main(int argc, char *argv[]) {
  char *test;
  int d = 1; 
int b, x;
  //myprintf2("Wprowadz stringa: ");
  myscanf("%s", &test);
  myprintf2("wiadomosc: %slol  ", test);
  myprintf2("liczba: %d", d);
  myprintf2("1 numer: dec: %d, bin: %b,\n, hex: %x a", d, d, d);

  /*myprintf("Podaj numer 1 w sys dzieisietnym: ");
  myscanf("%d", &d);
  myprintf("Podaj numer 2 w systemie dwojkowym: ");
  myscanf("%b", &b);
  myprintf("Podaj numer 3 w systemie szesnastkowym: ");
  myscanf("%x", &x);
  myprintf("Twoj napis: %s\n", test);
  myprintf("1 numer: dec: %d, bin: %b, hex: %x\n", d, d, d);
  myprintf("2 numer: bin: %b, hex: %x, dec: %d\n", b, b, b);
  myprintf("3 numer: hex: %x, dec: %d, bin: %b\n", x, x, x);*/
  return 0;
}
