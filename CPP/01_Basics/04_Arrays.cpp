// ─────────────────────────────────────────
//  ARRAYS  (raw arrays + std::array + std::vector)
// ─────────────────────────────────────────

#include <iostream>
#include <array>      // std::array (fixed size, safer)
#include <vector>     // std::vector (dynamic size)
#include <algorithm>  // sort, reverse, find, etc.
#include <numeric>    // accumulate, iota
using namespace std;

int main() {

    // ════════════════════════════════════
    //  RAW ARRAYS  (C-style — avoid when possible)
    // ════════════════════════════════════

    int nums[5] = {3, 1, 4, 1, 5};
    int zeros[5] = {};              // all zeros
    int partial[5] = {1, 2};       // rest are 0

    cout << nums[0] << endl;       // 3
    cout << nums[4] << endl;       // 5
    // No bounds checking! nums[10] = undefined behavior

    int size = sizeof(nums) / sizeof(nums[0]);   // length of raw array
    cout << "size: " << size << endl;   // 5

    for (int i = 0; i < 5; i++)
        cout << nums[i] << " ";
    cout << endl;

    for (int n : nums)   // range-based for (C++11)
        cout << n << " ";
    cout << endl;

    // 2D raw array
    int matrix[3][3] = {{1,2,3},{4,5,6},{7,8,9}};
    cout << matrix[1][2] << endl;   // 6

    // ════════════════════════════════════
    //  std::array<T, N>  (C++11, fixed size, safer)
    // ════════════════════════════════════

    array<int, 5> arr = {3, 1, 4, 1, 5};

    cout << arr[0]      << endl;   // 3
    cout << arr.at(4)   << endl;   // 5 (bounds-checked)
    cout << arr.size()  << endl;   // 5
    cout << arr.front() << endl;   // 3
    cout << arr.back()  << endl;   // 5

    arr.fill(0);                   // all zeros
    cout << arr[0] << endl;        // 0

    array<int, 5> arr2 = {3, 1, 4, 1, 5};
    sort(arr2.begin(), arr2.end());
    for (int n : arr2) cout << n << " ";   // 1 1 3 4 5
    cout << endl;

    // ════════════════════════════════════
    //  std::vector<T>  (dynamic size — use this most often)
    // ════════════════════════════════════

    vector<int> v = {3, 1, 4, 1, 5, 9, 2, 6};
    vector<string> fruits = {"apple", "banana", "cherry"};
    vector<int> empty_v;
    vector<int> fives(5, 7);   // 5 elements, all 7: {7,7,7,7,7}

    // Access
    cout << v[0]      << endl;   // 3
    cout << v.at(0)   << endl;   // 3 (bounds-checked)
    cout << v.front() << endl;   // 3
    cout << v.back()  << endl;   // 6
    cout << v.size()  << endl;   // 8

    // Add / Remove
    v.push_back(100);            // add to end
    v.pop_back();                // remove last
    v.insert(v.begin() + 2, 99);// insert at index 2
    v.erase(v.begin() + 2);     // remove at index 2
    v.clear();                   // remove all elements
    cout << v.empty() << endl;   // 1 (true)

    // Iterate
    vector<int> data = {5, 2, 8, 1, 9, 3};
    for (int n : data)
        cout << n << " ";
    cout << endl;

    for (size_t i = 0; i < data.size(); i++)
        cout << "[" << i << "]=" << data[i] << " ";
    cout << endl;

    // Iterator
    for (auto it = data.begin(); it != data.end(); ++it)
        cout << *it << " ";
    cout << endl;

    // Sort
    sort(data.begin(), data.end());                    // ascending
    for (int n : data) cout << n << " ";   // 1 2 3 5 8 9
    cout << endl;

    sort(data.begin(), data.end(), greater<int>());    // descending
    for (int n : data) cout << n << " ";   // 9 8 5 3 2 1
    cout << endl;

    // Custom sort — by absolute value
    vector<int> mixed = {-3, 1, -7, 4, -2};
    sort(mixed.begin(), mixed.end(), [](int a, int b) {
        return abs(a) < abs(b);
    });
    for (int n : mixed) cout << n << " ";   // 1 -2 -3 4 -7
    cout << endl;

    // Reverse
    reverse(data.begin(), data.end());

    // Search
    vector<int> haystack = {1, 2, 3, 4, 5};
    auto it = find(haystack.begin(), haystack.end(), 3);
    if (it != haystack.end())
        cout << "Found at index: " << (it - haystack.begin()) << endl;

    // Binary search (array must be sorted)
    sort(haystack.begin(), haystack.end());
    bool found = binary_search(haystack.begin(), haystack.end(), 3);
    cout << "Binary search: " << found << endl;

    // Count
    vector<int> dup = {1, 2, 2, 3, 3, 3};
    cout << count(dup.begin(), dup.end(), 3) << endl;  // 3

    // Min / Max
    cout << *min_element(data.begin(), data.end()) << endl;
    cout << *max_element(data.begin(), data.end()) << endl;

    // Sum (from <numeric>)
    int total = accumulate(data.begin(), data.end(), 0);
    cout << "Sum: " << total << endl;

    // Fill sequence (iota from <numeric>)
    vector<int> seq(5);
    iota(seq.begin(), seq.end(), 1);   // {1, 2, 3, 4, 5}
    for (int n : seq) cout << n << " ";
    cout << endl;

    // 2D vector
    vector<vector<int>> grid = {{1,2,3},{4,5,6},{7,8,9}};
    cout << grid[1][2] << endl;   // 6

    for (auto& row : grid) {
        for (int val : row)
            cout << val << " ";
        cout << endl;
    }

    // Resize
    vector<int> r = {1, 2, 3};
    r.resize(6, 0);       // {1, 2, 3, 0, 0, 0}
    r.resize(2);          // {1, 2} — truncates
    cout << r.size() << endl;   // 2

    // Reserve capacity (avoid reallocations)
    vector<int> big;
    big.reserve(1000);    // allocate space without adding elements
    cout << big.size()     << endl;   // 0
    cout << big.capacity() << endl;   // 1000

    return 0;
}
