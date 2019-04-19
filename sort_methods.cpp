// g++ test.cpp -o prog -lgraph -lX11

#include <iostream>
#include <vector>
#include "sort_view.hpp"

using namespace std;

void swap(int *val1, int *val2)
{
    int aux;
    aux = *val1;
    *val1 = *val2;
    *val2 = aux;
}

int partition(vector<int> &array, int init , int end)
{
    int pivot = array[end];
    int i = init - 1;
    for (int j = init; j < end; j++)
    {
        if (array[j] < pivot)
        {
            i = i + 1;
            swap(array[i], array[j]);
        }
        sortview.show(array, {i, j, pivot}, "rby");
    }
    if (array[end] < array[i+1])
        swap(array[i+1], array[end]);
    return i+1;
}

void quickSort(vector<int> &array, int init, int end)
{
    if (init < end)
    {
        int p = partition(array, init, end);
        sortview.show(array, {init, end, p}, "rby");
        quickSort(array, init, p - 1);
        quickSort(array, p + 1, end);
    }
}


void merge(vector<int> &array, int begin, int middle, int end)
{
    /*
        Cores:
        begin1 = red, begin2 = blue, middle = yellow, begin+i = merge = green
    */
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
        sortview.show(array, {begin1, begin2, middle}, "rby");
    }
    while (begin1 <= middle)
    {
        array_aux.push_back(array[begin1]);
        begin1++;
        sortview.show(array, {begin1, begin2, middle}, "rby");
    }
    while (begin2 <= end)
    {
        array_aux.push_back(array[begin2]);
        begin2++;
        sortview.show(array, {begin1, begin2, middle}, "rby");
    }
    for (int i = 0; i < array_aux.size(); i++)
    {
        array[begin + i] = array_aux[i];
        sortview.show(array, {begin+i}, "g");
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

void bucketSort(vector<int> &array, int bucket_qtt, int num_max, int num_min, int type_sort = 0)
{
    // faixas de valores dado o range do vetor
    int bucket_step = (num_max - num_min) / bucket_qtt;
    // vetor de buckets, vetor[qtd_buckets][nums]
    vector<vector<int>> bucket_array;
    bucket_array.reserve(bucket_qtt);

    auto sort = quickSort; // default
    //escolher qual metodo sera usado
    if (type_sort == 0)
    {
        sort = quickSort;
    }
    else if (type_sort == 1)
    {
        sort = mergeSort;
    }

    // cria os buckets
    // para conseguir jogar os buckets no proprio vetor, contador para fixalos e nao mais dar swap
    int count_bucket = 0;
    for (int i = 0, j = 0; i < bucket_qtt; i++)
    {
        for (j = 0; j < array.size(); j++)
        {
            if (array[j] <= bucket_step * (i + 1) && array[j] > bucket_step * (i))
            {
                // bucket_array[i].push_back(array[j]);
                swap(array[j], array[count_bucket]);
                count_bucket++;
            }
        }

        // ja realiza a ordenacao parcial no vetor (bucket reservado no proprio vetor)
        sort(array, i, j - 1);  // j-1 pois o j excede o tamanho do bucket quando sai do for anterior
    }
}