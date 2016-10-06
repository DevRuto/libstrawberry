#include "../../stdincl.h"

#include <libstrawberry/crypto/otp/isaac-otp.h>


sb_bool_t test_isaac_otp() {
	sb_crypto_otp_isaac_ctx_t isaac1, isaac2;
	sb_crypto_otp_isaac_init(&isaac1);
	sb_memcpy(&isaac2, &isaac1, sizeof(isaac2));

	char string[] = "UNKNCPCK. This is a test string thingy thing.";

	sb_size_t len = strlen(string);

	SB_MEM_BUFFER_ALLOC(uint8_t, xor_enc, len);
	SB_MEM_BUFFER_ALLOC(uint8_t, xor_dec, len);

	sb_crypto_otp_isaac_xor(&isaac1, xor_enc, string, len);
	sb_crypto_otp_isaac_xor(&isaac2, xor_dec, xor_enc, len);

	SB_MEM_BUFFER_ALLOC(uint8_t, add_enc, len);
	SB_MEM_BUFFER_ALLOC(uint8_t, sub_dec, len);

	sb_crypto_otp_isaac_add(&isaac1, add_enc, string, len);
	sb_crypto_otp_isaac_sub(&isaac2, sub_dec, add_enc, len);

	/*sb_vmemdump("Original", string, len);
	puts("");
	sb_vmemdump("Encrypted - XOR", xor_enc, len);
	puts("");
	sb_vmemdump("Decrypted - XOR", xor_dec, len);
	puts("");
	sb_vmemdump("Encrypted - ADD", add_enc, len);
	puts("");
	sb_vmemdump("Decrypted - SUB", sub_dec, len);
	puts("");*/

	sb_bool_t valid = (sb_memequ(string, xor_dec, len) && sb_memequ(string, sub_dec, len));

	SB_MEM_BUFFER_FREE(xor_enc);
	SB_MEM_BUFFER_FREE(xor_dec);
	SB_MEM_BUFFER_FREE(add_enc);
	SB_MEM_BUFFER_FREE(sub_dec);

	sb_crypto_otp_isaac_clear(&isaac1);
	sb_crypto_otp_isaac_clear(&isaac2);

	return valid;
}
