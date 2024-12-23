#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_URUN 100  // Maksimum ürün sayısı
#define MAX_AD 50     // Ürün adı için maksimum uzunluk

// Yapı tanımı: Ürün adı ve kalori değeri
typedef struct {
    char ad[MAX_AD];
    float kalori;
} Urun;

// Kalori bilgilerini dosyadan okuyarak bir dizi içine yükler
int kalori_dosyasi_oku(const char *dosya_adi, Urun urunler[])
{
    FILE *dosya = fopen(dosya_adi, "r");
    if (!dosya) {
        printf("Hata: %s dosyasi acilamadi.\n", dosya_adi);
        return 0;
    }

    int sayac = 0;  // Okunan ürün sayısını tutar
    while (fscanf(dosya, "%s %f", urunler[sayac].ad, &urunler[sayac].kalori) == 2) {
        sayac++;
    }

    fclose(dosya);
    return sayac;  // Toplam ürün sayısını döner
}

// Sipariş dosyasını okuyarak toplam kaloriyi hesaplar
float siparis_dosyasi_oku(const char *dosya_adi, Urun urunler[], int urun_sayisi)
{
    FILE *dosya = fopen(dosya_adi, "r");
    if (!dosya) {
        printf("Hata: %s dosyasi acilamadi.\n", dosya_adi);
        return 0;
    }

    float toplam_kalori = 0.0;
    char siparis_ad[MAX_AD];
    float porsiyon;

    while (fscanf(dosya, "%s %f", siparis_ad, &porsiyon) == 2) {
        int bulundu = 0;
        for (int i = 0; i < urun_sayisi; i++) {
            if (strcmp(siparis_ad, urunler[i].ad) == 0) {  // Ürün adı eşleşirse
                toplam_kalori += urunler[i].kalori * porsiyon;
                bulundu = 1;
                break;
            }
        }
        if (!bulundu) {
            printf("Uyari: %s kalori dosyasinda bulunamadi.\n", siparis_ad);
        }
    }

    fclose(dosya);
    return toplam_kalori;  // Toplam kaloriyi döner
}

int main()
{
    Urun urunler[MAX_URUN];  // Ürün bilgilerini saklayan dizi
    const char *kalori_dosya = "kalori.txt";
    const char *siparis_dosya = "siparis.txt";

    // 1. Adım: Kalori dosyasını oku
    int urun_sayisi = kalori_dosyasi_oku(kalori_dosya, urunler);
    if (urun_sayisi == 0) {
        printf("Hata: Kalori dosyasindan veri okunamadi.\n");
        return 1;
    }

    // 2. Adım: Sipariş dosyasını oku ve toplam kaloriyi hesapla
    float toplam_kalori = siparis_dosyasi_oku(siparis_dosya, urunler, urun_sayisi);

    // 3. Adım: Toplam kaloriyi ekrana yazdır
    printf("Toplam Kalori: %.2f kcal\n", toplam_kalori);

    return 0;
}