#include <bits/stdc++.h>
using namespace std;
#include <chrono>
using namespace std::chrono;
using namespace std;

std::ostream &operator<<(std::ostream &s, const vector<int32_t> &v)
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
    // auto start_input = high_resolution_clock::now();
    int T;
    int s = scanf("%d", &T);
    assert(s != EOF);
    int D1;
    s = scanf("%d", &D1);
    assert(s != EOF);
    // cerr << "D1: " << D1 << endl;
    int32_t p1[D1 + 1];
    // p1.reserve(D1);
    int tmp;
    for (int i = 0; i <= D1; i++)
    {
        int s = scanf("%d", &tmp);
        assert(s != EOF);
        p1[i] = tmp;
    }
    int D2;
    s = scanf("%d", &D2);
    assert(s != EOF);
    // cerr << "D2: " << D2 << endl;
    // vector<int32_t> p2;
    // p2.reserve(D2+1);
    int32_t p2[D2 + 1];
    for (int i = 0; i <= D2; i++)
    {
        int s = scanf("%d", &tmp);
        assert(s != EOF);
        p2[i] = tmp;
    }

    int OD = (D1) + (D2);
    vector<int> res(OD + 1, 0);

    // auto stop_input = high_resolution_clock::now();
    // cerr << "Time to read the input: " << duration_cast<nanoseconds>(stop_input - start_input).count()/1.0e9 << endl;

    // do this multithreaded as it is ridicuously parallelisable
    unsigned long num_threads = thread::hardware_concurrency();
    // cerr << "NUM THREADS:" << num_threads << endl;
    int package_size = D1; // max(D1/num_threads/4,(unsigned long int)1);
    // cerr << "PS:" << package_size << endl;
    vector<thread> workers;
    for (int j = 0;;)
    {
        int to = min(j + package_size, D1);
        workers.emplace_back(thread([&](int from, int to) -> void {
            for (int i=0; i<=D2; ++i) {
                for (int j=from; j<=to; ++j) {
                    res[i+j] += p1[j]*p2[i];
                }
            } 
        }, j, to));
        // cerr << "CREATED WORKER FROM " << j << " to " << to << " D1=" << D1 << endl;
        j += package_size + 1;
        if (to >= D1)
        {
            break;
        }
    }
    // cerr << "Waiting for workers " << workers.size() << " to finish" << endl;
    for (auto &w : workers)
    {
        w.join();
        // cerr << "Joined worker " << w.get_id() << endl;
    }

    // auto start_output = high_resolution_clock::now();
    printf("%d\n", OD);
    size_t res_size = res.size();
    for (int i = 0; i < res_size; i++)
    {
        if (i < res_size - 1)
            printf("%d ", res[i]);
        else
            printf("%d", res[i]);
    }
    // auto stop_output = high_resolution_clock::now();
    // cerr << "Time to write the result: " << duration_cast<nanoseconds>(stop_output - start_output).count()/1.0e9 << endl;
}
