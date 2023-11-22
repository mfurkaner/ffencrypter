#include <climits>
#include <string>
#include "../inc/encryptengine.hpp"
#include "../inc/ascii_avoid_list.hpp"

 unsigned long long hash_str(const char* s);

 std::string uint64_to_str(uint64_t num){
     return std::to_string(num);
 }

 uint8_t BaseEngine::_getCeasarShiftedCharAvoidNonChar(uint8_t c, const uint64_t& shift_amount, bool to_right){
     uint8_t actual_shift = shift_amount % (UCHAR_MAX + 1 - AVOID_LIST_SIZE);
     if(actual_shift == 0) return c;
     return ( to_right ) ? jump_avoid_elements_right(c, actual_shift) : jump_avoid_elements_left(c, actual_shift) ;
 } 

uint8_t BaseEngine::_getCeasarShiftedChar(uint8_t c, const uint64_t& shift_amount, bool to_right){
    uint8_t actual_shift = shift_amount % (UCHAR_MAX + 1);
    if(actual_shift == 0) return c;

    return (to_right) ? c + actual_shift : c - actual_shift;
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

  std::vector<uint8_t>  EncryptedHeader::getHeaderBin(const std::string& id, const std::string& pass){
     uint64_t uhash = hash_str(id.c_str());
     uint64_t phash = hash_str(pass.c_str());

     std::string uhash_str = uint64_to_str( uhash );
     std::string phash_str = uint64_to_str( phash );

     std::string seed = uint64_to_str(uhash + phash);
     std::string secret = uhash_str + phash_str;

     EncryptEngine headerEncrypter(uhash_str + phash_str, seed, secret);
     FurkanMangler mangler(headerEncrypter.getEncryptedText(), hash_str( (id + pass).c_str() ));

     std::vector<uint8_t> header_bin;
     auto header = mangler.getMangledText();

     for(int i = 0; i < header.size() ; i++){
        header_bin.push_back(header[i]);
     }

     return header_bin;
 }

 void EncryptEngine::encrypt(){
     if ( seed.length() == 0 || text.length() == 0 ){
         return;
     }
     std::string secretAndSeed = secret + seed;
     uint64_t secret_hash = hash_str(secretAndSeed.c_str()) ;
     std::string encrypted;
     for(uint32_t i = 0; i < text.length() ; i++){
         uint64_t shift_amount = seed.at( i % seed.length() ) * secret_hash ;
         encrypted += _getCeasarShiftedCharAvoidNonChar(text.at(i), shift_amount, true);
         if ( encrypted[i] == '\0'){
             std::cerr << "PANIC" << std::endl;
         }
     }
     enc_text = encrypted;
 }

 void BinaryEncryptEngine::encrypt(){
    if ( seed.length() == 0 || bin.size() == 0 ){
        return;
    }
    std::string secretAndSeed = secret + seed;
    uint64_t secret_hash = hash_str(secretAndSeed.c_str()) ;
    std::vector<uint8_t> encrypted;

    for(uint32_t i = 0; i < bin.size() ; i++){
        uint64_t shift_amount = seed.at( i % seed.length() ) * secret_hash ;
        encrypted.push_back( _getCeasarShiftedChar(bin.at(i), shift_amount, true));
        /*
        if ( encrypted[i] == '\0'){
            std::cerr << "PANIC" << std::endl;
        }*/
    }

    enc_bin = encrypted;
}


 std::string EncryptEngine::getEncryptedText(){
     if(enc_text == "NULL"){
        this->encrypt();
     }
     return enc_text;
 }

std::vector<uint8_t> BinaryEncryptEngine::getEncryptedBinaries(){
    if(enc_bin.empty()){
        this->encrypt();
    }
    return enc_bin;
}

 void DecryptEngine::decrypt(){
     if (seed.length() == 0 || text.length() == 0){
         return;
     }
     std::string secretAndSeed = secret + seed;
     uint64_t secret_hash = hash_str(secretAndSeed.c_str()) ;
     std::string decrpyted;
     for(uint32_t i = 0; i < text.length() ; i++){
         uint64_t shift_amount = seed.at( i % seed.length() ) * secret_hash ;
         decrpyted += _getCeasarShiftedCharAvoidNonChar(text.at(i), shift_amount, false);
     }
     dec_text = decrpyted;
 }

  void BinaryDecryptEngine::decrypt(){
    if ( seed.length() == 0 || bin.size() == 0 ){
        return;
    }
    std::string secretAndSeed = secret + seed;
    uint64_t secret_hash = hash_str(secretAndSeed.c_str()) ;
    std::vector<uint8_t> decrypted;

    for(uint32_t i = 0; i < bin.size() ; i++){
        uint64_t shift_amount = seed.at( i % seed.length() ) * secret_hash ;
        decrypted.push_back(_getCeasarShiftedChar(bin.at(i), shift_amount, false));
    }

    dec_bin = decrypted;
 }

 std::string DecryptEngine::getDecryptedText(){
     if(dec_text == "NULL"){
        this->decrypt();
     }
     return dec_text;
 } 

 std::vector<uint8_t> BinaryDecryptEngine::getDecryptedBinaries(){
    if(dec_bin.empty()){
        this->decrypt();
    }
    return dec_bin;
}