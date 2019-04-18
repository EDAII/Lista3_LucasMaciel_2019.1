#include <iostream>
#include <vector>
#include <cstdlib>
#include "sort_methods.cpp"

using namespace std;

void generateNumbers(vector<int> &numbers, int size, int max_value, int min_value);

int main()
{
    srand(time(NULL));
    int max_value = 400, min_value = 0;

    const int size = 70;
    vector<int> array(size, 0);

    // for (int i = 0; i < size; i++)
    //     array[i] = (rand() % (max_value - min_value + 1) + min_value);
    generateNumbers(array, size, max_value, min_value);
    // quickSort(array, 0, array.size() - 1);
    mergeSort(array, 0, array.size() - 1);
    view_lock();

    int bucket_qtt = 4;
    // bucketSort(array, bucket_qtt, max_value, min_value, 0);
    
    return 0;
}

void generateNumbers(vector<int> &numbers, int size, int max_value, int min_value)
{
  int tempNum;			// variavel temporaria para o numero gerado
  bool found;			// alerta para numero ja usado
  
  numbers[0] = (rand() % (max_value - min_value + 1) + min_value);	// gera o primeiro numero
  
    for (int index = 1; index < size; index++)	// loop para gerar cada numero e verificar se ja existe no vetor
    {
        do
        {
	        tempNum = (rand() % (max_value - min_value + 1) + min_value);
	        found = false;

	        for (int index2 = 0; index2 < size; index2++)
                if (tempNum == numbers[index2])
                {
                    found = true;
                    tempNum = numbers[index];
                }
        } while (found != false);
        numbers[index] = tempNum;
    }	 
}