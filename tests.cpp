#include <iostream>


//#include "mangler.hpp"
#include "ascii_avoid_list.hpp"
#include "filehandler.hpp"
#include "encrpytengine.hpp"
extern uint64_t hash_str(const char* s);


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
    FileHandler fh;
    std::string denemetext, text;
    fh.setFilePath("../a.txt");
    fh.getTextFromFile(denemetext);
    text = denemetext;

    EncryptEngine ee(text, "ali", "erfurkan");
    text = ee.getEncryptedText();
    ee.setSeed("atabaksanaAQ");
    text = ee.getEncryptedText();
    std::cout << "after enc "<< text.size() << std::endl;

    FurkanMangler mangler(text, hash_str("erfurkan"));
    text = mangler.getMangledText();
    std::cout << "after mang "<< text.size() << std::endl;

    fh.setFilePath("../denemeout.txt");
    fh.writeTextToFile(text);
    std::cout << "after write "<<text.size() << std::endl;

    fh.getTextFromFile(text);
    std::cout << "after get "<<text.size() << std::endl;

    mangler.setText(text);
    text = mangler.getUnmangledText();
    std::cout << "after unmeng "<< text.size() << std::endl;

    DecryptEngine de(text, "ali", "erfurkan");
    text = de.getDecryptedText();
    de.setSeed("atabaksanaAQ");
    text = de.getDecryptedText();


    std::cout << denemetext.size() << " " << text.size() << std::endl;
    fh.writeTextToFile(text);
}