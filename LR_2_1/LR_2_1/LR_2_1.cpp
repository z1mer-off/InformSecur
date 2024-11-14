#include <iostream>
#include <vector>
#include <string>

using namespace std;

//функция для проверки соответствия критериям Белла-Лападуллы
bool checkBellLaPadula(int n, int m, const vector<vector<string>>& A, const vector<int>& LS, const vector<int>& LO) {
    for (int i = 0; i < n; ++i) { //для каждого субъекта
        for (int j = 0; j < m; ++j) { //для каждого объекта
            //проверяем права доступа
            if (A[i][j].find('r') != string::npos) { //если субъект имеет право на чтение
                if (LS[i] < LO[j]) { //проверяем правило "Чтение сверху"
                    cout << "Violation: subject s" << (i + 1) << " cannot read object o" << (j + 1) << endl;
                    return false;
                }
            }
            if (A[i][j].find('w') != string::npos) { //если субъект имеет право на запись
                if (LS[i] > LO[j]) { //проверяем правило "Запись вниз"
                    cout << "Violation: subject s" << (i + 1) << " cannot write in object o" << (j + 1) << endl;
                    return false;
                }
            }
        }
    }
    return true; //система соответствует критериям
}

int main() {
    int n, m;

    //ввод количества субъектов и объектов
    cout << "Write a number of subjects (n): ";
    cin >> n;
    cout << "Write a number of objects (m): ";
    cin >> m;

    //ввод матрицы прав доступа
    vector<vector<string>> A(n, vector<string>(m));
    cout << "Write an access rights matrix (format: 'r', 'w' or nothing for lack of rights):" << endl;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            cout << "A[" << (i + 1) << "][" << (j + 1) << "]: ";
            cin >> A[i][j];
        }
    }

    //ввод уровней допуска субъектов
    vector<int> LS(n);
    cout << "Write an access levels of subjects (LS):" << endl;
    for (int i = 0; i < n; ++i) {
        cout << "LS[" << (i + 1) << "]: ";
        cin >> LS[i];
    }

    //ввод уровней секретности объектов
    vector<int> LO(m);
    cout << "Write an secrecy levels of objects (LO):" << endl;
    for (int j = 0; j < m; ++j) {
        cout << "LO[" << (j + 1) << "]: ";
        cin >> LO[j];
    }

    //проверка соответствия критериям Белла-Лападуллы
    if (checkBellLaPadula(n, m, A, LS, LO)) {
        cout << "CS meet the security criteria of Bella-Lapadull." << endl;
    }
    else {
        cout << "CS does not meet the security criteria of Bella-Lapadull." << endl;
    }

    return 0;
}
/*пример при котором критерий не выполняется:
    Input:
3
3

r w n n r w w n r
2 1 3
1 2 3

    Output:

Violation: subject s2 cannot read object o2

CS does not meet the security criteria of Bella-Lapadull.
*/