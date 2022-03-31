#include <algorithm>
#include <iostream>
#include <random>
#include <vector>
#include <chrono>

using namespace std;

void print(vector<int> &arr) {
  for (int i = 0; i < arr.size(); i++)
    cout << arr[i] << " ";
  cout << endl;
}

void CountingSort(vector<int> &arr, int pos) {
  auto compFunction = [pos](const int &a, const int &b) {
    int aValue = (a / pos) % 10;
    int bValue = (b / pos) % 10;
    return aValue < bValue;
  };

  int max = *max_element(arr.begin(), arr.end(), compFunction);
  int min = *min_element(arr.begin(), arr.end(), compFunction);
  int maxIndex = (max / pos) % 10;
  int minIndex = (min / pos) % 10;
  int range = maxIndex - minIndex + 1;

  vector<int> count(range, 0);
  vector<int> output(arr.size());

  for (int i = 0; i < arr.size(); i++) {
    int index = (arr[i] / pos) % 10;
    count[index - minIndex]++;
  }

  // Suma de los valores consecutivos del counting
  for (int i = 1; i < count.size(); i++)
    count[i] += count[i - 1];

  for (int i = arr.size() - 1; i >= 0; i--) {
    int index = (arr[i] / pos) % 10;
    output[count[index - minIndex] - 1] = arr[i];
    count[index - minIndex]--;
  }

  for (int i = 0; i < arr.size(); i++)
    arr[i] = output[i];
}

void RadixSort(vector<int> &arr) {
  int maxValue = *max_element(arr.begin(), arr.end());

  for (int i = 1; (maxValue / i) > 0; i *= 10) {
    CountingSort(arr, i);
  }
}

int main() {
  srand(time(0));
  vector<int> nums = {};
  int tam = 1000000;

  for (int i = 0; i < tam; i++) {
    int a = rand() % 1000;
    int b = rand() % 1000;
    nums.push_back(a - b);
  }

  // print(nums);

  // vector<int> a{90, 26, 58, 170, 45, 75, 90, 802, 24, 2, 66};
  auto start = chrono::high_resolution_clock::now();
  RadixSort(nums);
  auto end = chrono::high_resolution_clock::now();
  double time_taken = chrono::duration_cast<chrono::nanoseconds>(end - start).count();
  // print(nums);
  time_taken *= 1e-9;
  cout << "Time taken by program is : " << fixed << time_taken << " sec" << endl;
  return 0;
}
