// ─────────────────────────────────────────
//  STRINGS
// ─────────────────────────────────────────

#include <iostream>
#include <string>
#include <algorithm>  // transform, reverse
#include <sstream>    // stringstream
using namespace std;

int main() {

    string s = "Hello, World!";

    // ── Basic ─────────────────────────────────
    cout << s.length()  << endl;   // 13  (also .size())
    cout << s[0]        << endl;   // H
    cout << s.at(0)     << endl;   // H  (bounds-checked, throws if out of range)
    cout << s.front()   << endl;   // H
    cout << s.back()    << endl;   // !
    cout << s.empty()   << endl;   // false

    // ── Substrings ────────────────────────────
    cout << s.substr(7)     << endl;   // World!
    cout << s.substr(7, 5)  << endl;   // World  (start, length)

    // ── Search ────────────────────────────────
    size_t pos = s.find("World");
    if (pos != string::npos)
        cout << "Found at: " << pos << endl;   // Found at: 7

    cout << s.rfind("l")       << endl;   // 10 (last occurrence)
    cout << s.find_first_of("aeiou") << endl;  // 1 (first vowel)
    cout << s.find_last_of("l")      << endl;  // 10

    // ── Modify ────────────────────────────────
    string t = s;
    t.replace(7, 5, "C++");        // replace 5 chars at index 7
    cout << t << endl;             // Hello, C++!

    t.insert(5, " there");         // insert at index 5
    cout << t << endl;

    t.erase(5, 6);                 // erase 6 chars at index 5
    cout << t << endl;

    string joined = "Hello" + string(", ") + "World!";
    cout << joined << endl;

    // ── Case conversion (no built-in, use <algorithm>) ─
    string upper = s;
    transform(upper.begin(), upper.end(), upper.begin(), ::toupper);
    cout << upper << endl;   // HELLO, WORLD!

    string lower = s;
    transform(lower.begin(), lower.end(), lower.begin(), ::tolower);
    cout << lower << endl;

    // ── Compare ───────────────────────────────
    string a = "apple", b = "banana";
    cout << (a == b)        << endl;  // false
    cout << (a != b)        << endl;  // true
    cout << (a < b)         << endl;  // true (lexicographic)
    cout << a.compare(b)    << endl;  // negative (a < b)

    // ── Trim (no built-in — manual) ───────────
    auto trimLeft = [](string& s) {
        s.erase(s.begin(), find_if(s.begin(), s.end(), [](unsigned char c) {
            return !isspace(c);
        }));
    };
    auto trimRight = [](string& s) {
        s.erase(find_if(s.rbegin(), s.rend(), [](unsigned char c) {
            return !isspace(c);
        }).base(), s.end());
    };

    string padded = "   hello   ";
    trimLeft(padded);
    trimRight(padded);
    cout << "[" << padded << "]" << endl;   // [hello]

    // ── Split (no built-in — use stringstream) ─
    string csv = "apple,banana,cherry";
    stringstream ss(csv);
    string token;
    while (getline(ss, token, ','))
        cout << token << endl;

    // ── Reverse ───────────────────────────────
    string rev = "hello";
    reverse(rev.begin(), rev.end());
    cout << rev << endl;   // olleh

    // ── Char operations ───────────────────────
    for (char c : s) {
        if (isalpha(c)) cout << c;  // letters only
    }
    cout << endl;

    // isalpha, isdigit, isspace, isupper, islower, toupper, tolower

    // ── String ↔ number conversion ────────────
    string numStr = "42";
    int    i   = stoi(numStr);       // "42" → 42
    double d   = stod("3.14");       // "3.14" → 3.14
    long   l   = stol("9000000");    // → long

    string fromNum = to_string(i);   // 42 → "42"
    string fromDbl = to_string(d);   // 3.14 → "3.140000" (6 decimal places)
    cout << fromNum << " " << fromDbl << endl;

    // Better number → string formatting via stringstream
    ostringstream oss;
    oss.precision(2);
    oss << fixed << 3.14159;
    cout << oss.str() << endl;   // "3.14"

    // ── Read with spaces (cin reads word-by-word) ─
    // cin >> name;            // stops at whitespace
    // getline(cin, fullName); // reads full line

    // ── C-style strings (char arrays) — avoid, use std::string ─
    const char* cstr = "Hello";
    string fromCStr(cstr);        // convert to std::string
    cout << strlen(cstr) << endl; // 5

    // ── String operations summary ──────────────
    // s.length() / s.size()  — character count
    // s[i] / s.at(i)         — character at index
    // s.substr(pos, len)      — substring
    // s.find(str)             — first index or string::npos
    // s.replace(pos, len, str)
    // s.insert(pos, str)
    // s.erase(pos, len)
    // s.compare(other)        — 0 if equal, negative/positive otherwise
    // s.empty()               — true if ""
    // s += "more"             — append
    // s.append("more")        — append (same)
    // to_string(num)          — number → string
    // stoi/stod/stol(str)     — string → number

    return 0;
}
