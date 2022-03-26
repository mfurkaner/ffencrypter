#include "encrpytengine.hpp"
#include "filehandler.hpp"
#include "mangler.hpp"

#ifndef APPLICATION
#define APPLICATION
enum State{
    Reading, Encrypting, Decripting
};

class Application{
    State state;
    FileHandler fileHandler;
    EncryptedHeader header;
    std::string filepath;
    std::string fileout;
    std::string id, password;
    std::string text;
    std::vector<std::string> seeds;
    std::string header_in_txt;
    bool mangling = true;

    bool _checkAuthentication_();

    bool _readText_();
    bool _writeText_(const std::string& out);

    void _checkForDataLoss();

    void _handleMangling(std::string& text);
    void _handleUnmangling(std::string& text);
    bool _handleReading();
    bool _handleWriting(const std::string& out);

    void _getCretentials();
    void _getOutputPath();
    int _getLayerNumber();
    void _Encrypt(std::string& str, int num);
    void _Decrypt(std::string& str, int num);

    void handleEncryption();
    void handleDecryption();
    bool handleCommand();

    void printWelcomeMessage();
    void printExitMessage();
public:
    void Run();

};

#endif