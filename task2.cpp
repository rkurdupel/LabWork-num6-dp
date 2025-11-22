#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;




int** createMatrix(int n, int method_choice) {
    int** a = nullptr;

    if (method_choice == 1) {
        a = (int**) malloc(n * sizeof(int*));   
        for (int i = 0; i < n; i++) {
            a[i] = (int*) malloc(n * sizeof(int));     
        }
    }

    else if (method_choice == 2) {
        a = (int**) calloc(n, sizeof(int*));
        for (int i = 0; i < n; i++) {
            a[i] = (int*) calloc(n, sizeof(int));   
        }
    }
   
    else if (method_choice == 3) {
        a = new int*[n];
        for (int i = 0; i < n; i++) {
            a[i] = new int[n];     
            
        }
    }

    else {
        return nullptr;
    }

    return a;
}

void fillKeyboard(int** a, int n) {
    cout << "введіть елементи матриці:\n";
  
    for (int i = 0; i < n; i++) {

        for (int j = 0; j < n; j++) {
            cin >> a[i][j];
        }
    }
}

void fillRandom(int** a, int n) {
    srand(time(0));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            a[i][j] = rand() % (23 - 6 + 1) + 6;
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
    
    cout << "\n";
}


void calculationsIndex(int** a, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            int k = i * n + j;  // for global indexes (nxn 3x3 (0->8))
            if ((a[i][j] % 2 != 0) && (k % 3 == 0)) {
                cout << a[i][j] << " ";
            }
    
        }
    }
}

void calculationsPointer(int** a, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            int k = i * n + j;  // глобальний індекс у 1D-послідовності
            if (( *(*(a + i) + j) % 2 != 0 ) && (k % 3 == 0)) {
                cout << *(*(a + i) + j) << " ";
            }
        }
    }
}


void freeMemory(int** a, int n, int method_choice) {
    if (method_choice == 1 || method_choice == 2) {
        for (int i = 0; i < n; i++)
            free(a[i]);
        free(a);
    } else {
        for (int i = 0; i < n; i++)
            delete[] a[i];
        delete[] a;
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

    if (fill_type == 1)
        fillKeyboard(a, n);
    else
        fillRandom(a, n);

    printMatrix(a, n);
    

    cout << "всі елементи крім парних , де індекс % 3 == 0 (через індекси)\n"; 
    calculationsIndex(a, n);
    cout << "\nвсі елементи крім парних , де індекс % 3 == 0 (через вказівники)\n";
    calculationsPointer(a, n);

    freeMemory(a, n, method_choice);

    return 0;
}