///@author Tyler Proffitt
///@file Assignment 6

#include <string>
#include <cstdlib>
#include <iostream>
using namespace std;

template <class Type>
class myHash
{
  
  struct node
  {
    Type item;
    std::string key;
    node * link;
  };
  
public:
  myHash(int = 10);
  myHash(const myHash<Type>&);
  myHash& operator=(const myHash<Type>&);
  ~myHash();
  Type& operator[](std::string);
  void resize(int);
private:
  void destroyList();
  int getIndex1(std::string);
  int getIndex2(std::string);
  
  int size;
  node ** myHashList;
};


int main()
{
  myHash<int> h1;
  
  h1["car"] = 22;
  h1["red"] = 18;
  h1["reel"] = 11;
  h1["desk"] = 44;
  h1["cavalier"] = 12;
  h1["cane"] = 99;
  
  cout << "h1[\"car\"] = " << h1["car"] << endl;
  cout << "h1[\"red\"] = " << h1["red"] << endl;
  cout << "h1[\"reel\"] = " << h1["reel"] << endl;
  cout << "h1[\"desk\"] = " << h1["desk"] << endl;
  cout << "h1[\"cavalier\"] = " << h1["cavalier"] << endl;
  cout << "h1[\"cane\"] = " << h1["cane"] << endl;
  
  h1.resize(10);
  
  cout << endl << "After resizing" << endl << endl;
  
  cout << "h1[\"car\"] = " << h1["car"] << endl;
  cout << "h1[\"red\"] = " << h1["red"] << endl;
  cout << "h1[\"reel\"] = " << h1["reel"] << endl;
  cout << "h1[\"desk\"] = " << h1["desk"] << endl;
  cout << "h1[\"cavalier\"] = " << h1["cavalier"] << endl;
  cout << "h1[\"cane\"] = " << h1["cane"] << endl;
  
  
  myHash<int> h2(h1);
  
  myHash<int> h3;
  
  h3 = h2;
  
  cout << endl;
  
  cout << "h2[\"car\"] = " << h2["car"] << endl;
  cout << "h2[\"red\"] = " << h2["red"] << endl;
  cout << "h2[\"reel\"] = " << h2["reel"] << endl;
  cout << "h2[\"desk\"] = " << h2["desk"] << endl;
  cout << "h2[\"cavalier\"] = " << h2["cavalier"] << endl;
  cout << "h2[\"cane\"] = " << h2["cane"] << endl;
  
  cout << endl;
  
  cout << "h3[\"car\"] = " << h3["car"] << endl;
  cout << "h3[\"red\"] = " << h3["red"] << endl;
  cout << "h3[\"reel\"] = " << h3["reel"] << endl;
  cout << "h3[\"desk\"] = " << h3["desk"] << endl;
  cout << "h3[\"cavalier\"] = " << h3["cavalier"] << endl;
  cout << "h3[\"cane\"] = " << h3["cane"] << endl;
  
  cout << endl;
  
  return 0;
}


//--------------------------------------------------------------

///-----------------------------------------------------------------------------
/// default constructor
///@param init - size of hashtable, defaults to 10
///-----------------------------------------------------------------------------
template <class Type>
myHash<Type>::myHash(int init)
{
    size = init;
    myHashList = new node*[size];
    for (int i = 0; i < size; i++) {
        myHashList[i] = NULL;
    }
}

///-----------------------------------------------------------------------------
/// copy constructor
///@param copy - myHash object to create a deep copy of
///-----------------------------------------------------------------------------
template <class Type>
myHash<Type>::myHash(const myHash<Type>& copy)
{
    size = copy.size;
    myHashList = new node*[size];
    for (int i = 0; i < copy.size; i++) {
        if (copy.myHashList[i] == NULL) {   // if copy index is null, index is null
            myHashList[i] = NULL;
        } else {
            node *source = copy.myHashList[i];  // get copy index 
            node *newNode = new node;           // create new node
            newNode->key = source->key;         // copy source values into new
            newNode->item = source->item;
            newNode->link = source->link;
            myHashList[i] = newNode;            // add new node to list at index
            source = source->link;      // check next node
            if (source != NULL) {   // if index contains a second node
                newNode = new node; // repeat for second node
                newNode->key = source->key;
                newNode->item = source->item;
                newNode->link = source->link;
            }
        }
    }
}

///-----------------------------------------------------------------------------
/// assignment operator
///@param rhs - myHash object to set this to
///-----------------------------------------------------------------------------
template <class Type>
myHash<Type>& myHash<Type>::operator=(const myHash<Type>& rhs)
{
    if (this != &rhs)
    {
        destroyList();
        *this = myHash(rhs);
    }
  
  return *this;
}

///-----------------------------------------------------------------------------
/// [] operator
///@param searchKey - the key to search into the table for
///@return the item of the given key
///@brief uses hash function getIndex1 to search for key in table, if the index
/// is void or one node that isn't the key, insert the node and return the 
/// inserted element. If key isn't found and there are two nodes at index, use
/// getIndex2 to search alternate index, reapeating previous conditions. If 
/// collision, then index = (index + 1) % size.
///-----------------------------------------------------------------------------
template <class Type>
Type& myHash<Type>::operator[](std::string searchKey)
{
    bool found = false;
    int collisions = 0;
    int index = getIndex1(searchKey);
    
    while (!found) {
    if ( myHashList[index] == NULL ) {
        node *n = new node;
        n->key = searchKey;
        n->link = NULL;
        found = true;
    } else {
        if (myHashList[index]->key != searchKey) {
            if (myHashList[index]->link == NULL) {
                node *n = new node;
                n->key = searchKey;
                n->link = NULL;
                myHashList[index]->link = n;
                return myHashList[index]->link->item;
            } else {
                if (myHashList[index]->link->key == searchKey) {
                    return myHashList[index]->link->item;
                } else {
                    if (collisions == 0) {
                        index = getIndex2(searchKey);
                        collisions++;
                    } else {
                        index = (index + collisions) % size;
                    }
                }
            }
        }
    }
    }
    return myHashList[index]->item;
}

///-----------------------------------------------------------------------------
/// resize
///@param amount - the amount of additional indexes to be added to the table
///@brief resizes the table and rehashes all elements
///-----------------------------------------------------------------------------
template <class Type>
void myHash<Type>::resize(int amount)
{
    node ** oldTable = myHashList;
    size += amount;
    myHashList = new node * [size];
    // traverse all nodes in old table
    for ( int i = 0; i < size - amount; i++) {
        (*this)[oldTable[i]->key] = oldTable[i]->item;
    }
}

///-----------------------------------------------------------------------------
/// destructor
///@brief calls destroyList to deallocate memory
///-----------------------------------------------------------------------------
template <class Type>
myHash<Type>::~myHash()
{
    destroyList();
}

///-----------------------------------------------------------------------------
/// destroyList
///@brief deletes all nodes and deallocates all memory from list
///-----------------------------------------------------------------------------
template <class Type>
void myHash<Type>::destroyList()
{
    // delete members of each index
    for  (int i = 0; i < size; i++) {
        if (myHashList[i] != NULL) {
            if (myHashList[i]->link != NULL) {
                delete myHashList[i]->link;
            }
            delete myHashList[i];
        }
    }
    // delete list of indexes
    delete[] myHashList;
}

///-----------------------------------------------------------------------------
/// getIndex1 (primary hash function)
///@param str - string used to calculate index
///@return index for given string, first letter ascii value % table size
///-----------------------------------------------------------------------------
template <class Type>
int myHash<Type>::getIndex1(std::string str)
{
    return str[0] % size;
}

///-----------------------------------------------------------------------------
/// getIndex2 (secondary hash function)
///@param str - string used to calculate index
///@return index for given string, last letter ascii value % table size
///-----------------------------------------------------------------------------
template <class Type>
int myHash<Type>::getIndex2(std::string str)
{
    return str[str.length() - 1] % size;
}
