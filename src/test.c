#include <stdio.h>
#include <string.h>
#include "util.h"

char in[17] = "abcdefghijklmnop";
char out[17];
char test[17];

int main() {
	printf("If everything was setup ok, you should see 3 identical sections of plaintext - ciphertext - plaintext\n");

	void *obj = NULL;
	memset(out, 0, 17);
	memset(test, 0, 17);
	printf("\n");

	botan_init(&obj);
	printf("%s\n", in);
	botan_encrypt(obj, in, out, 1);
	printf("%s\n", out);
	botan_decrypt(obj, out, test, 1);
	printf("%s\n", test);
	botan_close(obj);

	obj = NULL;
	memset(out, 0, 17);
	memset(test, 0, 17);
	printf("\n");

	gcrypt_init(&obj);
	printf("%s\n", in);
	gcrypt_encrypt(obj, in, out, 1);
	printf("%s\n", out);
	gcrypt_decrypt(obj, out, test, 1);
	printf("%s\n", test);
	gcrypt_close(obj);

	obj = NULL;
	memset(out, 0, 17);
	memset(test, 0, 17);
	printf("\n");

	cryptopp_init(&obj);
	printf("%s\n", in);
	cryptopp_encrypt(obj, in, out, 1);
	printf("%s\n", out);
	cryptopp_decrypt(obj, out, test, 1);
	printf("%s\n", test);
	cryptopp_close(obj);

	return 0;
}
