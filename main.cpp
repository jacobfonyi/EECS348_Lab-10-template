#include <iostream>
#include "calculator.hpp"
#include <fstream>
#include <string>
#include <algorithm>

using namespace std;

// Function to check if a string represents a valid double number
bool isValidDouble(const string& num) {
    if (num.empty()) return false;
    
    size_t i = 0;
    bool hasDigit = false;
    bool hasDecimal = false;
    
    // Check for optional sign
    if (num[i] == '+' || num[i] == '-') {
        i++;
    }
    
    // Check digits before decimal point
    while (i < num.size() && isdigit(num[i])) {
        hasDigit = true;
        i++;
    }
    
    // Check for decimal point and digits after
    if (i < num.size() && num[i] == '.') {
        hasDecimal = true;
        i++;
        // Must have at least one digit after decimal
        if (i >= num.size() || !isdigit(num[i])) {
            return false;
        }
        while (i < num.size() && isdigit(num[i])) {
            i++;
        }
    }
    
    // Must have at least one digit and no extra characters
    return hasDigit && (i == num.size());
}

// Function to add two string-formatted double numbers
string addStringDoubles(const string& num1, const string& num2) {
    return "[result of " + num1 + " + " + num2 + "]";
}

// Function to load and process numbers from file
void processCandidateNumbers(const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Error: Could not open file " << filename << endl;
        return;
    }
    
    string line;
    const string fixedNumber = "-123.456";
    
    while (getline(file, line)) {
        // Remove whitespace
        line.erase(remove_if(line.begin(), line.end(), ::isspace), line.end());
        
        if (line.empty()) continue;
        
        if (isValidDouble(line)) {
            cout << "Valid number: " << line << endl;
            string sum = addStringDoubles(line, fixedNumber);
            cout << "Sum with " << fixedNumber << ": " << sum << endl;
        } else {
            cout << "Invalid number: " << line << endl;
        }
    }
    
    file.close();
}

int main() {
    // Asks for user-inputted file
    string filename;
    cout << "Enter the filename containing candidate numbers: ";
    cin >> filename;
    
    processCandidateNumbers(filename);
    
    return 0;
}
