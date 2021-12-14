#ifndef utama_H
#define utama_H

// Deklarasi Variabel
#define JUM_BLOK 1		/* sebuah record */
FILE *dtbuku;

typedef struct{
		int kode;
		char judul[26];
		char jenis[30];
		char genre[30];
		char umur[3];
		char pengarang[30];
		int tahun;
	}data_buku;

data_buku buku;

char jawab;
// Fungsi Input Buku
void Input_Buku();

// Fungsi Baca Daftar Buku
void Tampil_File();

// Prosedur Baca Status Peminjaman
void Tampil_Pinjam();

// Mengecek apakah file kosong atau tidak
//int empty();

// Function untuk mengecek kode buku
int checkKode(data_buku buku,int id);
int checkNomor(buku_pinjam bukupj,int id);

// Prosedur untuk menghapus data peminjaman
void hapusDataPinjam(buku_pinjam bukupj, int r);
void hapusdtbuku(data_buku buku, int r);
void hapusAllData(data_buku buku);

// Prosedur untuk mengambil tanggal sekarang
void Tanggal();

// Prosedur untuk menampilkan panduan aplikasi
void panduan();

// Prosedur Sorting Buku
void sortTahun(data_buku buku);
void sortKode(data_buku buku);







#endif
