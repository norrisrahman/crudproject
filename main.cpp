#include <iostream>
#include <array>
#include <cstdlib>
#include <fstream>
#include <ctime>
#include <string>

using namespace std;

struct Record {
	string tanggal;
	string ID;
    string jumlahTelur;
}ternak;

void addData();
void inputData();
void readData();
void printData();
int dataSize(fstream &Database);
void sortData(int x);
void saveDB(struct Record sortRecord[], int size);
void searchData();
void Search();

int main() {
    string x;

    menu:
    // system("cls");
    cout << "Pilih Jenis Operasi :" << endl;
    cout << "1. Tambah Data" << endl;
    cout << "2. Tampilkan Seluruh Data" << endl;
    cout << "3. Urutkan Data dari Data Terbaru" << endl;
    cout << "4. Urutkan Data Berdasarkan Jumlah Telur" << endl;
    cout << "5. Mencari Data" << endl;
    cout << "6. Exit" << endl;
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
    else if (x == "6") {
        system("cls");
        atexit;
    }
    else {
        cout << "\nInput Tidak Valid !!! \n" << endl;
        goto menu;
    }
	return 0;
}

void inputData() {
    srand((unsigned)time(0));
    string tanggal,bulan,tahun, tgl;

    cout << "Input Record Harian" << endl;
    cout << "Masukkan Tanggal \t: ";
    cin >> tanggal;
    cout << "Masukkan Bulan \t: ";
    cin >> bulan;
    cout << "Masukkan Tahun \t: ";
    cin >> tahun;

    ternak.tanggal = tanggal + "/" + bulan + "/" + tahun;

    ternak.ID = tahun + bulan + tanggal;

    cout << "Masukkan Jumlah \t: ";
    cin >> ternak.jumlahTelur;

    addData();
}

void addData() {
    fstream data;
    data.open("data.txt", ios::app);

    data << ternak.tanggal << "    "<< ternak.ID << "   " << ternak.jumlahTelur << endl;

    data.close();
}

void readData() {
    ifstream data;
    data.open("data.txt");

    data >> ternak.tanggal;
    data >> ternak.ID;
    data >> ternak.jumlahTelur;
    
    cout << "\nMenampilkan Semua Record Data :\n" << endl;
    cout << "Tanggal\t\t\t" << "ID Record\t" << "Jumlah Telur\t\t" << endl;
    cout << "=====================================================" << endl;
    while (!data.eof()){
        cout << ternak.tanggal << "\t\t" << ternak.ID << "\t\t" << ternak.jumlahTelur << endl;

        data >> ternak.tanggal;
        data >> ternak.ID;
        data >> ternak.jumlahTelur;
    }
    cout << endl;
    data.close();
}

void sortDesc(struct Record arr[], int n){
    int i, j;
    struct Record key;
    for (i = 1; i < n; i++) {
        key = arr[i];
        j = i - 1;        
        while (j >= 0 && arr[j].tanggal < key.tanggal) {
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
        while (j >= 0 && arr[j].jumlahTelur > key.jumlahTelur) {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
            arr[j + 1] = key;
    }
}

int dataSize(fstream &Database) {
    Record dataSize;
    int size;


    Database.open("data.txt");
    while (getline(Database, dataSize.tanggal))
        size++;

    Database.close();

    return size ;
}

void sortData(int x) {
    fstream Database;
    int size;

    size = dataSize(Database);

    Database.open("data.txt");

    Record* sortRecord = new Record[size];

    for(int i = 0; i<size; i++){

        Database >> sortRecord[i].tanggal;
        Database >> sortRecord[i].ID;
        Database >> sortRecord[i].jumlahTelur;
    }

    Database.close();

    if (x == 1) {
        sortDesc(sortRecord, size);
        saveDB(sortRecord, size);
    }
    else if ( x== 2) {
        sortQty(sortRecord, size);
        saveDB(sortRecord, size);
    }
}

void saveDB(struct Record sortRecord[], int size) {

    fstream Database;
    Database.open("data.txt", ios::trunc | ios::out);

    for (int i=0; i < size; i++){

        Database << sortRecord[i].tanggal << "    "<< sortRecord[i].ID << "   " << sortRecord[i].jumlahTelur << endl;
    }

    Database.close();
}

void printErr () {
    cout << "\n\nKeyword Invalid / Data Tidak Ada\n\n"<< endl;
}

void printSearch (Record array) {
    cout << "\nHasil Pencarian Data Mahasiswa :\n" << endl;
    cout << array.tanggal << "\t\t" << array.ID << "\t\t" << array.jumlahTelur << endl;
    cout << endl; 
}

void Search(){
    cout << "Hello" << endl;
}

void searchData () {
    string keyword;
    int size;

    fstream Database;

    size = dataSize(Database);

    Database.open("data.txt");

    Record* array = new Record[size];

    for(int i = 0; i<size; i++){

        Database >> array[i].tanggal;
        Database >> array[i].ID;
        Database >> array[i].jumlahTelur;
    }

    Database.close();

    cout<<"Masukkan Tanggal Record (dd/mm/yyyy) : ";
    cin >> keyword;

    for(int i=0;i<size;i++) {
        if(array[i].tanggal==keyword) {
            printSearch(array[i]);
            return;
        }
    }
    printErr();
}