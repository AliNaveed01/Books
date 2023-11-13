#include <iostream>
using namespace std;

template<class T>
class node
{
private:
	T data;
	node <T>* next;
public:
	node()
	{
		// default constructor
	}
	////////////////////////////
	
	node(node <T>* n, T d): next(n), data(d)
	{
		// overloaded constructor
	}
	///////////////////////////
	
	template<class T>
	friend class list;
};

template<class T>
class list 
{
private:
	node <T>* head;		// aka start of linkedlist
	node <T>* tail;		// aka last node of linkedlist
public:
	
	void InsertAtStart(T const k) 
	{
			node <T>* temp = new node <T>; 
			temp->data = k;
			temp->next = head;
			head = temp;		
	}
	//////////////////////////////////
	
	void InsertAtEnd(T const k) {

		node <T>* temp = new node<T>;
			temp->data = k;
			temp->next = NULL;
	}
	/////////////////////////////////
	
	void print() const
	{
		node <T>*temp = head;
		while (temp != NULL)
		{
			cout << temp->data <<endl;
			temp = temp->next;
		}

	}
	///////////////////////////////////
	
	bool search(T const& element) const{
		node<T>* temp = head;
		bool flag = false
		while (temp->next != nullptr)
		{
			if (temp->data == element)
			{
				flag = true;
			}
		}
		return flag;
	}
	////////////////////////////////////
	
	bool isEmpty () const
	{
		if (head->next == nullptr)
		{
			return true;
		}
	return false;
	}
	////////////////////////////////////

	bool InsertBefore(T const val1, T const val2)
	{
		int count=0;
		node <T>* temp = head;
		node <T>* temp2 = NULL;
		while(temp->next != NULL)
		{
			if(count==1)
			{
				temp2 = head;
			}
			if(temp-> data == v2  && counter !=0)
			{
				temp->next = new node<T>;
				temp2->next->next = temp;
			}
			else if(temp->data == v2 && counter ==0)
			{
				InsertAtStart(v1);
			}
			temp = temp-> next;
			
			if(temp2 != NULL)
			{
				temp2 = temp->next;
				count= count + 1
			}
		}


	}
	//////////////////////////////////////
	
	void deleteAll (T const val)
	{
		if (head != nullptr)
		{
			node<T>* temp = head;
			while (temp->data != nullptr)
			{
				if (temp->data == val) 
				{
					temp = temp->next;
					delete temp->data;
				}

			}
		}
	}
	//////////////////////////////////////

	void deleteAtStart()
	{

	}
	//////////////////////////////////////
	
};

//////////////////////////////////////////////////////////////////////
int main()
{
	list<int> myList;
	myList.InsertAtStart(2);
	myList.InsertAtStart(6);
	myList.InsertAtStart(7);
	myList.InsertAtEnd(9);
	myList.InsertAtEnd(7);
	myList.InsertAtEnd(8);
	myList.InsertAtStart(9);
	myList.print();
	/*myList.deleteAll(7);
	myList.print();
	myList.InsertBefore(10, 6);
	myList.print();
	cout << "searching for 10 :";
	cout << ((myList.search(10)) ? "Found " : "Not Found") << endl;
	cout << "searching for 11 :";
	cout << ((myList.search(11)) ? "Found " : "Not Found") << endl;
	myList.DeleteAtStart();
	myList.print();
	*/
	system("pause");
	return 0;
}