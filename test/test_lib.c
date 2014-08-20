#include "unity.h"
#include "unity_fixture.h"

#define getc    kz_getc
#define gets    kz_gets
#define putc    kz_putc
#define puts    kz_puts
#define size_t  kz_size_t
#define strncmp kz_strncmp
#define strlen  kz_strlen
#define memcmp  kz_memcmp
#define memset  kz_memset
#define memcpy  kz_memcpy


#undef NULL

#include "../bootloader/serial.h"
#include "../bootloader/serial.c"
#include "../bootloader/defines.h"
#include "../bootloader/lib.h"
#include "../bootloader/lib.c"

TEST_GROUP(lib);
TEST_SETUP(lib){}
TEST_TEAR_DOWN(lib){}

TEST(lib, format_int2hex_complete0){ // 先頭が0でもパディングする
	char buff[32];
	memset(buff, '\0', 32);
	format_int2hex(buff, 0x000a005a, 8);
	TEST_ASSERT_EQUAL_STRING("000a005a", buff);
}

TEST_GROUP_RUNNER(lib){
	RUN_TEST_CASE(lib, format_int2hex_complete0);  // 先頭が0でもパディングする
}
