
#include <iostream>
#include <queue>
#include <string>
using namespace std;

void generateBinaryNumbers(int n) {
    queue<string> q;
    q.push("1");

    for (int i = 0; i < n; i++) {
        string current = q.front();//samner element ta ber kore
        q.pop();

        cout << current << " ";

        q.push(current + "0");
        q.push(current + "1");
    }

    cout << endl;
}

int main() {
    int n;
    cout << "Enter number of binary numbers to generate: ";
    cin >> n;

    generateBinaryNumbers(n);

    return 0;
}
