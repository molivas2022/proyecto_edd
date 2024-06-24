#include "file_functions.h"

void cut_file(int size, const char *input_filename, const char *output_filename)
{
    std::ifstream input{input_filename}; /* entrada */
    std::ofstream output{output_filename}; /* salida */

    int i = 0;
    char c;
    while (i < size) /* lee hasta el limite */
    {
        input.get(c); /* entrada */
        if (c == EOF)
        {
            break;
        }
        output << c; /* salida */
        i += sizeof(c);
    }

    input.close();
    output.close();
}
