#include <iostream>
#include <cstdlib>
#include <vector>
#include <cmath>
#include <list>
#include <chrono>

using namespace std;

void display(vector<int> &array) {
    for(int i=0; i<30; i++)
        cout << array[i] << " ";
    cout << "..." << endl;
}
void countingSort(vector<int> &array, int place) {
    const int max = 10;
    int size = array.size();
    vector<int> output{};
    vector<int> count{};

    for (int i = 0; i < size; i++){
        count.push_back(0);
        output.push_back(0);
    }

    // Calculate count of elements
    for (int i = 0; i < size; i++)
        count[(array[i] / place) % 10]++;

    // Calculate cumulative count
    for (int i = 1; i < max; i++)
        count[i] += count[i - 1];

    // Place the elements in sorted order
    for (int i = size - 1; i >= 0; i--) {
        output[count[(array[i] / place) % 10] - 1] = array[i];
        count[(array[i] / place) % 10]--;
    }

    for (int i = 0; i < size; i++)
        array[i] = output[i];
}

// Main function to implement radix sort
void radix_sort(vector<int> &array, int max) {
    // Apply counting sort to sort elements based on place value.
    for (int place = 1; max / place > 0; place *= 10)
        countingSort(array, place);
}
void insertion_sort(vector<int> &vector){
    for(int i=1; i<vector.size(); i++)
    {
        int temp = vector[i];
        int j= i-1;
        while(j>=0 && temp <= vector[j])
        {
            vector[j+1] = vector[j];
            j--;
        }
        vector[j+1] = temp;
    }
}

int main() {
    vector<int> nums = {};
    int tam = 10;
//    int tam = 100;
//    int tam = 1000;
//    int tam = 10000;
//    int tam = 100000;
//    int tam = 1000000;
    for (int i=0; i<tam; i++) {
        nums.emplace_back(rand()%tam*2);
    }
    //cout << "insertion sort" << endl;
    cout << "radix sort" << endl;
    display(nums);
    auto start = chrono::high_resolution_clock::now();
    //insertion_sort(nums);
    radix_sort(nums, tam*2);
    auto end = chrono::high_resolution_clock::now();
    double time_taken = chrono::duration_cast<chrono::nanoseconds>(end - start).count();

    time_taken *= 1e-9;

    cout << "Time taken by program is : " << fixed << time_taken << " sec" << endl;
    display(nums);
}
