#ifndef NODE_LIST_H
#define NODE_LIST_H

template <typename T>
class Node_list {
public:
    T data;
    Node_list* next;

    Node_list(T value);
};

#endif // NODE_LIST_H