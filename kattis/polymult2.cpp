#include <bits/stdc++.h>
using namespace std;



std::ostream &operator<<(std::ostream &s, const vector<int> &v)
{
	s << "[";
	for (int i = 0; i < v.size(); i++)
	{
		s << v[i];
		if (i < v.size() - 1)
		{
			s << ",";
		}
	}
	s << "]";
	return s;
}

int main()
{
    int T;
    scanf("%d", &T);
    //cout << "T: " << T << endl;
    int D1;
    scanf("%d", &D1);
    //cout << "D1: " << D1 << endl;
    vector<int> p1;
    p1.reserve(D1);
    int tmp;  
    for (int i=0; i<=D1; i++) {    
        scanf("%d", &tmp);
        p1.push_back(tmp);
    }
    //cout << p1 << endl;
    int D2;
    scanf("%d", &D2);
    //cout << "D2: " << D2 << endl;
    vector<int> p2;
    p2.reserve(D2);
    for (int i=0; i<=D2; i++) {    
        scanf("%d", &tmp);
        p2.push_back(tmp);
    }
    //cout << p2 << endl;

    int OD = (D1)+(D2);
    //cout << "OD=" << OD << endl;
    vector<int> res(OD+1,0 );

    // first diagonals

    for (int d=0; d<=D1; ++d) {
        int i = d;
        int j = 0;
        //cout << "res[" << i << "]" << endl;
        int sum =0;
        while (i>=0 && j<=D2) {
            //cout << "(" << i << "," << j << "):: " << p1[i]*p2[j] << endl;
            sum+=p1[i]*p2[j];
            i-=1;
            j+=1;
        }
        //cout << "SUM: res[" << d << "]=" << sum << endl;
        res[d] = sum;
    }
    //cout << "..." << endl;
    for (int d=1; d<=D2; ++d) {
        int i=D1;
        int j=d;
        //cout << "res[" << D1+d << "]" << endl;
        int sum = 0;
        while (j<=D2 && i>=0) {
            //cout << "(" << i << "," << j << "):: " << p1[i]*p2[j] << endl;
            sum+=p1[i]*p2[j];
            i-=1;
            j+=1;
        }
        //cout << "SUM: res[" << D1+d << "]=" << sum << endl;
        res[D1+d] = sum;
    }
    //cout << "RESULT: " << res << endl;
    printf("%d\n", OD);
    size_t res_size = res.size();
    for (int i =0; i<res_size; i++) {
        if (i<res_size-1)
            printf("%d ", res[i]);
        else
            printf("%d", res[i]);
    }
}