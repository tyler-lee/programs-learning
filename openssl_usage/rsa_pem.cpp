/*
 * rsa_pem.cpp
 * - read RSA key files
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/rsa.h>
#include <openssl/pem.h>

int main(int argc, char** argv) {
	FILE* fp;
	RSA* rsa;

	// check usage
	if(2 != argc) {
		fprintf(stderr, "%s <RSA private key pem file\n", argv[0]);
		exit(-1);
	}

	// open RSA private key pem file
	fp = fopen(argv[1], "r");
	if(NULL == fp) {
		fprintf(stderr, "Unable to open %s RSA private key pem file\n", argv[1]);
		exit(-1);
	}
	rsa = PEM_read_RSAPrivateKey(fp, NULL, NULL, NULL);
	if(NULL == rsa) {
		fprintf(stderr, "Unable to read private key\n");
		exit(-1);
	}
	fclose(fp);

	// show key info
	printf("Content of Private key PEM file\n");
	RSA_print_fp(stdout, rsa, 0);
	printf("\n");

	return 0;
}
