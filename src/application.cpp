#include "../inc/application.hpp"
#include <cmath>
#include <fstream>
#include <sstream>

extern uint64_t hash_str(const char * s);

bool Application::_checkAuthentication_(){
    bool result = false; 
    /*
    if(_configuration.isBinaryFile()){
        result = header_in_bin == header.getHeaderBin(_configuration.getID(), _configuration.getPassword());
    }
    else{
        result = header_in_txt == header.getHeader(_configuration.getID(), _configuration.getPassword());
    }  */
    return header_in_txt == header.getHeader(_configuration.getID(), _configuration.getPassword());
}

bool Application::_readText_(){
    fileHandler.setFilePath(_configuration.getFilePath());
    std::string text_and_header;
    std::vector<uint8_t> text_and_header_bin;
    header_in_txt = "";

    if(_configuration.isBinaryFile()){
        if ( !fileHandler.getBinFromFile(text_and_header_bin) ) return false; 
    }
    else{
        if ( !fileHandler.getTextFromFile(text_and_header) ) return false; 
    }
    
    if ( state == Decrypting ){
        std::string hdr = header.getHeader(_configuration.getID(), _configuration.getPassword());
        if(_configuration.isBinaryFile()){
            for(int i = 0 ; i < hdr.length() ; i++){
                header_in_txt += text_and_header_bin[i];
            }
            //std::cout << "expected header : " << hdr << " size : " << hdr.length() << std::endl;
            //std::cout << "header in file : " << header_in_txt <<  " size : " << header_in_txt.length() << std::endl;
        }
        else{
            header_in_txt = text_and_header.substr(0, hdr.length() );
        }
    }

    if(_configuration.isBinaryFile()){
        binary = std::vector<uint8_t>(text_and_header_bin.begin() + header_in_txt.length(), text_and_header_bin.end());
    }
    else{
        text = text_and_header.substr(header_in_txt.length());
    }
    return true;
}

bool Application::_writeText_(const std::string& out){
    fileHandler.setFilePath(_configuration.getFileOut());
    if ( state == Encrypting )return fileHandler.writeTextToFile(header.getHeader(_configuration.getID(), _configuration.getPassword()) + out);
    return fileHandler.writeTextToFile(out);
}

bool Application::_writeBinary_(const std::vector<uint8_t>& out_bin){
    fileHandler.setFilePath(_configuration.getFileOut());
    if ( state == Encrypting ){
        std::vector<uint8_t> header_and_out = header.getHeaderBin(_configuration.getID(), _configuration.getPassword());
        for(auto i : out_bin){
            header_and_out.push_back(i);
        }
        return fileHandler.writeBinToFile(header_and_out);
    }
    return fileHandler.writeBinToFile(out_bin);
}

bool Application::_handleReading(){

    std::string filepath = _configuration.getFilePath();

    if (!_configuration.isConfigFromFile()) {
        std::cout << "Enter the file path : ";
        std::cin >> filepath;
        _configuration.setFilePath(filepath);
    }

    if( !_readText_() ){
        std::cerr << "Couldn't open " << filepath << std::endl;
        return false;
    }

    //std::cout << "Read " << (_configuration.isBinaryFile() ? binary.size() : text.length()) << " bytes from " << filepath << std::endl;
    //printPrimeNumbers();

    if ( state == Decrypting && !_checkAuthentication_()){
        std::cerr << "You are not authorized to decrypt this file." << std::endl;
        return false;
    }
    return true;
}

bool Application::_handleWriting(const std::string& out){

    if( !_writeText_(out) && !_configuration.isDataLossCheckEnabled()){
        std::cerr << "Couldn't open " << _configuration.getFileOut() << std::endl;
        return false;
    }
    std::cout << _configuration.getFilePath() << " is " << (state == Encrypting ? "encypted" : "decrypted" ) << " and written to \'" << _configuration.getFileOut() << "\'" << std::endl;
    return true;
}

bool Application::_handleWriting(const std::vector<uint8_t>& out_bin){

    if( !_writeBinary_(out_bin) && !_configuration.isDataLossCheckEnabled()){
        std::cerr << "Couldn't open " << _configuration.getFileOut() << std::endl;
        return false;
    }
    std::cout << _configuration.getFilePath() << " is " << (state == Encrypting ? "encypted" : "decrypted" ) << " and written to \'" << _configuration.getFileOut() << "\'" << std::endl;
    return true;
}

void Application::_handleMangling(std::string& text_to_mangle) const {
    if ( !_configuration.isManglingEnabled() ) return;
    FurkanMangler mangler(text_to_mangle, hash_str((_configuration.getPassword() + _configuration.getID()).c_str()), _configuration.getDepth());
    text_to_mangle = mangler.getMangledText();
}

void Application::_handleMangling(std::vector<uint8_t>& bin) const {
    if ( !_configuration.isManglingEnabled() ) return;
    FurkanMangler mangler(bin, hash_str((_configuration.getPassword() + _configuration.getID()).c_str()), _configuration.getDepth());
    bin = mangler.getMangledBin();
}

void Application::_handleUnmangling(std::string& text_to_unmangle) const {
    if ( !_configuration.isManglingEnabled()  ) return;
    FurkanMangler mangler(text_to_unmangle, hash_str((_configuration.getPassword() + _configuration.getID()).c_str()), _configuration.getDepth());
    text_to_unmangle = mangler.getUnmangledText();
}

void Application::_handleUnmangling(std::vector<uint8_t>& bin) const {
    if ( !_configuration.isManglingEnabled() ) return;
    FurkanMangler mangler(bin, hash_str((_configuration.getPassword() + _configuration.getID()).c_str()), _configuration.getDepth());
    bin = mangler.getUnmangledBin();
}

void Application::_updateCommand() {
    if (!_configuration.isConfigFromFile()) {
        std::cout << "\nEnter a command \n # enc : encrypt\n # dec : decrypt\n # runconfig : run a config file\n # gensf : generate a seed file\n # readsf : read the seeds in a seedfile\n # pdif : print diff\n # exit : exit\n -> ";
        std::cin >> command;
        return;
    }
    command = _configuration.getCommand();
}

void Application::_updateCretentials(){

    if (_configuration.isConfigFromFile()) return;

    std::string id;
    std::string password;
    std::cout << "Enter the id of encrypter: ";
    std::cin >> id;
    std::cout << "Enter the encryption password : ";
    std::cin >> password;
    _configuration.setID(id);
    _configuration.setPassword(password);
}

void Application::_updateOutputPath(){

    std::string fileout = _configuration.getFileOut();

    if (!_configuration.isConfigFromFile()) {

        std::cout << "Enter the output file path (to leave it as default enter '.' ): ";
        std::cin >> fileout;
        _configuration.setFileOut(fileout);
    }

    if (fileout == "." || fileout == ""){
        std::string filepath = _configuration.getFilePath();
        if ( state == Encrypting){
            _configuration.setFileOut( filepath.substr(0, filepath.find_last_of('.')) + "_enc." + filepath.substr(filepath.find_last_of('.') + 1) );
        }
        else{
            if(filepath.find("_enc") != std::string::npos){
                filepath = filepath.substr(0, filepath.find_last_of("_")) + filepath.substr(filepath.find_last_of('.') );
            }
            _configuration.setFileOut( filepath.substr(0, filepath.find_last_of('.')) + "_dec." + filepath.substr(filepath.find_last_of('.') + 1) );
        }
    }
}

uint32_t Application::_getLayerNumber() const{

    if (_configuration.isConfigFromFile()) return _configuration.getSeeds().size();

    std::string number;
    uint32_t num = 0;
    std::cout << "Layers of encryption : ";
    std::cin >> number;
    if(number != ""){
        num = atoi(number.c_str());
    }
    return num;
}

void Application::_getSeedFromUserUntil(uint32_t num){
    if (_configuration.isConfigFromFile()) return;
    _configuration.clearSeeds();
    while( _configuration.getSeeds().size() < num ){
        std::cout << "Enter a seed : " << std::flush;
        std::string seed;
        do{
            std::getline(std::cin, seed);
        }while(seed.empty());

        _configuration.addSeed(seed);
    }
}

const std::string& Application::_getSeed(uint32_t index) {
    return _configuration.getSeed(index);
}

void Application::_generatePlainSeedFile(){
    auto seeds = _configuration.getSeeds();
    text.clear();
    text += _configuration.getID() + "\n";
    text += std::to_string(hash_str(_configuration.getPassword().c_str())) + "\n";
    for(int i = 0; i < seeds.size(); i++){
        //std::cout << "Adding seed to seedfile : " << seeds[i] << "\n";
        text += seeds[i] + (i + 1 >= seeds.size() ? "" : "\n");
    }
}

std::vector<std::string> Application::_getSeedsFromDecryptedSeedFile(const std::string& seedfile){
    std::vector<std::string> seeds;

    std::stringstream ss(seedfile.c_str());
    std::string line;
    std::string pwline = std::to_string(hash_str(_configuration.getPassword().c_str()));
    bool idfound = false, pwfound = false;
    while(std::getline(ss, line)){
        if(idfound){
            if(pwfound)
                seeds.push_back(line);
            else
                pwfound = line == pwline;
        }
        else
            idfound = line == _configuration.getID();
    }

    return seeds;
}

void Application::_Encrypt(std::string& str, uint32_t num){

    for(uint32_t i = 0; i < num ; i++){
        std::string seed = _getSeed(i);
        if ( seed == _configuration.nullstr ) return;
        EncryptEngine e_engine(str, seed, _configuration.getPassword() + _configuration.getID());
        str = e_engine.getEncryptedText();
    }
}

void Application::_Encrypt(std::vector<uint8_t>& bin, uint32_t num){

    for(uint32_t i = 0; i < num ; i++){
        std::string seed = _getSeed(i);
        if ( seed == _configuration.nullstr ) return;
        BinaryEncryptEngine e_engine(bin, seed, _configuration.getPassword() + _configuration.getID());
        bin = e_engine.getEncryptedBinaries();
    }
}

void Application::_Decrypt(std::string& str, uint32_t num){
    for(uint32_t i = 0; i < num ; i++){
        std::string seed = _getSeed(i);
        DecryptEngine d_engine(str, seed, _configuration.getPassword() + _configuration.getID());
        str = d_engine.getDecryptedText();
    }
}

void Application::_Decrypt(std::vector<uint8_t>& bin, uint32_t num){
    for(uint32_t i = 0; i < num ; i++){
        std::string seed = _getSeed(i);
        BinaryDecryptEngine d_engine(bin, seed, _configuration.getPassword() + _configuration.getID());
        bin = d_engine.getDecryptedBinaries();
    }
}

bool Application::_checkForDataLoss(const std::string& out){

    if ( !_configuration.isDataLossCheckEnabled() ) return true;
    if ( !_writeText_(out) ) {std::cerr << "Data loss check could not be initiated due to a write issue." << std::endl; return false;}
    _configuration.reverseFilePaths();
    std::string textholder = text;
    state = Decrypting;
    if ( _readText_() ){
        _handleUnmangling(text);
        for (std::string seed : _configuration.getSeeds())
        {
            DecryptEngine de(text, seed, _configuration.getPassword() + _configuration.getID());
            text = de.getDecryptedText();
        }
    }
    state = Encrypting;
    _configuration.reverseFilePaths();
    uint32_t dataloss = FileHandler::printOnlyDifferences(textholder, text);
    text = textholder;
    if ( dataloss ){
        std::cerr << dataloss << " bytes lost." << std::endl;
        std::cerr << "There was an error while encrypting! Please notify the dev team about this issue." << std::endl;
    }
    return !dataloss;
}

bool Application::_checkForDataLoss(const std::vector<uint8_t>& out){

    if ( !_configuration.isDataLossCheckEnabled() ) return true;
    if ( !_writeBinary_(out) ) {std::cerr << "Data loss check could not be initiated due to a write issue." << std::endl; return false;}
    _configuration.reverseFilePaths();
    std::vector<uint8_t> bin_holder = binary;
    state = Decrypting;
    if ( _readText_() ){
        _handleUnmangling(binary);
        for (std::string seed : _configuration.getSeeds())
        {
            BinaryDecryptEngine de(binary, seed, _configuration.getPassword() + _configuration.getID());
            binary = de.getDecryptedBinaries();
        }
    }
    state = Encrypting;
    _configuration.reverseFilePaths();
    uint32_t dataloss = FileHandler::printOnlyDifferences(bin_holder, binary);
    binary = bin_holder;
    if ( dataloss != 0 ){
        std::cerr << dataloss << " bytes lost." << std::endl;
        std::cerr << "There was an error while encrypting! Please notify the dev team about this issue." << std::endl;
    }
    else{
        std::cout << "No data loss detected after encryption." << std::endl;
    }
    return !dataloss;
}


void Application::handleEncryption(){
    if ( _configuration.isUsingSeedFile() ){
        std::string filepath = _configuration.getFilePath();
        _configuration.setFilePath(_configuration.getSeedFile());
        handleGetSeedFile();
        state = Encrypting;
        _configuration.setFilePath(filepath);
    }
    if ( ! _handleReading() ) return;
    std::string encrypted_t = text;
    std::vector<uint8_t> encrypted_b = binary;
    _updateCretentials();
    _updateOutputPath();

    uint32_t layerCount = _getLayerNumber();
    _getSeedFromUserUntil(layerCount);


    if(_configuration.isBinaryFile()){
        _Encrypt(encrypted_b, layerCount);
        _handleMangling(encrypted_b);
        bool nodataloss = _checkForDataLoss(encrypted_b);
        if (nodataloss) _handleWriting(encrypted_b);
    }
    else{
        _Encrypt(encrypted_t, layerCount);
        _handleMangling(encrypted_t);
        bool nodataloss = _checkForDataLoss(encrypted_t);
        if (nodataloss) _handleWriting(encrypted_t);
    }
}

void Application::handleDecryption(){
    if ( _configuration.isUsingSeedFile() ){
        std::string filepath = _configuration.getFilePath();
        _configuration.setFilePath(_configuration.getSeedFile());
        handleGetSeedFile();
        state = Decrypting;
        _configuration.setFilePath(filepath);
    }
    _updateCretentials();
    if ( ! _handleReading() ) return;
    std::string decrypted_t = text;
    std::vector<uint8_t> decrypted_b = binary;
    _updateOutputPath();


    uint32_t layerCount = _getLayerNumber();
    _getSeedFromUserUntil(layerCount);
    
    if(_configuration.isBinaryFile()){
        _handleUnmangling(decrypted_b);
        _Decrypt(decrypted_b, layerCount);
        _handleWriting(decrypted_b);
    }
    else{
        _handleUnmangling(decrypted_t);
        _Decrypt(decrypted_t, layerCount);
        _handleWriting(decrypted_t);
    }
}

void Application::handleGenSeedFile(){
    // Setup the configuration
    _updateCretentials();
    _updateOutputPath();

    uint32_t layerCount = _getLayerNumber();
    _getSeedFromUserUntil(layerCount);

    // Create the seedfile
    _generatePlainSeedFile();

    // Create the encrypting seeds
    _configuration.clearSeeds();
    _configuration.addSeed(_configuration.getID());
    _configuration.addSeed(_configuration.getPassword());
    _configuration.addSeed(std::to_string(hash_str(_configuration.getID().c_str())));
    _configuration.addSeed(std::to_string(hash_str(_configuration.getPassword().c_str())));
    _configuration.addSeed(std::to_string(hash_str((_configuration.getPassword() + _configuration.getID()).c_str())));


    _configuration.setFilePath("Seedfile");
    
    state = Encrypting;
    std::vector<uint8_t> encrypted_b(text.begin(), text.end());

    _Encrypt(encrypted_b, 5);
    _handleMangling(encrypted_b);
    bool nodataloss = _checkForDataLoss(encrypted_b);
    if (nodataloss) _handleWriting(encrypted_b);
}

void Application::handleReadSeedFile(){
    handleGetSeedFile();

    std::cout << "Read the seed file : \n";
    for(auto seed : _configuration.getSeeds())
        std::cout << seed << std::endl;
    std::cout << "Total seeds : " << _configuration.getSeeds().size() << std::endl;
}

void Application::handleGetSeedFile(){
    state = Decrypting;
    _updateCretentials();
    if ( ! _handleReading() ) return;
    std::vector<uint8_t> decrypted_b = (_configuration.isBinaryFile() ? binary : std::vector<uint8_t>(text.begin(), text.end()));

    // Set the decryption seeds
    _configuration.clearSeeds();
    _configuration.addSeed(_configuration.getID());
    _configuration.addSeed(_configuration.getPassword());
    _configuration.addSeed(std::to_string(hash_str(_configuration.getID().c_str())));
    _configuration.addSeed(std::to_string(hash_str(_configuration.getPassword().c_str())));
    _configuration.addSeed(std::to_string(hash_str((_configuration.getPassword() + _configuration.getID()).c_str())));

    _handleUnmangling(decrypted_b);
    _Decrypt(decrypted_b, 5);
    auto seeds = _getSeedsFromDecryptedSeedFile(std::string(decrypted_b.begin(), decrypted_b.end()));

    _configuration.clearSeeds();
    for(auto seed : seeds)
        _configuration.addSeed(seed);
}

bool Application::handleCommand(){
    
    _updateCommand();

    if(command == "enc"){
        state = Encrypting;
        handleEncryption();
        _configuration.clear();
    }
    else if ( command == "dec" ){
        state = Decrypting;
        handleDecryption();
        _configuration.clear();
    }
    else if ( command == "pdif" ){
        std::string path1;
        std::string path2;
        std::cout << "Path of the first file : ";
        std::cin >> path1;
        std::cout << "Path of the second file : ";
        std::cin >> path2;
        FileHandler::printDifferencesOfFiles(path1, path2);
    }
    else if ( command == "runconfig"){
        std::string path;
        std::cout << "Path of the configuration file ('.' for default : 'config.in'): ";
        std::cin >> path;

        if( path == "." ){
            path = "config.in";
        }
        std::ifstream is(path, std::ios::in);
        if(is.good()){
            is.close();
            _configuration.getConfigurationFromFile(path);
            return true;
        }
        else{
            std::cerr << "Sorry, the configuration file does not exist.\n"; 
            return false;
        }
    }
    else if ( command == "gensf"){
        state = Encrypting;
        handleGenSeedFile();
        _configuration.clear();
    }
    else if ( command == "readsf"){
        state = Decrypting;
        handleReadSeedFile();
        _configuration.clear();
    }
    else if( command == "exit" ){
        shouldRun = false;
    }
    else{
        std::cerr << "Command \'" << command << "\' is invalid." << std::endl;
    }

    return !shouldRunOnce && shouldRun;
}

void Application::reset(){
    _configuration.clear();
    text = "";
    header_in_txt = "";
    fileHandler = FileHandler();
}

void Application::Run(){
    printWelcomeMessage();

    _configuration.printConfig();

    while (handleCommand());

    printExitMessage();

    reset();
}

void Application::printWelcomeMessage(){
    std::cout << "Welcome to zEncrypter!" << "\n";
}
void Application::printExitMessage(){
    std::cout << "Until we meet again..." << std::endl;
}

void Application::printPrimeNumbers(){
    std::vector<int> primes;

    size_t size = (_configuration.isBinaryFile() ? binary.size() : text.length());
    size_t s = size;

    while (size % 2 == 0)  
    {  
        primes.push_back(2);
        size = size/2;  
    }  
  
    // n must be odd at this point. So we can skip  
    // one element (Note i = i +2)  
    for (int i = 3; i <= std::sqrt(size); i = i + 2)  
    {  
        // While i divides n, print i and divide n  
        while (size % i == 0)  
        {  
            primes.push_back(i);
            size = size/i;  
        }  
    }  
  
    // This condition is to handle the case when n  
    // is a prime number greater than 2  
    if (size > 2)  
        primes.push_back(size);
        

    std::cout << "Prime divisors of " << s << ":\n";
    for(auto i : primes){
        std::cout << i<< ", ";
    }
    std::cout << std::endl;
}