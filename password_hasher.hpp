#include <string>

class PasswordHasher {
public:
    static unsigned long djb2Hash(const std::string& str);
    static std::string calcularHash(const std::string& password);
};