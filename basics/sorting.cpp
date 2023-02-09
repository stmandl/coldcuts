#include <cstdlib>
#include <vector>
#include <random>
#include <iostream>
#include <unistd.h>
using namespace std;
#include <chrono>
using namespace std::chrono;
#include <algorithm>

template<typename T>
ostream& operator<<(ostream& out, const vector<T>& vec)
{
    size_t vector_size = vec.size();
    if (vector_size != 0) {
	for (size_t i=0; i<vector_size; i++)
	{
	    out << vec[i];
	    if (i<vector_size-1)
	    {
		cout << ",";
	    }
	}
    }
    return out;
}

template<typename T>
void merge_sort_(vector<T>& vec, int from, int to, vector<T>& buffer)
{
    if (to > from) {
	int m = (from + to)/2;
	merge_sort_(vec, from, m, buffer);
	merge_sort_(vec, m+1, to, buffer);
	int a=from;
	int b=m+1;
	int outp = 0;
	while (a <= m || b <= to) {
	    if (a > m) {
		buffer[outp++] = vec[b++];
	    } else if (b > to) {
		buffer[outp++] = vec[a++];
	    } else if (vec[a] <= vec[b]) {
		buffer[outp++] = vec[a++];
	    } else {
		buffer[outp++] = vec[b++];
	    }
	}
	// zurückkopieren
	//cout << "TEMP=" << temp << endl;
	outp=0;
	for (size_t i=from; i<=to;)
	{
	    vec[i++] = buffer[outp++];
	}
    }
}

template<typename T>
void merge_sort(vector<T>& vec)
{
    // merge-sort
    // Gegeben zwei sortierte arrays, merge in ein einziges sortiertes array
    vector<T> buffer(vec.size()/2+1);
    merge_sort_(vec, 0, vec.size()-1, buffer);
}



template<typename T>
int partition(vector<T>& vec, int from, int to)
{
    int piv = vec[from];
    int l_insert = from + 1;
    for (int i=from+1; i <= to; i++) {
	if (vec[i] < piv)
	{
	    iter_swap(vec.begin() + (l_insert++), vec.begin()+ i);
	} 
    }
    iter_swap(vec.begin()+(l_insert-1), vec.begin()+from);
    return l_insert-1;
}

template<typename T>
void quicksort_(vector<T>& vec, int from, int to)
{
    if (to>from) {
	int pi = partition(vec, from, to);
	quicksort_(vec, from, pi-1);
	quicksort_(vec, pi+1, to);
    }
}

template<typename T>
void quicksort(vector<T>& vec)
{
    quicksort_(vec, 0, vec.size()-1);
}


int main() {
    
    vector<int> numbers;
    
    for (int i=0; i<1000; i++)
    {
	numbers.push_back(i);
    }

    for (int i=0; i<500; i++)
    {
	int a = rand() % numbers.size();
	int b = rand() % numbers.size();
	//cout << a << "<->" << b << ": " << numbers[a] << "," << numbers[b];
	int tmp = numbers[a];
	numbers[a] = numbers[b];
	numbers[b] = tmp;
	//cout << "-->" << numbers[a] << "," << numbers[b] << endl;
    }
    cout << "Given:" << numbers << endl;
    auto start = high_resolution_clock::now();
    //stable_sort(numbers.begin(), numbers.end());
    sort(numbers.begin(), numbers.end());
    //quicksort(numbers);
    auto stop = high_resolution_clock::now();
    cout << "Sorted: " << numbers << endl;
    auto duration = duration_cast<microseconds>(stop - start);	
    cout << "DURATION:" << duration.count() << endl;
}       
