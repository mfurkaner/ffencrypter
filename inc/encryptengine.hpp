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
};


class BaseEngine{
protected:
    std::string text;
    std::string seed;
    std::string secret;

    BaseEngine(std::string text, std::string seed, std::string secret) : text(text),seed(seed),secret(secret) {}

    uint8_t _getCeasarShiftedChar(uint8_t c, const uint64_t& shift_amount, bool to_right);
    public:
    void reset(){ secret = ""; seed = ""; text = "";};
    void setSeed(std::string seed) {this->seed = seed;}
    void setText(std::string text) {this->text = text;}
    void setSecret(std::string secret) {this->secret = secret;}
};


class EncryptEngine : public BaseEngine{
    
    std::string enc_text = "NULL";

    public:
    EncryptEngine(std::string text, std::string seed, std::string secret) : BaseEngine(text, seed, secret){}
    void encrypt();
    void reset(){ enc_text = "NULL"; BaseEngine::reset();}
    std::string getEncryptedText();
};

class DecryptEngine : public BaseEngine{
    std::string dec_text = "NULL";

    public:
    DecryptEngine(std::string text, std::string seed, std::string secret) : BaseEngine(text, seed, secret) {}
    void decrypt();
    void reset(){ dec_text = "NULL"; BaseEngine::reset();}
    std::string getDecryptedText();
};

#endif