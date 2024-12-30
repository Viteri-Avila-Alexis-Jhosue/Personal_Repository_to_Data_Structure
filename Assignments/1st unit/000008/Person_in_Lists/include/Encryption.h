#ifndef ENCRYPTION_H
#define ENCRYPTION_H

#include <string>

class Encryption {
public:
    static std::string cesar(const std::string& text, int clave);
    static std::string decryptCesar(const std::string& text, int clave);
};

#endif // ENCRYPTION_H
