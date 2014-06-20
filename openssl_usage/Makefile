CC=g++
CFLAGS=-Wall -g -O2
LIBS=-lcrypto

all: rsa dsa md_with_evp rsa_pem

rsa: rsa.cpp
	$(CC) $(CFLAGS) $^ -o $@ $(LIBS)

dsa: dsa.cpp
	$(CC) $(CFLAGS) $^ -o $@ $(LIBS)

md_with_evp: md_with_evp.cpp
	$(CC) $(CFLAGS) $^ -o $@ $(LIBS)

rsa_pem: rsa_pem.cpp
	$(CC) $(CFLAGS) $^ -o $@ $(LIBS)

clean:
	@rm -f rsa
	@rm -f dsa
	@rm -f md_with_evp
	@rm -f rsa_pem
