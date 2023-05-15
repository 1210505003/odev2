#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <limits.h>

#define A_SIZE 20
#define G_SIZE 10
#define MAX_W 10

//Max deger icin sonsuz sayi
#define INF INT_MAX

void generate(int a[], int size);
void function1(int a[], int size);
int function2(int a[], int size);
void function3(int g[][G_SIZE], int d[][G_SIZE], int size);
void print1(int a[], int size);
void print2(int g[][G_SIZE], int size);
void print3(int g[][G_SIZE], int size, int t);

int main() {
    int a[A_SIZE];
    int g[G_SIZE][G_SIZE] = {
    { 0, 10,  3,  0,  0,  5,  0, 17,  0, 22},
    {10,  0,  5,  0,  2,  0, 13,  0,  0,  0},
    { 3,  5,  0,  2,  0,  4,  0, 21,  0, 11},
    { 0,  0,  2,  0,  7,  0,  6,  0,  0,  0},
    { 0,  2,  0,  7,  0,  6,  0,  0, 19,  0},
    { 5,  0,  4,  0,  6,  0,  9,  3,  0,  0},
    { 0, 13,  0,  6,  0,  9,  0,  4,  0,  0},
    {17,  0, 21,  0,  0,  3,  4,  0,  8,  0},
    { 0,  0,  0,  0, 19,  0,  0,  8,  0,  5},
    {22,  0, 11,  0,  0,  0,  0,  0,  5,  0}
    };
    int d[G_SIZE][G_SIZE];
    int t;

    // Rastgele sayi uretici icin seed
    srand(time(NULL));

    // Calisma suresinin hesaplanmasi
    clock_t start, end;
    double time;

    start = clock();

    generate(a, A_SIZE);
    printf("A:\n");
    print1(a, A_SIZE);

    function1(a, A_SIZE);
    printf("\nFunction1 Sonuc:\n");
    print1(a, A_SIZE);

    t = function2(a, A_SIZE);
    printf("\nFunction2 Sonuc: %d\n", t);

    printf("\nG:\n");
    print2(g, G_SIZE);

    function3(g, d, G_SIZE);
    printf("\nFunction3 Sonuc:\n");
    print2(d, G_SIZE);

    printf("\n%d icin sonuc:\n", t);
    print3(d, G_SIZE, t);

    end = clock();
    time = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("\nCalisma Suresi: %f sn\n", time);

    return 0;
}

void generate(int a[], int size) {             // tanýmlanan a dizisine rastgele sayý atar.Bu Sayýlar MAX_W, -MAX_W arasýndadýr.
    for (int i = 0; i < size; i++) {
        a[i] = rand() % (2 * MAX_W) - MAX_W;
    }
}

void function1(int a[], int size) {         // Bubble sort algoritmasý kullanarak diziyi sýralar.
    for (int i = 0; i < size - 1; i++) {   //Bu algoritmada her sayý çifti birbirleri ile karþýlaþtýrýlarak büyükten küçüðe doðru sayýlarýn yerlerini deðiþtirerek tüm dizi sýralanmýþ olur.
        for (int j = 0; j < size - 1 - i; j++) { // Ýlk döngü, size - 1 kere çalýþýr. Her çalýþmada, dizinin en büyük elemaný dizinin sonunda olacaðýndan, bir sonraki döngüde son elemanýn dahil edilmemesi için size - 1 - i kere çalýþtýrýlýr.
            if (a[j] > a[j + 1]) {         //Ýkinci for döngüsü, bitiþik elemanlarý karþýlaþtýrýr ve yanlýþ sýrada duruyorlarsa yerlerini deðiþtirir. Bu iþlem, dizinin baþýndan sonuna kadar tekrarlanýr.
                int tmp = a[j];        // Bu iþlem, dizinin büyük elemanlarýný dizinin sonuna, küçük elemanlarýný ise dizinin baþýna doðru hareket ettirerek sýralamayý gerçekleþtirir.
                a[j] = a[j + 1];
                a[j + 1] = tmp;
            }
        }
    }
}

int function2(int a[], int size) {    // Fonksiyon, bu dizinin alt dizileri arasýnda en büyük olanýn ortalamasýný hesaplar.
    int t = 0, current_sum = 0, count=0;
    for (int i = 0; i < size; i++) {  //for döngüsü kullanarak, dizi elemanlarýnýn her biri üzerinde gezinir. Her adýmda, current_sum adlý deðiþkende bir toplam deðeri tutulur.
        if (current_sum + a[i] > 0) {    //if koþulu, mevcut toplamýn, bir sonraki elemanýn eklenmesiyle 0'dan büyük olup olmadýðýný kontrol eder.
            current_sum = current_sum + a[i]; //Eðer büyükse, bu eleman current_sum ile toplanýr ve yeni toplam current_sum olarak kaydedilir.
        }
        else {
            current_sum = 0; // Aksi halde, current_sum sýfýrlanýr.
        }
        if (current_sum > t) {  //bir baþka if koþulu, current_sum'ýn mevcut maksimum deðeri olan t'den büyük olup olmadýðýný kontrol eder
            t = current_sum; // Eðer büyükse, t'nin deðeri current_sum'a eþitlenir ve count bir artýrýlýr.
            count++;
        }
    }
    return t/count; //En büyük alt dizi toplamýnýn ortalamasý, return ifadesi ile geri döndürülür.
}

void function3(int g[][G_SIZE], int d[][G_SIZE], int size) { //iki boyutlu bir tamsayý dizisi olan g'yi bir aðýrlýk matrisi olarak alýr ve ayný boyutlarda bir tamsayý dizisi olan d'yi hesaplar.her iki düðüm arasýndaki en kýsa yol uzunluklarýný hesaplar.
      // Ýlk olarak, 'd' matrisi oluþturulur ve çaprazýndaki elemanlar 0 olarak ayarlanýr.
    // Matrisin diðer elemanlarý, girdi matrisindeki deðerlere eþitlenir.

    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            if (i == j) {
                d[i][j] = 0;
            }
            else if (g[i][j] != 0) {
                d[i][j] = g[i][j];
            }
            else {
                d[i][j] = INF;
            }
        }
    }
    // Floyd-Warshall algoritmasý, bu ikinci döngü ile gerçekleþtirilir.
    // Ýki düðüm arasýndaki en kýsa yol, iki farklý yol arasýnda kýyaslamalar yapýlarak bulunur.
    // 'k' deðiþkeni, ara düðümü temsil eder ve döngü, bu ara düðümler üzerinde yapýlýr.

    for (int k = 0; k < size; k++) {
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                if (d[i][k] != INF && d[k][j] != INF && // Ýki düðüm arasýnda yol var mý?
                    d[i][k] + d[k][j] < d[i][j]) { // Daha önce hesaplanan yol daha uzun mu?
                    d[i][j] = d[i][k] + d[k][j]; // Yeni yol daha kýsa ise, bu deðer 'd' matrisine kaydedilir.
                }
            }
        }
    }
}
//print1 print2 ve print3 fonksiyonlarý:  dizileri veya matrisleri yazdýrmak için kullanýlýr
void print1(int a[], int size) {
    for (int i = 0; i < size; i++) {
        printf("%d ", a[i]);
        if ((i + 1) % 10 == 0) {
            printf("\n");
        }
    }
}

void print2(int g[][G_SIZE], int size) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            if (g[i][j] == INF) {
                printf("INF ");
            }
            else {
                printf("%3d ", g[i][j]);
            }
        }
        printf("\n");
    }
}

void print3(int d[][G_SIZE], int size, int t) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            if (i != j && d[i][j] < t) {
                printf("%c -> %c: %d\n", 'A' + i, 'A' + j, d[i][j]);
            }
 }
}
}
