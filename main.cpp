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

struct Temp {
	string tanggal;
	int ID;
    string jumlahTelur;
};

void addData();
void inputData();
void readData();
void printData();
void sortDesc();
void sortData();

int main() {
    string x;

    menu:
    // system("cls");
    cout << "Pilih Jenis Operasi :" << endl;
    cout << "1. Tambah Data" << endl;
    cout << "2. Tampilkan Seluruh Data" << endl;
    cout << "3. Cari Record Data" << endl;
    cout << "4. Exit" << endl;
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
        while (j >= 0 && arr[j].ID < key.ID) {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
            arr[j + 1] = key;
    }
}

void printData (struct Temp array[], int n) {
    int i;
    cout << "\nHasil Pengurutan Data Mahasiswa :\n" << endl;
        for (i=0;i<n;i++) {
            cout << array[i].tanggal << "\t\t" << array[i].ID << "\t\t" << array[i].jumlahTelur << endl;
            i++;
	} 
    cout << endl;   
}

void sortData() {
    ifstream data;
    data.open("data.txt");
    int n = 0;

    Temp array[n];


    data >> ternak.tanggal;
    data >> ternak.ID;
    data >> ternak.jumlahTelur;
    
    while (!data.eof()){

        ternak.tanggal = array[n].tanggal;

        data >> ternak.tanggal;
        data >> ternak.ID;
        data >> ternak.jumlahTelur;
        n++;
    }

    data.close();

    cout << n << endl;
    cout << array[1].tanggal<< endl;

    // sortDesc(array, n);
    printData(array, n);
}
