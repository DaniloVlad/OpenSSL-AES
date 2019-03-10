#ifndef AES_H_
#define AES_H_

#include <stdlib.h>
#include <string.h>
#include <openssl/conf.h>
#include <openssl/evp.h>
#include <openssl/rand.h>
#include <openssl/err.h>

#define AES_BLOCK_SIZE 16
#define AES_KEY_SIZE 32

typedef struct msg_struct
{
    char *raw_msg;
    int raw_msg_len;
    unsigned char *enc_msg;
    int enc_msg_len;
    unsigned char *key;
    unsigned char *iv;
} MSG;

MSG * aes_init(char *);

int aes256_encrypt(MSG *);

int aes256_decrypt(MSG *);

void aes_cleanup();

#endif