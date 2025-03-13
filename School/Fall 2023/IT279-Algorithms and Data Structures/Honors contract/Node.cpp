// Shane Stevens

#include "Node.h"
using namespace std;

Node::Node(char letter = ' '){
    data = letter;
}

bool Node::add(char letter){
    int index;
    if(find(letter) == -1){
        if(letter == 0){
                index = 0;
            }
        else{
            index = letter - 96;
        }
    nextNodes[index] = new Node(letter);
    }
    else{
        return false;
    }
}

int Node::find(char letter){
    int index;
    if(letter == 0){
        index = 0;
    }
    else{
        index = letter - 96;
    }
    if(nextNodes[index] != nullptr){
        return index;
    }
    else{
        return -1;        
    }

}