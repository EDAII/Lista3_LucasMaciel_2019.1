#include <iostream>
#include <vector>
#include "sort_methods.cpp"

using namespace std;

int main()
{
    int max_value = 1000, min_value = 0;
    vector<int> vetor = {250, 1, 2, 3, 5, 4, 990, 1, 987, 100, 55, 66, 251};
    // quickSort(vetor, 0, vetor.size() - 1);
    mergeSort(vetor, 0, vetor.size() - 1);

    int bucket_qtt = 4;
    // bucketSort(vetor, bucket_qtt, max_value, min_value);
    for (int i = 0; i < vetor.size(); i++)
    {
        cout << vetor[i] << " ";
    }
    cout << endl;
    return 0;
}