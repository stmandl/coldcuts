#include <bits/stdc++.h>
using namespace std;

ostream& operator<<(ostream& os, const vector<int>& v) noexcept {
    if (v.size()==0) return os;
    os << v[0];
    for (decltype(v.cbegin()) it = v.cbegin()+1; it != v.cend(); ++it) {        
        os << " " << *it;        
    }
    return os;
}


double time_it(function<void()>& fn) {
    using namespace chrono;
    auto start = high_resolution_clock::now();
    fn();
    auto duration = high_resolution_clock::now() - start;
    return static_cast<double>(duration.count())*decltype(duration)::period::num / static_cast<double>(decltype(duration)::period::den);    
}

double time_it(function<void()>&& fn) {
    return time_it(fn);
}

// 1.24168
// template<typename T>
// void rotate_k(vector<T>& arr, size_t k) {
//     reverse(arr.begin(), arr.end());
//     reverse(arr.begin(), arr.begin()+(arr.size()-k));
//     reverse(arr.begin()+(arr.size()-k), arr.end());
// }

template<typename T>
void preverse(int f, vector<T>& arr, size_t from, size_t below);



template<typename T>
inline void rotate_k(vector<T>& arr, size_t k) {
    //my_reverse(arr, 0, arr.size());
    //my_reverse(arr, 0, arr.size()-k);
    //my_reverse(arr, arr.size()-k, arr.size());
    cerr << "A0" << endl;
    preverse(0, arr, 0, arr.size());
    preverse(1, arr, 0, arr.size()-k);
    preverse(2, arr, arr.size()-k, arr.size());
    // cerr << "A1" << endl;
    // auto fut1 = async(launch::async,[&arr,k]{preverse(1, arr, 0, arr.size()-k);});
    // cerr << "A2" << endl;
    // auto fut2 = async(launch::async,[&arr,k]{preverse(2, arr, arr.size()-k, arr.size());});
    // cerr << "A3" << endl;
    
    // fut1.wait();
    // cerr << "A4" << endl;
    // fut2.wait();
    // cerr << "A5" << endl;
    // // fut1.get();
    // cerr << "A6" << endl;
    // fut2.get();
}

// //
#include <future>
#include <thread>
// template<typename T>
// void my_reverse(vector<T>& arr, size_t from, size_t below, size_t offset, size_t step_size) {
//     //
//     assert (from <= below);
//     cerr << "r (" << from << " , " << below << " ) " << endl;
//     preverse(arr, from, below);
// }
template<typename T>
inline void qreverse(vector<T>& arr, size_t first, size_t last)
{
    if (first == last)	return;
    --last;
    while ( first < last) [[likely]]
	{      
      __builtin_prefetch(&arr[first+1],1,0);    
      __builtin_prefetch(&arr[last-1],1,0);
	  swap(arr[first], arr[last]);
	  ++first;
	  --last;
	}
}

template<typename T>
inline void preverse(int f, vector<T>& arr, size_t from, size_t below) {
    size_t cores = thread::hardware_concurrency();
    size_t task_size = (below-from) / cores;
    cerr << "TASK_SIZE=" << task_size << " for " << cores << " threads" << endl;
    vector<thread> tasks(cores);
    for (size_t t = 0; t<cores; t++) {
        size_t myfrom = from + t * task_size;
        size_t mybelow = min(myfrom + task_size, below);
        cerr << "t" << t << " size = " << mybelow - myfrom << endl;
        tasks[t] = thread([t, &arr,mybelow,myfrom]{
            //cerr << "TH: Reversing from " << myfrom << " to " << mybelow << endl;
            cerr << "TH: " <<t <<":: " << sched_getcpu() << endl;
            qreverse(arr,myfrom,mybelow);
        });
        // Create a cpu_set_t object representing a set of CPUs. Clear it and mark
    // only CPU i as set.
        cpu_set_t cpuset;
        CPU_ZERO(&cpuset);
        CPU_SET(t % thread::hardware_concurrency(), &cpuset);
        int rc = pthread_setaffinity_np(tasks[t].native_handle(),
                                        sizeof(cpu_set_t), &cpuset);
        if (rc != 0) {
            std::cerr << "Error calling pthread_setaffinity_np: " << rc << "\n";
        }
    }    
    for (auto& f : tasks) {
        f.join();
    }
    cout << f<<".." << endl;

}

int main()
{
    vector<int> small_array(20);
    iota(small_array.begin(), small_array.end(), 0);

    cout << "Given: " << small_array << endl;
    rotate_k(small_array, 10);
    cout << "rotate-10: " << small_array << endl;

    vector<int> big_array(2'000'000'000);    
    iota(big_array.begin(), big_array.end(), 0);    

    cout << "Rotating " << big_array.size() << " items took " <<  time_it([&big_array]{    
        rotate_k(big_array,big_array.size()/2);
    }) << " seconds" << endl;
    
    //cout << "Sleeping 1s took " << time_it([]{sleep(1);}) << " seconds" << endl;

    return 0;;
}
