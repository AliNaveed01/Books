#include <iostream>
using namespace std;

bool check(int arr[], int size)
{
	static int i = 1;
	bool c = false;
	if( i == size )
	{
		return true;
	}
	
	if(arr[i] < arr[i+1])
	{
		c=true;
		return check(arr+1,size-1);
	}
	else
	{
		c = false;
		return c;
	}
}

void incOrder(int n, int range)
{
	if(n == range )
	{
		cout<< range;
	}
	else
	{
		cout<<"Number in increasing order is "<< n<< " ";
		incOrder( n+1, range);	
	}
	
}


void decOrder(int n, int drange)
{
	if(n < drange )
	{
		cout<<"invalid";
		return;
	}
	else
	{
		if(n == drange)
		{
			cout<<drange;
		}
		else
		{
			cout<<"Number in decreasing order is "<< n<< " ";
			decOrder( n-1, drange);
		}
			
	}
	
}



int main ()
{
	int size;
	cout<<"enter the size of array: ";
	cin>> size;
	int arr[size];
	for(int i =0;i<size;i++)
	{
		cout<<"Enter values: ";
		cin>>arr[i];
	}
	
	bool flag =  check(arr, size);
	cout<< "answer is : "<< flag<<endl;
	system ("pause");
	
	int n = 7;
	int range = 12;
	int drange = 4;
	
	incOrder(n,range);
	decOrder(n,drange);
	
	system ("pause");
	return 0;
	
	
}
