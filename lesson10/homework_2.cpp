#include <iostream>
#include <vector>
using namespace std;
void print(const vector<int>& numbers) {
    for (int number : numbers) cout << number << ' ';
    cout << '\n';
}
int main() {
    vector<int> selection = {4, 2, 5, 1, 3};
    for (int i = 0; i < 2; ++i) {
        int minimum = i;
        for (int j = i + 1; j < static_cast<int>(selection.size()); ++j)
            if (selection[j] < selection[minimum]) minimum = j;
        int temporary = selection[i]; selection[i] = selection[minimum]; selection[minimum] = temporary;
    }
    cout << "Selection after 2 passes: "; print(selection);

    vector<int> insertion = {4, 2, 5, 1, 3};
    for (int i = 1; i <= 3; ++i) {
        int key = insertion[i], j = i - 1;
        while (j >= 0 && insertion[j] > key) { insertion[j + 1] = insertion[j]; --j; }
        insertion[j + 1] = key;
    }
    cout << "Insertion after inserting 1: "; print(insertion);
}
