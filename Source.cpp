#include <iostream>
#include <iomanip>
#include <vector>
#include <random>
#include <conio.h>
#include <fstream>
#include <windows.h> 

using namespace std;

void menu_dlya_vibora_vvoda() {
    cout <<" Меню ввода"<< endl;
    cout << " 1-если вы хотите заполнить ее случайными значениями" << endl;
    cout << " 2-если вы хотите ввести ее вручную" << endl;
    cout << " 3-если вы хотите заполнить матрицу элементами из файла" << endl;
}

void menu_obshee() {
    cout << " Меню" << endl;
    cout << " 1-если вы хотите создать матрицу" << endl;
    cout << " 2-если вы хотите загрузить дефолтную матрицу" << endl;
    cout << " 3-если вы хотите загрузить прошлую матрицу" << endl;
    cout << " 4-если вы хотите отсортировать матрицу" << endl;
    cout << " 5-если вы хотите изменить конкретный элемент матрицы" << endl;
    cout << " 6-если вы хотите посмотреть елементы матрицы и изменить конкретные при необходимости" << endl;
    cout << " 7-если вы хотите создать новую матрицу" << endl;
    cout << " 8-если вы хотите выйти" << endl;
}

vector <int> read_matrix(string& file) {
    vector <int> numbers;
    ifstream f(file, ios::binary);

    if (!f) {
        cerr << "Ошибка открытия файла!" <<endl;
        return numbers;
    }

    int number;
    while (f.read(reinterpret_cast<char*>(&number), sizeof(number))) {
        numbers.push_back(number);
    }

    f.close();
    return numbers;
}

void write_matrix(string& file, vector <int> numbers) {
    ofstream f(file, ios::out | ios::binary);

    if (!f) {
        cerr << "Ошибка открытия файла!" << endl;
        return;
    }

    for (int number : numbers) {
        f.write(reinterpret_cast<const char*>(&number), sizeof(number));
    }
    f.close();
}




// создание класса матрица
class Matrix {
private:
    vector<vector<int>> data;
    int rows;
    int cols;

public:
    // Конструктор для создания матрицы заданного размера
    Matrix(int r, int c) : rows(r), cols(c) {
        data.resize(rows, vector<int>(cols, 0)); // Инициализация нулями
    }

    // Метод для установки значения в ячейку матрицы
    void setValue(int r, int c, int value) {
        if (r >= 0 && r < rows && c >= 0 && c < cols) {
            data[r][c] = value;
        }
        else {
            cerr << "Вышли за границу" << endl;
        }
    }

    // Метод для получения значения из ячейки матрицы
    int getValue(int r, int c) const {
        if (r >= 0 && r < rows && c >= 0 && c < cols) {
            return data[r][c];
        }
        else {
            cerr << "Вышли за границу" << endl;
            return -1;
        }
    }

    // Метод для вывода матрицы на экран
    void display() const {
        for (const auto& row : data) {
            for (int elem : row) {
                cout <<setw(5)<< elem << " ";
            }
            cout << endl;
        }
    }

    void display_color(int stroka,int stolbec,int n,int m) const {
        HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m;j++) {
                if (stroka == i && stolbec == j) {
                    SetConsoleTextAttribute(console,2);   
                }
                else {
                    SetConsoleTextAttribute(console, 7);
                }
                cout << setw(5) << data[i][j] << " ";
            }
            cout << endl;
        }
    }

    // Метод для получения количества строк
    int getRows() const {
        return rows;
    }

    // Метод для получения количества столбцов
    int getCols() const {
        return cols;
    }

    //метод ля изменений размера матрицы
    void resize(int newRows, int newCols) {
        vector<vector<int>> newData(newRows, vector<int>(newCols, 0));

        // Копируем существующие данные в новую матрицу
        for (int i = 0; i < min(rows, newRows); ++i) {
            for (int j = 0; j < min(cols, newCols); ++j) {
                newData[i][j] = data[i][j];
            }
        }

        // Обновляем размеры и данные матрицы
        rows = newRows;
        cols = newCols;
        data = newData;
        
    }

    //для изменения размера под дефолтную матрицу
    void defolt_matrix_comletion( vector <int> numbers_defolt) {
        int count = 0;
        for (int i = 0; i < 10; i++) {
            for (int j = 0; j < 10; j++) {
                data[i][j] = numbers_defolt[count];
                count++;
            }
        }
    }

    //для изменения размера под последнюю матрицу
    void last_matrix_comletion(vector <int> numbers_last_matrix,int n,int m) {
        int count = 0;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                data[i][j] = numbers_last_matrix[count];
                count++;
            }
        }
    }

};

// нахождение кол-ва отрицательных элементов в столбцах
int* countNegatives(Matrix& matrix) {
    int* arr = new int[matrix.getCols()];

    for (int j = 0; j < matrix.getCols(); j++) {
        int count = 0;
        for (int i = 0; i < matrix.getRows(); i++) {
            if (matrix.getValue(i, j) < 0) {
                count++;
            }
        }
        arr[j] = count;
    }

    return arr;
}

// Функция для слияния двух подмассивов
void merge(int* arr, int* indexArr, int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    int* L = new int[n1];
    int* R = new int[n2];
    int* indexL = new int[n1];
    int* indexR = new int[n2];

    for (int i = 0; i < n1; i++) {
        L[i] = arr[left + i];
        indexL[i] = indexArr[left + i];
    }

    for (int j = 0; j < n2; j++) {
        R[j] = arr[mid + 1 + j];
        indexR[j] = indexArr[mid + 1 + j];
    }

    int i = 0, j = 0, k = left;

    while (i < n1 && j < n2) {
        if (L[i] >= R[j]) {
            arr[k] = L[i];
            indexArr[k] = indexL[i];
            i++;
        }
        else {
            arr[k] = R[j];
            indexArr[k] = indexR[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        arr[k] = L[i];
        indexArr[k] = indexL[i];
        i++;
        k++;
    }

    while (j < n2) {
        arr[k] = R[j];
        indexArr[k] = indexR[j];
        j++;
        k++;
    }

    delete[] L;
    delete[] R;
    delete[] indexL;
    delete[] indexR;
}

// Функция сортировки слиянием
void mergeSort(int* arr, int* indexArr, int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;

        mergeSort(arr, indexArr, left, mid);
        mergeSort(arr, indexArr, mid + 1, right);
        merge(arr, indexArr, left, mid, right);
    }
}

// Сортировка столбцов матрицы по количеству отрицательных элементов
void sortColumnsByNegatives(Matrix& matrix) {
    int cols = matrix.getCols();
    int* negCounts = countNegatives(matrix);

    // Индексы столбцов
    int* indices = new int[cols];
    for (int i = 0; i < cols; i++) {
        indices[i] = i;
    }

    // Сортируем по количеству отрицательных элементов
    mergeSort(negCounts, indices, 0, cols - 1);

    // Создаем новую матрицу для хранения отсортированных столбцов
    Matrix sortedMatrix(matrix.getRows(), matrix.getCols());

    for (int j = 0; j < cols; j++) {
        for (int i = 0; i < matrix.getRows(); i++) {
            sortedMatrix.setValue(i, j, matrix.getValue(i, indices[j]));
        }
    }

    // Копируем отсортированные данные обратно в исходную матрицу
    matrix = sortedMatrix;

    delete[] negCounts;
    delete[] indices;
}

int main() {
    setlocale(LC_ALL, "russian");

    int n, m, valume, numb, vvod, a, b, elem, stroka = 0, stolbec = 0, fut = 0,flag=0;
    char prosmotr, vopros;

    string file = "matrix.bin";//файл для чтения
    string file1 = "matrix2.bin";//файл для записи
    
    //матрицы для проверки
    string file_dlya_proverki_1 = "martrix_proverka_1";
    string file_dlya_proverki_2 = "martrix_proverka_2";
    string file_dlya_proverki_3 = "martrix_proverka_3";

    //векторы для чтения из файла
    vector <int> vect;
    
    vector <int> numbers_defolt = read_matrix(file);//массив со значениями матрицы из дефолтного файла

    cout << "Введите размеры" << endl;
    cin >> n >> m;
    if (n <= 0 || m <= 0) {
        cout << "неправильные значения" << endl;
        while (n <= 0 || m <= 0) {
            cout << "Введите размеры" << endl;
            cin >> n >> m;
        }
    }
    int rows_reserve = n;
    int cols_reserve = m;

    //для создания рандомных значений в диапозоне
    std::random_device rd;
    std::mt19937 eng(rd());
    std::uniform_int_distribution<> distr(-100, 100);


    Matrix matrix(n, m); // Создаем матрицу nxm


    

    system("cls");
    while (true) {
       
        //меню
        menu_obshee();
        cin >> numb;
        switch (numb) {
            
        case 1: {//создать матрицу 
            flag = 1;
            system("cls");
            menu_dlya_vibora_vvoda();
            cin >> vvod;
            switch (vvod) {
            case 1: {//ввод рандомом
                // Устанавливаем значения в матрице
                for (int i = 0; i < n; i++) {
                    for (int j = 0; j < m; j++) {
                        int random_number = distr(eng);
                        matrix.setValue(i, j, random_number);
                    }
                }
                // Выводим матрицу на экран
                //cout << "Исходная матрица:" << endl;
                //matrix.display();
                break;
            }

            case 2: {//заполнение вручную
                system("cls");
                for (int i = 0; i < n; i++) {
                    for (int j = 0; j < m; j++) {
                        cin >> valume;
                        matrix.setValue(i, j, valume);
                    }
                }
                // Выводим матрицу на экран
                //cout << "Исходная матрица:" << endl;
                break;
            }
            case 3: {//заполнение из бинарного файла
                fut = 0;
                system("cls");
                vector <int> numbers = read_matrix(file);//массив со значениями матрицы из файла
                for (int i = 0; i < n; i++) {
                    for (int j = 0; j < m; j++) {
                        matrix.setValue(i, j, numbers[fut]);
                        fut++;
                    }
                }
                break;
            }
            default:
                cout << "неверный выбор";
            }

            for (int i = 0; i < n; i++) {
                for (int j = 0; j < m; j++) {
                    vect.push_back(matrix.getValue(i, j));
                }
            }
            
            write_matrix(file1, vect);
            vect.clear();
            system("cls");
            matrix.display();
            break;
        }
        case 2: {//просмотр дефолтной матрицы
            flag = 1;
            system("cls");
            n = 10;
            m = 10;
            matrix.resize(n, m);
            matrix.defolt_matrix_comletion(numbers_defolt);
            matrix.display();
            break;
        }
        case 3: { //просмотр прошлой матрицы
            system("cls");
            if (flag == 1) {
                n = rows_reserve;
                m = cols_reserve;
                vector <int> numbers_last = read_matrix(file1);//массив со значениями матрицы из последнего созданного файла
                matrix.resize(n, m);
                matrix.last_matrix_comletion(numbers_last, n, m);
                matrix.display();
                break;
            }
            else {
                cout << "Матрица не создана, для начала создайте ее" << endl;
                break;
            }
        }

        case 4://сортировка
            system("cls");
            if (flag == 1) {
                sortColumnsByNegatives(matrix);
                matrix.display();
                break;
            }
            else {
                cout << "Матрица не создана, для начала создайте ее" << endl;
                break;
            }
        case 5://изменение конкретного элемента
            system("cls");
            if (flag == 1) {
                cout << "введите координаты элемента, который выхотите поменять (строчка и столбец)" << endl;
                cin >> a >> b;
                cout << matrix.getValue(a - 1, b - 1) << endl;
                cout << "введите новое значение" << endl;
                cin >> elem;
                matrix.setValue(a - 1, b - 1, elem);
                system("cls");
                matrix.display();
                break;
            }
            else {
                cout << "Матрица не создана, для начала создайте ее" << endl;
                break;
            }
        case 6: {//редактор
            system("cls");
            if (flag == 1) {
                matrix.display_color(stroka, stolbec, n, m);
                //color_text(matrix.getValue(0, 0), RED);
                //cout << matrix.getValue(0, 0) << endl;
                cout << "Если вы хотите заменить текущий элемент, нажмите пробел" << endl;
                while (true) {
                    prosmotr = _getch();
                    if (prosmotr == 72) {
                        if (stroka > 0)
                        {
                            stroka--;
                            system("cls");
                            matrix.display_color(stroka,stolbec,n,m);
                            //color_text(matrix.getValue(stroka, stolbec),RED);
                            //cout << matrix.getValue(stroka, stolbec) << endl;
                            cout << "Если вы хотите заменить текущий элемент, нажмите пробел" << endl;
                        }

                    }
                    else if (prosmotr == 75) {
                        if (stolbec > 0)
                        {
                            stolbec--;
                            system("cls");
                            matrix.display_color(stroka, stolbec, n, m);
                            //cout << matrix.getValue(stroka, stolbec) << endl;
                            cout << "Если вы хотите заменить текущий элемент, нажмите пробел" << endl;
                        }

                    }
                    else if (prosmotr == 77) {
                        if (stolbec < matrix.getCols())
                        {
                            stolbec++;
                            system("cls");
                            matrix.display_color(stroka, stolbec, n, m);
                            //cout << matrix.getValue(stroka, stolbec) << endl;
                            cout << "Если вы хотите заменить текущий элемент, нажмите пробел" << endl;
                        }
                    }

                    else if (prosmotr == 80) {
                        if (stolbec < matrix.getRows())
                        {
                            stroka++;
                            system("cls");
                            matrix.display_color(stroka, stolbec, n, m);
                            //cout << matrix.getValue(stroka, stolbec) << endl;
                            cout << "Если вы хотите заменить текущий элемент, нажмите пробел" << endl;
                        }

                    }
                    else if (prosmotr == 32) {
                        cout << "введите новое значение" << endl;
                        cin >> elem;
                        matrix.setValue(stroka, stolbec, elem);
                        system("cls");
                        matrix.display_color(stroka, stolbec, n, m);
                        cout << "Если вы хотите заменить текущий элемент, нажмите пробел" << endl;
                    }
                    else if (prosmotr == 13) {
                        system("cls");
                        matrix.display();
                        break;
                    }
                }
            }
            else {
                cout << "Матрица не создана, для начала создайте ее" << endl;
                break;
            }
            break;
        }

        case 7: {//пересоздание объекта
            
            system("cls");
            cout << "Введите размеры" << endl;
            cin >> n >> m;
            
            if (n <= 0 || m <= 0) {
                cout << "неправильные значения" << endl;
                while (n <= 0 || m <= 0) {
                    cout << "Введите размеры" << endl;
                    cin >> n >> m;
                }
            }
            rows_reserve = n;
            cols_reserve = m;
            matrix.resize(n, m);
            //matrix.display();
            flag = 0;
            break;
        }
        case 8:
            return 0;
        default:
            cout << "неверный выбор" << endl;
        }
    }

    return 0;
}