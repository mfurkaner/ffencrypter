#include <iostream>
#include <sstream>
#include <fstream>

#ifndef FILE_HANDLER
#define FILE_HANDLER


class FileHandler{
    std::string filepath;

public:

    void setFilePath(const std::string& path){ filepath = path;}

    bool getTextFromFile(std::string& text){
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
    bool writeTextToFile(const std::string& text){
        std::ofstream fout;
        fout.open(filepath, std::ios::out);
        if(fout.fail()) return false;
        fout << text;
        fout.close();
        return true;
    }

};

#endif