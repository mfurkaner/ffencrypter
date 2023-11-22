#include <string>
#include <vector>
#include "filehandler.hpp"

#ifndef CONFIGURATION
#define CONFIGURATION

class Configuration{
protected:
    std::vector<std::string> lines;
    bool _config_from_file;
    std::string _config_path;
    FileHandler _fileHandler;
    virtual bool _getConfig() = 0;
public:
    Configuration() : _config_from_file(false){  }

    Configuration(const std::string& config_path) :_config_from_file(true), _config_path(config_path) {
        _fileHandler.setFilePath(config_path); 
    }
};

class RunConfiguration : public Configuration{
    std::string _command;
    std::string _filepath;
    std::string _fileout = ".";
    std::string _id;
    std::string _password;
    std::vector<std::string> _seeds;
    bool _mangling = true;
    bool _check_for_data_loss = false;
    bool _binfile = true;
    int _depth = 10;

    bool _getConfig();

public:
    RunConfiguration(){ }
    RunConfiguration(const std::string& config_path) : Configuration(config_path) {_getConfig();}

    const std::string nullstr = "NULL";

//GETS
    const std::string& getCommand() const { return _command; }
    const std::string& getFilePath() const { return _filepath; }
    const std::string& getFileOut() const{ return _fileout; }
    const std::string& getID() const { return _id; }
    const std::string& getPassword() const { return _password; }
    const int getDepth() const { return _depth; }
    const std::vector<std::string>& getSeeds() const { return _seeds; }
    const std::string& getSeed(uint32_t index) { 
        if (_seeds.size() > index) return _seeds[index];
        return nullstr;  
    }
    bool isBinaryFile() const {return _binfile;}
    bool isManglingEnabled() const { return _mangling; }
    bool isDataLossCheckEnabled() const { return _check_for_data_loss; }
    bool isConfigFromFile() const { return _config_from_file; }
//SETS
    void setFilePath(const std::string& filepath){_filepath = filepath;}
    void setFileOut(const std::string& fileout){_fileout = fileout;}
    void setID(const std::string& id){_id= id;}
    void setPassword(const std::string& password){_password = password;}
    void enableMangling(){_mangling = true;}
    void disableMangling(){ _mangling = false;}
    void enableDataLossCheck(){_check_for_data_loss = true;}
    void disableDataLossCheck(){_check_for_data_loss = false;}
    void addSeed(const std::string& seed){_seeds.push_back(seed);}
    void popSeed(){_seeds.pop_back();}
    void clearSeeds(){_seeds.clear();}
    void reverseFilePaths(){std::string fileholder = _filepath; _filepath = _fileout; _fileout = fileholder;}


    void clear();
    bool isEmpty();

};

enum ConfigurationIndex{
    filepath_, fileout_, id_, pass_, seed_,
    mangling_, datalosscheck_, command_,
    binfile_, depth_,

    endofconfig
};

#endif