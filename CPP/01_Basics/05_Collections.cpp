// ─────────────────────────────────────────
//  COLLECTIONS  (map, set, queue, stack, unordered variants)
// ─────────────────────────────────────────

#include <iostream>
#include <map>
#include <unordered_map>
#include <set>
#include <unordered_set>
#include <queue>
#include <stack>
#include <list>
#include <deque>
using namespace std;

int main() {

    // ════════════════════════════════════
    //  map<K,V>  — key-value, sorted by key, unique keys
    // ════════════════════════════════════
    map<string, int> scores;
    scores["Alice"] = 90;
    scores["Bob"]   = 85;
    scores["Carol"] = 92;
    scores.insert({"Dave", 78});
    scores.emplace("Eve", 88);    // more efficient insert

    // Access
    cout << scores["Alice"] << endl;     // 90
    // scores["Unknown"] creates a new key with value 0 — be careful!

    // Safe access
    auto it = scores.find("Bob");
    if (it != scores.end())
        cout << it->first << ": " << it->second << endl;

    cout << scores.count("Alice") << endl;    // 1 (exists)
    cout << scores.count("Zara")  << endl;    // 0 (not found)

    // Update
    scores["Alice"] = 95;

    // Remove
    scores.erase("Dave");

    // Iterate — sorted by key alphabetically
    for (auto& [key, val] : scores)   // structured bindings (C++17)
        cout << key << ": " << val << endl;
    cout << endl;

    cout << "Size: " << scores.size() << endl;

    // ════════════════════════════════════
    //  unordered_map<K,V>  — hash map, O(1) average, no order
    // ════════════════════════════════════
    unordered_map<string, int> freq;
    string text = "hello world hello cpp hello";
    for (char c : text)
        if (c != ' ') freq[string(1, c)]++;

    // Count word frequency
    unordered_map<string, int> wordCount;
    wordCount["apple"]++;
    wordCount["banana"]++;
    wordCount["apple"]++;
    wordCount["apple"]++;

    for (auto& [word, count] : wordCount)
        cout << word << ": " << count << endl;

    // ════════════════════════════════════
    //  set<T>  — unique sorted values
    // ════════════════════════════════════
    set<int> s = {5, 3, 1, 4, 2, 3, 5};  // duplicates removed on insert
    cout << "Set: ";
    for (int n : s) cout << n << " ";    // 1 2 3 4 5 (sorted)
    cout << endl;

    s.insert(6);
    s.insert(3);           // duplicate — ignored
    s.erase(1);
    cout << s.count(4) << endl;   // 1 (exists)
    cout << s.count(99)<< endl;   // 0

    auto sit = s.find(4);
    if (sit != s.end())
        cout << "Found: " << *sit << endl;

    // lower_bound / upper_bound
    auto lb = s.lower_bound(3);   // first element >= 3
    auto ub = s.upper_bound(3);   // first element > 3
    cout << *lb << " " << *ub << endl;

    // ════════════════════════════════════
    //  unordered_set<T>  — hash set, O(1) average
    // ════════════════════════════════════
    unordered_set<string> seen;
    seen.insert("apple");
    seen.insert("banana");
    seen.insert("apple");   // duplicate ignored

    cout << seen.count("apple") << endl;   // 1
    cout << seen.size()         << endl;   // 2

    // Remove duplicates from a vector using unordered_set
    vector<int> vec = {1, 2, 2, 3, 3, 3, 4};
    unordered_set<int> unique(vec.begin(), vec.end());
    vector<int> deduped(unique.begin(), unique.end());
    // Note: order not guaranteed with unordered_set

    // ════════════════════════════════════
    //  queue<T>  — FIFO
    // ════════════════════════════════════
    queue<string> q;
    q.push("first");
    q.push("second");
    q.push("third");

    cout << q.front() << endl;   // first (doesn't remove)
    cout << q.back()  << endl;   // third
    q.pop();                     // removes front
    cout << q.front() << endl;   // second
    cout << q.size()  << endl;   // 2

    // ════════════════════════════════════
    //  stack<T>  — LIFO
    // ════════════════════════════════════
    stack<int> stk;
    stk.push(1);
    stk.push(2);
    stk.push(3);

    cout << stk.top() << endl;   // 3 (doesn't remove)
    stk.pop();
    cout << stk.top() << endl;   // 2
    cout << stk.size()<< endl;   // 2

    // ════════════════════════════════════
    //  priority_queue<T>  — max-heap by default
    // ════════════════════════════════════
    priority_queue<int> maxHeap;
    for (int n : {5, 2, 8, 1, 9})
        maxHeap.push(n);

    while (!maxHeap.empty()) {
        cout << maxHeap.top() << " ";   // 9 8 5 2 1
        maxHeap.pop();
    }
    cout << endl;

    // Min-heap
    priority_queue<int, vector<int>, greater<int>> minHeap;
    for (int n : {5, 2, 8, 1, 9})
        minHeap.push(n);

    while (!minHeap.empty()) {
        cout << minHeap.top() << " ";   // 1 2 5 8 9
        minHeap.pop();
    }
    cout << endl;

    // ════════════════════════════════════
    //  deque<T>  — double-ended queue
    // ════════════════════════════════════
    deque<int> dq = {2, 3, 4};
    dq.push_front(1);   // {1, 2, 3, 4}
    dq.push_back(5);    // {1, 2, 3, 4, 5}
    dq.pop_front();     // {2, 3, 4, 5}
    dq.pop_back();      // {2, 3, 4}

    for (int n : dq) cout << n << " ";
    cout << endl;

    // ════════════════════════════════════
    //  list<T>  — doubly linked list
    // ════════════════════════════════════
    list<int> lst = {1, 2, 3, 4, 5};
    lst.push_front(0);    // {0, 1, 2, 3, 4, 5}
    lst.push_back(6);     // {0, 1, 2, 3, 4, 5, 6}
    lst.pop_front();      // {1, 2, 3, 4, 5, 6}

    auto lit = find(lst.begin(), lst.end(), 3);
    lst.insert(lit, 99);   // insert 99 before 3
    lst.erase(lit);        // erase 3

    lst.sort();            // sort in place (list has own sort)
    lst.reverse();
    lst.unique();          // remove consecutive duplicates

    for (int n : lst) cout << n << " ";
    cout << endl;

    return 0;
}
