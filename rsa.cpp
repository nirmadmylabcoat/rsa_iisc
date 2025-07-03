#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

long long modexp(long long base, long long exp, long long mod) {
    long long result = 1;
    base = base % mod;

    while (exp > 0) {
        if (exp % 2 == 1)
            result = (result * base) % mod;

        exp = exp >> 1;
        base = (base * base) % mod;
    }
    return result;
}

long long gcd(long long a, long long b) {
    return b == 0 ? a : gcd(b, a % b);
}

long long chooseE(long long phi) {
    long long e = 3;
    while (gcd(e, phi) != 1)
        e += 2;
    return e;
}

// eea
long long modInverse(long long a, long long m) {
    long long m0 = m, x0 = 0, x1 = 1;
    while (a > 1) {
        long long q = a / m;
        long long t = m;

        m = a % m;
        a = t;

        t = x0;
        x0 = x1 - q * x0;
        x1 = t;
    }

    return x1 < 0 ? x1 + m0 : x1;
}

// random even int k
long long randomEven(long long n) {
    long long k;
    do {
        k = rand() % n;
    } while (k % 2 != 0 || k == 0);
    return k;
}

int main() {
    srand(time(0));
    long long p = 37;
    long long q = 53;
    cout << "p: " << p << "\nq: " << q << endl;
    long long n = p * q;
    long long phi = (p - 1) * (q - 1);

    long long e = chooseE(phi);
    long long d = modInverse(e, phi);
    cout << "Public Key (e, n): (" << e << ", " << n << ")\n";
    cout << "Private Key (d, n): (" << d << ", " << n << ")\n";
    long long m = rand() % 2;
    cout << "Original message (m): " << m << "\n";
    long long k = randomEven(n);
    cout << "Random even k: " << k << "\n";

    // Step 6: Encryption: (m + k)^e mod n
    long long c = modexp(m + k, e, n);
    cout << "Ciphertext: " << c << "\n";

    // Step 7: Decryption: c^d mod n
    long long decrypted = modexp(c, d, n);
    cout << "Decrypted value (m + k): " << decrypted << "\n";

    // Step 8: Recover m from parity
    long long recovered_m = decrypted % 2;
    cout << "Recovered message bit (m): " << recovered_m << "\n";

    return 0;
}
