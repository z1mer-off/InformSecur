#include <iostream>
#include <string>
using namespace std;
int main()
{
    string s;
    cin >> s;
    int t1=0, t2=1;
    while (t2 != s.length()-1) {
        if (s[t1] == s[t2]) {
            s.erase(t1, 2);
            if (t1 > 0) {
                t1--; t2--;
            }
        }
        else {
            t1++;
            t2++;
        }
        cout << s << endl;
    }
    cout << s;
    return 0;
}
