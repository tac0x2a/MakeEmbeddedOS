#include "defines.h"
#include "serial.h"
#include "lib.h"

/** 1文字送信  */
int putc(unsigned char c)
{
	if( c == '\n' ){
		serial_send_byte(SERIAL_DEFAULT_DEVICE, '\r');
	}
	return serial_send_byte(SERIAL_DEFAULT_DEVICE, c);
}

/** 文字列送信 */
int puts(unsigned char *str)
{
	while(*str){
		putc(*(str++));
	}
	return 0;
}

void * memset(void *s, int c, size_t n){
	for( int i = 0; i < n; i++ ){
		char *dst = (char*)s;
		*(dst + i) = c;
	}
	return s;
}

void * memcpy(void *dest, const void *src, size_t n){
	for( int i = 0; i < n; i++ ){
		const char *s = (const char*)src;
		char *d = (char*)dest;
		*(d + i) = *(s + i);
	}
	return dest;
}

int memcmp(const void *s1, const void *s2, size_t n){
	for( int i = 0; i < n; i++ ){
		const char *src1 = ((const char*)s1) + i;
		const char *src2 = ((const char*)s2) + i;

		if( *src1 == '\0' ) return 0;
		if( *src2 == '\0' ) return 0;

		const int diff = *src1 - *src2;
		if( diff != 0 ) return diff;
	}
	return 0;
}

size_t strlen(const char *s){
	int len = 0;
	while( *(s + len) != '\0' ) len++;
	return len;
}

char *strcpy(char *dest, const char *src){
	while( *src != '\0' ){
		*dest = *src;
		src++;
		dest++;
	}
	return dest;
}

int strcmp(const char *s1, const char *s2){
	int n1 = strlen(s1);
	int n2 = strlen(s2);
	return memcmp(s1, s2, n1 < n2 ? n1 : n2 );
}

int strncmp(const char *s1, const char *s2, size_t n){
	return memcmp(s1, s2, n);
}
