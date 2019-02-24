#include "SortingTests.hpp"

using namespace std;

const int SIZE = 10000;

int main()
{
    int random_array[SIZE];

    generateRandomArray(random_array, SIZE);

    cout << "Random Array\n";
    cout << "Merge Sort: " << mergeSortTest(random_array, SIZE) << endl;
    cout << "Selection Sort: " << sortTest(&selectionSort, random_array, SIZE) << endl;
    cout << "Insertion Sort: " << sortTest(&insertionSort, random_array, SIZE) << endl;

    cout << endl;

    int ascending_array[SIZE];

    generateAscendingArray(ascending_array, SIZE);

    cout << "Ascending Array\n";
    cout << "Merge Sort: " << mergeSortTest(ascending_array, SIZE) << endl;
    cout << "Selection Sort: " << sortTest(&selectionSort, ascending_array, SIZE) << endl;
    cout << "Insertion Sort: " << sortTest(&insertionSort, ascending_array, SIZE) << endl;

    cout << endl;

    int descending_array[SIZE];

    generateDescendingArray(descending_array, SIZE);

    cout << "Descending Array\n";
    cout << "Merge Sort: " << mergeSortTest(descending_array, SIZE) << endl;
    cout << "Selection Sort: " << sortTest(&selectionSort, descending_array, SIZE) << endl;
    cout << "Insertion Sort: " << sortTest(&insertionSort, descending_array, SIZE) << endl;

    cout << endl;

    int last_ten_array[SIZE];

    generateLastTenRandomArray(last_ten_array, SIZE);

    cout << "Last Ten Random Array\n";
    cout << "Merge Sort: " << mergeSortTest(last_ten_array, SIZE) << endl;
    cout << "Selection Sort: " << sortTest(&selectionSort, last_ten_array, SIZE) << endl;
    cout << "Insertion Sort: " << sortTest(&insertionSort, last_ten_array, SIZE) << endl;

    cout << endl;

    int few_array[SIZE];

    generateFewRandomArray(few_array, SIZE);

    cout << "Few Random Array\n";
    cout << "Merge Sort: " << mergeSortTest(few_array, SIZE) << endl;
    cout << "Selection Sort: " << sortTest(&selectionSort, few_array, SIZE) << endl;
    cout << "Insertion Sort: " << sortTest(&insertionSort, few_array, SIZE) << endl;

    cout << endl;

}
