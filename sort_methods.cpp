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

void merge(vector<int> &array, int begin, int middle, int end)
{
    int begin1 = begin, begin2 = middle + 1;
    int size = end - begin + 1;
    vector<int> array_aux;
    // array_aux.reserve(size);
    while (begin1 <= middle && begin2 <= end)
    {
        if (array[begin1] < array[begin2])
        {
            array_aux.push_back(array[begin1]);
            begin1++;
        }
        else
        {
            array_aux.push_back(array[begin2]);
            begin2++;
        }
    }
    while (begin1 <= middle)
    {
        array_aux.push_back(array[begin1]);
        begin1++;
    }
    while (begin2 <= end)
    {
        array_aux.push_back(array[begin2]);
        begin2++;
    }
    for (int i = 0; i < array_aux.size(); i++)
    {
        array[begin + i] = array_aux[i];
    }
}

void mergeSort(vector<int> &array, int begin, int end)
{
    if (begin < end)
    {
        int middle = (begin + end) / 2;
        mergeSort(array, begin, middle);
        mergeSort(array, middle + 1, end);
        merge(array, begin, middle, end);
    }
}

void bucketSort(vector<int> &array, int bucket_qtt, int num_max, int num_min)
{
    // faixas de valores dado o range do vetor
    int bucket_step = (num_max - num_min) / bucket_qtt;
    // vetor de buckets, vetor[qtd_buckets][nums]
    vector<vector<int>> bucket_array;
    bucket_array.reserve(bucket_qtt);

    for (int i = 0; i < array.size(); i++)
    {
        for (int j = 1; (bucket_step * j) <= num_max; j++)
        {
            if (array[i] <= bucket_step * j && array[i] > bucket_step * (j - 1))
            {
                bucket_array[j - 1].push_back(array[i]);
            }
        }
    }

    // buckets gerados
    quickSort(bucket_array[0], 0, bucket_array[0].size() - 1);
}