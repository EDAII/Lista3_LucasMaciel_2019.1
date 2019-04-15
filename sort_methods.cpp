// g++ test.cpp -o prog -lgraph -lX11

#include <iostream>
#include <vector>

using namespace std;

void swap(int *val1, int *val2)
{
    int aux;
    aux = *val1;
    *val1 = *val2;
    *val2 = aux;
}

void quickSort(vector<int> &array, int init, int end)
{
    int pivo;
    int i, j;
    int aux;
    i = init;
    j = end;
    pivo = array[(init + end) / 2];
    while (i <= j)
    {
        while (array[i] < pivo && i < end)
            i += 1;
        while (array[j] > pivo && j > init)
            j -= 1;
        if (i <= j)
        {
            // aux = array[i];
            // array[i] = array[j];
            // array[j] = aux;
            swap(array[i], array[j]);
            i += 1;
            j -= 1;
        }
        if (j > init)
            quickSort(array, init, j);
        if (i < end)
            quickSort(array, i, end);
    }
}


