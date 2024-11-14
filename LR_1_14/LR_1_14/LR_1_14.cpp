#include <iostream>
#include <fstream>
#include <vector>
#include <bitset>
using namespace std;
vector<string> generateGrayCode(int n) {
    int numCodes = 1 << n; // 2^n
    vector<string> grayCodes;

    for (int i = 0; i < numCodes; i++) {
        int gray = i ^ (i >> 1); //ф-ла для i-кода грея    
        grayCodes.push_back(bitset<16>(gray).to_string().substr(16 - n)); //двоичное представление
    }
    return grayCodes;
}

void writeGrayCodesToFile(int n) {
    ofstream outFile("output.txt");
    if (!outFile) {
        cerr << "Error with file opening!" << endl;
        return;
    }
    vector<std::string> grayCodes = generateGrayCode(n);
    for (const auto& code : grayCodes) {
        outFile << code << " "; //Через пробел записываем коды
    }
    outFile.close();
}

int main() {
    int n;
    cout << "Write number of bit (1 < n < 17): ";
    cin >> n;

    if (n >= 2 && n <= 16) {
        writeGrayCodesToFile(n);
        cout << "Gray's code for " << n << " bit is in  output.txt file." << endl;
    }
    else {
        cout << "Error: n should be more than 1 and less than 17." << endl;
    }

    return 0;
}
