#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <string.h>
#include "../inc/application.hpp"

int main(int argc, char *argv[]){
    std::string config_file = "config.in";
    bool command_line = false;
    if(argc > 1){
        if (strcmp(argv[0], "-cl")){
            command_line = true;
        }
        if(argc > 2 && strcmp(argv[0], "-c") == 0){
            config_file = argv[1];
        }
    }

    Application App(config_file);
    App.Run();

    return 0;
}
