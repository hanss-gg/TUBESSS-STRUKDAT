#ifndef TUBESSS_H_INCLUDED
#define TUBESSS_H_INCLUDED

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

#endif // TUBESSS_H_INCLUDED
