#include "file_functions.h"

void cut_file(int size, const char *input_filename, const char *output_filename)
{
    std::ifstream input{input_filename};
    std::ofstream output{output_filename};

    int i = 0;
    char c;
    while (i < size)
    {
        input.get(c);
        if (c == EOF)
        {
            break;
        }
        output << c;
        i += sizeof(c);
    }

    input.close();
    output.close();
}
