# soal-shift-sisop-modul-4-D10-2021

## Soal nomer 1

- Jika sebuah direktori dibuat dengan awalan “AtoZ_”, maka direktori tersebut akan menjadi direktori ter-encode.
- Jika sebuah direktori di-rename dengan awalan “AtoZ_”, maka direktori tersebut akan menjadi direktori ter-encode.
- Apabila direktori yang terenkripsi di-rename menjadi tidak ter-encode, maka isi direktori tersebut akan terdecode.
- Metode encode pada suatu direktori juga berlaku terhadap direktori yang ada di 

Algoritma Encode yang digunakan adalah encode at bash chipper. Pada encode ini, huruf akan dibalik sesuai urutan abjad. Contoh a->z, b->y, c->x, dll. Untuk itu, kita menggunakan :

gambar atoz : 

## Soal nomer 2

- Jika sebuah direktori dibuat dengan awalan “RX_[Nama]”, maka direktori tersebut akan menjadi direktori terencode beserta isinya dengan perubahan nama isi sesuai kasus nomor 1 dengan algoritma tambahan ROT13 (Atbash + ROT13).
- Jika sebuah direktori di-rename dengan awalan “RX_[Nama]”, maka direktori tersebut akan menjadi direktori terencode beserta isinya dengan perubahan nama isi sesuai dengan kasus nomor 1 dengan algoritma tambahan Vigenere Cipher dengan key “SISOP” (Case-sensitive, Atbash + Vigenere).
- Apabila direktori yang terencode di-rename (Dihilangkan “RX_” nya), maka folder menjadi tidak terencode dan isi direktori tersebut akan terdecode berdasar nama aslinya.

Pada nomer 2, encode digunakan dua kali. yang pertama encode yang digunakan pada nomer 1, kemudian ditambah encode rot13, dimana huruf akan ditambah/dikurangi 13. Jika dibawah n, maka akan ditambah 13 urutan, sedangkan jika di atas m akan dikurangi 13 urutan.

gambar rx

Kendala :
- Kebingungan maksud dari nomer 3
- Sering error saat membuat log
- Kesulitan memisah file pada nomer 2 e
- Kelompok kurang berkontribusi



