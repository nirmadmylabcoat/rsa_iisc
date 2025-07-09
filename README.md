# 🔐 RSA Encryption Demos in C++ and C (with OpenSSL)

This repository showcases two implementations of **RSA public-key cryptography**:
- One written in **standard C++**
- One using **OpenSSL's BIGNUM library in C**

Both demonstrate how RSA works at a low level — from key generation to encryption and decryption — with a focus on using random masking and parity recovery for single-bit messages.

---

## 📂 Files

- `rsa.cpp`: A pure C++ RSA implementation using native types and modular arithmetic.
- `rsaopenssl.c`: A C implementation using OpenSSL's BIGNUM API for secure big integer operations.

---

## 📖 What is RSA?

RSA is a widely used public-key encryption algorithm that relies on the difficulty of factoring large integers. It enables secure communication, digital signatures, and more. RSA involves:
- Generating a pair of keys (public and private)
- Encrypting a message using the public key
- Decrypting it using the private key

---

## 🧠 Implementation Details

### ✅ Common Idea

Both implementations encrypt a single-bit message `m ∈ {0,1}` using a **random even mask** `k`, then recover `m` via **parity** after decryption.

Encryption:
\[
c = (m + k)^e \mod n
\]

Decryption:
\[
m = (c^d \mod n) \mod 2
\]

---

## 🚀 `rsa.cpp`: C++ Native RSA Implementation

### 🔍 Description

- Uses small hardcoded primes `p = 37`, `q = 53` for simplicity.
- Modular arithmetic is done manually using 64-bit integers.
- Demonstrates RSA key generation, encryption, and decryption.
- Includes:
  - GCD calculation
  - Modular exponentiation
  - Modular inverse via Extended Euclidean Algorithm

### 🧪 Example Behavior

```bash
p: 37
q: 53
Public Key (e, n): (17, 1961)
Private Key (d, n): (113, 1961)
Original message (m): 1
Random even k: 1700
Ciphertext: 949
Decrypted value (m + k): 1701
Recovered message bit (m): 1
