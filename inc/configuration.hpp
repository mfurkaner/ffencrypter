#include <string>
#include <vector>
#include "filehandler.hpp"

#ifndef CONFIGURATION
#define CONFIGURATION

class Configuration{
protected:
    std::string _config_path;
    FileHandler _fileHandler;
    virtual bool _getConfig() = 0;
public:
    Configuration(){}
    Configuration(const std::string& config_path) : _config_path(config_path){_fileHandler.setFilePath(config_path);}
};


class ApplicationConfiguration : public Configuration{
    std::string _filepath;
    std::string _fileout;
    std::string _id, _password;
    std::vector<std::string> _seeds;
    bool _mangling = true;
    bool _check_for_data_loss = false;

    bool _getConfig();

public:
    ApplicationConfiguration(const ApplicationConfiguration& config){_check_for_data_loss = config._check_for_data_loss;}
    ApplicationConfiguration(const std::string& config_path) : Configuration(config_path) {_getConfig();}

//GETS
    const std::string& getFilePath(){return _filepath;}
    const std::string& getFileOut(){return _fileout;}
    const std::string& getID(){return _id;}
    const std::string& getPassword(){return _password;}
    const std::vector<std::string>& getSeeds(){return _seeds;}
    bool isManglingEnabled(){return _mangling;}
    bool isDataLossCheckEnabled(){return _check_for_data_loss;}
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

};

enum ConfigurationIndex{
    filepath_, fileout_, id_, pass_, seed_,
    mangling_, datalosscheck_,

    endofconfig
};

#endif