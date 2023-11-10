#include <iostream>
#include <string>
#include <stdlib.h>
#include <cmath>
#include <fstream>
#include <sstream>

using namespace std;

struct hp {
    string merkbarang;
    string jenisbarang;
    long long hargabarang;
    int stokbarang;
    hp* next;
};

struct User {
    string username;
    string password;
    bool isAdmin;
    User* next;
};

struct order {
    string id;
    string item;
    int quantity;
    bool statusProsesAdmin;

    string merk;
    string jenis;
    int stok;
    order* next;
};

User* userHead = nullptr;
hp* hphead = nullptr;
order* orderhead = nullptr;

string pilih;
string lanjut = "ya";
string targetId;
string usernameUserLogin;

void display() {
        system ("cls");
        hp* temp = hphead;
	    if (temp == nullptr) {
            cout<<"\n=================================================="<<endl;
            cout << "\t   TIDAK ADA DATA YANG TERSEDIA"<<endl;
            cout<<"=================================================="<<endl;
		return;
	    }

        system ("cls");
        cout<<"=================================================="<<endl;
        cout <<"\t\tDATA HANDPHONE SONIC PHONE\n";
        cout<<"=================================================="<<endl;
        int index = 1;
        while (temp != nullptr) {
            cout << index << "\tMerk\t: " << temp->merkbarang << endl;
            cout << "\tJenis\t: " << temp->jenisbarang << endl;
            cout << "\tHarga\t: " <<temp->hargabarang << endl;
            cout << "\tStok\t: "<< temp->stokbarang << endl<< endl;
            temp = temp->next;
            index++;
        }
}

void savehpToCSV() {
    ofstream file("hp.csv");
    hp* temp = hphead;
    while (temp != nullptr) {
        file << temp->merkbarang << "," << temp->jenisbarang << "," << temp->hargabarang << "," << temp->stokbarang << endl;
        temp = temp->next;
    }
    file.close();
}

void add() {
	do {
        system("cls");
		display();

        hp* newNode = new hp();
		cout << "Merk\t: ";
        fflush(stdin);
        getline(cin,newNode->merkbarang);
        cout << "Jenis\t: ";
        fflush(stdin);
        getline(cin,newNode->jenisbarang);
        cout << "Harga\t: ";
        cin >>newNode->hargabarang;
		cout << "Stok\t: ";
        cin >>newNode->stokbarang;
		newNode->next=nullptr;

        if (hphead == nullptr){
            hphead = newNode;
        } else {
            hp* temp = hphead;
            while (temp->next != nullptr){
                temp = temp->next;
            }
            temp->next = newNode;
        }

        savehpToCSV(); //Menyimpan ke file CSV setiap kali menambah data

        system ("cls");
		display();
		cout<<"=================================================="<<endl;
		cout << "\t    DATA BERHASIL DITAMBAH"<<endl;
		cout <<"\t   TAMBAH DATA LAGI [Y/T] : ";
        cin >> lanjut;
        cout<<"\n=================================================="<<endl;
	} while (lanjut == "y");
}

void edit() {
	do {
        system("cls");

		if (hphead == nullptr) {
			cout<<"\n=================================================="<<endl;
			cout <<"\n\t\tTIDAK ADA DATA"<<endl;
			cout<<"=================================================="<<endl;
			return;
		}

		int index;
		display();
		cout<<"\n=================================================="<<endl;
		cout << "MASUKKAN NOMOR DATA : ";
        cin >> index;
		index--;

        hp* temp = hphead;
        int count = 0;
        while (temp != nullptr && count != index){
            temp = temp->next;
            count++;
        }

		if (temp == nullptr) {
            cout << "\t\tNOMOR TIDAK VALID!!!"<<endl;
            continue;
		}

		cout<<"=================================================="<<endl;
        cout << "Merk\t: ";
        fflush(stdin);
        getline(cin,temp->merkbarang);
        cout << "Jenis\t: ";
        fflush(stdin);
        getline(cin,temp->jenisbarang);
        cout << "Harga\t: ";
        cin >> temp->hargabarang;
		cout << "Stok\t: ";
        cin >> temp->stokbarang;
        cout<<"=================================================="<<endl;

        system ("cls");
        display();
		cout<<"=================================================="<<endl;
		cout << "\t     DATA BERHASIL DIUBAH"<<endl;
		cout <<"\t      UBAH LAGI [Y/T] : ";cin >> lanjut;
		cout<<"=================================================="<<endl;
	} while(lanjut == "y");
}

void del() {
	do {
		if (hphead == nullptr) {
			cout<<"=================================================="<<endl;
			cout<<"\n\t\tTIDAK ADA DATA"<<endl;
			cout<<"=================================================="<<endl;
			return;
		}

		int index;
		display();
		cout<<"\n=================================================="<<endl;
		cout<<"MASUKKAN NOMOR DATA : ";
        cin >> index;
		index--;

        hp* temp = hphead;
        hp* prev = nullptr;
        int count = 0;
        while (temp != nullptr && count != index)
        {
            prev = temp;
            temp = temp->next;
            count++;
        }

		if (temp == nullptr) {
			cout << "\t\tNOMOR TIDAK VALID"<<endl;
		} else {
            if (prev == nullptr){
                hphead = temp->next;
            } else {
                prev->next = temp->next;
            }
            delete temp;
            cout<<"=================================================="<<endl;
		    cout<<"\t  DATA BERHASIL DIHAPUS"<<endl;
        }

        system ("cls");
		display();
		cout<<"\t    HAPUS LAGI [Y/T] : ";
        cin >> lanjut;
		cout<<"\n=================================================="<<endl;
	} while (lanjut == "y");
}

void displayAllUserOrder() {
    //system("cls");
    cout << "==================================================" << endl;
    cout << "=========== I S I  K E R A N J A N G ============" << endl;
    cout << "==================================================" << endl;

    order* temp = orderhead;
    while (temp != nullptr) {
        cout << "ID Pengguna: " << temp->id << endl;
        cout << "Item: " << temp->item << endl;
        cout << "Quantity: " << temp->quantity << endl;
            cout << "Status order : " << ((temp->statusProsesAdmin == false) ? "Belum diproses" : "Sudah diproses") << endl;
        cout << "----------------------------------------------" << endl;
        temp = temp->next;
    }

    cout << "==================================================" << endl;
    cout << "Tekan enter untuk kembali ke menu pengguna...";
    cin.ignore();
    cin.get();
}

void readOrderFromCSV() {
    ifstream file("order.csv");

    if (!file.is_open()) {
        cerr << "Gagal membuka file." << endl;
        exit(1);
    }

    string line;
    string token;
    while (getline(file, line)) {
        order* newNode = new order();

        istringstream iss(line);

        getline(iss, token, ',');
        newNode->id = token;

        getline(iss, token, ',');
        newNode->item= token;

        getline(iss, token, ',');
        newNode->quantity = stoi(token);

        getline(iss, token, ',');
        newNode->statusProsesAdmin = (token == "1");

        if (orderhead == nullptr){
            orderhead= newNode;
        } else {
            order* temp = orderhead;
            while (temp->next != nullptr){
                temp = temp->next;
            }
            temp->next = newNode;
        }

    }

    file.close();
    //displayAllUserOrder();
}


void saveOrderToCSV() {
    ofstream file("order.csv");
    if (!file.is_open()) {
        cerr << "Failed to open order file." << endl;
        return;
    }

    order* temp = orderhead;
    while (temp != nullptr) {
        file << temp->id << "," << temp->item << "," << temp->quantity << "," << temp->statusProsesAdmin << endl;
        temp = temp->next;
    }

    file.close();
}


void displayUserOrder() {
    system("cls");
    cout << "==================================================" << endl;
    cout << "=========== I S I  K E R A N J A N G ============" << endl;
    cout << "==================================================" << endl;

    order* temp = orderhead;
    bool found = false;

    while (temp != nullptr) {
        if (temp->id == usernameUserLogin) {
            cout << "ID Pengguna: " << temp->id << endl;
            cout << "Item: " << temp->item << endl;
            cout << "Quantity: " << temp->quantity << endl;
            cout << "Status order : " << ((temp->statusProsesAdmin == false) ? "Belum diproses" : "Sudah diproses") << endl;
            cout << "----------------------------------------------" << endl;
            found = true;
        }
        temp = temp->next;
    }

    if (!found) {
        cout << "Tidak ada item dalam keranjang untuk ID pengguna ini." << endl;
    }

    cout << "==================================================" << endl;
    cout << "Tekan enter untuk kembali ke menu pengguna...";
    cin.ignore();
    cin.get();
}

void orderUser() {
	do {
        // system("cls");
		// displayuser(targetId);

        order* newNode = new order();
        newNode->id = usernameUserLogin;

        cout << "Masukan item yang ingin dibeli : ";
        fflush(stdin);
        getline(cin, newNode->item);

        cout << "Masukan jumlah item yang ingin dibeli : ";
        fflush(stdin);
        cin >> newNode->quantity;

        newNode->statusProsesAdmin = false;

        if (orderhead == nullptr){
            orderhead= newNode;
        } else {
            order* temp = orderhead;
            while (temp->next != nullptr){
                temp = temp->next;
            }
            temp->next = newNode;
        }

        // system ("cls");
		// displayuser(targetId);

		displayUserOrder();
		saveOrderToCSV();

		cout<<"=================================================="<<endl;
		cout << "\t    DATA BERHASIL DITAMBAH"<<endl;
		cout <<"\t   TAMBAH DATA LAGI [Y/T] : ";
		cin >> lanjut;
        cout<<"\n=================================================="<<endl;
	} while (lanjut == "y");
}

// Fungsi untuk menggabungkan dua array terurut
void merge(hp* arr, int l, int m, int r, bool sortById) {
    int n1 = m - l + 1;
    int n2 = r - m;

    hp* L = new hp[n1];
    hp* R = new hp[n2];

    for (int i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (int j = 0; j < n2; j++)
        R[j] = arr[m + 1 + j];

    int i = 0;
    int j = 0;
    int k = l;
    while (i < n1 && j < n2) {
        if ((sortById && L[i].stokbarang <= R[j].stokbarang) || (!sortById && L[i].merkbarang >= R[j].merkbarang)) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }

    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }

    delete[] L;
    delete[] R;
}

// Fungsi merge sort untuk sorting berdasarkan ID barang
void mergeSort(hp* arr, int l, int r, bool sortById) {
    if (l >= r) {
        return;
    }
    int m = l + (r - l) / 2;
    mergeSort(arr, l, m, sortById);
    mergeSort(arr, m + 1, r, sortById);
    merge(arr, l, m, r, sortById);
}

// Fungsi untuk menampilkan data setelah sorting
void displaySortedData(bool sortById) {
    hp* temp = hphead;
    int index = 1;
    hp* arr = new hp[index];
    while (temp != nullptr) {
        hp* newArr = new hp[index];
        for (int i = 0; i < index - 1; ++i) {
            newArr[i] = arr[i];
        }
        newArr[index - 1] = *temp;
        delete[] arr;
        arr = newArr;
        temp = temp->next;
        ++index;
    }

    mergeSort(arr, 0, index - 2, sortById);

    cout << "==================================================" << endl;
    cout << "     DATA PERALATAN ELEKTRONIK RUMAH TANGGA\n";
    cout << "==================================================" << endl;
    for (int i = 0; i < index - 1; ++i) {
        cout << i + 1 << ".\tMerk\t: " << arr[i].merkbarang << endl;
        cout << ".\tJenis\t: " << arr[i].jenisbarang << endl;
        cout << "\tHarga    : " << arr[i].hargabarang << endl;
        cout << "\tStok\t: " << arr[i].stokbarang << endl;
    }
    delete[] arr;
}

// Fungsi untuk menampilkan menu sorting
void sortMenu() {
    system ("cls");
    bool sortById;
    string sortChoice;
    do {
        cout << "==================================================" << endl;
        cout << "===\t       PILIH JENIS SORTING      \t===" << endl;
        cout << "==================================================" << endl;
        cout << "[1]. Sorting Berdasarkan Stok Barang (Ascending)" << endl;
        cout << "[2]. Sorting Berdasarkan Merk Barang (Descending)" << endl;
        cout << "==================================================" << endl;
        cout << "Pilih jenis sorting : ";
        cin >> sortChoice;
        if (sortChoice == "1") {
            do {
                sortById = true;
                displaySortedData(sortById);
                cout<<"\nKEMBALI KEMENU [Y/T] : ";
                cin>>lanjut;
            } while(lanjut != "y");
        } else if (sortChoice == "2") {
            do {
                sortById = false;
                displaySortedData(sortById);
                cout<<"\nKEMBALI KEMENU [Y/T] : ";
                cin>>lanjut;
            } while(lanjut != "y");
        } else {
            cout << "==================================================" << endl;
            cout << "\t\tNOMOR TIDAK VALID!!!"<<endl;
        }
    } while (sortChoice != "1" && sortChoice != "2");
}

// Fungsi untuk mencari data menggunakan metode Fibonacci search
void fibonacciSearch(string key) {
    int n = 0;
    hp* temp = hphead;

    // Menghitung panjang linked list
    while (temp != nullptr) {
        temp = temp->next;
        n++;
    }

    // Kembalikan temp ke awal linked list
    temp = hphead;

    int fibMinus2 = 0;
    int fibMinus1 = 1;
    int fib = fibMinus1 + fibMinus2;

    // Mencari angka Fibonacci yang lebih besar atau sama dengan n
    while (fib < n) {
        fibMinus2 = fibMinus1;
        fibMinus1 = fib;
        fib = fibMinus1 + fibMinus2;
    }

    int offset = -1;

    // Melakukan pencarian pada linked list menggunakan Fibonacci search
    while (fib > 1) {
        int i = min(offset + fibMinus2, n - 1);

        temp = hphead;
        for (int j = 0; j < i; j++) {
            temp = temp->next;
        }

        // Jika key lebih besar, pindahkan dua angka Fibonacci ke depan
        if (temp->jenisbarang < key) {
            fib = fibMinus1;
            fibMinus1 = fibMinus2;
            fibMinus2 = fib - fibMinus1;
            offset = i;
        }
        // Jika key lebih kecil, pindahkan satu angka Fibonacci ke depan
        else if (temp->jenisbarang > key) {
            fib = fibMinus2;
            fibMinus1 = fibMinus1 - fibMinus2;
            fibMinus2 = fib - fibMinus1;
        }
        // Jika key ditemukan
        else {
            cout<<"=================================================="<< endl;
            cout << "\t\tDATA BERHASIL DITEMUKAN" << endl << endl;
            cout << "Merk\t: " << temp->merkbarang << endl;
            cout << "Jenis\t: " << temp->merkbarang << endl;
            cout << "Harga    : " << temp->hargabarang << endl;
            cout << "Stok\t: " << temp->stokbarang << endl;
            return;
        }
    }

    // Jika key tidak ditemukan
    cout<<"=================================================="<< endl;
    cout << "\t\tDATA TIDAK DITEMUKAN" << endl;
}

// Fungsi untuk melakukan pencarian menggunakan metode Jump Search
void jumpSearch(string key) {
    int n = 0;
    hp* temp = hphead;

    // Menghitung panjang linked list
    while (temp != nullptr) {
        temp = temp->next;
        n++;
    }

    int step = sqrt(n);
    int prev = 0;

    temp = hphead;

    // Melakukan pencarian pada linked list menggunakan Jump Search
    while (temp != nullptr && temp->merkbarang < key) {
        prev = step;
        for (int i = 0; i < step && temp != nullptr; i++) {
            temp = temp->next;
        }
        step = sqrt(step);
    }

    // Menemukan blok yang mungkin berisi elemen yang dicari, lakukan pencarian linear dalam blok
    while (temp != nullptr && temp->merkbarang != key && prev < n) {
        temp = temp->next;
        prev++;
    }

    // Jika key ditemukan
    if (temp != nullptr && temp->merkbarang== key) {
        cout << "==================================================" << endl;
        cout << "\t\tDATA BERHASIL DITEMUKAN" << endl << endl;
        cout << "Merk\t: " << temp->merkbarang << endl;
        cout << "Jenis\t: " << temp->merkbarang << endl;
        cout << "Harga    : " << temp->hargabarang << endl;
        cout << "Stok\t: " << temp->stokbarang << endl;
    } else {
        // Jika key tidak ditemukan
        cout << "==================================================" << endl;
        cout << "\t\tDATA TIDAK DITEMUKAN" << endl;
    }
}

void menusearchingfibonaci(){
    string key;
    cout<<"=================================================="<< endl ;
    cout << "Masukkan kode barang yang dicari : ";
    cin >> key;
    fibonacciSearch(key);
}

void menusearchingjump(){
    string key;
    cout << "==================================================" << endl;
    cout << "Masukkan nama barang yang dicari : ";
    cin.ignore();
    getline(cin, key);
    jumpSearch(key);
}

// Fungsi untuk menampilkan menu searching
void searchingMenu() {
    system ("cls");
    string searching;
    do {
        cout << "==================================================" << endl;
        cout << "===\t      PILIH JENIS SEARCHING      \t===" << endl;
        cout << "==================================================" << endl;
        cout << "[1]. Searching Berdasarkan Stok Barang" << endl;
        cout << "[2]. Searching Berdasarkan Jenis Barang" << endl;
        cout << "==================================================" << endl;
        cout << "Pilih jenis Searching : ";
        cin >> searching;
        if (searching == "1") {
            do {
                menusearchingfibonaci();
                cout<<"\nKEMBALI KEMENU [Y/T] : ";
                cin>>lanjut;
            } while(lanjut != "y");
        } else if (searching == "2") {
            do {
                menusearchingjump();
                cout<<"\nKEMBALI KEMENU [Y/T] : ";
                cin>>lanjut;
            } while(lanjut != "y");
        } else {
            cout << "==================================================" << endl;
            cout << "\t\tNOMOR TIDAK VALID!!!"<<endl;
        }
    } while (searching != "1" && searching != "2");
}

void menulogin(){
    system ("cls");
    cout<<"==================================================="<<endl;
    cout<<"===\t\tPENDATAAN HAND PHONE\t\t==="<<endl;
    cout<<"===\t\t  TOKO SONIC PHONE       \t==="<<endl;
	cout<<"=================================================="<<endl;
	cout<<"====== P E N D A T A A N  P E R A L A T A N ======"<<endl ;
	cout<<"=================================================="<<endl ;
	cout<<"\t\t[1]. ADMIN"<<endl ;
	cout<<"\t\t[2]. USER"<<endl ;
    cout<<"\t\t[3]. SELESAI"<<endl ;
	cout<<"=================================================="<< endl ;
}

void processOrder() {
    system("cls");
    cout << "==============================================================" << endl;
    cout << "=========== M E N U   P R O S E S   P E S A N A N ============" << endl;
    cout << "==============================================================" << endl;

    // Menampilkan semua pesanan yang belum diproses
    order* temp = orderhead;
    bool found = false;

    while (temp != nullptr) {
        if (temp->statusProsesAdmin == false) {
            cout << "ID Pengguna: " << temp->id << endl;
            cout << "Item: " << temp->item << endl;
            cout << "Quantity: " << temp->quantity << endl;
            cout << "Status order : " << ((temp->statusProsesAdmin == false) ? "Belum diproses" : "Sudah diproses") << endl;
            cout << "----------------------------------------------" << endl;
            found = true;
        }
        temp = temp->next;
    }

    if (!found) {
        cout << "Tidak ada pesanan yang bisa diproses." << endl;
    } else {

        // memproses orderan
        string confirm;
        cout << "Ingin memproses orderan sekarang [Y/T] ? ";
        fflush(stdin);
        getline(cin, confirm);

        if(confirm == "Y") {
            order* temp = orderhead;

            // reset kembali variabel found untuk digunakan di proses pemesanan data paling atas
            found = false;
            while (temp != nullptr) {
                if (temp->statusProsesAdmin == false && found == false) {
                    temp->statusProsesAdmin = true;
                    found = true;
                    break;
                }
                temp = temp->next;
            }
            saveOrderToCSV();
        }

    }

    cout << "==================================================" << endl;
    cout << "Tekan enter untuk kembali ke menu pengguna...";
    cin.ignore();
    cin.get();
}

void menuadmin() {
    system ("cls");
    do {
    cout<<"=================================================="<<endl;
	cout<<"========= P E N D A T A A N  B A R A N G ========="<<endl ;
	cout<<"=================================================="<<endl ;
	cout<<"\t\t[1]. TAMBAH DATA"<<endl ;
	cout<<"\t\t[2]. TAMPILKAN DATA"<<endl ;
	cout<<"\t\t[3]. UBAH DATA"<<endl ;
	cout<<"\t\t[4]. HAPUS DATA"<<endl ;
	cout<<"\t\t[5]. SORTING DATA"<<endl ;
	cout<<"\t\t[6]. SEARCHING"<<endl ;
	cout<<"\t\t[7]. PROSES PESANAN"<<endl ;
    cout<<"\t\t[8]. EXIT"<<endl ;
	cout<<"=================================================="<< endl ;
    cout << "Pilih menu : ";
    cin >> pilih;
        if (pilih == "1") {
            add();
        }
        else if(pilih == "2") {
            do {
                display();
                cout<<"\nKEMBALI KEMENU [Y/T] : ";
                cin>>lanjut;
            } while(lanjut != "y");
        }
        else if(pilih == "3") {
            edit();
        }
        else if(pilih == "4") {
            del();
        } else if(pilih == "5") {
            sortMenu();
        }else if(pilih == "6") {
            searchingMenu();
        }else if(pilih == "7") {
            processOrder();
        }else if(pilih == "8") {
            menulogin();
        }
        else {
            do {
                cout<<"\n=================================================="<<endl;
                cout << "    Masukkan nomor yang sesuai pada menu!!!"<< endl;
                cout<<"=================================================="<<endl;
                break;
            } while (lanjut == "y");
        }
    }while(pilih != "8");
}

bool adminLogin(){
    string username, password;
    system ("cls");
    cout<<"=================================================="<<endl;
	cout<<"============== L O G I N  A D M I N =============="<<endl ;
	cout<<"=================================================="<<endl ;
    cout << "USERNAME \t:";
    cin >> username;
    cout << "PASSWORD \t:";
    cin >> password;
    // Bandingkan dengan username dan password admin yang benar
    if (username == "admin" && password == "123") {
        menuadmin();
    } else {
        cout << "Username atau password salah. Silakan coba lagi." << endl;
        return false;
    }
}

void saveToCSV() {
    ofstream file("users.csv");
    User* temp = userHead;
    while (temp != nullptr) {
        file << temp->username << "," << temp->password << endl;
        temp = temp->next;
    }
    file.close();
}

void readHPFromCSV() {
    ifstream file("hp.csv");
    if (!file.is_open()) {
        cerr << "Failed to open HP file." << endl;
        return;
    }

    string line;
    while (getline(file, line)) {
        hp* newNode = new hp();
        istringstream iss(line);

        getline(iss, newNode->merkbarang, ',');
        getline(iss, newNode->jenisbarang, ',');
        iss >> newNode->hargabarang;
        iss.ignore(); // Ignore the comma
        iss >> newNode->stokbarang;

        newNode->next = nullptr;

        // Add newNode to your linked list
        // Similar to how you're currently adding nodes
    }

    file.close();
}


void userRegistration() {
    system("cls");
    string username, password;
    cout << "==================================================" << endl;
    cout << "========== R E G I S T R A S I  U S E R ==========" << endl;
    cout << "==================================================" << endl;
    cout << "USERNAME BARU\t: ";
    cin >> username;
    cout << "PASSWORD BARU\t: ";
    cin >> password;
    User* newUser = new User();
    newUser->username = username;
    newUser->password = password;
    newUser->next = nullptr;

    if (userHead == nullptr) {
        userHead = newUser;
    } else {
        User* temp = userHead;
        while (temp->next != nullptr) {
            temp = temp->next;
        }
        temp->next = newUser;
    }

    saveToCSV(); // Simpan pengguna ke file CSV setiap kali ada registrasi baru

    cout << "=============== REGISTRASI BERHASIL ==============" << endl;
    cout << "======== MASUK MENGGUNAKAN AKUN TERDAFTAR ========" << endl;
}

void readFromCSV() {
    ifstream file("users.csv");
    string line, username, password;
    while (getline(file, line)) {
        stringstream ss(line);
        getline(ss, username, ',');
        getline(ss, password, ',');
        User* newUser = new User();
        newUser->username = username;
        newUser->password = password;
        newUser->next = nullptr;

        if (userHead == nullptr) {
            userHead = newUser;
        } else {
            User* temp = userHead;
            while (temp->next != nullptr) {
                temp = temp->next;
            }
            temp->next = newUser;
        }
    }
    file.close();
}

void menuuser(){
    string targetId = "";
    system ("cls");
    do {
    cout<<"=================================================="<<endl;
	cout<<"======= S E L A M A T  B E R B E L A N J A ======="<<endl ;
	cout<<"=================================================="<<endl ;
	cout<<"\t\t[1]. ORDER"<<endl ;
	cout<<"\t\t[2]. KERANJANG"<<endl ;
    cout<<"\t\t[3]. EXIT"<<endl ;
	cout<<"=================================================="<< endl ;
    cout << "Pilih menu : ";
    cin >> pilih;
        if (pilih == "1") {
            orderUser();
        } else if(pilih == "2") {
            displayUserOrder();
        }else if(pilih == "3") {
            menulogin();
        }
        else{
            do {
                cout<<"\n=================================================="<<endl;
                cout << "    Masukkan nomor yang sesuai pada menu!!!"<< endl;
                cout<<"=================================================="<<endl;
                break;
            } while (lanjut == "y");
        }
    }while(pilih != "4");
}

bool userLogin() {
    system ("cls");
    string username, password;
    cout<<"=================================================="<<endl;
	cout<<"=============== L O G I N  U S E R ==============="<<endl ;
	cout<<"=================================================="<<endl ;
    cout << "USERNAME\t: ";
    cin >> username;
    cout << "PASSWORD\t: ";
    cin >> password;
    User* temp = userHead;
    while (temp != nullptr) {
        if (temp->username == username && temp->password == password) {
            menuuser();
            return true; // Mengembalikan true jika login berhasil
        }
        temp = temp->next;
    }
    cout<<"=================== LOGIN GAGAL =================="<<endl;
    cout<<"========== USERNAME ATAU PASSWORD SALAH =========="<<endl;
    return false;
}

void debugUserReg() {
    system("cls");
    string username, password;
    username = "asep";
    password = "asep";
    User* newUser = new User();
    newUser->username = username;
    newUser->password = password;
    newUser->next = nullptr;

    if (userHead == nullptr) {
        userHead = newUser;
    } else {
        User* temp = userHead;
        while (temp->next != nullptr) {
            temp = temp->next;
        }
        temp->next = newUser;
    }

    saveToCSV();
}

void user(){
    // untuk testing
    debugUserReg();

    system ("cls");
    do {
    cout<<"=================================================="<<endl;
	cout<<"================ M E N U  U S E R ================"<<endl ;
	cout<<"=================================================="<<endl ;
	cout<<"\t\t[1]. REGISRASI USER"<<endl ;
	cout<<"\t\t[2]. LOGIN USER"<<endl ;
    cout<<"\t\t[3]. EXIT"<<endl ;
	cout<<"=================================================="<< endl ;
    cout << "Pilih menu : ";
    cin >> pilih;
        if (pilih == "1") {
            userRegistration();
        }
        else if(pilih == "2") {
            userLogin();
        }else if(pilih == "3") {
            menulogin();
        }
        else{
            do {
                cout<<"\n=================================================="<<endl;
                cout << "    Masukkan nomor yang sesuai pada menu!!!"<< endl;
                cout<<"=================================================="<<endl;
                break;
            } while (lanjut == "y");
        }
    }while(pilih != "3");
}

void bacaDataDariCSV() {
    ifstream file("hp.csv"); // Ganti "data.csv" dengan nama file CSV Anda
    if (!file.is_open()) {
        cout << "Gagal membuka file CSV." << endl;
        return;
    }

    string line;
    while (getline(file, line)) {
        stringstream ss(line);
        hp* newhp = new hp;
        getline(ss, newhp->merkbarang, ',');
        getline(ss, newhp->jenisbarang, ',');
        ss >> newhp->hargabarang;
        ss.ignore(); // Mengabaikan koma setelah hargabarang
        ss >> newhp->stokbarang;
        newhp->next = nullptr;

        // Tambahkan newhp ke dalam linked list atau struktur data yang Anda gunakan
        // Contoh: Tambahkan ke akhir linked list
        if (hphead == nullptr) {
            hphead = newhp;
        } else {
            hp* temp = hphead;
            while (temp->next != nullptr) {
                temp = temp->next;
            }
            temp->next = newhp;
        }
    }

    file.close();
}

void debugMain() {
    readOrderFromCSV();
    processOrder();
}

int main() {
    readFromCSV();
    bacaDataDariCSV();
    readOrderFromCSV();
    readHPFromCSV();
    do {
        menulogin();
        cout << "Pilih menu : ";
        fflush(stdin);
        getline(cin, pilih);
            if (pilih == "1") {
                adminLogin();
            }
            else if(pilih == "2") {
                user();
            }else if(pilih == "3") {
                break;
            }
            else{
                do {
                    cout<<"\n=================================================="<<endl;
                    cout << "    Masukkan nomor yang sesuai pada menu!!!"<< endl;
                    cout<<"=================================================="<<endl;
                    break;
                } while (lanjut == "y");
            }
        }while(pilih != "3");

        system ("cls");
        cout<<"\n=================================================="<<endl;
        cout<<"========== P R O G R A M  S E L E S A I ==========\n";
        cout<<"=================================================="<<endl;
        //*/
        return 0;
}
