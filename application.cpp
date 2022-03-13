#include "application.hpp"



bool Application::checkAuthentication(){
    bool result = header_in_txt == header.getHeader(id, password);
    return result;
}

bool Application::readText(){
    fileHandler.setFilePath(filepath);
    std::string text_and_header;
    if ( !fileHandler.getTextFromFile(text_and_header) ) return false; 
    if ( state == Decripting ){
        header_in_txt = text_and_header.substr(0, header.getHeader(id, password).length() );
    }
    text = text_and_header.substr(header_in_txt.length());
    return true;
}

bool Application::writeText(const std::string& out){
    fileHandler.setFilePath(fileout);
    if ( state == Encrypting ) return fileHandler.writeTextToFile(header.getHeader(id, password) + out);
    return fileHandler.writeTextToFile(out);
}

void Application::handleEncryption(){
    std::string number, seed;
    int num = 0;
    std::cout << "Enter the file path : ";
    std::cin >> filepath;
    if( !readText() ){
        std::cout << "Couldn't open " << filepath << std::endl;
    }
    else{
        std::cout << "Enter the id of encryptor: ";
        std::cin >> id;
        std::cout << "Enter the encryption password : ";
        std::cin >> password;
        std::cout << "Enter the output file path (to leave it as default enter '.' ): ";
        std::cin >> fileout;
        if (fileout == "."){
            fileout = filepath.substr(0, filepath.find_last_of('.')) + ".enc";
        }
        std::string encrypted = text;
        std::cout << "Layers of encryption : ";
        std::cin >> number;
        if(number != ""){
            num = atoi(number.c_str());
        }
        for(int i = 0; i < num ; i++){
            std::cout << "Enter a seed : ";
            std::cin >> seed;
            EncryptEngine e_engine(encrypted, seed, password + id);
            encrypted = e_engine.getEncryptedText();
        }
        if( encrypted.find('\0') != std::string::npos || encrypted.find(3) != std::string::npos ){
            std::cout << "Cannot ensure no data loss with these seeds!" << encrypted.find('\0') << "    " << encrypted.find(3) << std::endl;
        }
        if( !writeText(encrypted) ){
            std::cout << "Couldn't open " << fileout << std::endl;
        }
        else{
            std::cout << filepath << " is encypted and written to \'" << fileout << "\'" << std::endl;
        }
    }
}

void Application::handleDecryption(){
    std::string number, seed;
    int num = 0;

    std::cout << "Enter the file path : ";
    std::cin >> filepath;
    std::cout << "Enter the id of encryptor: ";
    std::cin >> id;
    std::cout << "Enter the encryption password : ";
    std::cin >> password;
    if( !readText() ){
        std::cout << "Couldn't open " << filepath << std::endl;
    }
    else if ( !checkAuthentication() ) {
        std::cout << "You are not authorized to decrypt this file." << std::endl;
    }
    else{
        std::cout << "Enter the output file path (to leave it as default enter '.' ): ";
        std::cin >> fileout;
        if (fileout == "."){
            if(filepath.find(".enc")){
                fileout = filepath.substr(0, filepath.find_last_of('.')) + "_dec" + ".txt";
            }
        }
        std::string decrypted = text;
        std::cout << "Layers of decryption : ";
        std::cin >> number;
        if(number != ""){
            num = atoi(number.c_str());
        }
        for(int i = 0; i < num ; i++){
            std::cout << "Enter a seed : ";
            std::cin >> seed;
            DecryptEngine d_engine(decrypted, seed, password + id);
            decrypted = d_engine.getDecryptedText();
        }
        if( !writeText(decrypted) ){
            std::cout << "Couldn't open " << fileout << std::endl;
        }
        else{
            std::cout << filepath << " is decrypted and written to \'" << fileout << "\'" << std::endl;
        }
    }

}

bool Application::handleCommand(){
    std::string command ;
    
    std::cout << "Enter a command ( enc : encrypt, dec : decrypt, exit : exit) : ";
    std::cin >> command;

    if(command == "enc"){
        state = Encrypting;
        handleEncryption();
    }
    else if ( command == "dec" ){
        state = Decripting;
        handleDecryption();
    }
    else if( command == "exit" ){
        return false;
    }
    else{
        std::cout << "Wrong input." << std::endl;
    }

    return true;
}

void Application::Run(){
    printWelcomeMessage();

    while (handleCommand());

    printExitMessage();
}

void Application::printWelcomeMessage(){}
void Application::printExitMessage(){}