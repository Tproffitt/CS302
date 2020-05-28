///@author Tyler Proffitt
///@file Assignment 05

#include <iostream>
#include <cstdlib>
#include "bst.cpp"

using namespace std;

int findMaxEnemyTakeOuts(bst<int>::binTreeIterator);

int main()
{
    bst<int> * binSearchTree;
    bst<int>::binTreeIterator it;   // 
    int cases;          // variable to hold number of test cases
    int edgeId;         // variable to hold values for tree nodes
    
    cin >> cases;       // get number of test cases
    
    binSearchTree = new bst<int>[cases];    // create array of trees for tests
  
    for (int i = 0; i < cases; i++) {
        cin >> edgeId;              // get first value for tree
        while (edgeId != -1) {      // get values until reaching end case: -1
            binSearchTree[i].insert(edgeId);    // insert node
            cin >> edgeId;          // get next value for tree
        }
        
        it = binSearchTree[i].begin();  // get iterator to root of tree

        cout << "Case " << i + 1 << " : ";
        cout << findMaxEnemyTakeOuts(it) + 1 << endl;
    }
    
    return 0;
}

int findMaxEnemyTakeOuts(bst<int>::binTreeIterator it)
{
    int l = 0;
    int r = 0;
    if (!(it.leftSide() == NULL)) {     // if left child isn't NULL
        l = 1 + findMaxEnemyTakeOuts(it.leftSide());    // increment l and recurse
    }
    if (!(it.rightSide() == NULL)) {    // if right child isn't NULL
        r = findMaxEnemyTakeOuts(it.rightSide());       // recurse down right side
    }
    
    // return the greater value of l and r
    if ( l > r ) {
        return l;
    } else {
        return r;
    }
}
