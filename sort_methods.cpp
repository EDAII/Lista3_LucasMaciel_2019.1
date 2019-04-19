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

int partition(SortView *sortview, vector<int> &array, int init, int end, int &count_swap)
{
    int pivot = array[end];
    int i = init - 1;
    for (int j = init; j < end; j++)
    {
        if (array[j] < pivot)
        {
            i = i + 1;
            swap(array[i], array[j]);
            count_swap++;
        }
        sortview->show(array, {i, j, pivot}, "rby", count_swap);
    }
    if (array[end] < array[i + 1])
    {
        swap(array[i + 1], array[end]);
        sortview->show(array, {i, pivot}, "ry", count_swap);
        count_swap++;
    }
    return i + 1;
}

int quickSort(SortView *sortview, vector<int> &array, int init, int end, int count_swap = 0)
{
    if (init < end)
    {
        int p = partition(sortview, array, init, end, count_swap);
        sortview->show(array, {init, end, p}, "rby", count_swap);
        count_swap = quickSort(sortview, array, init, p - 1, count_swap);
        sortview->show(array, {init, end, p}, "rby", count_swap);
        count_swap = quickSort(sortview, array, p + 1, end, count_swap);
        sortview->show(array, {init, end, p}, "rby", count_swap);
    }
    return count_swap;
}

int merge(SortView *sortview, vector<int> &array, int begin, int middle, int end, int count_swap = 0)
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
        sortview->show(array, {begin1, begin2, middle}, "rby", count_swap);
    }
    while (begin1 <= middle)
    {
        array_aux.push_back(array[begin1]);
        begin1++;
        sortview->show(array, {begin1, begin2, middle}, "rby", count_swap);
    }
    while (begin2 <= end)
    {
        array_aux.push_back(array[begin2]);
        begin2++;
        sortview->show(array, {begin1, begin2, middle}, "rby", count_swap);
    }
    for (int i = 0; i < array_aux.size(); i++)
    {
        array[begin + i] = array_aux[i];
        count_swap++;
        sortview->show(array, {begin + i}, "g", count_swap);
    }
    return count_swap;
}

int mergeSort(SortView *sortview, vector<int> &array, int begin, int end, int count_swap = 0)
{
    if (begin < end)
    {
        int middle = (begin + end) / 2;
        count_swap = mergeSort(sortview, array, begin, middle, count_swap);
        count_swap = mergeSort(sortview, array, middle + 1, end, count_swap);
        count_swap = merge(sortview, array, begin, middle, end, count_swap);
    }
    return count_swap;
}

int bucketSort(SortView *sortview, vector<int> &array, int bucket_qtt, int num_max, int num_min, int type_sort = 0, int count_swap = 0)
{
    /*
        Cores:
        j = magenta, count_bucket = ciano
    */
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
    int count_bucket_ant = 0;
    for (int i = 0, j = 0; i < bucket_qtt; i++)
    {
        /*condicao para nao fazer a varredura para o ultimo bucket,
            pois obviamente os numeros já estão no bucket correto*/
        if (i != bucket_qtt - 1)
            for (j = count_bucket; j < array.size(); j++)
            {
                sortview->show(array, {j}, "m", count_swap);
                if (array[j] <= bucket_step * (i + 1) && array[j] > bucket_step * (i))
                {
                    // bucket_array[i].push_back(array[j]);
                    swap(array[j], array[count_bucket]);
                    count_swap++;
                    sortview->show(array, {j, count_bucket}, "mc", count_swap);
                    count_bucket++;
                }
            }
        else
            count_bucket = array.size();
        // ja realiza a ordenacao parcial no vetor (bucket reservado no proprio vetor)
        //(intervalo do bucket) a contagem dos elementos em cada bucket anterior ate o bucket atual
        count_swap = sort(sortview, array, count_bucket_ant, count_bucket - 1, count_swap);
        count_bucket_ant = count_bucket - 1;
    }
    return count_swap;
}