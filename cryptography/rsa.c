#include <stdio.h>
#include <stdlib.h>
#include <gmp.h>
#include "functions.h"

int main()
{
    // αρχικοποίηση γεννήτριας τυχαίων
    init();

    // μεταβλητές
    char* str = "hello \nRSA";
    mpz_t m;
    mpz_t p;
    mpz_t q;
    mpz_t n;
    mpz_t fi;
    mpz_t e;
    mpz_t d;
    mpz_t c;

    // αρχικοποίηση μεταβλητών
    mpz_init(m);
    mpz_init(p);
    mpz_init(q);
    mpz_init(n);
    mpz_init(fi);
    mpz_init(e);
    mpz_init(d);
    mpz_init(c);

    // τυχαίοι πρώτοι μεγέθους 512 bits
	get_random_prime(p,512);
	get_random_prime(q,512);

    // υπολογισμός n
    mpz_mul(n,p,q);

    // υπολογισμός φ(n)=(p-1)*(q-1)
    mpz_sub_ui(p,p,1);
    mpz_sub_ui(q,q,1);
    mpz_mul(fi,p,q);


    // τυχαίος e στο διάστημα (1,φ) σχετικά πρώτος με το φ
    // υπολογισμός d (αντίστροφος του e)
    // το d να μην ισούται με 0
    do {
        set_prime(e,fi);
        mpz_invert(d,e,fi);
    } while (mpz_cmp_ui(d,0)==0);

    printf("p:"); mpz_out_str(stdout,10,p); printf("\n\n");
    printf("q:"); mpz_out_str(stdout,10,q); printf("\n\n");
    printf("n:"); mpz_out_str(stdout,10,n); printf("\n\n");
    printf("fi:"); mpz_out_str(stdout,10,fi); printf("\n\n");
    printf("e:"); mpz_out_str(stdout,10,e); printf("\n\n");
    printf("d:"); mpz_out_str(stdout,10,d); printf("\n\n");

    char* str2;
    str2 = calloc(1,1);

    str2mpz(m,str);
    rsa_encrypt(c,m,e,n);
    mpz2str(&str2,c);
    printf("encrypted: %s\n",str2);

    rsa_decrypt(m,c,d,n);
    mpz2str(&str2,m);
    printf("decrypted: %s\n",str2);
    free(str2);



    mpz_clear(m);
    mpz_clear(p);
    mpz_clear(q);
    mpz_clear(n);
    mpz_clear(fi);
    mpz_clear(e);
    mpz_clear(d);
    mpz_clear(c);

    return 0;
}

