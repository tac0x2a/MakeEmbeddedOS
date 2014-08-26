#include <defines.h>
#include <serial.h>
#include <lib.h>

int main(void) {

  puts("Hello,World\n");

  static char cmd_buff[32];
  while(1){

    puts("tacos> ");
    gets(cmd_buff);

    #define MATCH(command) (strcmp(cmd_buff,command) == 0)
    #define MATCH_N(command, n) (strncmp(cmd_buff,command, n) == 0)

    if(MATCH_N("echo", 4)){
      puts(cmd_buff + 4); //残りの引数部分を出力
      puts("\n");
    }
    else if(MATCH("exit")){
      return 0;
    }
    else if( strlen(cmd_buff) > 0 ) {
      puts("undefined command.\n");
    }

  } // end of while(1)

  return 0;
}
