#include "../inc/configuration.hpp"


bool ApplicationConfiguration::_getConfig(){
    return true;
}

void ApplicationConfiguration::clear(){
    _config_path = "";
    _fileHandler = FileHandler();
    _filepath = "";
    _fileout = "";
    _id = "";
    _password = "";
    _seeds.clear();
    _mangling = true;
    _check_for_data_loss = false;
}