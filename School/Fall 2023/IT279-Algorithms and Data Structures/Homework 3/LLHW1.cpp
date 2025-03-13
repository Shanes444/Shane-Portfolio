// practice with linked lists in C++
// Homework exercises for IT 279 based on exercises from chapter 3 of Weiss text
// Mary Elaine Califf and ______

#include <iostream>
using namespace std;

// needed Node structure declarations
// Node struct for singly linked list
struct Node
{
    int dataVal;
    Node* next;

    Node(int data, Node* nextPtr = nullptr) : dataVal(data), next(nextPtr) {}
};

// DLNode is the node struct for a doubly linked list
struct DLNode
{
    int dataVal;
    DLNode* next;
    DLNode* prev;

    DLNode(int data, DLNode* prevPtr = nullptr, DLNode* nextPtr = nullptr) : dataVal(data), next(nextPtr), prev(prevPtr) {}
};

// function protoypes

// swaps the two nodes following prevNode in a linked list. The nodes to be swapped are guaranteed to present in the list
void swap(Node* prevNode);

// swaps the two nodes following preNode in a double linked list. There are guaranteed to be at least three nodes in the list after prevNode
void swap(DLNode* prevNode);

// prints the elements from listToPrintFrom at the indices in indexList to the screen. 
// The indices are zero-based. Neither list is modified in any way.
// Preconditions: indexList is sorted in ascending order and the last value in
//                indexList is less than the length of listToPrintFrom
void printByIndex(Node* listToPrintFrom, Node* indexList);

// prints the contents of theList to the screen
void printList(Node* theList);

// prints the contents of theList to the screen: first forward, then backward -- for testing purposes
void printList(DLNode* theList);

// creates a linked list from an array of elements and returns the head
// Precondition: numElements >= 1
Node* createList(int elements[], int numElems);

// creates a doubly linked list from an array of elements and returns the head of the list
// Precondition: numElements >= 1
DLNode* createDLList(int elements[], int numElems);


int main() // not using command line arguments
{
    int arr1[10] = { 0,1,2,3,4,5,6,7,8,9 };
    int arr2[5] = { 1,3,6,8,9 };
    int arr3[20] = { 9,3,5,1,6,2,4,10,20,53,21,14,17,100,90,80,70,60,50,30 };
    int arr4[10] = { 1,3,5,7,9,11,13,15,17,19 };
    int arr5[10] = { 0,2,4,6,8,10,12,14,16,18 };

    Node* list1 = createList(arr1, 10);
    Node* list2 = createList(arr2, 5);
    Node* list3 = createList(arr3, 20);
    Node* list4 = createList(arr2, 5);
    DLNode* list5 = createDLList(arr2, 5);
    Node* list6 = createList(arr4, 10);
    Node* list7 = createList(arr5, 10);

    // testing single list swap
    cout << "testing single list swap" << endl;
    cout << "swapping 3 and 6 in " << endl;
    printList(list2);
    swap(list2);
    printList(list2);

    cout << "\nswapping 3 and 8 in " << endl;
    printList(list2);
    swap(list2->next);
    printList(list2);

// test double list swap
    cout << "\ntesting swap for doubly linked lists" << endl;
    cout << "swapping 3 and 6 in " << endl;
    printList(list5);
    swap(list5);
    printList(list5);

    cout << "\nswapping 3 and 8 in " << endl;
    printList(list5);
    swap(list5->next);
    printList(list5);

    // testing printByIndex
    cout << "\ntesting the print by index" << endl;
    cout << "Expected output: "<<endl;
    cout << " 1 3 6 8 9" << endl;
    cout << "Actual output: "<<endl;
    printByIndex(list1,list4);
    cout << "\nExpect output: "<<endl;
    cout << " 3 1 4 20 53"<<endl;
    cout << "Actual output: "<<endl;
    printByIndex(list3,list4);
    cout << "\nExpect output: "<<endl;
    cout << " 9 3 5 1 6 2 4 10 20 53"<<endl;
    cout << "Actual output: "<<endl;
    printByIndex(list3,list1);
    cout << "\nExpect output: "<<endl;
    cout << " 3 1 2 10 53 14 100 80 60 30"<<endl;
    cout << "Actual output: "<<endl;
    printByIndex(list3,list6);   
    cout << "\nExpect output: "<<endl;
    cout << " 9 5 6 4 20 21 17 90 70 50"<<endl;
    cout << "Actual output: "<<endl;
    printByIndex(list3,list7);
    
    // note we are done with the program at the same time we are done with the memory so we are not bothering to clean up our memory

    return 0;
}

void swap(Node* prevNode)
{
    // to do: this function must swap the two nodes in the linked list following
    Node* temp = prevNode->next->next;
    Node*temp2 = prevNode->next;
    temp2->next = temp->next;
    temp->next = temp2;

    prevNode->next = temp;

}

void swap(DLNode* prevNode)
{
    // to do: this function must swap the two nodes in the linked list following prevNode
    DLNode* temp = prevNode->next->next;
    DLNode*temp2 = prevNode->next;
    DLNode*temp3 = temp->next;
    temp3->prev = temp2;
    temp->prev = prevNode;
    temp2->next = temp3;  
    temp->next = temp2;
    temp2->prev = temp;
    temp3->prev = temp2;
    
    
    prevNode->next = temp;
}

void printByIndex(Node* listToPrintFrom, Node* indexList)
{
    // to do: implement this as efficiently as possible based on the description above
    //        O(N^2)
    Node* curInd = indexList;
    Node* curPrnt = listToPrintFrom;
    int prevIndex = 0;
    while(curInd){
        for(int i = prevIndex; i<curInd->dataVal; i++ ){
            curPrnt = curPrnt->next;
            prevIndex++;
        }
        cout<< " " << curPrnt->dataVal ;
        curInd = curInd->next;
    }
    cout<<endl;
    

}

void printList(Node* theList)
{
    cout << "The list:";
    Node* curPtr = theList;
    while (curPtr)
    {
        cout << " " << curPtr->dataVal;
        curPtr = curPtr->next;
    }
    cout << endl;
}

void printList(DLNode* theList)
{
    DLNode* curPtr = theList;
    DLNode* prevPtr = nullptr;
    cout << "The list forward:";
    while (curPtr)
    {
        cout << " " << curPtr->dataVal;
        prevPtr = curPtr;
        curPtr = curPtr->next;
    }
    cout << "\nThe list backward:";
    while (prevPtr)
    {
        cout << " " << prevPtr->dataVal;
        prevPtr = prevPtr->prev;
    }
    cout << endl;
}

Node* createList(int elements[], int numElements)
{
    Node* head = new Node(elements[0]); // create the first node
    Node* curNode = head;
    for (int i = 1; i < numElements; i++)
    {
        Node* theNode = new Node(elements[i]); // create the node
        curNode->next = theNode; // add it to the end of the list
        curNode = theNode; // make curNode point to it.
    }
    return head;
}

DLNode* createDLList(int elements[], int numElements)
{
    DLNode* head = new DLNode(elements[0]); // create the first node
    DLNode* curNode = head;
    for (int i = 1; i < numElements; i++)
    {
        DLNode* theNode = new DLNode(elements[i], curNode); // create the node -- pointing at previous node
        curNode->next = theNode; // add it to the end of the list
        curNode = theNode; // make curNode point to it.
    }
    return head;
}

