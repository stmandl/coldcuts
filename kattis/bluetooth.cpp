#include <bits/stdc++.h>
using namespace std;

int main()
{
    int nprobs;
    cin >> nprobs;

    int num_upper_left = 8;
    int num_upper_right = 8;
    int num_lower_left = 8;
    int num_lower_right = 8;

    bool blue_tooth_left = false;
    bool blue_tooth_right = false;

    for (int i=0; i<nprobs; i++)
    {
        string pos, prob;
        cin >> pos >> prob;
        // cout << pos << "," << prob << endl;

        if (pos[0] == '+') {
            // upper left
            if (prob == "b") {
                blue_tooth_left = true;
            } else if (prob == "m") {
                num_upper_left--;
            }
        } else if (pos[1] == '+') {
            // upper right
            if (prob == "b") {
                blue_tooth_right = true;
            } else if (prob == "m") {
                num_upper_right--;
            }
        }  else if (pos[1] == '-') {
            // lower right
            if (prob == "b") {
                blue_tooth_right = true;
            } else if (prob == "m") {
                num_lower_right--;
            }
        }
          else if (pos[0] == '-') {
            // lower left
            if (prob == "b") {
                blue_tooth_left = true;
            } else if (prob == "m") {
                num_lower_left--;
            }
        }                
    }

    
    if (!blue_tooth_left && num_lower_left>=1 && num_upper_left >= 1 ) {             // left?
        cout << 0 << endl;
    } else if (!blue_tooth_right && num_lower_right >= 1 && num_upper_right >= 1 ) { // right?
        cout << 1 << endl;
    } else {
        cout << 2 << endl;
    }

    return 0;
}