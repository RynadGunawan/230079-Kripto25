"""
Nama    : Rynad Arkansyah Gunawan
NPM     : 140810230079
Program : Steganografi - Metode M-bit LSB
"""

from PIL import Image
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

# ubah m-bit LSB dari sebuah nilai pixel
def modify_bits(pixel_value, data_bits):
    m = len(data_bits)
    clear_mask = (255 << m) & 255
    cleared_pixel = pixel_value & clear_mask
    data_int = int(data_bits, 2)
    return cleared_pixel | data_int

# ekstraksi m-bit LSB dari sebuah nilai pixel
def extract_bits(pixel_value, m):
    extract_mask = (1 << m) - 1
    extracted_data = pixel_value & extract_mask
    return format(extracted_data, f'0{m}b')

# encode (enkripsi pesan)
def encode(file_name, data, file_output, m_bits):
    pixels, width, height, img = getImg(file_name)
    if not img: return

    if isinstance(data, str):
        data += "_#END#_"
        binary_data = ''.join([format(ord(char), '08b') for char in data])
    else:
        binary_data = ''.join([format(byte, '08b') for byte in data])

    data_len = len(binary_data)
    max_capacity = width * height * 3 * m_bits
    if data_len > max_capacity:
        print("Error! Ukuran data terlalu besar.")
        print(f"- Kapasitas gambar: {max_capacity // 8} bytes")
        print(f"- Ukuran data: {data_len // 8} bytes")
        return
        
    coordinate = [(x, y) for y in range(height) for x in range(width)]
    data_index = 0
    for x, y in coordinate:
        if data_index >= data_len: break
        pixel = list(pixels[x, y])
        for i in range(3):
            if data_index >= data_len: break
            bits_to_hide = binary_data[data_index : data_index + m_bits]
            actual_m = len(bits_to_hide)
            if actual_m < m_bits:
                bits_to_hide = bits_to_hide.ljust(m_bits, '0')

            pixel[i] = modify_bits(pixel[i], bits_to_hide)
            data_index += actual_m
        pixels[x, y] = tuple(pixel)

    img.save(file_output)
    print(f"Sukses! Data telah disembunyikan di '{file_output}'.\n")

# decode (dekripsi pesan)
def decode(file_name, is_text, m_bits):
    pixels, width, height, img = getImg(file_name)
    if not img: return None

    coordinate = [(x, y) for y in range(height) for x in range(width)]
    binary_data = ""
    delimiter_bin = ''.join(format(ord(c), '08b') for c in "_#END#_")

    for x, y in coordinate:
        pixel = pixels[x, y]
        for color_val in pixel[:3]:
            binary_data += extract_bits(color_val, m_bits)
            if is_text and delimiter_bin in binary_data:
                final_data_bin = binary_data.split(delimiter_bin)[0]
                chars = [chr(int(final_data_bin[i:i+8], 2)) for i in range(0, len(final_data_bin), 8) if len(final_data_bin[i:i+8]) == 8]
                return "".join(chars)

    bytes_list = [int(binary_data[i:i+8], 2) for i in range(0, len(binary_data), 8) if len(binary_data[i:i+8]) == 8]
    return bytes(bytes_list)

# menu dan pilihan user
def get_m_bits():
    while True:
        try:
            m = int(input("Masukkan jumlah bit yang ingin digunakan (1-8): "))
            if 1 <= m <= 8: return m
            else: print("Masukkan angka antara 1 dan 8.")
        except ValueError:
            print("Masukkan angka yang valid.")

def menuEncode():
    print("\nEmbedding file (encoder)")
    cover_img = input("Nama cover-object: ")
    m_bits = get_m_bits()
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
    encode(cover_img, data_to_hide, output_img, m_bits)

def menuDecode():
    print("\nEkstrasi file (decoder)")
    stego_img = input("Nama stego-object: ")
    m_bits = get_m_bits()
    file_type = input("Jenis file (1: Teks, 2: File Gambar): ")
    is_text = (file_type == '1')
    
    extracted_data = decode(stego_img, is_text, m_bits)
    
    if extracted_data is not None:
        if is_text:
            print(f"Ekstrasi secret message : {extracted_data}\n")
        else:
            output_file = input("Simpan file ekstrasi sebagai: ")
            with open(output_file, 'wb') as f: f.write(extracted_data)
            print(f"Sukses! File ekstrasi sebagai '{output_file}'.\n")

def menu():
    while True:
        print("Program Steganografi Metode M-bit LSB")
        print("1. Embedding pesan (encoder)")
        print("2. Ekstrasi pesan (decoder)")
        print("3. Keluar dari program")
        choice = input("Pilih Opsi (1-3): ")

        if choice == '1': menuEncode()
        elif choice == '2': menuDecode()
        elif choice == '3': print("Mengakhiri program..."); break
        else: print("[!] Pilihan invalid!")

if __name__ == '__main__':
    menu()