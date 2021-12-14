#include "encrpytengine.hpp"

 unsigned long long hash_str(const char* s);

 void EncryptEngine::encrypt(){
     unsigned long long secret_hash = hash_str(secret.c_str());
     std::string encrypted;
     for(int i = 0; i < text.length() ; i++){
         encrypted += (text.at(i) + (seed.at( i % seed.length() ) * secret_hash)) % 256;
     }
     enc_text = encrypted;
 }


 std::string EncryptEngine::getEncryptedText(){
     if(enc_text == "NULL"){
        this->encrypt();
     }
     return enc_text;
 }


 void DecryptEngine::decrypt(){
     unsigned long long secret_hash = hash_str(secret.c_str());
     std::string decrpyted;
     for(int i = 0; i < text.length() ; i++){
         decrpyted += (text.at(i) - (seed.at( i % seed.length() ) * secret_hash)) % 256;
     }
     dec_text = decrpyted;
 }

 std::string DecryptEngine::getDecryptedText(){
     if(dec_text == "NULL"){
        this->decrypt();
     }
     return dec_text;
 }
 

