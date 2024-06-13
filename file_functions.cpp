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

// Fuente: Chat GPT >.<
void compare_file(const char* &archivo1, const char* &archivo2)
{
    std::ifstream file1(archivo1);
    std::ifstream file2(archivo2);

    if (!file1.is_open() || !file2.is_open())
    {
        std::cerr << "Error al abrir los archivos." << std::endl;
        return;
    }

    std::string lineaArchivo1, lineaArchivo2;
    bool sonIguales = true;

    while (std::getline(file1, lineaArchivo1) && std::getline(file2, lineaArchivo2))
    {
        if (lineaArchivo1 != lineaArchivo2)
        {
            sonIguales = false;
            break;
        }
    }

    // Verificar si uno de los archivos tiene más líneas que el otro
    if (sonIguales)
    {
        if ((file1.eof() && !file2.eof()) || (!file1.eof() && file2.eof()))
        {
            sonIguales = false;
        }
    }

    if (sonIguales)
    {
        std::cout << "Los archivos son iguales" << std::endl;
    }
    else
    {
        std::cout << "Los archivos NO son iguales" << std::endl;
    }

    file1.close();
    file2.close();
}