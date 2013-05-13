#include "util.h"

struct crypto_api_t {
    unsigned char id;
    const char description[];
    void (*init)(void *obj);
    void (*encrypt)(void *obj, char *in, char *out, size_t blocks);
    void (*decrypt)(void *obj, char *in, char *out, size_t blocks);
    void (*close)(void *obj);
};

struct crypto_api_y apis[] = {
    {0, "botan", botan_init, botan_encrypt, botan_decrypt, botan_close},
    {1, "libgcrypt", gcrypt_init, gcrypt_encrypt, gcrypt_decrypt, gcrypt_close},
    {2, "crypto++", cryptopp_init, cryptopp_encrypt, cryptopp_decrypt, cryptopp_close}
};
