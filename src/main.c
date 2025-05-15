#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "Kasiski.h"
#include "Frequencias.h"
#include "Vigenere.h"
#include "FrequencyAnalisys.h"
#include "IoC.h"

void print_analysis_report(const char *text, const float *freqs) {  //report final para os resultados
    size_t len = strlen(text);
    int alpha = 0, non_alpha = 0;
    
    printf("\n=== ANALYSIS REPORT ===\n");
    printf("Total length: %zu\n", len);
    
    // Character statistics
    for (size_t i = 0; i < len; i++) {
        isalpha(text[i]) ? alpha++ : non_alpha++;
    }
    printf("Alphabetic: %d (%.1f%%)\n", alpha, (alpha*100.0)/len);
    printf("Non-alphabetic: %d\n", non_alpha);
    
    // Frequency validation
    float sum = sum_of_frequencies(freqs);
    printf("Frequency sum: %.4f\n", sum);
    
    // Sample ciphertext
    printf("\nFirst 200 characters:\n");
    for (int i = 0; i < 500 && text[i]; i++) {
        putchar(text[i]);
        if ((i+1) % 50 == 0) printf("\n");
    }
    printf("\n");
}

int main() {
    // Initialize pointers
    char *ciphertext = NULL;
    float pt_freq[26] = {0};
    int key_length = -1;
    char *key = NULL;
    char *plaintext = NULL;

    // 1. Load ciphertext
    printf("\n[1/5] Loading ciphertext...\n");
    ciphertext = load_ciphertext("data/3379-4.txt");
    if (!ciphertext || strlen(ciphertext) < 100) {    //armazena se texto for maior que 100 caracteres
        fprintf(stderr, "Error: Invalid ciphertext\n");
        goto cleanup;
    }

    // 2. Load frequencies
    printf("[2/5] Loading frequencies...\n");
    if (!load_frequencies("data/frequencia.txt", pt_freq)) {
        fprintf(stderr, "Error: Frequency load failed\n");
        goto cleanup;
    }

    // 3. Determine key length
    printf("[3/5] Finding key length...\n");
    key_length = find_key_length(ciphertext);  // método Kasiski
    if (key_length <= 0) {
        printf("Kasiski failed. Trying IoC...\n");
        key_length = alternative_key_length_method(ciphertext); //método índice de coincidência
    }
    if (key_length <= 0) key_length = 5;  // Fallback

    // 4. Find key
    printf("[4/5] Finding key (length %d)...\n", key_length);
    key = find_key(ciphertext, key_length, pt_freq);        //encontra os caracteres da cifra
    if (!key) {
        fprintf(stderr, "Error: Key discovery failed\n");
        goto cleanup;
    }

    // 5. Decrypt
    printf("[5/5] Decrypting...\n");
    plaintext = decrypt_vigenere(ciphertext, key);      //aplica a cifra para decriptar o texto
    if (!plaintext) {
        fprintf(stderr, "Error: Decryption failed\n");
        goto cleanup;
    }

    // Results
    printf("\nSUCCESS!\nKey: %s\n", key);
    printf("Decrypted text (partial):\n%.200s\n", plaintext); //mostra 200 primeiros caracteres do texto decriptado

    if (strchr(key, '?') != NULL) {  //caracteres inválidos
        fprintf(stderr, "\nERRO: Chave contém caracteres inválidos!\n");
        fprintf(stderr, "Possíveis causas:\n");
        fprintf(stderr, "1. Texto cifrado muito curto\n");
        fprintf(stderr, "2. Frequências mal formatadas\n");
        fprintf(stderr, "3. Chave muito longa\n");
    }

cleanup:

    free(ciphertext);   //limpa as memórias
    free(key);
    free(plaintext);
    return 0;
}