#include "../inc/encrpytengine.hpp"
#include "../inc/ascii_avoid_list.hpp"

 unsigned long long hash_str(const char* s);
 
 std::string uint64_to_str(uint64_t num){
     return std::to_string(num);
 }

 uint8_t BaseEngine::_getCeasarShiftedChar(uint8_t c, const uint64_t& shift_amount, bool to_right){
     uint8_t actual_shift = shift_amount % (UCHAR_MAX + 1 - AVOID_LIST_SIZE);
     if(actual_shift == 0) return c;
     return ( to_right ) ? jump_avoid_elements_right(c, actual_shift) : jump_avoid_elements_left(c, actual_shift) ;
 } 

 std::string EncryptedHeader::getHeader(const std::string& id, const std::string& pass){
     uint64_t uhash = hash_str(id.c_str());
     uint64_t phash = hash_str(pass.c_str());

     std::string uhash_str = uint64_to_str( uhash );
     std::string phash_str = uint64_to_str( phash );

     std::string seed = uint64_to_str(uhash + phash);
     std::string secret = uhash_str + phash_str;

     EncryptEngine headerEncrypter(uhash_str + phash_str, seed, secret);
     FurkanMangler mangler(headerEncrypter.getEncryptedText(), hash_str( (id + pass).c_str() ));
     return mangler.getMangledText();
 }

 void EncryptEngine::encrypt(){
     if ( seed.length() == 0 ){
         return;
     }
     std::string secretAndSeed = secret + seed;
     unsigned long long secret_hash = hash_str(secretAndSeed.c_str()) ;
     std::string encrypted;
     for(int i = 0; i < text.length() ; i++){
         //encrypted += (text.at(i) + (seed.at( i % seed.length() ) * secret_hash)) % 256;
         uint64_t shift_amount = seed.at( i % seed.length() ) * secret_hash ;
         char add = _getCeasarShiftedChar(text.at(i), shift_amount, true);
         encrypted += add;
         if ( encrypted[i] == '\0'){
             std::cout << "PANIC" << std::endl;
         }
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
     if (seed.length() == 0 ){
         return;
     }
     std::string secretAndSeed = secret + seed;
     unsigned long long secret_hash = hash_str(secretAndSeed.c_str()) ;
     std::string decrpyted;
     for(int i = 0; i < text.length() ; i++){
         uint64_t shift_amount = seed.at( i % seed.length() ) * secret_hash ;
         char add = _getCeasarShiftedChar(text.at(i), shift_amount, false);
         decrpyted += add;
     }
     dec_text = decrpyted;
 }

 std::string DecryptEngine::getDecryptedText(){
     if(dec_text == "NULL"){
        this->decrypt();
     }
     return dec_text;
 }
 

