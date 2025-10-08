# Program Steganografi

## Identitas
- **Nama**: Rynad Arkansyah Gunawan  
- **NPM**: 140810230079  
- **Program**: Steganografi dengan Metode Sequential, Acak, dan M-bit LSB  

---

## Deskripsi
Program ini merupakan implementasi dari **algoritma Steganografi berbasis LSB (Least Significant Bit)** menggunakan bahasa **Python**.  
Terdapat tiga metode utama yang diimplementasikan:

1. **Metode Sequential LSB**  
   Data disisipkan secara **berurutan** pada setiap bit paling rendah (LSB) dari pixel gambar pembawa.  

2. **Metode Acak LSB**  
   Data disisipkan secara **acak** berdasarkan *password* tertentu, sehingga posisi pixel yang digunakan tidak berurutan dan lebih aman.  

3. **Metode M-bit LSB**  
   Setiap channel warna (R, G, B) akan diganti sebanyak **M bit terbawah** dengan bit data rahasia, sehingga kapasitas penyisipan dapat diatur sesuai kebutuhan.

---

## Fitur Program
1. **Embedding (Encode)**  
   Menyembunyikan pesan teks atau file gambar ke dalam gambar lain (cover-object).

2. **Ekstraksi (Decode)**  
   Mengambil kembali pesan rahasia dari gambar yang telah disisipi.

3. **Interaktif (Menu Terminal)**  
   Program berjalan melalui menu interaktif berbasis terminal, sehingga mudah digunakan tanpa memerlukan antarmuka grafis.

---

## Alur Program

### 1. Menu Utama  
Saat dijalankan, program menampilkan menu:
- `1` → Embedding pesan (encoder)  
- `2` → Ekstraksi pesan (decoder)  
- `3` → Keluar dari program  

### 2. Embedding (Encode)  
Langkah-langkah:
- Masukkan nama file gambar pembawa (*cover-object*).  
- Pilih jenis data yang akan disembunyikan:  
  - `1` → Teks rahasia  
  - `2` → File gambar  
- Jika menggunakan **Metode Acak LSB**, pengguna akan diminta memasukkan **password pengacakan**.  
- Jika menggunakan **Metode M-bit LSB**, pengguna akan diminta menentukan jumlah bit `m` (1–8).  
- Masukkan nama file output (hasil gambar dengan pesan tersembunyi).  
- Program menyembunyikan data ke dalam gambar dan menampilkan pesan sukses.

### 3. Ekstraksi (Decode)  
Langkah-langkah:
- Masukkan nama file gambar yang berisi data tersembunyi (*stego-object*).  
- Pilih tipe data yang ingin diekstrak:  
  - `1` → Teks  
  - `2` → File Gambar  
- Jika metode **Acak** digunakan, masukkan password yang sama seperti saat encode.  
- Jika metode **M-bit** digunakan, masukkan jumlah bit yang sama dengan proses encode.  
- Hasil teks akan langsung ditampilkan di terminal, sedangkan file gambar disimpan ke file baru.

### 4. Keluar  
- Pilih `3` untuk mengakhiri program.  
- Program akan menampilkan pesan: `Mengakhiri program...`
---

## Cara Menjalankan Program
Pastikan Python dan library `Pillow` sudah terinstal.

### 1. Jalankan Metode Sequential
```bash
python sequential.py
```
### 2. Jalankan Metode Acak
```bash
python acak.py
```
### 1. Jalankan Metode M-Bit
```bash
python m-bit.py
```
---

# Screenshoot Running Program

## Metode Sequential LSB
### Embedding Teks
![Embedding Teks "Steganografi"](<embeddingTeksSequential.png>)
### Ekstrasi Teks
![Ekstrasi Teks "Steganografi"](<ekstrasiTeksSequential.png>)
### Embedding File Gambar
![Embedding File Gambar 'secret-picture.png'](<embeddingGambarSequential.png>)
### Ekstrasi File Gambar
![Ekstrasi File Gambar 'secret-picture.png'](<ekstrasiGambarSequential.png>)
### Keluar Program
![Keluar Program](<keluarProgramSequential.png>)

## Metode Acak LSB
### Embedding Teks
![Embedding Teks "Steganografi"](<embeddingTeksAcak.png>)
### Ekstrasi Teks
![Ekstrasi Teks "Steganografi"](<ekstrasiTeksAcak.png>)
### Embedding File Gambar
![Embedding File Gambar 'secret-picture.png'](<embeddingGambarAcak.png>)
### Ekstrasi File Gambar
![Ekstrasi File Gambar 'secret-picture.png'](<ekstrasiGambarAcak.png>)
### Keluar Program
![Keluar Program](<keluarProgramAcak.png>)

## Metode M-Bit LSB
### Embedding Teks
![Embedding Teks "Steganografi"](<embeddingTeksM-Bit.png>)
### Ekstrasi Teks
![Ekstrasi Teks "Steganografi"](<ekstrasiTeksM-Bit.png>)
### Embedding File Gambar
![Embedding File Gambar 'secret-picture.png'](<embeddingGambarM-Bit.png>)
### Ekstrasi File Gambar
![Ekstrasi File Gambar 'secret-picture.png'](<ekstrasiGambarM-Bit.png>)
### Keluar Program
![Keluar Program](<keluarProgramM-Bit.png>)

---

# Contoh Cover-Object, Embedded-Object, Stego-Object, dan Hasil Ekstrasi Stego-Object

## Cover-Object
!['picture.png'](<picture.png>)

## Embedded-Object
!['secret-picture.png'](<secret-picture.png>)

## Stego-Object (Metode Sequential LSB)
!['hasilPictureSequential.png'](<pictureSequential.png>)

## Stego-Object (Metode Acak LSB)
!['hasilPictureAcak.png'](<pictureAcak.png>)

## Stego-Object (Metode M-Bit LSB)
!['hasilPictureM-Bit.png'](<pictureM-Bit.png>)

## Hasil Ekstrasi Stego-Object (Metode Sequential LSB)
!['hasilPictureSequential.png'](<hasilPictureSequential.png>)

## Hasil Ekstrasi Stego-Object (Metode Acak LSB)
!['hasilPictureAcak.png'](<hasilPictureAcak.png>)

## Hasil Ekstrasi Stego-Object (Metode M-Bit LSB)
!['hasilPictureM-Bit.png'](<hasilPictureM-Bit.png>)