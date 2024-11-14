#include <iostream>
#include <vector>
#include <cstdlib> // for rand()
#include <ctime>   // for time()
#include <chrono>  // for timing

using namespace std;

// Deterministic Quick Sort
void quickSortDeterministic(vector<int> &arr, int low, int high);
int partitionDeterministic(vector<int> &arr, int low, int high);

// Randomized Quick Sort
void quickSortRandomized(vector<int> &arr, int low, int high);
int partitionRandomized(vector<int> &arr, int low, int high);

// Measure execution time
double measureTime(void (*sortFunc)(vector<int> &, int, int), vector<int> arr)
{
    auto start = chrono::high_resolution_clock::now();
    sortFunc(arr, 0, arr.size() - 1);
    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double> elapsed = end - start;
    return elapsed.count();
}

void analyzeQuickSort(const vector<int> &arr)
{
    cout << "Array size: " << arr.size() << endl;

    vector<int> arrCopy = arr;

    double deterministicTime = measureTime(quickSortDeterministic, arrCopy);
    cout << "Deterministic Quick Sort Time: " << deterministicTime << " seconds" << endl;

    arrCopy = arr;
    double randomizedTime = measureTime(quickSortRandomized, arrCopy);
    cout << "Randomized Quick Sort Time: " << randomizedTime << " seconds" << endl;
}

// Deterministic Quick Sort Implementation
void quickSortDeterministic(vector<int> &arr, int low, int high)
{
    if (low < high)
    {
        int pi = partitionDeterministic(arr, low, high);
        quickSortDeterministic(arr, low, pi - 1);
        quickSortDeterministic(arr, pi + 1, high);
    }
}

int partitionDeterministic(vector<int> &arr, int low, int high)
{
    int pivot = arr[high];
    int i = low - 1;
    for (int j = low; j < high; j++)
    {
        if (arr[j] < pivot)
        {
            i++;
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i + 1], arr[high]);
    return i + 1;
}

// Randomized Quick Sort Implementation
void quickSortRandomized(vector<int> &arr, int low, int high)
{
    if (low < high)
    {
        int pi = partitionRandomized(arr, low, high);
        quickSortRandomized(arr, low, pi - 1);
        quickSortRandomized(arr, pi + 1, high);
    }
}

int partitionRandomized(vector<int> &arr, int low, int high)
{
    int pivotIndex = low + rand() % (high - low + 1); // Choosing a random pivot
    swap(arr[pivotIndex], arr[high]);                 // Move pivot to end
    return partitionDeterministic(arr, low, high);
}

int main()
{
    srand(time(0)); // Seed for random number generation
    vector<int> arrSizes = {100, 1000, 5000};

    for (int size : arrSizes)
    {
        vector<int> arr(size);
        for (int &elem : arr)
        {
            elem = rand() % 10000; // Fill array with random numbers
        }

        cout << "\nTesting with array of size " << size << ":" << endl;
        analyzeQuickSort(arr);
    }

    return 0;
}
