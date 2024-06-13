#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>

#include "lz77_compression.h"

using namespace std; /* >.< */

void compress_file(const char *input_filename, const char *output_filename)
{
    ifstream input{input_filename};
    stringstream buffer;
    buffer << input.rdbuf();
    string str = buffer.str();

    auto code = compress_string(str);

    print_code(code);

    /* debugging */
    int size = code.size() * (sizeof(int) + sizeof(char));
    float in_kb = ((float)(size)) / 1000.0;
    cout << in_kb << " kB" << endl;

    ofstream output{output_filename, ios::binary};
    for (int i = 0; i < code.size(); i++)
    {
        output.write((char *)&(code[i].first), sizeof(int));
        output.write((char *)&(code[i].second), sizeof(char));
    }

    input.close();
    output.close();
}

void decompress_file(const char *input_filename, const char *output_filename)
{
    ifstream input{input_filename, ios::binary};
    if (!input.is_open())
    {
        /* debugging */ cout << "Oh oh!" << endl;
    }
    vector<pair<int, char>> vec;
    pair<int, char> value;
    while (true)
    {
        if (input.peek() != EOF)
        {
            input.read((char *)&value.first, sizeof(int));
            if (input.peek() != EOF)
            {
                input.read((char *)&value.second, sizeof(char));
                vec.push_back(value);
                continue;
            }
        }
        break;
    }

    auto decode = decompress_string(vec);

    ofstream output{output_filename};
    output << decode;

    input.close();
    output.close();
}
