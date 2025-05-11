#include "Frequencias.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>

// Carrega as frequências de letras do arquivo
int load_frequencies(const char *filename, float *frequencies) {
    FILE *file = fopen(filename, "r");
    if (!file) return 0;
    
    for (int i = 0; i < 26; i++) {
        if (fscanf(file, "%f", &frequencies[i]) != 1) {
            fclose(file);
            return 0;
        }
    }
    
    fclose(file);
    return 1;
}

// Calcula a frequência de letras em um texto
void calculate_letter_frequency(const char *text, float *frequencies) {
    int counts[26] = {0};
    int total = 0;
    
    for (int i = 0; text[i]; i++) {
        if (isalpha(text[i])) {
            char c = tolower(text[i]);
            counts[c - 'a']++;
            total++;
        }
    }
    
    for (int i = 0; i < 26; i++) {
        frequencies[i] = total > 0 ? (float)counts[i] / total : 0;
    }
}

// Calcula o índice de coincidência
float index_of_coincidence(const char *text) {
    int counts[26] = {0};
    int total = 0;
    
    for (int i = 0; text[i]; i++) {
        if (isalpha(text[i])) {
            char c = tolower(text[i]);
            counts[c - 'a']++;
            total++;
        }
    }
    
    if (total < 2) return 0.0f;
    
    float sum = 0.0f;
    for (int i = 0; i < 26; i++) {
        sum += counts[i] * (counts[i] - 1);
    }
    
    return sum / (total * (total - 1));
}

// Encontra a chave usando análise de frequência
char *find_key(const char *ciphertext, int key_length, const float *pt_freq) {
    char *key = malloc(key_length + 1);
    if (!key) return NULL;
    
    key[key_length] = '\0';
    
    // Para cada posição na chave
    for (int k = 0; k < key_length; k++) {
        // Extrai os caracteres cifrados com esta posição da chave
        int count = 0;
        for (int i = k; ciphertext[i]; i += key_length) {
            count++;
        }
        
        char *group = malloc(count + 1);
        if (!group) {
            free(key);
            return NULL;
        }
        
        int j = 0;
        for (int i = k; ciphertext[i]; i += key_length) {
            group[j++] = ciphertext[i];
        }
        group[j] = '\0';
        
        // Testa cada deslocamento possível (a-z)
        float best_score = -1.0f;
        char best_char = 'a';
        
        for (char c = 'a'; c <= 'z'; c++) {
            // Decifra o grupo com este caractere da chave
            char *decrypted = malloc(count + 1);
            if (!decrypted) {
                free(group);
                free(key);
                return NULL;
            }
            
            for (int i = 0; i < count; i++) {
                decrypted[i] = 'a' + (group[i] - c + 26) % 26;
            }
            decrypted[count] = '\0';
            
            // Calcula a frequência deste texto decifrado
            float freq[26];
            calculate_letter_frequency(decrypted, freq);
            
            // Compara com as frequências do português
            float score = 0.0f;
            for (int i = 0; i < 26; i++) {
                score += freq[i] * pt_freq[i];
            }
            
            if (score > best_score) {
                best_score = score;
                best_char = c;
            }
            
            free(decrypted);
        }
        
        key[k] = best_char;
        free(group);
    }
    
    return key;
}