#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Kasiski.h"
#include "Frequencias.h"
#include "Vigenere.h"

int main() {
    // Carrega o texto cifrado
    char *ciphertext = load_ciphertext("data/3379-4.txt");
    if (!ciphertext) {
        fprintf(stderr, "Erro ao carregar o texto cifrado\n");
        return 1;
    }

    // Carrega as frequências de letras em português
    float pt_freq[26];
    if (!load_frequencies("data/frequencia.txt", pt_freq)) {
        fprintf(stderr, "Erro ao carregar as frequências\n");
        free(ciphertext);
        return 1;
    }

    // Passo 1: Determinar o tamanho da chave
    int key_length = find_key_length(ciphertext);
    printf("Tamanho estimado da chave: %d\n", key_length);

    // Passo 2: Determinar a chave
    char *key = find_key(ciphertext, key_length, pt_freq);
    printf("Chave estimada: %s\n", key);

    // Passo 3: Decifrar o texto
    char *plaintext = decrypt_vigenere(ciphertext, key);
    printf("\nTexto decifrado:\n%s\n", plaintext);

    // Libera memória
    free(ciphertext);
    free(key);
    free(plaintext);

    return 0;
}