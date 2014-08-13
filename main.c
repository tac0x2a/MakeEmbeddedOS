#include "defines.h"
#include "serial.h"
#include "lib.h"

static int init(){

	/* リンカスクリプトで定義されているシンボル */
  extern int text_start,   etext;
  extern int rodata_start, erodata;// ROM上のデータ
	extern int data_start,   edata;  // 初期値のある静的データ
	extern int bss_start,    ebss;   // 初期値のない静的データデータ
	extern int stack;

	/** データ領域とBSS領域を初期化する */
	const long data_length = (long)&edata - (long)&data_start; // データ領域のサイズ
	memcpy(&data_start, &erodata, data_length); // ROM領域中の rom の終端からRAMまでごっそりコピーする
  //TODO ここよくわからん。rodataセクションの終端から dataの初期値が入ってるってこと？

	const long bss_length = (long)&ebss - (long)&bss_start; // BSS領域のサイズ。
	memset(&bss_start, 0, bss_length); //初期化されてない静的領域なので0で初期化してあげる

  /** シリアルの初期化 */
	serial_init(SERIAL_DEFAULT_DEVICE);

	return 0;
}

int hoge;
volatile int fuga = 128;
static int s_hoge;
static int s_fuga = 128;

int main(void)
{
	init();

	puts( "fuga!\n");
	putxval(fuga, 4); puts("\n");
	fuga++;
	putxval(fuga, 4); puts("\n");

	while(1);
	return 0;
}
