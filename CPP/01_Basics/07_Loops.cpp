// ─────────────────────────────────────────
//  LOOPS
// ─────────────────────────────────────────

#include <iostream>
#include <vector>
#include <map>
using namespace std;

int main() {

    // ── for loop ──────────────────────────────
    for (int i = 0; i < 5; i++)
        cout << i << " ";   // 0 1 2 3 4
    cout << endl;

    // Count down
    for (int i = 5; i > 0; i--)
        cout << i << " ";   // 5 4 3 2 1
    cout << endl;

    // Step by 2
    for (int i = 0; i < 10; i += 2)
        cout << i << " ";   // 0 2 4 6 8
    cout << endl;

    // Multiple variables
    for (int i = 0, j = 10; i < j; i++, j--)
        cout << "(" << i << "," << j << ") ";
    cout << endl;

    // ── range-based for (C++11) ───────────────
    vector<string> fruits = {"apple", "banana", "cherry"};

    for (const string& fruit : fruits)    // const ref — no copy, no modify
        cout << fruit << " ";
    cout << endl;

    for (string& fruit : fruits)          // ref — can modify
        fruit[0] = toupper(fruit[0]);

    for (string fruit : fruits)           // copy — safe but slower
        cout << fruit << " ";
    cout << endl;

    for (auto& f : fruits)               // auto deduces type
        cout << f << " ";
    cout << endl;

    // ── while loop ────────────────────────────
    int count = 0;
    while (count < 5) {
        cout << count << " ";
        count++;
    }
    cout << endl;

    // ── do-while — runs at least once ─────────
    int x = 10;
    do {
        cout << x << " ";
        x++;
    } while (x < 5);    // false immediately, but ran once
    cout << endl;

    // ── break — exit loop ─────────────────────
    for (int i = 0; i < 10; i++) {
        if (i == 5) break;
        cout << i << " ";   // 0 1 2 3 4
    }
    cout << endl;

    // ── continue — skip iteration ─────────────
    for (int i = 0; i < 10; i++) {
        if (i % 2 == 0) continue;
        cout << i << " ";   // 1 3 5 7 9
    }
    cout << endl;

    // ── Nested loops with goto (avoid — just for demo) ─
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (i == 1 && j == 1) goto exitLoop;
            cout << "(" << i << "," << j << ") ";
        }
    }
    exitLoop:
    cout << "\nExited nested loop" << endl;

    // Better: use a flag
    bool done = false;
    for (int i = 0; i < 3 && !done; i++) {
        for (int j = 0; j < 3 && !done; j++) {
            if (i == 1 && j == 1) { done = true; break; }
            cout << "(" << i << "," << j << ") ";
        }
    }
    cout << endl;

    // ── Iterate over map ──────────────────────
    map<string, int> score = {{"Alice", 90}, {"Bob", 85}};

    // C++11 style
    for (auto& pair : score)
        cout << pair.first << ": " << pair.second << endl;

    // C++17 structured bindings
    for (auto& [name, pts] : score)
        cout << name << " → " << pts << endl;

    // ── Iterate with index over vector ────────
    vector<string> items = {"a", "b", "c"};
    for (size_t i = 0; i < items.size(); i++)
        cout << i << ": " << items[i] << endl;

    // ── Iterator-based loop ───────────────────
    for (auto it = fruits.begin(); it != fruits.end(); ++it)
        cout << *it << " ";
    cout << endl;

    // Reverse iterator
    for (auto it = fruits.rbegin(); it != fruits.rend(); ++it)
        cout << *it << " ";
    cout << endl;

    // ── Infinite loop ─────────────────────────
    int n = 1;
    while (true) {
        cout << n << " ";
        n *= 2;
        if (n > 64) break;
    }
    cout << endl;

    // ── Loop over characters in string ────────
    string word = "hello";
    for (char c : word)
        cout << c << "-";
    cout << endl;

    return 0;
}
