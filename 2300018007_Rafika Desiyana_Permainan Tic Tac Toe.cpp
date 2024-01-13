#include <iostream>
using namespace std;

struct Pemain { // berfungsi untuk membuat tipe data baru yang terdiri dari beberapa tipe data lainnya
    string nama;
    char simbol;
    int menang;
};

char papan[3][3] = {{' ',' ',' '},{' ',' ',' '},{' ',' ',' '}}; // ddeklarasi array untuk papan permainan

void mulaipermainan() { // fungsi untuk menampilkan papan permainan
    cout << "PERHATIKAN PENOMORAN KOTAK DIBAWAH INI!!!" << endl;
    cout << "  1 | 2 | 3 " << endl;
    cout << "------------" << endl;
    cout << "  4 | 5 | 6 " << endl;
    cout << "------------" << endl;
    cout << "  7 | 8 | 9 " << endl;
    cout << "------------" << endl;
    cout << endl;
    
    cout << "************" << endl;
    cout << endl;
    
    for (int i = 0; i < 3; i++) { // berfungsi untuk mencetak baris dan kolom tic tac toe dengan memanggil array 2 dimensi yaitu papan
        cout << "  " << papan[i][0] << " | " << papan[i][1] << " | " << papan[i][2] << " \n";
        if (i < 2) { 
            cout << "-------------\n";
        }
    }
}

bool cekpemenang(char pemain) { // berfungsi untuk mengecek pemenang yakni baris, kolom dan diagonal
    for (int i = 0; i < 3; i++) {
        if ((papan[i][0] == pemain && papan[i][1] == pemain && papan[i][2] == pemain) || // baris
            (papan[0][i] == pemain && papan[1][i] == pemain && papan[2][i] == pemain)) { // kolom
            return true; 
        }
    }

    if ((papan[0][0] == pemain && papan[1][1] == pemain && papan[2][2] == pemain) || // diagonal utama
        (papan[0][2] == pemain && papan[1][1] == pemain && papan[2][0] == pemain)) { // diagonal sekunder
        return true;
    }

    return false;
}

bool cekseri() { // berfungsi untuk mengecek seri dengan menggunkan perulangan for dengan jumlah baris dan kolom terisi semua
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (papan[i][j] != 'X' && papan[i][j] != 'O') {
                return false;  // Ada kotak yang masih kosong
            }
        }
    }
    return true;  // Semua kotak terisi
}

int inputpemain(Pemain& pemain) { // berfungsi untuk pergantian pemain
    int choice;
    cout << "Giliran pemain " << pemain.nama << " (" << pemain.simbol << "). Masukkan nomor kotak yang ingin ditandai: ";
    cin >> choice;

    while (choice < 1 || choice > 9 || papan[(choice-1)/3][(choice-1)%3] == 'X' || papan[(choice-1)/3][(choice-1)%3] == 'O') {
        cout << "Input tidak valid. Masukkan nomor kotak yang kosong antara 1 sampai 9: ";
        cin >> choice;
    }

    return choice;
}

void langkahpermainan(int choice, char simbol) {  // fungsi untuk mengganti isi array dengan simbol pemain
    papan[(choice-1)/3][(choice-1)%3] = simbol; // mengganti nilai dengan simbol pemain
}

int main() { // fungsi utama dalam menjalankan permainan Tic Tac Toe 
    Pemain pemainX = {"Pemain X", 'X', 0};
    Pemain pemainO = {"Pemain O", 'O', 0};

    bool gameselesai = false; 
    char pemenang;
    char mengulanggame;

    do {
        mulaipermainan();
        
        int pilihan = inputpemain(pemainX);
        langkahpermainan(pilihan, pemainX.simbol);
        if (cekpemenang(pemainX.simbol)) {
            gameselesai = true;
            pemenang = pemainX.simbol;
        } else {
            mulaipermainan();

            pilihan = inputpemain(pemainO);
            langkahpermainan(pilihan, pemainO.simbol);
            if (cekpemenang(pemainO.simbol)) {
                gameselesai = true;
                pemenang = pemainO.simbol;
            }
        }

        if (!gameselesai) {
            mulaipermainan();

            if (cekseri()) {
                gameselesai = true;
                pemenang = 'S'; // Seri
            }
        }

        if (gameselesai) {
            mulaipermainan();
            if (pemenang == 'S') {
                cout << "Permainan berakhir seri!" << endl;
            } else {
                cout << "Pemenangnya adalah " << (pemenang == pemainX.simbol ? pemainX.nama : pemainO.nama) << endl;
            }

            cout << "Apakah Anda ingin bermain lagi? (Y/T): ";
            cin >> mengulanggame;

            if (mengulanggame == 'Y' || mengulanggame == 'y') { // jika ingin mengulang lagi permainan
                gameselesai = false;
                // Mengosongkan papan permainan
                for (int i = 0; i < 3; i++) {
                    for (int j = 0; j < 3; j++) {
                        papan[i][j] = ' ';
                    }
                }
            }
        }
    } while (!gameselesai); // mengulang permainan sampai ada pemenang atau seri

    return 0;
}

