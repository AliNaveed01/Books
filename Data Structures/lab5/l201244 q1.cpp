#include<iostream>
using namespace std;
template <class T>

class Node
{
private:
	
	    T data;
    	Node<T>* next;	
		///////////////////////////
		
public:
    
    Node(T d = 0, Node<T>* n = nullptr) :data(d), next(n)
    {
    	////////////////////////
    	
	}
    Node(const Node<T>& obj)
    {

        this->data = obj.data;
    }
    
    friend class List;
};

 //////////////////////////////////////////////////////

template <class T>
class List

{
    Node<T>* head;
    Node<T>* tail;

public:

    List() :head(new Node<T>), tail(new Node<T>)
    {
		 head->next = tail;
    }
//////////////////////////////////////////////////
    void insertAtStart(T d)
    {

        Node<T>* temp = head->next;
        head->next = new Node<T>;
        head->next->data = d;
        head->next->next = temp;
    }
    /////////////////////////////////
    
    void insertAtEnd(T dat)
    {
        tail->data = dat;
        tail->next = new Node<T>;
        tail = tail->next;
    }
    ////////////////////////////////

    void insertAfter(const T data1, const T data2)
    {
        Node<T>* temp = head->next;
        while (temp != tail)
        {

            if (temp->next != tail && temp->data == data1)
            {
                Node<T>* tmp = temp->next->next;
                temp->next = new Node<T>;
                temp->next->next = tmp;
                temp->next->data = data2;
            }
            else if (temp->next == tail && temp->data == data1)
            {
                this->insertAtEnd(data2);
            }
            temp = temp->next;
        }
    }
//////////////////////////////////////////////////////////
 
    void delete_atStart()
    {
        if (head->next == nullptr)
        {
        	cout << "The List list is empty." << endl;  
        }
        else
        {
        	Node<T>* temp = head->next->next;
            delete head->next;
            head->next = temp;
        }
    }
    /////////////////////////////////////////////////
    
    void delete_atEnd()
    {
        Node<T>* temp = head->next;
        while (temp != tail)
        {
            if (temp->next->next == tail)
            {
                delete temp->next;
                temp->next = tail;
            }
            temp = temp->next;
        }
    }
    /////////////////////////////////
    
    void delete_after(const T dat)
    {
        Node<T>* temp = head->next;
        while (temp != tail)
        {
            if (temp->data == dat)
            {
                Node<T>* tmp = temp->next->next;
                delete temp->next;
                temp->next = tmp;
            }
            temp = temp->next;
        }
	}
	
   	bool isEmpty()
	{
		head->next ==  nullptr;
		return head->next;
	}
	
    //////////////////////////////////////
	T last_element()
	{
		Node<T>* temp = head->next;
		T tmp = 0;
		while(temp->next != nullptr)
		{
			tmp = temp->data;
			temp = temp->next;
		}
		return tmp;
	} 
    
    void print()
    {
    	if(head->next == nullptr)
    	{
    		cout<<"The list is empty..!"<<endl;
		}
		else
		{
	    	Node<T>* temp = head->next;
        	while (temp != tail)
        	{
        	    cout << temp->data << " ";
	        	    temp = temp->next;
        	}	
		}
    }
};

//////////////////////////////////////////////////////
template <class T>

class Stack
{
private:
	List<T> s;
	int size;
public:
	Stack(): size(0) 
	{
		///////
	}
	//////////////////////////////
	int Size()
	{
		return size;
	}
	
	bool isEmpty() 
	{	
		return s.isEmpty();
	}

	bool top(T& element)
	{
		if (isEmpty())
		{
			
		 return false;
		
		}
		else
		{
			
			element = s.last_element();
		
		}
		return true;
	}
	/////////////////////////////
	void push(T const& e)
	{
		
		s.insertAtEnd(e);
		size++;
		
	}
	////////////////////////
	
	void pop() 
	{
		if (isEmpty()) 
		{
			cout << "The list is empty." << endl;
		}
		else
		{
			s.delete_atEnd();
			size--;
		}
	}
	
	void print()
	{
		s.print();
	}
	
};

/////////////////////////////////////////////

string reverse(string str)
{
    Stack<char> rev;
    const int s = str.size();
    for (int i = 0; i < s;i++)
    {
        rev.push(str[i]);
    }
    string revers;
    char data;
    for (int i = 0; i < s ;i++)
    {
        rev.top(data);
        cout << data;
        rev.pop();
    }
    return revers;
}

int main()
{

	Stack<int> s1;
	s1.push(10);
	s1.push(15);
	s1.print();
	s1.pop();
	s1.push(20);
	s1.push(25);
	s1.print();
	s1.pop();
	int num = 3;
	s1.top(num);
	s1.print();

	string str = reverse("Naveed");

	system("pause");
	return 0;
}
