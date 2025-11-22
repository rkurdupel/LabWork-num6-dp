#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

// int* = [row1, row2, row3]
// int** = [row1[el, el, el], row2[el, el, el], row3[el, el, el]]


int** createMatrix(int n, int method_choice) {
    int** a = nullptr;

    if (method_choice == 1) {
        a = (int**) malloc(n * sizeof(int*));   
        for (int i = 0; i < n; i++) {
            a[i] = (int*) malloc(n * sizeof(int));      // just allocates dynamic memory
        }
    }

    else if (method_choice == 2) {
        a = (int**) calloc(n, sizeof(int*));
        for (int i = 0; i < n; i++) {
            a[i] = (int*) calloc(n, sizeof(int));   // allocates and sets all values = 0
        }
    }
   
    else if (method_choice == 3) {
        a = new int*[n];
        for (int i = 0; i < n; i++) {
            a[i] = new int[n];     
             // allocates memory and triggers initialization
             // (if new int[n]() - all values will be set to 0 ) 
        }
    }

    else {
        return nullptr;
    }

    return a;
}

void fillKeyboard(int** a, int n) {
    cout << "введіть елементи матриці:\n";
    // take each row one by one
    for (int i = 0; i < n; i++) {
        // set value to each el in the row (1 row -> [1, 2, 3] 2 row -> [4, 5, 6] 3 row [7, 8, 9])
        for (int j = 0; j < n; j++) {
            cin >> a[i][j];
        }
    }
}

void fillRandom(int** a, int n) {
    srand(time(0));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            a[i][j] = rand() % 50 - 10;
        }
    }
}

void printMatrix(int** a, int n) {
    cout << "матриця:\n";
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << a[i][j] << "\t";
        }
        cout << "\n";
    }
}

int maxDiagIndex(int** a, int n) {
    int mx = a[0][0];
    for (int i = 1; i < n; i++) {
        if (a[i][i] > mx) { // a[0][0] a[1][1] a[2][2] a[3][3] ...
            mx = a[i][i];
        }
    }
    return mx;
}

int maxDiagPointer(int** a, int n) {
    int mx = *(*(a + 0) + 0);

    for (int i = 1; i < n; i++) {
        int val = *(*(a + i) + i);
        if (val > mx) {
            mx = val;
        }
    }
    return mx;
}

void freeMemory(int** a, int n, int method_choice) {
    if (method_choice == 1 || method_choice == 2) {
        for (int i = 0; i < n; i++) {
            free(a[i]);
        }
        free(a);
    }
    else {
        for (int i = 0; i < n; i++) {
            delete[] a[i]; 
        }
        delete[] a; // ([][][])
    }
}

int main() {
    int n, method_choice, fill_type;

    cout << "введіть розмір квадратної матриці NxN: ";
    cin >> n;

    cout << "оберіть спосіб створення масиву:\n1 - malloc\n2 - calloc\n3 - new\n";
    cin >> method_choice;

    int** a = createMatrix(n, method_choice);

    cout << "виберіть спосіб заповнення елементів матриці:\n1 - клавіатура\n2 - випадкові числа\n";
    cin >> fill_type;

    if (fill_type == 1) {
        fillKeyboard(a, n);
    } else {
        fillRandom(a, n);
    }

    printMatrix(a, n);

    int mxIndex = maxDiagIndex(a , n);
    int mxPtr = maxDiagPointer(a , n);

    cout << "максимальний елемент головної діагоналі через індекси: " << mxIndex << endl;
    cout << "максимальний елемент головної діагоналі через вказівники: " << mxPtr << endl;

    freeMemory(a, n, method_choice);

    return 0;
}
