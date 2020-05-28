///@author Tyler Proffitt

#include <vector>
#include <iostream>

using namespace std;

int main() {
    vector<int> v;
    vector<bool> checker;
    int sizeOfList;
    int randomNum;
    
    cin >> sizeOfList;
    
    checker.resize(sizeOfList);                 // size loopup array to sizeOfList
    
    for (int i = 0; i < sizeOfList; i++) {
        bool inserted = false;
        while (!inserted) {                 // loop until number is added to v
            randomNum = rand() % sizeOfList + 1;    // generate random number
            if (checker[randomNum - 1] == false) {  // if the coresponding loopup
                v.push_back(randomNum);             //  index is false, insert num,
                checker[randomNum - 1] = true;      //  set loopup to true
                inserted = true;                    // set flag to leave loop
            }
        }
    }
    
/*    for (size_t j = 0; j < v.size(); j++) {
        cout << v[j] << endl;
    }
*/    
    return 0;
}
