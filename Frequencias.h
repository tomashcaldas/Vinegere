#ifndef FREQUENCIAS_H
#define FREQUENCIAS_H

int load_frequencies(const char *filename, float *frequencies);
void calculate_letter_frequency(const char *text, float *frequencies);
float index_of_coincidence(const char *text);
char *find_key(const char *ciphertext, int key_length, const float *pt_freq);

#endif