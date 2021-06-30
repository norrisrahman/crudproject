#include <iostream>
#include <array>
#include <cstdlib>
#include <fstream>
#include <string>

using namespace std;

struct Toko {
	string produk;
	string harga;
    int stok;
};

void tulisData ( Toko tulisData) {
    fstream myFile;
    myFile.open("data.txt", ios::app);

    myFile << tulisData.produk << "           "<< tulisData.harga << "           " << tulisData.stok <<  endl;

    myFile.close();
}

void tambahData() {
    string tanggal,bulan,tahun, tgl;

    Toko tambahData;

    cout << "Masukkan Nama produk \t\t: ";
    cin >> tambahData.produk;
    cout << "Masukkan Jumlah Telur \t\t: ";
    cin >> tambahData.harga;
    cout << "Masukkan Harga Telur/Kg \t: ";
    cin >> tambahData.stok; 

    tulisData(tambahData);

    cout << endl;
}

void bacaData() {
    ifstream myFile;
    Toko dataToko;

    myFile.open("data.txt");

    myFile >> dataToko.produk;
    myFile >> dataToko.harga;
    myFile >> dataToko.stok;
    
    system ("clear");
    cout << "\nMenampilkan Semua Record Data :\n" << endl;
    cout << "Tanggal\t\t\t" << "ID Record\t" << "Jumlah Telur" << "\t" << "Harga /Kg" << endl;
    cout << "======================================================================" << endl;
    while (!myFile.eof()){
        cout << dataToko.produk << "\t\t" << dataToko.harga << "\t" << dataToko.stok <<  endl;

        myFile >> dataToko.produk;
        myFile >> dataToko.harga;
        myFile >> dataToko.stok;
    }
    cout << endl;
    
    myFile.close();
}

int main() {
    int x;

    cout << "\t\t\t DATABASE PENJUALAN MINIMARKET ABC \t\t\t" << endl;
    menu:
    cout << "Pilih Menu :" << endl;
    cout << "1. Tambahkan Produk" << endl;
    cout << "2. Tampilkan Seluruh Data Produk" << endl;
    cout << "3. Urutkan Produk Berdasarkan Update Terbaru" << endl;
    cout << "4. Mencari Data" << endl;
    cout << "5. Perbarui Data" << endl;
    cout << "6. Hapus Data" << endl;
    cout << "7. Keluar";
    cout << endl;

    cout << "Pilih Menu [1-6]: ";
    cin >> x;

    switch (x) {
    case 1:
        system ("clear");
        tambahData();
        goto menu;
        break;
    case 2 :
        system("clear");
        bacaData();
        goto menu;
        break;
    
    default:
        break;
    }

    
	return 0;
}