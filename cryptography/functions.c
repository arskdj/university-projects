#include <string.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <gmp.h>
#include <stdlib.h>
#include "functions.h"

void init()
{
    long sd = 0;
    mpz_t seed;

    mpz_init(seed);
    gmp_randinit(stat, GMP_RAND_ALG_LC,120);
    srand((unsigned) getpid());
    sd = rand();
    mpz_set_ui(seed,sd);
    gmp_randseed(stat, seed);
}

/* 
 * Δημιουργείται ο αριθμός p ο οποίος είναι σχετικά 
 * πρώτος με το n στο διάστημα (1,n)
 */
void set_prime(mpz_t p, mpz_t n)
{
    mpz_t g;
    mpz_init(g);

    // Έλεγχος εάν ο p είναι μεγαλύτερος του 1
    // και αν ο gcd είναι 1
    while( !(mpz_cmp_ui(p,1)>0 && mpz_cmp_ui(g,1)==0) ){
        mpz_gcd(g,p,n);
        mpz_urandomm(p,stat,n);
    }

    mpz_clear(g);
}

/*
 * Μετατροπή μηνύματος σε αριθμό με βάση 
 * όσοι οι χαρακτήρες του αλφαβήτου
 */
void str2mpz(mpz_t n, char* msg)
{
    char* m = msg;   // index μηνύματος
    int    i;        //index αλφαβήτου

    while(*m){
        for (i=0;CHARSET[i] && *m!=CHARSET[i];i++);
        //printf("%c = %d\n",*m,i);
        mpz_mul_ui(n,n,BASE+1); // επόμενο ψηφίο
        mpz_add_ui(n,n,i+1);  // τιμή χαρακτήρα
        *m++;
    }
}

/*
 * Μετατροπή αριθμού με βάση 52 σε μήνυμα
 */
int mpz2str(char** msg, mpz_t z)
{
    // temp number
    mpz_t n;
    mpz_init(n);
    mpz_set(n,z);

    // υπόλοιπο
    mpz_t r;
    mpz_init(r);

    // διαίρεση με αποκοπή(truncate)
    // μπαίνουν χαρακτήρες στο m με αντίστροφη σειρά
    int   i=0;
    int   len = 0;  //μήκος μηνύματος
    char* m = calloc(1,sizeof(char));
    char* ptr;
    while (mpz_cmp_ui(n,0) > 0){
        mpz_tdiv_qr_ui(n,r,n,BASE+1);
        i = mpz_get_ui(r)-1;
        if (i<=-1)
            i=1;
        *(m+len) = CHARSET[i];
        len++;
        ptr = realloc(m,(len+2)*sizeof(char));
        if (ptr==NULL){
            free(m);
            return 0;
        }else{
            m = ptr;
        }
    }
    *(m+len) = '\0';

    // αντιστρέφω το m
    *msg = realloc(*msg,(len+2)*sizeof(char));
    for (i=0;i<len;i++){
        *(*msg+i)=*(m+len-1-i);
    }
    *(*msg+i)='\0';

    mpz_clear(n);
    mpz_clear(r);

    free(m);

    return 1;
}

/*
 * Κρυπτογράφηση rsa
 * c = m^e mod n
 */
int rsa_encrypt(mpz_t c, mpz_t m, mpz_t e, mpz_t n)
{
    // αν το μήνυμα είναι μεγαλύτερο από n-1
    if (mpz_cmp(m,n)>=0)
        return -1;

    // κρυπτογράφηση μηνύματος
    mpz_powm(c,m,e,n);

    return 1;
}


/*
 * Αποκρυπτογράφηση rsa
 * m = c^d mod n
 */
int rsa_decrypt(mpz_t m, mpz_t c, mpz_t d, mpz_t n)
{
    mpz_powm(m,c,d,n);
    return 1;
}

void lastNbits(mpz_t r, mpz_t n, int N){
	mpz_t mask;
	mpz_init(mask);

	mpz_set_ui(mask,1);
	// παίρνουμε δυαδικό αριθμό με N άσσους
	mpz_mul_2exp(mask,mask,N);
	mpz_sub_ui(mask,mask,1);

	mpz_and(r,n,mask);
}

/*
 * Kρυπτογράφηση rabin
 * c = m^2 mod n
 */
int rabin_encrypt(mpz_t c, mpz_t m, mpz_t n)
{
	//mpz_out_str(stdout,2,m);printf("\n");
	mpz_t red; //redundant bits
	mpz_init(red);
	lastNbits(red,m,RABIN_RED);
	//mpz_out_str(stdout,2,red);printf("\n");
	//shift left to make space for redundant bits
	mpz_mul_2exp(m,m,RABIN_RED);
	//add them
	mpz_ior(m,m,red);
	//mpz_out_str(stdout,2,m);printf("\n");

    // αν το μήνυμα είναι μεγαλύτερο από n-1
    if (mpz_cmp(m,n)>=0){
		printf("Message too big >n. can not encrypt\n");
        return -1;
		}

    mpz_powm_ui(c,m,2,n);
    return 1;
}

/*
 * Επεκταμένος αλγόριθμος του Ευκλίδη
 */
void extended_euclid(mpz_t x, mpz_t y, mpz_t in1, mpz_t in2)
{
	mpz_t a;
	mpz_t b;
	mpz_t x1;
	mpz_t x2;
	mpz_t y1;
	mpz_t y2;
	mpz_t q;
	mpz_t r;
	mpz_t temp;

	mpz_init(a);
	mpz_init(b);
	mpz_init(x1);
	mpz_init(x2);
	mpz_init(y1);
	mpz_init(y2);
	mpz_init(q);
	mpz_init(r);
	mpz_init(temp);

	mpz_set_ui(x1,0);
	mpz_set_ui(x2,1);
	mpz_set_ui(y1,1);
	mpz_set_ui(y2,0);

	if (mpz_cmp(in1,in2)>=0){
			mpz_set(a,in1);
			mpz_set(b,in2);
	}else{
			mpz_set(b,in1);
			mpz_set(a,in2);
	}

	while (mpz_cmp_ui(b,0)>0){
			// a/b
			mpz_fdiv_qr(q,r,a,b);

			// x = x2 -q*x1
			mpz_mul(temp,q,x1);
			mpz_sub(x,x2,temp);
			
			// y = y2 -q*y1
			mpz_mul(temp,q,y1);
			mpz_sub(y,y2,temp);

			mpz_set(a,b);
			mpz_set(b,r);
			mpz_set(x2,x1);
			mpz_set(x1,x);
			mpz_set(y2,y1);
			mpz_set(y1,y);
	}
	
	mpz_set(x,x2);
	mpz_set(y,y2);

}

/*
 * Αποκρυπτογράφηση Rabin
 * Δημιουργούμε 4 ρίζες του κρυπτογραφημένου αριθμού
 * και ελέγχουμε κάθε μία αν τα τελευταία 64 bits επαναλαμβάνονται
 */
int rabin_decrypt(mpz_t m, mpz_t c, mpz_t p,mpz_t q, mpz_t n)
{
	mpz_t a;
	mpz_t b;
	mpz_t r;
	mpz_t s;
	mpz_t x;
	mpz_t y;
	mpz_t temp;
	mpz_t temp2;
	mpz_t aps;
	mpz_t bqr;

	mpz_init(a);
	mpz_init(b);
	mpz_init(r);
	mpz_init(s);
	mpz_init(temp);
	mpz_init(temp2);
	mpz_init(aps);
	mpz_init(bqr);
	mpz_init(x);
	mpz_init(y);

	extended_euclid(a,b,p,q);

	// (p + 1)/4
	mpz_add_ui(temp,p,1);
	mpz_tdiv_q_ui(temp,temp,4);
	mpz_powm(r,c,temp,p);

	// (q + 1)/4
	mpz_add_ui(temp,q,1);
	mpz_tdiv_q_ui(temp,temp,4);
	mpz_powm(s,c,temp,q);

	// aps
	mpz_mul(aps,a,p);
	mpz_mul(aps,aps,s);

	// bqr
	mpz_mul(bqr,b,q);
	mpz_mul(bqr,bqr,r);


	// x
	mpz_add(temp,aps,bqr);
	mpz_mod(x,temp,n);
	if (validate_rabin_root(x)){
		mpz_set(m,x);
	}
	printf("x=");mpz_out_str(stdout,2,x);printf("\n");

	// y
	mpz_sub(temp,aps,bqr);
	mpz_mod(y,temp,n);


	if (validate_rabin_root(y)){
		mpz_set(m,y);
	}
	printf("y=");mpz_out_str(stdout,2,y);printf("\n");

	// -x
	mpz_com(x,x);
	mpz_add_ui(x,x,1);
	mpz_mod(x,x,n);

	if (validate_rabin_root(x)){
		mpz_set(m,x);
	}
	printf("-x=");mpz_out_str(stdout,2,x);printf("\n");

	// -y
	mpz_com(y,y);
	mpz_add_ui(y,y,1);
	mpz_mod(y,y,n);

	if (validate_rabin_root(y)){
		mpz_set(m,y);
	}

	printf("-y=");mpz_out_str(stdout,2,y);printf("\n");
		
	mpz_clear(a);
	mpz_clear(b);
	mpz_clear(r);
	mpz_clear(s);
	mpz_clear(temp);
	mpz_clear(temp2);
	mpz_clear(aps);
	mpz_clear(bqr);
	mpz_clear(x);
	mpz_clear(y);
}

/*
 * Έλεγχος εάν επαναλαμβάνονται τα τελευταία 64 ψηφία
 * Ο υπολογισμός γίνεται με bitwise operators
 */
int validate_rabin_root(mpz_t root)
{
	int ret=0;

	mpz_t t1;
	mpz_t t2;
	mpz_init(t1);
	mpz_init(t2);

	lastNbits(t1,root,RABIN_RED);
	// right shift 64 
	// Διώχνουμε τα επιπλέον ψηφία
	mpz_tdiv_q_2exp(root,root,RABIN_RED);
	lastNbits(t2,root,RABIN_RED);
	// Εάν τα τελευταία 64 ψηφία ισούνται με επιπλέον 64 ψηφία
	if (mpz_cmp(t1,t2)==0){
		ret = 1;
	}

	mpz_clear(t1);
	mpz_clear(t2);

	return ret;
}

/*
 * Υπολογισμός γεννήτορα και αποθήκευση στο g
 * sp: safe prime = 2*q + 1 όπου q είναι πρώτος
 * t: τάξη = sp - 1 
 * Η τάξη παραγοντοποιείται έυκολα σε 2,q
 */
void get_generator(mpz_t a, mpz_t sp)
{
	int flag;
	mpz_t t; 
	mpz_t b1;
	mpz_t b2;
	mpz_t q;
	mpz_t temp;

	mpz_init(t);
	mpz_init(b1);
	mpz_init(b2);
	mpz_init(q);
	mpz_init(temp);

	mpz_sub_ui(t,sp,1);
	
	flag=1;
	while (flag){
			mpz_urandomm(a,stat,sp);	

			// check factor 1 = 2
			// b1 = a ^ 2 mod sp
			mpz_powm_ui(b1,a,2,sp);

			// check factor 2
			// b2 = a ^ q mod sp
			mpz_tdiv_q_ui(q,sp,2);
			mpz_powm(b2,a,q,sp);

			flag = mpz_cmp_ui(b1,1)==0 || mpz_cmp_ui(b2,1) ==0;
			//mpz_out_str(stdout,10,b1);printf("\n");
			//mpz_out_str(stdout,10,b2);printf("\n");
			}
}

/*
 * p = 2q + 1
 * Όπου p,q πρώτοι αριθμοί
 */
void get_safe_prime(mpz_t p, int bits)
{
	mpz_urandomb(p,stat,bits);
	mpz_mul_ui(p,p,2);
	mpz_add_ui(p,p,1);

	while(!mpz_probab_prime_p(p, 10)){
		mpz_urandomb(p,stat,bits);
		mpz_mul_ui(p,p,2);
		mpz_add_ui(p,p,1);
	}

}
/*
 * Υπολογισμός τυχαίου πρώτου
 */
void get_random_prime(mpz_t p, int bits)
{
    mpz_urandomb(p,stat,bits);
    mpz_nextprime(p,p);
}

/*
 * Κρυπτογράφηση El Gamal
 * γ,δ: κρυπτοκείμενο
 * m: μήνυμα
 * ad: α^d
 */
void elgamal_encrypt(mpz_t gamma, mpz_t delta, mpz_t m,mpz_t p, mpz_t a, mpz_t ad)
{
	mpz_t k;
	mpz_t dk;
	mpz_t p2;
	mpz_t temp;

	mpz_init(k);
	mpz_init(dk);
	mpz_init(p2);
	mpz_init(temp);

	// k random(1,p-2)
	mpz_sub_ui(p2,p,2);
	mpz_urandomm(k,stat,p2);

	// γ = a^k mod p
	mpz_powm(gamma,a,k,p);

	// δ = ma^(dk) mod p
	mpz_powm(temp,ad,k,p);
	mpz_mul(temp,temp,m);
	mpz_mod(delta,temp,p);

}

/*
 * Αποκρυπτογράφηση El Gamal
 * m: αποκρυπτογραφημένο μήνυμα
 * γ,δ: κρυπτοκείμενο
 * d: ιδιωτικό κλειδί
 */
void elgamal_decrypt(mpz_t m, mpz_t gamma, mpz_t delta, mpz_t d,  mpz_t p)
{
	mpz_t minus_d;
	mpz_t temp;

	mpz_init(minus_d);
	mpz_init(temp);
	
	// -d
	mpz_com(minus_d,d);
	mpz_add_ui(minus_d,minus_d,1);

	// δ * γ^(-d) mod p
	mpz_powm(temp,gamma,minus_d,p);
	mpz_mul(temp,temp,delta);	
	mpz_mod(m,temp,p);
}

void elgamal_genkeys(int bits, mpz_t p, mpz_t a, mpz_t ad, mpz_t d)
{
	mpz_t n;
	mpz_init(n);

	get_safe_prime(p, bits);
	printf("safe prime: ");mpz_out_str(stdout,16,p);printf("\n");

	get_generator(a,p);
	printf("generator: ");mpz_out_str(stdout,16,a);printf("\n");

	// Ιδιωτικό κλειδί d
	mpz_sub_ui(n,p,2);
	mpz_urandomm(d,stat,n);

	// a^d % p
	mpz_powm(ad,a,d,p);

	mpz_clear(n);
}
