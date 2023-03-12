#include <bits/stdc++.h>
using namespace std;

int main()
{
    string line;

    getline(cin, line);

    while (true) {
        getline(cin, line);
        if (!cin.eof()) {
            cout << line << endl;
        } else {
            break;
        }
        getline(cin, line);
    }

    return 0;
}