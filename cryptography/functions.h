#include <gmp.h>

#define CHARSET "\n abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ"
#define BASE 54
#define RABIN_RED 30

gmp_randstate_t stat;

void init();
int mpz2str(char** msg, mpz_t z);
void str2mpz(mpz_t n, char* msg);
void set_prime(mpz_t p, mpz_t n);
int rsa_decrypt(mpz_t m, mpz_t c, mpz_t d, mpz_t n);
int rsa_encrypt(mpz_t c, mpz_t m, mpz_t e, mpz_t n);
int rabin_encrypt(mpz_t c, mpz_t m, mpz_t n);
void lastNbits(mpz_t r, mpz_t n, int N);
int rabin_decrypt(mpz_t m, mpz_t c, mpz_t p,mpz_t q, mpz_t n);
void extended_euclid(mpz_t x, mpz_t y, mpz_t in1, mpz_t in2);
int validate_rabin_root(mpz_t root);
void get_safe_prime(mpz_t n, int bits);
void get_random_prime(mpz_t p, int bits);
void get_generator(mpz_t a, mpz_t sp);
void elgamal_genkeys(int bits, mpz_t p, mpz_t a, mpz_t ad, mpz_t d);
void elgamal_encrypt(mpz_t gamma, mpz_t delta, mpz_t m,mpz_t p, mpz_t a, mpz_t ad);
void elgamal_decrypt(mpz_t m, mpz_t gamma, mpz_t delta, mpz_t d,  mpz_t p);
