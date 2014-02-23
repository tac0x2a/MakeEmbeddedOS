#include "defines.h"
#include "serial.h"
#include "lib.h"

int main(void)
{
	serial_init(SERIAL_DEFAULT_DEVICE);

	puts( "hoge!\n");
	putxval(0x2a, 4); puts("\n");
	puts( "Hello World!\n");
	while(1);
	return 0;
}
