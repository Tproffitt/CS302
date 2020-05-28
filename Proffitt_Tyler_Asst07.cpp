///@author Tyler Proffitt
///@file Asst 07

#include <iostream>
#include <cstdlib>

using namespace std;

template <class Type>
class binMaxHeap
{
public:
  binMaxHeap(int = 10);
  binMaxHeap(const binMaxHeap<Type>&);
  ~binMaxHeap();
  binMaxHeap& operator=(const binMaxHeap<Type>&);
  void insert(const Type&);
  void deleteMax();
  Type getMax() const;
  bool isEmpty() const;
private:
  void bubbleUp(int);
  void bubbleDown(int);
  
  int capacity;
  int size;
  Type * heapArray;
};

struct stadiumRow
{
  int rowId;
  int seatsAvailable;
  
  bool operator<(stadiumRow rhs)
  {
    bool result = false;
    
    if ( seatsAvailable < rhs.seatsAvailable ){
        result = true;
    }
    return result;
  } 
  
  bool operator>(stadiumRow rhs)
  {
    bool result = false;
    
    if ( seatsAvailable > rhs.seatsAvailable ){
        result = true;
    }
    return result;
  }
  
};

/// ============================================================================
///         M   A   I   N
/// ============================================================================
int main()
{
    int fans, rows, moneyMade = 0;
    stadiumRow row;
    
    cin >> rows;                        // get number of rows
    cin >> fans;                        // get number of fans
    
    binMaxHeap<stadiumRow> tickets(rows);   // create heap
    
    // fill heap
    for (int i = 1; i <= rows; i++) {
        row.rowId = i;                  // set row number
        cin >> row.seatsAvailable;      // get seats value from stdIn
        tickets.insert(row);            // insert row into heap
    }
    
    int i = 0;          // counter for iterations (number of fans sold tickets)
    bool soldOut = false;   // flag for incase of empty heap
    while ( i < fans && !soldOut ) {
        if ( !tickets.isEmpty() ) {
            row = tickets.getMax();     // get the max from the heap
            tickets.deleteMax();        // remove max element from heap
            moneyMade += row.seatsAvailable;    // add seats from that row to sum
            row.seatsAvailable--;       // decrement seat in that row
            if ( row.seatsAvailable > 0 ) {
                tickets.insert(row);    // if seats remain, reinsert the row
            } else {                    // otherwise output that the row is full
                cout << "Row " << row.rowId << " has sold out!" << endl;
            }
        } else {                        // if heap is empty (all seats sold)
            cout << "All rows sold out!" << endl;   // output message
            soldOut = true;             // set flag to stop looping fans
        }
        i++;    // increment counter
    }
    
    // output total earnings
    cout << "\nMoney made: " << moneyMade << " pounds\n" << endl;
    
    return 0;
}

// *****************************************************************************
//          F U N C T I O N   D E F I N I T I O N S
// *****************************************************************************

///-----------------------------------------------------------------------------
/// default constructor
///@param capacity - the capacity for the heap being created
///@brief allocates an array of size capacity to heapArray pointer and sets cap
///-----------------------------------------------------------------------------
template <class Type>
binMaxHeap<Type>::binMaxHeap(int capacity)
{
    heapArray = new Type [capacity];
    this->capacity = capacity;
}

///-----------------------------------------------------------------------------
/// copy constructor
///@param copy - the heap object to make a deep copy of
///@brief makes a deep copy of the heap object passed in
///-----------------------------------------------------------------------------
template <class Type>
binMaxHeap<Type>::binMaxHeap(const binMaxHeap<Type>& copy)
{
    heapArray = new Type [copy.capacity];       // allocate memory
    for ( int i = 0; i <= copy.size; i++ ) {
        heapArray[i] = copy.heapArray[i];       // copy values from copy array
    }
    capacity = copy.capacity;                   // set capacity
}

///-----------------------------------------------------------------------------
/// destructor
///@brief deallocates the heap
///-----------------------------------------------------------------------------
template <class Type>
binMaxHeap<Type>::~binMaxHeap()
{
    delete[] heapArray;
}

///-----------------------------------------------------------------------------
/// assignment operator
///@param rhs = the heap object to copy
///@brief creates a deep copy of rhs into this heap
///-----------------------------------------------------------------------------
template <class Type>
binMaxHeap<Type>& binMaxHeap<Type>::operator=(const binMaxHeap<Type>& rhs)
{
    if ( this != rhs ) {                        // check for self assignment
        delete[] heapArray;                     // deallocate array
        heapArray = new Type [rhs.capacity];    // allocate space for new array
        for ( int i = 0; i <= rhs.size; i++ ) {
            heapArray[i] = rhs.heapArray[i];    // copy values from rhs
        }
    }
    
    return *this;
}

///-----------------------------------------------------------------------------
/// insert
///@param item - the value to be inserted
///@brief inserts item to the end of the heap array, increments size, and bubbles
/// up the inserted value
///-----------------------------------------------------------------------------
template <class Type>
void binMaxHeap<Type>::insert(const Type& item)
{
    if ( size == capacity ) {
        
    }
    heapArray[size] = item;                     // insert value
    size++;                                     // increment size
    bubbleUp(size - 1);                         // bubble up newly inserted item
}

///-----------------------------------------------------------------------------
/// deleteMax
///@brief replaces first item of heap array with last item and bubbles down the
/// new first item
///-----------------------------------------------------------------------------
template <class Type>
void binMaxHeap<Type>::deleteMax()
{
    heapArray[1] = heapArray[size - 1];     // replace first with last element
    size--;                                 // decrement size
    if ( !isEmpty() ) {
        bubbleDown(1);                      // bubble down if heap isn't empty
    }
}

///-----------------------------------------------------------------------------
/// getMax
///@brief returns heapArray[1] if heap isn't empty, returns meaningless object
/// at heapArray[0] otherwise
///-----------------------------------------------------------------------------
template <class Type>
Type binMaxHeap<Type>::getMax() const
{
    Type max = heapArray[0];            // max = random object at index 0
    if ( !isEmpty() ) {
        max = heapArray[1];             // if heap isn't empty max = index 1
    }
    
    return max;
}

///-----------------------------------------------------------------------------
/// isEmpty
///@brief returns true if size is 1 (meaning empty heap) and false otherwise
///-----------------------------------------------------------------------------
template <class Type>
bool binMaxHeap<Type>::isEmpty() const
{
    bool result = false;
    if ( size == 1) {                   // if size is 1, the heap is empty
        result = true;
    }
    return result;
}

///-----------------------------------------------------------------------------
/// bubbleUp
///@param x - index into the heap array
///@brief recursively bubbles the value at index x up to its parent's position
/// if it's greater than the parent
///-----------------------------------------------------------------------------
template <class Type>
void binMaxHeap<Type>::bubbleUp(int x)
{
    if ( x == 1 ) {                 // base case: index is the max index (root)
        return;
    }
    
    if ( heapArray[x] > heapArray[x / 2] ) {    // if x greater than parent
        swap( heapArray[x], heapArray[x / 2] );     // swap x and parent
        bubbleUp(x / 2);                            // bubble again
    }
}

///-----------------------------------------------------------------------------
/// bubbleDown
///@param x - index into the heap array
///@brief recursively bubbles the value at index x down to its greater child's
/// position if it's less than the child
///-----------------------------------------------------------------------------
template <class Type>
void binMaxHeap<Type>::bubbleDown(int x)
{
    if ( x * 2 > size ) {           // base case: index is a leaf
        return;
    }
    
    // check if x is less than one of its children
    if (heapArray[x] < heapArray[x * 2] || heapArray[x] < heapArray[x * 2 + 1]){
        if ( heapArray[x * 2] > heapArray[x * 2 + 1] ) {    // if right child greater
            swap( heapArray[x], heapArray[x * 2] );     // swap x and right child
            bubbleDown(x * 2);                          // bubble again
        } else {                                    // if left child greater
            swap( heapArray[x], heapArray[x * 2 + 1] ); // swap x and left child
            bubbleDown(x * 2 + 1);                      // bubble again
        }
    }
}
