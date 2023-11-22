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
    RunConfiguration _configuration;
    State state;
    FileHandler fileHandler;
    EncryptedHeader header;
    std::string command;

    std::string text;
    std::string out_text;
    
    std::vector<uint8_t> binary;
    std::vector<uint8_t> out_binary;

    std::string header_in_txt;
    std::vector<uint8_t> header_in_bin;

    bool _checkAuthentication_();

    bool _readText_();
    bool _writeText_(const std::string& out);
    bool _writeBinary_(const std::vector<uint8_t>& out_bin);

    bool _checkForDataLoss(const std::string& out);
    bool _checkForDataLoss(const std::vector<uint8_t>& out);

    void _handleMangling(std::string& text_to_mangle) const;
    void _handleMangling(std::vector<uint8_t>& bin) const;

    void _handleUnmangling(std::string& text_to_unmangle) const;
    void _handleUnmangling(std::vector<uint8_t>& bin) const;

    bool _handleReading();
    bool _handleWriting(const std::string& out);
    bool _handleWriting(const std::vector<uint8_t>& out_bin);

    const std::string& _getSeed(uint32_t index);
    void _getSeedFromUserUntil(uint32_t num);
    void _updateCommand();
    void _updateCretentials();
    void _updateOutputPath();
    uint32_t _getLayerNumber() const;

    void _Encrypt(std::string& str, uint32_t num);
    void _Encrypt(std::vector<uint8_t>& bin, uint32_t num);

    void _Decrypt(std::string& str, uint32_t num);
    void _Decrypt(std::vector<uint8_t>& bin, uint32_t num);

    void handleEncryption();
    void handleDecryption();
    bool handleCommand();

    void printWelcomeMessage();
    void printExitMessage();

    void printPrimeNumbers();

    void reset();
public:
    Application(const std::string& config_path) : _configuration(config_path){}
    Application(const RunConfiguration& configuration) : _configuration(configuration){}
    
    void Run();

};

#endif