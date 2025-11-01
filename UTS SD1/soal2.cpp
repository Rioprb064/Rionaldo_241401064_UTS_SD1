#include <iostream>
#include <string>
using namespace std;

struct Film {
    string judul;
    int tahun;
    int rating;
    Film* next;
};

Film* head = nullptr;

Film* buatFilm(string judul, int tahun, int rating) {
    Film* baru = new Film;
    baru->judul = judul;
    baru->tahun = tahun;
    baru->rating = rating;
    baru->next = nullptr;
    return baru;
}

void tambahBelakang(string judul, int tahun, int rating) {
    Film* baru = buatFilm(judul, tahun, rating);
    if (head == nullptr) {
        head = baru;
    } else {
        Film* temp = head;
        while (temp->next != nullptr)
            temp = temp->next;
        temp->next = baru;
    }
}

void tambahDepan(string judul, int tahun, int rating) {
    Film* baru = buatFilm(judul, tahun, rating);
    baru->next = head;
    head = baru;
}

void tambahSetelah(string target, string judul, int tahun, int rating) {
    Film* temp = head;
    while (temp != nullptr && temp->judul != target)
        temp = temp->next;

    if (temp == nullptr) {
        cout << "Film dengan judul \"" << target << "\" tidak ditemukan!\n";
        return;
    }

    Film* baru = buatFilm(judul, tahun, rating);
    baru->next = temp->next;
    temp->next = baru;
}

void hapusFilm(string judul) {
    if (head == nullptr) {
        cout << "Daftar film kosong!\n";
        return;
    }

    Film* temp = head;
    Film* prev = nullptr;

    while (temp != nullptr && temp->judul != judul) {
        prev = temp;
        temp = temp->next;
    }

    if (temp == nullptr) {
        cout << "Film \"" << judul << "\" tidak ditemukan!\n";
        return;
    }

    if (prev == nullptr) {
        head = head->next;
    } else {
        prev->next = temp->next;
    }

    delete temp;
    cout << "Film \"" << judul << "\" berhasil dihapus.\n";
}

void tampilkanFilm() {
    Film* temp = head;
    int total = 0;
    if (temp == nullptr) {
        cout << "Daftar film kosong.\n";
        return;
    }
    while (temp != nullptr) {
        cout << temp->judul << " (" << temp->tahun << ") - Rating: " << temp->rating << endl;
        temp = temp->next;
        total++;
    }
    cout << "\nTotal film tersisa: " << total << endl;
}

int main() {
    int n;
    cout << "Masukkan jumlah film awal: ";
    cin >> n;
    cin.ignore();

    for (int i = 0; i < n; i++) {
        string judul;
        int tahun, rating;

        cout << "\nFilm " << i + 1 << ":\n";
        cout << "Judul: ";
        getline(cin, judul);
        cout << "Tahun: ";
        cin >> tahun;
        cout << "Rating: ";
        cin >> rating;
        cin.ignore();

        tambahBelakang(judul, tahun, rating);
    }

    char pilihan;
    do {
        cout << "\n=== MENU MANAJEMEN FILM ===\n";
        cout << "1. Tambah film di depan\n";
        cout << "2. Tambah film di belakang\n";
        cout << "3. Tambah film di tengah (setelah judul tertentu)\n";
        cout << "4. Hapus film\n";
        cout << "5. Tampilkan daftar film\n";
        cout << "6. Keluar\n";
        cout << "Pilih menu (1-6): ";
        cin >> pilihan;
        cin.ignore();

        if (pilihan == '1') {
            string judul; int tahun, rating;
            cout << "\nMasukkan data film baru:\n";
            cout << "Judul: "; getline(cin, judul);
            cout << "Tahun: "; cin >> tahun;
            cout << "Rating: "; cin >> rating;
            cin.ignore();
            tambahDepan(judul, tahun, rating);
        } 
        else if (pilihan == '2') {
            string judul; int tahun, rating;
            cout << "\nMasukkan data film baru:\n";
            cout << "Judul: "; getline(cin, judul);
            cout << "Tahun: "; cin >> tahun;
            cout << "Rating: "; cin >> rating;
            cin.ignore();
            tambahBelakang(judul, tahun, rating);
        } 
        else if (pilihan == '3') {
            string target, judul; int tahun, rating;
            cout << "Masukkan judul film yang akan disisipkan setelahnya: ";
            getline(cin, target);
            cout << "Masukkan data film baru:\n";
            cout << "Judul: "; getline(cin, judul);
            cout << "Tahun: "; cin >> tahun;
            cout << "Rating: "; cin >> rating;
            cin.ignore();
            tambahSetelah(target, judul, tahun, rating);
        } 
        else if (pilihan == '4') {
            string judulHapus;
            cout << "Masukkan judul film yang ingin dihapus: ";
            getline(cin, judulHapus);
            hapusFilm(judulHapus);
        } 
        else if (pilihan == '5') {
            cout << "\nDaftar Film:\n";
            tampilkanFilm();
        } 
        else if (pilihan == '6') {
            cout << "Keluar dari program...\n";
        } 
        else {
            cout << "Pilihan tidak valid!\n";
        }

    } while (pilihan != '6');

    return 0;
}