#include "encrpytengine.hpp"

 unsigned long long hash_str(const char* s);
 
 std::string uint64_to_str(uint64_t num){
     return std::to_string(num);
 }

 std::string EncryptedHeader::getHeader(const std::string& id, const std::string& pass){
     uint64_t uhash = hash_str(id.c_str());
     uint64_t phash = hash_str(pass.c_str());

     std::string uhash_str = uint64_to_str( uhash );
     std::string phash_str = uint64_to_str( phash );

     std::string seed = uint64_to_str(uhash + phash);
     std::string secret = uhash_str + phash_str;

     EncryptEngine headerEncrypter(uhash_str + phash_str, seed, secret);
     
     return headerEncrypter.getEncryptedText();
 }

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
 

