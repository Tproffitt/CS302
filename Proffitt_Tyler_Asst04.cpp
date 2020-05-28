///@author Tyler Proffitt
///@file Proffitt_Tyler_Asst04.cpp
///@brief Implement a sorting algorithm that will run in parallel using threads

#include <thread>
#include <vector>
#include <iostream>
#include <cstdlib>
#include <fstream>

using namespace std;

vector<int> list;               // global vector to be worked on

void swapAdj(unsigned int a, unsigned int b);

void mergeLists(unsigned int leftLeft, unsigned int leftRight, 
                unsigned int rightLeft, unsigned int rightRight);

/// ----------------------------------------------------------------------------
///@param args - the number of arguments passed, should be 4
///@param argv - a pointer to the array of passed argument as characters
///             1) the input file containing the numbers to be sorted
///             2) the output file to write the sorted array to
///             3) the size of the array
///             4) the maximum number of threads to spawn
///@brief takes in a series of integers from a file and performs a modified 
///         merge sort to sort the array and output it to the given file name
/// ----------------------------------------------------------------------------
int main(int args, char * argv[]){
    
    ifstream in(argv[1]);               // input file
    ofstream out(argv[2]);              // output file
    unsigned int listSize = atoi(argv[3]);       // number of integers in list
    unsigned int amountThreads = atoi(argv[4]);  // number of threads to create at a time
    
    vector<thread> threadPool;          // vector to hold all of the threads
    
    // populate the list from input file
    for (unsigned int n = 0; n < listSize; n++) {
        int temp;
        in >> temp;
        list.push_back(temp);
    }
   
    // perform swapAdj on all pairs of elements in list (ie (0,1), (2,3), etc)
    for (unsigned int i = 0; i < listSize; i += (2 * amountThreads)){
        for (unsigned int j = 0; j < amountThreads; j++) {
            threadPool.push_back(thread(swapAdj, i + (2 * j), i + (2 * j) + 1));
        }
        for (unsigned int j = 0; j < threadPool.size(); j++){
            threadPool[j].join();
        }
        
        threadPool.clear();     // clear the thread pool to allow spawning more
    }
    
    unsigned int ll, lr, rl, rr;
    
    // pass through list logn times with i increasing exponentially to listSize
    for (unsigned int i = 2; i <= listSize / 2; i *= 2) {    // i = size of sub array
        // initialize amountThreads # of threads to mergeLists for entire list
        for (unsigned int j = 0; j < listSize; j += (2 * i * amountThreads)) { 
            // create the threads amountThreads at a time
            for (unsigned int k = 0; k < amountThreads; k++) {
                // calculate the values for ll, lr, rl, rr
                ll = j;         // j = starting index of batch of threads
                ll = ll + ((2 * i) * k);    // ll += two sub arrays * # threads made
                lr = ll + i - 1;            // lr = ll plus sub array size - 1
                rl = lr + 1;
                rr = rl + i - 1;            // rr = rl plus sub array size - 1
                
                // in case out of range do not spawn more threads
                if (ll >= listSize || lr >= listSize || rl >= listSize 
                    || rr >= listSize){
                    break;
                }
                
                // merges all the sub arrays
                threadPool.push_back(thread(mergeLists, ll, lr, rl, rr));
            }
            // join all the threads
            for (unsigned int k = 0; k < threadPool.size(); k++) {
                threadPool[k].join();
            }
            
            // clear thread pool to make room for more threads
            threadPool.clear();
        }
    }
    
    // write sorted list to output file
    for (unsigned int x = 0; x < list.size(); x++) {
        out << list[x] << endl;
    }
    
    return 0;
}

/// ----------------------------------------------------------------------------
///@param a - an index into an array
///@param b - an index into an array
///@brief compares items list[a] and list[b] and if list[a] > list[b] then swap
///         list[a] and list[b]
/// ----------------------------------------------------------------------------
void swapAdj(unsigned int a, unsigned int b) {
    if (list[a] > list[b]) {
        swap(list[a], list[b]);
    }
}

/// ----------------------------------------------------------------------------
///@param leftLeft - the left bound of the left array
///@param leftRight - the right bound of the right array
///@param rightLeft - the left bound of the right array
///@param rightRight - the right bound of the right array
///@brief merges sub arrays [leftLeft...leftRight] and [rightLeft...rightRight]
///         so that the new sub array [leftLeft...rightRight] is in order
/// ----------------------------------------------------------------------------
void mergeLists(unsigned int leftLeft, unsigned int leftRight, 
                unsigned int rightLeft, unsigned int rightRight) {

    unsigned int length = leftRight -leftLeft + 1;  // calc length of sub arrays

    vector<int> temp1;                      // temp array for [ll...lr]
    vector<int> temp2;                      // temp array for [rl...rr]
    unsigned int i;                         // index for traversing temp array 1
    unsigned int j;                         // index for traversing temp array 2
    
    for (i = 0; i < length; i++) {  // populate left temp array
        temp1.push_back(list[leftLeft + i]);
    }
    for (j = 0; j < length; j++) {  // populate right temp array
        temp2.push_back(list[rightLeft + j]);
    }
    
    i = 0;
    j = 0;
    
    // merge temp1 and temp2, inserting the lower value of temp1[i] and temp2[j]
    //  into the list at list[offset + i + j] and incrementing the respective 
    //  index(i or j) until one goes out of bounds
    while (i < length && j < length) {
        if (temp1[i] <= temp2[j]) {
            list[leftLeft + i + j] = temp1[i];
            i++;
        } else {
            list[leftLeft + i + j] = temp2[j];
            j++;
        }
    }
    
    while (i < length) {        // move remaining elements of left temp if any
        list[leftLeft + i + j] = temp1[i];
        i++;
    }
    while (j < length) {        // move remaining elements of right temp if any
        list[leftLeft + i + j] = temp2[j];
        j++;
    }
}
