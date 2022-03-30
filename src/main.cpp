#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include "../inc/application.hpp"

int main(){
    
    Application App("config.in");
    App.Run();

    return 0;
}
