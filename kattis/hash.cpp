#include <bits/stdc++.h>
using namespace std;


int count_hashes(uint32_t word_length, uint32_t hash_value, uint32_t mod)
{
    if (hash_value > mod) {return 0;}

    vector<char> word;
    word.assign(word_length, 0);
    int match_counter = 0;
    while (true) {
        for (auto c:word ) {
            if (c>0) {
                cout << static_cast<char>('a' - 1 + c);
            } else {
                cout << ".";
            }
        }
        for (int d = 0; d<word_length; d++) {
            word[d] += 1;
            if (word[d] == 27) {
                if (d == word_length - 1) {
                    return match_counter;
                } else {
                    
                }
            }
        }
        cout << endl;
        break;
    }
    return match_counter;
}

int main()
{

    uint32_t N,K,M;
    cin >> N >> K >> M;

    cout << count_hashes(N,K,M);

    return 0;
}