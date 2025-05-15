#include "Kasiski.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

void find_repeated_sequences(const char *text, int **distances, int *count) {
    *count = 0;
    size_t text_len = strlen(text);   //obtem o comprimento do texto cifrado
    size_t capacity = 100;              //capacidade inicial do array dinâmico
    
    *distances = malloc(capacity * sizeof(int));    //aloca em memoria dinâmica para array de inteiros distância
    if (!*distances) return;

    for (size_t i = 0; i < text_len - 3; i++) {  //varre o texto a cada 3 caracteres formando trigramas
        char trigram[4];              
        strncpy(trigram, text + i, 3); //guarda trigrama
        trigram[3] = '\0';

        for (size_t j = i + 3; j < text_len - 3; j++) {  //varre a partir do ponto de varredura anterior procurando outro trigrama igual ao atual
            if (strncmp(trigram, text + j, 3) == 0) {
                if (*count >= capacity) {    //se ficar sem espaço, dobra o tamanho do vetor dinâmico
                    capacity *= 2;
                    int *temp = realloc(*distances, capacity * sizeof(int));
                    if (!temp) {
                        free(*distances);
                        *distances = NULL;
                        *count = 0;
                        return;
                    }
                    *distances = temp;
                }
                (*distances)[(*count)++] = j - i;   //quando encontrar uma repetição de trigrama, armazena a distancia entre os dois
            }
        }
    }
}

int gcd(int a, int b) {             //maior divisor comum
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

int find_key_length(const char *ciphertext) {
    if (!ciphertext || strlen(ciphertext) < 50) return -1;  //porque kasiski é ineficiente com tamanhos pequenos de texto

    int *distances = NULL;
    int count = 0;
    find_repeated_sequences(ciphertext, &distances, &count); //encontra as distancias de trigramas

    int result = -1;
    if (count > 0) {                //se houver trigramas com distancias encontradas,
        int current_gcd = distances[0];         //adiciona essa distância como resultado inicial para gcd()
        for (int i = 1; i < count && current_gcd != 1; i++) { //mais de uma distância -> armazena e vai calculando o gdc()
            current_gcd = gcd(current_gcd, distances[i]);
        }
        result = current_gcd > 1 ? current_gcd : -1;  // tamanho de cifra é maior que 1? se sim, este é o tamanho final
    }

    free(distances);
    return result;
}