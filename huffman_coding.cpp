#include "huffman_coding.h"
#include "huffman_tree.h"
#include <string>
#include <fstream>
#include <iostream>

using namespace Huffman;

const bool _HUFFMAN_CODING_DEBUG = 0; /* Modo de depuración */
size_t Huffman::LastSavedSize = 0;

/* debugging :33 :3 */
void printbits(unsigned char v);

std::string Huffman::str_encode(std::fstream& ifs) 
{
    auto freq_map = readFrequencies(ifs);           
    auto huffman_tree = createHuffmanTree(freq_map);
    std::string encoded_msg;

    /* Obtiene mapas de codificación y decodificación del texto leído */
    auto dicts = getMaps(huffman_tree, freq_map);
    auto coding = dicts.first;
    auto decoding = dicts.second;

    /* Vuelve al inicio del archivo y define un string con el mensaje codificado */
    ifs.clear();
    ifs.seekg(0, std::ios::beg);
    char ch;
    while (ifs >> std::noskipws >> ch) {
        encoded_msg += coding[ch];
    }

    /* DEBUGGING PRINT */
    if (_HUFFMAN_CODING_DEBUG) {
        for (auto it = coding.begin(); it != coding.end(); it++) {
            auto key = it->first;
            std::cout << "'" << key << "' :     " << coding[key] << std::endl;
        }
        std::cout << encoded_msg << std::endl;
    }

    return encoded_msg;
}

std::pair<unsigned int,unsigned char*> Huffman::bit_encode(std::fstream& ifs) 
{
    auto freq_map = readFrequencies(ifs);           
    auto huffman_tree = createHuffmanTree(freq_map);

    /* Obtiene mapas de codificación y decodificación del texto leído */
    auto dicts = getMaps(huffman_tree, freq_map);
    auto coding = dicts.first;
    auto decoding = dicts.second;

    /* Computar tamaño del mensaje codificado mediante la tabla de frecuencias, luego pedir memoria heap para arreglo de este tamaño. */
    size_t encoded_msg_len = 0;
    for (auto it = coding.begin(); it != coding.end(); it++) {
        char key = it->first;
        encoded_msg_len += ((freq_map.find(key))->second)*((coding[key]).length());
    }

    /* Vuelve al inicio del archivo y define un string con el mensaje codificado */
    ifs.clear();
    ifs.seekg(0, std::ios::beg);

    /* Para guardar los caracteres codificados, modificamos cada byte de un arreglo de unsigned char ``encoded_msg``, que tiene suficiente espacio para llenar el texto codificado completo */
    unsigned char* encoded_msg;

    /* Si por suerte el largo del mensaje codificado es un multiplo de 8, entonces guardamos la cantidad exacta de bits */
    if (encoded_msg_len % 8 == 0)
        encoded_msg = new unsigned char[(encoded_msg_len/8)]; 
    else
        encoded_msg = new unsigned char[(encoded_msg_len/8)+1];
    
    encoded_msg[0] = (unsigned char)0; // inicializa a 0 para eliminar "basura"
    int EncMsg_idx = 0;
    char current_ch; // char del texto original que se está leyendo
    int bitflip_pos = 7; // posicion de Izquierda a Derecha (mayor a menor) donde se voltea un bit

    /* me voy a matar ctm (Loop para insertar secuencias de bits en cada byte del arreglo encoded_msg) */
    while (ifs >> std::noskipws >> current_ch) {
        std::string encoded_char = (coding[current_ch]);

        for (int i=0; i < (int)encoded_char.length(); i++) {
            /* cuando un byte del arreglo se llena, incrementar el indice de encoded_msg para asi pasar al siguiente byte */
            if (bitflip_pos < 0) {
                EncMsg_idx++;
                encoded_msg[EncMsg_idx] = (unsigned char)0;
                bitflip_pos = 7;
            }
            /* hacer flip del bit en bitflip_pos (pensando los indices de un byte como decreciendo hacia la derecha) si es que el char codificado posee un 1 en la i-esima posicion*/
            if (encoded_char[i] == '1') {
                encoded_msg[EncMsg_idx] |= ((unsigned char)1 << bitflip_pos);
            }
            bitflip_pos--;
        }
    }

    /* Debugging prints */
    if (_HUFFMAN_CODING_DEBUG) {
        std::cout << "Encoding generated: " << std::endl;
        for (auto it = coding.begin(); it != coding.end(); it++) {
            auto key = it->first;
            if (key == '\n')
                std::cout << "'" << "[NEWLINE]" << "' :     " << coding[key] << std::endl;
            else if (key == ' ')
                std::cout << "'" << "[WHITESPACE]" << "' :     " << coding[key] << std::endl;
            else
                std::cout << "'" << key << "' :     " << coding[key] << std::endl;
        }
        std::cout << std::endl;

        int char_arr_size = (encoded_msg_len/8)+1;
        std::cout << "char array size: " << char_arr_size << std::endl;
        std::cout << "encoded message length: " << encoded_msg_len << " bits" << std::endl;
        std::cout << "printing encoded message's array... " << std::endl;
        for (int i=0; i < (int)(encoded_msg_len/8)+1; i++) {
            printbits(encoded_msg[i]);
            std::cout << " ";
        }
    }

    LastSavedSize = encoded_msg_len;
    return std::make_pair((unsigned int)encoded_msg_len, encoded_msg);
}

std::string Huffman::bit_decode(unsigned char* encoded_msg, size_t n_bits, Node* tree_head) 
{
    int EncMsg_idx = 0;
    std::string RetStr;

    Node* current_node = tree_head;
    int bit_pos = 7;
    for (size_t i=0; i < n_bits; i++) {
        /* Comprueba si se llegó al limite del BYTE que se está leyendo en encoded_msg */
        if (bit_pos < 0) {
            EncMsg_idx++;
            bit_pos = 7;
        }
        /* Comprueba si el BIT leído es 0, en tal caso viaja al hijo izquierdo */
        if ((encoded_msg[EncMsg_idx] & ((unsigned char)1 << bit_pos)) == (unsigned char)0) {
            Node* left_child = current_node->left;
            current_node = left_child;
        }
        /* En caso contrario al anterior (1), viaja al hijo derecho */
        else {
            Node* right_child = current_node->right;
            current_node = right_child;
        }
        /* Si uno de los dos hijos de current_node es nullptr, es un nodo hoja (carácter) */
        if (current_node->left == nullptr || current_node->right == nullptr) {
            RetStr += current_node->symbol;
            current_node = tree_head;
        }
        bit_pos--;
    }

    return RetStr;
}

/* debug */
void printbits(unsigned char v) {
    for(int i = 7; i >= 0; i--) putchar('0' + ((v >> i) & 1));
}