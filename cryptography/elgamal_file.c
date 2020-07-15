#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <gmp.h>
#include "functions.h"

#define KEYSIZE  1024

int main(int argc, char* argv[])
{
	int encryption = !strcmp(argv[1],"d")==0;
	int decryption = !strcmp(argv[1],"e")==0;
	
	// Ελέγχοι παραμέτρων
	if (!encryption && !decryption){
		printf("Wrong argument: Enter e for encryption, d for decryption.\n");
		return -1;
	}

	if (argc !=3 && encryption){
		printf("Encryption: elgamal_file e <file>\n");
		return 0;
	}

	if (argc !=4 && decryption){
		printf("Decryption: elgamal_file d <gamma> <delta>\n");
		return 0;
	}





    // αρχικοποίηση γεννήτριας τυχαίων
    init();

    // μεταβλητές
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
	
	char* p_path = "keys/p.pub";
	char* a_path = "keys/a.pub";
	char* ad_path = "keys/ad.pub";
	char* priv_path  = "keys/d.priv";

	FILE* fp = fopen(p_path,"r");
	FILE* fa = fopen(a_path,"r");
	FILE* fad = fopen(ad_path,"r");
	FILE* fpriv = fopen(priv_path,"r");

	char* str = calloc(1,1);

	// Αν δεν υπάρχουν τα αρχεία δημιούργησέ τα 
	if (!fp || !fa || !fad || !fpriv){
		if (fp)
				fclose(fp);
		if (fa)
				fclose(fa);
		if (fad)
				fclose(fad);
		if (fpriv)
				fclose(fpriv);

		fp = fopen(p_path,"w");
		fa = fopen(a_path,"w");
		fad = fopen(ad_path,"w");
		fpriv = fopen(priv_path,"w");

		printf("Generating keys\n");
		elgamal_genkeys(KEYSIZE,p,a,ad,d);

		printf("Save keys to keys dir\n");
		mpz_out_str(fp,16,p);
		mpz_out_str(fa,16,a);
		mpz_out_str(fad,16,ad);
		mpz_out_str(fpriv,16,d);

		fclose(fp);
		fclose(fa);
		fclose(fad);
		fclose(fpriv);
	}else{
	//Αλλιώς διάβασέ τα
		mpz_inp_str(p,fp,16);
		mpz_inp_str(a,fa,16);
		mpz_inp_str(ad,fad,16);
		mpz_inp_str(d,fpriv,16);

	}

	// Κρυπτογράφηση
	if (encryption){

			char* filepath = malloc(100);
			strcpy(filepath,argv[2]);

			FILE* file = fopen(filepath,"r");
			if (file==NULL){
				printf("Error: File does not exist\n");
				return -1;
			}			


			char* buffer = malloc(1000);

			fgets(buffer,1000,file);


			str2mpz(m,buffer);
			elgamal_encrypt(gamma,delta,m,p,a,ad);


			// Αποθήκευση κρυπτοκείμενου
			char* gamma_path = malloc(100);
			char* delta_path = malloc(100);

			strcpy(gamma_path,filepath);
			strcat(gamma_path,".gamma");

			strcpy(delta_path,filepath);
			strcat(delta_path,".delta");

			FILE* fgamma = fopen(gamma_path,"w");
			FILE* fdelta = fopen(delta_path,"w");



			mpz_out_str(fgamma,16,gamma);
			mpz_out_str(fdelta,16,delta);


		printf("Saved output to %s and %s\n\n",gamma_path, delta_path);
		
			free(filepath);	
			free(buffer);	
			free(gamma_path);	
			free(delta_path);	

			fclose(fgamma);
			fclose(fdelta);
			fclose(file);
	}

	// Αποκρυπτογράφηση
	if (decryption){
		FILE* fgamma = fopen(argv[2],"r");
		FILE* fdelta = fopen(argv[3],"r");

			if (fgamma==NULL){
				printf("Error: File %s does not exist\n",argv[2]);
				return -1;
		}
			if (fdelta==NULL){
				printf("Error: File %s does not exist\n",argv[3]);
				return -1;
		}

		FILE* fdecrypted = fopen("decrypted.txt","w");

		mpz_inp_str(gamma,fgamma,16);
		mpz_inp_str(delta,fdelta,16);


		elgamal_decrypt(m,gamma,delta,d,p);

		char* msg = calloc(1,1);
		mpz2str(&msg,m);

		while (*msg){
			fputc(*msg, fdecrypted);
			*msg++;
	}

		printf("Saved output to decrypted.txt\n\n");
		fclose(fgamma);
		fclose(fdelta);
		fclose(fdecrypted);

	}
	
		printf("m=");mpz_out_str(stdout,16,p);printf("\n");
		printf("p=");mpz_out_str(stdout,16,p);printf("\n");
		printf("a=");mpz_out_str(stdout,16,a);printf("\n");
		printf("ad=");mpz_out_str(stdout,16,ad);printf("\n");
		printf("d=");mpz_out_str(stdout,16,d);printf("\n");
		printf("gamma=");mpz_out_str(stdout,16,gamma);printf("\n");
		printf("delta=");mpz_out_str(stdout,16,delta);printf("\n");

	mpz_clear(m);
	mpz_clear(p);
	mpz_clear(a);
	mpz_clear(d);
	mpz_clear(ad);
	mpz_clear(gamma);
	mpz_clear(delta);

    return 0;
}

