#include <iostream>
#include <vector>
#include "sort_methods.cpp"

using namespace std;

int main()
{
    vector<int> vetor = {1, 2, 3, 5, 4, 990, 1, 987, 100, 55, 66};
    // quickSort(vetor, 0, vetor.size() - 1);
    mergeSort(vetor, 0, vetor.size() - 1);

    for (int i = 0; i < 11; i++)
    {
        cout << vetor[i] << " ";
    }
    cout << endl;
    return 0;
}