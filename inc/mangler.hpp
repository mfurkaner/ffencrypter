#include <vector>
#ifndef MANGLER
#define MANGLER

class Mangler{
protected:
    std::string text;
    uint64_t hash;
    std::string mangledText;
    
    virtual void _mangle(std::string& str) = 0;
    virtual void _unmangle(std::string& str) = 0;

    static bool is_prime(size_t num);
public:
    Mangler(){}
    Mangler(const std::string& text, uint64_t hash):text(text), hash(hash){}

    void setText(const std::string& text){ this->text = text; }
    void setHash(uint64_t hash){ this->hash = hash;}
    std::string getMangledText();
    std::string getUnmangledText();
};

class FurkanMangler : public Mangler{
public:
    FurkanMangler(){}
    FurkanMangler(const std::string& text, uint64_t hash) : Mangler(text, hash) {}

    static void _shift(std::string& str, size_t amount, bool to_right = true);
    
protected:
    void _mangle(std::string& str);
    void _unmangle(std::string& str);

private:
    static size_t _getMaxPrimeDivider(size_t count);

    void _mangleSubStrings(std::vector<std::string>& subStrings);
    void _mangleSmallestSection(std::string& str);

    void _unmangleSubStrings(std::vector<std::string>& subStrings);
    void _unmangleSmallestSection(std::string& str);

    void _shift(std::vector<std::string>& subStrings, size_t amount, bool to_right);

    std::string _concatStrings(const std::vector<std::string>& subStrings);
};

#endif