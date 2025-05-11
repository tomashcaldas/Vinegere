#include "Kasiski.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

// Função para encontrar sequências repetidas e calcular distâncias
void find_repeated_sequences(const char *text, int *distances, int *count) {
    // Implementação simplificada - na prática seria mais complexa
    // Procura por trigramas repetidos
    for (int i = 0; i < strlen(text) - 3; i++) {
        char trigram[4];
        strncpy(trigram, text + i, 3);
        trigram[3] = '\0';
        
        for (int j = i + 3; j < strlen(text) - 3; j++) {
            if (strncmp(trigram, text + j, 3) == 0) {
                distances[*count] = j - i;
                (*count)++;
            }
        }
    }
}

// Calcula o MDC de dois números
int gcd(int a, int b) {
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

// Encontra o tamanho mais provável da chave
int find_key_length(const char *ciphertext) {
    int distances[1000];
    int count = 0;
    
    find_repeated_sequences(ciphertext, distances, &count);
    
    if (count == 0) {
        return -1; // Não encontrou sequências repetidas
    }
    
    // Calcula o MDC das distâncias encontradas
    int current_gcd = distances[0];
    for (int i = 1; i < count; i++) {
        current_gcd = gcd(current_gcd, distances[i]);
        if (current_gcd == 1) {
            break;
        }
    }
    
    return current_gcd > 1 ? current_gcd : -1;
}