# soal-shift-sisop-modul-4-D10-2021

## Soal nomer 1

- Jika sebuah direktori dibuat dengan awalan “AtoZ_”, maka direktori tersebut akan menjadi direktori ter-encode.
- Jika sebuah direktori di-rename dengan awalan “AtoZ_”, maka direktori tersebut akan menjadi direktori ter-encode.
- Apabila direktori yang terenkripsi di-rename menjadi tidak ter-encode, maka isi direktori tersebut akan terdecode.
- Metode encode pada suatu direktori juga berlaku terhadap direktori yang ada di 

Algoritma Encode yang digunakan adalah encode at bash chipper. Pada encode ini, huruf akan dibalik sesuai urutan abjad. Contoh a->z, b->y, c->x, dll. Untuk itu, kita menggunakan :

![WhatsApp Image 2021-06-13 at 21 40 42](https://user-images.githubusercontent.com/77373958/121812142-fd2eed00-cc90-11eb-96ea-9afe4ad64208.jpeg)
![WhatsApp Image 2021-06-13 at 21 43 40](https://user-images.githubusercontent.com/77373958/121812145-fef8b080-cc90-11eb-9566-ceba779d9356.jpeg)
![WhatsApp Image 2021-06-13 at 21 45 19](https://user-images.githubusercontent.com/77373958/121812146-ff914700-cc90-11eb-8352-d0709497369b.jpeg)
![WhatsApp Image 2021-06-13 at 21 45 58](https://user-images.githubusercontent.com/77373958/121812147-0029dd80-cc91-11eb-85df-75fbbe12b15a.jpeg)
![WhatsApp Image 2021-06-13 at 21 38 53](https://user-images.githubusercontent.com/77373958/121812148-0029dd80-cc91-11eb-9e94-10ffd169c3cb.jpeg)


### Sebelum :

![WhatsApp Image 2021-06-13 at 21 43 40](https://user-images.githubusercontent.com/77373958/121812145-fef8b080-cc90-11eb-9566-ceba779d9356.jpeg)

### Sesudah :

![WhatsApp Image 2021-06-13 at 21 45 19](https://user-images.githubusercontent.com/77373958/121812146-ff914700-cc90-11eb-8352-d0709497369b.jpeg)

## Soal nomer 2

- Jika sebuah direktori dibuat dengan awalan “RX_[Nama]”, maka direktori tersebut akan menjadi direktori terencode beserta isinya dengan perubahan nama isi sesuai kasus nomor 1 dengan algoritma tambahan ROT13 (Atbash + ROT13).
- Jika sebuah direktori di-rename dengan awalan “RX_[Nama]”, maka direktori tersebut akan menjadi direktori terencode beserta isinya dengan perubahan nama isi sesuai dengan kasus nomor 1 dengan algoritma tambahan Vigenere Cipher dengan key “SISOP” (Case-sensitive, Atbash + Vigenere).
- Apabila direktori yang terencode di-rename (Dihilangkan “RX_” nya), maka folder menjadi tidak terencode dan isi direktori tersebut akan terdecode berdasar nama aslinya.

Pada nomer 2, encode digunakan dua kali. yang pertama encode yang digunakan pada nomer 1, kemudian ditambah encode rot13, dimana huruf akan ditambah/dikurangi 13. Jika dibawah n, maka akan ditambah 13 urutan, sedangkan jika di atas m akan dikurangi 13 urutan.


![WhatsApp Image 2021-06-13 at 21 40 42](https://user-images.githubusercontent.com/77373958/121812142-fd2eed00-cc90-11eb-96ea-9afe4ad64208.jpeg)

### Sebelum :

![WhatsApp Image 2021-06-13 at 21 43 40](https://user-images.githubusercontent.com/77373958/121812145-fef8b080-cc90-11eb-9566-ceba779d9356.jpeg)

### Sesudah :

![WhatsApp Image 2021-06-13 at 21 45 58](https://user-images.githubusercontent.com/77373958/121812147-0029dd80-cc91-11eb-85df-75fbbe12b15a.jpeg)

Kendala :
- Kebingungan maksud dari nomer 3
- Sering error saat membuat log
- Kesulitan memisah file pada nomer 2 e
- Kelompok kurang berkontribusi



