#include <16f877.h>    

#device ADC=10  // 10 bitlik ADC kullanilacagi belirtiliyor.

// Denetleyici konfigürasyon ayarlari
#fuses XT,NOWDT,NOPROTECT,NOBROWNOUT,NOLVP,NOPUT,NOWRT,NODEBUG,NOCPD

#use delay (clock=4000000) // Gecikme fonksiyonu için kullanilacak osilatör frekansi belirtiliyor.

#use fast_io(a) //Port yönlendirme komutlari A portu için gecerli

#define use_portb_lcd TRUE   // LCD B portuna bagli

#include <lcd.c>   // lcd.c dosyasy tanitiliyor

unsigned long int bilgi; // Isaretsiz 16 bitlik tam sayi tipinde degisken tanimlaniyor
float voltaj,sicaklik;   // ondalikli tipte degiskenler tanitiliyor

//********** ANA PROGRAM FONKIYONU*******

void main ( )
{
   setup_psp(PSP_DISABLED);        // PSP birimi devre disi
   setup_timer_1(T1_DISABLED);     // T1 zamanlayicyisi devre disi
   setup_timer_2(T2_DISABLED,0,1); // T2 zamanlayycysy devre disi
   setup_CCP1(CCP_OFF);            // CCP1 birimi devre disi
   setup_CCP2(CCP_OFF);            // CCP2 birimi devre disi

   set_tris_a(0x01);  // RA0 Giris olarak yönlendiriliyor

   setup_adc(adc_clock_div_32);   // ADC clock frekansi fosc/32
   setup_adc_ports(AN0); //RA0/AN0 girisi analog

   lcd_init();   // LCD hazir hale getiriliyor

   set_adc_channel(0);   // RA0/AN0 ucundaki sinyal A/D islemine tabi tutulacak
   delay_us(20);         // Kanal seçiminde sonra bu bekleme süresi verilmelidir

   printf(lcd_putc, "\fAlitalip Sever" ); // Ekrana herhangi bir yazi yazdirma
   delay_ms(1000);                        // Ekranda yazi kalma suresi

   printf(lcd_putc,"\fSicaklik="); // LCD'ye yazi yazdiriliyor

   while(1)   // sonsuz döngü
   {
      bilgi=read_adc();  // ADC sonucu okunuyor ve bilgi degiskenine aktarililiyor

      voltaj=(0.0048828125*bilgi)*1000;   // Dijitale çevirme islemine ugrayan sinyalin mV olarak gerilimi hesaplaniyor
      sicaklik=(voltaj/10);    // Her 10mV'ta 1 derece artma

      lcd_gotoxy(10,1); // Imlec 1. satir 10.sutunda
      printf(lcd_putc,"%5.1f'C",sicaklik); // LCD'ye sicaklik degeri yazdiriliyor
      // Gösterilecek ondalikli degerin toplam basamak sayisi 5 olacak.
      // Gösterilecek degerin ondalikli kismi ise 1 basamak olacak. %5.1f
      // komutu ile bu islemler yaptirilmistir
      delay_ms(100); // 100 msn gecikme
   }
}


