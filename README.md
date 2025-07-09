# 🔐 RSA Encryption Demos

This repository contains two implementations of basic RSA encryption:

- 🧾 `rsa.cpp` – Educational RSA in plain C++
- 🧾 `rsaopenssl.c` – Practical RSA using OpenSSL's BIGNUM library

Each encrypts a single-bit message masked with a random even number, demonstrating how RSA can be securely adapted to prevent brute-force attacks.

---

## 📘 What is RSA?

RSA is a widely used public-key encryption algorithm based on the difficulty of factoring large integers. It enables secure key exchange, digital signatures, and data encryption.

In this project, we use a masked encryption strategy:
\[
c = (m + k)^e \mod n
\]
where `m ∈ {0,1}` and `k` is a random even number.

---

## 🧩 Files

- `rsa.cpp` – Pure C++ RSA demo with small primes
- `rsaopenssl.c` – RSA with OpenSSL's `BIGNUM` for strong cryptographic support

---

## 🔐 Security Note

Masking the message bit `m` with a random even `k` (i.e., encrypting `m + k`) ensures:

- 🔒 **Brute-force safe** – The ciphertext reveals no structure about `m` or `k`.
- 🔒 **No precomputation attacks** – `k` randomizes `m`, avoiding known-plaintext attacks.
- 🔐 Only the private key can recover `m` by computing `(c^d mod n) % 2`.

---

## ⚙️ Build & Run Instructions

### 📌 Prerequisites

- For `rsa.cpp`: A C++ compiler (e.g., `g++`)
- For `rsaopenssl.c`: OpenSSL development libraries (e.g., `libssl-dev`)

---

### 🛠️ Compile

```bash
# Compile rsa.cpp
g++ rsa.cpp -o rsa_demo

# Compile rsaopenssl.c with OpenSSL
gcc rsaopenssl.c -o rsa_openssl -lcrypto
