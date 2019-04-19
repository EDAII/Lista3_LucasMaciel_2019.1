#include <iostream>
#include <vector>
#include <cstdlib>
#include "sort_methods.cpp"

using namespace std;

void main_menu();
void bucket_menu(MPlayer *mplayer, MyWindow *mywindow, SortView *sortview, vector<int> array, int num_max, int num_min);
void generateNumbers(vector<int> &numbers, int size, int max_value, int min_value, bool repeate);

int main()
{
    main_menu();

    return 0;
}

void main_menu()
{
    srand(time(NULL));
    int max_value = 500, min_value = 0;
    int count_swap = 0;
    const int size = 150;
    vector<int> array(size, 0);

    generateNumbers(array, size, max_value, min_value, false);
    int op = 0;

    SortView *sortview;
    MyWindow *mywindow;
    MPlayer *mplayer;

    while (true)
    {
        vector<int> array_cp(array.size(), 0);
        for (int i = 0; i < array.size(); i++)
            array_cp[i] = array[i];

        cout << "---------------------------------------------------------------------------" << endl;
        cout << "\t(1) - Gerar outro vetor" << endl;
        cout << "\t(2) - QuickSort" << endl;
        cout << "\t(3) - MergeSort" << endl;
        cout << "\t(4) - BucketSort" << endl;
        cout << "\t(0) - Fechar Programa" << endl;
        cout << "---------------------------------------------------------------------------" << endl;
        cout << "Digite uma opcao: ";
        cin >> op;
        switch (op)
        {
        case 0:
            exit(0);
            break;
        case 1:
            break;
        case 2:
            mywindow = new MyWindow();
            mplayer = new MPlayer(mywindow);
            sortview = new SortView(mplayer, mywindow);
            sortview->set_thick(size); // redimensiona tamanho da barra de acorodo com o tamanho do vetor
            count_swap = quickSort(sortview, array_cp, 0, array.size() - 1);
            sortview->view_lock();
            delete (sortview);
            delete (mplayer);
            delete (mywindow);
            break;
        case 3:
            mywindow = new MyWindow();
            mplayer = new MPlayer(mywindow);
            sortview = new SortView(mplayer, mywindow);
            sortview->set_thick(size); // redimensiona tamanho da barra de acorodo com o tamanho do vetor
            count_swap = mergeSort(sortview, array, 0, array.size() - 1);
            sortview->view_lock();
            delete (sortview);
            delete (mplayer);
            delete (mywindow);
            break;
        case 4:
            bucket_menu(mplayer, mywindow, sortview, array_cp, max_value, min_value);
            break;

        default:
            break;
        }
    }
}

void bucket_menu(MPlayer *mplayer, MyWindow *mywindow, SortView *sortview, vector<int> array, int num_max, int num_min)
{
    int bucket_qtt = 2;

    int op = 0;

    while (true)
    {
        cout << "---------------------------------------------------------------------------" << endl;
        cout << "\t(1) - Quantidade de Baldes" << endl;
        cout << "\t(2) - Bucket com QuickSort" << endl;
        cout << "\t(3) - Bucket com MergeSort" << endl;
        cout << "\t(0) - Fechar Programa" << endl;
        cout << "---------------------------------------------------------------------------" << endl;
        cout << "Digite uma opcao: ";
        cin >> op;

        switch (op)
        {
        case 1:
            cout << "Digite o numero de Baldes: (max 10)" << endl;
            cin >> bucket_qtt;
            break;
        case 2:
            mywindow = new MyWindow();
            mplayer = new MPlayer(mywindow);
            sortview = new SortView(mplayer, mywindow);
            sortview->set_thick(array.size()); // redimensiona tamanho da barra de acorodo com o tamanho do vetor
            bucketSort(sortview, array, bucket_qtt, num_max, num_min, 1);
            sortview->view_lock();
            delete (sortview);
            delete (mplayer);
            delete (mywindow);

        default:
            break;
        }
    }
}

void generateNumbers(vector<int> &numbers, int size, int max_value, int min_value, bool repeate)
{
    int tempNum; // variavel temporaria para o numero gerado
    bool found;  // alerta para numero ja usado

    if (repeate == true)
    {
        for (int i = 0; i < size; i++)
            numbers[i] = (rand() % (max_value - min_value + 1) + min_value);
        return;
    }

    numbers[0] = (rand() % (max_value - min_value + 1) + min_value); // gera o primeiro numero
    for (int index = 1; index < size; index++)                       // loop para gerar cada numero e verificar se ja existe no vetor
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