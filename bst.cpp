#include <cstdlib>

template <class Type>
class bst
{
  struct binTreeNode
  {
    binTreeNode * left;
    binTreeNode * right;
    Type item;
  };
  
public:
  class binTreeIterator
  {
  public:
    friend class bst;
    binTreeIterator();
    binTreeIterator(binTreeNode*);
    bool operator==(binTreeNode*);
    bool operator==(binTreeIterator);
    binTreeIterator rightSide();
    binTreeIterator leftSide();
  private:
    binTreeNode * current;
  };
  
  bst();
  bst(const bst<Type>&);
  const bst& operator=(const bst<Type>&);
  ~bst();
  void insert(const Type&);
  binTreeIterator begin();
  binTreeIterator end();

private:
  binTreeNode* insert(binTreeNode*, const Type&);
  void destroyTree(binTreeNode*);
  void cloneTree(binTreeNode*, binTreeNode*);
  binTreeNode * root;
};

/**************************************************
FUNCTION NAME : binTreeIterator
PARAMETERS : N/A
RETURN TYPE : N/A
DESCRIPTION : default constructor for binTreeIterator object sets current to NULL
**************************************************/
template <class Type>
bst<Type>::binTreeIterator::binTreeIterator()
{
    current = NULL;
}

/**************************************************
FUNCTION NAME : binTreeIterator
PARAMETERS : c-pointer to a binTreeNode
RETURN TYPE : N/A
DESCRIPTION : itemized constructor for binTreeIterator sets current to the ptr c
**************************************************/
template <class Type>
bst<Type>::binTreeIterator::binTreeIterator(bst<Type>::binTreeNode * c)
{
    current = c;
}

/**************************************************
FUNCTION NAME : operator== (comparison operator)
PARAMETERS : rhs-pointer to binTreeNode that will be compared against
RETURN TYPE : bool
DESCRIPTION : overloaded == operator compares current to the node pointer rhs 
*           returns true if current equals the rhs pointer, false otherwise
**************************************************/
template <class Type>
bool bst<Type>::binTreeIterator::operator== (bst<Type>::binTreeNode * rhs)
{
    if (current == rhs) {
        return true;
    } else {
        return false;
    }
}

/**************************************************
FUNCTION NAME : operator== (comparison operator)
PARAMETERS : rhs-binTreeIterator that will compared against
RETURN TYPE :
DESCRIPTION : overloaded == operator compares current to the iterator rhs's
*           current, return true if equal, false otherwise
**************************************************/
template <class Type>
bool bst<Type>::binTreeIterator::operator== (bst<Type>::binTreeIterator rhs)
{
    if (current == rhs.current) {
        return true;
    } else {
        return false;
    }
}

/**************************************************
FUNCTION NAME : rightSide
PARAMETERS : none
RETURN TYPE : typename iterator object
DESCRIPTION : returns an iterator that is to the right child of the iterator that
*           calls it
**************************************************/
template <class Type>
typename bst<Type>::binTreeIterator bst<Type>::binTreeIterator::rightSide()
{
    binTreeIterator it(current->right);
    return it;
}

/**************************************************
FUNCTION NAME : leftSide
PARAMETERS : none
RETURN TYPE : typename iterator object
DESCRIPTION : returns an iterator that is to the left child of the iterator that
*           calls it
**************************************************/
template <class Type>		
typename bst<Type>::binTreeIterator bst<Type>::binTreeIterator::leftSide()
{
    binTreeIterator it(current->left);
    return it;
}

/**************************************************
FUNCTION NAME : bst
PARAMETERS : none
RETURN TYPE : N/A
DESCRIPTION : default constructor for bst class, sets root to NULL
**************************************************/
template <class Type>
bst<Type>::bst()
{
    root = NULL;
}

/**************************************************
FUNCTION NAME : bst
PARAMETERS : copy-bst object to be copied
RETURN TYPE : N/A
DESCRIPTION : copy constructor for bst, calls cloneTree to create a clone of copy
**************************************************/
template <class Type>
bst<Type>::bst(const bst<Type>& copy)
{
    cloneTree(root, copy.root);
}

/**************************************************
FUNCTION NAME : operator= (assignment operator)
PARAMETERS : rhs-bst object to be 
RETURN TYPE : bst this pointer
DESCRIPTION : assigns the values of rhs to this bst
**************************************************/
template <class Type>
const bst<Type>& bst<Type>::operator=(const bst<Type>& rhs)
{
  if (this != &rhs)     // check for self assignment
    {
        destroyTree(this);
        cloneTree(this, rhs);
    }
  
  return *this;
}

/**************************************************
FUNCTION NAME : ~bst()
PARAMETERS : none
RETURN TYPE : N/A
DESCRIPTION : Class destructor for bst, calls destroyTree
**************************************************/
template <class Type>
bst<Type>::~bst()
{
    destroyTree(root);
}

/**************************************************
FUNCTION NAME : insert
PARAMETERS : element-the item to be added to the bst
RETURN TYPE : void
DESCRIPTION : if tree is empty, inserts into root, else if tree isn't empty calls 
*           private insert
**************************************************/
template <class Type>
void bst<Type>::insert(const Type& element)
{
    if (root == NULL)
    {
        root = new binTreeNode;
        root->item = element;
        root->left = NULL;
        root->right = NULL;
        return;
    }
  
    if (root->item < element) {
        insert(root->right, element);
    } else {
        insert(root->left, element);
    }
    
    return;
}

/**************************************************
FUNCTION NAME : insert
PARAMETERS : r-pointer to bst node
*           element-the value to be inserted
RETURN TYPE : pointer to binTreeNode
DESCRIPTION : traverses the tree to find the spot to insert element and do so
**************************************************/
template <class Type>
typename bst<Type>::binTreeNode* bst<Type>::insert(bst<Type>::binTreeNode * r, const Type& element)
{
    if (r == NULL) {
        binTreeNode * tmp;
        tmp = new binTreeNode;
        tmp->item = element;
        tmp->left = NULL;
        tmp->right = NULL;
        return tmp;
    }
    if (r->item < element) {
        r->right = insert(r->right, element);
    } else {
        r->left = insert(r->left, element);
    }
    return r;
}

/**************************************************
FUNCTION NAME : begin
PARAMETERS : none
RETURN TYPE : binTreeIterator
DESCRIPTION : returns an iterator consaining the root pointer
**************************************************/
template <class Type>
typename bst<Type>::binTreeIterator bst<Type>::begin()
{
    return binTreeIterator(root);
}

/**************************************************
FUNCTION NAME : end
PARAMETERS : none
RETURN TYPE : binTreeIterator
DESCRIPTION : returns an iterator containing a NULL pointer
**************************************************/
template <class Type>
typename bst<Type>::binTreeIterator bst<Type>::end()
{
    return binTreeIterator(NULL);
}

/**************************************************
FUNCTION NAME : destroyTree
PARAMETERS : r-pointer to a bst node
RETURN TYPE : void
DESCRIPTION : recursively deletes nodes in a post order traversal
**************************************************/
template <class Type>
void bst<Type>::destroyTree(bst<Type>::binTreeNode * r)
{
    if (r != NULL) {
        destroyTree(r->left);
        destroyTree(r->right);
        delete r;
    }
}

/**************************************************
FUNCTION NAME : cloneTree
PARAMETERS : l-pointer to tree to be copied into
*           r-pointer to tree to be copied from
RETURN TYPE : void
DESCRIPTION : 
**************************************************/
template <class Type>
void bst<Type>::cloneTree(bst<Type>::binTreeNode * l, bst<Type>::binTreeNode * r)
{
    if (r->left != NULL) {
        binTreeNode * tmp;
        tmp = new binTreeNode;
        tmp->item = r->left;
        tmp->left = NULL;
        tmp->right = NULL;
        l->left = tmp;
        cloneTree(l->left, r->left);
    }
    if (r->right != NULL) {
        binTreeNode * tmp;
        tmp = new binTreeNode;
        tmp->item = r->left;
        tmp->left = NULL;
        tmp->right = NULL;
        l->right = tmp;
        cloneTree(l->right, r->right);
    }
}
