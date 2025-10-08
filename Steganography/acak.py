"""
Nama    : Rynad Arkansyah Gunawan
NPM     : 140810230079
Program : Steganografi Metode Acak LSB
"""

from PIL import Image
import random
import os

# membuka gambar dan ekstrak pixel map
def getImg(file_name):
    try:
        img = Image.open(file_name, 'r')
        width, height = img.size
        return img.load(), width, height, img
    except (FileNotFoundError, IOError):
        print(f"Error! File gambar tidak ditemukan di '{file_name}'.")
        return None, None, None, None

def modify_bit(pixel_value, data_bit):
    return (pixel_value & 254) | int(data_bit)

def extract_bit(pixel_value):
    return str(pixel_value & 1)

# encode (enkripsi pesan)
def encode(file_name, data, file_output, password):
    pixels, width, height, img = getImg(file_name)
    if not img: return

    if not password:
        print("Error! Metode acak memerlukan password.")
        return

    if isinstance(data, str):
        data += "_#END#_" 
        binary_data = ''.join([format(ord(char), '08b') for char in data])
    else:
        binary_data = ''.join([format(byte, '08b') for byte in data])

    data_length = len(binary_data)
    max_capacity = width * height * 3
    if data_length > max_capacity:
        print("Error! Ukuran data terlalu besar.")
        return

    # buat daftar koordinat dan acak berdasarkan password
    coordinate = [(x, y) for x in range(width) for y in range(height)]
    random.seed(password)
    random.shuffle(coordinate)

    data_index = 0
    for x, y in coordinate:
        if data_index >= data_length: break
        pixel = list(pixels[x, y])
        for i in range(3):
            if data_index >= data_length: break
            pixel[i] = modify_bit(pixel[i], binary_data[data_index])
            data_index += 1
        pixels[x, y] = tuple(pixel)

    img.save(file_output)
    print(f"Sukses! Data telah disembunyikan di '{file_output}'.\n")

# decode (dekripsi pesan)
def decode(file_name, is_text, password):
    pixels, width, height, img = getImg(file_name)
    if not img: return None
    if not password:
        print("Error! Metode acak memerlukan password.")
        return None

    # hasilkan urutan acak yang sama dengan menggunakan password yang sama
    coordinate = [(x, y) for x in range(width) for y in range(height)]
    random.seed(password)
    random.shuffle(coordinate)

    binary_data = ""
    delimiter_bin = ''.join(format(ord(c), '08b') for c in "_#END#_")

    for x, y in coordinate:
        pixel = pixels[x, y]
        for color_val in pixel[:3]:
            binary_data += extract_bit(color_val)
            if is_text and delimiter_bin in binary_data:
                final_data_bin = binary_data.split(delimiter_bin)[0]
                chars = [chr(int(final_data_bin[i:i+8], 2)) for i in range(0, len(final_data_bin), 8) if len(final_data_bin[i:i+8]) == 8]
                return "".join(chars)

    bytes_list = [int(binary_data[i:i+8], 2) for i in range(0, len(binary_data), 8) if len(binary_data[i:i+8]) == 8]
    return bytes(bytes_list)

# menu dan pilihan user
def menuEncode():
    print("\nEmbedding file (encoder)")
    cover_img = input("Nama cover-object: ")
    password = input("Password pengacakan: ")
    file_type = input("Jenis file (1: Teks, 2: File Gambar): ")
    data_to_hide = None

    if file_type == '1':
        data_to_hide = input("Secret message: ")
    elif file_type == '2':
        secret_file = input("Secret file: ")
        try:
            with open(secret_file, 'rb') as f: data_to_hide = f.read()
        except FileNotFoundError:
            print(f"File '{secret_file}' tidak ditemukan."); return
    else:
        print("Pilihan invalid!"); return

    output_img = input("Nama file output: ")
    encode(cover_img, data_to_hide, output_img, password)

def menuDecode():
    print("\nEkstrasi file (decoder)")
    stego_img = input("Nama stego-object: ")
    password = input("Password ekstraksi: ")
    file_type = input("Jenis file (1: Teks, 2: File Gambar): ")
    is_text = (file_type == '1')
    
    extracted_data = decode(stego_img, is_text, password)
    
    if extracted_data is not None:
        if is_text:
            print(f"Ekstrasi secret message : {extracted_data}\n")
        else:
            output_file = input("Simpan file ekstrasi sebagai: ")
            with open(output_file, 'wb') as f: f.write(extracted_data)
            print(f"Sukses! File ekstrasi sebagai '{output_file}'.\n")

def menu():
    while True:
        print("Program Steganografi Metode Acak LSB")
        print("1. Embedding pesan (encoder)")
        print("2. Ekstrasi pesan (decoder)")
        print("3. Keluar dari program")
        choice = input("Pilih Opsi (1-3): ")

        if choice == '1': menuEncode()
        elif choice == '2': menuDecode()
        elif choice == '3': print("Mengakhiri program...");break
        else: print("[!] Pilihan invalid!")

if __name__ == '__main__':
    menu()