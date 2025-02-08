#ifndef NODE_H
#define NODE_H

#include <string>

class Node {
private:
    int index;
    std::string word;

public:
    // Constructor
    Node(int idx, const std::string &wrd) : index(idx), word(wrd) {}

    // Getter for index
    int getIndex() const {
        return index;
    }

    // Setter for index
    void setIndex(int idx) {
        index = idx;
    }

    // Getter for word
    std::string getWord() const {
        return word;
    }

    // Setter for word
    void setWord(const std::string &wrd) {
        word = wrd;
    }
};

#endif // NODE_H