

#ifndef FILE_HANDLER
#define FILE_HANDLER

#include <vector>


class FileHandler{
    std::string filepath;
public:

    void setFilePath(const std::string& path){ filepath = path;}

    bool getTextFromFile(std::string& text);
    bool getBinFromFile(std::vector<uint8_t>& bin);
    bool writeTextToFile(const std::string& text);
    bool writeBinToFile(const std::vector<uint8_t>& bin);

    static uint32_t printOnlyDifferences(const std::string& t1, const std::string& t2);
    static uint32_t printOnlyDifferences(const std::vector<uint8_t>& t1, const std::vector<uint8_t>& t2);

    static void printDifferences(const std::string& t1, const std::string& t2);
    static void printDifferencesOfFiles(const std::string& f1, const std::string& f2);

};

#endif