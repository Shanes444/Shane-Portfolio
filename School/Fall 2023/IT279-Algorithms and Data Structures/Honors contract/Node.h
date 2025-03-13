//Shane Stevens

#ifndef NODE_H
#define NODE_H

class Node{

public:

    Node* nextNodes[27];
    char data;

    Node(char letter = ' ');

    bool add(char letter);

    int find(char letter);

    void printValues();

    ~Node();

private:
    void clear();

    

};
#endif