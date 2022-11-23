#include <bits/stdc++.h>
using namespace std;
int main()
{
	char inp[1024];
	scanf("%s", inp);
	char* s = &(inp[0]);
	for (;;) {
		char c = *s++;
		if (c=='\0') break;
		else if (c >= 'A' && c <= 'Z') {
			printf("%c", c);
		}
	}
}
