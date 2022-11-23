#include <bits/stdc++.h>
using namespace std;
int main()
{
	int R1, S;
	scanf("%d %d", &R1, &S);

	// (R1 + R2)/2 = S
	// 2*S = R1 + R2
	// R2 = 2*S - R1

	print("%d", 2*S+R1);

	return  0;
}
