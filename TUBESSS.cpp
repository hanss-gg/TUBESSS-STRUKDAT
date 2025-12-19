#include <iostream>
#include "TUBESSS.h"

using namespace std;

void createListDosen(ListDsn &LD){
    first(LD) = NULL;
}

void createListMahasiswa(ListMhs &LM){
    first(LM) = NULL;
}

adrDsn createElmDosen(infotypeDsn X){
    adrDsn D = new elmDsn;
    info(D) = X;
    first(relasi(D)) = NULL;
    nextDsn(D) = NULL;
    return D;
}

adrMhs createElmMahasiswa(infotypeMhs X){
    adrMhs M = new elmMhs;
    info(M) = X;
    nextMhs(M) = NULL;
    return M;
}

void insertDosen(ListDsn &LD,adrDsn D){
    if(cariDosen(LD,info(D).NIDN) != NULL){
        cout << "Dosen dengan NIDN sama telah terdaftar" <<endl;
    } else {
        if(first(LD)==NULL){
            first(LD) = D;
        } else {
            adrDsn P = first(LD);
            while(nextDsn(P)!=NULL){
                P = nextDsn(P);
            }
            nextDsn(P) = D;
        }
        cout << "Dosen Berhasil Ditambahkan" <<endl;
    }
}

void insertDosenFirst(ListDsn &LD, adrDsn D){
    if(cariDosen(LD,info(D).NIDN) != NULL){
        cout << "Dosen dengan NIDN sama telah terdaftar" <<endl;
    } else {
        if(first(LD) == NULL){
            first(LD) = D;
        } else {
            nextDsn(D) = first(LD);
            first(LD) = D;
        }
        cout << "Dosen Berhasil Ditambahkan" <<endl;
    }
}

void insertDosenAfter(ListDsn &LD, string NIDN, adrDsn D){
    adrDsn P = cariDosen(LD, NIDN);
    if(cariDosen(LD,info(D).NIDN) != NULL){
        cout << "Dosen dengan NIDN sama telah terdaftar" <<endl;
    } else {
        if(P == NULL){
            cout << "Dosen yang dicari tidak ditemukan" << endl;
        } else {
            nextDsn(D) = nextDsn(P);
            nextDsn(P) = D;
        }
        cout << "Dosen Berhasil Ditambahkan" <<endl;
    }
}

void insertMhs(ListMhs &LM,adrMhs M){
    if(cariMahasiswa(LM,info(M).NIM) != NULL){
        cout << "Mahasiswa dengan NIM sama telah terdaftar" <<endl;
    } else {
        if(first(LM)==NULL){
            first(LM) = M;
        } else {
            adrMhs P = first(LM);
            while(nextMhs(P)!=NULL){
                P = nextMhs(P);
            }
            nextMhs(P) = M;
        }
        cout << "Mahasiswa Berhasil Ditambahkan" <<endl;
    }
}

void insertMhsFirst(ListMhs &LM, adrMhs M){
    if(cariMahasiswa(LM,info(M).NIM) != NULL){
        cout << "Mahasiswa dengan NIM sama telah terdaftar" <<endl;
    } else {
        if(first(LM) == NULL){
            first(LM) = M;
        } else {
            nextMhs(M) = first(LM);
            first(LM) = M;
        }
        cout << "Mahasiswa Berhasil Ditambahkan" <<endl;
    }
}

void insertMhsAfter(ListMhs &LM, string NIM, adrMhs M){
    adrMhs P = cariMahasiswa(LM, NIM);
    if(cariMahasiswa(LM,info(M).NIM) != NULL){
        cout << "Mahasiswa dengan NIM sama telah terdaftar" <<endl;
    } else {
        if(P == NULL){
            cout << "Mahasiswa acuan tidak ditemukan" << endl;
        } else {
            nextMhs(M) = nextMhs(P);
            nextMhs(P) = M;
        }
    }
    cout << "Mahasiswa Berhasil Ditambahkan" <<endl;
}


void insertRelasi(ListDsn LD, ListMhs LM,string NIDN,string NIM){
    adrDsn D = cariDosen(LD,NIDN);
    adrMhs M = cariMahasiswa(LM,NIM);
    if(D != NULL && M != NULL){
        if(info(M).semester<7){
            cout << "Mahasiswa Minimal Semester 7" <<endl;
        }else if(findRelasi(D,M) != NULL){
            cout << "Mahasiswa dan Dosen sudah Berelasi" <<endl;
        } else if(info(M).jumlahPembimbing>=2){
            cout << "Jumlah Dosen Pembimbing Max" <<endl;
        } else {
            adrR R = new elmR;
            nextR(R) = NULL;
            PMhs(R) = M;
            if (first(relasi(D)) == NULL) {
                first(relasi(D)) = R;
            } else {
                nextR(R) = first(relasi(D));
                first(relasi(D)) = R;
            }
            info(D).jumlahMhsBimbingan++;
            info(M).jumlahPembimbing++;
            cout << "Relasi Berhasil Dilakukan" <<endl;
        }
    } else {
        cout << "Tidak Tersedia Mahasiswa dan Dosen"<<endl;
    }
}
void deleteDosen(ListDsn &LD,string NIDN){
    adrDsn D = cariDosen(LD,NIDN);

    if(D == NULL){
        cout << "Dosen tidak ditemukan" << endl;
    } else {
        adrR R = first(relasi(D));
        while(R != NULL){
            info(PMhs(R)).jumlahPembimbing--;
            adrR X = R;
            R = nextR(R);
            delete X;
        }
        if(D == first(LD)){
            first(LD) = nextDsn(D);
        } else {
            adrDsn prec = first(LD);
            while(nextDsn(prec)!=D){
                prec = nextDsn(prec);
            }
            nextDsn(prec) = nextDsn(D);
        }
        cout << "Dosen berhasil dihapus" << endl;
    }
}
void deleteMhs(ListDsn LD,ListMhs &LM,string NIM){
    adrMhs prec = first(LM);
    adrMhs P = cariMahasiswa(LM,NIM);

    if(P == NULL){
        cout << "Mahasiswa tidak ditemukan" << endl;
    } else {
        if(P == first(LM)){
            first(LM) = nextMhs(P);
        } else {
            while(nextMhs(prec) != P){
                prec = nextMhs(prec);
            }
            nextMhs(prec) = nextMhs(P);
        }
        adrDsn D = first(LD);
        while (D != NULL) {
            deleteRelasi(LD, info(D).NIDN, NIM);
            D = nextDsn(D);
        }
        delete P;
        cout << "Mahasiswa behasil dihapus dari list mahasiswa, pastikan relasi juga dihapus dari semua dosen" << endl;
    }
}
void deleteRelasi(ListDsn &LD,string NIDN,string NIM){
    adrDsn D = cariDosen(LD, NIDN);
    if(D == NULL){
        cout << "Dosen tidak ditemukan" << endl;
    } else {
        adrR R = first(relasi(D));
        adrR prec = NULL;
        while(R != NULL && info(PMhs(R)).NIM != NIM){
            prec = R;
            R = nextR(R);
        }
        if(R == NULL){
            cout << "Relasi tidak ditemukan" << endl;
        } else {
            if(R == first(relasi(D))){
                first(relasi(D)) = nextR(R);
            } else {
                nextR(prec) = nextR(R);
            }
            info(D).jumlahMhsBimbingan--;
            info(PMhs(R)).jumlahPembimbing--;
            delete R;
            cout << "Relasi berhasil dihapus" << endl;
        }
    }
}

adrDsn cariDosen(ListDsn LD, string NIDN){
    if(first(LD) == NULL){
        return NULL;
    } else {
        adrDsn P = first(LD);
        while(P != NULL){
            if(info(P).NIDN == NIDN){
                return P;
            } else {
                P = nextDsn(P);
            }
        }
        return NULL;
    }
}
adrMhs cariMahasiswa(ListMhs LM, string NIM){
    if(first(LM) == NULL){
        return NULL;
    } else {
        adrMhs P = first(LM);
        while(P != NULL){
            if(info(P).NIM == NIM){
                return P;
            } else {
                P = nextMhs(P);
            }
        }
        return NULL;
    }
}

adrR findRelasi(adrDsn D, adrMhs M){
    if(D == NULL){
        return NULL;
    } else if(M == NULL){
        return NULL;
    } else {
        adrR R = first(relasi(D));
        while (R != NULL) {
            if (PMhs(R) == M) {
                return R;
            }
            R = nextR(R);
        }
        return NULL;
    }
}

//Tampilan Semua Dosen
void showAllDosen(ListDsn LD){
    adrDsn P = first(LD);
    if(P == NULL){
        cout << "List dosen kosong" << endl;
    } else {
        while(P != NULL) {
            cout << "NIDN            : " << info(P).NIDN << endl;
            cout << "Nama            : " << info(P).nama << endl;
            cout << "Jurusan         : " << info(P).jurusan << endl;
            cout << "Total Bimbingan : " << info(P).jumlahMhsBimbingan << endl;
            P = nextDsn(P);
        }
    }
    cout << endl;
}

//Tampilan Semua Mahasiswa
void showAllMahasiswa(ListMhs LM){
    adrMhs P = first(LM);
    if(P == NULL){
        cout << "List mahasiswa kosong" << endl;
    } else {
        while(P != NULL){
            cout << "NIM               : " << info(P).NIM << endl;
            cout << "Nama              : " << info(P).nama << endl;
            cout << "Jurusan           : " << info(P).jurusan << endl;
            cout << "JudulTA           : " << info(P).judulTA << endl;
            cout << "Semester          : " << info(P).semester << endl;
            cout << "Jumlah Pembimbing : " << info(P).jumlahPembimbing << endl;
            P = nextMhs(P);
        }
    }
}

//Tampilan Mahasiswa yang dibimbing seorang dosen
void showMahasiswaBimbinganDosen(ListDsn LD, string NIDN){
    adrDsn D = cariDosen(LD, NIDN);
    if(D == NULL){
        cout << "Dosen tidak ditemukan" << endl;
    } else {
        adrR R = first(relasi(D));
        if(R == NULL){
            cout << "Dosen ini belum memiliki mahasiswa dibimbing" << endl;
        } else {
            cout << "Mahasiswa yang dibimbing " << info(D).nama << ":" << endl;
            while(R != NULL){
                cout << "- " << info (PMhs (R)).NIM << " | " << info(PMhs(R)).nama << endl;
                R = nextR(R);
            }
        }
    }
}

//Tampilan Semua Dosen dengan mahasiswa yg dibimbing
void showAllDosenDenganMahasiswa(ListDsn LD){
    adrDsn D = first(LD);
    if(D == NULL){
        cout << "List dosen belum terisi" << endl;
    } else {
        while(D != NULL){
            cout << "NIDN                : " << info(D).NIDN << endl;
            cout << "Nama                : " << info(D).nama << endl;
            cout << "Jurusan             : " << info(D).jurusan << endl;
            cout << "Jumlah Mahasiswa    : " << info(D).jumlahMhsBimbingan << endl;
            adrR R = first(relasi(D));
            if(R == NULL){
                cout << " (Belum membimbing mahasiswa)" << endl;
            } else {
                cout << " Mahasiswa bimbingan: " << endl;
                while(R != NULL){
                    cout << " - " << info(PMhs(R)).NIM << " | " << info(PMhs(R)).nama << endl;
                    R = nextR(R);
                }
            }
            D = nextDsn(D);
        }
    }
}

//Tampilan Semua Mahasiswa dengan dosen pembimbing
void showAllMahasiswaDenganPembimbing(ListMhs LM, ListDsn LD) {
    adrMhs M = first(LM);
    if (M == NULL) {
        cout << "Tidak ada data mahasiswa." << endl;
    } else {
        while (M != NULL) {
            cout << "\nMahasiswa: " << info(M).nama << " (" << info(M).NIM << ")" << endl;
            cout << "Pembimbing:" << endl;
            adrDsn D = first(LD);
            while (D != NULL) {
                if (findRelasi(D, M) != NULL) {
                    cout << "- " << info(D).nama << " | NIDN: " << info(D).NIDN << endl;
                }
                D = nextDsn(D);
            }
            M = nextMhs(M);
        }
    }
}

//Tampilan Dosen yg membimbing seorang mahasiswa
void showDosenPembimbingMahasiswa(ListDsn LD,ListMhs LM, string NIM){
    adrMhs M = cariMahasiswa(LM, NIM);
    adrDsn D = first(LD);
    if(M == NULL){
        cout << "Mahasiswa tidak ditemukan" << endl;
    } else {
        cout << "Daftar Dosen Pembimbing: " << endl;
        while(D != NULL){
            if(findRelasi(D,M) != NULL){
                cout << "- " << info(D).nama << " | NIDN: " << info(D).NIDN << " | Jurusan: " << info(D).jurusan << endl;
            }
            D = nextDsn(D);
        }
    }
}

void countRelasiPerDosen(ListDsn LD) {
    if (first(LD) == NULL) {
        cout << "Tidak ada data dosen." << endl;
    } else {
        adrDsn D = first(LD);
        while (D != NULL) {
            int hitung = 0;
            adrR R = first(relasi(D));
            while (R != NULL) {
                hitung++;
                R = nextR(R);
            }
        cout << info(D).nama << " membimbing " << hitung << " mahasiswa." << endl;
        D = nextDsn(D);
        }
    }
}

void countRelasiMahasiswa(ListDsn LD, ListMhs LM, string NIM){
    adrMhs M = cariMahasiswa(LM, NIM);

    if(M == NULL){
        cout << "Mahasiswa tidak ditemukan" << endl;
    } else {
        int hitung = 0;
        adrDsn D = first(LD);
        while (D != NULL){
            if(findRelasi(D, M) != NULL){
                hitung++;
            }
            D = nextDsn(D);
        }
        cout << "Mahasiswa " << info(M).nama
             << " memiliki " << hitung
             << " dosen pembimbing. " << endl;
    }
}

void countMahasiswaTanpaPembimbing(ListMhs LM){
    adrMhs M = first(LM);
    int hitung = 0;
    if(M == NULL){
        cout << "List mahasiswa kosong" << endl;
    } else {
        while(M != NULL){
            if(info(M).jumlahPembimbing == 0){
                hitung++;
            }
            M = nextMhs(M);
        }
        cout << "Jumlah mahasiswa yang belum memiliki dosen pembimbing: " << hitung << endl;
    }
}

void editRelasiPindahDosen(ListDsn &LD, ListMhs &LM,string NIDN_lama,string NIDN_baru,string NIM) {
    adrDsn D_lama = cariDosen(LD, NIDN_lama);
    adrDsn D_baru = cariDosen(LD, NIDN_baru);
    adrMhs M = cariMahasiswa(LM, NIM);

    if (D_lama == NULL || D_baru == NULL || M == NULL) {
        cout << "Data dosen atau mahasiswa tidak ditemukan" << endl;
    } else if (findRelasi(D_lama,M) == NULL) {
        cout << "Relasi tidak ditemukan" << endl;
    } else if (findRelasi(D_baru,M) != NULL){
        cout << "Mahasiswa sudah dibimbing dosen tersebut"<<endl;
    }else {
        deleteRelasi(LD,NIDN_lama,NIM);
        insertRelasi(LD,LM,NIDN_baru,NIM);
        cout << "Dosen pembimbing berhasil dipindah" << endl;
    }
}

void editRelasiPindahMahasiswa(ListDsn &LD, ListMhs &LM,string NIDN,string NIM_lama,string NIM_baru) {
    adrDsn D = cariDosen(LD, NIDN);
    adrMhs M_lama = cariMahasiswa(LM, NIM_lama);
    adrMhs M_baru = cariMahasiswa(LM, NIM_baru);

    if (M_lama == NULL || M_baru == NULL || D == NULL) {
        cout << "Data dosen atau mahasiswa tidak ditemukan" << endl;
    } else if (findRelasi(D,M_lama) == NULL) {
        cout << "Relasi tidak ditemukan" << endl;
    } else if (findRelasi(D,M_baru) != NULL){
        cout << "Mahasiswa sudah dibimbing dosen tersebut"<<endl;
    } else if (info(M_baru).jumlahPembimbing >= 2){
        cout << "Mahasiswa baru sudah memiliki 2 pembimbing" << endl;
    }else {
        deleteRelasi(LD,NIDN,NIM_lama);
        insertRelasi(LD,LM,NIDN,NIM_baru);
        cout << "Mahasiswa Bimbingan berhasil dipindah" << endl;
    }
}


void showDosenTanpaMahasiswa(ListDsn LD){
    adrDsn D = first(LD);
    bool ada = false;
    if(D == NULL){
        cout<< "List Dosen Kosong" <<endl;
    } else {
        while(D != NULL){
            if(first(relasi(D)) == NULL){
                cout << "- " << info(D).nama
                     << " | NIDN: " << info(D).NIDN << endl;
                ada = true;
            }
            D = nextDsn(D);
        }

        if(!ada){
            cout << "Semua dosen memiliki mahasiswa bimbingan" << endl;
        }
    }

}

void showMahasiswaTanpaPembimbing(ListMhs LM){
    adrMhs M = first(LM);
    bool ada = false;

    if(M == NULL){
        cout<< "List Mahasiswa Kosong" <<endl;
    }else {
        while(M != NULL){
            if(info(M).jumlahPembimbing == 0){
                cout << "- " << info(M).nama
                     << " | NIM: " << info(M).NIM << endl;
                ada = true;
            }
            M = nextMhs(M);
        }

        if(!ada){
            cout << "Semua mahasiswa sudah memiliki dosen pembimbing" << endl;
        }
    }
}

void editDosen(ListDsn &LD, string NIDN){
    adrDsn D = cariDosen(LD, NIDN);

    if(D == NULL){
        cout << "Dosen tidak ditemukan" << endl;
    } else {
        cout << "Masukkan Nama Baru   : ";
        cin.ignore();
        getline(cin, info(D).nama);
        cout << "Masukkan Jurusan Baru: ";
        cin.ignore();
        getline(cin, info(D).jurusan);

        cout << "Data dosen berhasil diperbarui" << endl;
    }
}

void editMahasiswa(ListMhs &LM, string NIM){
    adrMhs M = cariMahasiswa(LM, NIM);

    if(M == NULL){
        cout << "Mahasiswa tidak ditemukan" << endl;
    } else {
        cout << "Masukkan Nama Baru    : ";
        cin.ignore();
        getline(cin, info(M).nama);
        cout << "Masukkan Jurusan Baru : ";
        cin.ignore();
        getline(cin, info(M).jurusan);
        cout << "Masukkan Judul TA Baru: ";
        cin.ignore();
        getline(cin, info(M).judulTA);
        cout << "Masukkan Semester     : ";
        cin >> info(M).semester;

        cout << "Data mahasiswa berhasil diperbarui" << endl;
    }
}

void TampilanMenuAwal(){
    cout << "\n===== MENU UTAMA BIMBINGAN TA =====\n";
    cout << "1. Manajemen Data Dosen\n";
    cout << "2. Manajemen Data Mahasiswa\n";
    cout << "3. Manajemen Relasi\n";
    cout << "4. Tampilkan Data Mahasiswa & Dosen\n";
    cout << "0. Keluar\n";
}

void TampilanMenuDosen(){
    cout << "\n--- Manajemen Dosen ---\n";
    cout << "1. Tambah Dosen\n";
    cout << "2. Hapus Dosen\n";
    cout << "3. Edit Dosen\n";
    cout << "4. Tampilkan Semua Dosen\n";
    cout << "0. Menu Utama\n";
}

void TampilanMenuMahasiswa(){
    cout << "\n--- Manajemen Mahasiswa ---\n";
    cout << "1. Tambah Mahasiswa\n";
    cout << "2. Hapus Mahasiswa\n";
    cout << "3. Edit Mahasiswa\n";
    cout << "4. Tampilkan Semua Mahasiswa\n";
    cout << "0. Menu Utama\n";
}
void TampilanMenuRelasi(){
    cout << "\n--- Manajemen Relasi ---\n";
    cout << "1. Buat Relasi\n";
    cout << "2. Hapus Relasi\n";
    cout << "3. Edit Dosen Pembimbing\n";
    cout << "4. Edit Mahasiswa Bimbingan\n";
    cout << "0. Menu Utama\n";
}
void TampilanMenuTampilkan(){
    cout << "\n--- Tampilkan Data ---\n";
    cout << "1. Mahasiswa Bimbingan Dosen\n";
    cout << "2. Dosen Pembimbing Mahasiswa\n";
    cout << "3. Mahasiswa Bimbingan Seorang Dosen\n";
    cout << "4. Dosen Pembimbing Seorang Mahasiswa\n";
    cout << "5. Dosen Tidak Punya Bimbingan\n";
    cout << "6. Mahasiswa Tidak Punya Bimbingan\n";
    cout << "0. Menu Utama\n";
}
