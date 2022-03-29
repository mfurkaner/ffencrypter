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
        text = "";
        std::ifstream fin;
        fin.open(filepath, std::ios::in | std::ios::binary);
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
        fout.open(filepath, std::ios::out | std::ios::binary);
        if(fout.fail()) return false;
        fout << text;
        fout.close();
        return true;
    } 

    static int printOnlyDifferences(const std::string& t1, const std::string& t2){
        int count = 0;
        for(uint32_t i = 0; i < t1.size() && i < t2.size() ; i++){
            if( t1.at(i) != t2.at(i) ){
                std::cout << "They differ at " << i << " : t1=" << t1.at(i) << " t2=" << t2.at(i) << std::endl; 
                count++;
            }
        }
        return count;
    }
    
    static void printDifferences(const std::string& t1, const std::string& t2){
        int count = printOnlyDifferences(t1, t2);
        std::cout << "Size of t1 : " << t1.size() << "  size of t2 : " << t2.size() << std::endl;
        std::cout << "Total diff : " << count << std::endl;
    }

    static void printDifferencesOfFiles(const std::string& f1, const std::string& f2){
        FileHandler fh1, fh2;
        std::string s1, s2;
        fh1.setFilePath(f1);
        fh1.getTextFromFile(s1);
        fh2.setFilePath(f2);
        fh2.getTextFromFile(s2);
        printDifferences(s1, s2);
    }

};

#endif