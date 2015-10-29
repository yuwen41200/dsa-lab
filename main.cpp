/**
 * main.cpp
 * Developer: Yu-wen Pwu, NCTU CS, Taiwan
 * Compilation command: g++ -Wall -Wextra -Wpedantic --std=c++11 main.cpp -o main
 */
#include <iostream>
#include <fstream>
#include <queue>
#include <ctime>
#include <string>
#include <cctype>
using namespace std;

int* kmpInit(string searching);
int kmpSearch(string searched, string searching, int* table);
void kmpDestroy(int* table);

/**
 * Problem: Dr. Mao-Mao and X Company's Vault
 * @return The status code, 0 indicates success.
 */
int main() {

    // Get the file paths and start the timer.
    string finPath, foutPath, str, substr, temp;
    cin >> finPath >> foutPath;
    clock_t time = clock();

    // Open the files, read the input data, then close the input file.
    fstream fin, fout;
    fin.open(finPath, ios::in);
    fout.open(foutPath, ios::out | ios::trunc);
    if (!fin.is_open() || !fout.is_open())
        return 1;
    while (getline(fin, temp))
        str += temp + '\n';
    fin.close();

    // Build an array whose indices corresponds to the word count of the string.
    int* wordCount = new int[str.length()];
    int pos, word = 1;
    bool prevCharIsSpaceOrPunct = false;
    for (pos = 0; pos < (int) str.length(); ++pos) {
        if (isspace(str[pos]) || ispunct(str[pos])) {
            wordCount[pos] = 0;
            if (!prevCharIsSpaceOrPunct)
                ++word;
            prevCharIsSpaceOrPunct = true;
        }
        else {
            wordCount[pos] = word;
            prevCharIsSpaceOrPunct = false;
        }
    }

    // Get the keyword Dr. Mao-Mao wants to search.
    for (pos = 0; pos < (int) str.length(); ++pos) {
        if (!wordCount[pos])
            break;
    }
    substr = str.substr(0, (size_t) pos);

    // Search the keyword in the string and store the results in a queue.
    int* kmpTable = kmpInit(substr);
    queue<int> foundQue;
    int found = kmpSearch(str, substr, kmpTable);
    while (found != -1) {
        foundQue.push(found);
        str = str.substr((size_t) found + 1, string::npos);
        found = kmpSearch(str, substr, kmpTable);
    }
    kmpDestroy(kmpTable);

    // Convert the results to the word counts.
    found = -1;
    string ans;
    while (!foundQue.empty()) {
        found = found + foundQue.front() + 1;
        ans += to_string(wordCount[found]);
        foundQue.pop();
    }
    delete [] wordCount;

    // Stop the timer, write the answer to the output file, then close the output file.
    time = clock() - time;
    fout << 1000 * (double) time / CLOCKS_PER_SEC << "ms" << endl;
    fout << ans << endl;
    fout.close();
    return 0;

}

/**
 * Initialize the KMP table.
 * @param searching The searching string.
 * @return The pointer to the KMP table.
 */
int* kmpInit(string searching) {

    int working = 2, candidate = 0;

    int* table = new int[searching.length()];
    table[0] = -1;
    table[1] = 0;

    while (working < (int) searching.length()) {
        if (searching[working-1] == searching[candidate]) {
            ++candidate;
            table[working] = candidate;
            ++working;
        }
        else if (candidate > 0)
            candidate = table[candidate];
        else {
            table[working] = 0;
            ++working;
        }
    }

    return table;

}

/**
 * Search for a substring using the KMP algorithm.
 * @param searched The searched string.
 * @param searching The searching string.
 * @param table The pointer to the KMP table.
 * @return The position of the first match, -1 if failure.
 */
int kmpSearch(string searched, string searching, int* table) {

    int match = 0, position = 0;

    while (match + position < (int) searched.length()) {
        if (searching[position] == searched[match+position]) {
            if (position == (int) searching.length() - 1)
                return match;
            ++position;
        }
        else {
            if (table[position] > -1) {
                match = match + position - table[position];
                position = table[position];
            }
            else {
                position = 0;
                ++match;
            }
        }
    }

    return -1;

}

/**
 * Free the allocated space for the KMP table.
 * @param table The pointer to the KMP table.
 */
void kmpDestroy(int* table) {

    delete [] table;

}
