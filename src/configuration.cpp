#include "../inc/configuration.hpp"
#include <iostream>
#include <algorithm>

const char* const AVAILABLE_CONFIGURATIONS[endofconfig] = {
    "filepath", "fileout", 
    "id", "pass", "seedfile", "addseed", 
    "mangling", "check", "command",
    "binfile", "depth"
};

const char* const AVAILABLE_TR_CONFIGURATIONS[endofconfig] = {
    "konum", "kayit", 
    "id", "sifre", "tohumdosyasi", "tohumekle", 
    "calkala", "kontrol", "komut",
    "bindosyasi"
};

bool RunConfiguration::_getConfig(){
    std::string config_txt;
    _fileHandler.setFilePath(_config_path);

    if ( !_fileHandler.getTextFromFile(config_txt) ){
        std::cerr << "Config file not found at " << _config_path <<  std::endl;
        return false;
    } 

    while ( config_txt.length() ){
        uint64_t line_start_index = ( config_txt.find_last_of('\n') < config_txt.find_last_of('\r') ) ? config_txt.find_last_of('\n') : config_txt.find_last_of('\r');
        std::string line = config_txt.substr(line_start_index == std::string::npos ? 0 : line_start_index );
        if ( line.length() && line.find('#') == std::string::npos ){
            lines.push_back( line );
        }
        for(uint32_t i = 0; i < line.length() ; i++){
            config_txt.pop_back();
        }
    }

    while( !lines.empty() )
    {
        uint32_t i = lines.size() - 1;
        uint32_t config_index = 0;
        const std::string command = lines[i];
        for ( ; config_index < endofconfig ; config_index++ ){
            if ( command.find( AVAILABLE_CONFIGURATIONS[config_index] ) != std::string::npos ){
                break;
            }
        }
        switch (config_index)
        {
        case filepath_:
            /*
            _filepath = command.substr(command.find_first_of('=') + 1);
            while ( _filepath.find(' ') != std::string::npos ){
                _filepath.erase(_filepath.find(' '),  1);
            }*/
            if ( command.find('\'') != std::string::npos && command.find_first_of('\'') != command.find_last_of('\'') ){
                _filepath = command.substr(command.find_first_of('\'') + 1, command.find_last_of('\'') - command.find_first_of('\'') - 1 );
            }
            break;
        case fileout_:
            /*_fileout = command.substr(command.find_first_of('=') + 1);
            while ( _fileout.find(' ') != std::string::npos ){
                _fileout.erase(_fileout.find(' '), 1);
            }*/
            if ( command.find('\'') != std::string::npos && command.find_first_of('\'') != command.find_last_of('\'') ){
                _fileout = command.substr(command.find_first_of('\'') + 1, command.find_last_of('\'') - command.find_first_of('\'') - 1 );
            }
            break;  
        case id_: 
            _id = command.substr(command.find_first_of('=') + 1);
            while ( _id.find(' ') != std::string::npos ){
                _id.erase(_id.find(' '), 1);
            }
            break;
        case pass_:
            _password = command.substr(command.find_first_of('=') + 1);
            while ( _password.find(' ') != std::string::npos ){
                _password.erase(_password.find(' '), 1);
            }
            break;
        case seedfile_:
            /*
            _seedfile = command.substr(command.find_first_of('=') + 1);
            while ( _seedfile.find(' ') != std::string::npos ){
                _seedfile.erase(_seedfile.find(' '), 1);
            }
            _use_seed_file = true;
            */
            if ( command.find('\'') != std::string::npos && command.find_first_of('\'') != command.find_last_of('\'') ){
                _seedfile = command.substr(command.find_first_of('\'') + 1, command.find_last_of('\'') - command.find_first_of('\'') - 1 );
                _use_seed_file = true;
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
        case command_:
            _command = command.substr(command.find_first_of('=') + 1);
            while (_command.find(' ') != std::string::npos) {
                _command.erase(_command.find(' '), 1);
            }
            break;
        case binfile_:
            _binfile = atoi(command.substr(command.find('=') + 1).c_str());
            break;
        case depth_:
            _depth = atoi(command.substr(command.find('=') + 1).c_str());
            break;
        default:
            break;
        }
        lines.pop_back();
    }

    return true;
}

void RunConfiguration::clear(){
    _config_path = "";
    _fileHandler = FileHandler();
    _filepath = "";
    _fileout = "";
    _id = "";
    _password = "";
    _seeds.clear();
    _mangling = true;
    _check_for_data_loss = false;
    _config_from_file = false;
}
void RunConfiguration::printConfig(){
    for(int i = 0; i < endofconfig; i++){
        std::string data;
        switch (i){
            case filepath_:
                data = _filepath;
                break;
            case fileout_:
                data = _fileout;
                break;  
            case id_: 
                data = _id;
                break;
            case pass_:
                data = _password;
                break;
            case seedfile_:
                data = _seedfile;
                break;
            case seed_:
                for(int j = 0; j < _seeds.size(); j++){
                    std::cout << AVAILABLE_CONFIGURATIONS[i] << " : " + _seeds[j] << std::endl;
                }
                continue;
            case mangling_:
                data = std::to_string(_mangling);
                break;
            case datalosscheck_:
                data = std::to_string(_check_for_data_loss);
                break;
            case command_:
                data = _command;
                break;
            case binfile_:
                data = std::to_string(_binfile);
                break;
            case depth_:
                data = std::to_string(_depth);
                break;
            default:
                break;
        }
        std::cout << AVAILABLE_CONFIGURATIONS[i] << " : ";
        std::cout << data << std::endl;
    }
}