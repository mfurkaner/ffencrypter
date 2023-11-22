#include <iostream>
#include <stdint.h>
#include <vector>

#ifndef HASH
#define HASH
#define A 54059 /* a prime */
#define B 76963 /* another prime */
#define C 86969 /* yet another prime */
#define FIRSTH 37 /* also prime */

uint64_t hash_str(const char* s)
{
   unsigned h = FIRSTH;
   while (*s) {
     h = (h * A) ^ (s[0] * B);
     s++;
   }
   return h; // or return h % C;
}

uint64_t hash_str_ign_char_order(const char* s)
{
   uint64_t h = FIRSTH;
   while (*s) {
     h += (FIRSTH * A) ^ (s[0] * B);
     s++;
   }
   return h; // or return h % C;
}

uint64_t hash_bin(const std::vector<uint8_t>& v)
{
   uint64_t h = FIRSTH;
   for(int i = 0; i < v.size();i++){
    h += (FIRSTH * A) ^ (v[i] * B);
   }
   return h; // or return h % C;
}
#endif