#include <iostream>


#ifndef ENCRYPT_ENGINE
#define ENCRYPT_ENGINE
#include "mangler.hpp"


class EncryptedHeader{
    std::string username;
    std::string password;
public:
    EncryptedHeader(){}
    EncryptedHeader(std::string username, std::string password) : username(username) , password(password){};
    void setUsername(const std::string& username) { this->username = username;}
    void setPassword(const std::string& password) { this->password = password;}
    std::string getHeader(const std::string& id, const std::string& pass);
    std::vector<uint8_t> getHeaderBin(const std::string& id, const std::string& pass);
};


class BaseEngine{
protected:
    std::string seed;
    std::string secret;

    BaseEngine(std::string seed, std::string secret) :seed(seed),secret(secret) {}

    uint8_t _getCeasarShiftedChar(uint8_t c, const uint64_t& shift_amount, bool to_right);
    uint8_t _getCeasarShiftedCharAvoidNonChar(uint8_t c, const uint64_t& shift_amount, bool to_right);
    
    public:
    void reset(){ secret = ""; seed = ""; };
    void setSeed(std::string seed) {this->seed = seed;}
    void setSecret(std::string secret) {this->secret = secret;}
};

class BaseTextEngine: public BaseEngine{
    protected:
    std::string text;

    public:
    BaseTextEngine(std::string text, std::string seed, std::string secret) : text(text), BaseEngine(seed, secret){}
    void setText(std::string text) {this->text = text;}
    void reset(){ text = ""; BaseEngine::reset(); };
};

class BaseBinaryEngine: public BaseEngine{
    protected:
    std::vector<uint8_t> bin;

    public:
    BaseBinaryEngine(std::vector<uint8_t>& bin, std::string seed, std::string secret) : bin(bin), BaseEngine(seed, secret){}
    void setBin(std::vector<uint8_t> bin){this->bin = bin;}
    void reset(){ bin.clear(); BaseEngine::reset(); };
};


class EncryptEngine : public BaseTextEngine{
    
    std::string enc_text = "NULL";

    public:
    EncryptEngine(std::string text, std::string seed, std::string secret) : BaseTextEngine(text, seed, secret){}
    void encrypt();
    void reset(){ enc_text = "NULL"; BaseTextEngine::reset();}
    std::string getEncryptedText();
};

class DecryptEngine : public BaseTextEngine{
    std::string dec_text = "NULL";

    public:
    DecryptEngine(std::string text, std::string seed, std::string secret) : BaseTextEngine(text, seed, secret) {}
    void decrypt();
    void reset(){ dec_text = "NULL"; BaseTextEngine::reset();}
    std::string getDecryptedText();
};


class BinaryEncryptEngine : public BaseBinaryEngine{
    std::vector<uint8_t> enc_bin;

    public:
    BinaryEncryptEngine(std::vector<uint8_t>& bin, std::string seed, std::string secret) : BaseBinaryEngine(bin, seed, secret){}
    void encrypt();
    void reset(){ enc_bin.clear(); BaseBinaryEngine::reset();}
    std::vector<uint8_t> getEncryptedBinaries();
};

class BinaryDecryptEngine : public BaseBinaryEngine{
    std::vector<uint8_t> dec_bin;

    public:
    BinaryDecryptEngine(std::vector<uint8_t>& bin, std::string seed, std::string secret) : BaseBinaryEngine(bin, seed, secret){}
    void decrypt();
    void reset(){ dec_bin.clear(); BaseBinaryEngine::reset();}
    std::vector<uint8_t> getDecryptedBinaries();
};

#endif