#include <bits/stdc++.h>
using namespace std;

struct Rect {
    int w,h;
    Rect(int a, int b) : w(a), h(b) {};
};


void flow_layout(const vector<Rect>& rects, int max_width) {
    if (rects.empty()) {
        cout << "0 x 0" << endl;
        return;
    }
    const Rect& fr = rects[0];
    int max_x = fr.w;
    int posx = fr.w, posy = 0, nexty = fr.h;

    for (auto rit = rects.begin()+1; rit != rects.end(); ++rit) {
        int h = rit->h;
        int w = rit->w;
        if (posx + w > max_width) {
            // new line
            posx = w;
            posy = nexty;
            nexty = posy + h;
        } else {
            // continue in same line
            posx += w;
            nexty = max(nexty, posy + h);
        }
        max_x = max(max_x, posx);
    }

    cout << max_x << " x " << nexty << endl;
    

}

int main()
{
    while (true)
    {
        int max_width;
        cin >> max_width;
        if (max_width == 0) break;
        
        vector<Rect> rects;
        while (true) {
            
            int w,h;
            cin >> w >> h;
            if (w == -1 && h == -1) break;
            rects.emplace_back(w,h);
        }

        flow_layout(rects, max_width);

    }

    return 0;
}