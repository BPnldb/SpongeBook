/*
* WEIYUAN CHEN, Christopher Gentibano

* CIS 22C, Lab 8
*/


#ifndef BST_H_
#define BST_H_

#include <cstddef>
#include <string>
#include <assert.h>

using namespace std;
template<typename bstdata>

class BST {
private:
    struct Node {
        bstdata data;
        Node* left;
        Node* right;

        Node(bstdata newdata){
            data = newdata;
            left = NULL;
            right = NULL;
        }
    };

    Node* root;

    /**Private helper functions*/
    void insertNode(Node* root, bstdata data);
    //private helper function for insert
    //recursively inserts a value into the BST

    void inOrderPrint(ostream& out, Node* root) const;
    //private helper function for inOrderPrint
    //recursively prints tree values in order from smallest to largest

    void preOrderPrint(ostream& out, Node* root) const;
    //private helper function for preOrderPrint
    //recursively prints tree values in pre order

    void postOrderPrint(ostream& out, Node* root) const;
    //private helper function for postOrderPrint
    //recursively prints tree values in post order

    void copyNode(Node* copy);
    //recursive helper function to the copy constructor

    void freeNode(Node* root);
    //private helper function for the destructor
    //recursively frees the memory in the BST

    bool searchNode(Node* root, bstdata data) const;
    //recursive helper function to search
    //returns whether the value is found in the tree

    bstdata minimum(Node* root) const;
    //recursive helper function to minimum
    //returns the minimum value in the tree

    bstdata maximum(Node* root) const;
    //recursive helper function to maximum
    //returns the maximum value in the tree

    Node* removeNode(Node* root, bstdata data);
    //recursive helper function to remove
    //removes data from the tree

    void getSize(Node* root, int& size) const;
    //recursive helper function to the size function
    //calculates the size of the tree
    //stores the result in size

    int getHeight(Node* root) const;
    //recursive helper function to the height function
    //returns the height of the tree

public:

    /**constructors and destructor*/

    BST();
    //Instantiates a new BST

    BST(const BST &bst);
    //copy constructor

    ~BST();
    //deallocates the tree memory

    /**access functions*/

    bstdata minimum() const;
    //returns the minimum value in the BST
    //pre: !empty()

    bstdata maximum() const;
    //returns the maximum value in the BST
    //pre: !empty()

    bool isEmpty() const;
    //determines whether the BST is empty

    int getSize() const;
    //returns the size of the tree

    bstdata getRoot() const;
    //returns the value stored at the root of the BST
    //pre: !isEmpty()

    int getHeight() const;
    //returns the height of the tree

    bool search(bstdata data) const;
    //returns whether the data is found in the tree
    //pre: !isEmpty()

    /**manipulation procedures*/

    void insert(bstdata data);
    //inserts new data into the BST

    void remove(bstdata data);
    //removes the specified value from the tree
    //pre: data is located in the tree
    //pre: !isEmpty()

    /**additional functions*/

    void inOrderPrint(ostream& out) const;
    //calls the inOrderPrint function to print out the values
    //stored in the BST

    void preOrderPrint(ostream& out) const;
    //calls the reOrderPrint function to print out the values
    //stored in the BST

    void postOrderPrint(ostream& out) const;
    //calls the postOrderPrint function to print out the values
    //stored in the BST
};


/***				Constructors and destructors				***/

//default Constructors
template<class bstdata>
BST<bstdata>::BST()
{
	root = NULL;
}


// copy constructor
template <class bstdata>
BST <bstdata>::BST(const BST &bst)
{
	root = NULL;

	if(bst.root != NULL) // if original tree is not empty
		copyNode(bst.root);
}

// copy constructor private helper function
template <class bstdata>
void BST<bstdata>::copyNode(Node* copy)
{
	if(copy != NULL) // if parent in copy not pointing to NULL
	{
		if(root == NULL) // if root is empty
			root = new Node(copy->data);
		else
		{
			insertNode(root, copy->data); // call insertNode private helper function
		}
		copyNode(copy->left); // recursive to left
		copyNode(copy->right); // recursive to right
	}
}

//destructors
template<class bstdata>
BST<bstdata>::~BST()
{
	freeNode(root);
}

//destructors private helper function
template<class bstdata>
void BST<bstdata>::freeNode(Node* root)
{
	if(root != NULL)
	{
		freeNode(root->left);
		freeNode(root->right);
		delete root;
	}
}

/**manipulation procedures*/

//public insert function
template<class bstdata>
void BST<bstdata>::insert(bstdata data)
{
	if(root == NULL) // if tree is empty
	{
		root = new Node(data);
	}
	else
		insertNode(root, data);
}

//insert private helper function
template<class bstdata>
void BST<bstdata>::insertNode(Node* root, bstdata data)
{
	if(data == root->data) // no duplicated data
		return;
	else if(data < root->data) // go to left subtree
	{
		if(root->left == NULL)
			root->left = new Node(data);
		else
			insertNode(root->left, data);
	}
	else // go to right subtree
	{
		if(root->right == NULL)
			root->right = new Node(data);
		else
			insertNode(root->right, data);
	}
}

//remove a data from tree
template<class bstdata>
void BST<bstdata>::remove(bstdata data)
{
	assert(!isEmpty()); //tree can't be empty
	assert(search(data)); // data has to be in the tree
	removeNode(root, data);
}

//private helper for remove
template<class bstdata>
typename BST<bstdata>::Node* BST<bstdata>::removeNode(Node* root, bstdata data)
{
	if(root == NULL) //prevent comparing data with NULL
		return root;
	else if(data < root->data) //to left subtree
		root->left = removeNode(root->left, data);
	else if(data > root->data) //to right subtree
		root->right = removeNode(root->right, data);
	else
	{
		if(root->left == NULL && root->right == NULL) //if the parent root is leaf
		{
			delete root;
			root = NULL;
		}
		else if(root->left != NULL && root->right == NULL) //if the parent root has only left child
		{
			Node* temp = root;
			root = root->left;
			delete temp;
		}
		else if(root->right != NULL && root->left == NULL) //if the parent root has only right child
		{
			Node* temp = root;
			root = root->right;
			delete temp;
		}
		else // //if the parent root has both left and right child
		{
			root->data = minimum(root->right);
			root->right = removeNode(root->right, minimum(root->right));
		}
	}
	return root; //return the parent root at that parent
}

/**additional functions*/

//print in sorted order : left - node -right
template<class bstdata>
void BST<bstdata>::inOrderPrint(ostream& out) const
{
	inOrderPrint(out, root);
	out << endl;
}

//inorder print private helper function
template<class bstdata>
void BST<bstdata>::inOrderPrint(ostream& out, Node* root) const
{
	if(root != NULL)
	{
		inOrderPrint(out, root->left);
		out << root->data << endl;
		inOrderPrint(out, root->right);
	}
}

//print in preorder : node - left - right
template<class bstdata>
void BST<bstdata>::preOrderPrint(ostream& out) const
{
	preOrderPrint(out, root);
	out << endl;
}

//preoreder private helper
template<class bstdata>
void BST<bstdata>::preOrderPrint(ostream& out, Node* root) const
{
	if(root != NULL)
	{
		out << root->data <<" ";
		preOrderPrint(out, root->left);
		preOrderPrint(out, root->right);
	}
}

//print in postorder : left - right - node
template<class bstdata>
void BST<bstdata>::postOrderPrint(ostream& out) const
{
	postOrderPrint(out, root);
	out << endl;
}

//postorder print private hepler function
template<class bstdata>
void BST<bstdata>::postOrderPrint(ostream& out, Node* root) const
{
	if(root != NULL)
	{
		postOrderPrint(out, root->left);
		postOrderPrint(out, root->right);
		out << root->data <<" ";
	}
}

/**access functions*/

//get the data of the root of the tree
template<class bstdata>
bstdata BST<bstdata>::getRoot() const
{
	assert(root != NULL);
	return root->data;
}

//check whether the tree is empty
template<class bstdata>
bool BST<bstdata>::isEmpty() const
{
	return root == NULL;
}

//public get the number of nodes in the tree
template<class bstdata>
int BST<bstdata>::getSize() const
{
	int size = 0;
	getSize(root, size);
	return size;
}

//private helper for getSize
template<class bstdata>
void BST<bstdata>::getSize(Node* root, int& size) const
{
	if(root != NULL)
	{
		size++;
		getSize(root->left, size);
		getSize(root->right, size);
	}

}

//public wrapper to get the height of the root
template<class bstdata>
int BST<bstdata>::getHeight() const
{
	return getHeight(root);
}

//private helper for getHeight
template<class bstdata>
int BST<bstdata>::getHeight(Node* root) const
{
	if(root == NULL) // null is -1 height
		return -1;
	int left = 1 + getHeight(root->left);
	int right = 1 + getHeight(root->right);

	if (left > right)
		return left ;
	else
		return right ;
}

//to find to smallest value of the tree
template<class bstdata>
bstdata BST<bstdata>::minimum() const
{
	assert(!isEmpty());
	return minimum(root);
}

//private helper for minimum
template<class bstdata>
bstdata BST<bstdata>::minimum(Node* root) const
{
	if(root->left != NULL) // smallest value always on the left subtree
		return minimum(root->left);
	else
		return root->data;
}

//to find to largest value of the tree
template<class bstdata>
bstdata BST<bstdata>::maximum() const
{
	assert(!isEmpty());
	return maximum(root);
}

//private helper for maximum
template<class bstdata>
bstdata BST<bstdata>::maximum(Node* root) const
{
	if(root->right != NULL) // largest value always on the subtree
		return maximum(root->right);
	else
		return root->data;
}

//searching for data
template<class bstdata>
bool BST<bstdata>::search(bstdata data) const
{
	assert(!isEmpty());
	return searchNode(root, data);
}

//private helper for search
template<class bstdata>
bool BST<bstdata>::searchNode(Node* root, bstdata data) const
{
	if(data == root->data)// found the data
		return true;
	else if(data < root->data) // going to left subtree
		{
			if(root->left == NULL)//not found
				return false;
			else
				return searchNode(root->left, data);
		}
	else // going to right subtree
		{
			if(root->right == NULL) //not found
				return false;
			else
				return searchNode(root->right, data);
		}
}
#endif /* BST_H_ */
