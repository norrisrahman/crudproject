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
void sortData(int x);
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
    // system("clear");
    cout << "Pilih Jenis Operasi :" << endl;
    cout << "1. Tambah Data" << endl;
    cout << "2. Tampilkan Seluruh Data" << endl;
    cout << "3. Urutkan Data dari Data Terbaru" << endl;
    cout << "4. Urutkan Data Berdasarkan Jumlah Telur" << endl;
    cout << "5. Mencari Data" << endl;
    cout << "6. Update Data" << endl;
    cout << "7. Hapus Data" << endl;
    cout << "8. Exit" << endl;
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
        sortData(1);
        goto menu;
    }
    else if (x == "4"){
        sortData(2);
        goto menu;
    }
    else if (x =="5") {
        searchData();
        goto menu;
    }
    else if (x == "6"){
        updateData();
        goto menu;
    }
    else if (x== "7") {
        deleteData();
        system("clear");
        cout << "Penghapusan Data Sukses" << endl;
        goto menu;
    }
    else if (x == "8") {
        system("clear");
        atexit;
    }
    else {
        system ("clear");
        cout << "\nInput Tidak Valid !!! \n" << endl;
        goto menu;
    }
	return 0;
}

void checkDb() {
    fstream Database;
    Database.open("data.txt", ios::app);
    Database.close();
}

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


void inputData() {
    string tanggal,bulan,tahun, tgl;
    int income;

    Record inputData;

    system("clear");
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

    cout << "Masukkan Jumlah Telur \t\t: ";
    cin >> inputData.jumlahTelur;
    cout << "Masukkan Harga Telur/Kg \t: ";
    cin >> inputData.harga; 

    income = inputData.jumlahTelur * inputData.harga;

    inputData.income = formatAngka(income);

    addData(inputData);

    cout << endl;
}

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

void addData( Record addData) {
    fstream Database;
    Database.open("data.txt", ios::app);

    Database << addData.tanggal << "    "<< addData.ID << "   " << addData.jumlahTelur << "    " << addData.harga << "         " << addData.income << endl;

    Database.close();
}

int dataSize() {
    fstream data;
    Record ternak;
    int size = 0;


    data.open("data.txt");
    
    data >> ternak.tanggal;
    data >> ternak.ID;
    data >> ternak.jumlahTelur;
    data >> ternak.harga;
    data >> ternak.income;
    
    while (!data.eof()){
        size++;
        data >> ternak.tanggal;
        data >> ternak.ID;
        data >> ternak.jumlahTelur;
        data >> ternak.harga;
        data >> ternak.income;
    }
    
    data.close();

    return size;
}

void readData() {

    int size = dataSize();
    
    Record* readData = new Record[size];

    getDb(readData, size);

    system("clear");
    cout << "Menampilkan Semua Data :\n" << endl;
    cout << "Tanggal\t\t" << "ID Record\t" << "Jumlah Telur" << "\t" << "Harga /Kg\t" << "Total Pemasukan" << endl;
    cout << "================================================================================" << endl;
    for ( int i=0; i<size; i++) {
        cout << readData[i].tanggal << "\t" << readData[i].ID << "\t" << readData[i].jumlahTelur << "\t\t"<< "Rp " << readData[i].harga << "\t"<< "Rp " << readData[i].income << endl; 
    }

    cout << endl;
}

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

void sortQty(struct Record arr[], int n) {
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

void sortData(int x) {
    int size = dataSize();
    
    Record* sortRecord = new Record[size];

    getDb(sortRecord, size);

    if (x == 1) {
        sortDesc(sortRecord, size);
        saveDB(sortRecord, size);
    }
    else if ( x== 2) {
        sortQty(sortRecord, size);
        saveDB(sortRecord, size);
    }
    
    system("clear");
    cout << "Hasil Pengurutan Data :\n" << endl;
    cout << "Tanggal\t\t" << "ID Record\t" << "Jumlah Telur" << "\t" << "Harga /Kg\t" << "Total Pemasukan" << endl;
    cout << "================================================================================" << endl;
    for ( int i=0; i<size; i++) {
        cout << sortRecord[i].tanggal << "\t" << sortRecord[i].ID << "\t" << sortRecord[i].jumlahTelur << "\t\t"<< "Rp " << sortRecord[i].harga << "\t"<< "Rp " << sortRecord[i].income << endl;  
    }

    cout << endl;
    
}

void saveDB(struct Record sortRecord[], int size) {

    fstream Database;
    Database.open("data.txt", ios::trunc | ios::out);

    for (int i=0; i < size; i++){

        Database << sortRecord[i].tanggal << "    " << sortRecord[i].ID << "   " << sortRecord[i].jumlahTelur << "      " << sortRecord[i].harga  << "         " << sortRecord[i].income << endl;
    }

    Database.close();
}

void printErr () {
    system ("clear");
    cout << "\n\nKeyword Invalid / Data Tidak Ada\n\n"<< endl;
}

void searchData () {
    string keyword;
    int ind= 0;

    int size = dataSize();
    
    Record* array = new Record[size];

    getDb(array, size);

    cout<<"Masukkan Tanggal Record (dd/mm/yyyy) : ";
    cin >> keyword;

    system("clear");
    cout << "Hasil Pencarian :" << endl;
    cout << "Tanggal\t\t" << "ID Record\t" << "Jumlah Telur" << "\t" << "Harga /Kg\t" << "Total Pemasukan" << endl;
    cout << "================================================================================" << endl;
    for(int i=0;i<size;i++) {
        if(array[i].tanggal==keyword) {
            cout << array[i].tanggal << "\t" << array[i].ID << "\t" << array[i].jumlahTelur << "\t\t"<< "Rp " << array[i].harga << "\t"<< "Rp " << array[i].income << endl;
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

void updateData() {
    string keyword, tanggal,bulan,tahun, tgl;
    int income;

    int size = dataSize();
    
    Record* array = new Record[size];

    getDb(array, size);

    readData();

    cout<<"Masukkan Tanggal Record Untuk Update Data (dd/mm/yyyy) : ";
    cin >> keyword;

    for(int i=0;i<size;i++) {
        if(array[i].tanggal==keyword) {
            cout << "Tanggal\t\t" << "ID Record\t" << "Jumlah Telur" << "\t" << "Harga /Kg\t" << "Total Pemasukan" << endl;
            cout << "================================================================================" << endl;
            cout << array[i].tanggal << "\t" << array[i].ID << "\t" << array[i].jumlahTelur << "\t\t"<< "Rp " << array[i].harga << "\t"<< "Rp " << array[i].income << endl; 

            cout << "\nMasukkan Data Baru : " << endl;
                cout << "Masukkan Tanggal \t\t: ";
                cin >> tanggal;
                cout << "Masukkan Bulan \t\t\t: ";
                cin >> bulan;
                cout << "Masukkan Tahun \t\t\t: ";
                cin >> tahun;

                array[i].tanggal = tanggal + "/" + bulan + "/" + tahun;
                array[i].ID = tahun + bulan + tanggal;

                cout << "Masukkan Jumlah Telur \t\t: ";
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