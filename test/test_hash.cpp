#include <assert.h>
#include <iostream>
#include "../inc/encrpytengine.hpp"
extern uint64_t hash_str(const char* s);
extern uint64_t hash_str_ign_char_order(const char* s);

void hash_str_ign_char_order_test(){
    char teststr[500];
    std::cout << "text to test hash (max 500 characters) : " ;
    std::cin.getline(teststr, 500);
    int num;
    std::cout << "number of shifts : "  << std::flush;
    std::cin >> num;
    std::string teststring(teststr);
    uint64_t init_hash = hash_str_ign_char_order(teststring.c_str());
    while(num){
        num--;
        FurkanMangler::_shift(teststring, 1, true);
        bool state = init_hash == hash_str_ign_char_order(teststring.c_str());
        assert(state && "Shifted string doesn't have the same hash.");
        teststring[0]++;
        state = init_hash != hash_str_ign_char_order(teststring.c_str());
        assert(state && "Different strings have the same hash.");
        teststring[0]--;
    }
    std::cout << "\t[SUCCESS] : hash_str_ign_char_order(const char*)" << std::endl;
}