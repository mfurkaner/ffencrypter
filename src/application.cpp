#include "../inc/application.hpp"

extern uint64_t hash_str(const char * s);

bool Application::_checkAuthentication_(){
    bool result = header_in_txt == header.getHeader(_configuration.getID(), _configuration.getPassword());
    return result;
}

bool Application::_readText_(){
    fileHandler.setFilePath(_configuration.getFilePath());
    std::string text_and_header;
    header_in_txt = "";

    if ( !fileHandler.getTextFromFile(text_and_header) ) return false; 
    
    if ( state == Decrypting ){
        std::string hdr = header.getHeader(_configuration.getID(), _configuration.getPassword());
        header_in_txt = text_and_header.substr(0, hdr.length() );
    }

    text = text_and_header.substr(header_in_txt.length());
    return true;
}

bool Application::_writeText_(const std::string& out){
    fileHandler.setFilePath(_configuration.getFileOut());
    if ( state == Encrypting ) return fileHandler.writeTextToFile(header.getHeader(_configuration.getID(), _configuration.getPassword()) + out);
    return fileHandler.writeTextToFile(out);
}

bool Application::_handleReading(){
    std::string filepath;
    std::cout << "Enter the file path : ";
    std::cin >> filepath;
    _configuration.setFilePath(filepath);
    if( !_readText_() ){
        std::cout << "Couldn't open " << filepath << std::endl;
        return false;
    }
    if ( state == Decrypting && !_checkAuthentication_()){
        std::cout << "You are not authorized to decrypt this file." << std::endl;
        return false;
    }
    return true;
}

bool Application::_handleWriting(const std::string& out){

    if( !_configuration.isDataLossCheckEnabled() && !_writeText_(out) ){
        std::cout << "Couldn't open " << _configuration.getFileOut() << std::endl;
        return false;
    }
    std::cout << _configuration.getFilePath() << " is " << (state == Encrypting ? "encypted" : "decrypted" ) << " and written to \'" << _configuration.getFileOut() << "\'" << std::endl;
    return true;
}

void Application::_handleMangling(std::string& text_to_mangle){
    if ( !_configuration.isManglingEnabled() ) return;
    FurkanMangler mangler(text_to_mangle, hash_str((_configuration.getPassword() + _configuration.getID()).c_str()));
    text_to_mangle = mangler.getMangledText();
}

void Application::_handleUnmangling(std::string& text_to_unmangle){
    if ( !_configuration.isManglingEnabled()  ) return;
    FurkanMangler mangler(text_to_unmangle, hash_str((_configuration.getPassword() + _configuration.getID()).c_str()));
    text_to_unmangle = mangler.getUnmangledText();
}

void Application::_getCretentials(){
    std::string id, password;
    std::cout << "Enter the id of encrypter: ";
    std::cin >> id;
    std::cout << "Enter the encryption password : ";
    std::cin >> password;
    _configuration.setID(id);
    _configuration.setPassword(password);
}

void Application::_getOutputPath(){
    std::string fileout;
    std::cout << "Enter the output file path (to leave it as default enter '.' ): ";
    std::cin >> fileout;
    _configuration.setFileOut(fileout);
    if (fileout == "."){
        std::string filepath = _configuration.getFilePath();
        if ( state == Encrypting){
            _configuration.setFileOut( filepath.substr(0, filepath.find_last_of('.')) + ".enc" );
        }
        else if(filepath.find(".enc")){
            _configuration.setFileOut( filepath.substr(0, filepath.find_last_of('.')) + "_dec" + ".txt" );
        }
    }
}

int Application::_getLayerNumber(){
    std::string number;
    uint32_t num = 0;
    std::cout << "Layers of encryption : ";
    std::cin >> number;
    if(number != ""){
        num = atoi(number.c_str());
    }
    return num;
}

void Application::_Encrypt(std::string& str, int num){
    for(int i = 0; i < num ; i++){
        std::cout << "Enter a seed : ";
        std::string seed;
        std::cin >> seed;
        _configuration.addSeed(seed);
        EncryptEngine e_engine(str, seed, _configuration.getPassword() + _configuration.getID());
        str = e_engine.getEncryptedText();
    }
}

void Application::_Decrypt(std::string& str, int num){
    for(int i = 0; i < num ; i++){
        std::cout << "Enter a seed : ";
        std::string seed;
        std::cin >> seed;
        DecryptEngine d_engine(str, seed, _configuration.getPassword() + _configuration.getID());
        str = d_engine.getDecryptedText();
    }
}

bool Application::_checkForDataLoss(const std::string& out){

    if ( !_configuration.isDataLossCheckEnabled() ) return true;
    if ( !_writeText_(out) ) {std::cout << "Data loss check could not be initiated due to a write issue." << std::endl; return false;}
    _configuration.reverseFilePaths();
    std::string textholder = text;
    state = Decrypting;
    if ( _readText_() ){
        _handleUnmangling(text);
        for (std::string seed : _configuration.getSeeds())
        {
            DecryptEngine de(text, seed, _configuration.getPassword() + _configuration.getID());
            text = de.getDecryptedText();
        }
    }
    state = Encrypting;
    _configuration.reverseFilePaths();
    uint32_t dataloss = FileHandler::printOnlyDifferences(textholder, text);
    text = textholder;
    if ( dataloss ){
        std::cout << dataloss << " bytes lost." << std::endl;
        std::cout << "There was an error while encrypting! Please notify the dev team about this issue." << std::endl;
    }
    return !dataloss;
}


void Application::handleEncryption(){
    if ( ! _handleReading() ) return;
    std::string encrypted = text;
    _getCretentials();
    _getOutputPath();
    _Encrypt(encrypted, _getLayerNumber());
    _handleMangling(encrypted);
    bool nodataloss = _checkForDataLoss(encrypted);
    if (nodataloss) _handleWriting(encrypted);
}

void Application::handleDecryption(){
    _getCretentials();
    if ( ! _handleReading() ) return;
    std::string decrypted = text;
    _getOutputPath();
    _handleUnmangling(decrypted);
    _Decrypt(decrypted, _getLayerNumber());
    _handleWriting(decrypted);
}

bool Application::handleCommand(){
    std::string command ;
    
    std::cout << "Enter a command ( enc : encrypt, dec : decrypt, pdif : print diff, exit : exit) : ";
    std::cin >> command;

    if(command == "enc"){
        state = Encrypting;
        handleEncryption();
    }
    else if ( command == "dec" ){
        state = Decrypting;
        handleDecryption();
    }
    else if ( command == "pdif" ){
        std::string path1,path2;
        std::cout << "Path of the first file : ";
        std::cin >> path1;
        std::cout << "Path of the second file : ";
        std::cin >> path2;
        FileHandler::printDifferencesOfFiles(path1, path2);
    }
    else if ( command == "settings"){

    }
    else if( command == "exit" ){
        return false;
    }
    else{
        std::cout << "Wrong input." << std::endl;
    }

    return true;
}

void Application::reset(){
    _configuration.clear();
    text = "";
    header_in_txt = "";
    fileHandler = FileHandler();
}

void Application::Run(){
    printWelcomeMessage();

    while (handleCommand());

    printExitMessage();

    reset();
}

void Application::printWelcomeMessage(){}
void Application::printExitMessage(){}