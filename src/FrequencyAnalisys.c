#include "FrequencyAnalisys.h"
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include <stdio.h>

char *find_key(const char *ciphertext, int key_length, const float *pt_freq) { //recebe texto, tamanho da chave e Ic da lingua portuguesa
    if (!ciphertext || key_length <= 0 || !pt_freq) return NULL;  //se chave calculada tiver tamanho <= 0 ; return NULL

    char *key = malloc(key_length + 1); //aloca expaço de chave + \0
    if (!key) return NULL;
    key[key_length] = '\0';

    for (int k = 0; k < key_length; k++) { // loop para a posição da chave com todos os caracteres iniciados como 'a'
        float max_score = -1;
        char best_char = 'a';

        for (char c = 'a'; c <= 'z'; c++) { //testa todas as letras para a posição atual
            float score = 0;
            int count = 0;

            for (int i = k; ciphertext[i]; i += key_length) {  //decifra parcialmente usando a fórmula de decifração posicional
                if (!isalpha(ciphertext[i])) continue;
                char decrypted = (tolower(ciphertext[i]) - c + 26) % 26 + 'a'; //usando o valor de letra minuscula
                score += pt_freq[decrypted - 'a'];   // acumula a frequência da letra resultante como o 'score'
                count++;
            }

            printf("Analisando posição %d/%d: candidato '%c' (score: %.3f)\n", 
                  k+1, key_length, c, count > 0 ? score/count : 0);

            if (count > 0 && score > max_score) { //define se o caractere é o melhor atual desta posição
                max_score = score;
                best_char = c;
            }
        }

        if (max_score < 0.04) { //descarta letras de score < 0.04
            fprintf(stderr, "Aviso: Pontuação baixa para posição %d (%.3f)\n", k, max_score);
            best_char = '?';
        }

        key[k] = best_char; //escolhida a letra para aquela posição
    }
    return key;
}