#include <iostream>
using namespace std;

int fact(int n)
{
	if (n<=0)
	{
		return 1;
	}
	else 
	{
		return (n) * fact(n-1);
	}
}

int main()
{
	int num;
	cout<<"enter the number of which u want fact..?: ";
	cin>> num;
	
	int ans = fact(num);
	cout<<"the factorial of "<< num << " is : "<<ans<<endl;
	
	system ("pause");
	return 0;
}
