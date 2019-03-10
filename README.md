# OpenSSL-AES

An example of using OpenSSL EVP Interface for aes256 in cipher block chaining mode (CBC).
For more information visit the [OpenSSL docs](https://www.openssl.org/docs/manmaster/)

## Usage
Compile the code with:
```
gcc main.c -lcrypto aes.c -o main
```

## Reason
This is coming to github as part of my 30-day consecutive activity goal.  I saw loads of questions on
stackoverflow on how to implement a simple aes256 example. So here it is!

## Sample Output
```
root@server:~$ gcc main.c -lcrypto aes.c -o main
root@server:~$ ./main
Enter a message shorter than 16 chars: 
Hello World!    
Key:

3A 45 17 FE 
C8 28 F2 7C 
83 22 10 51 
9E 3D 75 F8 
BD 0E 44 FF 
1A 14 D4 99 
54 F0 77 32 
CF 36 72 3F 

IV:

85 90 D7 55 
C9 36 A7 3D 
B6 8C 0A CA 
4D B4 9E 54 
B1 06 18 F4 
D6 C8 A1 DB 
51 F0 80 17 
3C 8B 9C 4D 

Message:

48 65 6C 6C 
6F 20 57 6F 
72 6C 64 21 
0A 

Encrypted Message

AF 5C 1E 1D 
BC AD 2E 2F 
9D 08 B2 A6 
52 0C D7 12 

Decrypted Message

48 65 6C 6C 
6F 20 57 6F 
72 6C 64 21 
0A 

```