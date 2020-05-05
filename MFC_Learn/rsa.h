#ifndef _RSA_H_ 
#define _RSA_H_
 
#pragma once

int Encryption(char* Plaintext , char* RKey, char* Rn, char* Encryptext);
int Decryption(char* Encryptext , char* RKey, char* Rn, char* Plaintext);
void getRsakey(char* UK, char* RK, char* Rn, int* len);
int Change(char* s, int len, char* bits);
 
#endif //_RSA_H_