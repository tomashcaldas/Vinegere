#ifndef KASISKI_H
#define KASISKI_H

#include <stdlib.h>

// Interface para teste de Kasiski
void find_repeated_sequences(const char *text, int **distances, int *count);
int gcd(int a, int b);
int find_key_length(const char *ciphertext);

#endif