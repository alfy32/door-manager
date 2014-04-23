#ifndef ALFY_LIST_SORTED_H
#define ALFY_LIST_SORTED_H

template<typename Key, typename Value>
class Alfy_List_Sorted
{
private:
	struct Node			//structure for the nodes of the list
	{
		Key key;
		Value value;
		Node *next;
	};

	Node *head;			//head to keep track of list
	int size;			//keeps track of the size of the list
public:
	//default constructor
	Alfy_List_Sorted():head(0),size(0) {};

	//add a node in order
	void push(Key keyValue, Value value);

	void pop();				//removes the last node
	void clear();			//deletes all the nodes in the list
	bool isEmpty();			//reports whether the list is empty

	const Node &getFirst()	//reads the first node
	{
		if(size > 0)
			return *head;
		else
			throw "It's empty.";
	};
};

template<typename Key, typename Value>
void Alfy_List_Sorted<Key,Value>::push(Key keyValue, Value value)
{
	//create the new node
	Node *newNode = new Node;
	newNode->key = keyValue;
	newNode->value = value;
	newNode->next = 0;

	//increment the size of the list
	size++;

	//*******************************
	//if the list is empty
	//*******************************
	if(head == 0)
	{
		head = newNode;
	}
	//*******************************
	//if there is only one node
	//*******************************
	else if(head->next == 0)
	{
		//if the new item goes before the head item
		if(newNode->key < head->key)
		{
			newNode->next = head;
			head = newNode;
		}
		//if the new item is the same or greater and goes after the one item
		else
			head->next = newNode;
	}
	//*******************************
	//if there are two or more nodes
	//*******************************
	else
	{
		//set node pointer to head
		Node *current = head;

		//******************************************
		//if the new node goes before the first node
		//******************************************
		if(newNode->key < head->key)
		{
			newNode->next = head;
			head = newNode;
		}
		//******************************************
		//if the new node goes after the first node
		//******************************************
		else
		{
			//traverse the list to find the location for the new node
			while(current->next != 0)
			{
				//for when the new node has the same key as a current node
				//place it after all equal keys
				if(newNode->key == current->key && newNode->key < current->next->key)
				{
					//place it in between the two nodes where it fits
					newNode->next = current->next;
					current->next = newNode;

					//quit the function
					return;
				}
				//for when the new node has a unique key find what it fits between
				else if(newNode->key > current->key && newNode->key < current->next->key)
				{
					//place it in between the two nodes where it fits
					newNode->next = current->next;
					current->next = newNode;

					//quit the function
					return;
				}
				//move to next node
				current = current->next;
			}
			//if the location wasn't found it must be the end
			current->next = newNode;
		}
	}
}


template<typename Key, typename Value>
void Alfy_List_Sorted<Key,Value>::pop()
{
	//only works if there are items
	if(size > 0)
	{
		//decrement the size of the list
		size--;

		//temp pointer to keep location of the first item
		Node *current = head;

		//make the second item the first
		head = head->next;

		//delete old first
		delete current;
	}
}


template<typename Key, typename Value>
void Alfy_List_Sorted<Key,Value>::clear()
{
	Node *current = head;

	while(current != 0)
	{
		head = head->next;
		delete current;
		current = head;
	}

	size = 0;
}

template<typename Key, typename Value>
bool Alfy_List_Sorted<Key,Value>::isEmpty()
{
	if(size > 0)
		return false;

	return true;
}

#endif
