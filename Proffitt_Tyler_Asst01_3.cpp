///@author Tyler Proffitt

#include <vector>
#include <iostream>

using namespace std;

int main() {
    vector<int> v;
    int sizeOfList;
    int randomNum1;
    int randomNum2;
    
    cin >> sizeOfList;
    
    for (int i = 0; i < sizeOfList; i++) {      // populate list with numbers
        v.push_back(i + 1);                     //  1 to sizeOfList in order
    }
    
    for (int j = 0; j < sizeOfList; j++) {
        do {
            randomNum1 = rand() % sizeOfList;   // generate two random numbers
            randomNum2 = rand() % sizeOfList;   //  for indices into v
        }
        while (randomNum1 == randomNum2);       // check indices aren't equal
        
        swap(v[randomNum1], v[randomNum2]);     // swap the values at the indices
    }
    
/*    for (size_t k = 0; k < v.size(); k++) {
        cout << v[k] << endl;
    }
*/
    return 0;
}
