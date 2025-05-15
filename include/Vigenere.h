#ifndef VIGENERE_H
#define VIGENERE_H

#include <stdio.h>

// Interface para operações Vigenère
char *load_ciphertext(const char *filename);
char *decrypt_vigenere(const char *ciphertext, const char *key);

#endif