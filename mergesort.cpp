#include <iostream>
#include <vector>
#include <thread>
#include <algorithm>

using namespace std;

class MergeSort {
public:
    void Sort(vector<int>& array) {
        if (array.size() <= 1) {
            return;
        }

        vector<int> left(array.begin(), array.begin() + array.size() / 2);
        vector<int> right(array.begin() + array.size() / 2, array.end());

        thread leftThread(&MergeSort::Sort, this, ref(left));
        thread rightThread(&MergeSort::Sort, this, ref(right));

        leftThread.join();
        rightThread.join();

        Merge(array, left, right);
    }

private:
    void Merge(vector<int>& array, const vector<int>& left, const vector<int>& right) {
        size_t i = 0, j = 0, k = 0;

        while (i < left.size() && j < right.size()) {
            if (left[i] <= right[j]) {
                array[k++] = left[i++];
            }
            else {
                array[k++] = right[j++];
            }
        }

        while (i < left.size()) {
            array[k++] = left[i++];
        }

        while (j < right.size()) {
            array[k++] = right[j++];
        }
    }
};

int main() {
    setlocale(LC_ALL, "ru");
    vector<int> array(10);
    cout << "Введите 10 целых чисел: ";
    for (int& num : array) {
        cin >> num;
    }

    MergeSort mergeSort;
    auto sortFunction = [&mergeSort](vector<int>& array) {
        mergeSort.Sort(array);
    };

    thread mergeSortThread(sortFunction, ref(array));
    mergeSortThread.join();

    cout << "Отсортированный массив: ";
    for (const int& num : array) {
        cout << num << " ";
    }
    cout << "\n";

    return 0;
}