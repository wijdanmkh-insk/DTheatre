//Built-In File
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/*          NOTES TO TAKE
=> Type 0 = admin, Type 1 = user
*/
//DEKLARASI VARIABEL GLOBAL
int max = 3;
char genre[5][20] = {"Komedi", "Romance", "Horror", "Anak-anak", "Sci-Fi"};

//DEKLARASI DATA UNTUK USER
struct account{
    char nama[120];
    char usn[120];
    char password[120];
    long int saldo;
};

struct tiket{
    char jenis[20];
    long int harga;
    int stok;
    char lokasi[300];
};

//ANOTHER VARIABLES
struct waktu{
    int jam;
    int menit;
};

struct tanggal{
    int hari;
    int bulan;
    int tahun;
};

struct fnb{//MAKANAN DAN MINUMAN
    long int harga;
    int stok;
};  

struct riwayat{
    char nama[120];
    char usn[120];
    char namaFilm[120];
    char ulasan[300];
    int no_kursi;
    struct tiket pembelian_tiket;
    struct tanggal tgl_tonton;
    struct waktu wkt_tonton;
    struct fnb popcorn;
    struct fnb minuman;
    long int total;
    float rating;
};

//DEKLARASI STRUCT DATA FILM
struct data_film{
    char nama[250];
    char deskripsi[1000];
    char genre[20];
    struct tanggal tgl_tayang;
    struct tanggal tgl_tayang_akhir;
    struct waktu wkt_tayang;
    struct waktu durasi;
    struct tiket reguler;
    struct tiket premiere;
    float rating;
};

//DEKLARASI STRUCT KURSI
struct kursi{
    char judul[250];
    int no_kursi_reguler[6][8];
    int no_kursi_premier[3][5];
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
void menuUser(char *nama, char *usn);
void lihatFilm(char *user, char *usn);
void lihatFilmDetail(char *user, char *usn);
void pesanTiket(char *user, char *usn);
void beriUlasan(char *user, char *usn);
void cariFilm(char *user, char *usn);
void cariFilmGenre(char *user, char *usn);
void cariFilmJudul();
void gantiPass(char *user);

//DEKLARASI FUNGSI NON ROLE
void sortirFilm();
void invoice(struct riwayat *riwayat);

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
    struct account trackData;
    int dataSama;
    dataSama = 0;

    FILE *dataUser;
    dataUser = fopen("infoPengguna.dat", "ab+");

    logo();
    puts("================ INFORMASI PENDAFTARAN =================\n");
    printf("Masukkan nickname : "); gets(dataBaru.nama);
    printf("Masukkan Username : "); gets(dataBaru.usn);
    printf("Masukkan password : "); gets(dataBaru.password);
    dataBaru.saldo = 0;
    
    do{
        fseek(dataUser, 0, SEEK_SET);
        while(fread(&trackData, sizeof(trackData), 1, dataUser)!=0){
            if(strcmp(trackData.usn, dataBaru.usn)==0){
                dataSama = 1;
                break;
            }else{
                dataSama = 0;
            }
        }

        if(dataSama == 1){
            printf("Username yang anda ambil sudah ada! Silahkan pilih username yang lain!\n");
            printf("Username baru : "); gets(dataBaru.usn);
        }
    }while(dataSama==1);

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

    int genreN;
    //PROSES INPUT INFORMASI FILM
    for(int a = 0; a < banyak_film; a++){
        printf("======================== FILM KE-%d ========================\n", a+1);    
        printf("Masukkan judul film           : "); gets(film_baru[a].nama);
        printf("Masukkan deskripsi film       : "); gets(film_baru[a].deskripsi);
        printf("Silahkan masukkan genre film  : 1. Komedi 2. Romance 3. Horror 4. Anak-anak 5. Sci-Fi\nPilih : "); scanf("%d", &genreN); strcpy(film_baru->genre, genre[genreN]);
        printf("Masukkan tanggal tayang       : "); scanf("%d %d %d", &film_baru[a].tgl_tayang.hari, &film_baru[a].tgl_tayang.bulan, &film_baru[a].tgl_tayang.tahun);
        printf("Masukkan tanggal tayang akhir : "); scanf("%d %d %d", &film_baru[a].tgl_tayang_akhir.hari, &film_baru[a].tgl_tayang_akhir.bulan, &film_baru[a].tgl_tayang_akhir.tahun);
        printf("Masukkan durasi film          : "); scanf("%d %d", &film_baru[a].durasi.jam, &film_baru[a].durasi.menit); getchar();
        printf("Masukkan harga tiket reguler  : "); scanf("%ld", &film_baru->reguler.harga);
        printf("Masukkan stok tiket reguler   : "); scanf("%ld", &film_baru->reguler.stok);
        printf("Masukkan harga tiket premiere : "); scanf("%ld", &film_baru->premiere.harga); 
        printf("Masukkan stok tiket premiere : "); scanf("%ld", &film_baru->premiere.stok); getchar();
        film_baru->rating = 0;
        printf("\n");
    }

    for (int a = 0; a < banyak_film; a++) {
        fwrite(&film_baru[a], sizeof(struct data_film), 1, daftar_film);
    }

    free(film_baru);
    fclose(daftar_film);

    printf("Data film berhasil disimpan!\n");

    //PROSES SORTING FILM BERDASARKAN JUDUL DIMULAI DISINI
    sortirFilm();

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
    puts("LIHAT AKUN PENGGUNA");

    int count = 1;
    //STRUCT
    struct account lihat;

    //FILE
    FILE *data_user;
    data_user = fopen("infoPengguna.dat", "rb");

    while(fread(&lihat, sizeof(lihat), 1, data_user)!=0){
        printf("========== Data ke-%d\n ==============\n", count);
        printf("Nama     : %s\n", lihat.nama);
        printf("Username : %s\n", lihat.usn);
        printf("Saldo    : %ld\n\n", lihat.saldo);
        count++;
    }
    fclose(data_user);
    puts("Tekan tombol apa saja untuk kembali ke menu utama...");
    getchar();
    menuAdmin();

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
    valid = 0;
    cari_data = fopen("infoPengguna.dat", "rb");

    logo();
    puts("==================== INFORMASI MASUK =====================\n");
    printf("Masukkan Username : "); gets(input.usn);
    printf("Masukkan password : "); gets(input.password);

    while(fread(&find, sizeof(find), 1, cari_data) == 1){
        if(strcmp(input.usn, find.usn) == 0 && strcmp(input.password, find.password) == 0){
            valid = 1;
            break;
        }
    }

    fclose(cari_data);
    if(valid == 0){
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

    if(valid == 1){
        menuUser(find.nama, find.usn);
    }
}

void menuUser(char *user, char *usn){
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
        puts("3. Cari Film");
        puts("4. Lihat Detail Film");
        puts("4. Kasih Rating dan Ulasan");
        puts("5. Lihat Riwayat Film Yang Pernah Ditonton");
        puts("6. Ganti Password");

        printf("Silahkan pilih : "); scanf("%d", &pilih); getchar();

        switch(pilih){
            case 1:
                lihatFilm(user, usn);
                break;
            case 2:
                pesanTiket(user, usn);
                break;
            case 3:
                cariFilm(user, usn);
                break;
            case 4:
                lihatFilmDetail(user, usn);
            default :
                printf("Pilihan Salah! Coba lagi pilih");
        }
    }while(invalid == 1);
}

void lihatFilmDetail(char *user, char *usn){
    system("cls");
    logo();
    struct data_film cari;
    FILE *daftar_film;
    int count = 1;

    daftar_film = fopen("daftar_film.dat", "rb");

    puts("===================== HASIL PENCARIAN =====================");
    while(fread(&cari, sizeof(cari), 1, daftar_film) != 0){
        printf("========== FILM KE-%d ==========\n", count);
        printf("Judul film           : %s\n", cari.nama);
        printf("Deskripsi film       : %s\n", cari.deskripsi);
        printf("Genre film           : %s\n",cari.genre);
        printf("Tanggal tayang       : %d %d %d\n", cari.tgl_tayang.hari, cari.tgl_tayang.bulan, cari.tgl_tayang.tahun);
        printf("Tanggal tayang akhir : %d %d %d\n", cari.tgl_tayang_akhir.hari, cari.tgl_tayang_akhir.bulan, cari.tgl_tayang_akhir.tahun);
        printf("Durasi film          : %d %d\n", cari.durasi.jam, cari.durasi.menit); 
        printf("Harga tiket reguler  : %ld\n", cari.reguler.harga);
        printf("Stok tiket reguler   : %ld\n", cari.reguler.stok);
        printf("Harga tiket premiere : %ld\n", cari.premiere.harga); 
        printf("Stok tiket premiere  : %ld\n", cari.premiere.stok);
        printf("Rating film          : %.lf\n", cari.rating);
        count+=1;
    }

    fclose(daftar_film);

    printf("Tekan tombol apa saja untuk kembali ke menu utama...\n");
    getchar();
    menuUser(user, usn);
}

void lihatFilm(char *user, char *usn){
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
    }

    puts("Tekan tombol apa saja untuk kembali ke menu pelanggan..."); 
    getchar();
    menuUser(user, usn);
}

void pesanTiket(char *user, char *usn){
    //DEFINE VARIABLES
    struct account cari_akun;
    struct data_film cari_film;
    struct riwayat riwayat_pembelian;

    char cari[250];
    FILE *daftar_film;
    //FILE *infoPengguna;
    int found, pilih, valid;

    daftar_film = fopen("daftar_film.dat", "rb");
    //infoPengguna = fopen("infoPengguna.dat", "rb");

    logo();
    puts("MENU PEMESANAN TIKET");
    printf("Halo, %s! Kamu mau nonton apa?\nYuk cek film yang tersedia disini!\nCari : ", user); gets(cari);

    found = 0;
    while(fread(&cari_film, sizeof(cari_film), 1, daftar_film) != 0){
        if(strcmp(cari, cari_film.nama) == 0){
            found = 1;
            break;
        }else{
            found = 0;
        }
    }

    
    if(found == 1){
        logo();
        puts("------------- MENU PEMESANAN TIKET -------------");
        puts("Berikut adalah informasi mengenai film yang akan kamu beli tiketnya : ");
        printf("Judul film : %s\n", cari_film.nama);
        printf("Deskripsi  : %s\n", cari_film.deskripsi);
        printf("Durasi     : %d : %d\n\n", cari_film.durasi.jam, cari_film.durasi.menit);
        puts("KETERSEDIAAN TIKET");
        puts("Berikut adalah ketersediaan tiket beserta stoknya ya!");
        puts("--------------- TIKET REGULER  ---------------");
        printf("- Harga    : %ld\n", cari_film.reguler.harga);
        printf("- Stok     : %d\n", cari_film.reguler.stok);
        puts("--------------- TIKET PREMIERE ---------------");
        printf("- Harga    : %ld\n", cari_film.premiere.harga);
        printf("- Stok     : %d\n", cari_film.premiere.stok);
    }

    //SALIN DATA UNTUK DIPINDAHKAN KE INVOICE
    strcpy(riwayat_pembelian.namaFilm, cari_film.nama);

    //TANGGAL
    riwayat_pembelian.tgl_tonton.hari = cari_film.tgl_tayang.hari;
    riwayat_pembelian.tgl_tonton.bulan = cari_film.tgl_tayang.bulan;
    riwayat_pembelian.tgl_tonton.tahun = cari_film.tgl_tayang.tahun;

    //JAM
    riwayat_pembelian.wkt_tonton.jam = cari_film.wkt_tayang.jam;
    riwayat_pembelian.wkt_tonton.menit = cari_film.wkt_tayang.menit;


    fclose(daftar_film);
    getchar();
    valid = 1;
    do{
        //system("cls");
        logo();
        puts("MENU MEMILIH TIKET");
        puts("Silahkan pilih jenis tiket yang akan dibeli");
        puts("1. Tiket Reguler");
        puts("2. Tiket Premiere");
        printf("Pilih : "); scanf("%d", &pilih);

        switch(pilih){
            case 1:
                strcpy(riwayat_pembelian.pembelian_tiket.jenis, "Reguler");
                riwayat_pembelian.pembelian_tiket.harga = cari_film.reguler.harga;
                strcpy(riwayat_pembelian.pembelian_tiket.lokasi, "Gd A Asrama Putri");
                break;
            case 2:
                strcpy(riwayat_pembelian.pembelian_tiket.jenis, "Premiere");
                riwayat_pembelian.pembelian_tiket.harga=cari_film.premiere.harga;
                strcpy(riwayat_pembelian.pembelian_tiket.jenis, "Gd B Asrama Putri");
                break;
            default :
            valid = 0;
            printf("Pilihan Salah! Silahkan pilih lagi!");
        }
    }while(valid == 0);
    getchar();

    puts("Silahkan tentukan banyak tiket yang akan dibeli : ");
    printf("Jumlah tiket : "); scanf("%d", &riwayat_pembelian.pembelian_tiket.stok);

    valid = 1;
    do{
        //system("cls");
        logo();
        puts("MENU MEMILIH MAKANAN");
        printf("Apakah anda ingin membeli popcorn atau minuman?\n1. YA\n2. Tidak\nPilih :");
        scanf("%d", &pilih);

        switch(pilih){
            case 1:
            printf("Banyak popcorn yang akan dibeli : "); scanf("%d", &riwayat_pembelian.popcorn.stok);
            printf("Banyak minuman yang akan dibeli : "); scanf("%d", &riwayat_pembelian.minuman.stok);
            break;
        
            case 2:
            riwayat_pembelian.popcorn.stok = 0;
            riwayat_pembelian.minuman.stok = 0;
            break;

            default:
            printf("Pilihan salah!");
        }
    }while(valid ==0);

    fclose(daftar_film);
    getchar();
    logo();
    invoice(&riwayat_pembelian);

    printf("Tekan tombol mana saja untuk kembali ke menu user");
    getchar();
    menuUser(user, usn);
}

void beriUlasan(char *user, char *usn){
    //DEFINE VARIABLES
    FILE *ulasan;
    FILE *riwayat_pembelian;
    FILE *daftar_film;

    struct data_film semua_film[100];
    struct riwayat ulasan_user;

    ulasan = fopen("daftar_ulasan.dat", "ab");
    riwayat_pembelian = fopen("riwayat_pembelian.dat", "rb");
    daftar_film = fopen("daftar_film.dat", "rb");

    while(fread(&ulasan_user, sizeof(ulasan_user), 1, riwayat_pembelian) == 1){
        if(strcmp(ulasan_user.usn, usn)==0){
            if(ulasan_user.rating == 0){

            }
        }
    }

    system("cls");
    logo();
    puts("SISTEM BERI ULASAN");
    printf("Halo, %s! Karena kamu sudah menonton film yang ada dibawah, tolong kasih ulasannya ya!\n", user);
}

void cariFilm(char *user, char *usn){
    //DEKLARASI VARIABEL
    int pilih, valid; 

    valid = 1;
    do{
        system("cls");
        logo();
        printf("Selamat datang, %s! Kamu mau cari film pake judul atau genre nih?\n1. Judul\n2. Genre\nPilih : ", user); scanf("%d", &pilih); getchar();

        switch(pilih){
            case 1:
                cariFilmJudul(user, usn);
                break;
            case 2:
                cariFilmGenre(user, usn);
                break;
            default : 
                valid = 0;
                printf("Pilihan salah!");
        }
    }while(valid == 0);
}

void cariFilmJudul(char *user, char *usn){
    //DEKLARASIKAN VARIABEL
    FILE *daftar_film;
    struct data_film cari;
    char keywords[250];
    int found, lagi;


    daftar_film = fopen("daftar_film.dat", "rb");
    system("cls");
    logo();

    found = 0;
    lagi = 0;
    
    do{
        puts("======================== CARI FILM BERDASARKAN JUDUL ==========================");
        printf("Masukkan judul film : "); gets(keywords);

        while(fread(&cari, sizeof(cari), 1, daftar_film) != 0){
            if(strcmp(keywords, cari.nama) == 0){
                found = 1;
                break;
            }else{
                found = 0;
            }
        }

        system("cls");
        logo();
        puts("===================== HASIL PENCARIAN BERDASARKAN JUDUL =====================");
        if(found == 1){
            printf("Judul film           : %s\n", cari.nama);
            printf("Deskripsi film       : %s\n", cari.deskripsi);
            printf("Genre film           : %s\n");
            printf("Tanggal tayang       : %d %d %d\n", cari.tgl_tayang.hari, cari.tgl_tayang.bulan, cari.tgl_tayang.tahun);
            printf("Tanggal tayang akhir : %d %d %d\n"); scanf("%d %d %d", cari.tgl_tayang_akhir.hari, cari.tgl_tayang_akhir.bulan, cari.tgl_tayang_akhir.tahun);
            printf("Durasi film          : %d %d %d\n", cari.durasi.jam, cari.durasi.menit); getchar();
            printf("Harga tiket reguler  : %ld\n", cari.reguler.harga);
            printf("Stok tiket reguler   : %ld\n", cari.reguler.stok);
            printf("Harga tiket premiere : %ld\n", cari.premiere.harga); 
            printf("Stok tiket premiere  : %ld\n", cari.premiere.stok);
            printf("Rating film          : %.lf\n", cari.rating);
            lagi = 0;
        }else{
            puts("Judul film tidak ditemukan. Ingin mencari lagi? 1. YA\n2. TIDAK\nPilih : "); scanf("%d", &lagi); getchar();
            if(lagi == 1){
                lagi = 1;
            }else if(lagi == 2){
                lagi = 0;
            }
        }
    }while(lagi == 1);

    puts("Tekan tombol apa saja untuk kembali ke menu utama...");
    getchar();
    menuUser(user, usn);
}

void cariFilmGenre(char *user, char *usn){
    //DEKLARASIKAN VARIABEL
    FILE *daftar_film;
    struct data_film cari;
    int cariGenre;
    int found, lagi;


    daftar_film = fopen("daftar_film.dat", "rb");
    system("cls");
    logo();

    found = 0;
    lagi = 0;
    
    do{
        puts("======================== CARI FILM BERDASARKAN GENRE ==========================");
        puts("Genre tersedia : 1. Komedi 2. Romance 3. Horror 4. Anak-anak 5. Sci-Fi");
        printf("Masukkan genre film "); scanf("%d", &cariGenre); getchar();

        while(fread(&cari, sizeof(cari), 1, daftar_film) != 0){
            if(strcmp(genre[cariGenre], cari.genre) == 0){
                found = 1;
                break;
            }else{
                found = 0;
            }
        }

        system("cls");
        logo();
        puts("===================== HASIL PENCARIAN BERDASARKAN JUDUL =====================");
        if(found == 1){
            printf("Judul film           : %s\n", cari.nama);
            printf("Deskripsi film       : %s\n", cari.deskripsi);
            printf("Genre film           : %s\n");
            printf("Tanggal tayang       : %d %d %d\n", cari.tgl_tayang.hari, cari.tgl_tayang.bulan, cari.tgl_tayang.tahun);
            printf("Tanggal tayang akhir : %d %d %d\n"); scanf("%d %d %d", cari.tgl_tayang_akhir.hari, cari.tgl_tayang_akhir.bulan, cari.tgl_tayang_akhir.tahun);
            printf("Durasi film          : %d %d %d\n", cari.durasi.jam, cari.durasi.menit); getchar();
            printf("Harga tiket reguler  : %ld\n", cari.reguler.harga);
            printf("Stok tiket reguler   : %ld\n", cari.reguler.stok);
            printf("Harga tiket premiere : %ld\n", cari.premiere.harga); 
            printf("Stok tiket premiere  : %ld\n", cari.premiere.stok);
            printf("Rating film          : %.lf\n", cari.rating);
        }else{
            puts("Judul film tidak ditemukan. Ingin mencari lagi? 1. YA\n2. TIDAK\nPilih : "); scanf("%d", &lagi); getchar();
        }
    }while(!(lagi-1) == 1);

    puts("Tekan tombol apa saja untuk kembali ke menu utama...");
    getchar();
    menuUser(user, usn);
}

//DEKLARASI FUNGSI SPESIFIK FUNGSIONAL
void invoice(struct riwayat *riwayat){
    //DEFINE VARIABLES
    FILE *simpan_riwayat;

    simpan_riwayat = fopen("riwayat_pembelian.dat", "ab");

    puts("======================= BUKTI PEMBAYARAN ===========================");
    puts("-------------------- DESKRIPSI SINGKAT TIKET ------------------------");
    printf("Nama Film       : %s\n", riwayat->namaFilm);
    printf("Tgl Tonton      : %d-%d-%d\n", riwayat->tgl_tonton.hari, riwayat->tgl_tonton.bulan, riwayat->tgl_tonton.tahun);
    printf("Wkt Tonton      : %dJm: %dMin\n\n", riwayat->wkt_tonton.jam, riwayat->wkt_tonton.menit);
    printf("Lokasi bioskop  : %s\n", riwayat->pembelian_tiket.lokasi);

    puts("---------------------- PEMBELIAN MAKANAN ---------------------------");
    printf("Popcorn (%d) : %d\n",riwayat->popcorn.stok, 50000*riwayat->popcorn.stok);
    printf("Minuman (%d) : %d\n",riwayat->minuman.stok, 25000*riwayat->minuman.stok);
    riwayat->total = 50000*riwayat->popcorn.stok+25000*riwayat->minuman.stok+riwayat->pembelian_tiket.harga;
    printf("Total        : %ld\n", riwayat->total);

    fwrite(riwayat, sizeof(struct riwayat), 1, simpan_riwayat);
    fclose(simpan_riwayat);
}

void sortirFilm(){
    //DEKLARASIKAN VARIABEL
    FILE *daftar_film;
    struct data_film *data_film;
    struct data_film cari;
    struct data_film temp;
    int count = 0;

    data_film = (struct data_film*)malloc(100 * sizeof(struct data_film));
    daftar_film = fopen("daftar_film.dat", "ab");

    while(fread(&cari, sizeof(cari), 1, daftar_film) != 0){
        data_film[count] = cari;
        count++;
    }

    for(int a=0;a<count;a++){
        for(int b=0;b<count;b++){
            if(strcmp(data_film[a].nama, data_film[a+1].nama)<0){
                temp = data_film[a];
                data_film[a] = data_film[a+1];
                data_film[a+1] = temp;
            }
        }
    }
    
    for(int a=0;a<count;a++){
        fwrite(&data_film[a], sizeof(struct data_film[a]), 1, daftar_film);
    }

    fclose(daftar_film);
}

