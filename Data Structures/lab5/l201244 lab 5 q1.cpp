#include<iostream>
using namespace std;
//l201244 lab 5 q1


int Is_member(int array[],int size, int key)
{
	int i = size;
	if (i == 0 )
	{
		cout<<"element not found"<<endl;
		return -1;
	}
	else
	{
		if (array[size] == key)
		{
			cout<<"Element found"<<endl;
			return 0;
		}
		else
		{
			return Is_member(array, size=size-1, key);
		}
	}
}

int main()
{
	const int len = 5;

	int arr[len];
	int key;
	cout << "Enter the value of the arrays: ";
	for (int i = 0; i < len; i++)
	{
		cin >> arr[i];
	}
	cout << "enter the number you want to search : ";
	cin >> key;

	Is_member(arr, 5, key);
	
	system("pause");
	return 0;

}
