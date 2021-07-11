#include "cstring.h"

int inttostr(uint32_t num){
    char str[100] = {0};
    char buf[100] = {0};
	int negative = 0;
	int len = 0, k = 0, i = 0, tmp = 0, n = 0, lenstr = 0;
 
	if(num < 0){
		negative = 1;
		n = -num;
	} else {
		n = num;
	}
 
	do{
		tmp = n % 10;
		buf[k++] = tmp + '0';
		n = n / 10;
	} while(n != 0);
 
	len = k;
	lenstr = len;
 
	k = 0;
	if(1 == negative){
		str[k++] = '-';
		lenstr = lenstr + 1;
	}
 
	for(i = len - 1; i >= 0; i--){
		str[k++] = buf[i];
	}
	
	str[lenstr] = '\0';
	
	return str;
 
}