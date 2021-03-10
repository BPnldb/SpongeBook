/*
* WEIYUAN CHEN, Christopher Gentibano

* CIS 22C, Lab 8
*/

#ifndef LIST_H_
#define LIST_H_
#include <iostream>
#include <cstddef> //for NULL
#include <assert.h> //for assert
using namespace std;


template <class listdata> //list stores generic listdata, not any specific C++ type
class List {

private:
    struct Node {
        listdata data;
        Node* next;
        Node* prev;

        Node(listdata newData){
            data = newData;
            next = NULL;
            prev = NULL;
        }
    };

    Node* first;
    Node* last;
    Node* iterator;
    int length;

    void reversePrint(Node* node) const;
    //Helper function for the public reversePrint() function.
    //Recursively prints the data in a List in reverse.

    bool isSorted(Node* node) const;
    //Helper function for the public isSorted() function.
    //Recursively determines whether a list is sorted in ascending order.

    int binarySearch(int low, int high, listdata data) const;
    //Recursively search the list by dividing the search space in half
    //Returns the index of the element, if it is found in the List
    //Returns -1 if the element is not in the List
    //Post: The iterator location has not been changed

public:

    /**Constructors and Destructors*/

    List();
    //Default constructor; initializes and empty list
    //Postcondition: initialize the fields inside the list class with a starting value

    List(const List &list);
    //copy constructor; create a separated but identical linked list
    //postcondition: if the list is empty, pointers to NULL, else starts copy node.

    ~List();
    //Destructor. Frees memory allocated to the list
    //Postcondition: delete the nodes in the linked list

    /**Accessors*/

    listdata getFirst() const;
    //Returns the first data in the list
    //Precondition: the linked list must not be empty

    listdata getLast() const;
    //Returns the last data in the list
    //Precondition: the linked list must not be empty

    bool isEmpty() const;
    //Determines whether a list is empty.

    int getLength() const;
    //Returns the size of the list

    listdata getIterator() const;
    //get the data that iterator pointing to
    //Precondition: iterator != NULL
    //Postcondition: return the data of the node

    bool offEnd() const;
    //check whether the node is pointing to NULL
    //Postcondition: return true if pointing NULL, false if not pointing to NULL

    bool operator==(const List& list);
    //check whether two linked lists are the same
    //return true is it's the same, false if it's not the same

    bool isSorted() const;
    //Wrapper function that calls the isSorted helper function to determine whether
    //a list is sorted in ascending order.
    //We will consider that a list is trivially sorted if it is empty.
    //Therefore, no precondition is needed for this function

    int getIndex() const;
    //Indicates the index of the Node where the iterator is currently pointing
    //Nodes are numbered starting at 1 through the size of the list
    //Pre: !offEnd()

    int linearSearch(listdata data) const;
    //Searchs the list, element by element, from the start of the List to the end of the List
    //Returns the index of the element, if it is found in the List
    //Does not call the indexing functions in the implementation
    //Returns -1 if the element is not in the List
    //Pre: length != 0
    //Post: The iterator location has not been changed

    int binarySearch(listdata data) const;
    //Returns the index where data is located in the List
    //Calls the private helper function binarySearch to perform the search
    //Pre: length != 0
    //Pre: List is sorted (must test on a sorted list)
    //Post: The iterator location has not been changed

    /**Manipulation Procedures*/

    void removeFirst();
    //Removes the value stored in first node in the list
    //Precondition: the linked list must not be empty
    //Postcondition: remove the first node in the linked list

    void removeLast();
    //Removes the value stored in the last node in the list
    //Precondition: the linked list must not be empty
    //Postcondition: remove the last node in the linked list

    void insertFirst (listdata data);
    //Inserts a new data at the beginning of the list
    //If the list is empty, the new data becomes both first and last
    //Postcondition: if the list is not empty, the new data is updated to be the first node of the list

    void insertLast(listdata data);
    //Inserts a new data at the end of the list
    //If the list is empty, the new data becomes both first and last
    //Postcondition:if the list is not empty, the new data is updated to be the last node of the list

    void startIterator();
    //iterator point the first node of the list
    //Precondition: the linked list must not be empty
    //Postcondition: iterator points to first

    void removeIterator();
    //remove the node that iterator pointing to
    //Precondition: iterator != NULL
    //Postcondition: case1 - to remove the first node, case2 - to remove the last node, case3 - remove the node between middle

    void insertIterator(listdata data);
    //insert the node in the position that iterator pointing to
    //Precondition: iterator != NULL
    //Postcondition: two cases to insert a node through iterator

    void advanceIterator();
    //move iterator to point to next node
    //Precondition: iterator != NULL
    //Postcondition: iterator point to next node

    void reverseIterator();
    //move iterator to point to next node
    //Precondition: iterator != NULL
    //Postcondition: two cases to insert a node through iterator

    void advanceToIndex(int index);
    //Moves the iterator to the node whose index number is specified in the parameter
    //Nodes are numbered starting at 1 through the size of the List
    //Pre: size != 0
    //Pre: index <= size

    /**Additional List Operations*/

    void printList(ostream &out) const;
    //Prints to the console the value of each data in the list sequentially
    //and separated by a blank space
    //Prints nothing if the list is empty
    //Prints a empty newline character if it's empty..


    void printNumberedList() const;
    //printing the list in the format below
    // #. data of the node


    void reversePrint() const;
    //Wrapper function that calls the reverse helper function to print a list in reverse
    //prints nothing if the List is empty



};

//Constructor -- giving default values
template <class listdata>
List<listdata>::List()
{
	first = NULL;
	last = NULL;
	iterator = NULL;
	length = 0;
}

//copy constructor
template <class listdata>
List<listdata>::List(const List &list)
{

    if(list.first == NULL) //If the original list is empty, make an empty list for this list
    {
        first = last = iterator = NULL;
    }
    else
    {
        first = new Node(list.first->data); //calling Node constructor
        Node* temp = list.first; //set a temporary node pointer to point at the first of the original list
        iterator = first; //set iterator to point to first node of the new list

        while(temp->next != NULL)
        {

            temp = temp->next; //advance up to the next node in the original list
            iterator->next = new Node(temp->data); //using node constructor to create new node w/ copy of data
            iterator->next->prev = iterator; // build the doubly link list
            iterator = iterator->next; //advance to this new node

        }

        last = iterator; //update the last pointer to the last of the list
        iterator = NULL;

    }

    length = list.length;
}

//Destructor
template <class listdata>
List<listdata>::~List()
{
    Node* b = first;
    Node* a = NULL; //a stands for "after" (i.e. after b)
    while (b != NULL)
    {
        a = b->next; //move a to node after b
        delete b; //remove b (you know it is not NULL from if)
        b = a; //b "catches up" with a (both point to same place in list)
    }
}

//print the values of the linked list
template <class listdata>
void List<listdata>::printList(ostream &out) const
{
    Node* temp = first; //create a temporary iterator
    while (temp != NULL)
    {
    	out << temp->data <<" ";
    	temp = temp->next;

    }
    out << endl; //go to next line.

}

//insert a new node that will become the first node of the list
template <class listdata>
void List<listdata>::insertFirst(listdata data)
{
    Node* N = new Node(data);//create a new node
    if (length == 0)//if list is empty
    {
        first = N;
        last = N;
    }
    else// if list is not empty
    {
        N->next = first;
        first->prev = N;
        first = N;
    }
    length++;
}

//insert a new node that will become the last node of the list
template <class listdata>
void List<listdata>::insertLast(listdata data)
{
    Node* N = new Node(data);//create a new node
    if (length == 0)//if list is empty
    {
        first = N;
        last = N;
    }
    else//if list is not empty
    {
        last->next = N;
        N->prev = last;
        last = N;
    }
    length++;
}

//remove the first node of the list
template <class listdata>
void List<listdata>::removeFirst()
{

    assert(length !=0 );
    if(length == 1)//only one node in the list
    {
        delete first;
        first = last = NULL;
    }
    else//more than one nodes in the list
    {
        Node* temp = first;
        first = first->next;
        first->prev = NULL;
        delete temp;
    }
    iterator = NULL;
    length--;
}

//remove the last node of the list
template <class listdata>
void List<listdata>::removeLast()
{

    assert(length != 0);
    if (length == 1)//only one node in the list
    {
    	delete last;
    	first = last = NULL;
    }
    else//more than one nodes in the list
    {
        Node* temp = last;
        last = last->prev;
        delete temp;
        last->next = NULL; //set new last pointer to point at NULL rather than deallocated memory
    }
    iterator = NULL;
    length--;

}

//to check is list empty or not.
template <class listdata>
bool List<listdata>::isEmpty() const
{
	return length == 0;
}

//get how many nodes in the list
template <class listdata>
int List<listdata>::getLength() const
{
	return length;
}

//get the data of the first node
template <class listdata>
listdata List<listdata>::getFirst() const
{
	assert(length != 0);
	return first->data;
}

//get the data of the last node
template <class listdata>
listdata List<listdata>::getLast() const
{
	assert(length != 0);
	return last->data;
}

//make iterator point to the first node
template <class listdata>
void List<listdata>::startIterator()
{
	assert(length != 0);
	iterator = first;
}

//iterator points to next node
template <class listdata>
void List<listdata>::advanceIterator()
{
	assert(iterator != NULL);
	iterator = iterator->next;
}

//iterator points to previous node
template <class listdata>
void List<listdata>::reverseIterator()
{
	assert(iterator != NULL);
	iterator = iterator->prev;
}

//insert a new node after the node that iterator pointing to
template <class listdata>
void List<listdata>::insertIterator(listdata data)
{
	assert(!offEnd());//iterator != NULL

	if(iterator == last)//data becoming the last node of the list
	{
		insertLast(data);
	}
	else
	{
		Node *N = new Node(data);
		N->next = iterator->next;
		N->prev = iterator;
		N->next->prev = N;
		iterator->next = N;
		length ++;
	}

}

//if iterator is pointing to NULL
template <class listdata>
bool List<listdata>::offEnd() const
{
	return iterator == NULL;
}

//get the data of the node that iterator pointing to
template <class listdata>
listdata List<listdata>::getIterator() const
{
	assert(iterator != NULL);
	return iterator->data;
}

//remove the node that iterator pointing to
template <class listdata>
void List<listdata>::removeIterator()
{
	assert(iterator != NULL);

	if(iterator == first)//remove the first node of the list
	{
		removeFirst();
	}
	else if(iterator == last)//remove the last node of the list
	{
		removeLast();
	}
	else// remove the middle node
	{
		iterator->prev->next = iterator->next;
		iterator->next->prev = iterator->prev;
		delete iterator;
		iterator = NULL;
		length --;
	}
}

//print the node in the format #. data
template <class listdata>
void List<listdata>::printNumberedList() const
{
	Node* temp = first;
	int num = 0;
	while(temp != NULL)
	{
		num ++;
		cout << num << ". " << temp->data <<endl;
		temp = temp->next;
	}
	cout << endl;

}

//check if two list are the same
template <class listdata>
bool List<listdata>::operator==(const List& list)// if two length are not equal
{
    if(length != list.length)
        return false;
    Node* temp1 = first;
    Node* temp2 = list.first;
    while(temp1 != NULL)
    {
        if(temp1->data != temp2->data)//if one of the data are not equal
            return false;
        temp1 = temp1->next;
        temp2 = temp2->next;
    }
    return true;
}

//calling the private reversePrint function
template <class listdata>
void List<listdata>::reversePrint() const
{
	reversePrint(last);
}

//print the list reversely by using recursion
template <class listdata>
void List<listdata>::reversePrint(Node* node) const
{
	if(node != NULL)//print the data until reach to NULL
	{
		cout << node->data << " ";
		return reversePrint(node->prev);
	}
	else
		cout << endl; // empty line or skip a line
}

//calling private isSorted function
template <class listdata>
bool List<listdata>::isSorted() const
{
	if(isSorted(first))
		return true;
	else
		return false;
}

//check the list whether is sorted by recursion
template <class listdata>
bool List<listdata>::isSorted(Node* node) const
{
	if(node == NULL) // if list is empty
		return true;
	else if(node == last) // when node reach the last node, should be always sorted
	{
		return true;
	}
	else if(node->data < node->next->data)// comparing current node and the next node, if current node <= next node, go into recursion
	{
		return isSorted(node->next);
	}
	else if(node->data == node->next->data)
	{
		return isSorted(node->next);
	}
	else
		return false;
}

//get the index of the node that iterator pointing to
template <class listdata>
int List<listdata>::getIndex() const
{
	assert(!offEnd());//iterator can't be NULL

	int count = 1; //counting the index
	Node* temp = first;
	while(temp != iterator)
	{
		temp = temp->next;
		count ++;
	}
	return count;
}

//move iterator to the node with a indicating index
template <class listdata>
void List<listdata>::advanceToIndex(int index)
{
	assert(length != 0);//length can't be 0
	assert(index <= length);//index can't lager than length

	int count = 1;
	startIterator();
	while(count != index)// moving the iterator
	{
		advanceIterator();
		count ++;
	}
}

//searching a data by linearSearch
template <class listdata>
int List<listdata>::linearSearch(listdata data) const
{
	assert(length != 0);//length can't be 0

	Node* temp = first;
	int index = 1;
	while(temp != NULL) // walking the temp from last to NULL
	{
		if(temp->data == data) // if found the target
			return index;
		index ++;
		temp = temp->next;
	}
		return -1; // not found
}

//calling the private binarySearch function
template <class listdata>
int List<listdata>::binarySearch(listdata data) const
{
	assert(length != 0); //length can't be 0
	assert(isSorted()); //list must be sorted

	return binarySearch(1, length, data);
}

//searching data by binarySearch, return data or -1 for not found
template <class listdata>
int List<listdata>::binarySearch(int low, int high, listdata data) const
{
	if(high < low)
		return -1;
	int mid = low + (high - low) / 2; // middle position
	Node* temp = first;
	for(int i = 1; i < mid; i++)//move temp to the mid position
	{
		temp = temp->next;
	}
	if(temp->data == data)//if mid data == target
		return mid;
	else if(temp->data > data)// if target on the left side
		return binarySearch(low, high - 1, data);
	else                      // if target on the right side
		return binarySearch(low + 1, high, data);
}
#endif /* LIST_H_ */
