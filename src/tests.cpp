#include <ios>
#include <iostream>
#include <string>
#include <assert.h>


#include "../inc/ascii_avoid_list.hpp"
#include "../inc/filehandler.hpp"
#include "../inc/encryptengine.hpp"

extern uint64_t hash_str(const char* s);
extern uint64_t hash_str_ign_char_order(const char* s);
extern void hash_str_ign_char_order_test();


int main(int argc, char* argv[]){
    /*
    std::string str = "Enter a number and the Prime Number Calculator will instantly tell you if it is a prime number or not.";
    FurkanMangler mangler(str, atoi(argv[1]));
    //std::cout << "Count is : " << str.size() << std::endl;
    //std::cout << "Before : " << str << std::endl;
    std::string mangled = mangler.getMangledText();
    std::cout << "After mangling : " << std::endl << mangled << std::endl;
    mangler.setText(mangled);
    //std::cout << "After unmangling : " << std::endl << mangler.getUnmangledText() << std::endl;
    */
   /*
    unsigned char c = 'x';
    int num;
    std::cin >> num;
    num %= (UCHAR_MAX + 1 - AVOID_LIST_SIZE);
    
    unsigned char left = jump_avoid_elements_left(c, num);
    unsigned char right = jump_avoid_elements_right(left, num);
    std::cout << "Before : " << c << std::endl;
    std::cout << "After left : " << left << std::endl;
    std::cout << "After right : " << right << std::endl;
    */


    /*
    FileHandler fh;
    std::string fin = "../deneme.txt", fmid = "ali.enc", fdec = "../ali.txt", fmen = "../men.txt";
    std::string denemetext, text;
    fh.setFilePath(fin);
    fh.getTextFromFile(text);
    does_have_avoid_element(text);
    denemetext = text;

    std::string id = "furkan";
    std::string pass = "er";
    std::string secret = pass + id;
    std::string seed1 = "aliatabak";
    std::string seed2 = "furkey";

    EncryptEngine ee(text, seed1, secret);
    text = ee.getEncryptedText();
    ee.reset();
    ee.setSeed(seed2);
    ee.setText(text);
    text = ee.getEncryptedText();

    FurkanMangler mangler(text, hash_str(secret.c_str()));
    text = mangler.getMangledText();

    fh.setFilePath(fmid);
    fh.writeTextToFile(text);
    fh.getTextFromFile(text);
    //does_have_avoid_element(text);
    //printDifferences(text, denemetext);

    mangler.setText(text);
    text = mangler.getUnmangledText();

    DecryptEngine de(text, seed1, secret);
    text = de.getDecryptedText();
    de.reset();
    de.setSeed(seed2);
    de.setText(text);
    text = de.getDecryptedText();
    does_have_avoid_element(text);


    fh.setFilePath(fdec);
    fh.writeTextToFile(text);

    fh.setFilePath(fmen);
    mangler.setText(denemetext);
    denemetext = mangler.getMangledText();
    fh.writeTextToFile(denemetext);

    FileHandler::printDifferencesOfFiles(fin, fdec);
    */

    hash_str_ign_char_order_test();

}