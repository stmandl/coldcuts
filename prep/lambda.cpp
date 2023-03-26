#include <bits/stdc++.h>
using namespace std;

class Holder
{
	friend ostream& operator<<(ostream& os, const Holder& h);
	int val;
public:
	Holder(int v) : val(v) {}

	auto modder() {
		return [this](int v)->void {
			val = v;
		};
	}
};

ostream& operator<<(ostream& os, const Holder& h) {
	os << h.val;
	return os;
}

int main()
{
	Holder a(12);
	cout << a << endl;
	auto m = a.modder();
	m(13);
	cout << a << endl;
	m(14);
	cout << a << endl;
	return 0;
}
