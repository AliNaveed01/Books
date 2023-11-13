#include<iostream>
using namespace std;
//l201244 lab 5 q2

int fabonacci(int num)
{
	if (num == 0 || num == 1)
	{
		return num;
	}
	else
	{
		return (fabonacci(num - 1) + fabonacci(num - 2));
	}

}

int sum (int num)
{
	if (num == 0 || num == 1)
	{
		return num;
	}
	else
	{
		return num + sum(num-1);
	}
}
int main()
{
	int num;
	cout << "please enter the number of which yo want fabonnaci number: ";
	cin >> num;

	cout<< "The F number of "<<num <<" is : "<<fabonacci(num)<<endl;
	cout<<"The sum of numbers uptill "<< num <<" is : "<< sum(num);
}
