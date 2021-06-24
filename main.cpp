#include <iostream>
#include <array>
#include <cstdlib>
#include <fstream>
#include <ctime>

using namespace std;

struct Record {
	string tanggal;
	int ID;
    string jumlahTelur;
}ternak;

void addData();
void inputData();
void readData();
void sortData();

int main() {
    string x;

    menu:
    // system("cls");
    cout << "Pilih Jenis Operasi :" << endl;
    cout << "1. Tambah Data" << endl;
    cout << "2. Tampilkan Seluruh Data" << endl;
    cout << "3. Exit" << endl;
    cout << endl;

    cout << "Pilih Menu [1-3]: ";
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
    else if (x == "4") {
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

    cout << "Input Record Harian" << endl;
    cout << "Masukkan Tanggal \t: ";
    cin >> ternak.tanggal;

    ternak.ID = rand();

    cout << "Masukkan Jumlah \t: ";
    cin >> ternak.jumlahTelur;

    addData();
}

void addData() {
    fstream data;
    data.open("data.txt", ios::app);

    data << ternak.tanggal <<endl;
    data << ternak.ID << endl;
    data << ternak.jumlahTelur << endl << endl;

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

void sortData() {
    ifstream data;
    data.open("data.txt");


    data >> ternak.tanggal;
    data >> ternak.ID;
    data >> ternak.jumlahTelur;
    
    while (!data.eof()){

        data >> ternak.tanggal;
        data >> ternak.ID;
        data >> ternak.jumlahTelur;
    }

    int size = sizeof(Record);
    
    Record* array = new Record[size];

    

    data.close();
}