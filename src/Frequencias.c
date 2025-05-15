#include "Frequencias.h"
#include <stdio.h>
#include <stdlib.h>

float sum_of_frequencies(const float *freqs) {
    float sum = 0;
    for (int i = 0; i < 26; i++) sum += freqs[i]; // frequencias de A-Z
    return sum;
}

int load_frequencies(const char *filename, float *freqs) { //lê o arquivo de freqências
    FILE *file = fopen(filename, "r");
    if (!file) {
        perror("Frequency file error");
        return 0;
    }

    for (int i = 0; i < 26; i++) {
        if (fscanf(file, "%f", &freqs[i]) != 1) {
            fprintf(stderr, "Invalid format at line %d\n", i+1);
            fclose(file);
            return 0;
        }
    }

    float sum = sum_of_frequencies(freqs);
    if (sum < 0.95 || sum > 1.05) {
        fprintf(stderr, "Warning: Frequency sum %.3f\n", sum);
        for (int i = 0; i < 26; i++) freqs[i] /= sum; // Normalize
    }

    fclose(file);
    return 1;
}