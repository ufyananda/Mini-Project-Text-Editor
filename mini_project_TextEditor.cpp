/*
Mini Project Pemrograman Berorientasi Objek (Teks Editor)
1. UFY ANANDA YATNA (221402060)
2. MUHAMMAD NAYAKA PUTRA (221402001)
3. FILDZA RASYIKA (221402101)
4. RUTH LIMIKE PUTERI SIHALOHO (221402128)
*/

#include <iostream> 
#include <fstream> 
#include <vector>
#include <limits>
#include <iomanip>

using namespace std;

class TextEditor {
private:
    string fileName;            //Menyimpan nama file yang sedang aktif.
    vector<string> lines;       //Menyimpan konten file dalam bentuk vektor string, di mana setiap string mewakili satu baris dalam file.
    int cursorPosition;         //Menyimpan posisi kursor saat ini dalam file.

public:
    TextEditor();               //Constructor

    //fitur pada menu pilihan utama
    void createFile();          //membuat file                                  {{ Nayaka Putra }} 
    void emptyFile();           //mengosongkan isi file                         {{ Nayaka Putra }}
    void deleteFile();          //menghapus file                                {{ Nayaka Putra }}
    void copyFile();            //menyalin file                                 {{ Fildza Rasyika }}
    void compileAndRun();       //mengkompilasi dan menjalankan file            {{ Ruth Sihaloho }}
    void readFile();            //membaca file                                  {{ Fildza Rasyika }}
    void choice();              //menampilkan menu pilihan utama                {{ Ruth Sihaloho }}

    //fitur pada menu pilihan edit (setelah masuk fungsi readFile)
    void addText();             //menambah teks pada file                       {{ Ufy Ananda }}
    void deleteText();          //menghapus teks pada file                      {{ Ufy Ananda }}
    void editText();            //mengubah teks pada file                       {{ Ufy Ananda }}
    void findText();            //mencari teks pada file                        {{ Ufy Ananda }}
    void save();                //menyimpan teks yang telah diedit pada file    {{ Fildza Rasyika }}
    void edit();                //menampilkan menu pilihan edit                 {{ Ruth Sihaloho }}

    ~TextEditor(){}             //Destructor
};


//fungsi Konstruktor TextEditor untuk menginisialisasi objek TextEditor dengan memberikan nilai awal filename dan cursorPosition
TextEditor::TextEditor() { 
    fileName = fileName;
    cursorPosition = (0);
}


void TextEditor::createFile() { 
    cout << "Masukkan nama file berekstensi (contoh : uwau.txt): ";
    cin >> fileName;
    ofstream file(fileName);                                    //file dibuat menggunakan objek ofstream bernama file sesuai inputan
    if (file) {
        cout << "File berhasil dibuat." << endl;
        file.close();
    } else {
        cout << "File gagal dibuat." << endl;
    }
}
/*  fungsi createFile membuat file baru dengan nama file yang dimasukkan oleh pengguna.
    fungsi dibuat   : M. Nayaka Putra -> 21/May/2023    */


void TextEditor::emptyFile() {
    cout << "Masukkan nama file: ";
    cin >> fileName;
    ifstream inputFile(fileName); 

    if (inputFile.is_open()) {                                  //last update : pengecekan file tersedia
        inputFile.close();

        ofstream outputFile(fileName, ios::trunc);              //code utama untuk mengosongkan teks pada file menggunakan objek ofstream dengan mode ios::trunc

        if (outputFile.is_open()) {
            outputFile.close();
            cout << "File berhasil dikosongkan.\n";
        } else {
            cout << "Gagal membuka file untuk pengosongan.\n";
        }
    } else {
        cout << "Gagal membuka file.\n";
    }
}
/*  fungsi emptyFile mengosongkan isi file yang dimasukkan oleh pengguna.
    fungsi dibuat   : M. Nayaka Putra -> 21/May/2023
    fungsi diupdate : Ufy Ananda Yatna -> 23/May/2023       */


void TextEditor::deleteFile() { 
    cout << "Masukkan nama file: "; 
    cin >> fileName;
    if (remove(fileName.c_str()) == 0) {                        //fungsi remove menghapus file, jika menghasilkan 0 maka fungsi tidak menghasilkan pesan kesalahan dan file berhasil diapus
        cout << "File berhasil dihapus." << endl;
    } else {
        cout << "File gagal dihapus." << endl;
    }
}
/*  fungsi deleteFile menghapus file yang dimasukkan oleh pengguna.
    fungsi dibuat   : M. Nayaka Putra -> 21/May/2023    */


void TextEditor::copyFile() {
    string newFileName;
    cout << "Masukkan nama file yang ingin disalin: ";
    cin >> fileName;
    cout << "Masukkan nama file baru: "; 
    cin >> newFileName;

    ifstream sourceFile(fileName);
    ofstream destFile(newFileName);

    if (sourceFile && destFile) { 
        destFile << sourceFile.rdbuf();                         //fungsi rdbuf() sebagai fungsi utama digunakan untuk menyalin file
        cout << "File berhasil disalin." << endl;
    } else {
        cout << "Gagal menyalin file." << endl;
    }

    sourceFile.close();
    destFile.close();
}
/*  fungsi copyFile menyalin isi file yang dimasukkan oleh pengguna ke file baru.
    fungsi dibuat   : Fildza Rasyika -> 22/May/2023    */


void TextEditor::compileAndRun() {
    cout << "Masukkan nama file dengan ekstensi .cpp (contoh: test.cpp): ";
    cin >> fileName;

    string compileCommand = "g++ " + fileName + " -o temp";     //last update : variabel compileCommand dan runCommand bertipe string untuk menampung string command line
    string runCommand = "temp.exe";

    int compileResult = system(compileCommand.c_str());         //code utama untuk mengkompilasi file yaitu system(compileComand.c_str()) untuk menjalankan command pada system terminal
    if (compileResult == 0) {
        cout << "Program berhasil dikompilasi." << "\033[33m" << endl;
        int runResult = system(runCommand.c_str());             //code utama untuk run file yaitu system(runComand.c_str()) untuk menjalankan command pada system terminal
        cout << "\033[0m";
        if (runResult != 0) {
            cout << "Program tidak dapat dijalankan." << endl;
        }
    } else {
        cout << "Program gagal dikompilasi." << endl;
    }
}
/*  fungsi compileAndRun mengompilasi dan menjalankan program C++ yang dimasukkan oleh pengguna.
    fungsi dibuat   : Ruth Limike Puteri Sihaloho -> 25/May/2023
    fungsi diupdate : Ufy Ananda Yatna -> 26/May/2023   */


void TextEditor::readFile() { 
    cout << "Masukkan nama file : ";
    cin >> fileName;
    ifstream file(fileName);
    if (file.is_open()) {
        string line;
        while (getline(file, line)) {
            lines.push_back(line);                  //code utama untuk membaca file yaitu push_back() yang merupakan fungsi khusus pada vector
        }
        file.close();
        edit();
    }
    else {
        cout << "File tidak ditemukan." << endl;
    }
    lines.clear();
}
/*  fungsi readFile membaca isi file yang dimasukkan oleh pengguna dan menyimpannya dalam vektor lines.
    fungsi dibuat   : Fildza Rasyika -> 23/May/2023    */


void TextEditor::choice() {
    char command;
    do {
        system("cls");
        cout << "\033[32m";
        cout << "~~~~~~~~~~~~~~~" << endl;
        cout << "| TEKS EDITOR |" << endl;
        cout << "~~~~~~~~~~~~~~~" << endl;
        cout << endl;
        cout << "\033[35m";
        cout << "----------------------" << endl;
        cout << "# menu pilihan utama #" << endl;
        cout << "----------------------" << endl;
        cout << "\033[0m";
        cout << "R - baca file" << endl;
        cout << "C - buat file" << endl;
        cout << "E - kosongkan file" << endl;
        cout << "D - hapus file" << endl;
        cout << "G - salin file" << endl;
        cout << "O - kompilasi dan jalankan file" << endl;
        cout << "Q - exit" << endl;
        cout << "Pilih perintah: ";
        cin >> command;
        switch (command) {
            case 'R':
                readFile();
                break;
            case 'C':
                createFile();
                break;
            case 'E':
                emptyFile();
                break;
            case 'D':
                deleteFile();
                break;
            case 'G':
                copyFile();
                break;
            case 'O':
                compileAndRun();
                break;
            case 'Q':
                break;
            default:
                cout << "Perintah tidak valid." << endl;
                break;
        }
        cout << "Tekan Enter untuk melanjutkan...";
        cin.ignore();
        cin.get();
    } while (command != 'Q');
}
/*  fungsi choice menampilkan menu pilihan utama untuk pengguna dan memanggil fungsi yang sesuai berdasarkan pilihan pengguna.
    fungsi dibuat   : Ruth Limike Puteri Sihaloho -> 23/May/2023    */


void TextEditor::addText() {
    cin.ignore(numeric_limits<streamsize>::max(), '\n');            //untuk mengabaikan/menghapus karakter yang tersisa setelah membaca inputan sebelumnya
    string newText;
    
    cout << "Masukkan posisi kursor(pilih baris): ";
    cin >> cursorPosition;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    cout << "Teks baru(ketik xx untuk menyelesaikan): \n";

    while (true) {
        int i = cursorPosition - 1;
        getline(cin, newText);

        if (newText == "xx") {                                      //kondisi untuk menyelesaikan inputan teks
            lines.erase(lines.begin() + i);
            break;
        }

        lines.insert(lines.begin() + cursorPosition, "");           //fungsi insert() untuk memasukan baris baru
        lines[i].append(newText);                                   //fungsi append() untuk menambahkan teks ke dalam baris baru
        cursorPosition++;
    }
}
/*  fungsi addText menambahkan teks pada posisi kursor yang ditentukan oleh pengguna ke dalam lines.
    fungsi dibuat   : Ufy Ananda Yatna -> 25/May/2023    */


void TextEditor::deleteText() {
    int i, j;
    int cursor;
    int length;
    char command;
    do {
        int k = 1;
        system("cls");
        for (const string& line : lines) {
            cout << "\033[34m" << setw(3) << k << " " << "\033[37m" << line << endl;
            k++;
        }
        cout << endl;
        cout << "\033[35m";
        cout << "Hapus Teks : " << endl;
        cout << "\033[0m";
        cout << "B - hapus baris" << endl;
        cout << "T - hapus teks" << endl;
        cout << "Q - kembali ke menu edit" << endl;
        cout << "Pilih perintah: ";
        cin >> command;
        switch (command) {
            case 'B':                                                                   //case untuk menghapus setiap baris
                cout << "Masukkan posisi kursor (pilih baris) : ";
                cin >> cursorPosition;
                cout << "Masukkan banyak baris yang akan dihapus : ";
                cin >> length;
                i = cursorPosition - 1;
                if (i >= 0 && i + length <= lines[i].size()) {
                    lines.erase(lines.begin() + i, lines.begin() + i + length);         //fungsi erase() untuk menghapus baris
                    cout << "Baris telah dihapus" << endl;
                } else {
                    cout << "banyak baris melebihi batas." << endl;
                }
                break;
            case 'T':                                                                   //case untuk menghapus teks pada baris
                cout << "Masukkan posisi kursor (pilih baris) : ";
                cin >> cursorPosition;
                cout << "Masukkan posisi kursor (pilih character) : ";
                cin >> cursor;
                cout << "Masukkan panjang (character) yang akan dihapus : ";
                cin >> length;
                i = cursorPosition - 1;
                j = cursor - 1;
                if (i >= 0 && i <= lines.size() && j >= 0 && j < lines[i].size()){
                    lines[i].erase(lines[i].begin() + j, lines[i].begin() + j + length); //fungsi erase() untuk menghapus baris
                } else {
                    cout << "Baris tidak ditemukan" << endl;
                }
                break;
            case 'Q':
                break;
            default:
                cout << "Perintah tidak valid." << endl;
                break;
        }
        cout << "Tekan Enter untuk melanjutkan...";
        cin.ignore();
        cin.get();
    } while (command != 'Q');
}
/*  fungsi deleteText menghapus teks/baris yang dipilih oleh pengguna dari lines.
    fungsi dibuat   : Ufy Ananda Yatna -> 25/May/2023    */


void TextEditor::editText() {
    cin.ignore();
    string newText;
    int i, j, cursor, length;
    char command;
    do {
        int k = 1;
        system("cls");
        for (const string& line : lines) {
            cout << "\033[34m" << setw(3) << k << " " << "\033[37m" << line << endl;
            k++;
        }
        cout << endl;
        cout << "\033[35m";
        cout << "Ubah Teks : " << endl;
        cout << "\033[0m";
        cout << "B - ubah baris" << endl;
        cout << "T - ubah teks" << endl;
        cout << "Q - kembali ke menu edit" << endl;
        cout << "Pilih perintah: ";
        cin >> command;
        switch (command) {
            case 'B':                                                                       //case untuk mengubah baris
                cout << "Masukkan posisi kursor (pilih baris) : ";
                cin >> cursorPosition;
                cin.ignore();
                cout << "Teks baru : ";
                getline(cin, newText);
                i = cursorPosition - 1;
                if (i >= 0 && i < lines[i].size()) {
                    lines.erase(lines.begin() + i);                                         //fungsi erase() untuk menghapus baris yang dipilih
                    lines.insert(lines.begin() + i, "");                                    //fungsi insert() untuk memasukan baris baru
                    lines[i].append(newText);                                               //fungsi append() untuk menambahkan teks ke dalam baris baru
                    cout << "Baris berhasil diubah" << endl;
                } else {
                    cout << "Baris tidak ditemukan." << endl;
                }
                break;
            case 'T':                                                                       //case untuk mengubah teks pada baris
                cout << "Masukkan posisi kursor (pilih baris) : ";
                cin >> cursorPosition;
                cout << "Masukkan posisi kursor (pilih character) : ";
                cin >> cursor;
                cout << "Masukkan panjang (character) yang akan diubah : ";
                cin >> length;
                cin.ignore();
                cout << "Teks baru : ";
                getline(cin, newText);
                i = cursorPosition - 1;
                j = cursor - 1;
                if (i >= 0 && i < lines.size()){
                    if(j >= 0 && j < lines[i].size()){
                        lines[i].erase(lines[i].begin() + j, lines[i].begin() + j + length);    //fungsi erase() untuk menghapus teks pada baris
                        lines[i].insert(j, newText);                                            //fungsi insert() untuk menambahkan teks ke dalam character yang dipilih
                    } else {
                        cout << "posisi kursor dalam baris (character) tidak ditemukan";
                    }
                } else {
                    cout << "Baris tidak ditemukan" << endl;
                }
                break;
            case 'Q':
                break;
            default:
                cout << "Perintah tidak valid." << endl;
                break;
        }
        cout << "Tekan Enter untuk melanjutkan...";
        cin.ignore();
        cin.get();
    } while (command != 'Q');
}
/*  fungsi editText mengubah teks yang dipilih oleh pengguna dalam lines.
    fungsi dibuat   : Ufy Ananda Yatna -> 25/May/2023    */


void TextEditor::findText() {
    string findStr, replaceStr;
    cout << "Masukkan teks yang ingin ditemukan: ";
    cin.ignore();
    getline(cin, findStr);

    for (char& c : findStr) {
        c = std::tolower(c);                                                                    //perulangan untuk menjadikan semua karakter menjadi huruf kecil menggunakan fungsi tolower()
    }

    for (size_t i = 0; i < lines.size(); i++) {
        size_t pos = lines[i].find(findStr);
        if(true){
            cout << "kata \"" << "\033[33m" << findStr << "\033[0m" << "\" ditemukan pada kalimat: " << endl;   //perulangan untuk mengecek apakah kata yang dicari terdapat pada baris.
            break;
        }
    }

    for (size_t i = 0; i < lines.size(); i++) {                                                 //perulangan untuk mengecek satu persatu karakter.
        string lowercaseLine = lines[i];
        for (char& c : lowercaseLine) {
            c = std::tolower(c);                                                                //perulangan untuk merubah karater menjadi huruf kecil menggunakan fungsi tolower().
        }

        size_t pos = lowercaseLine.find(findStr);                                               //fungsi yang digunakan untuk mencari kemunculan pertama dari findStr dalam lowercaseLine.
        while (pos != string::npos) {                                                           //Jika findStr ditemukan, posisi kemunculannya akan dikembalikan. Jika tidak, fungsi mengembalikan string::npos (nilai khusus yang menandakan tidak ditemukannya string).
            cout << "\033[33m" << lines[i] << "\033[0m" << " (baris ke " << i + 1 << ")" << endl;               
            pos = lowercaseLine.find(findStr, pos + findStr.length());
        }
    }
}
/*  fungsi findText mencari teks yang dimasukkan oleh pengguna dalam lines.
    fungsi dibuat   : Ufy Ananda Yatna -> 25/May/2023    */


void TextEditor::save() {
    ofstream file(fileName);
    if (file.is_open()) {                           //last update : pengkondisian if else untuk mengecek fileName
        for (const string& line : lines) {
            file << line << endl;                   //code utama untuk menyimpan file yaitu memasukkan seluruh perubahan pada lines ke file
        }
        file.close();
        cout << "File berhasil disimpan." << endl;
    }
    else {
        cout << "File tidak dapat disimpan." << endl;
    }
}
/*  fungsi save menyimpan perubahan yang dilakukan pada lines ke file yang sedang aktif.
    fungsi dibuat   : Fildza Rasyika -> 23/May/2023
    fungsi diupdate : Ufy Ananda Yatna -> 25/May/2023    */


void TextEditor::edit() {
    char command;
    do {
        int k = 1;
        system("cls");
        for (const string& line : lines) {
            cout << "\033[34m" << setw(3) << k << " " << "\033[37m" << line << endl;
            k++;
        }
        cout << endl;
        cout << "\033[35m";
        cout << "-------------" << endl;
        cout << "# Edit Teks # " << endl;
        cout << "-------------" << endl;
        cout << "\033[0m";
        cout << "A - tambah teks" << endl;
        cout << "D - hapus teks" << endl;
        cout << "E - ubah teks" << endl;
        cout << "F - cari teks" << endl;
        cout << "S - simpan dan keluar" << endl;
        cout << "Q - keluar tanpa menyimpan" << endl;
        cout << "Pilih perintah: ";
        cin >> command;
        switch (command) {
            case 'A':
                addText();
                break;
            case 'D':
                deleteText();
                break;
            case 'E':
                editText();
                break;
            case 'F':
                findText();
                break;
            case 'S': 
                save();
                break;
            case 'Q':
                cout << "Keluar tanpa menyimpan." << endl;
                break;
            default:
                cout << "Perintah tidak valid." << endl;
                break;
        }
        cout << "Tekan Enter untuk melanjutkan...";
        cin.ignore();
        cin.get();
    } while (command != 'Q' && command != 'S');
}
/*  fungsi edit menampilkan menu pilihan edit untuk pengguna dan memanggil fungsi yang sesuai berdasarkan pilihan pengguna.
    fungsi dibuat   : Ruth Limike Puteri Sihaloho -> 23/May/2023    */


int main() {
    TextEditor editor;
    editor.choice();

    return 0;
}