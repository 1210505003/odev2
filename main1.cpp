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

void generate(int a[], int size) {             // tan�mlanan a dizisine rastgele say� atar.Bu Say�lar MAX_W, -MAX_W aras�ndad�r.
    for (int i = 0; i < size; i++) {
        a[i] = rand() % (2 * MAX_W) - MAX_W;
    }
}

void function1(int a[], int size) {         // Bubble sort algoritmas� kullanarak diziyi s�ralar.
    for (int i = 0; i < size - 1; i++) {   //Bu algoritmada her say� �ifti birbirleri ile kar��la�t�r�larak b�y�kten k����e do�ru say�lar�n yerlerini de�i�tirerek t�m dizi s�ralanm�� olur.
        for (int j = 0; j < size - 1 - i; j++) { // �lk d�ng�, size - 1 kere �al���r. Her �al��mada, dizinin en b�y�k eleman� dizinin sonunda olaca��ndan, bir sonraki d�ng�de son eleman�n dahil edilmemesi i�in size - 1 - i kere �al��t�r�l�r.
            if (a[j] > a[j + 1]) {         //�kinci for d�ng�s�, biti�ik elemanlar� kar��la�t�r�r ve yanl�� s�rada duruyorlarsa yerlerini de�i�tirir. Bu i�lem, dizinin ba��ndan sonuna kadar tekrarlan�r.
                int tmp = a[j];        // Bu i�lem, dizinin b�y�k elemanlar�n� dizinin sonuna, k���k elemanlar�n� ise dizinin ba��na do�ru hareket ettirerek s�ralamay� ger�ekle�tirir.
                a[j] = a[j + 1];
                a[j + 1] = tmp;
            }
        }
    }
}

int function2(int a[], int size) {    // Fonksiyon, bu dizinin alt dizileri aras�nda en b�y�k olan�n ortalamas�n� hesaplar.
    int t = 0, current_sum = 0, count=0;
    for (int i = 0; i < size; i++) {  //for d�ng�s� kullanarak, dizi elemanlar�n�n her biri �zerinde gezinir. Her ad�mda, current_sum adl� de�i�kende bir toplam de�eri tutulur.
        if (current_sum + a[i] > 0) {    //if ko�ulu, mevcut toplam�n, bir sonraki eleman�n eklenmesiyle 0'dan b�y�k olup olmad���n� kontrol eder.
            current_sum = current_sum + a[i]; //E�er b�y�kse, bu eleman current_sum ile toplan�r ve yeni toplam current_sum olarak kaydedilir.
        }
        else {
            current_sum = 0; // Aksi halde, current_sum s�f�rlan�r.
        }
        if (current_sum > t) {  //bir ba�ka if ko�ulu, current_sum'�n mevcut maksimum de�eri olan t'den b�y�k olup olmad���n� kontrol eder
            t = current_sum; // E�er b�y�kse, t'nin de�eri current_sum'a e�itlenir ve count bir art�r�l�r.
            count++;
        }
    }
    return t/count; //En b�y�k alt dizi toplam�n�n ortalamas�, return ifadesi ile geri d�nd�r�l�r.
}

void function3(int g[][G_SIZE], int d[][G_SIZE], int size) { //iki boyutlu bir tamsay� dizisi olan g'yi bir a��rl�k matrisi olarak al�r ve ayn� boyutlarda bir tamsay� dizisi olan d'yi hesaplar.her iki d���m aras�ndaki en k�sa yol uzunluklar�n� hesaplar.
      // �lk olarak, 'd' matrisi olu�turulur ve �apraz�ndaki elemanlar 0 olarak ayarlan�r.
    // Matrisin di�er elemanlar�, girdi matrisindeki de�erlere e�itlenir.

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
    // Floyd-Warshall algoritmas�, bu ikinci d�ng� ile ger�ekle�tirilir.
    // �ki d���m aras�ndaki en k�sa yol, iki farkl� yol aras�nda k�yaslamalar yap�larak bulunur.
    // 'k' de�i�keni, ara d���m� temsil eder ve d�ng�, bu ara d���mler �zerinde yap�l�r.

    for (int k = 0; k < size; k++) {
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                if (d[i][k] != INF && d[k][j] != INF && // �ki d���m aras�nda yol var m�?
                    d[i][k] + d[k][j] < d[i][j]) { // Daha �nce hesaplanan yol daha uzun mu?
                    d[i][j] = d[i][k] + d[k][j]; // Yeni yol daha k�sa ise, bu de�er 'd' matrisine kaydedilir.
                }
            }
        }
    }
}
//print1 print2 ve print3 fonksiyonlar�:  dizileri veya matrisleri yazd�rmak i�in kullan�l�r
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
