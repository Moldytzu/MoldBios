#include "cstring.h"

int strlen(char* str) {
	int i = 0;
	for(;str[i] !=0;i++);
	return i;
}

int strcmp(const char *s1, const char *s2) {
	while (*s1 == *s2++)
		if (*s1++ == 0)
			return 0;
	return (*(unsigned char *)s1 - *(unsigned char *)--s2);
}

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

char toupper(char chr) {
	if(chr >= 'A' && chr <= 'Z')
		return chr + 32;
	return chr;
}
