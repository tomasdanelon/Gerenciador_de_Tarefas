#include "password_hasher.hpp"
#include <iomanip>
#include <sstream>

unsigned long PasswordHasher::djb2Hash(const std::string& str) {
    const char* s = str.c_str();
    unsigned long hash = 5381;
    int c;

    while ((c = *s++)) {
        hash = ((hash << 5) + hash) + c; // hash * 33 + c
    }

    return hash;
}

std::string PasswordHasher::calcularHash(const std::string& password) {
    unsigned long hash = djb2Hash(password);
    std::string hashString = std::to_string(hash);
    return hashString;
}