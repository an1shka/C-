#include <algorithm>
#include <chrono>
#include <iostream>
#include <random>
#include <vector>
using namespace std;

void bubbleSort(vector<int>& numbers) {
    for (int i = 0; i + 1 < static_cast<int>(numbers.size()); ++i) {
        bool changed = false;
        for (int j = 0; j + 1 < static_cast<int>(numbers.size()) - i; ++j) {
            if (numbers[j] > numbers[j + 1]) { swap(numbers[j], numbers[j + 1]); changed = true; }
        }
        if (!changed) break;
    }
}
void insertionSort(vector<int>& numbers) {
    for (int i = 1; i < static_cast<int>(numbers.size()); ++i) {
        int key = numbers[i], j = i - 1;
        while (j >= 0 && numbers[j] > key) { numbers[j + 1] = numbers[j]; --j; }
        numbers[j + 1] = key;
    }
}
template <typename Sorter>
long long measure(vector<int> numbers, Sorter sorter, bool& sorted) {
    auto start = chrono::steady_clock::now();
    sorter(numbers);
    auto finish = chrono::steady_clock::now();
    sorted = is_sorted(numbers.begin(), numbers.end());
    return chrono::duration_cast<chrono::microseconds>(finish - start).count();
}
int main() {
    mt19937 generator(42);
    uniform_int_distribution<int> distribution(0, 100000);
    for (int size : {1000, 5000}) {
        vector<int> original(size);
        for (int& number : original) number = distribution(generator);
        bool bubbleOk, insertionOk, standardOk;
        long long bubbleTime = measure(original, bubbleSort, bubbleOk);
        long long insertionTime = measure(original, insertionSort, insertionOk);
        long long standardTime = measure(original, [](vector<int>& values) { sort(values.begin(), values.end()); }, standardOk);
        cout << "n = " << size << "\nBubble: " << bubbleTime << " us, sorted: " << boolalpha << bubbleOk
             << "\nInsertion: " << insertionTime << " us, sorted: " << insertionOk
             << "\nstd::sort: " << standardTime << " us, sorted: " << standardOk << "\n\n";
    }
}
