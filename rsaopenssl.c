#include <stdio.h>
#include <openssl/bn.h>
#include <openssl/rsa.h>
#include <openssl/err.h>
#include <time.h>
#include <stdlib.h>

int main() {
    BN_CTX *ctx = BN_CTX_new();

    // BIGNUM variables
    BIGNUM *p = BN_new(), *q = BN_new(), *n = BN_new();
    BIGNUM *phi = BN_new(), *e = BN_new(), *d = BN_new();
    BIGNUM *p_minus1 = BN_new(), *q_minus1 = BN_new();
    BIGNUM *k = BN_new(), *m = BN_new(), *m_plus_k = BN_new();
    BIGNUM *c = BN_new(), *decrypted = BN_new();
    BIGNUM *recovered_m = BN_new(), *two = BN_new(), *num = BN_new();

    // Generate large random primes p and q (e.g., 64 bits)
    BN_generate_prime_ex(p, 64, 1, NULL, NULL, NULL);
    BN_generate_prime_ex(q, 64, 1, NULL, NULL, NULL);

    // n = p * q
    BN_mul(n, p, q, ctx);

    // phi = (p-1)(q-1)
    BN_sub(p_minus1, p, BN_value_one());
    BN_sub(q_minus1, q, BN_value_one());
    BN_mul(phi, p_minus1, q_minus1, ctx);

    // Choose public exponent e = 3 or 65537 commonly
    BN_set_word(e, 65537);
    BIGNUM *gcd = BN_new();
    BN_gcd(gcd, e, phi, ctx);
    if (!BN_is_one(gcd)) {
        // fallback to smaller prime if 65537 isn't coprime
        BN_set_word(e, 3);
        while (1) {
            BN_gcd(gcd, e, phi, ctx);
            if (BN_is_one(gcd)) break;
            BN_add(e, e, BN_value_one());
        }
    }
    BN_free(gcd);

    // d = e^-1 mod phi
    BN_mod_inverse(d, e, phi, ctx);

    // m = 0
    BN_set_word(num,2);
    BN_rand_range(m,num);

    // Random even k < n
    srand(time(0));
    while (1) {
        BN_rand_range(k, n);
        if (!BN_is_zero(k) && BN_is_odd(k) == 0) break;
    }

    // m + k
    BN_add(m_plus_k, m, k);

    // Encrypt: c = (m + k)^e mod n
    BN_mod_exp(c, m_plus_k, e, n, ctx);

    // Decrypt: (c)^d mod n
    BN_mod_exp(decrypted, c, d, n, ctx);

    // Recovered message bit: decrypted % 2
    BN_set_word(two, 2);
    BN_mod(recovered_m, decrypted, two, ctx);

    // Output everything
    printf("Generated p: "); BN_print_fp(stdout, p); printf("\n");
    printf("Generated q: "); BN_print_fp(stdout, q); printf("\n");
    printf("n = p * q: "); BN_print_fp(stdout, n); printf("\n");
    printf("phi(n): "); BN_print_fp(stdout, phi); printf("\n");
    printf("Public exponent (e): "); BN_print_fp(stdout, e); printf("\n");
    printf("Private exponent (d): "); BN_print_fp(stdout, d); printf("\n");
    printf("Message (m): "); BN_print_fp(stdout, m); printf("\n");
    printf("Random even k: "); BN_print_fp(stdout, k); printf("\n");
    printf("Ciphertext: "); BN_print_fp(stdout, c); printf("\n");
    printf("Decrypted (m + k): "); BN_print_fp(stdout, decrypted); printf("\n");
    printf("Recovered bit m = (m + k) mod 2: "); BN_print_fp(stdout, recovered_m); printf("\n");

    // Cleanup
    BN_free(p); BN_free(q); BN_free(n); BN_free(phi); BN_free(e); BN_free(d);
    BN_free(p_minus1); BN_free(q_minus1); BN_free(k); BN_free(m);
    BN_free(m_plus_k); BN_free(c); BN_free(decrypted); BN_free(recovered_m); BN_free(two);
    BN_CTX_free(ctx);

    return 0;
}

# 🔐 RSA Encryption in C using OpenSSL

This repository contains a compact RSA implementation in C using the **OpenSSL BIGNUM library**. It demonstrates how to:

- Generate RSA keys with large random primes
- Perform encryption of a masked single-bit message using exponentiation
- Decrypt and recover the original bit using parity

This is a practical extension of textbook RSA using real cryptographic libraries.

---

## 📄 File: `rsaopenssl.c`

### 🧠 What It Demonstrates

- RSA key generation using `BN_generate_prime_ex`
- Modular arithmetic via OpenSSL's `BIGNUM` API
- Random bit message + random even masking
- RSA encryption:  
  \[
  c = (m + k)^e \mod n
  \]
- Decryption and message recovery via:  
  \[
  m = (c^d \mod n) \mod 2
  \]

---


---

## ⚙️ How to Build and Run

### 🧰 Requirements

- OpenSSL development libraries (libssl-dev)
- GCC or Clang

### 🛠️ Build

```bash
gcc rsaopenssl.c -o rsaopenssl -lcrypto

