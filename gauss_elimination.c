/*
===============================================================================
                    PROGRAM ELIMINASI GAUSS
                  Sistem Persamaan Linear
===============================================================================
Program ini dibuat untuk PEMULA yang baru belajar bahasa C
Struktur program dibuat sesederhana mungkin agar mudah dipahami
===============================================================================
*/

#include <stdio.h>

/*
===============================================================================
FUNGSI-FUNGSI PEMBANTU (Helper Functions)
===============================================================================
*/

/* Fungsi untuk membersihkan buffer input */
/* Berguna agar program tidak skip saat menerima input */
void bersihkanBuffer() {
    while(getchar() != '\n');
}

/* Fungsi untuk pause program (menunggu user tekan Enter) */
void tekanEnter() {
    printf("\nTekan ENTER untuk melanjutkan...");
    getchar();
    printf("\n");
}

/*
===============================================================================
FUNGSI 1: INPUT MATRIKS
===============================================================================
Fungsi ini digunakan untuk menerima input dari user
User akan memasukkan angka-angka untuk matriks augmented
*/

void inputMatriks(int n, float mat[10][11]) {
    int baris, kolom;
    
    printf("\n");
    printf("=======================================================\n");
    printf("           INPUT MATRIKS AUGMENTED\n");
    printf("=======================================================\n");
    printf("Anda akan memasukkan %d baris\n", n);
    printf("Setiap baris berisi %d angka (pisahkan dengan SPASI)\n", n+1);
    printf("Setelah selesai 1 baris, tekan ENTER\n");
    printf("=======================================================\n\n");
    
    /* Contoh untuk membantu user */
    printf("Contoh input untuk sistem 3 persamaan:\n");
    printf("  2x + 1y - 1z = 8  -->  ketik: 2 1 -1 8\n");
    printf("-------------------------------------------------------\n\n");
    
    /* Proses input untuk setiap baris */
    for(baris = 0; baris < n; baris++) {
        printf("Baris ke-%d: ", baris + 1);
        
        /* Input setiap elemen dalam baris */
        for(kolom = 0; kolom <= n; kolom++) {
            scanf("%f", &mat[baris][kolom]);
        }
        bersihkanBuffer(); /* Bersihkan buffer setelah input */
    }
    
    printf("\nSemua data berhasil diinput!\n");
    tekanEnter();
}

/*
===============================================================================
FUNGSI 2: TAMPILKAN MATRIKS
===============================================================================
Fungsi ini menampilkan matriks ke layar dengan format yang rapi
*/

void tampilkanMatriks(int n, float mat[10][11], char judul[]) {
    int baris, kolom;
    
    printf("=======================================================\n");
    printf("  %s\n", judul);
    printf("=======================================================\n\n");
    
    /* Tampilkan setiap baris matriks */
    for(baris = 0; baris < n; baris++) {
        printf("[ ");
        
        /* Tampilkan koefisien (kolom A) */
        for(kolom = 0; kolom < n; kolom++) {
            printf("%7.2f ", mat[baris][kolom]);
        }
        
        /* Garis pemisah sebelum konstanta */
        printf("|");
        
        /* Tampilkan konstanta (kolom b) */
        printf("%7.2f ", mat[baris][n]);
        
        printf("]\n");
    }
    
    printf("\n");
}

/*
===============================================================================
FUNGSI 3: PROSES ELIMINASI GAUSS
===============================================================================
Fungsi ini mengubah matriks menjadi bentuk segitiga atas
Caranya: membuat angka di bawah diagonal utama menjadi 0
*/

void prosesEliminasi(int n, float mat[10][11]) {
    int pivotBaris, targetBaris, kolom;
    float pengali;
    
    printf("=======================================================\n");
    printf("        PROSES ELIMINASI GAUSS DIMULAI\n");
    printf("=======================================================\n\n");
    
    /* Loop untuk setiap pivot (elemen diagonal) */
    for(pivotBaris = 0; pivotBaris < n-1; pivotBaris++) {
        
        printf("--- LANGKAH %d ---\n", pivotBaris + 1);
        printf("Membuat angka di bawah pivot baris %d menjadi 0\n\n", pivotBaris + 1);
        
        /* Loop untuk setiap baris di bawah pivot */
        for(targetBaris = pivotBaris + 1; targetBaris < n; targetBaris++) {
            
            /* Hitung angka pengali */
            pengali = mat[targetBaris][pivotBaris] / mat[pivotBaris][pivotBaris];
            
            printf("  Baris %d dikurangi (%.2f x Baris %d)\n", 
                   targetBaris+1, pengali, pivotBaris+1);
            
            /* Lakukan operasi: Baris_target = Baris_target - (pengali x Baris_pivot) */
            for(kolom = pivotBaris; kolom <= n; kolom++) {
                mat[targetBaris][kolom] = mat[targetBaris][kolom] - (pengali * mat[pivotBaris][kolom]);
            }
        }
        
        printf("\n");
    }
    
    printf("Eliminasi selesai! Matriks sudah berbentuk segitiga atas.\n");
    tekanEnter();
}

/*
===============================================================================
FUNGSI 4: SUBSTITUSI BALIK
===============================================================================
Fungsi ini menghitung nilai x, y, z, ... dari matriks segitiga atas
Caranya: mulai dari baris paling bawah, hitung ke atas
*/

void hitungSolusi(int n, float mat[10][11], float hasil[10]) {
    int baris, kolom;
    float jumlah;
    
    printf("=======================================================\n");
    printf("         MENGHITUNG SOLUSI (Substitusi Balik)\n");
    printf("=======================================================\n\n");
    
    /* Mulai dari baris terakhir, naik ke atas */
    for(baris = n-1; baris >= 0; baris--) {
        
        /* Ambil nilai konstanta dari kolom terakhir */
        jumlah = mat[baris][n];
        
        printf("Menghitung x%d:\n", baris+1);
        printf("  Mulai dari: %.2f\n", jumlah);
        
        /* Kurangi dengan hasil variabel yang sudah diketahui */
        for(kolom = baris+1; kolom < n; kolom++) {
            jumlah = jumlah - (mat[baris][kolom] * hasil[kolom]);
            printf("  Kurangi: %.2f x %.2f = %.2f\n", 
                   mat[baris][kolom], hasil[kolom], mat[baris][kolom] * hasil[kolom]);
        }
        
        /* Bagi dengan koefisien diagonal */
        hasil[baris] = jumlah / mat[baris][baris];
        
        printf("  Bagi dengan: %.2f\n", mat[baris][baris]);
        printf("  --> x%d = %.4f\n\n", baris+1, hasil[baris]);
    }
    
    tekanEnter();
}

/*
===============================================================================
FUNGSI 5: TAMPILKAN HASIL AKHIR
===============================================================================
Fungsi ini menampilkan solusi akhir dengan format yang jelas
*/

void tampilkanHasil(int n, float hasil[10]) {
    int i;
    
    printf("=======================================================\n");
    printf("                  HASIL AKHIR\n");
    printf("=======================================================\n\n");
    
    printf("  Solusi dari sistem persamaan linear:\n\n");
    
    for(i = 0; i < n; i++) {
        printf("      x%d  =  %.4f\n", i+1, hasil[i]);
    }
    
    printf("\n=======================================================\n\n");
}

/*
===============================================================================
PROGRAM UTAMA (MAIN)
===============================================================================
*/

int main() {
    /* Deklarasi variabel */
    int jumlahPersamaan;
    float matriks[10][11];  /* Matriks augmented maksimal 10x11 */
    float solusi[10];       /* Array untuk menyimpan hasil x1, x2, x3, ... */
    
    /*
    ========================================================================
    LANGKAH 1: TAMPILKAN JUDUL PROGRAM
    ========================================================================
    */
    
    printf("\n");
    printf("=======================================================\n");
    printf("=======================================================\n");
    printf("                                                       \n");
    printf("        PROGRAM ELIMINASI GAUSS                        \n");
    printf("        Penyelesaian Sistem Persamaan Linear          \n");
    printf("                                                       \n");
    printf("=======================================================\n");
    printf("=======================================================\n");
    printf("\n");
    
    /*
    ========================================================================
    LANGKAH 2: INPUT JUMLAH PERSAMAAN
    ========================================================================
    */
    
    printf("Berapa jumlah persamaan yang ingin diselesaikan?\n");
    printf("(Minimal 1, Maksimal 10)\n\n");
    printf("Jumlah persamaan: ");
    scanf("%d", &jumlahPersamaan);
    bersihkanBuffer();
    
    /* Validasi input */
    if(jumlahPersamaan < 1 || jumlahPersamaan > 10) {
        printf("\nERROR: Jumlah persamaan harus antara 1-10!\n");
        printf("Program dihentikan.\n\n");
        return 1;
    }
    
    tekanEnter();
    
    /*
    ========================================================================
    LANGKAH 3: INPUT MATRIKS AUGMENTED
    ========================================================================
    */
    
    inputMatriks(jumlahPersamaan, matriks);
    
    /*
    ========================================================================
    LANGKAH 4: TAMPILKAN MATRIKS AWAL
    ========================================================================
    */
    
    tampilkanMatriks(jumlahPersamaan, matriks, "MATRIKS AWAL (Input Anda)");
    tekanEnter();
    
    /*
    ========================================================================
    LANGKAH 5: PROSES ELIMINASI GAUSS
    ========================================================================
    */
    
    prosesEliminasi(jumlahPersamaan, matriks);
    
    /*
    ========================================================================
    LANGKAH 6: TAMPILKAN MATRIKS SETELAH ELIMINASI
    ========================================================================
    */
    
    tampilkanMatriks(jumlahPersamaan, matriks, "MATRIKS SETELAH ELIMINASI");
    tekanEnter();
    
    /*
    ========================================================================
    LANGKAH 7: HITUNG SOLUSI DENGAN SUBSTITUSI BALIK
    ========================================================================
    */
    
    hitungSolusi(jumlahPersamaan, matriks, solusi);
    
    /*
    ========================================================================
    LANGKAH 8: TAMPILKAN HASIL AKHIR
    ========================================================================
    */
    
    tampilkanHasil(jumlahPersamaan, solusi);
    
    /*
    ========================================================================
    PROGRAM SELESAI
    ========================================================================
    */
    
    printf("Terima kasih telah menggunakan program ini!\n");
    printf("Tekan ENTER untuk keluar...");
    getchar();
    
    return 0;
}

/*
===============================================================================
                        CARA MENGGUNAKAN PROGRAM
===============================================================================

1. COMPILE PROGRAM
   Di terminal VS Code, ketik:
   gcc gauss.c -o gauss
   
2. JALANKAN PROGRAM
   Windows: gauss.exe
   Linux/Mac: ./gauss

3. CONTOH INPUT

   Misalkan Anda ingin menyelesaikan sistem persamaan:
   
   2x + 1y - 1z = 8
   -3x - 1y + 2z = -11
   -2x + 1y + 2z = -3
   
   Cara input:
   
   Jumlah persamaan: 3 [ENTER]
   
   Baris ke-1: 2 1 -1 8 [ENTER]
   Baris ke-2: -3 -1 2 -11 [ENTER]
   Baris ke-3: -2 1 2 -3 [ENTER]
   
   [Tekan ENTER beberapa kali untuk melihat proses]
   
4. OUTPUT YANG DIHARAPKAN

   HASIL AKHIR
   
   x1 = 2.0000
   x2 = 3.0000
   x3 = -1.0000

===============================================================================
                            TIPS PENTING
===============================================================================

- Pisahkan angka dengan SPASI (bukan koma)
- Gunakan TITIK untuk desimal (contoh: 3.5, bukan 3,5)
- Untuk angka negatif, gunakan tanda MINUS di depan (contoh: -3)
- Setiap baris harus diakhiri dengan ENTER
- Program akan pause di beberapa tempat, tekan ENTER untuk lanjut

===============================================================================
*/
