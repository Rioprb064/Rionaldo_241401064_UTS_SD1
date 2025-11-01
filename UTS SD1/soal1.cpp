#include <iostream>
#include <vector>
#include <string>
using namespace std;

struct Pasien {
    string nama;
    string jenis;
    int umur;
    int tingkatDarurat;
};

void tukarPasien(Pasien &a, Pasien &b) {
    Pasien temp = a;
    a = b;
    b = temp;
}

void urutkanPasien(vector<Pasien> &daftar) {
    for (int i = 0; i < daftar.size() - 1; i++) {
        for (int j = 0; j < daftar.size() - i - 1; j++) {
            if (daftar[j].tingkatDarurat < daftar[j + 1].tingkatDarurat) {
                tukarPasien(daftar[j], daftar[j + 1]);
            }
        }
    }
}

int main() {
    int jumlahPasien;
    cout << "Masukkan jumlah pasien: ";
    cin >> jumlahPasien;
    cin.ignore();

    vector<Pasien> antrean;

    for (int i = 0; i < jumlahPasien; i++) {
        Pasien p;
        cout << "\nPasien " << i + 1 << ":\n";
        cout << "Nama hewan : ";
        getline(cin, p.nama);
        cout << "Jenis hewan : ";
        getline(cin, p.jenis);
        cout << "Umur : ";
        cin >> p.umur;

        do {
            cout << "Tingkat darurat (1-5): ";
            cin >> p.tingkatDarurat;
            if (p.tingkatDarurat < 1 || p.tingkatDarurat > 5) {
                cout << "Nilai harus antara 1 sampai 5. Silakan masukkan lagi.\n";
            }
        } while (p.tingkatDarurat < 1 || p.tingkatDarurat > 5);

        cin.ignore(); 
        antrean.push_back(p);
    }

    urutkanPasien(antrean);

    cout << "\nUrutan Penanganan Pasien\n";
    for (int i = 0; i < antrean.size(); i++) {
        cout << i + 1 << ". " << antrean[i].nama << " (" << antrean[i].umur << " tahun)"
             << " - Darurat " << antrean[i].tingkatDarurat << endl;
    }

    return 0;
}
