//Built-In File
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/*          NOTES TO TAKE
=> Type 0 = admin, Type 1 = user
*/
//DEKLARASI VARIABEL GLOBAL
int max = 3;

//DEKLARASI DATA UNTUK USER
struct account{
    char nama[120];
    char usn[120];
    char password[120];
    long int saldo;
}dataUser;

struct riwayat{
    char nama[120];
    char namaFilm[120];
    long int payment;
    float rating;
};

//DEKLARASI STRUCT DATA FILM
struct waktu{
    int jam;
    int menit;
};

struct tanggal{
    int hari;
    int bulan;
    int tahun;
};

struct data_film{
    char nama[250];
    char deskripsi[1000];
    struct tanggal tgl_tayang;
    struct tanggal tgl_tayang_akhir;
    struct waktu wkt_tayang;
    struct waktu durasi;
    float rating;
};

//DEKLARASI FUNCTION UMUM
void logo();
void halUtama();
void daftarAkun();
void masukAkun();

//DEKLARASI FUNCTION ADMIN
void loginAdmin(int maxLog);
void menuAdmin();
void tambahFilm();
void riwayatPembelian();
void ulasanFilm();
void lihatAkun();
void hapusAkun();
void topUp();

//DEKLARASI FUNCTION USER
void loginUser(int maxLog);
void menuUser(char *nama);
void lihatFilm(char *user);

int main(){
    halUtama();
}

//DEKLARASI SPESIFIK UNTUK FUNGSI DIATAS

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
    system("cls");
    int pilih;

    int invalid = 0;
    do{
        logo();
        puts("                                      pilihan : ");
        puts("                              1. Daftar akun");
        puts("                              2. Masuk akun");
        puts("                              0. Keluar");
        printf("\n                              Pilih : "); scanf("%d", &pilih); getchar();
        
        switch(pilih){
        case 0:
            exit(0);
            break;
        case 1:
            daftarAkun();
            break;
        case 2:
            masukAkun();
            break;
        default :
            printf("                           Pilihan salah! Coba lagi!");
            getchar();
            invalid = 1;
            break;
        }
    }while(invalid == 1);

}

void daftarAkun(){
    system("cls");
    struct account dataBaru;

    FILE *dataUser;
    dataUser = fopen("infoPengguna.dat", "ab");

    logo();
    puts("================ INFORMASI PENDAFTARAN =================\n");
    printf("Masukkan nickname : "); gets(dataBaru.nama);
    printf("Masukkan Username : "); gets(dataBaru.usn);
    printf("Masukkan password : "); gets(dataBaru.password);
    printf("Masukkan saldo    : "); scanf("%d", &dataBaru.saldo);
    
    if(fwrite(&dataBaru, sizeof(dataBaru), 1, dataUser) == 1){
        printf("Data berhasil disimpan! Silahkan login dengan menekan tombol apa saja");
        getchar();
    }
    fclose(dataUser);
    halUtama();
}

void masukAkun(){
    int pilih;
    pilih = 0;

    do{
        system("cls");
        logo();
        printf("Anda akan masuk sebagai :\n1. Admin\n2. Pembeli\nSilahkan pilih : ");scanf("%d", &pilih); getchar();

        switch(pilih){
            case 1:
                loginAdmin(max);
                break;
            case 2:
                loginUser(max);
                break;
            default:
                getchar();
                printf("Pilihan salah! Coba lagi!\n");
                break;
        }
    }while(pilih != 1 || pilih != 2);    
}

//DEKLARASI SPESIFIK FUNCTION ADMIN
void loginAdmin(int maxLog){
    system("cls");
    struct account input;
    int valid;

    logo();
    puts("================ INFORMASI MASUK =================\n");
    printf("Masukkan Username : "); gets(input.usn);
    printf("Masukkan password : "); gets(input.password);

    if(strcmp(input.usn, "admin") == 0 && strcmp(input.password, "admin1230") == 0){
        menuAdmin();
    }else{
        if(maxLog > 0){
            system("cls");
            valid = 0;

            logo();
            printf("Informasi masuk salah! Kesempatan login tersisa %d lagi", maxLog-1);
            getchar();
            loginAdmin(maxLog-1);
        }else{
            printf("Maaf, kesempatan login sudah habis!");
        }
    }

}

void menuAdmin(){
    system("cls");
    int pilih;
    int invalid;
    int keluar;

    do{
        invalid = 0;

        logo();
        puts("Selamat datang, Admin! Berikut adalah menu yang dapat dipilih : ");
        
        puts("FITUR PILIHAN FILM : ");
        puts("1. Tambah Film"); //FITUR TERMASUK MENAMBAHKAN WAKTU TAYANG
        puts("2. Lihat Riwayat Pembelian");
        puts("3. Lihat Ulasan Film\n");
        
        puts("FITUR PILIHAN AKUN");
        puts("4. Lihat Akun Customer");
        puts("5. Hapus Akun Customer");
        puts("6. Top Up Saldo\n");

        puts("KELUAR");
        puts("7. KELUAR DARI AKUN");
        puts("8. KELUAR DARI APLIKASI");

        printf("Silahkan pilih : "); scanf("%d", &pilih); getchar();

        switch(pilih){
            case 1:
                tambahFilm();
                break;
            case 2:
                riwayatPembelian();
                break;
            case 3:
                ulasanFilm();
                break;
            case 4:
                lihatAkun();
                break;
            case 5:
                hapusAkun();
                break;
            case 6 : 
                topUp();
                break;
            case 7:
                invalid = 0;
                do{
                    logo();
                    puts("Apakah anda yakin ingin keluar dari akun?\n1. YA\n2. TIDAK"); 
                    scanf("%d", &keluar);

                    if(keluar == 1){
                        halUtama();
                    }else if(keluar == 2){
                        menuAdmin();
                    }else{
                        invalid = 1;
                        printf("Pilihan salah! Coba lagi!");
                    }
                }while(invalid == 1);
                break;
            case 8 :
                invalid = 0;
                do{
                    logo();
                    puts("Apakah anda yakin ingin keluar dari APLIKASI? 1. YA\n2. TIDAK"); 
                    puts("===============================================================");
                    puts("NOTE : JIKA ANDA MENEKAN 'TIDAK', MAKA MENU AKAN KEMBALI KE MENU\nPILIHAN ADMIN");
                    scanf("%d", &keluar);

                    if(keluar == 1){
                        exit(0);
                    }else if(keluar == 2){
                        menuAdmin();
                    }else{
                        invalid = 1;
                        printf("Pilihan salah! Coba lagi!");
                    }
                }while(invalid == 1);
                break;
            default:
                invalid = 1;
                puts("Pilihan salah! Coba lagi!");
                getchar();
                break;
        }
    }while(invalid == 1);
}

void tambahFilm(){
    //MENCARI DAN MEMBUKA FILE
    system("cls");
    logo();
    FILE *daftar_film;
    daftar_film = fopen("daftar_film.dat", "ab");

    //VARIABEL PENTING
    struct data_film *film_baru;
    int pilih, banyak_film;
    int invalid; invalid = 0;

    //VERIFIKASI JUMLAH FILM YANG AKAN DIMASUKKAN
    printf("Masukkan jumlah film yang ingin didaftarkan : "); scanf("%d", &banyak_film); getchar();
    
    //PROSES PENGALOKASIAN MEMORI UNTUK MENYIMPAN DATA FILM
    film_baru = (struct data_film *)malloc(banyak_film * sizeof(struct data_film));

    //PROSES INPUT INFORMASI FILM
    for(int a = 0; a < banyak_film; a++){
        printf("======================== FILM KE-%d ========================\n", a+1);    
        printf("Masukkan judul film           : "); gets(film_baru[a].nama);
        printf("Masukkan deskripsi film       : "); gets(film_baru[a].deskripsi);
        printf("Masukkan tanggal tayang       :"); scanf("%d %d %d", &film_baru[a].tgl_tayang.hari, &film_baru[a].tgl_tayang.bulan, &film_baru[a].tgl_tayang.tahun);
        printf("Masukkan tanggal tayang akhir :"); scanf("%d %d %d", &film_baru[a].tgl_tayang_akhir.hari, &film_baru[a].tgl_tayang_akhir.bulan, &film_baru[a].tgl_tayang_akhir.tahun);
        printf("Masukkan durasi film          :"); scanf("%d %d", &film_baru[a].durasi.jam, &film_baru[a].durasi.menit); getchar();
        film_baru->rating = 0;
        printf("\n");
    }

    for (int a = 0; a < banyak_film; a++) {
        fwrite(&film_baru[a], sizeof(struct data_film), 1, daftar_film);
    }

    free(film_baru);
    fclose(daftar_film);

    printf("Data film berhasil disimpan!\n");

        /*
        system("cls");
        //PENGECEKAN DATA FILM
        puts("Berikut adalah informasi film yang akan di cek datanya : ");
        printf("1. Judul                         :\n%s\n", film_baru.nama);
        printf("2. Deskripsi                     :\n%s\n", film_baru.deskripsi);
        printf("3. Masukkan tanggal tayang       :\n%d %d %d\n", &film_baru.tgl_tayang.hari, &film_baru.tgl_tayang.bulan, &film_baru.tgl_tayang.tahun);
        printf("4. Masukkan tanggal tayang akhir :\n%d %d %d", &film_baru.tgl_tayang_akhir.hari, &film_baru.tgl_tayang_akhir.bulan, &film_baru.tgl_tayang_akhir.tahun);
        printf("5. Masukkan durasi film          :\n%d %d", &film_baru.durasi.jam, &film_baru.durasi.menit);

        puts("Apakah data film diatas sudah benar? 1. YA\n2. TIDAK\nPilih : ");
        puts("NOTE : Jika ada data yang tidak benar, silahkan tekan TIDAK dan pilih angka yang\nakan direvisi informasinya. Urutannya ada seperti yang ada diatas");
        scanf("%d", &pilih);       
        */
    puts("Tekan tombol apa saja untuk kembali ke menu admin..."); 
    getchar();
    menuAdmin();
}

void riwayatPembelian(){
    logo();
}

void ulasanFilm(){
    logo();
    
    //FILE DAN VARIABEL
    FILE *daftar_film;

    struct data_film data_film;

    //BUKA DATA FILM
    daftar_film = fopen("daftar_film.dat", "rb");
    if(daftar_film == NULL){
        printf("Belum ada ulasan film apapun. Yay!");
    }else{
        if(fread(&data_film, sizeof(data_film), 1, daftar_film) == 1){
            puts("Ulasan Film dari : ");
            printf("1. Judul Film                    :\n%s\n", data_film.nama);
            printf("2. Deskripsi                     :\n%s\n", data_film.deskripsi);
        }
    }
    fclose(daftar_film);
}

void lihatAkun(){
    logo();

    //FILE
    FILE *data_user;
    data_user = fopen("data_user.dat", "rb");
}

void hapusAkun(){
    //DEFINE VARIABLES
    struct account hapus_akun;
    char cari_akun[250];

    system("cls");
    logo();
    puts("MENU HAPUS AKUN ");
    printf("Silahkan masukkan username : "); gets(cari_akun);

    FILE *data_user; 
    FILE *data_user_baru;
    data_user = fopen("data_user.dat", "rb");
    data_user_baru = fopen("data_user1.dat", "rb");

    while(fread(&hapus_akun, sizeof(hapus_akun), 1, data_user) == 1){
        if(strcmp(cari_akun, hapus_akun.usn) != 0){
            fwrite(&hapus_akun, sizeof(hapus_akun), 1, data_user_baru);
        }
    }

    fclose(data_user);
    fclose(data_user_baru);
    remove("data_user.dat");
    rename("data_user1.dat", "data_user.dat");

}

void topUp(){
    //DEFINE VARIABLES
    struct account cari_akun;
    char key_cari[250];
    int valid;
    long int saldo_masuk;

    system("cls");
    logo();
    puts("MENU TOP UP ");
    printf("Silahkan masukkan username : "); gets(key_cari);

    FILE *data_user; 
    data_user = fopen("infoPengguna.dat", "ab+");
    valid = 0;

        while(fread(&cari_akun, sizeof(cari_akun), 1, data_user) == 1){
            if(strcmp(key_cari, cari_akun.usn) == 0){
                valid = 1;
                break;
            }else{
                valid = 0;
            }
        }

    if(valid==1){
        printf("Masukkan saldo yang akan diisi ke akun : "); scanf("%d",&saldo_masuk);
        cari_akun.saldo+=saldo_masuk;

        if(fwrite(&cari_akun, sizeof(cari_akun), 1, data_user)!=0){
            puts("Pengisian saldo berhasil!\n");
        }
    }else{
        printf("Data yang dicari tidak ditemukan\n");
    }

    fclose(data_user);

    puts("Tekan tombol mana saja untuk kembali ke menu utama...");
    getchar();
    menuAdmin();
}

//DEKLARASI SPESIFIK FUNCTION USER
void loginUser(int maxLog){
    system("cls");

    //DEFINE VARIABLE
    struct account input;
    struct account find;
    FILE *cari_data;
    int valid;

    //PROSES DATA
    cari_data = fopen("infoPengguna.dat", "rb");

    logo();
    puts("==================== INFORMASI MASUK =====================\n");
    printf("Masukkan Username : "); gets(input.usn);
    printf("Masukkan password : "); gets(input.password);

    while(fread(&find, sizeof(find), 1, cari_data) == 1){
        if(strcmp(input.usn, find.usn) == 0 && strcmp(input.password, find.password) == 0){
            valid = 1;
            break;
        }else{
            if(maxLog > 0){
                system("cls");
                valid = 0;

                logo();
                printf("Informasi masuk salah! Kesempatan login tersisa %d lagi", maxLog-1);
                getchar();
                loginUser(maxLog-1);
            }else{
                printf("Maaf, kesempatan login sudah habis!");
            }
        }
    }

    fclose(cari_data);

    if(valid == 1){
        menuUser(find.nama);
    }
}

void menuUser(char *user){
    system("cls");

    //DEKLARASI VARIABEL 
    int pilih;
    int invalid;

    invalid = 0;

    do{
        logo();
        printf("Selamat datang, %s! Berikut adalah menu yang bisa kamu pilih\n", user);
        puts("1. Lihat Film Yang Tayang");
        puts("2. Pesan Tiket Nonton");
        puts("3. Beli Snack Buat Nonton");
        puts("4. Lihat Riwayat Film Yang Pernah Ditonton");
        puts("5. Ganti Password");

        printf("Silahkan pilih : "); scanf("%d", &pilih);

        switch(pilih){
            case 1:
                lihatFilm(user);
            default :
                printf("Pilihan Salah! Coba lagi pilih");
        }
    }while(invalid == 1);
}

void lihatFilm(char *user){
    system("cls");
    logo();
    struct data_film film_baru;
    FILE *daftar_film;

    daftar_film = fopen("daftar_film.dat", "rb");
    if(daftar_film == NULL){
        printf("Wah, kayaknya belum ada film baru nih %s. Maaf ya...\n", user);
        getchar();
    }else{
        printf("Selamat datang, %s! Silahkan cek film yang cocok untukmu ya!\n", user);
        printf("\t| JUDUL\t| TGL TAYANG\t| TGL TAYANG AKHIR | DURASI\n");
        while(fread(&film_baru, sizeof(film_baru), 1, daftar_film) != 0){
            printf("\t| %s\t| %d:%d:%d\t\t| %d:%d:%d\t\t   | %d:%d\n", film_baru.nama, film_baru.tgl_tayang.hari, film_baru.tgl_tayang.bulan, film_baru.tgl_tayang.tahun, film_baru.tgl_tayang_akhir.hari, film_baru.tgl_tayang_akhir.bulan, film_baru.tgl_tayang_akhir.tahun, film_baru.durasi.jam, film_baru.durasi.menit);
            
            /*
            printf("1. Judul                :\n%s\n", film_baru.nama);
            printf("2. Deskripsi            :\n%s\n", film_baru.deskripsi);
            printf("3. Tanggal tayang       :\n%d %d %d\n", &film_baru.tgl_tayang.hari, &film_baru.tgl_tayang.bulan, &film_baru.tgl_tayang.tahun);
            printf("4. Tanggal tayang akhir :\n%d %d %d", &film_baru.tgl_tayang_akhir.hari, &film_baru.tgl_tayang_akhir.bulan, &film_baru.tgl_tayang_akhir.tahun);
            printf("5. Durasi film          :\n%d %d", &film_baru.durasi.jam, &film_baru.durasi.menit);
            */
        }
        getchar();
    }

    puts("Tekan tombol apa saja untuk kembali ke menu pelanggan..."); 
    getchar();
    menuUser(user);
}

//DEKLARASI FUNGSI SPESIFIK FUNGSIONAL
