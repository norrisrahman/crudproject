#include <iostream>
#include <array>
#include <cstdlib>
#include <fstream>
#include <string>

using namespace std;

struct Record {
	string tanggal;
	string ID;
    int jumlahTelur;
    int harga;
    string income;
};

void checkDb();
int dataSize();
void getDb();
void addData(Record ternak);
string formatAngka(int angka);
void inputData();
void readData();
void printData();
void sortData();
void saveDB(struct Record sortRecord[], int size);
void searchData();
void Search();
void updateData();
void deleteData();

int main() {
    string x;
    checkDb();

    cout << "=========================================================" << endl;
    cout << "    Program Record Data Harian Peternakan Ayam Petelur" << endl;
    cout << "=========================================================" << endl;

    menu:
    // system("cls");
    cout << "Pilih Jenis Operasi :" << endl;
    cout << "1. Tambah Data" << endl;
    cout << "2. Tampilkan Seluruh Data" << endl;
    cout << "3. Urutkan Data" << endl;
    cout << "4. Mencari Data" << endl;
    cout << "5. Update Data" << endl;
    cout << "6. Hapus Data" << endl;
    cout << "7. Exit" << endl;
    cout << endl;

    cout << "Pilih Menu [1-4]: ";
    cin >> x;

    if (x == "1"){
        inputData();
        goto menu;
    }
    else if ( x=="2"){
        readData();
        goto menu;
    }
    else if (x =="3" ) {
        sortData();
        goto menu;
    }
    else if (x =="4") {
        searchData();
        goto menu;
    }
    else if (x == "5"){
        updateData();
        system("cls");
        cout << "Update Data Sukses" << endl;
        goto menu;
    }
    else if (x== "6") {
        deleteData();
        system("cls");
        cout << "Penghapusan Data Sukses" << endl;
        goto menu;
    }
    else if (x == "7") {
        system("cls");
        atexit;
    }
    else {
        system ("cls");
        cout << "\nInput Tidak Valid !!! \n" << endl;
        goto menu;
    }
	return 0;
}

//Untuk Mengecek File Dtabase
void checkDb() {
    fstream Database;
    Database.open("data.txt", ios::app);
    Database.close();
}

//Untuk Mengambil Database
void getDb(struct Record getDb[], int size) {
    fstream Database;

    Database.open("data.txt");

    for(int i = 0; i<size; i++){

        Database >> getDb[i].tanggal;
        Database >> getDb[i].ID;
        Database >> getDb[i].jumlahTelur;
        Database >> getDb[i].harga;
        Database >> getDb[i].income;
    }

    Database.close();
    
}

//Untuk Input Data
void inputData() {
    string tanggal,bulan,tahun, tgl;
    int income;

    Record inputData;

    system("cls");
    cout << "\nInput Record Harian" << endl;
    cout << "===================================\n"  << endl;
    cout << "Masukkan Tanggal (dd)\t\t: ";
    cin >> tanggal;
    cout << "Masukkan Bulan (mm)\t\t: ";
    cin >> bulan;
    cout << "Masukkan Tahun (yyyy)\t\t: ";
    cin >> tahun;

    inputData.tanggal = tanggal + "/" + bulan + "/" + tahun;

    inputData.ID = tahun + bulan + tanggal;

    cout << "Masukkan Jumlah Telur (Kg) \t: ";
    cin >> inputData.jumlahTelur;
    cout << "Masukkan Harga Telur/Kg \t: ";
    cin >> inputData.harga; 

    income = inputData.jumlahTelur * inputData.harga;

    inputData.income = formatAngka(income);

    addData(inputData);

    cout << endl;
}

//Untuk Memformat Agka Menjadi 3 digit
string formatAngka(int angka) {
    string perantara = ".";
    string output = to_string(angka);
    int inspost = output.length() - 3;
    while (inspost > 0) {
        output.insert(inspost, perantara);
        inspost -= 3;
    }
    return output;
}

//Untuk Menyimpan Data Input Ke Database
void addData( Record addData) {
    fstream Database;
    Database.open("data.txt", ios::app);

    Database << addData.tanggal << "    "<< addData.ID << "   " << addData.jumlahTelur << "    " << addData.harga << "         " << addData.income << endl;

    Database.close();
}

//Untuk Menghitung Besar Data dalam Database
int dataSize() {
    fstream Database;
    Record dataSize;
    int size = 0;


    Database.open("data.txt");
    
    Database >> dataSize.tanggal;
    Database >> dataSize.ID;
    Database >> dataSize.jumlahTelur;
    Database >> dataSize.harga;
    Database >> dataSize.income;
    
    while (!Database.eof()){
        size++;
        Database >> dataSize.tanggal;
        Database >> dataSize.ID;
        Database >> dataSize.jumlahTelur;
        Database >> dataSize.harga;
        Database >> dataSize.income;
    }
    
    Database.close();

    return size;
}


//Untuk Membaca Data dalam Database
void readData() {

    int size = dataSize();
    
    Record* readData = new Record[size];

    getDb(readData, size);

    system("cls");
    cout << "Menampilkan Semua Data :\n" << endl;
    cout << "Tanggal\t\t" << "ID Record\t" << "Jumlah Telur (Kg)" << "\t" << "Harga /Kg\t" << "Total Pemasukan" << endl;
    cout << "==========================================================================================" << endl;
    for ( int i=0; i<size; i++) {
        cout << readData[i].tanggal << "\t" << readData[i].ID << "\t" << readData[i].jumlahTelur << "\t\t\t"<< "Rp " << readData[i].harga << "\t"<< "Rp " << readData[i].income << endl; 
    }

    cout << endl;
}

//Fungsi Untuk Mengurutkan Berdasarkan Tanggal Terbaru
void sortDesc(struct Record arr[], int n){
    int i, j;
    struct Record key;
    for (i = 1; i < n; i++) {
        key = arr[i];
        j = i - 1;        
        while (j >= 0 && arr[j].ID < key.ID) {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
            arr[j + 1] = key;
    }
}

//Fungsi Untuk Mengurutkan Berdasarkan Tanggal Terlama
void sortAcc(struct Record arr[], int n){
    int i, j;
    struct Record key;
    for (i = 1; i < n; i++) {
        key = arr[i];
        j = i - 1;        
        while (j >= 0 && arr[j].ID > key.ID) {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
            arr[j + 1] = key;
    }
}

//Fungsi Untuk Mengurutkan Berdasarkan Jumlah Telur Terbanyak
void sortQty(struct Record arr[], int n){
    int i, j;
    struct Record key;
    for (i = 1; i < n; i++) {
        key = arr[i];
        j = i - 1;        
        while (j >= 0 && arr[j].jumlahTelur < key.jumlahTelur) {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
            arr[j + 1] = key;
    }
}

//Untuk Mengurutkan Dan Menampilkan Hasil Pengurutan Data
void sortData() {
    string opt;
    int size = dataSize();
    
    Record* sortRecord = new Record[size];

    getDb(sortRecord, size);

    system ("cls");
    opt:
    cout << "Pilih Jenis Pengurutan Data :" << endl;
    cout << "=============================" << endl;
    cout << "1. Urutkan Data Berdasarkan Tanggal Terbaru"  << endl;
    cout << "2. Urutkan Data Dari Tanggal Terlama"  << endl;
    cout << "3. Urutkan Data Dari Jumlah Telur Terbanyak\n"  << endl;
    cout << "Masukkan Pilihan [1-2] : ";
    cin >> opt;

    if (opt == "1") {
        sortDesc(sortRecord, size);
        saveDB(sortRecord, size);
    }
    else if ( opt == "2") {
        sortAcc(sortRecord, size);
        saveDB(sortRecord, size);
    }
    else if (opt == "3") {
        sortQty(sortRecord, size);
        saveDB(sortRecord, size);
    }
    else{
        cout << "Input Tidak Valid" << endl;
        goto opt;
    }
    
    system("cls");
    cout << "Hasil Pengurutan Data :\n" << endl;
    cout << "Tanggal\t\t" << "ID Record\t" << "Jumlah Telur (Kg)" << "\t" << "Harga /Kg\t" << "Total Pemasukan" << endl;
    cout << "==========================================================================================" << endl;
    for ( int i=0; i<size; i++) {
        cout << sortRecord[i].tanggal << "\t" << sortRecord[i].ID << "\t" << sortRecord[i].jumlahTelur << "\t\t\t"<< "Rp " << sortRecord[i].harga << "\t"<< "Rp " << sortRecord[i].income << endl;  
    }

    cout << endl;
    
}

//Untuk Menyimpan Data Kedalam Database;
void saveDB(struct Record sortRecord[], int size) {

    fstream Database;
    Database.open("data.txt", ios::trunc | ios::out);

    for (int i=0; i < size; i++){

        Database << sortRecord[i].tanggal << "    " << sortRecord[i].ID << "   " << sortRecord[i].jumlahTelur << "      " << sortRecord[i].harga  << "         " << sortRecord[i].income << endl;
    }

    Database.close();
}

//Untuk menampilkan Pesan Error
void printErr () {
    system ("cls");
    cout << "\n\nKeyword Invalid / Data Tidak Ada\n\n"<< endl;
}

//Untuk Mencari Data
void searchData () {
    string keyword;
    int ind= 0;

    int size = dataSize();
    
    Record* array = new Record[size];

    getDb(array, size);

    cout<<"Masukkan Tanggal Record (dd/mm/yyyy) : ";
    cin >> keyword;

    system("cls");
    cout << "Hasil Pencarian :" << endl;
    cout << "Tanggal\t\t" << "ID Record\t" << "Jumlah Telur (Kg)" << "\t" << "Harga /Kg\t" << "Total Pemasukan" << endl;
    cout << "==========================================================================================" << endl;
    for(int i=0;i<size;i++) {
        if(array[i].tanggal==keyword) {
            cout << array[i].tanggal << "\t" << array[i].ID << "\t" << array[i].jumlahTelur << "\t\t\t"<< "Rp " << array[i].harga << "\t"<< "Rp " << array[i].income << endl;
            ind++;
        }
    }
    cout << endl;
    if (ind == 0){
        printErr();
    }else{
        return; 
    }
}

//Untuk Mengganti Data
void updateData() {
    string keyword, tanggal,bulan,tahun, tgl;
    int income;

    int size = dataSize();
    
    Record* array = new Record[size];

    getDb(array, size);

    readData();

    cout<<"Masukkan Tanggal Record Untuk Update Data (dd/mm/yyyy) : ";
    cin >> keyword;

    system("cls");

    for(int i=0;i<size;i++) {
        if(array[i].tanggal==keyword) {
            cout << "Tanggal\t\t" << "ID Record\t" << "Jumlah Telur (Kg)" << "\t" << "Harga /Kg\t" << "Total Pemasukan" << endl;
            cout << "==========================================================================================" << endl;
            cout << array[i].tanggal << "\t" << array[i].ID << "\t" << array[i].jumlahTelur << "\t\t\t"<< "Rp " << array[i].harga << "\t"<< "Rp " << array[i].income << endl; 

            cout << "\nMasukkan Data Baru : " << endl;
                cout << "Masukkan Tanggal (dd)\t\t: ";
                cin >> tanggal;
                cout << "Masukkan Bulan (mm)\t\t: ";
                cin >> bulan;
                cout << "Masukkan Tahun (yyyy)\t\t: ";
                cin >> tahun;

                array[i].tanggal = tanggal + "/" + bulan + "/" + tahun;
                array[i].ID = tahun + bulan + tanggal;

                cout << "Masukkan Jumlah Telur (Kg)\t: ";
                cin >> array[i].jumlahTelur;
                cout << "Masukkan Harga Telur/Kg \t: ";
                cin >> array[i].harga;

                income = array[i].jumlahTelur * array[i].harga;

                array[i].income = formatAngka(income);

                saveDB(array, size);

                cout << endl;
            return;
        }
    }
    printErr();
}

//Untuk Menghapus Data
void deleteData () {
    string keyword, tanggal,bulan,tahun, tgl;
    int size = dataSize();
    
    Record* array = new Record[size];

    getDb(array, size);

    readData();

    cout<<"Masukkan tanggal record yang ingin dihapus (dd/mm/yyyy) : ";
    cin >> keyword;

    for(int i=0;i<size;i++) {
        if(array[i].tanggal==keyword) {
            for(int j=i; j<size -1; j++) {
                array[j].tanggal = array[j+1].tanggal;
                array[j].ID = array[j+1].ID;
                array[j].jumlahTelur = array[j+1].jumlahTelur;
                array[j].harga = array[j+1].harga;
                array[j].income = array[j+1].income;
            }
            size--;

            saveDB(array, size);
            readData();
            return;
        }
    }
    printErr(); 
}