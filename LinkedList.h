#include <iostream>
#include <vector>
using namespace std;


template <typename T>
class LinkedList {
public:
    struct Node {
        T data; // data we are storing
        Node* next;
        Node* prev;
        Node();

    };
private:
    Node* head;
    Node* tail;
    unsigned int nodeCount;


// *=== Accessors ===*
public:
unsigned int NodeCount() const;


    void PrintForward() const;
    void PrintReverse() const;
    void PrintForwardRecursive(const Node* node) const;
    void PrintReverseRecursive(const Node* node) const;

    void FindAll(vector<Node*>& outData, const T& value) const;

    const Node* Find(const T& data) const;
    Node* Find(const T& data);
    const Node* GetNode(unsigned int index) const;
    Node* GetNode(unsigned int index);
    Node* Head();
    const Node* Head() const;
    Node* Tail();
    const Node* Tail() const;

    //Insertion
    void AddHead(const T& data);
    void AddTail(const T& data);
    void AddNodesHead(const T* data, unsigned int count);
    void AddNodesTail(const T* data, unsigned int count);
    void InsertAfter(Node* node, const T& data);
    void InsertBefore(Node* node, const T& data);
    void InsertAt(const T& data, unsigned int index);

    // Removal
    bool RemoveHead();
    bool RemoveTail();
    unsigned int Remove(const T& data);
    bool RemoveAt(unsigned int index);
    void Clear();

    //operators
    const T& operator[](unsigned int index) const;
    T& operator[](unsigned int index);
    bool operator==(const LinkedList<T>& rhs);

    // Big three
    LinkedList();
    LinkedList(const LinkedList<T>& list);
    LinkedList<T>& operator=(const LinkedList<T>& list); //not on project info
    ~LinkedList();

};

/* =============== END HEADER FILE; BEGIN FUNCTION DEFINITIONS ================ */

//default constructors
template <typename T>
LinkedList<T>::Node::Node() {
    next = nullptr;
    prev = nullptr;
}
template <typename T>
LinkedList<T> ::LinkedList() {
     head = nullptr;
     tail = nullptr;
     nodeCount = 0;
}

// copy constructor
template <typename T>
LinkedList<T> ::LinkedList(const LinkedList<T>& list) {

//nodeCount = list.nodeCount; or just increment nodecount
nodeCount = 0;
head = nullptr;
tail = nullptr;

    Node* listNode = list.head;

    while (listNode != nullptr) {
     AddTail(listNode->data);
     listNode = listNode->next;
    }
}
template <typename T>
LinkedList<T>& LinkedList<T> ::operator=(const LinkedList<T>& list) { //copy assignment operator
  // deleting all the information( copy code from destructor), copy information over (use copy constructor), return *this

    Node* currNode = head;
    while (currNode != nullptr)
    {
        Node* temp = currNode->next;
        delete currNode;
        currNode = temp; // will eventually reach nullptr
    }
    nodeCount = 0;
    head = nullptr;
    tail = nullptr;

    Node* listNode = list.head;
    while (listNode != nullptr) {
        AddTail(listNode->data);
        listNode = listNode->next;
    }
    return *this;
}
template <typename T>
LinkedList<T> ::~LinkedList() { //destructor
   Node* currNode = head;
   while (currNode != nullptr)
   {
       Node* temp = currNode->next;
       delete currNode;

       currNode = temp; // will eventually reach nullptr
   }
   nodeCount = 0;
   head = nullptr;
   tail = nullptr;
}

template <typename T>
void LinkedList<T> ::PrintForward() const {
Node* currNode = head;
while (currNode != nullptr) {
    cout << currNode->data << endl;
    currNode = currNode->next;
}
}

template <typename T>
void  LinkedList<T> ::PrintReverse() const {
    Node* currNode = tail;
    while (currNode != nullptr) {
        cout << currNode->data << endl;
        currNode = currNode->prev;
}
}

template <typename T>
void LinkedList<T> ::PrintForwardRecursive(const Node* node) const {

    if (node == nullptr) {
        return;
    }
    cout << node->data << endl;// recursion through function calls; base case reached-> stop. must start with base case if statement
    PrintForwardRecursive(node->next);
}

template <typename T>
void LinkedList<T> ::PrintReverseRecursive(const Node* node) const {
    if (node == nullptr) {
        return;
    }
    cout << node->data << endl;
    PrintReverseRecursive(node->prev);
}

template <typename T>
unsigned int LinkedList<T> :: NodeCount() const{
    return nodeCount;
}

//Find all nodes which match the passed in parameter value, and store a pointer to
//that node in the passed in vector. Use of a parameter like this (passing a
//something in by reference, and storing data for later use) is called an output
//parameter.
//Find the first node with a data value matching the passed in parameter,
//        returning a pointer to that node. Returns nullptr if no matching node found.
//GetNode Given an index, return a pointer to the node at that index. Throws an exception
//        of type out_of_range if the index is out of range. Const and non-const versions.

template <typename T>
void LinkedList<T> ::FindAll(vector<Node*>& outData, const T& value) const {
    Node* currNode = head;
    while (currNode != nullptr) { //traverse whole list
        if (currNode->data == value) {
            outData.push_back(currNode);
        }
        currNode = currNode->next;
    }

}

// for following classes: define typename Node* that belongs to list class with function definition
template <typename T>
const typename LinkedList<T>::Node*  LinkedList<T>::Find(const T& data) const {
    Node* currNode = head;
    unsigned int count = 0;
    while (count == 0 && currNode != nullptr) {
        if (currNode->data == data) {
            count++;
            return currNode;
        }
        currNode = currNode->next;
        }
    return nullptr;
    }

template <typename T>
typename LinkedList<T>::Node*  LinkedList<T>::Find(const T& data) {
    Node* currNode = head;
    unsigned int count = 0;
    while (count == 0 && currNode != nullptr) {
        if (currNode->data == data) {
            count++;
            return currNode;
        }
        currNode = currNode->next;
    }
    return nullptr;
}

template <typename T>
const typename LinkedList<T>:: Node* LinkedList<T>:: GetNode(unsigned int index) const{
    if (index < 0 || index >= nodeCount) {
        throw out_of_range("boo");
    }
    unsigned int count = 0;
    Node* currNode = head;
    while (currNode != nullptr) { // index from 0 to n
        if (count == index) {
            return currNode;
        }
        currNode = currNode->next;
        count++;
    }
    return nullptr;
}

template <typename T>
typename LinkedList<T>:: Node* LinkedList<T>::GetNode(unsigned int index) {
    if (index < 0 || index >= nodeCount) {
        throw out_of_range("boo");
    }
    unsigned int count = 0;
    Node* currNode = head;
    while (currNode != nullptr) { // index from 0 to n
        if (count == index) {
            return currNode;
        }
        currNode = currNode->next;
        count++;
    }
    return nullptr;
}

template <typename T>
typename LinkedList<T>::Node* LinkedList<T>::Head() {
    return head; // return head ptr (Node class object)
}
template <typename T>
const typename LinkedList<T>:: Node* LinkedList<T>::Head() const {
    return head;
}
template <typename T>
typename LinkedList<T>::Node* LinkedList<T>::Tail() {
    return tail;
}

template <typename T>
const typename LinkedList<T>::Node* LinkedList<T>::Tail() const {
    return tail;
}


//Insertion ===============================================================


template <typename T>
void LinkedList<T>::AddHead(const T& data) { // AddHead: Create a new Node at the front of the list to store the passed in parameter.


    if (nodeCount == 0) {
        Node *n2 = new Node;
        head = n2;
        tail = n2;
        n2->data = data; //store data in head object from class Node
        n2->next = nullptr;
        n2->prev = nullptr;
        nodeCount++;
    } else {  // if there are other nodes...
        Node* n2 = new Node;
        n2->data = data;
        n2->next = head;
        head->prev = n2;

        head = n2; // change pointer of "head" to new node
        nodeCount++;
    }
}

template <typename T>
void  LinkedList<T>::AddTail(const T& data){
    if (nodeCount == 0) {
     Node* n2 = new Node;
     tail = n2;
     head = n2;
     tail->data = data;
     tail->next = nullptr;
     tail->prev = nullptr;
     nodeCount ++;}
    else {
        Node* n2 = new Node;
        n2->data = data;
        tail->next = n2;
        n2-> prev = tail;

        tail = n2;
        nodeCount++;
    }
}

template <typename T>
void  LinkedList<T>::AddNodesHead(const T* data, unsigned int count){
for ( int i = count-1; i >= 0; i-- ) { //non negative int: underflows
    AddHead(data[i]);
}

}

template <typename T>
void  LinkedList<T>::AddNodesTail(const T* data, unsigned int count){
    for (unsigned int i = 0; i < count; i++ ) {
        AddTail(data[i]);
    }

}

template <typename T>
void LinkedList<T>::InsertAfter(Node* node, const T& data){
    if (node->next == nullptr) {
        AddTail(data);
    }
    else {
    Node* n2= new Node;
    n2->data = data;
    n2->next = node->next;
    node->next->prev = n2;
    node->next = n2;
    n2->prev = node;
    nodeCount ++;
    }
}

template <typename T>
void LinkedList<T>::InsertBefore(Node* node, const T& data){
    /* Create a new node, nBefore, and make it point(next) to the node.
     * It points back to whatever node's prev pointed to.
     * Now, update node's pointers: it points back(prev) to nBefore, and its next stays the same.
     */
    if (node->prev == nullptr) {
       AddHead(data);
    }
    else {
        Node *nBefore = new Node;
        nBefore->data = data;

        nBefore->next = node;
        node->prev->next = nBefore;
        nBefore->prev = node->prev;
        node->prev = nBefore; // reassign node->prev to our new node

        nodeCount ++;
    }

}

template <typename T>
void LinkedList<T>::InsertAt(const T& data, unsigned int index) {

    if (index < 0 || index > nodeCount) {
        throw out_of_range("boo");
    }
    else {
 if (index == 0) {
     AddHead(data);
 }
 else if (index == nodeCount) {
     AddTail(data);
 }
 else {
     InsertAfter(GetNode(index-1), data);
 }
// if index = 0 : add head
// if index = nodeCount : add tail
// else insert after(GetNode(index-1))


    }
}
template <typename T>
const T& LinkedList<T>::operator[](unsigned int index) const {
    if (index < 0 || index > nodeCount-1) {
        throw out_of_range("boo");
    }
    unsigned int count = 0;
    Node* node = head;
    while (count <= index) { // index from 0 to n
        node = node->next;
        count++;
    }
    return node->data;
}

template <typename T>
T& LinkedList<T>::operator[](unsigned int index) {
    if (index < 0 || index > nodeCount-1) {
        throw out_of_range("boo");
    }
    int count = 0;
    Node* node = head;
    while (count < index) { // index from 0 to n
        node = node->next;
        count++;
    }
    return node->data;
}

template <typename T>
bool LinkedList<T>::operator==(const LinkedList<T>& rhs) {
    if (nodeCount != rhs.nodeCount) {
        return false;
    }
    Node* currNode = head;
    Node* rhsNode = rhs.head;
    unsigned int countEq = 0;
    while (currNode != nullptr) { //traverse whole list
        if (currNode->data == rhsNode->data) {
         countEq ++;
        }
        currNode = currNode->next;
        rhsNode = rhsNode->next;
    }
    if (countEq == nodeCount) { //if there are as many corresponding equalities as there are nodes, then the lists are equivalent
        return true; }
    else {return false;}

}

template <typename T>
bool LinkedList<T>::RemoveHead() {
    if (nodeCount == 0) {return false;} //
 Node* n2 = head;
    if (nodeCount == 1) {
        n2->next = nullptr;
        n2->prev = nullptr;
        delete n2;
        head = nullptr;
        tail = nullptr;
    }
    else {
        head->next->prev = nullptr;
        head = head->next;
        delete n2;
    }

 nodeCount--;



 return true;
}

template <typename T>
bool LinkedList<T>::RemoveTail() {
    if (nodeCount == 0) {return false;}
Node* n2 = tail;
    if (nodeCount == 1) {
        n2->next = nullptr;
        n2->prev = nullptr;
        delete n2;
        head = nullptr;
        tail = nullptr;}

    else {
        tail->prev->next = nullptr; //important: sever the node's connections before deleting
        tail = tail->prev;
        delete n2;
    }

nodeCount--;
//
// do not delete a nullptr
return true;
}

template <typename T>
unsigned int LinkedList<T>::Remove(const T& data) {
    //deletion code: case 1, it is the head, case 2 (call functions) tail, or case 3 in the middle ;
    //
    Node* currNode = head;
    unsigned int count = 0;
    while (currNode != nullptr) { //traverse whole list
        //1. We need to delete the node...
        if (currNode->data == data) { // if we need to delete this node:
            if (currNode == head) {
                RemoveHead();
                currNode = head;
            }
            else if (currNode == tail) {
                RemoveTail();
                currNode = nullptr;

            }
            else {
                Node* nodePrev = currNode->prev;
                Node* nodeNext = currNode->next;
                nodePrev->next = nodeNext;
                nodeNext->prev = nodePrev;


                delete currNode;
                currNode = nodeNext;
                nodeCount --;

            }
            count++; // count is number of NODES REMOVED
        }
        //2. We don't delete the node; progress currNode to next
        else {
            currNode = currNode->next; // before this it ran on zybooks
        }
    }
    return count;
} // before deleting currnode make sure you progress it

template <typename T>
bool LinkedList<T>::RemoveAt(unsigned int index) {
    if (index < 0 || index >= nodeCount) {
       return false;
    }
    if (index == 0) {
        RemoveHead();
        return true;
    }
    else if (index == nodeCount-1) {
        RemoveTail();
        return true;
    }
    else {
        Node *nodeToRemove = GetNode(index);
        Node *nodePrev = nodeToRemove->prev;
        Node *nodeNext = nodeToRemove->next;
        nodePrev->next = nodeNext;
        nodeNext->prev = nodePrev;
        nodeToRemove->next = nullptr; // might not need these: sever pointers?
        nodeToRemove->prev = nullptr;

        delete nodeToRemove;
        nodeCount --;
        return true;
    }
}

template <typename T>
void LinkedList<T>::Clear() {
    Node* currNode = head; // just reuse destructor
    while (currNode != nullptr)
    {
        Node* temp = currNode->next;
        delete currNode;

        currNode = temp; // will eventually reach nullptr
    }
    nodeCount = 0;
    head = nullptr;
    tail = nullptr;
}



