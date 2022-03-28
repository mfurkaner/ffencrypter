#include <string>
#include <vector>

extern uint64_t hash_str_ign_char_order(const char* s);

#ifndef MANGLER
#define MANGLER

class Mangler{
protected:
    uint64_t hash;
    std::string text;
    std::string mangledText;
    
    virtual void _mangle(std::string& str) = 0;
    virtual void _unmangle(std::string& str) = 0;

    static bool is_prime(size_t num){
    if (num <= 1)
        return false;

    for(int i = 2; i <= num / 2; i++) {
        if(num % i == 0) {
            return false;
        }
    }
    return true;
}
public:
    Mangler(){}
    Mangler(const std::string& text, uint64_t hash):text(text), hash(hash){}

    void setText(const std::string& text){
        this->text = text;
    }
    void setHash(uint64_t hash){
        this->hash = hash;
    }
    std::string getMangledText(){
        mangledText = text;
        _mangle(mangledText);
        return mangledText;
    }
    std::string getUnmangledText(){
        mangledText = text;
        _unmangle(mangledText);
        return mangledText;
    }
};

class FurkanMangler : public Mangler{
public:
    FurkanMangler(){}
    FurkanMangler(const std::string& text, uint64_t hash) : Mangler(text, hash) {}
    static void _shift(std::string& str, size_t amount, bool to_right = true){
        std::string shifted = "";

        for(int i = 0; i < str.size(); i++){
            if (to_right){
                shifted += str[ i - amount + ( i < amount  ? str.size() : 0 ) ];
            }
            else{
                shifted += str[ i + amount - ( i + amount < str.size()  ? 0 : str.size() ) ];
            }
        }

        str = shifted;
    }
protected:
    void _mangle(std::string& str){

        size_t maxDivider = _getMaxPrimeDivider( str.size() );

        if ( maxDivider == str.size() ){
            _mangleSmallestSection(str);
            return;
        }

        std::vector<std::string> subStrings;
        size_t amount_to_shift = str.size() / maxDivider;

        for( size_t i = 0 ; i < maxDivider ; i++){
            subStrings.push_back( str.substr(i*amount_to_shift, amount_to_shift) );
            _mangle(subStrings[i]);
        }
        _mangleSubStrings(subStrings);
        str = _concatStrings(subStrings);
    }

    void _unmangle(std::string& str){

        size_t maxDivider = _getMaxPrimeDivider( str.size() );

        if ( maxDivider == str.size() ){
            _unmangleSmallestSection(str);
            return;
        }

        std::vector<std::string> subStrings;
        size_t amount_to_shift = str.size() / maxDivider;

        for( size_t i = 0 ; i < maxDivider ; i++){
            subStrings.push_back( str.substr(i*amount_to_shift, amount_to_shift) );
            _unmangle(subStrings[i]);
        }
        _unmangleSubStrings(subStrings);
        str = _concatStrings(subStrings);
    }

private:
    static size_t _getMaxPrimeDivider(size_t count){
        for ( int i = count/2 ; i >= 2 ; i--){
            if( count % i == 0 && is_prime(i) ){
                return i;
            }
        }
        return count;
    }

    void _mangleSubStrings(std::vector<std::string>& subStrings){
        size_t shift_amount = hash % subStrings.size();
        _shift(subStrings, shift_amount, false);
    }

    void _mangleSmallestSection(std::string& str){
        size_t shift_amount = ( hash_str_ign_char_order(str.c_str()) * hash ) % str.size();
        _shift(str, shift_amount, true);
    }

    void _unmangleSubStrings(std::vector<std::string>& subStrings){
        size_t shift_amount = hash % subStrings.size();
        _shift(subStrings, shift_amount, true);
    }

    void _unmangleSmallestSection(std::string& str){
        size_t shift_amount = ( hash_str_ign_char_order(str.c_str()) * hash ) % str.size();
        _shift(str, shift_amount, false);
    }

    void _shift(std::vector<std::string>& subStrings, size_t amount, bool to_right){
        std::vector<std::string> shifted;
        for(int i = 0; i < subStrings.size(); i++){
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

    std::string _concatStrings(const std::vector<std::string>& subStrings){
        std::string out = "";
        for(int i = 0; i < subStrings.size() ; i++){
            out += subStrings[i];
        }
        return out;
    }
};

#endif