#include <stdio.h>
#include <stdlib.h>
#include <gmp.h>
#include "functions.h"


int main()
{
    // αρχικοποίηση γεννήτριας τυχαίων
    init();

    // μεταβλητές
    char* str = "hello El Gamal";
    char* str2;
    str2 = calloc(1,1);

    mpz_t m;
    mpz_t a;
    mpz_t p;
    mpz_t d;
    mpz_t ad;
	mpz_t gamma;
	mpz_t delta;

    // αρχικοποίηση μεταβλητών
    mpz_init(m);
    mpz_init(p);
	mpz_init(a);
    mpz_init(d);
    mpz_init(ad);
	mpz_init(gamma);
	mpz_init(delta);

	// Δημιουργία κλειδιών
	elgamal_genkeys(200,p,a,ad,d);

	// plaintext
	str2mpz(m,str);
	elgamal_encrypt(gamma,delta,m,p,a,ad);

    mpz2str(&str2,gamma);
    printf("gamma: %s\n",str2);

    mpz2str(&str2,delta);
    printf("delta: %s\n",str2);

	elgamal_decrypt(m,gamma,delta,d,p);
    mpz2str(&str2,m);
    printf("decrypted: %s\n",str2);

		mpz_clear(m);
		mpz_clear(p);
		mpz_clear(a);
		mpz_clear(d);
		mpz_clear(ad);
		mpz_clear(gamma);
		mpz_clear(delta);

    return 0;
}

