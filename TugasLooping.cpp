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