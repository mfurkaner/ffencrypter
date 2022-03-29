#include "encryptengine.hpp"
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
    std::string header_in_txt;
    std::vector<std::string> seeds;
    bool mangling = true;
    bool check_for_data_loss = true;

    bool _checkAuthentication_();

    bool _readText_();
    bool _writeText_(const std::string& out);

    bool _checkForDataLoss(const std::string& out);

    void _handleMangling(std::string& text_to_mangle);
    void _handleUnmangling(std::string& text_to_unmangle);
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

    void reset();
public:
    void Run();

};

#endif