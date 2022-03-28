#include "../inc/application.hpp"

extern uint64_t hash_str(const char * s);

bool Application::_checkAuthentication_(){
    bool result = header_in_txt == header.getHeader(id, password);
    return result;
}

bool Application::_readText_(){
    fileHandler.setFilePath(filepath);
    std::string text_and_header;
    header_in_txt = "";

    if ( !fileHandler.getTextFromFile(text_and_header) ) return false; 
    
    if ( state == Decripting ){
        std::string hdr = header.getHeader(id, password);
        header_in_txt = text_and_header.substr(0, hdr.length() );
    }

    text = text_and_header.substr(header_in_txt.length());
    return true;
}

bool Application::_writeText_(const std::string& out){
    fileHandler.setFilePath(fileout);
    if ( state == Encrypting ) return fileHandler.writeTextToFile(header.getHeader(id, password) + out);
    return fileHandler.writeTextToFile(out);
}

bool Application::_handleReading(){
    std::cout << "Enter the file path : ";
    std::cin >> filepath;
    if( !_readText_() ){
        std::cout << "Couldn't open " << filepath << std::endl;
        return false;
    }
    if ( state == Decripting && !_checkAuthentication_()){
        std::cout << "You are not authorized to decrypt this file." << std::endl;
        return false;
    }
    return true;
}

bool Application::_handleWriting(const std::string& out){
    if( !_writeText_(out) ){
        std::cout << "Couldn't open " << fileout << std::endl;
        return false;
    }
    std::cout << filepath << " is " << (state == Encrypting ? "encypted" : "decrypted" ) << " and written to \'" << fileout << "\'" << std::endl;
    return true;
}

void Application::_handleMangling(std::string& text){
    if ( !mangling ) return;
    FurkanMangler mangler(text, hash_str((password + id).c_str()));
    text = mangler.getMangledText();
}

void Application::_handleUnmangling(std::string& text){
    if ( !mangling ) return;
    FurkanMangler mangler(text, hash_str((password + id).c_str()));
    text = mangler.getUnmangledText();
}

void Application::_getCretentials(){
    std::cout << "Enter the id of encrypter: ";
    std::cin >> id;
    std::cout << "Enter the encryption password : ";
    std::cin >> password;
}

void Application::_getOutputPath(){
    std::cout << "Enter the output file path (to leave it as default enter '.' ): ";
    std::cin >> fileout;
    if (fileout == "."){
        if ( state == Encrypting){
            fileout = filepath.substr(0, filepath.find_last_of('.')) + ".enc";
        }
        else if(filepath.find(".enc")){
            fileout = filepath.substr(0, filepath.find_last_of('.')) + "_dec" + ".txt";
        }
    }
}

int Application::_getLayerNumber(){
    std::string number;
    int num = 0;
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
        seeds.push_back(seed);
        EncryptEngine e_engine(str, seed, password + id);
        str = e_engine.getEncryptedText();
    }
}

void Application::_Decrypt(std::string& str, int num){
    for(int i = 0; i < num ; i++){
        std::cout << "Enter a seed : ";
        std::string seed;
        std::cin >> seed;
        DecryptEngine d_engine(str, seed, password + id);
        str = d_engine.getDecryptedText();
    }
}

void Application::_checkForDataLoss(){
    std::string check;
    std::string fileholder = filepath;
    filepath = fileout;
    std::string textholder = text;
    state = Decripting;
    if ( _readText_() ){
        check = text;
        _handleUnmangling(check);
        for (std::string seed : seeds)
        {
            DecryptEngine de(check, seed, password + id);
            check = de.getDecryptedText();
        }
    }
    state = Encrypting;
    text = textholder;
    filepath = fileholder;
    int dataloss = FileHandler::printOnlyDifferences(check, text);
    if ( dataloss ){
        std::cout << dataloss << " bytes lost." << std::endl;
        std::cout << "There was an error while encrypting! Please notify the dev team about this issue." << std::endl;
    }
}


void Application::handleEncryption(){
    if ( ! _handleReading() ) return;
    std::string encrypted = text;
    _getCretentials();
    _getOutputPath();
    _Encrypt(encrypted, _getLayerNumber());
    _checkForDataLoss();
    _handleMangling(encrypted);
    _handleWriting(encrypted);
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
        state = Decripting;
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
    filepath = "";
    fileout = "";
    id = "";
    password = "";
    text = "";
    header_in_txt = "";
    fileHandler = FileHandler();
    seeds.clear();
    mangling = true;
}

void Application::Run(){
    printWelcomeMessage();

    while (handleCommand());

    printExitMessage();

    reset();
}

void Application::printWelcomeMessage(){}
void Application::printExitMessage(){}