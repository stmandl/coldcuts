#include <bits/stdc++.h>
using namespace std;


template<typename T>
ostream& operator<<(ostream& out, const vector<T>& vec)
{
    size_t vector_size = vec.size();
    if (vector_size != 0) {
	for (size_t i=0; i<vector_size; i++)
	{
	    out << vec[i];
	    if (i<vector_size-1)
	    {
		cout << ",";
	    }
	}
    }
    return out;
}


bool even(string& l) {
    int sp = -1;
    int last_black = 0;
    bool scanning_white = false;
    for (int i=1; i<l.size(); i++) {
	if (l[i] == '.') {
	    if (!scanning_white) {
		last_black = i-1;
	    }
	    scanning_white=true;
	}
	if (l[i] == '*') {
	    //if (scanning_white) {
		int new_width = i-last_black;
		if (sp == -1) {
		    sp = new_width;
		}
		if (new_width != sp) {
		    return false;
		}
		sp = new_width;
		scanning_white = false;
		last_black = i;
	}
    }
    return true;
    
}

int main() {
    string line;
    int ln = 1;
    while (!cin.eof()) {
	getline(cin, line);
	if (line == "END") {
	    break;
	}
	cout << ln << " ";
	if (even(line)) {
	    cout << "EVEN";
	} else {
	    cout << "NOT EVEN";
	}
	cout << endl;
	ln++;
    }
    return 0;
}
	
