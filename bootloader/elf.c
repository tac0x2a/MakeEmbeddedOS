#include <defines.h>
#include <lib.h>
#include "elf.h"

// ELFヘッダ
typedef struct {
  // 16バイトの識別情報
  struct {
    unsigned char magic[4];    // マジックナンバ
    unsigned char class;       // 32,64bitの区別
    unsigned char format;      // エンディアン情報
    unsigned char version;     // ELFフォーマットのバージョン
    unsigned char abi;         // OSの種類
    unsigned char abi_version; // OSのバージョン
    unsigned char reserve[7];  // 予約領域(未使用)
  } id;
  short type;                  // ファイルの種別
  short arch;                  // CPUの種類
  long  version;               // ELF形式のバージョン
  long  entry_point;           // エントリポイント(実行開始アドレス)
  long  program_header_offset; // プログラム・ヘッダテーブルの位置
  long  section_header_offset; // セクション・ヘッダテーブルの位置
  long  falgs;                 // 各種フラグ
  short header_size;           // ELFヘッダのサイズ
  short program_header_size;   // プログラムヘッダのサイズ
  short program_header_num;    // プログラムヘッダの個数
  short section_header_size;   // セクションヘッダのサイズ
  short section_header_num;    // セクションヘッダの個数
  short section_name_index;    // セクション名格納するセクション
} ELF_HEADER;

// プログラムヘッダ
typedef struct  {
  long type;          // セグメントの種類
  long offset;        // ELFファイル内の位置
  long virtual_addr;  // 論理アドレス(VA)
  long physical_addr; // 物理アドレス(PA)
  long file_size;     // ELFファイル内のサイズ
  long memory_size;   // メモリ上のサイズ
  long flags;         // 各種フラグ
  long align;         // アライメント
} ELF_PROGRAM_HEADDR;

// ELFヘッダのバリデーション。不正な場合は -1, 正しい場合は 0 を返す。
static int elf_check(ELF_HEADER *header){
  if(header == NULL) return -1;

  // check Magic Number.
  if( memcmp(header->id.magic, "\x7f" "ELF", 4) != 0 ) return -1;

  if(header->id.class   != 1) return -1; // Required ELF32.
  if(header->id.format  != 2) return -1; // Required Big endian.
  if(header->id.version != 1) return -1; // Required version 1.
  if(header->type       != 2) return -1; // Required Executable file.
  if(header->version    != 1) return -1; // Required version 1.

  // Is H8 ?
  if(header->arch != 46 && header->arch != 47) return -1;

  return 0; // Is correct.
}

// セグメント単位でのロード(プログラムヘッダの解析)
static int elf_load_program(ELF_HEADER *header){
  if(header == NULL) return -1;

  for( int i = 0; i < header->program_header_num; i++ ){

    // i番目のプログラムヘッダテーブルの先頭アドレス
    const ELF_PROGRAM_HEADDR *program_header =
      (char*)header +
      header->program_header_offset +
      header->program_header_size * i;

    // ロード対象ではないセグメントは解析しない
    if(program_header->type != 1) continue;

    { //TODO サンプルだよ！
      putxval(program_header->offset,6);        puts(" ");
      putxval(program_header->virtual_addr,8);  puts(" ");
      putxval(program_header->physical_addr,8); puts(" ");
      putxval(program_header->file_size,5);     puts(" ");
      putxval(program_header->memory_size,5);   puts(" ");
      putxval(program_header->flags,2);         puts(" ");
      putxval(program_header->align,2);         puts("\n");
    }

    // 物理アドレスにセグメントをロード
    memcpy((char*)program_header->physical_addr,
           (char*)program_header->offset,
           program_header->file_size);

    // "ELFファイル内のサイズ < メモリ上のサイズ" なところを0で埋める
    memset( (char*)(program_header->physical_addr + program_header->file_size),
            0x00,
            program_header->memory_size - program_header->file_size);

  } // end of for segments.

  return 0;
}


// ELFフォーマットの解析。成功したらエントリポイントのアドレスを返す。
char *elf_load(char *buff){
  if(buff == NULL) return NULL;

  const ELF_HEADER *header = (ELF_HEADER*)buff;
  if( elf_check(header) < 0 ) return NULL;

  int res_load = elf_load_program(header);
  if( res_load < 0 ) return NULL;

  return header->entry_point;
}
