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

bool isPrima(int n) {
    if (n <= 1) return false;
    if (n <= 3) return true;
    if (n % 2 == 0 || n % 3 == 0) return false;
    
    int i = 5;
    while (i * i <= n) {
        if (n % i == 0 || n % (i + 2) == 0) return false;
        i += 6;
    }
    return true;
}

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

typedef bool (*FungsiPengecekan)(int);

void prosesPengecekan(string namaTipe, FungsiPengecekan fungsiCek) {

    while (true) {
        cout << "Masukkan angka untuk cek " << namaTipe << ": ";
        if (cin >> angka && angka >= 0) break;
        cout << "Input tidak valid! Masukkan bilangan bulat positif.\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }