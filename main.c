#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>


typedef struct Hasta {
    char ad[50];
    char tc[12];
    char receteNo[10];
    int oncelik;
    struct Hasta* sonraki;
} Hasta;

Hasta* bas = NULL;


void receteNoUret(char* receteNo)
{
    sprintf(receteNo, "RX-%04d", rand() % 10000);
}


void hastaEkle(char* ad, char* tc, int oncelik)
{
    Hasta* yeni = (Hasta*)malloc(sizeof(Hasta));
    strcpy(yeni->ad, ad);
    strcpy(yeni->tc, tc);
    yeni->oncelik = oncelik;
    receteNoUret(yeni->receteNo);
    yeni->sonraki = NULL;

    if (bas == NULL || bas->oncelik > oncelik)
    {
        yeni->sonraki = bas;
        bas = yeni;
    }
    else
    {
        Hasta* temp = bas;
        while (temp->sonraki != NULL && temp->sonraki->oncelik <= oncelik)
        {
            temp = temp->sonraki;
        }
        yeni->sonraki = temp->sonraki;
        temp->sonraki = yeni;
    }
    printf("Hasta %s (%s) sisteme eklendi! Recete No: %s\n", ad, tc, yeni->receteNo);
}

void hastaCagir()
{
    if (bas == NULL)
    {
        printf("Bekleyen hasta yok!\n");
        return;
    }
    Hasta* temp = bas;
    printf("Hastaya cagri yapiliyor: %s (%s) - Recete No: %s\n", temp->ad, temp->tc, temp->receteNo);
    bas = bas->sonraki;
    free(temp);
}


void hastaListele()
{
    if (bas == NULL)
    {
        printf("Bekleyen hasta yok!\n");
        return;
    }
    printf("Bekleyen hastalar:\n");
    Hasta* temp = bas;
    while (temp != NULL)
    {
        printf("%s (%s) - Oncelik: %d - Recete No: %s\n", temp->ad, temp->tc, temp->oncelik, temp->receteNo);
        temp = temp->sonraki;
    }
}

int main() {
    srand(time(NULL));
    int secim;
    char ad[50], tc[12];
    int oncelik;

    while (1) {
        printf("\nAcil Servis Yonetim Sistemi\n");
        printf("1. Yeni Hasta Ekle\n");
        printf("2. Hasta Cagir\n");
        printf("3. Hasta Listesini Goruntule\n");
        printf("4. Cikis\n");
        printf("Seciminizi yapin: ");
        scanf("%d", &secim);

        switch (secim) {
            case 1:
                printf("Hasta Adi: ");
                scanf("%s", ad);
                printf("T.C. Kimlik No: ");
                scanf("%s", tc);
                printf("Oncelik (1: Kirmizi, 2: Sari, 3: Yesil): ");
                scanf("%d", &oncelik);
                hastaEkle(ad, tc, oncelik);
                break;
            case 2:
                hastaCagir();
                break;
            case 3:
                hastaListele();
                break;
            case 4:
                printf("Sistemden cikiliyor...\n");
                return 0;
            default:
                printf("Gecersiz secim!\n");
        }
    }
}

