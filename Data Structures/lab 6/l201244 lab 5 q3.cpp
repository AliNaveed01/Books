#include<iostream>
using namespace std;

///l201244 lab 5 q3///
int countDigits(int num)
{
	static int count = 0;

	if (num > 0)
	{
		count++;
		countDigits(num / 10);
	}
	else
	{
		return count;
	}
}

//driver code

int sumOfDigits(int num)
{
	int rotator = 0;
	int sum = 0;

	if (num < 10)
	{
		return num;
	}
	else
	{
		while (num != 0)
		{
			rotator = num % 10;
			num = num / 10;
			sum = sum + rotator;
		}
		/*if (num != 0)
		{
			rotator = num % 10;
			num = num / 10;
			sum = sum + rotator;
		}*/
		return sumOfDigits(sum);
	}
}



int main()
{
	int num;
	cout << "please enter the number ";
	cin >> num;
	cout << "number of digits in the given value is : " << countDigits(num) << endl;
	cout << "After recursive call, The number of digit in answer is 1 and " << endl;
    cout << "Sum is : " << sumOfDigits(num) << endl;
}