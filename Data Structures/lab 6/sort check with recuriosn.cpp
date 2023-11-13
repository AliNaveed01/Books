#include <iostream>
using namespace std;

bool check(int arr[], int size)
{
	if (size == 1)
	{
		return true;
	}
	
	bool remainarr = check( arr+1, size-1);
	return (arr[0]<arr[1] && remainarr);
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
	
	
}