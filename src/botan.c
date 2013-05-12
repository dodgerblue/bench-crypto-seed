#include <iostream>
#include <botan/botan.h>
#include <botan/seed.h>
#include "util.h"

void botan_init(void **obj) {
	// Botan::LibraryInitializer init;
	*obj = new Botan::SEED();
	((Botan::SEED*)(*obj))->set_key((unsigned char *)MY_KEY, MY_BLOCKSIZE);
}

void botan_encrypt(void *obj, char *in, char *out, size_t blocks) {
	(*(Botan::SEED*)obj).encrypt_n((const unsigned char*)in, (unsigned char *)out, blocks);
}

void botan_decrypt(void *obj, char *in, char *out, size_t blocks) {
	(*(Botan::SEED*)obj).decrypt_n((const unsigned char*)in, (unsigned char *)out, blocks);
}

void botan_close(void *obj) {
	free(obj);
}
