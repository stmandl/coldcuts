#include <bits/stdc++.h>
using namespace std;
int main()
{
	char inp[1000];
	scanf("%s", inp);
	char* s = &(inp[0]);
	assert(*s == 'h');
	int count = 0;
	while (*++s == 'e') {
		count++;
	}
        assert(*s == 'y');
	printf("h");
	for (int i=0; i<count*2; i++) {
		printf("e");
	}
	printf("y");
	return 0;
}
