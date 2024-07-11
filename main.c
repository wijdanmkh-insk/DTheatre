#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/*          NOTES TO TAKE
=> Type 0 = admin, Type 1 = user
*/

//DEKLARASI DATA UNTUK USER
struct account{
    char nama[120];
    char usn[120];
    char password[120];
    int type;
}dataUser;

//DEKLARASI AKUN ADMIN
struct account admin = {"admin", "admin", "admin1230", 0};

//DEKLARASI FUNCTION UMUM
void logo(){
    puts("========================================================================================");
    puts("              ____  _ _____ _                _");            
    puts("             |  _ \\( )_   _| |__   ___  __ _| |_ _ __ ___"); 
    puts("             | | | |/  | | | '_ \\ / _ \\/ _` | __| '__/ _ \\");
    puts("             | |_| |   | | | | | |  __/ (_| | |_| | |  __/");
    puts("             |____/    |_| |_| |_|\\___|\\__,_|\\__|_|  \\___|");
    puts("========================================================================================");
}

void halUtama(){
    int pilih;
    logo();
    puts("                                      pilihan : ");
    puts("                              1. Daftar akun");
    puts("                              2. Masuk akun");
    puts("                              0. Keluar");
    printf("\n                              Pilih : "); scanf("%d", &pilih);

    if(pilih == 1){
        daftarAkun();
    }
}
void daftarAkun(){
    struct account dataBaru;

    FILE *dataUser;
    dataUser = fopen("infoPengguna.dat", "ab");

    puts("================ INFORMASI PENDAFTARAN =================\n");
    printf("Masukkan username   : "); gets(dataBaru.nama);
    printf("Masukkan Username : "); gets(dataBaru.usn);
    printf("Masukkan password : "); gets(dataBaru.password);
    dataBaru.type = 1;
    
    if(fwrite(&dataBaru, sizeof(dataBaru), 1, dataUser) == 1){
        printf("Data berhasil disimpan! Silahkan login");
    }
}
//DEKLARASI FUNCTION ADMIN
//DEKLARASI FUNCTION USER

int main(){
    halUtama();
}

//DEKLARASI SPESIFIK UNTUK FUNGSI DIATAS