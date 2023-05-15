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
void quick_sort(int a[], int size);
int average_Max_Sum(int a[], int size);
void floyd_Warshall_Algorithm(int g[][G_SIZE], int d[][G_SIZE], int size);
void printIntArray(int a[], int size);
void printWeightedGraph(int g[][G_SIZE], int size);
void printShortPaths(int g[][G_SIZE], int size, int t);

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
    printIntArray(a, A_SIZE);

    quick_sort(a, A_SIZE);
    printf("\n  quick sort Sonuc:\n");
    printIntArray(a, A_SIZE);

    t = average_Max_Sum(a, A_SIZE);
    printf("\n max sum Sonuc: %d\n", t);

    printf("\nG:\n");
    printWeightedGraph(g, G_SIZE);

    floyd_Warshall_Algorithm(g, d, G_SIZE);
    printf("\n Sonuc:\n");
    printWeightedGraph(d, G_SIZE);

    printf("\n%d icin sonuc:\n", t);
    printShortPaths(d, G_SIZE, t);

    end = clock();
    time = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("\nCalisma Suresi: %f sn\n", time);

    return 0;
}

void generate(int a[], int size) {
    for (int i = 0; i < size; i++) {
        a[i] = rand() % (2 * MAX_W) - MAX_W;
    }
}

void quicksort(int a[], int left, int right); // Bu fonksiyon, verilen diziyi quicksort algoritmasý kullanarak sýralar.



void quicksort(int a[], int left, int right) {
    if (left >= right) { // Sol indis, sað indisten büyük veya eþit olduðunda, dizi sýralanmýþ demektir.
        return;
    }

    int pivot = a[(left + right) / 2];  // Pivot elemaný, dizinin sol ve sað indislerinin ortalamasý olarak belirlenir.
    int i = left - 1;  // Ýndis deðiþkenleri, pivot elemanýndan küçük ve büyük elemanlarý ayrýmak için kullanýlýr.
    int j = right + 1;

    while (1) {  // Bu döngü, pivot elemanýndan küçük ve büyük elemanlarý doðru yere yerleþtirmek için kullanýlýr.
      // Pivot elemanýndan küçük elemanlarý bulmak için, sol taraftan baþlayarak ilerlenir.
        do {
            i++;
        } while (a[i] < pivot);

        do {               // Pivot elemanýndan büyük elemanlarý bulmak için, sað taraftan baþlayarak ilerlenir.
            j--;
        } while (a[j] > pivot);
        // Ýndis deðiþkenleri birbirini geçtiðinde, tüm elemanlar pivot elemanýndan küçük veya büyük demektir.
        if (i >= j) {
            break;
        }
         // Pivot elemanýndan küçük ve büyük elemanlar yer deðiþtirilir.
        int tmp = a[i];
        a[i] = a[j];
        a[j] = tmp;
    }
      // Pivot elemanýndan küçük elemanlar, pivot elemanýndan büyük elemanlardan küçük olduðundan, bu kýsým için quicksort çaðrýlýr.
    quicksort(a, left, j);
     // Pivot elemanýndan büyük elemanlar, pivot elemanýndan küçük elemanlardan büyük olduðundan, bu kýsým için rekürsif olarak quicksort çaðrýlýr.
    quicksort(a, j + 1, right);
}
void quick_sort(int a[], int size) { // Bu fonksiyon, verilen dizinin tüm elemanlarýný quicksort algoritmasý kullanarak sýralar.
    quicksort(a, 0, size - 1);
}

int average_Max_Sum(int a[], int size) {
    int t = 0, current_sum = 0, count=0;
    for (int i = 0; i < size; i++) {
        if (current_sum + a[i] > 0) {
            current_sum = current_sum + a[i];
        }
        else {
            current_sum = 0;
        }
        if (current_sum > t) {
            t = current_sum;
            count++;
        }
    }
    return t/count;
}

void floyd_Warshall_Algorithm(int g[][G_SIZE], int d[][G_SIZE], int size) {
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

    for (int k = 0; k < size; k++) {
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                if (d[i][k] != INF && d[k][j] != INF &&
                    d[i][k] + d[k][j] < d[i][j]) {
                    d[i][j] = d[i][k] + d[k][j];
                }
            }
        }
    }
}

void printIntArray(int a[], int size) {
    for (int i = 0; i < size; i++) {
        printf("%d ", a[i]);
        if ((i + 1) % 10 == 0) {
            printf("\n");
        }
    }
}

void printWeightedGraph(int g[][G_SIZE], int size) {
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

void printShortPaths(int d[][G_SIZE], int size, int t) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            if (i != j && d[i][j] < t) {
                printf("%c -> %c: %d\n", 'A' + i, 'A' + j, d[i][j]);
}
}
}
}
