#include <bits/stdc++.h>

using namespace std;

int main() {
    int n; cin >> n;
    if (n < 0) {
        cout << "Error!\n";
        return 1;
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << (j + i) % n + 1 << " ";
        }
        cout << endl;
    }
}