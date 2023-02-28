#include <bits/stdc++.h>
#include <cstddef>
#include <cstring>
using namespace std;

struct Editor {

    string buf = "";
    int pos = 0;

    void insert(char c) {
        buf.insert(pos, 1, c);
        pos += 1;
    }

    void show() {
        cout << buf;
    }

    // move "after" the \n that separated the lines
    void goto_line_start() {
        while (pos > 0) {
            if (buf[pos-1] == '\n') {
                break;
            }
            pos--;
        }
    }

    void goto_line_end() {
        while (pos < buf.size()-1) {
            if (buf[pos] == '\n') {
                break;
            }
            pos++;
        }
    }

    int count_to_line_start() {
        int p = pos;
        int c = 0;
        while (p > 0) {
            if (buf[p-1] == '\n') {
                break;
            }
            p--;
            c++;
        }
        return c;
    }

    void left() {
        if (pos > 0) pos--;
    }

    void right() {
        if (pos < buf.size()-1) pos++;
    }

    void down() {
        int offset = count_to_line_start();
        goto_line_end();
        right();
        for (int i=0; i<offset; i++) {
            right();
        }
    }

    void up() {
        int offset = count_to_line_start();
        goto_line_start();
        left();
        goto_line_start();
        for (int i=0; i<offset; i++) {
            right();
        }
    }
};


int main() {
    Editor ed;
    for (char c : "Hello World") {
        ed.insert(c);
    }
    ed.insert('\n');
    for (char c : "you suckers") {
        ed.insert(c);
    }

    ed.goto_line_start();
    cout << ed.pos << endl;
    cout << ed.buf[ed.pos] << endl;
    ed.left();
    cout << ed.pos << endl;
    ed.goto_line_start();
    cout << ed.pos << endl;
    ed.right();
    ed.right();
    cout << ed.pos << endl;
    ed.insert('-');
    ed.left();
    // print('pos:',ed.pos)
    ed.down();
    ed.insert('-');
    ed.right();
    ed.insert('*');
    ed.left();
    ed.up();
    ed.insert('*');
    ed.show();
    return 0;
}

