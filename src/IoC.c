#include "IoC.h"
#include <math.h>
#include <ctype.h>

float index_of_coincidence(const char *text, int start, int step) {
    int counts[26] = {0};
    int total = 0;

    for (int i = start; text[i]; i += step) {
        if (isalpha(text[i])) {                    // caractere é alfabeto?
            counts[tolower(text[i]) - 'a']++;
            total++;
        }
    }

    if (total < 2) return 0.0f;         
    
    float sum = 0;
    for (int i = 0; i < 26; i++) {              // aplica a formula do indice de coincidência
        sum += counts[i] * (counts[i] - 1);
    }
    
    return sum / (total * (total - 1));
}

int alternative_key_length_method(const char *ciphertext) {  //recebe o texto encriptado
    const float target = 0.07797f;              //Ic da lingua portuguesa (Ic alvo)
    int best_length = 1;
    float best_diff = INFINITY;             //inicialmente diferença é infinita

    for (int l = 1; l <= 20; l++) {    // testa valores de L de 1 a 20
        float avg = 0;
        for (int offset = 0; offset < l; offset++) {
            avg += index_of_coincidence(ciphertext, offset, l);
        }
        avg /= l;
        
        float diff = fabs(avg - target);  //valor em ponto flutuante para differença com o Ic alvo
        if (diff < best_diff) {
            best_diff = diff;
            best_length = l;
        }
    }

    return best_diff < 0.005 ? best_length : -1; // Mais rigoroso (retorna o melhor tamanho se a
                                                 //     melhor diferença for menor que 0.005% do Ic alvo)
}