#include "encrpytengine.hpp"
#include "filehandler.hpp"

#ifndef APPLICATION
#define APPLICATION
enum State{
    Reading, Encrypting, Decripting
};

class Application{
    FileHandler fileHandler;
    EncryptedHeader header;
    std::string filepath;
    std::string fileout;
    std::string id, password;
    State state;
    std::string text;
    std::string header_in_txt;

    bool checkAuthentication();

    bool readText();
    bool writeText(const std::string& out);

    void handleEncryption();
    void handleDecryption();
    bool handleCommand();

    void printWelcomeMessage();
    void printExitMessage();
public:
    void Run();

};

#endif