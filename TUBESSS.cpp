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
    if(first(LD)==NULL){
        first(LD) = D;
    } else {
        adrDsn P = first(LD);
        while(nextDsn(P)!=NULL){
            P = nextDsn(P);
        }
        nextDsn(P) = D;
    }
}
void insertMhs(ListMhs &LM,adrMhs M){
    if(first(LM)==NULL){
        first(LM) = M;
    } else {
        adrMhs P = first(LM);
        while(nextMhs(P)!=NULL){
            P = nextMhs(P);
        }
        nextMhs(P) = M;
    }
}

void insertRelasi(ListDsn LD, ListMhs LM,string NIDN,string NIM){
    adrDsn D = cariDosen(LD,NIDN);
    adrMhs M = cariMahasiswa(LM,NIM);
    if(D != NULL && M != NULL){
        if(info(M).jumlahPembimbing<2){
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
        } else {
            cout << "Jumlah Dosen Pembimbing Max" <<endl;
        }
    } else {
        cout << "Tidak Tersedia Mahasiswa dan Dosen"<<endl;
    }
}
void deleteDosen(ListDsn &LD,string NIDN, adrDsn X){
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
        X = D;
        cout << "Dosen berhasil dihapus" << endl;
    }
}
void deleteMhs(ListMhs &LM,string NIM, adrMhs P){
    adrMhs prec = NULL;
    P = first(LM);

    while(P != NULL && info(P).NIM != NIM){
        prec = P;
        P =nextMhs (P);
    }
    if(P == NULL){
        cout << "Mahasiswa tidak ditemukan" << endl;
    } else {
        if(P == first(LM)){
            first(LM) = nextMhs(P);
        } else {
            nextMhs(prec) = nextMhs(P);
        }
        delete P;
        cout << "Mahasiswa behasil dihapus dari list mahasiswa, pastikan relasi juga dihapus dari semua dosen" << endl;
    }
}
void deleteRelasi(ListDsn LD,string NIDN,string NIM){
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
        cout <<"List Kosong"<<endl;
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
        cout <<"List Kosong"<<endl;
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

void showAllDosen(ListDsn LD){
    adrDsn P = first(LD);
    if(P == NULL){
        cout << "List dosen kosong" << endl;
    } else {
        while(P != NULL) {
            cout << "NIDN    : " << info(P).NIDN << endl;
            cout << "nama    : " << info(P).nama << endl;
            cout << "jurusan : " << info(P).jurusan << endl;
            cout << "jumlahMhsBimbingan: " << info(P).jumlahMhsBimbingan << endl;
            P = nextDsn(P);
        }
    }
}
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

void showAllMahasiswaDenganPembimbing(ListMhs LM, ListDsn LD) {
    adrMhs M = first(LM);
    adrDsn D = first(LD);
    if (M == NULL) {
        cout << "Tidak ada data mahasiswa." << endl;
    } else {
        while (M != NULL) {
            cout << "\nMahasiswa: " << info(M).nama << " (" << info(M).NIM << ")" << endl;
            cout << "Pembimbing:" << endl;
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
