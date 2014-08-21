#include <defines.h>
#include <serial.h>
#include <lib.h>
#include "xmodem.h"

#define XMODEM_SOH 0x01
#define XMODEM_STX 0x02
#define XMODEM_EOT 0x04 //データのおわり
#define XMODEM_ACK 0x06
#define XMODEM_NAK 0x15
#define XMODEM_CAN 0x18
#define XMODEM_EOF 0x1a

#define XMODEM_BLOCK_SIZE 128

/* 受信開始されるまで送信要求 (NAC) を送る
*/
static int xmodem_wait(void) {
	long cnt = 0;
	while(!serial_is_recv_enable(SERIAL_DEFAULT_DEVICE)){
		cnt++;
		if( cnt > 20000 ){
			cnt = 0;
			serial_send_byte(SERIAL_DEFAULT_DEVICE, XMODEM_NAK);
		}
	}
	return 0;
}

/* ブロック単位で受信
	 成功: 受信したバイト数
	 失敗: -1
*/
static int xmodem_read_block(unsigned char block_id, char *buf){

	// ブロック番号
	const unsigned char block_id_recv = serial_recv_byte(SERIAL_DEFAULT_DEVICE);
	if( block_id_recv != block_id ){
		return -1;
	}

	// ブロック番号を反転したもの(チェック用)
	const unsigned char block_id_inv = serial_recv_byte(SERIAL_DEFAULT_DEVICE);
	if( (block_id_recv ^ block_id_inv) != 0xFF ){
		return -1;
	}

	// いよいよブロック受信
	unsigned char check_sum = 0;
	int i = 0;
	for( i = 0; i < XMODEM_BLOCK_SIZE; i++ ){
		const unsigned char c = serial_recv_byte(SERIAL_DEFAULT_DEVICE);
		*(buf) = c;
		buf++;
		check_sum += c;
	}

	// チェックサムを反転したもの
	const char check_sum_inv = serial_recv_byte(SERIAL_DEFAULT_DEVICE);
	if( (check_sum^check_sum_inv) != 0x00 ){
		return -1;
	}

	return i;
}


/* ブロックを受けとれるだけ受け取ってbuffへ詰めて返す.
	 受信失敗orキャンセル: -1
	 受信成功            : 受信したデータサイズ[byte]
*/
long xmodem_recv(unsigned char *buff){

	unsigned char r_block_cnt  = 1; //1はじまりのうほうがいいらしい
	unsigned long r_total_size = 0;

	while(1) {

		// 受信準備出来たので送信要求を出す
		if(r_total_size <= 0)	xmodem_wait();

		const char c = serial_recv_byte(SERIAL_DEFAULT_DEVICE);
		if( c == XMODEM_CAN ) return -1; //キャンセル
		if( c == XMODEM_EOT ) { //データ終端
			serial_send_byte(SERIAL_DEFAULT_DEVICE, XMODEM_ACK);
			return r_total_size;
		}

		if( c == XMODEM_SOH ) {
			// 1ブロック受信
			const int received_byte = xmodem_read_block(r_block_cnt, &buff[r_total_size]);

			if(received_byte >= 0){ //受信できたっぽい
				r_block_cnt++;
				r_total_size += received_byte;
				serial_send_byte(SERIAL_DEFAULT_DEVICE, XMODEM_ACK);
			} else {// 受信失敗、再送要求
				serial_send_byte(SERIAL_DEFAULT_DEVICE, XMODEM_NAK);
			}
		} else { // なんかおかしいのが来た
			if( r_total_size > 0 ) return -1;
		}

	} // end of While
}
