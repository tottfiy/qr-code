#include <stdio.h>
#include <stdlib.h>
#include <openssl/bio.h> /* BasicInput/Output streams */
#include <openssl/err.h> /* errors */
#include <openssl/ssl.h> /* core library */
#define stdin  /* implementation defined */
#define stdout /* implementation defined */
#define stderr /* implementation defined */
int bits = 4098;

void error() {
    void ERR_print_errors_fp(stderr);
    abort();
}

void keygen() {
    BIGNUM *bnum = BN_new();
    if (bnum==NULL) {
        error();
    }
    
    RSA *rsa = RSA_new();
    if (rsa==NULL) {
        error();
    }

    BN_GENCB *cb = NULL;
    int RSA_generate_key_ex(RSA *rsa, int bits, BIGNUM *bnum, BN_GENCB cb);



}