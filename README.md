# 🔐 RSA Encryption Demo in C++

This repository contains a simple and illustrative implementation of **RSA public-key encryption** in C++. It demonstrates key generation, encryption, decryption, and message recovery using modular arithmetic — designed to help understand how RSA works in practice.

---

## 📦 Files

- `rsa.cpp`: Full RSA implementation with a demonstration of secure encryption using `(m + k)^e mod n` and parity-based decryption.
- (Optional Context) Sample AVP-related notes in comments: The Additive Veto Protocol is referenced as a potential use-case for integrating RSA for secure vote handling.

---

## 🧠 How It Works

This implementation simulates the following RSA operations:

1. **Key Generation**
   - Chooses two small primes `p` and `q`
   - Computes `n = p * q` and `φ(n) = (p - 1)(q - 1)`
   - Chooses public exponent `e` such that `gcd(e, φ) = 1`
   - Computes private key `d` as the modular inverse of `e mod φ(n)`

2. **Message Encryption**
   - A random even number `k` is added to the original message bit `m ∈ {0,1}`
   - Ciphertext is computed as:  
     \[
     c = (m + k)^e \mod n
     \]

3. **Message Decryption**
   - Decrypted value:  
     \[
     (m + k)^d \mod n
     \]
   - The original bit `m` is recovered using parity: `decrypted % 2`

---
