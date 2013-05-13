#ifndef UTIL_H_
#define UTIL_H_

#include <stdio.h>

// SEED works with 128 bit input / output data block size
#define MY_BLOCKSIZE 16 // bytes
#define MY_KEY "ThisIsTheNewShit"
#define BUFSIZE 128

struct crypto_api_t {
    unsigned char id;
    const char description[BUFSIZE];
    void (*init)(void **obj);
    void (*encrypt)(void *obj, char *in, char *out, size_t blocks);
    void (*decrypt)(void *obj, char *in, char *out, size_t blocks);
    void (*close)(void *obj);
};

void botan_init(void **obj);
void botan_encrypt(void *obj, char *in, char *out, size_t blocks);
void botan_decrypt(void *obj, char *in, char *out, size_t blocks);
void botan_close(void *obj);

void gcrypt_init(void **obj);
void gcrypt_encrypt(void *obj, char *in, char *out, size_t blocks);
void gcrypt_decrypt(void *obj, char *in, char *out, size_t blocks);
void gcrypt_close(void *obj);

void cryptopp_init(void **obj);
void cryptopp_encrypt(void *obj, char *in, char *out, size_t blocks);
void cryptopp_decrypt(void *obj, char *in, char *out, size_t blocks);
void cryptopp_close(void *obj);

#endif
