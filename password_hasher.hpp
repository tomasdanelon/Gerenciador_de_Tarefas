#include <string>

class PasswordHasher {
public:
    static std::string calcularHash(const std::string& password);
};