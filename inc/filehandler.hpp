

#ifndef FILE_HANDLER
#define FILE_HANDLER


class FileHandler{
    std::string filepath;
public:

    void setFilePath(const std::string& path){ filepath = path;}

    bool getTextFromFile(std::string& text);
    bool writeTextToFile(const std::string& text);

    static uint32_t printOnlyDifferences(const std::string& t1, const std::string& t2);
    static void printDifferences(const std::string& t1, const std::string& t2);
    static void printDifferencesOfFiles(const std::string& f1, const std::string& f2);

};

#endif