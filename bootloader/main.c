#include "defines.h"
#include "serial.h"
#include "lib.h"
#include "elf.h"
#include "xmodem.h"

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

// buf を bytes だけダンプする
static int dump_h(unsigned char *buf, long bytes){
  if(bytes < 0){
    puts("no data.\n");
    return -1;
  }

  int i = 0;
  for( i = 0; i < bytes; i++ ){
    putxval(buf[i], 2);
    if( (i & 0xF) == 0xF ) puts("\n"); // 16バイトごとに改行
    if( (i & 0xF) == 0x7 ) puts(" ");  //  8バイトごとにスペース挿入
  }
  puts("\n");

  return 0;
}

// wait is 300000
static void wait(const long wait){
  volatile long i = 0;
  for( i = 0; i < wait; i++);
}

static int receive_program(unsigned char* buf){
  unsigned char *loadbuf = (unsigned char*)buf;
  long size = xmodem_recv(loadbuf);
  wait(300000);

  if( size < 0 ){ //受信失敗
    puts("\nXMODEM receive error!\n");
    return -1;
  }

  puts("\nXMODEM receive success!\n");

  return size;
}


int main(void) {

  extern int program_buffer;
  memset(&program_buffer, 0x00, 0x001d00);

  init();

  puts("kzload (kozos boot loader) started.\n");

  while(1){

    static long program_size = -1;

    #define CommandSize 16
    static char command_buff[CommandSize];
    memset(command_buff, 0x00, CommandSize);

    puts("kzload> ");
    gets(command_buff);

    #define MATCH(command) (strcmp(command_buff,command) == 0)

    if(MATCH("load")){ // XMODEMでファイルをダウンロード
      memset(&program_buffer, 0x00, 0x001d00);
      program_size = receive_program((unsigned char*)&program_buffer);
    }
    else if(MATCH("dump")){
      puts("size: "); putxval(program_size, 12);
      puts("\n");
      dump_h((unsigned char*)&program_buffer, program_size);
    }
    else if(MATCH("run")) {
      elf_load((unsigned char*)&program_buffer);
    }
    else {
      puts("unknown command.\n");
    }

  } // end of while(1)

  return 0;
}
