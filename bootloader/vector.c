#include <defines.h>

extern void start(void);

/**
 * @file vector.c
 * @brief 割り込みベクタの設定
 *        リンカスクリプトの定義により，先頭番地に配置される．
 *        vectorsの先頭に指定した関数が，ボードの電源ON時に実行される．
 *        リセット・ベクタとも．
 */
void (*vectors[])(void) = { //!< start() へのポインタを設定
	start, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	NULL,  NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	NULL,  NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	NULL,  NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	NULL,  NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	NULL,  NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	NULL,  NULL, NULL, NULL, NULL, NULL, NULL, NULL,
	NULL,  NULL, NULL, NULL, NULL, NULL, NULL, NULL,
};
