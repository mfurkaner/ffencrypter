#include <iostream>
#include <sstream>
#include <fstream>
#include "../inc/filehandler.hpp"

bool FileHandler::getTextFromFile(std::string& text){
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

bool FileHandler::getBinFromFile(std::vector<uint8_t>& bin){
    std::ifstream fin;
    fin.open(filepath, std::ios::in | std::ios::binary);
    if(fin.fail()) return false;
    bin = std::vector<uint8_t>(std::istreambuf_iterator<char>(fin), {});
    fin.close();
    return true;
}

bool FileHandler::writeTextToFile(const std::string& text){
    std::ofstream fout;
    fout.open(filepath, std::ios::out | std::ios::binary);
    if(fout.fail()) return false;
    fout << text;
    fout.close();
    return true;
} 

bool FileHandler::writeBinToFile(const std::vector<uint8_t>& bin){
    std::ofstream fout;
    fout.open(filepath, std::ios::out | std::ios::binary);
    if(fout.fail()) return false;

    uint8_t* bins =  new uint8_t[bin.size()];
    for(int i = 0 ; i < bin.size(); i++){
        bins[i] = bin[i];
    }
    fout.write((const char*)bins, bin.size());
    fout.close();
    delete [] bins;
    return true;
}

uint32_t FileHandler::printOnlyDifferences(const std::string& t1, const std::string& t2){
    uint32_t count = 0;
    for(uint32_t i = 0; i < t1.size() && i < t2.size() ; i++){
        if( t1.at(i) != t2.at(i) ){
            std::cout << "They differ at " << i << " : t1=" << t1.at(i) << " t2=" << t2.at(i) << std::endl; 
            count++;
        }
    }
    return count;
}

uint32_t FileHandler::printOnlyDifferences(const std::vector<uint8_t>& t1, const std::vector<uint8_t>& t2){
    uint32_t count = 0;
    for(uint32_t i = 0; i < t1.size() && i < t2.size() ; i++){
        if( t1.at(i) != t2.at(i) ){
            std::cout << "They differ at " << i << " : t1=" << static_cast<char>(t1.at(i)) << " t2=" <<static_cast<char>(t2.at(i)) << std::endl; 
            count++;
        }
    }
    return count;
}

void FileHandler::printDifferences(const std::string& t1, const std::string& t2){
    uint32_t count = printOnlyDifferences(t1, t2);
    std::cout << "Size of t1 : " << t1.size() << "  size of t2 : " << t2.size() << std::endl;
    std::cout << "Total diff : " << count << std::endl;
}

void FileHandler::printDifferencesOfFiles(const std::string& f1, const std::string& f2){
    FileHandler fh1, fh2;
    std::string s1, s2;
    fh1.setFilePath(f1);
    fh1.getTextFromFile(s1);
    fh2.setFilePath(f2);
    fh2.getTextFromFile(s2);
    printDifferences(s1, s2);
}
