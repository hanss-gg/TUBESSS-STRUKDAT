#ifndef TUBESSS_H_INCLUDED
#define TUBESSS_H_INCLUDED

#include <iostream>

#define first(L) L.first
#define info(P) P->info
#define nextDsn(P) P->nextDsn
#define nextR(P) P->nextR
#define nextMhs(P) P->nextMhs
#define PMhs(P) P->PMhs
#define relasi(P) P->relasi

using namespace std;

struct Dosen{
    string NIDN;
    string nama;
    string jurusan;
    int jumlahMhsBimbingan;
};

struct Mahasiswa{
    string NIM;
    string nama;
    string jurusan;
    string judulTA;
    int semester;
    int jumlahPembimbing;
};

typedef Mahasiswa infotypeMhs;
typedef Dosen infotypeDsn;

typedef struct elmDsn* adrDsn;
typedef struct elmMhs* adrMhs;
typedef struct elmR* adrR;

struct elmR{
    adrMhs PMhs;
    adrR nextR;
};

struct ListR{
    adrR first;
};

struct elmDsn{
    infotypeDsn info;
    ListR relasi;
    adrDsn nextDsn;
};

struct elmMhs{
    infotypeMhs info;
    adrMhs nextMhs;
};

struct ListDsn{
    adrDsn first;
};

struct ListMhs{
    adrMhs first;
};

void createListDosen(ListDsn &LD);
void createListMahasiswa(ListMhs &LM);
adrDsn createElmDosen(infotypeDsn X);
adrMhs createElmMahasiswa(infotypeMhs X);
void insertDosen(ListDsn &LD,adrDsn D);
void insertDosenFirst(ListDsn &LD, adrDsn D);
void insertDosenAfter(ListDsn &LD, string NIDN, adrDsn D);
void insertMhs(ListMhs &LM,adrMhs M);
void insertMhsFirst(ListMhs &LM, adrMhs M);
void insertMhsAfter(ListMhs &LM, string NIM, adrMhs M);
void insertRelasi(ListDsn LD, ListMhs LM,string NIDN,string NIM);
void deleteDosen(ListDsn &LD,string NIDN, adrDsn P);
void deleteMhs(ListMhs &LM,string NIM, adrMhs P);
void deleteRelasi(string NIDN,string NIM);
adrDsn cariDosen(ListDsn LD, string NIDN);
adrMhs cariMahasiswa(ListMhs LM, string NIM);
adrR findRelasi(adrDsn D, adrMhs M);
void showAllDosen(ListDsn LD);
void showAllMahasiswa(ListMhs LM);
void showMahasiswaBimbinganDosen(ListDsn LD, string NIDN);
void showAllDosenDenganMahasiswa(ListDsn LD);
void showAllMahasiswaDenganPembimbing(ListMhs LM, ListDsn LD);
void showDosenPembimbingMahasiswa(ListDsn LD,ListMhs LM, string NIM);
void countRelasiPerDosen(ListDsn LD);
void countRelasiMahasiswa(ListDsn LD, ListMhs LM, string NIM);
void countMahasiswaTanpaPembimbing(ListMhs LM);
void editRelasi(ListDsn LD, ListMhs LM, string NIDN, string NIM_lama, string NIM_baru);
void showDosenTanpaMahasiswa(ListDsn LD);
void showMahasiswaTanpaPembimbing(ListMhs LM);
void editDosen(ListDsn LD, string NIDN);
void editMahasiswa(ListMhs LM, string NIM);

#endif // TUBESSS_H_INCLUDED

