/*
Hneitir is a high school student, which means he has to do homework for various subjects. Hneitir is not lazy, but he gets bored studying at home, especially for chemistry. Tomorrow he will have to solve some problems on the board, in front of the class. He doesn’t know exactly which problems he’ll need to solve, but he does have a list of problems that his chemistry teacher, Ormhildur, has mentioned. Hneitir figures that if he solves all of those problems, he will be prepared for class.

Given the list of problems Ormhildur has mentioned, how many problems does Hneitir need to solve?

Input
The input is one line and specifies the problems that Hneitir needs to solve. Hneitir always need to solve at least one problem. The problems are numbered from  up to  and are listed in ascending order, separated by semicolons (;). If two or more problems are in a row, that range is specified with -. A example of an input is 1-3;5;7;10-13 and this means that Hneitir needs to solve problems ,,,,,,,, and .

Output
Write out one integer , the number of problems that Hneitir has to solve.

*/

#include <bits/stdc++.h>
using namespace std;

// basic idea:
// * parse the input points and ranges
// * mark them in an unordered set
// * return the size of the set

int main()
{
    unordered_set<int> exercises;

    for (int next_char = 0; next_char != EOF;) {
        // now we should be able to read a number
        int num;
        cin >> num;
        //cout << "num=" << num << endl;
        // is it a range?
        next_char = cin.peek();
        if (next_char == '-') {
            cin.get(); // read the '-'
            int num2;
            cin >> num2;
            //cout << "num2=" << num2 << endl;
            // do something with the range
            for (int ex = num; ex <=num2; ex++) {
                exercises.insert(ex);
            }
            if (cin.get() == EOF) {
                break;
            }
        } else if (next_char == ';') {
             cin.get();
            // insert point  
            exercises.insert(num);
        } else if (next_char ==EOF) {             
            // insert point  
            exercises.insert(num);
            break;
        }
    }

    cout << exercises.size();
}