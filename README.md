## Proyecto semestral: Codificación vs Compresión

Programa para comprimir o descomprimir archivos de texto mediante el algoritmo de codificación de Huffman o mediante compresión LZ77. Ambas implementaciones fueron desarrolladas por los miembros del grupo de trabajo formado para el proyecto final del curso Estructura de Datos de la Universidad de Concepción.

Instrucciones de compilación:
```
g++ main.cpp huffman_tree.cpp huffman_coding.cpp huffman_serialization.cpp lz77_trie.cpp lz77_compression.cpp lz77_serialization.cpp -I headers/ -Wall -Wextra -o main
```

Instrucciones de ejecución:
```
./main <operacion> <path al archivo de entrada> <nombre del archivo de salida>
```
El ejecutable necesita tres argumentos:
- ``<operacion>`` tiene cuatro opciones disponibles: encode, decode, compress y decompress. Encode y decode utilizan el método de Huffman, mientras que compress y decompress utilizan compresión LZ.
- ``<path al archivo de entrada>`` es el path relativo al archivo de texto que se desea comprimir o descomprimir.
- ``<nombre del archivo de salida>`` es el nombre del archivo binario de salida (si se utilizó encode/compress) o del archivo de texto de salida (si se utilizó decode/decompress) 

En la carpeta ``sample`` se encuentran algunos de los archivos de texto utilizados para hacer los test de compresión.
El resto de archivos de texto se encuentran en la siguiente dirección: https://drive.google.com/file/d/1jtSCU4wMwNdJK9na5H8dm7br4Ft75P9j/view
