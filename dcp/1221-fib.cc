/*
Good morning! Here's your coding interview problem for today.

This problem was asked by Apple.

Implement the function fib(n), which returns the nth number in the Fibonacci sequence, using only O(1) space.
*/

#include <iostream>
#include <charconv>
#include <cstring>

using namespace std;

//
// 1, 2, 3, 4, 5, 6, 7, ...
// 1, 1, 2, 3, 5, 8, 13, ..
// 
int fib(int n)
{
	if (n <= 2)
	{
		return 1;
	}
	int a=1, b=1, c=3;
	int tmp = -1;
	while (c++ <= n)
	{
		tmp = b;
		b = tmp + a;
		a = tmp;
	}
	return b;
		       
}
       

int main(int argc, char** argv)
{
	int n;	
	if (argc != 2 || from_chars(argv[1], argv[1]+strlen(argv[1]), n, 10).ec != errc())
	{
		cerr << "Usage: 1212-fib number" << endl;
		return 0;
	}
	cout << fib(n) << endl;
	return 0;
}

// g++ 1221-fib.cc -g -O0