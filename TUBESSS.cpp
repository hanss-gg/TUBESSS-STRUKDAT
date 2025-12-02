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
void deleteDosen(ListDsn &LD,string NIDN, adrDsn P);
void deleteMhs(ListMhs &LM,string NIM, adrMhs P);
void deleteRelasi(string NIDN,string NIM);
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
