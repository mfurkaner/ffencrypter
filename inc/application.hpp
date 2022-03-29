#include "encryptengine.hpp"
#include "filehandler.hpp"
#include "mangler.hpp"
#include "configuration.hpp"

#ifndef APPLICATION
#define APPLICATION
enum State{
    Reading, Encrypting, Decrypting
};

class Application{
    ApplicationConfiguration _configuration;
    State state;
    FileHandler fileHandler;
    EncryptedHeader header;
    std::string text;
    std::string header_in_txt;

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
    Application(const std::string& config_path) : _configuration(config_path){}
    Application(const ApplicationConfiguration& configuration) : _configuration(configuration){}
    
    void Run();

};

#endif