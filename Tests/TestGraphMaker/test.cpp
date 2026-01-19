#include <iostream>
#include <fstream>
#include <unordered_map>
#include <string>

#include "GraphMaker.h"

using namespace std;

typedef unordered_map<string, unordered_map<string, int>> LogData;

void runTest(const string& testName, const LogData& data) {
    string filename = testName + ".dot";

    cout << "--- Running " << testName << " ---" << endl;

    // 1. Setup
    GraphMaker grapher(filename);

    // 2. Generate
    grapher.generateGraphFile(data);

    cout << "Check file: " << filename << "\n" << endl;
}

int main() {
    // case 1
    // ---------------------------------------------------------
    // user went from "google.com" to "index.html" 1 time.
    LogData data1;
    data1["index.html"]["google.com"] = 1;

    runTest("test1", data1);

    // CASE 2: High Traffic
    // ---------------------------------------------------------
    // "twitter.com" directed users 50 times to "news.html".
    LogData data2;
    data2["news.html"]["twitter.com"] = 50;

    runTest("test2", data2);

    // CASE 3: page that gets accessed from multiple sites
    // ---------------------------------------------------------
    // - "blog.html" links to "home.html" (5 times)
    // - "shop.html" links to "home.html" (10 times)
    LogData data3;
    data3["home.html"]["blog.html"] = 5;
    data3["home.html"]["shop.html"] = 10;

    runTest("test3", data3);

    // CASE 4: cycle
    // ---------------------------------------------------------
    // - A links to B and B to A
    LogData data4;
    data4["pageB.html"]["pageA.html"] = 1; // A -> B
    data4["pageA.html"]["pageB.html"] = 1; // B -> A

    runTest("test4_cycle", data4);

    // CASE 5: data has no data, ironic!
    // ---------------------------------------------------------
    LogData data5; // Just declaring it makes it empty
    runTest("test5_empty", data5);

    return 0;
}
