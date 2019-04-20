#include <iostream>
#include <vector>
#include <cstdlib>
#include "sort_methods.cpp"

using namespace std;

void main_menu();
void bucket_menu(MPlayer *mplayer, MyWindow *mywindow, SortView *sortview, vector<int> array, int num_min, int num_max);
vector<int> build_array(int size, int min_value, int max_value, bool repeat);
void generateNumbers(vector<int> &numbers, int size, int min_value, int max_value, bool repeate);

int main()
{
    main_menu();

    return 0;
}

void main_menu()
{
    srand(time(NULL));
    char name_method[100];
    string text_colors[10];
    int max_value = 500, min_value = 0;
    int size = 100;
    bool repeat_value = false;

    vector<int> array = build_array(size, min_value, max_value, repeat_value);

    int op = 0;

    SortView *sortview;
    MyWindow *mywindow;
    MPlayer *mplayer;

    while (true)
    {
        system("clear");
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
            do
            {
                cout << "---------------------------------------------------------------------------" << endl;
                cout << "Vetor com valores repetidos?(0 - nao, 1 - sim) ";
                cin >> repeat_value;
                repeat_value = (repeat_value == 1) ? true : false;
                cout << "Tamanho do vetor(max 500): ";
                cin >> size;
                cout << "Maior valor no vetor(max 500): ";
                cin >> max_value;
                cout << "Menor valor no vetor(min 0): ";
                cin >> min_value;
            } while ((size > 500 || size < 10) || (max_value > 500 || max_value <= min_value) || (min_value < 0 || min_value >= max_value) || (repeat_value == false && max_value < size));

            array = build_array(size, min_value, max_value, repeat_value);
            break;
        case 2:
            //Cores:  i = red, j = blue, end + init = index pivot = yelow
            sprintf(name_method, "QuickSort\ttamanho: %ld", array.size());
            mywindow = new MyWindow();
            mplayer = new MPlayer(mywindow, name_method, {"incrementador", "decrementador", "pivo"}, "rby");
            sortview = new SortView(mplayer, mywindow);
            sortview->set_thick(size); // redimensiona tamanho da barra de acorodo com o tamanho do vetor
            quickSort(sortview, array_cp, 0, array.size() - 1);
            sortview->view_lock();
            delete (sortview);
            delete (mplayer);
            delete (mywindow);
            break;
        case 3:
            //Cores: begin1 = red, begin2 = blue, middle = yellow, begin+i = merge = green
            sprintf(name_method, "MergeSort\ttamanho: %ld", array.size());
            mywindow = new MyWindow();
            mplayer = new MPlayer(mywindow, name_method, {"inicio1", "inicio2", "meio", "mesclagem"}, "rbyg");
            sortview = new SortView(mplayer, mywindow);
            sortview->set_thick(size); // redimensiona tamanho da barra de acorodo com o tamanho do vetor
            mergeSort(sortview, array_cp, 0, array.size() - 1);
            sortview->view_lock();
            delete (sortview);
            delete (mplayer);
            delete (mywindow);
            break;
        case 4:
            bucket_menu(mplayer, mywindow, sortview, array_cp, min_value, max_value);
            break;

        default:
            break;
        }
    }
}

void bucket_menu(MPlayer *mplayer, MyWindow *mywindow, SortView *sortview, vector<int> array, int num_min, int num_max)
{
    int bucket_qtt = 2;
    char name_method[100];

    int op = 0;

    while (true)
    {
        system("clear");
        cout << "---------------------------------------------------------------------------" << endl;
        cout << "\t(1) - Quantidade de Baldes" << endl;
        cout << "\t(2) - Bucket com QuickSort" << endl;
        cout << "\t(3) - Bucket com MergeSort" << endl;
        cout << "\t(4) - Retornar ao Menu Principal" << endl;
        cout << "\t(0) - Fechar Programa" << endl;
        cout << "---------------------------------------------------------------------------" << endl;
        cout << "Digite uma opcao: ";
        cin >> op;

        switch (op)
        {
        case 0:
            exit(0);
        case 1:
            do
            {
                cout << "---------------------------------------------------------------------------" << endl;
                cout << "Digite o numero de Baldes(max 10): ";
                cin >> bucket_qtt;
            } while (bucket_qtt > 10 || bucket_qtt < 1);
            break;
        case 2:
            // Cores: j = magenta, count_bucket = ciano, i = red, j = blue, end + init = index pivot = yelow
            sprintf(name_method, "BucketSort(QuickSort)\ttamanho: %ld\tbaldes: %d", array.size(), bucket_qtt);
            mywindow = new MyWindow();
            mplayer = new MPlayer(mywindow, name_method, {"varredura", "alocacao", "incrementador", "decrementador", "pivo"}, "mcrby");
            sortview = new SortView(mplayer, mywindow);
            sortview->set_thick(array.size()); // redimensiona tamanho da barra de acorodo com o tamanho do vetor
            bucketSort(sortview, array, bucket_qtt, num_max, num_min, 0);
            sortview->view_lock();
            delete (sortview);
            delete (mplayer);
            delete (mywindow);
            break;
        case 3:
            // Cores: j = magenta, count_bucket = ciano, begin1 = red, begin2 = blue, middle = yellow, begin+i = merge = green
            sprintf(name_method, "BucketSort(MergeSort)\ttamanho: %ld\tbaldes: %d", array.size(), bucket_qtt);
            mywindow = new MyWindow();
            mplayer = new MPlayer(mywindow, name_method, {"varredura", "alocacao", "inicio1", "inicio2", "meio", "mesclagem"}, "mcrbyg");
            sortview = new SortView(mplayer, mywindow);
            sortview->set_thick(array.size()); // redimensiona tamanho da barra de acorodo com o tamanho do vetor
            bucketSort(sortview, array, bucket_qtt, num_max, num_min, 1);
            sortview->view_lock();
            delete (sortview);
            delete (mplayer);
            delete (mywindow);
            break;
        case 4:
            main_menu();
            break;

        default:
            break;
        }
    }
}

vector<int> build_array(int size, int min_value, int max_value, bool repeate)
{
    vector<int> array(size, 0);
    generateNumbers(array, size, min_value, max_value, repeate);
    return array;
}

void generateNumbers(vector<int> &numbers, int size, int min_value, int max_value, bool repeate)
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