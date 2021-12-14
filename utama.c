#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include "fituradm.h"
#include "utama.h"
#define MAX_LEN 100 // Length of each line in input file.

//======================================================================= Prosedur Menginput Buku  =============================================================================
void Input_Buku(){
	system("cls");
	printf("\n========================================================================================================================\n");
	printf("|                                             	[Input Buku]     	     	                                     |\n");
	printf("========================================================================================================================\n");
	if ((dtbuku=fopen("daftarbuku.dat", "ab")) == NULL )
	{
		printf("File tidak dapat dibuat!\r\n");
		main();
	}
	
	do {
		printf("Kode buku : "); fflush(stdin);
		scanf("%d", &buku.kode);
		printf("Judul buku : "); fflush(stdin);
		gets(buku.judul);
		printf("Jenis buku : "); fflush(stdin);
		gets(buku.jenis);
		printf("Genre buku : "); fflush(stdin);
		gets(buku.genre);
		printf("Kategori Umur : "); fflush(stdin);
		gets(buku.umur);
		printf("Nama pengarang : "); fflush(stdin);
		gets(buku.pengarang);
		printf("Tahun Terbit : "); fflush(stdin);
		scanf("%d", &buku.tahun);
		
		/* Rekam sebuah data bertipe record menggunakan fungsi fwrite */
		fwrite(&buku, sizeof(buku), 1, dtbuku);
		
		printf("\r\nMemasukkan data lagi (Y/T)?"); fflush(stdin);
		jawab = toupper(getche());		/* Baca jawaban dari keyboard */
	}
	while (jawab == 'Y');
	fclose(dtbuku);		/* Tutup file */
	
	printf("\r\nData sudah disimpan pada file.\r\n");
	printf("\r\nLihat isi file (Y/T)?"); fflush(stdin);
	jawab = toupper(getche());			/* Baca jawaban dari keyboard */
	if (jawab == 'Y');
	{	Tampil_File();
	}
	
	menuadm();
}

//======================================================================= Prosedur Menampilkan File  ===========================================================================
void Tampil_File(){
	console_clear_screen();
	printf("========================================================================================================================\n\n");
	printf("\t\t\t\t\t\tD A F T A R  B U K U\n\n");
	printf("========================================================================================================================\n");
	printf("| Kode |        Judul Buku       | Jenis Buku  |     Genre         | Umur     |   	 Pengarang  	 | Tahun Terbit|\n");
	/* Buka file untuk dibaca isinya */
	if ((dtbuku=fopen("daftarbuku.dat", "rt")) == NULL )
		{
			printf("File tidak dapat dibuka!\r\n");
			exit(1);
		}
	printf("\n");
		/* Ambil isi file ngenggunakan fungsi fread(), lalu tampilkan ke layar */
	while ((fread(&buku, sizeof(buku), JUM_BLOK, dtbuku)) == JUM_BLOK )
	printf("  %d\t %-26s %-16s %-16s %-3s\t %-16s       	%4d\n", buku.kode, buku.judul, buku.jenis, buku.genre, buku.umur, buku.pengarang, buku.tahun);
	fclose(dtbuku);		/* Tutup file */
	
}

//=================================================================  Prosedur menampilkan status peminjaman  ===================================================================
void Tampil_Pinjam(){
	system("cls");
	printf("\n========================================================================================================================\n");
	printf("|                                             [Status Peminjaman Buku]                                               |\n");
	printf("========================================================================================================================\n");
	printf("|  Nomor  |        Nama       |  Kode Buku  |			Judul Buku 			|  Tanggal Peminjaman  |\n");
	/* Buka file untuk dibaca isinya */
	if ((dtpinjam=fopen("datapinjam.dat", "rb")) == NULL )
		{
			printf("File tidak dapat dibuka!\r\n");
			exit(1);
		}
	printf("\n");
		/* Ambil isi file ngenggunakan fungsi fread(), lalu tampilkan ke layar */
	while ((fread(&bukupj, sizeof(bukupj), JUM_BLOK, dtpinjam)) == JUM_BLOK )
	printf(" %2d		 %-16s   %2d				%-26s		%d - %d - %4d	",bukupj.nomor,bukupj.nama,bukupj.kode,bukupj.judul,bukupj.tgl_pinjam.bln,bukupj.tgl_pinjam.tgl,bukupj.tgl_pinjam.thn);
	fclose(dtpinjam);
	printf("\n\n\n========================================================================================================================\n\n");
}

//===================================================================  Function untuk mengecek kode buku  =======================================================================
int checkKode(data_buku buku,int id){
	FILE *dtbuku;
	int c = 1;
	if(c==1){
		dtbuku = fopen("daftarbuku.dat","rb");
		while(fread(&buku, sizeof(buku),1,dtbuku)){
			if( id == buku.kode){
				fclose(dtbuku);
				return 1;
			}
		}
	}else{
		c = 0;
		fclose(dtbuku);
		return 0;
	}
}

//===================================================================  Function untuk mengecek nomor buku  ======================================================================
int checkNomor(buku_pinjam bukupj,int id){
	FILE *dtpinjam;
	int c = 1;
	if(c==1){
		dtpinjam = fopen("datapinjam.dat","rb");
		while(fread(&bukupj, sizeof(bukupj),1,dtpinjam)){
			if( id == bukupj.nomor){
				fclose(dtpinjam);
				return 1;
			}
		}
	}else{
		c = 0;
		fclose(dtpinjam);
		return 0;
	}
}

//=================================================================  Prosedur untuk menghapus data peminjaman  ==================================================================
void hapusbuku(buku_pinjam bukupj, int r){
	FILE *tmp;
	int s;
	
		if (checkNomor(bukupj, r) == 0){
			printf("\n Data peminjaman %d tidak ditemukan\n\n",r);
		}
		else{
			dtpinjam = fopen("datapinjam.dat","rb");
			tmp = fopen("Temp_Data.txt","wb");
			while (fread(&bukupj, sizeof(bukupj), 1, dtpinjam)){
				s = bukupj.nomor;
				if ( s != r){
					//Menyalin data file yang tidak ingin dihapus
					fwrite(&bukupj, sizeof(bukupj), 1, tmp);
				}
			}
			fclose(dtpinjam);
			fclose(tmp);
			dtpinjam = fopen("datapinjam.dat","wb");
			tmp = fopen("Temp_Data.txt","rb");
			while(fread(&bukupj,sizeof(bukupj),1,tmp)){
				fwrite(&bukupj,sizeof(bukupj),1,dtpinjam);
			}
			fclose(dtpinjam);
			fclose(tmp);
		}
	}

void hapusdtbuku(data_buku buku, int r){
	FILE *tmp;
	int s;
	
		if (checkKode(buku, r) == 0){
			printf("\n Data peminjaman %d tidak ditemukan\n\n",r);
		}
		else{
			dtpinjam = fopen("daftarbuku.dat","rb");
			tmp = fopen("Temp_Data.txt","wb");
			while (fread(&buku, sizeof(buku), 1, dtbuku)){
				s = buku.kode;
				if ( s != r){
					//Menyalin data file yang tidak ingin dihapus
					fwrite(&buku, sizeof(buku), 1, tmp);
				}
			}
			fclose(dtbuku);
			fclose(tmp);
			dtbuku = fopen("daftarbuku.dat","wb");
			tmp = fopen("Temp_Data.txt","rb");
			while(fread(&buku,sizeof(buku),1,tmp)){
				fwrite(&buku,sizeof(buku),1,dtbuku);
			}
			fclose(dtbuku);
			fclose(tmp);
		}
	}
//=================================================================  Prosedur untuk mengambil tanggal sekarang  =================================================================
void Tanggal(){
    struct tm *Sys_T;
 
    time_t Tval;
    Tval = time(NULL);
    Sys_T = localtime(&Tval); /* Untuk mendapatkan waktu lokal komputer */
    /* Sys_T = gmtime(&Tval); */ /* Untuk mendapatkan waktu komputer berbasis GMT/UTC */
 	
    printf("\t Tanggal	= %d", Sys_T->tm_mday);
    printf("\n\t Bulan		= %d", Sys_T->tm_mon+1); /* Ditambah 1 karena Januari dimulai dari 0 */
    printf("\n\t Tahun		= %d", 1900+Sys_T->tm_year); /* Ditambah 1900, karena tahun dimulai dari 1900 */
}

//=================================================================  Prosedur untuk menampilkan panduan aplikasi  ===============================================================
void panduan(){
	FILE *dtpanduan;
	system("cls");
	printf("\n========================================================================================================================\n");
	printf("|                                             [BUKU PANDUAN]                                                           |\n");
	printf("========================================================================================================================\n\n");
	char string[1000];
	/* pada output, tuliskan sebuah nama file yang akan dibaca, lengkap dengan ekstensinya. */
	
	/* buka file untuk dibaca */
	if ((dtpanduan=fopen("panduan.txt", "rt")) == NULL)
	{
		printf("File tidak dapat dibuka!\r\n");
		exit(1);
	}
	
	/* Baca string dari file selama masih ada */
	while ((fgets(string, 1000, dtpanduan)) != NULL)
	/* Tampilkan string ke layar*/
	printf("%s\r", string);
	
	fclose(dtpanduan);				/* tutup file setiap selesai proses terhadap file*/
	printf("\r\n\n\tKembali ke halaman sebelumnya (Y)"); fflush(stdin);
	jawab = toupper(getche());		/* Baca jawaban dari keyboard */
	if(jawab == 'Y'){
			system("cls");
			main();
		}
		system("cls");
		main();

}

//=================================================================== Prosedur Sorting Buku berdasarkan Tahun ===================================================================
void sortTahun(data_buku buku){
	int a[20];
	int count = 0;
	int i,j,t,c;
	FILE *fpt;
	dtbuku = fopen("daftarbuku.dat","rb");
	fpt = fopen("Temp_Data.txt","wb");
	while (fread(&buku, sizeof(buku),1,dtbuku)){
		a[count] = buku.tahun;
		count++;
	}
	
	c = count;
	for (i = 0; i<count -1;i++){
		for (j = i + 1; j<count; j++){
			if (a[i]>a[j]){
				t = a[i];
				a[i] = a[j];
				a[j] = t;
			}
		}
	}
	count = c;
	for (i = 0; i<count; i++){
		rewind(dtbuku);
		while (fread(&buku, sizeof(buku),1,dtbuku)){
			if (a[i]==buku.tahun){
				fwrite(&buku, sizeof(buku),1,fpt);
			}
		}
	}
	fclose(dtbuku);
  	fclose(fpt);
  		dtbuku = fopen("daftarbuku.dat","wb");
  		fpt = fopen("Temp_Data.txt","rb");
  		while (fread(&buku,sizeof(buku),1, fpt)){
  			fwrite(&buku,sizeof(buku),1,dtbuku);
		  }
			fclose(dtbuku);
			fclose(fpt);
	Tampil_File();
	menudaftar();
}

//=================================================================== Prosedur untuk menghapus semua data buku ==================================================================
void hapusAllData(data_buku buku){
	char a[20][26];
	int count = 0;
	char t[26];
	int i,j,c;
	FILE *fpt;
	dtbuku = fopen("daftarbuku.dat","rb");
	fpt = fopen("Temp_Data.txt","wb");
	while (fread(&buku, sizeof(buku),1,dtbuku)){
		strcpy(a[count],buku.judul);
		count++;
	}
	
	c = count;
	for (i = 0; i<count -1;i++){
		for (j = i + 1; j<count; j++){
			if (a[i]>a[j]){
				strcpy(t,a[i]);
				strcpy(a[i],a[j]);
				strcpy(a[j],t);
			}
		}
	}
	count = c;
	for (i = 0; i<count; i++){
		rewind(dtbuku);
		while (fread(&buku, sizeof(buku),1,dtbuku)){
			if (a[i]==buku.judul){
				fwrite(&buku, sizeof(buku),1,fpt);
			}
		}
	}
	fclose(dtbuku);
  	fclose(fpt);
  		dtbuku = fopen("daftarbuku.dat","wb");
  		fpt = fopen("Temp_Data.txt","rb");
  		while (fread(&buku,sizeof(buku),1, fpt)){
  			fwrite(&buku,sizeof(buku),1,dtbuku);
		  }
			fclose(dtbuku);
			fclose(fpt);
	Tampil_File();
	menudaftar();
}

//======================================================================= Prosedur Sorting Buku berdasarkan Kode ================================================================
void sortKode(data_buku buku){
	int a[20];
	int count = 0;
	int i,j,t,c;
	FILE *fpt;
	dtbuku = fopen("daftarbuku.dat","rb");
	fpt = fopen("Temp_Data.txt","wb");
	while (fread(&buku, sizeof(buku),1,dtbuku)){
		a[count] = buku.kode;
		count++;
	}
	
	c = count;
	for (i = 0; i<count -1;i++){
		for (j = i + 1; j<count; j++){
			if (a[i]>a[j]){
				t = a[i];
				a[i] = a[j];
				a[j] = t;
			}
		}
	}
	count = c;
	for (i = 0; i<count; i++){
		rewind(dtbuku);
		while (fread(&buku, sizeof(buku),1,dtbuku)){
			if (a[i]==buku.kode){
				fwrite(&buku, sizeof(buku),1,fpt);
			}
		}
	}
	fclose(dtbuku);
  	fclose(fpt);
  		dtbuku = fopen("daftarbuku.dat","wb");
  		fpt = fopen("Temp_Data.txt","rb");
  		while (fread(&buku,sizeof(buku),1, fpt)){
  			fwrite(&buku,sizeof(buku),1,dtbuku);
		  }
			fclose(dtbuku);
			fclose(fpt);
	Tampil_File();
}


