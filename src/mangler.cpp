#include <string>
#include <vector>
#include <cmath>
#include "../inc/mangler.hpp"

extern uint64_t hash_str_ign_char_order(const char* s);
extern uint64_t hash_bin(const std::vector<uint8_t>& v);

bool Mangler::is_prime(size_t num){
    if (num <= 1)   return false;
    for(uint32_t i = 2; i <= num / 2; i++) {
        if(num % i == 0) {
            return false;
        }
    }
    return true;
}

std::string Mangler::getMangledText(){
    mangledText = text;
    _mangle(mangledText, _depth);
    return mangledText;
}

std::string Mangler::getUnmangledText(){
    mangledText = text;
    _unmangle(mangledText, _depth);
    return mangledText;
}

std::vector<uint8_t> Mangler::getMangledBin(){
    mangledBin = bin;
    _mangle(mangledBin, _depth);
    return mangledBin;
}

std::vector<uint8_t> Mangler::getUnmangledBin(){
    mangledBin = bin;
    _unmangle(mangledBin, _depth);
    return mangledBin;
}

void FurkanMangler::_shift(std::string& str, size_t amount, bool to_right){
    std::string shifted = "";

    for(uint32_t i = 0; i < str.size(); i++){
        if (to_right){
            shifted += str[ i - amount + ( i < amount  ? str.size() : 0 ) ];
        }
        else{
            shifted += str[ i + amount - ( i + amount < str.size()  ? 0 : str.size() ) ];
        }
    }

    str = shifted;
}

void FurkanMangler::_shift(std::vector<uint8_t>& v, size_t amount, bool to_right){
    std::vector<uint8_t> shifted;

    for(uint32_t i = 0; i < v.size(); i++){
        if (to_right){
            shifted.push_back( v[ i - amount + ( i < amount  ? v.size() : 0 ) ] );
        }
        else{
            shifted.push_back(v[ i + amount - ( i + amount < v.size()  ? 0 : v.size() ) ] );
        }
    }
    v = shifted;
}

void FurkanMangler::_mangle(std::string& str, int depth){
    if(depth == 0) return;
    size_t maxDivider = _getMaxPrimeDivider( str.size() );

    if (maxDivider == str.size() ){
        _mangleSmallestSection(str);
        return;
    }

    std::vector<std::string> subStrings;
    size_t amount_to_shift = str.size() / maxDivider;

    for( size_t i = 0 ; i < maxDivider ; i++){
        subStrings.push_back( str.substr(i*amount_to_shift, amount_to_shift) );
        _mangle(subStrings[i], depth-1);
    }

    _mangleSubStrings(subStrings);
    str = _concatStrings(subStrings);
}

void FurkanMangler::_mangle(std::vector<uint8_t>& bin, int depth){
    if(depth == 0){
        _mangleSmallestSection(bin);
        return;
    }
    size_t maxDivider = _getMaxPrimeDivider( bin.size() );

    if (maxDivider == bin.size() ){
        _mangleSmallestSection(bin);
        return;
    }

    std::vector<std::vector<uint8_t>> subVectors;
    size_t amount_to_shift = bin.size() / maxDivider;

    for( size_t i = 0 ; i < maxDivider ; i++){
        std::vector<uint8_t>::const_iterator first = bin.begin() + i*amount_to_shift;
        std::vector<uint8_t>::const_iterator last = bin.begin() + (i+1)*amount_to_shift; 
        subVectors.push_back( std::vector<uint8_t>(first, last) );
        _mangle(subVectors[i], depth-1);
    }

    _mangleSubVectors(subVectors);
    bin = _concatVectors(subVectors);
}

void FurkanMangler::_unmangle(std::string& str, int depth){
    if(depth == 0) return;
    size_t maxDivider = _getMaxPrimeDivider( str.size() );

    if ( maxDivider == str.size() ){
        _unmangleSmallestSection(str);
        return;
    }

    std::vector<std::string> subStrings;
    size_t amount_to_shift = str.size() / maxDivider;

    for( size_t i = 0 ; i < maxDivider ; i++){
        subStrings.push_back( str.substr(i*amount_to_shift, amount_to_shift) );
        _unmangle(subStrings[i], depth-1);
    }

    _unmangleSubStrings(subStrings);
    str = _concatStrings(subStrings);
}

void FurkanMangler::_unmangle(std::vector<uint8_t>& bin, int depth){
    if(depth == 0){
        _unmangleSmallestSection(bin);
        return;
    }
    size_t maxDivider = _getMaxPrimeDivider( bin.size() );

    if (maxDivider == bin.size() ){
        _unmangleSmallestSection(bin);
        return;
    }

    std::vector<std::vector<uint8_t>> subVectors;
    size_t amount_to_shift = bin.size() / maxDivider;

    for( size_t i = 0 ; i < maxDivider ; i++){
        std::vector<uint8_t>::const_iterator first = bin.begin() + i*amount_to_shift;
        std::vector<uint8_t>::const_iterator last = bin.begin() + (i+1)*amount_to_shift; 
        subVectors.push_back( std::vector<uint8_t>(first, last) );
        _unmangle(subVectors[i], depth-1);
    }

    _unmangleSubVectors(subVectors);
    bin = _concatVectors(subVectors);
}

size_t FurkanMangler::_getMaxPrimeDivider(size_t count){
    if(count == 0) return 0;

    size_t maxPrime = 1;
    while (count % 2 == 0)  
    {  
        maxPrime = 2;
        count = count/2;  
    }  
  
    // n must be odd at this point. So we can skip  
    // one element (Note i = i +2)  
    for (int i = 3; i <= std::sqrt(count); i = i + 2)  
    {  
        // While i divides n, print i and divide n  
        while (count % i == 0)  
        {  
            if(i > maxPrime){
                maxPrime = i;
            }
            count = count/i;  
        }  
    }  
  
    // This condition is to handle the case when n  
    // is a prime number greater than 2  
    if (count > 2 && maxPrime < count)  
        maxPrime = count;

    return maxPrime;
}

void FurkanMangler::_mangleSubStrings(std::vector<std::string>& subStrings){
    size_t shift_amount = hash % subStrings.size();
    _shift(subStrings, shift_amount, false);
}

void FurkanMangler::_mangleSubVectors(std::vector<std::vector<uint8_t>>& subVectors ){
    size_t shift_amount = hash % subVectors.size();
    _shift(subVectors, shift_amount, false);
}

void FurkanMangler::_mangleSmallestSection(std::string& str){
    size_t shift_amount = ( hash_str_ign_char_order(str.c_str()) * hash ) % str.size();
    _shift(str, shift_amount, true);
}

void FurkanMangler::_mangleSmallestSection(std::vector<uint8_t>& bin){
    size_t shift_amount = ( hash_bin(bin) * hash ) % bin.size();
    _shift(bin, shift_amount, true);
}

void FurkanMangler::_unmangleSmallestSection(std::string& str){
    size_t shift_amount = ( hash_str_ign_char_order(str.c_str()) * hash ) % str.size();
    _shift(str, shift_amount, false);
}

void FurkanMangler::_unmangleSmallestSection(std::vector<uint8_t>& bin){
    size_t shift_amount = ( hash_bin(bin) * hash ) % bin.size();
    _shift(bin, shift_amount, false);
}

void FurkanMangler::_unmangleSubStrings(std::vector<std::string>& subStrings){
    size_t shift_amount = hash % subStrings.size();
    _shift(subStrings, shift_amount, true);
}


void FurkanMangler::_unmangleSubVectors(std::vector<std::vector<uint8_t>>& subVectors ){
    size_t shift_amount = hash % subVectors.size();
    _shift(subVectors, shift_amount, true);
}

void FurkanMangler::_shift(std::vector<std::string>& subStrings, size_t amount, bool to_right){
    std::vector<std::string> shifted;
    for(uint32_t i = 0; i < subStrings.size(); i++){
        std::string var;
        if (to_right){
            var = subStrings[ i - amount + ( i < amount  ? subStrings.size() : 0 )] ;
        }
        else{
            var = subStrings[ i + amount - ( i + amount < subStrings.size()  ? 0 : subStrings.size() ) ] ;
        }
        shifted.push_back(var);
    }
    subStrings = shifted;
}


void FurkanMangler::_shift(std::vector<std::vector<uint8_t>>& subVectors, size_t amount, bool to_right){
    std::vector<std::vector<uint8_t>> shifted;
    for(uint32_t i = 0; i < subVectors.size(); i++){
        std::vector<uint8_t> var;
        if (to_right){
            var = subVectors[ i - amount + ( i < amount  ? subVectors.size() : 0 )] ;
        }
        else{
            var = subVectors[ i + amount - ( i + amount < subVectors.size()  ? 0 : subVectors.size() ) ] ;
        }
        shifted.push_back(var);
    }
    subVectors = shifted;
}

std::string FurkanMangler::_concatStrings(const std::vector<std::string>& subStrings){
    std::string out = "";
    for(uint32_t i = 0; i < subStrings.size() ; i++){
        out += subStrings[i];
    }
    return out;
}


std::vector<uint8_t> FurkanMangler::_concatVectors(const std::vector<std::vector<uint8_t>>& subVectors){
    std::vector<uint8_t> out;
    for(auto v : subVectors){
        for(auto i : v){
            out.push_back(i);
        }
    }

    return out;
}