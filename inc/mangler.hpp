#include <vector>
#ifndef MANGLER
#define MANGLER

class Mangler{
protected:
    std::string text;
    std::vector<uint8_t> bin;

    int _depth;

    uint64_t hash;
    std::string mangledText;
    std::vector<uint8_t> mangledBin;
    
    virtual void _mangle(std::string& str, int depth) = 0;
    virtual void _mangle(std::vector<uint8_t>& bin, int depth) = 0;

    virtual void _unmangle(std::string& str, int depth) = 0;
    virtual void _unmangle(std::vector<uint8_t>& bin, int depth) = 0;

    static bool is_prime(size_t num);
public:
    Mangler(){}
    Mangler(const std::string& text, uint64_t hash, int depth):text(text), hash(hash), _depth(depth){}
    Mangler(const std::vector<uint8_t>& bin, uint64_t hash,  int depth) : bin(bin), hash(hash), _depth(depth) {}

    void setText(const std::string& text){ this->text = text; }
    void setHash(uint64_t hash){ this->hash = hash;}
    std::string getMangledText();
    std::string getUnmangledText();

    std::vector<uint8_t> getMangledBin();
    std::vector<uint8_t> getUnmangledBin();
};

class FurkanMangler : public Mangler{
public:
    FurkanMangler(){}
    FurkanMangler(const std::string& text, uint64_t hash, int depth) : Mangler(text, hash, depth) {}
    FurkanMangler(const std::vector<uint8_t>& bin, uint64_t hash, int depth) : Mangler(bin, hash, depth) {}

    static void _shift(std::string& str, size_t amount, bool to_right = true);
    static void _shift(std::vector<uint8_t>& v, size_t amount, bool to_right = true);

    static size_t _getMaxPrimeDivider(size_t count);
    
protected:
    void _mangle(std::string& str, int depth);
    void _mangle(std::vector<uint8_t>& bin, int depth);

    void _unmangle(std::string& str, int depth);
    void _unmangle(std::vector<uint8_t>& bin, int depth);

private:

    void _mangleSubStrings(std::vector<std::string>& subStrings);
    void _mangleSubVectors(std::vector<std::vector<uint8_t>>& subVectors );

    void _mangleSmallestSection(std::string& str);
    void _mangleSmallestSection(std::vector<uint8_t>& bin);

    void _unmangleSubStrings(std::vector<std::string>& subStrings);
    void _unmangleSubVectors(std::vector<std::vector<uint8_t>>& subVectors );

    void _unmangleSmallestSection(std::string& str);
    void _unmangleSmallestSection(std::vector<uint8_t>& bin);

    void _shift(std::vector<std::string>& subStrings, size_t amount, bool to_right);
    void _shift(std::vector<std::vector<uint8_t>>& subStrings, size_t amount, bool to_right);

    std::string _concatStrings(const std::vector<std::string>& subStrings);
    std::vector<uint8_t> _concatVectors(const std::vector<std::vector<uint8_t>>& subVectors);
};

#endif