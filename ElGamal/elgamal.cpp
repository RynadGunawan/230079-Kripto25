/*
Nama    : Rynad Arkansyah Gunawan
NPM     : 140810230079
Program : El Gamal
*/

#include <iostream>
using namespace std;

// perpangkatan modulo
long long modExp(long long base, long long exp, long long mod) {
    long long result = 1;
    base %= mod;
    while (exp > 0) {
        if (exp & 1) result = (result * base) % mod;
        exp >>= 1;
        base = (base * base) % mod;
    }
    return result;
}

// cari invers modulo (extended euclidean)
long long modInv(long long a, long long m) {
    long long m0 = m, x0 = 0, x1 = 1;
    if (m == 1) return 0;
    while (a > 1) {
        long long q = a / m;
        long long t = m;
        m = a % m, a = t;
        t = x0;
        x0 = x1 - q * x0;
        x1 = t;
    }
    if (x1 < 0) x1 += m0;
    return x1;
}

// enkripsi (M -> (C1,C2))
void encrypt(int M[], int n, long long p, long long g, long long y, long long k, long long C1[], long long C2[]) {
    long long s = modExp(y, k, p);
    long long c1 = modExp(g, k, p);
    for (int i=0; i<n; i++) {
        C1[i] = c1;
        C2[i] = (M[i] * s) % p;
    }
}

// dekripsi (C1,C2 -> M)
void decrypt(long long C1[], long long C2[], int n, long long p, long long x, int M[]) {
    for (int i=0; i<n; i++) {
        long long c1x = modExp(C1[i], x, p);
        long long inv = modInv(c1x, p);
        M[i] = (C2[i] * inv) % p;
    }
}

// ubah huruf jadi angka
int charToInt(char c) {
    if (c >= 'A' && c <= 'Z') {
        return c - 'A';
    } else if (c >= 'a' && c <= 'z') {
        return c - 'a';  // input huruf kecil
    }
    return 0; 
}

// ubah angka jadi huruf
char intToChar(int n) {
    return char((n % 26) + 'A');
}

int main() {
    int choice;
    const int N = 100;
    int M[N];            
    long long C1[N], C2[N];
    int n;              
    
    long long p, g, x, k;

    do {
        cout << "El Gamal\n";
        cout << "1. Enkripsi\n";
        cout << "2. Dekripsi\n";
        cout << "0. Keluar\n";
        cout << "Pilih: ";
        cin >> choice;

        if (choice == 1) {
            cout << "\nMasukkan p: "; cin >> p;
            cout << "Masukkan g: "; cin >> g;
            cout << "Masukkan x: "; cin >> x;
            cout << "Masukkan k: "; cin >> k;

            long long y = modExp(g, x, p);

            string plaintext;
            cout << "\nMasukkan plaintext (huruf): ";
            cin >> plaintext;
            n = plaintext.size();

            cout << "\nKonversi huruf ke angka:\n";
            for (int i=0; i<n; i++) {
                M[i] = charToInt(plaintext[i]);
                cout << plaintext[i] << " = " << M[i] << "\n";
            }

            encrypt(M, n, p, g, y, k, C1, C2);

            cout << "\nHasil Ciphertext (C1,C2):\n";
            for (int i=0; i<n; i++) {
                cout << "(" << C1[i] << "," << C2[i] << ") ";
            }
            cout << "\n\n";

        } else if (choice == 2) {
            cout << "\nMasukkan p: "; cin >> p;
            cout << "Masukkan g: "; cin >> g;
            cout << "Masukkan x: "; cin >> x;

            cout << "\nMasukkan jumlah huruf: ";
            cin >> n;
            cout << "Masukkan ciphertext (C1 dan C2):\n";
            for (int i=0; i<n; i++) cin >> C1[i] >> C2[i];

            decrypt(C1, C2, n, p, x, M);

            cout << "\nHasil Plaintext:\n";
            for (int i=0; i<n; i++) {
                cout << M[i] << " = " << intToChar(M[i]) << "\n";
            }

            cout << "\nPlaintext (huruf): ";
            for (int i=0; i<n; i++) cout << intToChar(M[i]);
            cout << "\n\n";
        }

    } while (choice != 0);

    cout << "Mengakhiri program...\n";
    return 0;
}