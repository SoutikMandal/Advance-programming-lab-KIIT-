#include <iostream>
#include <fstream>
#include <cmath>
using namespace std;

// Linear Search
int linearSearch(int arr[], int n, int key, int &comparisons)
{
    comparisons = 0;

    for (int i = 0; i < n; i++)
    {
        comparisons++;

        if (arr[i] == key)  
            return i;
    }

    return -1;
}

// Binary Search
int binarySearch(int arr[], int n, int key, int &comparisons)
{
    int low = 0, high = n - 1;
    comparisons = 0;

    while (low <= high)
    {
        comparisons++;

        int mid = (low + high) / 2;

        if (arr[mid] == key)
            return mid;
        else if (arr[mid] < key)
            low = mid + 1;
        else
            high = mid - 1;
    }

    return -1;
}

int main()
{
    ofstream file("search_graph.csv");

    file << "InputSize,LinearBest,LinearAverage,LinearWorst,BinaryBest,BinaryAverage,BinaryWorst\n";

    cout << "InputSize\tLinearBest\tLinearAvg\tLinearWorst\tBinaryBest\tBinaryAvg\tBinaryWorst\n";

    // Different input sizes up to 10000
    for (int n = 1000; n <= 10000; n += 1000)
    {
        int *arr = new int[n];

        // Sorted array for binary search
        for (int i = 0; i < n; i++)
            arr[i] = i + 1;

        int comp;

        // -------- Linear Search --------

        // Best case: first element
        linearSearch(arr, n, arr[0], comp);
        int linearBest = comp;

        // Worst case: last element
        linearSearch(arr, n, arr[n - 1], comp);
        int linearWorst = comp;

        // Average case: middle element
        linearSearch(arr, n, arr[n / 2], comp);
        int linearAverage = comp;

        // -------- Binary Search --------

        // Best case: middle element
        binarySearch(arr, n, arr[n / 2], comp);
        int binaryBest = comp;

        // Worst case: last element
        binarySearch(arr, n, arr[n - 1], comp);
        int binaryWorst = comp;

        // Average case: quarter element
        binarySearch(arr, n, arr[n / 4], comp);
        int binaryAverage = comp;

        // Display
        cout << n << "\t\t"
             << linearBest << "\t\t"
             << linearAverage << "\t\t"
             << linearWorst << "\t\t"
             << binaryBest << "\t\t"
             << binaryAverage << "\t\t"
             << binaryWorst << endl;

        // Write to CSV
        file << n << ","
             << linearBest << ","
             << linearAverage << ","
             << linearWorst << ","
             << binaryBest << ","
             << binaryAverage << ","
             << binaryWorst << "\n";

        delete[] arr;
    }

    file.close();

    cout << "\nData saved to search_graph.csv" << endl;

    return 0;
}