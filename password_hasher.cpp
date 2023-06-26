#include "password_hasher.hpp"
#include <iomanip>
#include <iostream>

std::string PasswordHasher::calcularHash(const std::string& password) {
    unsigned long hash = 0;

    for (char c : password) {
        hash += static_cast<unsigned long>(c);
    }

    std::ostringstream oss;
    oss << std::hex << std::setw(16) << std::setfill('0') << hash;

    return oss.str();
}