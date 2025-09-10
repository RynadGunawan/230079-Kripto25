/*
Nama    : Rynad Arkansyah Gunawan
NPM     : 140810230079
Program : Hill Cipher
*/

#include <iostream>
using namespace std;

// modulo untuk alfabet (A-Z)
const int MOD = 26;

// ubah huruf jadi angka (A=0, B=1, ... Z=25)
int charToInt(char c) {
    return toupper(c) - 'A';
}

// ubah angka jadi huruf
char intToChar(int x) {
    return (x % MOD) + 'A';
}

// hitung determinan matriks 2x2
int determinant(int m[2][2]) {
    return (m[0][0]*m[1][1] - m[0][1]*m[1][0]) % MOD;
}

// cari invers modulo (a^-1 mod m)
int modInverse(int a, int m) {
    a = (a % m + m) % m;
    for (int x = 1; x < m; x++) {
        if ((a * x) % m == 1) return x;
    }
    return -1; // tidak ada invers
}

// cari matriks invers 2x2
bool inverseMatrix(int key[2][2], int inv[2][2]) {
    int det = determinant(key);
    int inverseDeterminant = modInverse(det, MOD);
    if (inverseDeterminant == -1) return false; // gagal

    inv[0][0] = ( key[1][1] * inverseDeterminant) % MOD;
    inv[0][1] = (-key[0][1] * inverseDeterminant) % MOD;
    inv[1][0] = (-key[1][0] * inverseDeterminant) % MOD;
    inv[1][1] = ( key[0][0] * inverseDeterminant) % MOD;

    // agar semua elemen positif
    for (int i=0; i<2; i++)
        for (int j=0; j<2; j++)
            inv[i][j] = (inv[i][j] % MOD + MOD) % MOD;

    return true;
}

// enkripsi Hill Cipher
string encrypt(string plaintext, int key[2][2]) {
    if (plaintext.size() % 2 != 0) plaintext += "X"; // tambah padding
    string ciphertext = "";
    for (size_t i=0; i<plaintext.size(); i+=2) {
        int a = charToInt(plaintext[i]);
        int b = charToInt(plaintext[i+1]);
        int c1 = (key[0][0]*a + key[0][1]*b) % MOD;
        int c2 = (key[1][0]*a + key[1][1]*b) % MOD;
        ciphertext += intToChar(c1);
        ciphertext += intToChar(c2);
    }
    return ciphertext;
}

// dekripsi Hill Cipher
string decrypt(string ciphertext, int key[2][2]) {
    string plaintext = "";
    int inv[2][2];
    if (!inverseMatrix(key, inv)) return "Kunci tidak valid!";

    for (size_t i=0; i<ciphertext.size(); i+=2) {
        int a = charToInt(ciphertext[i]);
        int b = charToInt(ciphertext[i+1]);
        int p1 = (inv[0][0]*a + inv[0][1]*b) % MOD;
        int p2 = (inv[1][0]*a + inv[1][1]*b) % MOD;
        plaintext += intToChar(p1);
        plaintext += intToChar(p2);
    }
    return plaintext;
}

// mencari kunci dari plainteks & cipherteks
bool findKey(string plain, string cipher, int key[2][2]) {
    int P[2][2] = {
        {charToInt(plain[0]), charToInt(plain[2])},
        {charToInt(plain[1]), charToInt(plain[3])}
    };
    int C[2][2] = {
        {charToInt(cipher[0]), charToInt(cipher[2])},
        {charToInt(cipher[1]), charToInt(cipher[3])}
    };

    // cari determinan dan invers matriks P
    int Pinv[2][2];
    if (!inverseMatrix(P, Pinv)) {
        cout << "\nDeterminan tidak memiliki invers modulo 26.";
        return false;
    }

    // hitung K = C * P^-1
    for (int i=0; i<2; i++) {
        for (int j=0; j<2; j++) {
            key[i][j] = 0;
            for (int k=0; k<2; k++) {
                key[i][j] += C[i][k] * Pinv[k][j];
            }
            key[i][j] = (key[i][j] % MOD + MOD) % MOD;
        }
    }
    return true;
}

int main() {
    int choice;
    int key[2][2];

    do {
        cout << "Hill Cipher\n";
        cout << "1. Enkripsi\n";
        cout << "2. Dekripsi\n";
        cout << "3. Cari kunci dari plainteks & cipherteks\n";
        cout << "0. Keluar\n";
        cout << "Pilih: ";
        cin >> choice;

        if (choice == 1) {
            string plain;
            cout << "\nMasukkan plaintext:\n";
            cin >> plain;
            cout << "Masukkan kunci 2x2:\n";
            for (int i=0; i<2; i++)
                for (int j=0; j<2; j++)
                    cin >> key[i][j];

            string cipher = encrypt(plain, key);
            cout << "\nCiphertext: \n" << cipher << endl << endl;

        } else if (choice == 2) {
            string cipher;
            cout << "\nMasukkan ciphertext:\n";
            cin >> cipher;
            cout << "Masukkan kunci 2x2:\n";
            for (int i=0; i<2; i++)
                for (int j=0; j<2; j++)
                    cin >> key[i][j];

            string plain = decrypt(cipher, key);
            cout << "\nPlaintext : \n" << plain << endl << endl;

        } else if (choice == 3) {
            string P, C;
            cout << "\nMasukkan plaintext : ";
            cin >> P;
            cout << "Masukkan ciphertext: ";
            cin >> C;

            int foundKey[2][2];
            if (findKey(P, C, foundKey)) {
                cout << "\nKunci ditemukan:\n";
                for (int i=0; i<2; i++) {
                    for (int j=0; j<2; j++) {
                        cout << foundKey[i][j] << " ";
                    }
                    cout << endl;
                }
                cout << endl;
            } else {
                cout << "\nKunci tidak dapat ditemukan!\n\n";
            }
        }

    } while (choice != 0);
    cout << "Mengakhiri program...\n";
    return 0;
}