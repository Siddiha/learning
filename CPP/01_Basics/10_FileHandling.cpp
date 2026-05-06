// ─────────────────────────────────────────
//  FILE HANDLING
// ─────────────────────────────────────────

#include <iostream>
#include <fstream>    // ifstream, ofstream, fstream
#include <sstream>    // stringstream
#include <string>
#include <vector>
#include <filesystem> // C++17 — path, directory operations
namespace fs = filesystem;
using namespace std;

int main() {

    // ════════════════════════════════════
    //  WRITE TO FILE
    // ════════════════════════════════════

    // ofstream — output file stream (write)
    ofstream outFile("example.txt");
    if (!outFile) {
        cerr << "Failed to open file!" << endl;
        return 1;
    }
    outFile << "Hello, World!" << endl;
    outFile << "Line 2" << endl;
    outFile << "Line 3" << endl;
    outFile.close();   // always close when done (or use RAII scope)

    // RAII style — auto-closes when goes out of scope
    {
        ofstream f("raii.txt");
        f << "Written via RAII" << endl;
    }   // f.close() called automatically here

    // Append mode
    ofstream appendFile("example.txt", ios::app);
    appendFile << "Appended line" << endl;
    appendFile.close();

    // ════════════════════════════════════
    //  READ FROM FILE
    // ════════════════════════════════════

    // ifstream — input file stream (read)
    ifstream inFile("example.txt");
    if (!inFile) {
        cerr << "File not found!" << endl;
        return 1;
    }

    // Read line by line
    string line;
    while (getline(inFile, line))
        cout << line << endl;
    inFile.close();

    // Read word by word
    ifstream f2("example.txt");
    string word;
    while (f2 >> word)
        cout << word << " ";
    cout << endl;
    f2.close();

    // Read entire file into a string
    ifstream f3("example.txt");
    ostringstream ss;
    ss << f3.rdbuf();         // read all into stringstream
    string content = ss.str();
    cout << content << endl;
    f3.close();

    // Read into vector of lines
    ifstream f4("example.txt");
    vector<string> lines;
    while (getline(f4, line))
        lines.push_back(line);
    f4.close();
    cout << "Total lines: " << lines.size() << endl;

    // ════════════════════════════════════
    //  READ & WRITE (fstream)
    // ════════════════════════════════════
    fstream rwFile("rw.txt", ios::in | ios::out | ios::trunc);
    rwFile << "Hello from fstream" << endl;
    rwFile.seekg(0);   // go back to beginning
    getline(rwFile, line);
    cout << line << endl;
    rwFile.close();

    // ════════════════════════════════════
    //  FILE MODES
    // ════════════════════════════════════
    // ios::in      — read
    // ios::out     — write (creates/truncates)
    // ios::app     — append
    // ios::trunc   — truncate existing file
    // ios::binary  — binary mode
    // ios::ate     — open and seek to end

    // ════════════════════════════════════
    //  BINARY FILES
    // ════════════════════════════════════
    struct Point { int x, y; };

    // Write binary
    Point p = {10, 20};
    ofstream binOut("data.bin", ios::binary);
    binOut.write(reinterpret_cast<char*>(&p), sizeof(p));
    binOut.close();

    // Read binary
    Point p2;
    ifstream binIn("data.bin", ios::binary);
    binIn.read(reinterpret_cast<char*>(&p2), sizeof(p2));
    cout << p2.x << ", " << p2.y << endl;   // 10, 20
    binIn.close();

    // ════════════════════════════════════
    //  FILESYSTEM (C++17)
    // ════════════════════════════════════

    // Check existence
    cout << fs::exists("example.txt")   << endl;   // 1
    cout << fs::exists("missing.txt")   << endl;   // 0
    cout << fs::is_regular_file("example.txt") << endl;
    cout << fs::is_directory(".")       << endl;   // 1

    // File size
    cout << fs::file_size("example.txt") << " bytes" << endl;

    // Path manipulation
    fs::path p3 = "folder/sub/file.txt";
    cout << p3.filename()    << endl;   // "file.txt"
    cout << p3.stem()        << endl;   // "file"
    cout << p3.extension()   << endl;   // ".txt"
    cout << p3.parent_path() << endl;   // "folder/sub"
    cout << fs::absolute(p3) << endl;   // full absolute path

    // Combine paths
    fs::path dir = "mydir";
    fs::path file = dir / "output.txt";
    cout << file << endl;   // mydir/output.txt

    // Create directories
    fs::create_directories("test/nested/dir");

    // List directory contents
    for (auto& entry : fs::directory_iterator(".")) {
        if (entry.is_regular_file())
            cout << entry.path().filename() << " ("
                 << entry.file_size() << " bytes)" << endl;
    }

    // Recursive list
    for (auto& entry : fs::recursive_directory_iterator("test"))
        cout << entry.path() << endl;

    // Copy / rename / delete
    fs::copy("example.txt", "copy.txt", fs::copy_options::overwrite_existing);
    fs::rename("copy.txt", "moved.txt");
    fs::remove("moved.txt");
    fs::remove_all("test");   // delete directory and all contents

    // ════════════════════════════════════
    //  STRINGSTREAM — in-memory "file"
    // ════════════════════════════════════
    stringstream stream;
    stream << "Name: Alice" << endl;
    stream << "Age: 25" << endl;

    string key, value;
    while (stream >> key >> value)
        cout << key << " " << value << endl;

    // Parse numbers from string
    istringstream iss("1 2 3 4 5");
    int num;
    while (iss >> num)
        cout << num * 2 << " ";
    cout << endl;

    // ── Cleanup ───────────────────────────────
    for (auto f : {"example.txt", "raii.txt", "rw.txt", "data.bin"})
        fs::remove(f);

    return 0;
}
