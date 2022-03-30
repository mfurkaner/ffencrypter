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
    std::string command;
    std::string text;
    std::string header_in_txt;

    bool _checkAuthentication_();

    bool _readText_();
    bool _writeText_(const std::string& out);

    bool _checkForDataLoss(const std::string& out);

    void _handleMangling(std::string& text_to_mangle) const;
    void _handleUnmangling(std::string& text_to_unmangle) const;
    bool _handleReading();
    bool _handleWriting(const std::string& out);

    const std::string& _getSeed(uint32_t index);
    void _updateCommand();
    void _updateCretentials();
    void _updateOutputPath();
    uint32_t _getLayerNumber() const;
    void _Encrypt(std::string& str, uint32_t num);
    void _Decrypt(std::string& str, uint32_t num);

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