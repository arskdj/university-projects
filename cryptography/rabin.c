#include <stdio.h>
#include <stdlib.h>
#include <gmp.h>
#include "functions.h"

gmp_randstate_t stat;

int main()
{
    // αρχικοποίηση γεννήτριας τυχαίων
    init(stat);

    // μεταβλητές
    char* str = "hello Rabin";
    mpz_t m;
    mpz_t p;
    mpz_t q;
    mpz_t n;
    mpz_t c;
    mpz_t decrypted;

    // αρχικοποίηση μεταβλητών
    mpz_init(m);
    mpz_init(p);
    mpz_init(q);
    mpz_init(n);
    mpz_init(c);
    mpz_init(decrypted);


    // τυχαίοι πρώτοι μεγέθους 200 bits
    // οι οποίοι είναι ισότιμοι με 3 mod 4
	//
	//int bits=200;
	//mpz_urandomb(p,stat,bits);
    //while (!mpz_probab_prime_p(p,10))
	//	while (!mpz_congruent_ui_p(p,3,4))
	//		mpz_nextprime(p,p);
	//		
	//mpz_urandomb(q,stat,bits);
    //while (!mpz_probab_prime_p(q,10))
	//		while (!mpz_congruent_ui_p(q,3,4))
	//			mpz_nextprime(q,q);

	//  υπολογισμένοι p,q
	mpz_set_str(p,"6452532e37332ec325af793ea8125363cbf1dd7695f2c7fdcf",16);
	mpz_set_str(q,"1bb2c0879d6cacd11c16f45d8b7eb42c7b5006c1485aa03b27",16);

    // υπολογισμός n
    mpz_mul(n,p,q);

    char* str2;
    str2 = calloc(1,1);

    char* str3;
    str2 = calloc(1,1);

    str2mpz(m,str);
    rabin_encrypt(c,m,n);
    mpz2str(&str2,c);
	printf("with red bits = ");mpz_out_str(stdout,2,m);printf("\n");
    printf("encrypted: %s\n",str2);
	rabin_decrypt(decrypted,c,p,q,n);
	//mpz_out_str(stdout,2,decrypted);printf("\n");
    mpz2str(&str3,decrypted);
    printf("decrypted: %s\n",str3);
	
    free(str2);
    free(str3);

    mpz_clear(m);
    mpz_clear(p);
    mpz_clear(q);
    mpz_clear(n);
    mpz_clear(c);

    return 0;
}

