/*
Nama    : Rynad Arkansyah Gunawan
NPM     : 140810230079
Program : Vigenere Cipher
*/

#include <iostream>
using namespace std;

const int MOD = 26;

// ubah huruf ke angka
int charToInt(char c) {
    return toupper(c) - 'A';
}

// ubah angka ke huruf
char intToChar(int x) {
    return (x % MOD) + 'A';
}

// enkripsi Vigenere
string encrypt(string plaintext, string key) {
    string ct = "";
    int keyLength = key.size();
    for (int i = 0; i < plaintext.size(); i++) {
        int p = charToInt(plaintext[i]);
        int k = charToInt(key[i % keyLength]);
        ct += intToChar((p + k) % MOD);
    }
    return ct;
}

// dekripsi Vigenere
string decrypt(string ciphertext, string key) {
    string pt = "";
    int keyLength = key.size();
    for (int i = 0; i < ciphertext.size(); i++) {
        int c = charToInt(ciphertext[i]);
        int k = charToInt(key[i % keyLength]);
        pt += intToChar((c - k + MOD) % MOD);
    }
    return pt;
}

int main() {
    int choice;
    string text, key;

    do {
        cout << "Vigenere Cipher\n";
        cout << "1. Enkripsi\n";
        cout << "2. Dekripsi\n";
        cout << "0. Keluar\n";
        cout << "Pilih: ";
        cin >> choice;

        if (choice == 1) {
            cout << "\nMasukkan plaintext: ";
            cin >> text;
            cout << "Masukkan kunci: ";
            cin >> key;

            string ct = encrypt(text, key);
            cout << "\nCiphertext: " << ct << "\n\n";

        } else if (choice == 2) {
            cout << "\nMasukkan ciphertext: ";
            cin >> text;
            cout << "Masukkan kunci: ";
            cin >> key;

            string pt = decrypt(text, key);
            cout << "\nPlaintext: " << pt << "\n\n";
        }

    } while (choice != 0);

    cout << "Mengakhiri program...\n";
    return 0;
}