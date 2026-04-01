#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <limits>

using namespace std;

// --- STRUKTUR DATA & VARIABEL GLOBAL ---
struct Riwayat {
    int nilai;
    string jenis;
    bool status;
};

vector<Riwayat> histori;
int angka;
int pilihan;

// --- UTILITY FUNGSI ---
void bersihkanLayar() {
    #if defined(_WIN32)
        system("cls");
    #else
        system("clear");
    #endif
}

// --- OPTIMASI ALGORITMA MATEMATIKA ---

// Efisiensi: Menggunakan metode 6k +/- 1. Membuang pengecekan genap dan kelipatan 3.
bool isPrima(int n) {
    if (n <= 1) return false;
    if (n <= 3) return true;
    if (n % 2 == 0 || n % 3 == 0) return false;
    
    int i = 5;
    // While loop berjalan jauh lebih cepat karena melompat 6 angka tiap iterasi
    while (i * i <= n) {
        if (n % i == 0 || n % (i + 2) == 0) return false;
        i += 6;
    }
    return true;
}

// Efisiensi: Iterasi hanya terjadi maksimal ~46 kali untuk limit integer C++
bool isFibonacci(int n) {
    if (n < 0) return false;
    if (n == 0 || n == 1) return true;
    
    int a = 0, b = 1, c = 1;
    while (c < n) {
        a = b;
        b = c;
        c = a + b;
    }
    return (c == n);
}

bool isGenap(int n) { return (n % 2 == 0); }

bool isPalindrome(int n) {
    int reversed = 0, remainder, original = n;
    while (n > 0) {
        remainder = n % 10;
        reversed = reversed * 10 + remainder;
        n /= 10;
    }
    return (original == reversed);
}

// --- OPTIMASI KODE (DRY PRINCIPLE) ---
// Membuat tipe data baru berupa "Pointer ke Fungsi" yang mereturn bool dan menerima int
typedef bool (*FungsiPengecekan)(int);

// Prosedur ini menangani SEMUA jenis input, proses, output, dan riwayat sekaligus
void prosesPengecekan(string namaTipe, FungsiPengecekan fungsiCek) {
    // 1. Validasi Input (Hanya menerima angka positif)
    while (true) {
        cout << "Masukkan angka untuk cek " << namaTipe << ": ";
        if (cin >> angka && angka >= 0) break;
        cout << "Input tidak valid! Masukkan bilangan bulat positif.\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    // 2. Eksekusi fungsi matematika yang dikirim via parameter
    bool hasil = fungsiCek(angka);

    // 3. Tampilkan Hasil
    cout << "-> HASIL: " << angka << (hasil ? " ADALAH " : " BUKAN ") << namaTipe << ".\n";

    // 4. Simpan ke histori
    histori.push_back({angka, namaTipe, hasil});

    // Jeda
    cout << "\nTekan Enter untuk melanjutkan...";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.get();
}

// --- FITUR TAMBAHAN ---
void tampilkanHistori() {
    cout << "\n=== RIWAYAT PENGECEKAN ===\n";
    if (histori.empty()) {
        cout << "Riwayat masih kosong.\n";
    } else {
        int i = 0;
        while (i < histori.size()) {
            cout << i+1 << ". Angka: " << histori[i].nilai 
                 << "\t| Tipe: " << histori[i].jenis 
                 << "\t| Hasil: " << (histori[i].status ? "Ya" : "Bukan") << "\n";
            i++;
        }
    }
    cout << "\nTekan Enter untuk kembali...";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.get();
}

void simpanFile() {
    ofstream file("Laporan_Angka.txt");
    if (file.is_open()) {
        file << "=== LAPORAN SISTEM ===\n";
        for (size_t i = 0; i < histori.size(); i++) {
            file << i+1 << ". Angka: " << histori[i].nilai 
                 << " | Tipe: " << histori[i].jenis 
                 << " | Status: " << (histori[i].status ? "Valid" : "Tidak Valid") << "\n";
        }
        file.close();
        cout << "Data sukses di-export ke 'Laporan_Angka.txt'!\n";
    }
    cout << "\nTekan Enter untuk melanjutkan...";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.get();
}

// --- MAIN MENU ---
int main() {
    // Alokasi memori awal untuk vector agar lebih cepat dan tidak membebani RAM
    histori.reserve(100); 
    pilihan = -1;

    while (pilihan != 0) {
        bersihkanLayar();
        cout << "==================================\n";
        cout << "      ENGINE PENGECEKAN v2.0      \n";
        cout << "==================================\n";
        cout << "1. Cek Bilangan Prima\n";
        cout << "2. Cek Bilangan Fibonacci\n";
        cout << "3. Cek Bilangan Genap/Ganjil\n";
        cout << "4. Cek Bilangan Palindrome\n";
        cout << "5. Lihat Riwayat (Histori)\n";
        cout << "6. Export Riwayat (.txt)\n";
        cout << "0. Keluar\n";
        cout << "Pilih menu (0-6): ";
        
        if (!(cin >> pilihan)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue; // Skip ke iterasi while berikutnya jika input bukan angka
        }

        switch (pilihan) {
            // Mengirim string dan NAMA FUNGSI sebagai parameter (Function Pointer)
            case 1: prosesPengecekan("Prima", isPrima); break;
            case 2: prosesPengecekan("Fibonacci", isFibonacci); break;
            case 3: prosesPengecekan("Genap", isGenap); break;
            case 4: prosesPengecekan("Palindrome", isPalindrome); break;
            case 5: tampilkanHistori(); break;
            case 6: simpanFile(); break;
            case 0: cout << "Sistem dihentikan.\n"; break;
            default: cout << "Opsi tidak valid!\n"; break;
        }
    }
    return 0;
}