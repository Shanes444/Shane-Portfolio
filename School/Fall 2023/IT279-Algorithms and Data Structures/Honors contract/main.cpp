//Shane Stevens

#include "Node.h"
#include <iostream>

using namespace std;

int main(){
    Node* trie = new Node();
    trie->add('a');
    int aIndex = trie->find('a');
    trie->nextNodes[aIndex]->add('b');
    int bIndex = trie->nextNodes[aIndex]->find('b');
    char a = aIndex + 96;
    char b = bIndex + 96;
    cout<<a<<b<<endl;
}