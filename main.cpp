#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include "encrpytengine.hpp"


#define USER_HASH 3028186019//3481592634            // default user-id hash
#define PASS_HASH 2495492740//260277150            // default password hash


#ifdef __APPLE__
#define ERASE_STR "\033[A\33[2K\033[A\33[2K"
#endif

#ifdef _WIN32
#define ERASE_STR ""
#endif

unsigned long long hash_str(const char* s);

bool checkUser(std::string id, std::string pass);
bool getTextFromFile(std::string filepath, std::string& text);
bool writeTextToFile(std::string filepath, const std::string text);
bool handleEncDec(std::string id, std::string pass);

int main(){
    std::string id, password, seed = "mountain", filepath, filepath_out, text, command;
    std::cout << "---Commands---" << std::endl;
    std::cout << "signin : Sign in to encrypt and decrypt a file" << std::endl;
    std::cout << "gethash : Get a hash of a word" << std::endl;
    std::cout << std::endl << "Enter a command : ";
    std::cin >> command;

    if( command == "signin" ){

        std::cout << "Enter your id : ";
        std::cin >> id;
        std::cout << "Enter your password : ";
        std::cin >> password;
        if (checkUser(id, password)) {
            std::cout << ERASE_STR << std::endl;
            while (handleEncDec(id, password));
        }
        else {
            std::cout << std::endl << "Id or password is wrong." << std::endl;
#ifdef _WIN32
            system("pause");
#endif
        }
    }
    else if( command == "gethash" ){
        std::cout << "To exit, enter 'exit' " << std::endl;
        while(text != "exit"){
            std::cout << "-> "; std::cin >> text;
            std::cout << "Hash of " << text << " = " << hash_str(text.c_str()) << std::endl;
        }
    }

    return 0;
}


bool checkUser(std::string id, std::string password) {
    if (USER_HASH == hash_str(id.c_str()) && PASS_HASH == hash_str(password.c_str())) {
        return true;
    }
    return false;
}

bool getTextFromFile(std::string filepath, std::string& text){
    std::ifstream fin;
    fin.open(filepath, std::ios::in);
    std::string line;
    if(fin.fail()) return false;
    while( !fin.eof() ){
        std::getline(fin, line);
        text += line + ( fin.eof() ? "" : "\n" );
    }
    fin.close();
    return true;
}

bool writeTextToFile(std::string filepath, const std::string text){
    std::ofstream fout;
    fout.open(filepath, std::ios::out);
    if(fout.fail()) return false;
    fout << text;
    fout.close();
    return true;
}

bool handleEncDec(std::string id, std::string password){
    std::string seed, filepath, filepath_out, text, command;
    

#ifdef __APPLE__
        system("clear");
#endif // 
#ifdef _WIN32
        system("cls");
#endif
        std::cout << "Welcome back " << id << std::endl << std::endl;

        std::cout << "Enter a command ( enc : encrypt, dec : decrypt, exit : exit) : ";
        std::cin >> command;
        

        if(command == "enc"){
            std::cout << "Enter the file path : ";
            std::cin >> filepath;
            if( !getTextFromFile(filepath, text) ){
                std::cout << "Couldn't open " << filepath << std::endl;
            }
            else{
                std::cout << "Enter the output file path (to leave it as default enter '.' ): ";
                std::cin >> filepath_out;
                if (filepath_out == "."){
                    filepath_out = filepath.substr(0, filepath.find_last_of('.')) + ".enc";
                }
                std::cout << "Enter a seed : ";
                std::cin >> seed;
                EncryptEngine e_engine(text, seed, password + id);
                std::string encrypted = e_engine.getEncryptedText();
                if( !writeTextToFile(filepath_out, encrypted) ){
                    std::cout << "Couldn't open " << filepath_out << std::endl;
                }
                else{
                    std::cout << filepath << " is encypted and written to \'" << filepath_out << "\'" << std::endl;
                }
            }
        }
        
        else if ( command == "dec" ){
            std::cout << "Enter the file path : ";
            std::cin >> filepath;
            if( !getTextFromFile(filepath, text) ){
                std::cout << "Couldn't open " << filepath << std::endl;
            }
            else{
                std::cout << "Enter the output file path (to leave it as default enter '.' ): ";
                std::cin >> filepath_out;
                if (filepath_out == "."){
                    if(filepath.find(".enc")){
                        filepath_out = filepath.substr(0, filepath.find_last_of('.')) + "_dec" + ".txt";
                    }
                }
                std::cout << "Enter a seed : ";
                std::cin >> seed;
                DecryptEngine d_engine(text, seed, password + id);
                std::string decrypted = d_engine.getDecryptedText();
                if( !writeTextToFile(filepath_out, decrypted) ){
                    std::cout << "Couldn't open " << filepath_out << std::endl;
                }
                else{
                    std::cout << filepath << " is decrypted and written to \'" << filepath_out << "\'" << std::endl;
                }
            }
        }
        else if( command == "exit" ){
            return false;
        }
        else{
            std::cout << "Wrong input." << std::endl;
        }
    
    
    return true;
}