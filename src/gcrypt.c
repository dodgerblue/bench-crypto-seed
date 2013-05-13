#include <gcrypt.h>
#include "util.h"

void gcrypt_init(void **obj) {
	gcry_error_t err = 0;

	*obj = malloc(sizeof(gcry_cipher_hd_t));

	/* Disable secure memory.  */
	gcry_control (GCRYCTL_DISABLE_SECMEM, 0);

	/* Tell Libgcrypt that initialization has completed. */
	gcry_control (GCRYCTL_INITIALIZATION_FINISHED, 0);

	err = gcry_cipher_open ((gcry_cipher_hd_t*)(*obj), GCRY_CIPHER_SEED, GCRY_CIPHER_MODE_ECB, 0);
	if (err != GPG_ERR_NO_ERROR) {
		printf("Error opening libgcrypt handle %u\n", err);
		exit(1);
	}

	err = gcry_cipher_setkey (*(gcry_cipher_hd_t*)(*obj), MY_KEY, MY_BLOCKSIZE);
	if (err != GPG_ERR_NO_ERROR) {
		printf("Error setting handle key %u\n", err);
		exit(1);
	}
}

void gcrypt_encrypt(void *obj, char *in, char *out, size_t blocks) {
	gcry_error_t err = 0;

	err = gcry_cipher_encrypt(*(gcry_cipher_hd_t *)obj, out, blocks * MY_BLOCKSIZE, in, blocks * MY_BLOCKSIZE);
	if (err != GPG_ERR_NO_ERROR) {
		printf("Error encrypting %u\n", err);
		exit(1);
	}
}

void gcrypt_decrypt(void *obj, char *in, char *out, size_t blocks) {
	gcry_error_t err = 0;

	gcry_cipher_decrypt(*(gcry_cipher_hd_t *) obj, out, blocks * MY_BLOCKSIZE, in, blocks * MY_BLOCKSIZE);
	if (err != GPG_ERR_NO_ERROR) {
		printf("Error decrypting %u\n", err);
		exit(1);
	}
}

void gcrypt_close(void *obj) {
	free(obj);
}
