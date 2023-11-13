#include<iostream>
using namespace std;

//apparoach is template based programming for implementation of circular linked lists
template<class T>
class node
{
private:
	node<T>* next;	//a pointer which will hold the adress of the next pointer to be called
	T data;		

public:
	node()
	{
		//default constructor
		next = nullptr;
	}
	node(T data)		//this will work when the user gives the data which he want to store in it as an arguement
	{
		//paramterized constructor
		this->data = data;
		next = nullptr;
	}

	node (T data, node<T>* next)	//this will work when user also wants to point towards a particular node
	{
		// another overloaded constructor
		this->data = data;
		this->next= next;
	}

	// in order to access the private data members, we will have to make list a friend class of node
	template<class T>
	friend class list;
};

template<class T>
class list
{
private:
	node<T>* head;		// it will point to the start of the list
	node<T>* tail;		// it will be pointing to the end node of the list which will further point to the first node hence making it a circular one

public:
	list()
	{
		// default constructor

		head= nullptr;
		tail = nullptr;
	}
	 bool isempty()
	 {
		 // this will return true if list is empty and false when its not
		 return (head==nullptr);
	 }

	 void insert (T data)
	 {
		 // making an inserter to insert data

		 node<T>* inserter = new node<T>(data);
		 // incase the list is empty
		 if(head==nullptr)
		 {
			 head = inserter;		//both the head and the tail will be pointing towards the inserter which will be poiting to itself
			 tail = inserter;
			 inserter->next = head;
			 return;
		 }
		 else
		 {
			 node<T>* temp = head;
			 while(temp->next!= head)
				 temp=temp->next;

			 temp= inserter;
			 tail->next = inserter;
			 inserter->next = head;
		 }
	 }

	 void print()
	 {
		 node<T>* temp = head;
		 if(head==nullptr)
		 {
			 //incase the list is empty
			 cout<<"Your list is empty..!"<<endl;
			 return;
		 }

		 else
		 {
			 do
			 {
				 //traverse the list until it comes back to itself.
				 cout<<temp->data<<" , ";
				 temp=temp->next;
			 }while(temp!= tail);
		 }

	 }

	 //helper function which will give us the length of the cll
	int length()
	{
		int len = 1;
		node<T>* temp = head;
		if (head == nullptr)
		{
			return 0;
		}
		else
		{
			node<T>* temp = tail;

			while (temp->next != tail)
			{
				len++;
				temp = temp->next;
			}
		}
		return len;
    }





	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////QUESTION 2	/////////////////////////////////////////////////////////////////////////





	void split()
	{
		node<T>* temp = head;
		int size = length();
		if(size == 0)
		{
			cout<<"empty list..!"<<endl;
			return;
		}

		if(size%2 == 0)
		{
			// this is an even cll
			/*list<T>* newlist = new list();*/
			node<T>* temp2 = new node<T>();
			node<T>* temp3 = new node<T>();
			for(int i = 0;i<size/2;i++)
			{
				temp->data = temp2->data;
				temp= temp->next;
				temp2 = temp2->next;
			}
			for (int i = size/2;i<size;i++)
			{
				temp->data = temp3->data;
				temp= temp->next;
				temp3 = temp3->next;
			}
		}
		else if(size%2 !=0)
		{
		if (size == 1)
		{
			cout<<temp->data<<" ";
			return;
		}
			// it is an odd list
			node<T>* temp2 = new node<T>();
			node<T>* temp3 = new node<T>();
			for(int i = 0;i<size/2+1;i++)
			{
				temp->data = temp2->data;
				temp= temp->next;
				temp2 = temp2->next;
				cout<<temp2->data<<" , ";
			}
			for (int i = size/2+1;i<size;i++)
			{
				temp->data = temp3->data;
				temp= temp->next;
				temp3 = temp3->next;
				cout<<temp3->data<<" , ";
			}

		}

	}


		///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////QUESTION 3	/////////////////////////////////////////////////////////////////////////
	void AboveAvg(int val)
	{
		node<T>* traverser = head;
		int ans =  AboveAvgg( val,traverser );

		cout<<ans<<endl;
	}


	int AboveAvgg(int val, node<T>* traverser)
	{
		int size = length();
		if(size == 0)
		{
			return 0;
		}
		int avg=0;
		 




		//due to some reason idk why, im not able to store the value of nodes i
		int sum = 0
		int count = 0;
		if(traverser->data > val)
			{
				arr[count] = traverser->data;
				sum = sum+ traverser->data;
				count++;
				AboveAvgg (val,traverser->next);
			}
			else 
			{
				AboveAvgg (val,traverser->next);
			}
		/*while (traverser->next != head)
		{
			if(traverser->data > val)
			{
				arr[count] = traverser->data;
				count++;
				traverser= traverser->next;
			}
			else 
			{
				traverser= traverser->next;
			}
		}*/
		avg = sum/count;

		delete[] arr;
		arr = nullptr;
		return avg;
	}


};



int main()
{
	cout<<"THIS PROGRAM WILL IMPLEMENT A CIRCULAR SINGLY LINKED LIST WHICH CONSISTS OF A HEAD AND A TAIL..!"<<endl<<endl;
	list<int> test;


	test.insert(12);


	//test.insert(18);
	//test.insert(5);
	//test.insert(2);*/
	
	test.print();
	test.split();

	test.AboveAvg(10);


	system ("pause");
	return 0;
}



