#include <iostream>
#include <string>
#include <fstream>

using namespace std;

struct Toko {
    string produk;
    string harga;
    string stok;
};

int banyakData() {
    fstream database;
    int ukuran;
    Toko data;

    database.open("data.txt");

    while(!database.eof()){
        getline(database, data.produk);
        getline(database, data.harga);
        getline(database, data.stok);
        ukuran++;
    }
    database.close();

    ukuran = ukuran -1 ;

    cout << ukuran << endl;

    return ukuran;

}

void printData(struct Toko printData[], int ukuran){
    for(int i=0; i<ukuran; i++){
        cout  << printData[i].produk << "\t\t\t" << printData[i].harga  << "\t\t\t" << printData[i].stok << endl; 
    }
}

void isiData() {
    fstream database;

    Toko inputData;

    cout << "Masukkan Data : " << endl;

    cout << "Masukkan Nama Produk : ";
    cin >> inputData.produk;
    cout << "Masukkan Nama Harga : ";
    cin >> inputData.harga;
    cout << "Masukkan Nama Stok : ";
    cin >> inputData.stok;

    database.open("data.txt", ios::app);

    database << inputData.produk << endl;
    database << inputData.harga << endl;
    database << inputData.stok << endl << endl;

    database.close();

}

void bacaData() {
    fstream database;

    int ukuran = banyakData();
    
    Toko bacaData[ukuran];

    database.open ("data.txt");

    for (int i=0; i < ukuran; i++ ){
        database  >> bacaData[i].produk;
        database  >> bacaData[i].harga;
        database  >> bacaData[i].stok;
    }

    database.close();

    printData(bacaData, ukuran);


}

int main(){
    isiData();
    bacaData();
}