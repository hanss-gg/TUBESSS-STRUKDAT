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
