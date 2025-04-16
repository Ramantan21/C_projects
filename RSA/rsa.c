#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

long long gcd(long long a, long long b) {
    if (b == 0)
        return llabs(a);
    return gcd(b, a % b);
}

int is_prime(long long x) {
    if (x < 2) return 0;
    if (x == 2) return 1;
    for (long long i = 2; i * i <= x; i++) {
        if (x % i == 0)
            return 0;
    }
    return 1;
}

int co_prime(long long a, long long b) {
    return gcd(a, b) == 1;
}

long long euler(long long n) {
    long long result = n;
    for (long long p = 2; p * p <= n; p++) {
        if (n % p == 0) {
            while (n % p == 0)
                n /= p;
            result -= result / p;
        }
    }
    if (n > 1)
        result -= result / n;
    return result;
}

int is_reverse(long long a, long long b, long long phi) {
    return ((a * b) % phi) == 1;
}

long long llpower(long long a, long long b, long long modulus) {
    long long result = 1;
    a %= modulus;
    if (a == 0)
        return 0;
    while (b > 0) {
        if (b & 1)
            result = (result * a) % modulus;
        b >>= 1;
        a = (a * a) % modulus;
    }
    return result;
}

long long encrypt(long long m, long long e, long long N) {
    return llpower(m, e, N);
}

long long decrypt(long long c, long long d, long long N) {
    return llpower(c, d, N);
}

int main(int argc, char* argv[]) {
    if (argc != 6) {
        printf("Usage: ./rsa enc|dec <e> <d> <p> <q>\n");
        return 1;
    }

    if (strcmp(argv[1], "enc") != 0 && strcmp(argv[1], "dec") != 0) {
        printf("First argument must be 'enc' or 'dec'\n");
        return 1;
    }

    char *endptr[4];
    long long e = strtoll(argv[2], &endptr[0], 10);
    long long d = strtoll(argv[3], &endptr[1], 10);
    long long p = strtoll(argv[4], &endptr[2], 10);
    long long q = strtoll(argv[5], &endptr[3], 10);

    for (int i = 0; i < 4; i++) {
        if (*endptr[i] != '\0') {
            printf("All arguments must be valid numbers\n");
            return 1;
        }
    }

    if (e <= 0 || d <= 0 || p <= 0 || q <= 0) {
        printf("Negative or zero values are not allowed\n");
        return 1;
    }

    if (!is_prime(p) || !is_prime(q)) {
        printf("p and q must be prime numbers\n");
        return 1;
    }

    long long N = p * q;
    long long phi = euler(N);

    if (!co_prime(e, phi)) {
        printf("e is not coprime with phi(N)\n");
        return 1;
    }

    if (!is_reverse(e, d, phi)) {
        printf("e and d are not modular inverses (e * d mod phi(N) != 1)\n");
        return 1;
    }

    printf("Enter message (as a number): ");
    long long message;
    if (scanf("%lld", &message) != 1) {
        printf("Error reading message\n");
        return 1;
    }

    if (message < 0) {
        printf("Negative message not allowed\n");
        return 1;
    }

    if (message >= N) {
        printf("Message must be less than N = %lld\n", N);
        return 1;
    }

    if (strcmp(argv[1], "enc") == 0) {
        printf("Encrypted: %lld\n", encrypt(message, e, N));
    } else {
        printf("Decrypted: %lld\n", decrypt(message, d, N));
    }

    return 0;
}
