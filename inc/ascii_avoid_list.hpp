

const unsigned char ASCII_AVOID_LIST[] = {0, 1, 2, 3, 4, 5, 6, 8, 
                                 16, 17, 18, 19, 20, 21, 
                                 23, 24, 25, 26, 27, 28, 
                                 29, 30, 31 };

#define AVOID_LIST_SIZE sizeof(ASCII_AVOID_LIST)/sizeof(char)

inline bool does_have_avoid_element(const std::string& str){
    for(int i = 0 ; i < str.size() ; i++){
        for(int j = 0; j < AVOID_LIST_SIZE ; j++){
            if( ASCII_AVOID_LIST[j] == str.at(i)){
                std::cout << "Found an avoid char at " << i << " with value " << ASCII_AVOID_LIST[j] << std::endl;
            }
        }
    }
    return true;
}

inline uint8_t jump_avoid_elements_right(uint8_t c, uint8_t shift_amount){
    if ( !shift_amount ) return 0;
    uint16_t candidate = c;
    uint8_t overflow;
    do{
        uint8_t count = 0;
        candidate += shift_amount;
        overflow = ( candidate >> 8 ) * ( candidate & 0xff );    // if the 9th bit is set (there is overflow on 8 bits) get the 8 bits, i.e the overflow
        candidate &= 0xff;
        for( uint8_t i = 0; i < AVOID_LIST_SIZE; i++){
            if ( ASCII_AVOID_LIST[i] == candidate ){
                count++;
                continue;
            }
            if( overflow ){
                count += (ASCII_AVOID_LIST[i] > c) || (ASCII_AVOID_LIST[i] <= overflow);   // c < avoid < 256 or 0 < avoid <= candidate
            }
            else{
                count += (ASCII_AVOID_LIST[i] > c) && (ASCII_AVOID_LIST[i] <= candidate);  // c < avoid <= candidate
            }
        }
        c = candidate;
        shift_amount = count;
    }while (shift_amount);
    return candidate;
}

inline uint8_t jump_avoid_elements_left(uint8_t c, uint8_t shift_amount){
    if ( !shift_amount ) return 0;
    uint8_t candidate = c;
    do{
        uint8_t count = 0;
        candidate -= shift_amount;
        for( uint8_t i = 0; i < AVOID_LIST_SIZE; i++){
            if ( ASCII_AVOID_LIST[i] == candidate ){
                count++;
                continue;
            }
            if( shift_amount > c ){
                count += (ASCII_AVOID_LIST[i] < c) || (ASCII_AVOID_LIST[i] > candidate);   // c < avoid < 256 or 0 < avoid <= candidate
            }
            else{
                count += (ASCII_AVOID_LIST[i] < c) && (ASCII_AVOID_LIST[i] > candidate);  // c < avoid <= candidate
            }
        }
        c = candidate;
        shift_amount = count;
    }while (shift_amount);
    return candidate;
}

