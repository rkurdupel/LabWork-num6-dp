#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;


double** createMatrix(int n, int method_choice) {
    double** a = nullptr;

    if (method_choice == 1) {
        a = (double**) malloc(n * sizeof(double*));
        for (int i = 0; i < n; i++)
            a[i] = (double*) malloc(n * sizeof(double));
    }
    else if (method_choice == 2) {
        a = (double**) calloc(n, sizeof(double*));
        for (int i = 0; i < n; i++)
            a[i] = (double*) calloc(n, sizeof(double));
    }
    else if (method_choice == 3) {
        a = new double*[n];
        for (int i = 0; i < n; i++)
            a[i] = new double[n];
    }

    return a;
}


void fillKeyboard(double** a, int n) {
    cout << "Введіть елементи матриці:\n";
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            cin >> a[i][j];
}


void fillRandom(double** a, int n) {
    srand(time(0));
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            a[i][j] = (rand() % 2001 - 1000) / 100.0;
}


void printMatrix(double** a, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++)
            cout << a[i][j] << "\t";
        cout << "\n";
    }
}


void maxToDiagonal_index(double** a, int n) {
    for (int d = 0; d < n; d++) {

        double maxVal = a[d][d];
        int max_i = d, max_j = d;

        for (int i = d; i < n; i++)
            for (int j = d; j < n; j++)
                if (a[i][j] > maxVal) {
                    maxVal = a[i][j];
                    max_i = i;
                    max_j = j;
                }

        double temp = a[d][d];
        a[d][d] = a[max_i][max_j];
        a[max_i][max_j] = temp;
    }
}


void maxToDiagonal_pointer(double** a, int n) {
    for (int d = 0; d < n; d++) {

        double maxVal = *(*(a + d) + d);
        int max_i = d, max_j = d;

        for (int i = d; i < n; i++)
            for (int j = d; j < n; j++)
                if (*(*(a + i) + j) > maxVal) {
                    maxVal = *(*(a + i) + j);
                    max_i = i;
                    max_j = j;
                }

        double temp = *(*(a + d) + d);
        *(*(a + d) + d) = *(*(a + max_i) + max_j);
        *(*(a + max_i) + max_j) = temp;
    }
}


int firstRowNoPositive_index(double** a, int n) {
    for (int i = 0; i < n; i++) {
        bool pos = false;
        for (int j = 0; j < n; j++)
            if (a[i][j] > 0) {
                pos = true;
                break;
            }
        if (!pos) return i;
    }
    return -1;
}

int firstRowNoPositive_pointer(double** a, int n) {
    for (int i = 0; i < n; i++) {
        bool pos = false;
        for (int j = 0; j < n; j++)
            if (*(*(a + i) + j) > 0) {
                pos = true;
                break;
            }
        if (!pos) return i;
    }
    return -1;
}





void freeMemory(double** a, int n, int method_choice) {
    if (method_choice == 1 || method_choice == 2) {
        for (int i = 0; i < n; i++) free(a[i]);
        free(a);
    } else {
        for (int i = 0; i < n; i++) delete[] a[i];
        delete[] a;
    }
}


int main() {
    int n, method_choice, fill_type;

    cout << "Введіть розмір квадратної матриці NxN: ";
    cin >> n;

    cout << "Метод виділення пам'яті:\n1 - malloc\n2 - calloc\n3 - new\n";
    cin >> method_choice;

    double** a = createMatrix(n, method_choice);

    cout << "Заповнення:\n1 - клавіатура\n2 - випадкові числа\n";
    cin >> fill_type;

    if (fill_type == 1) fillKeyboard(a, n);
    else fillRandom(a, n);

    cout << "\nПочаткова матриця:\n";
    printMatrix(a, n);

    maxToDiagonal_index(a, n);
    cout << "\nПісля перестановки (індекси):\n";
    printMatrix(a, n);

    int r1 = firstRowNoPositive_index(a, n);
    cout << "Перший рядок без додатніх (індекси): " << r1 << endl;

    maxToDiagonal_pointer(a, n);
    cout << "\nПісля перестановки (вказівники):\n";
    printMatrix(a, n);

    int r2 = firstRowNoPositive_pointer(a, n);
    cout << "Перший рядок без додатніх (вказівники): " << r2 << endl;

    freeMemory(a, n, method_choice);
    return 0;
}
