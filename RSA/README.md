# 🔐 RSA Encryption & Decryption in C

This project implements a simplified RSA algorithm in C for encrypting and decrypting numeric messages.

---

## 📦 Description

The program accepts the following parameters:

- `e` — Public exponent
- `d` — Private exponent
- `p` and `q` — Prime numbers used to compute the modulus
- `message` — Numeric input read from standard input

## ⚙️ Compilation

Using `gcc`:

```bash
gcc rsa.c -o rsa
```

## ▶️ Usage
```bash
./rsa enc|dec <e> <d> <p> <q>
Use enc to encrypt a message
Use dec to decrypt a message
The program reads the message from stdin after execution starts
```
## 🔍 Example
```bash
./rsa enc 7 103 17 11
> 42
Encrypted: 2

```bash
./rsa dec 7 103 17 11
> 2
Decrypted: 42
```
## 🧠 What It Does
```bash
Calculates N = p * q

Computes Euler’s Totient φ(N)

Validates that e is coprime with φ(N)

Ensures that d is the modular inverse of e mod φ(N)

Performs modular exponentiation for both encryption and decryption
```
## ⚠️ Limitations
```bash
The message must be a non-negative number less than N

Only supports numeric messages (no strings or files)

Does not implement padding or large-key cryptographic security

All RSA parameters (e, d, p, q) must be user-provided
```