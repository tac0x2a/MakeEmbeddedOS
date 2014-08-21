#ifndef ELF_H
#define ELF_H

// ELFフォーマットの解析。成功したらエントリポイントのアドレスを返す。
char *elf_load(char *buff);

#endif
