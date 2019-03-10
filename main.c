#include <stdio.h>
#include "includes/aes.h"

void hex_print(unsigned char *in, size_t len) {
    for(int i = 0; i < len; i++) {
        if(i % 4 == 0)
            printf("\n");
        printf("%02X ", *(in + i));
    }
    printf("\n\n");
}

int main() {
    // Initialize openSSL
    ERR_load_crypto_strings();
    OpenSSL_add_all_algorithms();
    OPENSSL_config(NULL);

    //create message pointer
    MSG *message = NULL;
    //input buffer, the AES alg (Rijndael) works on blocks of 16 bytes in a 4x4
    //If a string is 12 chars (bytes) it gets padded to 16.
    char input[16] = {0};
   

    //get message to be encrypted
    printf("Enter a message shorter than 16 chars: \n");
    fgets(input, 16, stdin);

    //initialize aes message (generates the key & iv)
    message = aes_init(input);
    
    printf("Key:\n");
    hex_print(message -> key, AES_KEY_SIZE);
    printf("IV:\n");
    hex_print(message -> iv, AES_KEY_SIZE);
    printf("Message:\n");
    hex_print(message -> raw_msg, message -> raw_msg_len);

    //send message to be encrypted
    if(aes256_encrypt(message) != 0) {
        printf("Error encrypting message!");
    }

    printf("Encrypted Message\n");
    hex_print(message -> enc_msg, message -> enc_msg_len);
    //zero the raw msg
    memset(message -> raw_msg, 0 , message -> raw_msg_len);

    //send encrypted message to be decrypted
    if(aes256_decrypt(message) != 0) {
        printf("Error decrypting message!");
    }

    printf("Decrypted Message\n");
    hex_print(message -> raw_msg, message -> raw_msg_len);

    //destroy message struct
    aes_cleanup(message);
    //clean up ssl;
    EVP_cleanup(); 
    CRYPTO_cleanup_all_ex_data(); //Stop data leaks
    ERR_free_strings();

    return 0;
}
