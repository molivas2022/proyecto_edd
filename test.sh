#!/bin/bash

# Imprimimos una cabecera para nuestro archivo CSV
echo "Tipo de compresión;Tiempo de compresión;Tiempo de descompresión;Tamaño original;Tamaño comprimido"

# Compilamos (Quizás no es buena idea compilar en un .sh)
g++ -w test.cpp huffman_tree.cpp huffman_coding.cpp huffman_serialization.cpp lz77_trie.cpp lz77_compression.cpp lz77_serialization.cpp -I headers/ -Wall -Wextra -o test

# Repetiremos los experimentos varias veces (Opcional)
for (( r=1; r<=1; r++ ))
do
    # En caso de haber descargado todos los archivos, se revisan todos:
    # for folder in /100kb /200kb /300kb /400kb /500kb /600kb /700kb /800kb /900kb /1mb /2mb /3mb /4mb /5mb /6mb /7mb /8mb /9mb /10mb /11mb /12mb /13mb /14mb /15mb /16mb /17mb /18mb /19mb /20mb /40mb /60mb /80mb /100mb /120mb /140mb /160mb /180mb /200mb
    # En caso de sólo tener los archivos subidos al repositorio
    for folder in /100kb /200kb /300kb /400kb /500kb /600kb /700kb /800kb /900kb
    do
        # Revisaremos todos los ejemplos de texto
        for file in /0.txt /1.txt /2.txt /3.txt /4.txt /5.txt /6.txt /7.txt /8.txt /9.txt /10.txt /11.txt /12.txt /13.txt /14.txt /15.txt /16.txt /17.txt /18.txt /19.txt /20.txt /21.txt /22.txt /23.txt /24.txt /25.txt /26.txt /27.txt /28.txt /29.txt
        do
            ./test ./samples$folder$file encode
            ./test ./samples$folder$file compress
        done
    done
done
