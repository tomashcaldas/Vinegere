#include "Vigenere.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *load_ciphertext(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (!file) return NULL;

    fseek(file, 0, SEEK_END);
    long length = ftell(file);
    fseek(file, 0, SEEK_SET);

    char *buffer = malloc(length + 1);
    if (!buffer) {
        fclose(file);
        return NULL;
    }

    if (fread(buffer, 1, length, file) != length) {
        free(buffer);
        fclose(file);
        return NULL;
    }

    buffer[length] = '\0';
    fclose(file);
    return buffer;
}

char *decrypt_vigenere(const char *ciphertext, const char *key) { //usa a cifra encontrada para decriptar o texto
    if (!ciphertext || !key) return NULL;

    size_t text_len = strlen(ciphertext); //tamanho texto
    size_t key_len = strlen(key); //tamanho cifra
    char *result = malloc(text_len + 1); //vetor resultado + \0

    size_t key_idx = 0;
    for (size_t i = 0; i < text_len; i++) {
        if (isalpha(ciphertext[i])) {
            char base = islower(ciphertext[i]) ? 'a' : 'A'; // caractere minúsculo ou maiúsculo?
            char k = tolower(key[key_idx % key_len]) - 'a'; 
            result[i] = (ciphertext[i] - base - k + 26) % 26 + base; //resultado de 1 a 26 transformado na letra decriptada respectiva
            key_idx++;
        } else {
            result[i] = ciphertext[i];
        }
    }
    result[text_len] = '\0';
    return result;
}