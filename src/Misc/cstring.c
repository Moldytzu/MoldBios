#include "cstring.h"

int inttostr(uint32_t num){
    volatile char str[100] = {0};
    char buf[100] = {0};
	int k = 0, tmp = 0;
 
	do{
		tmp = num % 10;
		buf[k++] = tmp + '0';
		num = num / 10;
	} while(num != 0);
 
	tmp = k;
	k = 0;
 
	for(int i = tmp - 1; i >= 0; i--){
		str[k++] = buf[i];
	}
	
	str[tmp] = '\0';
	
	return str;
}