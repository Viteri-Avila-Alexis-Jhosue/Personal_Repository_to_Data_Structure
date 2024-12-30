#include "../include/Encryption.h"

std::string Encryption::cesar(const std::string& text, int clave) {
    std::string result = text;
    for (char& c : result) {
        if (isalpha(c)) {
            char base = islower(c) ? 'a' : 'A';
            c = static_cast<char>((c - base + clave) % 26 + base);
        }
    }
    return result;
}
std::string Encryption::decryptCesar(const std::string& text, int clave) {
    std::string decryptedText = text;
    for (char& c : decryptedText) {
        if (isalpha(c)) {
            char base = islower(c) ? 'a' : 'A';
            c = (c - base - clave + 26) % 26 + base;
        }
    }
    return decryptedText;
}
