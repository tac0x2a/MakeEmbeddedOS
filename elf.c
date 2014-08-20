#include "elf.h"

#include "defines.h"
#include "elf.h"
#include "lib.h"

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
	short program_header_num;	   // プログラムヘッダの個数
	short section_header_size;   // セクションヘッダのサイズ
	short section_header_num;	   // セクションヘッダの個数
	short section_name_index;    // セクション名格納するセクション
} ELF_HEADER;

// プログラムヘッダ
typedef struct  {
	long type;          // セグメントの種類
	long offset;        // ELFファイル内の位置
	long virtual_addr;  //論理アドレス(VA)
	long physical_addr; //物理アドレス(PA)
	long file_size;     // ELFファイル内のサイズ
	long memory_size;   // メモリ上のサイズ
	long flags;         //各種フラグ
	long align;         //アライメント
} ELF_PROGRAM_HEADDR;
