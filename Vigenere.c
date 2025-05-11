#include "Vigenere.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// Carrega o texto cifrado do arquivo
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
    
    fread(buffer, 1, length, file);
    buffer[length] = '\0';
    
    fclose(file);
    return buffer;
}

// Decifra o texto usando a chave encontrada
char *decrypt_vigenere(const char *ciphertext, const char *key) {
    int key_len = strlen(key);
    if (key_len == 0) return NULL;
    
    int text_len = strlen(ciphertext);
    char *plaintext = malloc(text_len + 1);
    if (!plaintext) return NULL;
    
    for (int i = 0, j = 0; ciphertext[i]; i++) {
        if (isalpha(ciphertext[i])) {
            char c = tolower(ciphertext[i]);
            char k = tolower(key[j % key_len]);
            
            plaintext[i] = 'a' + (c - k + 26) % 26;
            j++;
        } else {
            plaintext[i] = ciphertext[i];
        }
    }
    plaintext[text_len] = '\0';
    
    return plaintext;
}