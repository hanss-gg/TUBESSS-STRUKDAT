#include <iostream>
#include "TUBESSS.h"

using namespace std;

int main() {
    ListDsn LD;
    ListMhs LM;
    bool keluar = false;

    createListDosen(LD);
    createListMahasiswa(LM);

    int menu;
    while (!keluar) {
        TampilanMenuAwal();
        cout << "Pilih menu: ";
        cin >> menu;

        if (menu == 1) {
            int p;
            bool kembali = false;
            while(!kembali){
                TampilanMenuDosen();
                cout << "Pilih: ";
                cin >> p;
                if (p == 1) {
                    infotypeDsn d;
                    cout << "NIDN: ";
                    cin >> d.NIDN;
                    cout << "Nama: ";
                    cin.ignore();
                    getline(cin, d.nama);
                    cout << "Jurusan: ";
                    cin.ignore();
                    getline(cin, d.jurusan);
                    d.jumlahMhsBimbingan = 0;
                    insertDosen(LD, createElmDosen(d));
                } else if (p == 2) {
                    string nidn;
                    cout << "Masukkan NIDN: ";
                    cin >> nidn;
                    deleteDosen(LD, nidn);
                } else if (p == 3) {
                    string nidn;
                    cout << "NIDN Dosen yang ingin di Edit: ";
                    cin >> nidn;
                    editDosen(LD,nidn);
                } else if (p == 4) {
                    showAllDosen(LD);
                } else if (p == 0){
                    kembali = true;
                } else {
                    cout << "Pilihan Tidak Valid" <<endl;
                }
            }

        } else if (menu == 2) {
            int p;
            bool kembali= false;
            while(!kembali){
                TampilanMenuMahasiswa();
                cout << "Pilih: ";
                cin >> p;
                if (p == 1) {
                    infotypeMhs m;
                    cout << "NIM: ";
                    cin >> m.NIM;
                    cout << "Nama: ";
                    cin.ignore();
                    getline(cin, m.nama);
                    cout << "Jurusan: ";
                    cin.ignore();
                    getline(cin, m.jurusan);
                    cout << "Judul TA: ";
                    cin.ignore();
                    getline(cin, m.judulTA);
                    cout << "Semester: ";
                    cin >> m.semester;
                    m.jumlahPembimbing = 0;
                    insertMhs(LM, createElmMahasiswa(m));
                } else if (p == 2) {
                    string nim;
                    cout << "Masukkan NIM: ";
                    cin >> nim;
                    deleteMhs(LD,LM, nim);
                } else if(p==3){
                    string nim;
                    cout << "NIM Mahasiswa yang ingin di Edit: ";
                    cin >> nim;
                    editMahasiswa(LM,nim);
                }else if (p == 4) {
                    showAllMahasiswa(LM);
                } else if(p==0){
                    kembali = true;
                }else{
                    cout << "Pilihan Tidak Valid" <<endl;
                }
            }

        } else if (menu == 3) {
            int p;
            bool kembali= false;
            while(!kembali){
                TampilanMenuRelasi();
                cout << "Pilih: ";
                cin >> p;
                if (p == 1) {
                    string nidn, nim;
                    cout << "NIDN: ";
                    cin >> nidn;
                    cout << "NIM: ";
                    cin >> nim;
                    insertRelasi(LD, LM, nidn, nim);
                } else if (p == 2) {
                    string nidn, nim;
                    cout << "NIDN: ";
                    cin >> nidn;
                    cout << "NIM: ";
                    cin >> nim;
                    deleteRelasi(LD, nidn, nim);
                } else if (p == 3) {
                    string lama, baru, nim;
                    cout << "NIDN Lama: ";
                    cin >> lama;
                    cout << "NIDN Baru: ";
                    cin >> baru;
                    cout << "NIM: "; cin >> nim;
                    editRelasiPindahDosen(LD, LM, lama, baru, nim);
                } else if (p == 4) {
                    string nidn, lama, baru;
                    cout << "NIDN: ";
                    cin >> nidn;
                    cout << "NIM Lama: ";
                    cin >> lama;
                    cout << "NIM Baru: ";
                    cin >> baru;
                    editRelasiPindahMahasiswa(LD, LM, nidn, lama, baru);
                } else if(p==0){
                    kembali = true;
                }else{
                    cout << "Pilihan Tidak Valid" <<endl;
                }
            }

        } else if (menu == 4) {
            int p;
            bool kembali= false;
            while(!kembali){
                TampilanMenuTampilkan();
                cout << "Pilih: ";
                cin >> p;
                if (p == 1) {
                    showAllDosenDenganMahasiswa(LD);
                } else if (p == 2) {
                    showAllMahasiswaDenganPembimbing(LM, LD);
                } else if (p == 3) {
                    string nidn;
                    cout << "Masukkan NIDN Dosen: ";
                    cin >> nidn;
                    showMahasiswaBimbinganDosen(LD,nidn);
                } else if (p ==4){
                    string nim;
                    cout << "Masukkan NIM Mahasiswa: ";
                    cin >> nim;
                    showDosenPembimbingMahasiswa(LD,LM,nim);
                } else if (p==5){
                    showDosenTanpaMahasiswa(LD);
                } else if (p==6){
                    showMahasiswaTanpaPembimbing(LM);
                } else if (p==0){
                    kembali =true;
                } else {
                    cout << "Pilihan Tidak Valid" <<endl;
                }
            }
        } else if (menu == 0) {
            cout << "Program selesai.\n";
            keluar = true;
        } else {
            cout << "Menu tidak valid.\n";
        }
    }

    return 0;
}
