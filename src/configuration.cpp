#include "../inc/configuration.hpp"

const char* AVAILABLE_CONFIGURATIONS[endofconfig] = {
    "filepath", "fileout", 
    "id", "pass", "setseed", 
    "mangling", "check"
};

bool ApplicationConfiguration::_getConfig(){
    std::string config_txt;
    _fileHandler.setFilePath(_config_path);
    if ( !_fileHandler.getTextFromFile(config_txt) ) return false;

    std::vector<std::string> commands;

    while ( config_txt.length() ){
        uint32_t line_start_index = config_txt.find_last_of('\n');
        std::string line = config_txt.substr(line_start_index);
        if ( line.length() && line.find('#') == std::string::npos ){
            commands.push_back( line );
        }
        for(uint32_t i = 0; i < line.length() ; i++){
            config_txt.pop_back();
        }
    }
    commands.reserve(commands.size());
    for(std::string command : commands){
        uint32_t config_index = 0;
        for ( ; config_index < endofconfig ; config_index++ ){
            if ( command.find( AVAILABLE_CONFIGURATIONS[config_index] ) != std::string::npos ){
                break;
            }
        }
        switch (config_index)
        {
        case filepath_:
            _filepath = command.substr(command.find_first_of('=') + 1);
            while ( _filepath.find(' ') != std::string::npos ){
                _filepath.erase(_filepath.find(' '));
            }
            break;
        case fileout_:
            _fileout = command.substr(command.find_first_of('=') + 1);
            while ( _fileout.find(' ') != std::string::npos ){
                _fileout.erase(_fileout.find(' '));
            }
            break;  
        case id_: 
            _id = command.substr(command.find_first_of('=') + 1);
            while ( _id.find(' ') != std::string::npos ){
                _id.erase(_id.find(' '));
            }
            break;
        case pass_:
            _password = command.substr(command.find_first_of('=') + 1);
            while ( _password.find(' ') != std::string::npos ){
                _password.erase(_password.find(' '));
            }
            break;
        case seed_:
            if ( command.find('\'') != std::string::npos && command.find_first_of('\'') != command.find_last_of('\'') ){
                _seeds.push_back(command.substr(command.find_first_of('\'') + 1, command.find_last_of('\'') - command.find_first_of('\'') - 1 ));
            }
            break;
        case mangling_:
            _mangling = atoi(command.substr(command.find('=') + 1).c_str());
            break;
        case datalosscheck_:
            _check_for_data_loss = atoi(command.substr(command.find('=') + 1).c_str());
            break;
        default:
            break;
        }
    }

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