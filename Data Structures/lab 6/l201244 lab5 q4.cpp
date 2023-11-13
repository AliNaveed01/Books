#include<iostream>
#include <math.h>
#include <cmath>

using namespace std;

///l201244 lab 5 q4//


int No_ways(int number, int power, int currNum = 0, int currSum = 0)
{
	int R = 0;
	int p = pow(currNum, power);
	while (p + currSum < number)
	{
		R = R + No_ways(number, power,currNum+1, p +currSum);
		currNum++;
		p = pow(currNum, power);
	}

	if (p + currSum == number)
	{
		R = R + 1;
	}
	return R;
	/*if (number < 0 || number < pow(i, power))
	{
		return 0;
	}
	if (number == 0 || number == pow(i, power))
	{
		return 1;
	}*/
}

int main()
{
	int num;
	int p;
	cout << "please enter the number of which you want to find the no. of possible ways ";
	cin >> num;
	
	cout << "enter the power : ";
	cin >> p;

	cout << "number of possible ways are : " << No_ways(num, p);
	
}