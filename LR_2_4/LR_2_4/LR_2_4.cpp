#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <unordered_set>

using namespace std;

int main() {
    ifstream inputFile("access_matr.txt");
    if (!inputFile) {
        cerr << "File opening error!" << endl;
        return 1;
    }

    int n, m;
    inputFile >> n >> m;

    //creating matrix of access rights
    vector<vector<string>> accessMatrix(n, vector<string>(m));

    //reading matrix of access rights
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            inputFile >> accessMatrix[i][j];
        }
    }

    inputFile.close();

    //1. Список объектов, доступ к которым не задан никому
    vector<int> noAccessObjects;
    for (int j = 0; j < m; ++j) {
        bool hasAccess = false;
        for (int i = 0; i < n; ++i) {
            if (!accessMatrix[i][j].empty()) {
                hasAccess = true;
                break;
            }
        }
        if (!hasAccess) {
            noAccessObjects.push_back(j + 1); //Сохраняем номер объекта
        }
    }

    //2. Список субъектов, не обращающихся ни к каким объектам
    vector<int> noAccessSubjects;
    for (int i = 0; i < n; ++i) {
        bool hasAccess = false;
        for (int j = 0; j < m; ++j) {
            if (!accessMatrix[i][j].empty()) {
                hasAccess = true;
                break;
            }
        }
        if (!hasAccess) {
            noAccessSubjects.push_back(i + 1); //Сохраняем номер
        }
    }

    //3. Список субъектов, имеющих полный доступ ко всем объектам
    vector<int> fullAccessSubjects;
    for (int i = 0; i < n; ++i) {
        bool hasFullAccess = true;
        for (int j = 0; j < m; ++j) {
            if (accessMatrix[i][j] != "rw") {
                hasFullAccess = false;
                break;
            }
        }
        if (hasFullAccess) {
            fullAccessSubjects.push_back(i + 1); //Сохраняем номер
        }
    }

    //4. Список C1, C2, …, Ct, где Ci – список субъектов, которые все имеют право записи в некоторый один объект oj
    vector<vector<int>> writeConflictGroups;
    for (int j = 0; j < m; ++j) {
        vector<int> writers;
        for (int i = 0; i < n; ++i) {
            if (accessMatrix[i][j].find('w') != string::npos) {
                writers.push_back(i + 1); //Сохраняем номер
            }
        }
        if (!writers.empty()) {
            writeConflictGroups.push_back(writers);
        }
    }

    //5. Список субъектов, каждый из которых имеет полный доступ только к одному объекту
    vector<int> singleAccessSubjects;
    for (int i = 0; i < n; ++i) {
        int accessCount = 0;
        for (int j = 0; j < m; ++j) {
            if (accessMatrix[i][j] == "rw") {
                accessCount++;
            }
        }
        if (accessCount == 1) {
            singleAccessSubjects.push_back(i + 1); //Сохраняем номер
        }
    }

    //Result outputing
    cout << "Objects that no one has access to: ";
    if (noAccessObjects.size() > 0) {
        for (int obj : noAccessObjects) {
            cout << obj << " ";
        }
    }
    else {
        cout << "None";
    }
    cout << endl;
    cout << "Subjects that do not access any objects: ";
    if (noAccessSubjects.size() > 0) {        
        for (int subj : noAccessSubjects) {
            cout << subj << " ";
        }
    }
    else {
        cout << "None";
    }
    cout << endl;

    
    cout << "Subjects that have full access to all objects: ";
    if (fullAccessSubjects.size() > 0) {
        for (int subj : fullAccessSubjects) {
            cout << subj << " ";
        }
    }
    else {
        cout << "None";
    }
    cout << endl;

    cout << "Subjects that all have the right to write to some one object: " << endl;
    for (const auto& group : writeConflictGroups) {
        cout << "Group of subj: ";
        for (int subj : group) {
            cout << subj << " ";
        }
        cout << endl;
    }

    cout << "Subjects that have full access to only one object: ";
    for (int subj : singleAccessSubjects) {
        cout << subj << " ";
    }
    cout << endl;

    return 0;
}
