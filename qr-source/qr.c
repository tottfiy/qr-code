#include <qr.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// #include "qrcodegen.h"

// static void genQR(void) {
// 	const char *text =
// 			"Alice was beginning to get very tired of sitting by her sister on the bank, "
// 			"and of having nothing to do: once or twice she had peeped into the book her sister was reading, "
// 			"but it had no pictures or conversations in it, 'and what is the use of a book,' thought Alice "
// 			"'without pictures or conversations?' So she was considering in her own mind (as well as she could, "
// 			"for the hot day made her feel very sleepy and stupid), whether the pleasure of making a "
// 			"daisy-chain would be worth the trouble of getting up and picking the daisies, when suddenly "
// 			"a White Rabbit with pink eyes ran close by her.";
// 		uint8_t qrcode[qrcodegen_BUFFER_LEN_MAX];
// 		uint8_t tempBuffer[qrcodegen_BUFFER_LEN_MAX];
// 		bool ok = qrcodegen_encodeText(text, tempBuffer, qrcode,
// 			qrcodegen_Ecc_HIGH, qrcodegen_VERSION_MIN, qrcodegen_VERSION_MAX, qrcodegen_Mask_AUTO, true);
// 		if (ok)
// 			printQr(qrcode);
// }

// int main() {
//     input_handler();
//     return 0;
// }