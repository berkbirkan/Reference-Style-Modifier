#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

/*

VİDEO LİNK : https://drive.google.com/file/d/1UVxcxzoYCSdfd2gX0f7_26Tes_VW5J7t/view?usp=sharing

This program reads the input file "input.txt" and stores the content as a string. Then, it calls the `convert_to_apa()` function
to convert the MLA format to APA format. The converted content is written to another file called "output.txt".

Note that the above program implementation is not perfect solution and might have bugs, so it may have to be debugged and/or
modified if it does not fully meet the requirement, but it should give you a good starting point for your project. 
Also you can use different techniques for reading the file, parsing and formatting according to the requirement.

How to run this program:
g++ -std=c++11 reference_style_modifier.cpp -o reference_style_modifier
./reference_style_modifier

*/

// Function to convert MLA format to APA format
string convert_to_apa(string mla) {
    string apa;

    // Split the string into lines
    vector<string> lines;
    string line;
    for (char c : mla) {
        if (c == '\n') {
            lines.push_back(line);
            line.clear();
        } else {
            line += c;
        }
    }
    lines.push_back(line);

    // Convert each line
    for (string& line : lines) {
        // Remove the period after the publication title
        if (line.back() == '.') {
            line.pop_back();
        }

        // Change the format of the authors
        size_t first_and = line.find(" and ");
        if (first_and != string::npos) {
            line.replace(first_and, 4, ", ");
            size_t next_and = line.find(" and ", first_and + 2);
            while (next_and != string::npos) {
                line.replace(next_and, 4, ", ");
                next_and = line.find(" and ", next_and + 2);
            }
        }

        // Add the publication date in parentheses
        size_t first_comma = line.find(",");
        if (first_comma != string::npos) {
            size_t second_comma = line.find(",", first_comma + 1);
            if (second_comma != string::npos) {
                line.insert(second_comma + 1, " (");
                line.push_back(')');
            }
        }

        // Add the period after the last element
        if(!line.empty())
            line.push_back('.');
    }

    // Build the resulting string
    for (string& line : lines) {
        apa += line;
        apa.push_back('\n');
    }
    return apa;
}

int main() {
    // Open the input file
    ifstream input_file("input.txt");
    if (!input_file.is_open()) {
        cerr << "Error: Failed to open input file." << endl;
        return 1;
    }

    // Read the input file
    string input;
    string line;
    while (getline(input_file, line)) {
        input += line;
        input.push_back('\n');
    }
    input_file.close();

    // Convert the input to APA format
    string output = convert_to_apa(input);

    // Open the output file
    ofstream output_file("output.txt");
    if (!output_file.is_open()) {
        cerr << "Error: Failed to open output file." << endl;
        return 1;
    }

    // Write the output to the file
    output_file << output;
    output_file.close();
    cout << "Successfully converted MLA format to APA format and written to output file." << endl;

    return 0;
    }

