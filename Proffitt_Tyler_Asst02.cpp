#include <iostream>
using namespace std;

template <class Type>
class myStack
{
public:
  myStack();
  myStack(const myStack<Type>&);
  const myStack<Type>& operator=(const myStack<Type>&);
  ~myStack();
  
  void push(const Type&);
  void pop();
  void pop(Type&);
  Type top() const;
  bool isEmpty() const;
  
private:
  struct node
  {
    Type item;
    node * next;
  };
  
  node * topOfmyStack;
};

template <class Type>
myStack<Type>::myStack()
{
  
}

template <class Type>
myStack<Type>::myStack(const myStack<Type>& copy)
{
  
}

template<class Type>
const myStack<Type>& myStack<Type>::operator=(const myStack<Type>& rhs)
{
  if (this != &rhs)
    {
      
    }
  return *this;
}

template<class Type>
myStack<Type>::~myStack()
{
  
}

template <class Type>
void myStack<Type>::push(const Type& insert)
{
  
}

template <class Type>
void myStack<Type>::pop()
{
  
}

template <class Type>
void myStack<Type>::pop(Type& item)
{
  
}

template <class Type>
Type myStack<Type>::top() const
{
  
}

template <class Type>
bool myStack<Type>::isEmpty() const
{
  
}

int main()
{
  
  return 0;
}
