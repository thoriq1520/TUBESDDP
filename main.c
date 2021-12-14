#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h> 
#include "fituradm.h"
#include "utama.h"
	
int main()
{
	console_clear_screen();
	int pil = 0; 																//variabel
	for (;;) 																	//pengulangan
	{
		system("color 0E");
		printf("\n\n\n\n\n\n\n\n\t\t\t\t==============================================\n");
		printf("\t\t\t\t\t[Welcome to Thorfinn Library]\n");
		printf("\t\t\t\t==============================================\n\n");
		printf("\t\t\t\t\t 1. Masuk sebagai admin \n");
		printf("\t\t\t\t\t 2. Daftar Buku \n");
		printf("\t\t\t\t\t 3. Panduan menggunakan aplikasi \n");
		printf("\t\t\t\t\t 4. Selesai \n");
		printf("\n\t\t\t\t\t Pilihan	: ");
		scanf("%d", &pil); fflush(stdin);											//input pilihan
		switch (pil) {
			case 1 : { 	loginpassword();

				break;
			}
			case 2 : { Tampil_File();
			menudaftar();
				break;
			}
			case 3 : { panduan();
				break;
			}
			case 4 : { exit(0);
			}
			default : {
			printf("\n\t\t\t\t\t Pilihan tidak ditemukan!");
			getch();
			system("cls");
			main();
			break;
			}
		}
	}	
}


