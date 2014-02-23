#ifndef _LIB_H_INCLUDED_
#define _LIB_H_INCLUDED_

typedef long size_t;

int putc(unsigned char c);   /** 1文字送信  */
int puts(unsigned char *str);/** 文字列送信 */

void * memset(void *s, int c, size_t n);
void * memcpy(void *dest, const void *src, size_t n);
int memcmp(const void *s1, const void *s2, size_t n);
size_t strlen(const char *s);
char *strcpy(char *dest, const char *src);
int strcmp(const char *s1, const char *s2);
int strncmp(const char *s1, const char *s2, size_t n);

#endif
