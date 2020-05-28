///@author Tyler Proffitt

#include <vector>
#include <iostream>

using namespace std;

int main() {
    vector<int> v;
    int sizeOfList;
    int randomNum;
    
    cin >> sizeOfList;
    
    for (int i = 0; i < sizeOfList; i++) {
        bool found = true;                          // reset flag
        while (found) {
            found = false;
            randomNum = rand() % sizeOfList + 1;    // generate random number
            for (size_t j = 0; j < v.size(); j++) { // iterate through array
                if (v[j] == randomNum) {    // if generated number is already in
                    found = true;           //  array, set flag to continue looping
                }                           //  and generate new number and try again
            }
        }
        v.push_back(randomNum); // if num isn't in array, exit loop and add it
    }
    
 /*   for (size_t k = 0; k < v.size(); k++) {
        cout << v[k] << endl;
    }
*/    
    return 0;
}
