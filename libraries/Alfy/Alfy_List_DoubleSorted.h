#ifndef ALFY_LIST_DOUBLESORTED_H
#define ALFY_LIST_DOUBLESORTED_H

template<typename Key, typename Key2, typename Value>
class Alfy_List_DoubleSorted
{
private:
	struct Node			//structure for the nodes of the list
	{
		Key key;
		Key2 key2;
		Value value;
		Node *next;
	};
	Node *head;			//head to keep track of list
	int size;			//keeps track of the size of the list
public:
	//default constructor
	Alfy_List_DoubleSorted():head(0),size(0) {};

	//add a node in order
	void push(Key keyValue, Key2 keyValue2, Value value);

	void pop();				//removes the last node
	void clear();			//deletes all the nodes in the list
	bool isEmpty();			//checks if the list is empty

	const Node &getFirst()	//reads the first node
	{
		if(size > 0)
			return *head;
		else
			throw "It's empty.";
	};
};

//places the new node in its sorted loaction
template<typename Key, typename Key2, typename Value>
void Alfy_List_DoubleSorted<Key,Key2,Value>::push(Key keyValue, Key2 keyValue2, Value value)
{
	//create the new node
	Node *newNode = new Node;
	newNode->key = keyValue;
	newNode->key2 = keyValue2;
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
		if(newNode->key <= head->key && head->key2 <= head->key2 )
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
		if(newNode->key <= head->key && newNode->key2 <= head->key2 )
		{
			newNode->next = head;
			head = newNode;
		}
		//******************************************
		//if the new node goes after the first node
		//******************************************
		else
		{
			//keep track of the previous node
			Node *prev = head;

			//traverse the list to find where key fits
			while(current->next != 0)
			{
				//***************************************
				//when the key matching the key is found
				//***************************************
				if(newNode->key == current->key)
				{
					//traverse from the current location while the keys match
					while(newNode->key == current->key && current->next != 0)
					{
						//if the new node fits before the current
						if(newNode->key2 < current->key2)
						{
							//place the node between the previous and the current
							prev->next = newNode;
							newNode->next = current;
							//quit the function
							return;
						}
						//move the pointers to the next two nodes
						prev = current;
						current = current->next;
					}
					//if the new node fits after all the nodes in which key matches place it now at the end of the matching ones
					prev->next = newNode;
					newNode->next = current;
					//quit the function
					return;
				}
				//*******************************************************
				//when there is no matching key find what it fits between
				//*******************************************************
				else if(newNode->key > current->key && newNode->key < current->next->key)
				{
					newNode->next = current->next;
					current->next = newNode;
					//quit the function
					return;
				}
				//move the pointers to the next two nodes
				prev = current;
				current = current->next;
			}
		//***********************************************
		//if the location wasn't found it must be the end
		//***********************************************
		current->next = newNode;
		}
	}
}

//removes the fisrt node
template<typename Key, typename Key2, typename Value>
void Alfy_List_DoubleSorted<Key,Key2,Value>::pop()
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

//clears the whole list
template<typename Key, typename Key2, typename Value>
void Alfy_List_DoubleSorted<Key,Key2,Value>::clear()
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

//reports if the list is empty
template<typename Key, typename Key2, typename Value>
bool Alfy_List_DoubleSorted<Key,Key2,Value>::isEmpty()
{
	if(size > 0)
		return false;

	return true;
}

#endif
