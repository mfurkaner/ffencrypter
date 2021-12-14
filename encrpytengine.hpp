#include <iostream>


class EncryptEngine{
    std::string secret;
    std::string seed;
    std::string text;
    std::string enc_text = "NULL";

    public:
    EncryptEngine(std::string text, std::string seed, std::string secret) : text(text),seed(seed),secret(secret) {}

    void setSeed(std::string seed) {this->seed = seed;}
    void setText(std::string text) {this->text = text;}
    void setSecret(std::string secret) {this->secret = secret;}

    void encrypt();

    std::string getEncryptedText();
};

class DecryptEngine{
    std::string secret;
    std::string seed;
    std::string text;
    std::string dec_text = "NULL";

    public:
    DecryptEngine(std::string text, std::string seed, std::string secret) : text(text),seed(seed),secret(secret) {}

    void setSeed(std::string seed) {this->seed = seed;}
    void setText(std::string text) {this->text = text;}
    void setSecret(std::string secret) {this->secret = secret;}

    void decrypt();

    std::string getDecryptedText();
};