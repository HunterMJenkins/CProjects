//Jack Utzerath and Hunter Jenkins
//CST-315
//Command Line Interpreter
//02/25/2024

#include <iostream>
#include <string>
#include <vector>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <sstream>
#include <memory>
#include <algorithm>
#include <fstream>
#include <regex>

using std::cout;
using std::cin;
using std::cerr;
using std::endl;
using std::string;
using std::vector;
using std::istringstream;
using std::ifstream;
using std::unique_ptr;
using std::make_unique;

// Function declarations
void executeInput(const string& cmd);
void batchMode(const char* fileName);
vector<string> split(const string& str, char delimiter);
bool grep(const string& pattern, const string& filename);
size_t wordCount(const string& filename);

// main function 
int main(int argc, char* argv[]) {
    if (argc > 1) {
        batchMode(argv[1]);
    } else {
        string input;
        while (true) {
            cout << "hunter+jackshell> "; //printing the shell name
            getline(cin, input); // getting in the iput
            if (input == "quit") {
                cout << "Exiting shell..." << endl;
                break;
            }
            // used for splitting up the commands
            auto commands = split(input, ';');
            for (const auto& cmd : commands) {
                executeInput(cmd);
            }
        }
    }
    return 0;
}

// Improved split function 
vector<string> split(const string& str, char delimiter) {
    vector<string> tokens;
    string token;
    istringstream tokenStream(str);
    while (getline(tokenStream, token, delimiter)) {
        tokens.push_back(token); 
    }
    return tokens;
}
// Execute the Input
void executeInput(const string& cmd) {
    auto args = split(cmd, ' ');
    // using unique_ptr for dynamic memory management
    unique_ptr<char*[]> c_args = make_unique<char*[]>(args.size() + 1);
    for (size_t i = 0; i < args.size(); ++i) {
        c_args[i] = &args[i][0];
    }
    c_args[args.size()] = nullptr;
    // for cd
    if (args[0] == "cd") { 
        if (args.size() < 2 || chdir(args[1].c_str()) != 0) {
            perror("chdir failed");
        }
        return;
    }
    // for grep function
    else if (args[0] == "grep") {
        if (args.size() < 3) {
            cout << "Usage: grep <pattern> <filename>" << endl;
            return;
        }
        string pattern = args[1];
        string filename = args[2];
        if (!grep(pattern, filename)) {
            cerr << "Error: grep failed" << endl;
        }
        return;
    }
    //caluclates the word count
    else if (args[0] == "wordcount") {
        if (args.size() < 2) {
            cout << "Usage: wordcount <filename>" << endl;
            return;
        }
        string filename = args[1];
        size_t count = wordCount(filename);
        cout << "Word count of " << filename << ": " << count << endl;
        return;
    }
    // fork is used for multiple commands that were no added such as 'ls'
    pid_t pid = fork();
    if (pid == 0) {
        execvp(c_args[0], c_args.get());
        perror("execvp failed");
        exit(EXIT_FAILURE);
    } else if (pid < 0) {
        perror("fork failed");
    } else {
        waitpid(pid, nullptr, 0);
    }
}
// batch made used for taking in the inputted batch file
void batchMode(const char* fileName) {
    ifstream batchFile(fileName);
    if (!batchFile.is_open()) {
        cerr << "Unable to open file: " << fileName << endl; // throw error
        return;
    }

    string line;
    while (getline(batchFile, line)) {
        cout << line << endl;
        executeInput(line); // get each line seperate then execute
    }
}

// grep function
bool grep(const string& pattern, const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Unable to open file: " << filename << endl; // throw error
        return false;
    }

    std::regex pattern_regex(pattern);
    string line;
    while (getline(file, line)) {
        if (std::regex_search(line, pattern_regex)) {
            cout << line << endl;
        }
    }

    file.close();
    return true;
}

size_t wordCount(const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Unable to open file: " << filename << endl;
        return 0;
    }

    size_t count = 0;
    string word;
    while (file >> word) {
        ++count; // increment the work counter
    }

    file.close();
    return count;
}