#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <string.h>
#include "../inc/application.hpp"

int main(int argc, char *argv[]){
    std::string config_file = "config.in";
    bool command_line = true;
    if(argc > 1){
        if("-c" == std::string(argv[1]) ){
            config_file = argv[2];
            command_line = false;
        }
    }

    if(command_line){
        RunConfiguration rc;
        Application App(rc);
        App.Run();
    }
    else{
        Application App(config_file);
        App.Run();
    }

    //std::string a;
    //std::getline(std::cin, a);
    system("pause");

    return 0;
}
