#include <stdio.h>
#include <string.h>
#include "util.h"

char in[17] = "abcdefghijklmnop";
char out[17];
char test[17];

int main() {
	void *obj = NULL;
	memset(out, 0, 17);
	memset(test, 0, 17);

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

	cryptopp_init(&obj);
	printf("%s\n", in);
	cryptopp_encrypt(obj, in, out, 1);
	printf("%s\n", out);
	cryptopp_decrypt(obj, out, test, 1);
	printf("%s\n", test);
	cryptopp_close(obj);

	return 0;
}
