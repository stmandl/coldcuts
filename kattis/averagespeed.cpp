#include <bits/stdc++.h>
using namespace std;

int main()
{

    double dist = 0;
    double last_seconds = 0;
    double speed = 0;
    for (;;) {
        if (feof(stdin)) {
            break;
        }
        int hour, minute, second;                
        if (EOF == scanf("%d:%d:%d", &hour, &minute, &second)) {
            break;
        }
        double new_seconds = second + minute*60 + hour*60*60;            
        double elapsed_time = new_seconds - last_seconds;
        dist += elapsed_time/3600 * speed;

        char next_char = getchar();
        if (next_char == ' ') {            
            scanf("%lf", &speed);            
        } else {
            ungetc(next_char, stdin);
            cout << setw(2)<<setfill('0') << hour << ":" << setw(2)<<setfill('0') << minute << ":" << setw(2)<<setfill('0') << second << " " << std::fixed << std::setprecision(2) << dist << " km" << endl;            
        }
        last_seconds = new_seconds;
    }   
    return 0;
}
