#include "defines.h"
#include "serial.h"
#include "lib.h"

int hoge;
volatile int fuga = 128;
static int s_hoge;
static int s_fuga = 128;

int main(void)
{
	serial_init(SERIAL_DEFAULT_DEVICE);

	puts( "fuga!\n");
	putxval(fuga, 4); puts("\n");
	fuga++;
	putxval(fuga, 4); puts("\n");

	while(1);
	return 0;
}
