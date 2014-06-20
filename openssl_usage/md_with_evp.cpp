/*
 * md_with_evp.cpp
 * - show the usage of message digest function in openssl
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <openssl/evp.h>

int main(int argc, char** argv) {
	EVP_MD_CTX* ctx;
	const EVP_MD* md;
	char* input_string;
	unsigned char hash_value[EVP_MAX_MD_SIZE];
	unsigned int hash_length;
	char* digest_name = "sha1";

	// check arguments
	if(1 >= argc) {
		fprintf(stderr, "%s <input_string> [digest type]\n", argv[0]);
		exit(-1);
	}
	else if(3 == argc) {
		// set the digest name
		digest_name = (char*)calloc(strlen(argv[2])+1, sizeof(char));
		if(NULL == digest_name) {
			fprintf(stderr,"Allocate memory for digest_name error\n");
			exit(-1);
		}
		strncpy(digest_name, argv[2], strlen(argv[2]));
	}

	// set the input string
	input_string = (char*)calloc(strlen(argv[1])+1, sizeof(char));
	if(NULL == input_string) {
		fprintf(stderr,"Allocate memory for input_string error\n");
		exit(-1);
	}
	strncpy(input_string, argv[1], strlen(argv[1]));

	// load digest
	OpenSSL_add_all_digests();

	// set digest type
	md = EVP_get_digestbyname(digest_name);
	if(!md) {
		fprintf(stderr,"Unknown message digest\n");
		exit(-1);
	}

	// create and process
	ctx = EVP_MD_CTX_create();
	EVP_DigestInit_ex(ctx, md, NULL);
	EVP_DigestUpdate(ctx, input_string, strlen(input_string));
	EVP_DigestFinal_ex(ctx, hash_value, &hash_length);
	EVP_MD_CTX_destroy(ctx);

	printf("Digest is:\n");
	for(unsigned int i=0; i<hash_length; i++) {
		printf("%02x", hash_value[i]);
	}
	printf("\n");

	return 0;
}
