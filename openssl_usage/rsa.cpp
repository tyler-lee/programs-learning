/*
 * rsa.cpp
 * -- Show the usage of RSA encryption and decryption with openssl
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <openssl/rsa.h>
#include <openssl/bn.h>

int main(int argc, char** argv) {
	RSA* rsa;
	unsigned char* input_string;
	unsigned char* encrypt_string;
	unsigned char* decrypt_string;
	int bit_number = 1024;

	// check arguments
	if(2 != argc) {
		fprintf(stderr, "%s <plain text>\n", argv[0]);
		exit(-1);
	}

	// set the input string
	input_string = (unsigned char*)calloc(strlen(argv[1])+1, sizeof(unsigned char));
	if(NULL == input_string) {
		fprintf(stderr,"Allocate memory for input_string error\n");
		exit(-1);
	}
	strncpy((char*)input_string, argv[1], strlen(argv[1]));

	// generate RSA parameters with bit_number bits and e = 65537
	unsigned long e = 65537;
	rsa = RSA_generate_key(bit_number, e, NULL, NULL);

	// allocate memory for encrypt_string
	encrypt_string = (unsigned char*)calloc(RSA_size(rsa), sizeof(unsigned char));
	if(NULL == encrypt_string) {
		fprintf(stderr,"Allocate memory for encrypt_string error\n");
		exit(-1);
	}

	// encrypt input_string, be careful that flen must be < RSA_size-41 if
	// RSA_PKCS1_OAEP_PADDING is used
	int encrypt_size = RSA_public_encrypt(strlen((char*)input_string)
			, input_string, encrypt_string, rsa, RSA_PKCS1_OAEP_PADDING);

	// allocate memory for decrypt_string
	decrypt_string = (unsigned char*)calloc(RSA_size(rsa), sizeof(unsigned char));
	if(NULL == decrypt_string) {
		fprintf(stderr,"Allocate memory for decrypt_string error\n");
		exit(-1);
	}

	// decrypt encrypt_string into decrypt_string
	int decrypt_size = RSA_private_decrypt(encrypt_size, encrypt_string, decrypt_string, rsa, RSA_PKCS1_OAEP_PADDING);

	// show string before encryption, after encryption and after decryption
	printf("input_string = %s\n", input_string);
	printf("encrypt_string = ");
	for(int i=0; i<encrypt_size; i++) {
		printf("%02x", encrypt_string[i]);
		//printf("%x%x", (encrypt_string[i] >> 4) & 0xf, encrypt_string[i] & 0xf);

	}
	printf("\n");
	printf("decrypt_string (%d) = %s\n", decrypt_size, decrypt_string);

	return 0;
}
