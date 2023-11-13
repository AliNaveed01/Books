#include <iostream>
#include <string>
#include<strings.h>
using namespace std;

template <class T>
class Queue
{
private:
    T *array;        
    int limit;
	int face, back, count;    
 	int num = 15;
 	////////////////////////////
 	
public:
    Queue(int size = num)
	{
		array = new T[size];
		limit = size;
		face =count =  0;
		back = -1;
	}
////////////////////////////////
	void enQueue(T n)
	{
		if (isComplete())
		{
			cout << "Overflow";
			exit(-1);
		}
		else
		{
			cout << " The inserted element is : " << n << " ";
			back = (back + 1) % limit;
			array[back] = n;
			count++;
		}
	}
	
   void deQueue()
	{
		if (IsEmpty())
		{
			cout << "StackOverflow";
			exit(-1);
		}
		else
		{
			cout << " The Removed element is : " << array[face] << " ";
			face = (face + 1) % limit;
			count--;
		}
	}
	//////////////////////////

	int size()
	{
		return count;
	}

	T Front()
	{
		if (IsEmpty())
		{	
			cout << "Error..!";
			exit(-1);
		}
		else
		{
			return array[face];
		}
	}

	bool isComplete()
	{
		if(size() == limit)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	bool IsEmpty()
	{
		if(size() == 0)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
};

int main()
{
	int size = 5
    Queue<string> l1(size);
    l1.enQueue("N");
    l1.enQueue("U");
    l1.enQueue("C");
	l1.enQueue("E");
	l1.enQueue("S");
	
	cout << "The face element is " << l1.Front() << endl;
    cout << "The size of  Queue  " << l1.size() << endl;
    for(int i = 0;i<size;i++)
    {
    	l1.deQueue();	
	}
	
    
    if (l1.IsEmpty())
	{
		cout << "Empty Queue.!"<<endl;
    }
    else
	{
     	cout << "Not Empty Queue";  
    }
	system("pause");
    return 0;
}
