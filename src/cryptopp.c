#include <crypto++/modes.h>
#include <crypto++/seed.h>
#include "util.h"

struct cryptopp_t {
	CryptoPP::ECB_Mode<CryptoPP::SEED>::Encryption *enc;
	CryptoPP::ECB_Mode<CryptoPP::SEED>::Decryption *dec;
};

void cryptopp_init(void **obj) {
	struct cryptopp_t * res = (struct cryptopp_t *) malloc(sizeof(struct cryptopp_t));
	res->enc = new CryptoPP::ECB_Mode<CryptoPP::SEED>::Encryption((const byte *)MY_KEY, MY_BLOCKSIZE);
	res->dec = new CryptoPP::ECB_Mode<CryptoPP::SEED>::Decryption((const byte *)MY_KEY, MY_BLOCKSIZE);
	*obj = res;
}

void cryptopp_encrypt(void *obj, char *in, char *out, size_t blocks) {
	((struct cryptopp_t *)obj)->enc->ProcessData((byte *)out, (const byte *)in, blocks * MY_BLOCKSIZE);
}

void cryptopp_decrypt(void *obj, char *in, char *out, size_t blocks) {
	((struct cryptopp_t *)obj)->dec->ProcessData((byte *)out, (const byte *)in, blocks * MY_BLOCKSIZE);
}

void cryptopp_close(void *obj) {
	free(((struct cryptopp_t *)obj)->enc);
	free(((struct cryptopp_t *)obj)->dec);
	free(obj);
}
