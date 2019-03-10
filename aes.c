#include "includes/aes.h"

MSG *aes_init(char * input) {
    MSG *message = malloc(sizeof(MSG));
    int in_len = strlen(input);
    //chars are always exactly 1 byte
    message -> raw_msg_len = in_len;
    message -> enc_msg_len = in_len + AES_BLOCK_SIZE;
    message -> raw_msg = malloc(in_len);
    message -> enc_msg = malloc(in_len + AES_BLOCK_SIZE);
    message -> key = malloc(AES_KEY_SIZE);
    message -> iv = malloc(AES_KEY_SIZE);

    //c will allocate the memory but the memory may still have data in it
    memset(message -> enc_msg, 0, in_len + AES_BLOCK_SIZE);
    //copy over the message
    strcpy(message -> raw_msg, input); 

    if(RAND_bytes(message -> key, AES_KEY_SIZE) != 1) {
        printf("Error: couldn't generate key.");
        exit(1);
    }

    if(RAND_bytes(message -> iv, AES_KEY_SIZE) != 1) {
        printf("Error: couldn't generate iv.");
        exit(1);
    }

    return message;
}

//TO-DO: expand for text larger than 16 bytes
int aes256_encrypt(MSG *msg) {
    EVP_CIPHER_CTX *enc_ctx;
    enc_ctx = EVP_CIPHER_CTX_new();
    
    EVP_EncryptInit(enc_ctx, EVP_aes_256_cbc(), msg -> key, msg -> iv);
    if(!EVP_EncryptUpdate(enc_ctx, msg -> enc_msg, &msg -> enc_msg_len, msg -> raw_msg, msg -> raw_msg_len)) {
        EVP_CIPHER_CTX_cleanup(enc_ctx);
        printf("EVP Error: couldn't update encryption with plain text!\n");
        return 1;
    }
    if(!EVP_EncryptFinal_ex(enc_ctx, msg -> enc_msg, &(msg -> enc_msg_len))) {
        EVP_CIPHER_CTX_cleanup(enc_ctx);
        printf("EVP Error: couldn't finalize encryption!\n");
        return 1;
    }
    return 0;
}

int aes256_decrypt(MSG *msg) {
    EVP_CIPHER_CTX *dec_ctx;

    dec_ctx = EVP_CIPHER_CTX_new();
    
    EVP_DecryptInit(dec_ctx, EVP_aes_256_cbc(), msg -> key, msg -> iv);
    if(!EVP_DecryptUpdate(dec_ctx, msg -> raw_msg, &(msg -> raw_msg_len), msg -> enc_msg, msg -> enc_msg_len)) {
        EVP_CIPHER_CTX_cleanup(dec_ctx);
        printf("EVP Error: couldn't update decrypt with text!\n");
        return 1;
    }

    if(!EVP_DecryptFinal_ex(dec_ctx, msg -> raw_msg, &(msg -> raw_msg_len))) {
        EVP_CIPHER_CTX_cleanup(dec_ctx);
        printf("EVP Error: couldn't finalize decryption!\n");
        return 1;
    }
    return 0;
}

void aes_cleanup(MSG *message) {
    free(message -> enc_msg);
    free(message -> raw_msg);
    free(message -> key);
    free(message -> iv);
    free(message);

}

