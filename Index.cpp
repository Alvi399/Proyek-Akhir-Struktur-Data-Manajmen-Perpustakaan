#include <iostream>
using namespace std;
class Peminjaman {
public:
    int id_peminjaman;
    string judul_buku;
    string nama_peminjam;
    string tanggal_peminjaman;
    string tanggal_pengembalian;

    Peminjaman(int id, string judul, string peminjam, string tgl_pinjam, string tgl_kembali) {
        id_peminjaman = id;
        judul_buku = judul;
        nama_peminjam = peminjam;
        tanggal_peminjaman = tgl_pinjam;
        tanggal_pengembalian = tgl_kembali;
    }
};
class PeminjamanNode {
public:
    Peminjaman peminjaman;
    PeminjamanNode* left;
    PeminjamanNode* right;

    PeminjamanNode(Peminjaman p)
        : peminjaman(p), left(nullptr), right(nullptr) {}
};
struct Node {
    string buku;
    Node* next;
    
    Node(string _buku) : buku(_buku), next(nullptr) {}
};

class PeminjamanTree {
private:
    int hash(int id) {
        return id % 10;
    }
    string hashTable[10];

public:
    PeminjamanNode* root;
    PeminjamanTree() : root(nullptr) {}
    void insert(Peminjaman p) {
        root = insertRec(root, p);
    }
    PeminjamanNode* insertRec(PeminjamanNode* root, Peminjaman p) {
        if (root == nullptr) {
            root = new PeminjamanNode(p);
            return root;
        }
        if (p.id_peminjaman < root->peminjaman.id_peminjaman) {
            root->left = insertRec(root->left, p);
        } else if (p.id_peminjaman > root->peminjaman.id_peminjaman) {
            root->right = insertRec(root->right, p);
        }
        return root;
    }
    void inorder() {
        inorderRec(root);
    }
    void inorderRec(PeminjamanNode* root) {
        if (root != nullptr) {
            inorderRec(root->left);
            cout << "+=========================================+" << endl;
            cout << "ID Peminjaman: " << root->peminjaman.id_peminjaman << endl;
            cout << "Judul Buku: " << root->peminjaman.judul_buku << endl;
            cout << "Nama Peminjam: " << root->peminjaman.nama_peminjam << endl;
            cout << "Tanggal Peminjaman: " << root->peminjaman.tanggal_peminjaman << endl;
            cout << "Tanggal Pengembalian: " << root->peminjaman.tanggal_pengembalian << endl;
            cout << "+=========================================+" << endl;
            cout << endl;
            inorderRec(root->right);
        }
    }
    PeminjamanNode* search(PeminjamanNode* root, int id) {
        if (root == nullptr || root->peminjaman.id_peminjaman == id) {
            return root;
        }
        if (root->peminjaman.id_peminjaman < id) {
            return search(root->right, id);
        }
        return search(root->left, id);
    }
    void search(int id) {
        PeminjamanNode* result = search(root, id);
        if (result == nullptr) {
            cout << "Peminjaman dengan ID " << id << " tidak ditemukan" << endl;
        } else {
            cout << "+=========================================+" << endl;
            cout << "ID Peminjaman: " << result->peminjaman.id_peminjaman << endl;
            cout << "Judul Buku: " << result->peminjaman.judul_buku << endl;
            cout << "Genre Buku: " << result->peminjaman.nama_peminjam << endl;
            cout << "Tanggal Peminjaman: " << result->peminjaman.tanggal_peminjaman << endl;
            cout << "Tanggal Pengembalian: " << result->peminjaman.tanggal_pengembalian << endl;
            cout << "+=========================================+" << endl;
        }
    }
    void insertHash(Peminjaman p) {
        int index = hash(p.id_peminjaman);
        if (hashTable[index].empty()) {
            hashTable[index] = p.nama_peminjam + " | " + p.tanggal_peminjaman + " | " + p.tanggal_pengembalian;
        } else {
            // Collision handling
            hashTable[index] += " -> " + p.nama_peminjam + " | " + p.tanggal_peminjaman + " | " + p.tanggal_pengembalian;
        }
    }
    void displayHash() {
        for (int i = 0; i < 10; i++) {
            cout <<"|"<< i << "| " << hashTable[i] << endl;
        }
    }
    //implementasi graph
    Node* graph[10];
    bool dikunjungi[10];

    void loadReks() {                    
        for (int i = 0; i < 10; i++) {
            graph[i] = nullptr;
        }
    }
    void tambahkanHubunganBuku(Node* graph[], string buku_sumber, string buku_target) {
        Node* node = new Node(buku_target);
        node->next = graph[hash1(buku_sumber)];
        graph[hash1(buku_sumber)] = node;
    }
// Fungsi hash sederhana
    int hash1(const string& buku) {
        int h = 0;
        for (char c : buku) {
            h += c;
        }
        return h % 10; // Modulus 10 digunakan sebagai contoh, dapat disesuaikan dengan skala yang lebih besar
    }

    // Fungsi rekursif DFS untuk merekomendasikan buku
    void dfs(Node* graph[], string buku_sekarang, bool dikunjungi[]) {
        dikunjungi[hash1(buku_sekarang)] = true;
        cout << buku_sekarang << endl;

        // Jelajahi buku-buku terkait
        Node* node = graph[hash1(buku_sekarang)];
        while (node != nullptr) {
            if (!dikunjungi[hash1(node->buku)]) {
                dfs(graph, node->buku, dikunjungi);
            }
            node = node->next;
        }
    }    
};
class Perpus {
    private:
        int id_pinjam = 0;
        string books[90][5]; //index, title, author, year, genre;
        PeminjamanTree peminjamanTree;
        string all_trim(string str) {
            // Dummy trim function for example, implement accordingly
            str.erase(str.find_last_not_of(" \n\r\t") + 1);
            str.erase(0, str.find_first_not_of(" \n\r\t"));
            return str;
        }
        int getBookIndex(int start, string title) //implementasi rekrusi
        {
            int max = sizeof(books) / sizeof(books[0]);
            if (start >= max) {
                return -1;
            } else if (all_trim(books[start][1]) == all_trim(title)) {
                return start;
            } else {
                return getBookIndex(start + 1, title);
            }
        }
        int getBookbyAuthor (string nameAuthor) { //implementasi searching - sequatial search
            int max = sizeof(books) / sizeof(books[0]);
            for (int i = 0; i < max; i++)
            {
                if (books[i][2] == nameAuthor)
                {
                    getBookInfo(i);
                    cout << endl;
                }
                
            }
            
        }
        void getBookInfo(int index) {
            cout << "+=========================================+" << endl;
            cout << "Id: " << books[index][0] << endl;
            cout << "Title: " << books[index][1] << endl;
            cout << "Author: " << books[index][2] << endl;
            cout << "Year: " << books[index][3] << endl;
            cout << "Genre: " << books[index][4] << endl;
            cout << "+=========================================+" << endl;
        }

        void addBook(string title, string author, string year, string genre) {
            int max = sizeof(books) / sizeof(books[0]);
            int index = -1;
            for (int i = 0; i < max; i++) {
                if (books[i][1].empty()) {
                    index = i;
                    break;
                }
            }
            if (index == -1) {
                cout << "No empty slot available to add a new book" << endl;
            } else {
                books[index][0] = to_string(index + 1); // Use the index for numbering
                books[index][1] = title;
                books[index][2] = author;
                books[index][3] = year;
                books[index][4] = genre;
                cout << "Buku berhasil ditambahkan di index " << index << endl;
            }
        }
        void displayByName() { //implementasi sorting - bubble sort
            const int MAX_BOOKS = 90;
            string sortedBooks[MAX_BOOKS][5];

            // Copy books to sortedBooks
            for (int i = 0; i < MAX_BOOKS; i++) {
                for (int j = 0; j < 5; j++) {
                    sortedBooks[i][j] = books[i][j];
                }
            }

            // Determine the number of books (non-empty titles)
            int numBooks = 0;
            for (int i = 0; i < MAX_BOOKS; i++) {
                if (!sortedBooks[i][1].empty()) {
                    numBooks++;
                } else {
                    break;
                }
            }

            // Bubble sort by book titles (sortedBooks[][1])
            for (int i = 0; i < numBooks - 1; i++) {
                for (int j = 0; j < numBooks - i - 1; j++) {
                    if (sortedBooks[j][1] > sortedBooks[j + 1][1]) {
                        // Swap the entire row
                        for (int k = 0; k < 5; k++) {
                            swap(sortedBooks[j][k], sortedBooks[j + 1][k]);
                        }
                    }
                }
            }

            // Display sorted books
            for (int i = 0; i < numBooks; i++) {
                cout << "+=========================================+" << endl;
                cout << "Id: " << sortedBooks[i][0] << endl;
                cout << "Title: " << sortedBooks[i][1] << endl;
                cout << "Author: " << sortedBooks[i][2] << endl;
                cout << "Year: " << sortedBooks[i][3] << endl;
                cout << "Genre: " << sortedBooks[i][4] << endl;
                cout << endl;
                cout << "+=========================================+" << endl;
            }
        }
        void displayByYear() { //implementasi sorting - insertion sort
            string sortedBooks[90][5];
            //copy to sortedBooks
            for (int i = 0; i < 90; i++) {
                sortedBooks[i][0] = books[i][0];
                sortedBooks[i][1] = books[i][1];
                sortedBooks[i][2] = books[i][2];
                sortedBooks[i][3] = books[i][3];
                sortedBooks[i][4] = books[i][4];
            }
            int i,j,index,max;
            for (int i = 0; i < 90; i++) {
                if (sortedBooks[i][1] == "") {
                    max = i;
                    break;
                }
            }
            //inseration sort
            for (i = 1; i < max; i++) {
                string key[5];
                key[0] = sortedBooks[i][0];
                key[1] = sortedBooks[i][1];
                key[2] = sortedBooks[i][2];
                key[3] = sortedBooks[i][3];
                key[4] = sortedBooks[i][4];
                j = i - 1;
                while (j >= 0 && sortedBooks[j][3] > key[3]) {
                    sortedBooks[j+1][0] = sortedBooks[j][0];
                    sortedBooks[j+1][1] = sortedBooks[j][1];
                    sortedBooks[j+1][2] = sortedBooks[j][2];
                    sortedBooks[j+1][3] = sortedBooks[j][3];
                    sortedBooks[j+1][4] = sortedBooks[j][4];
                    j = j - 1;
                }
                sortedBooks[j+1][0] = key[0];
                sortedBooks[j+1][1] = key[1];
                sortedBooks[j+1][2] = key[2];
                sortedBooks[j+1][3] = key[3];
                sortedBooks[j+1][4] = key[4];
            }
            
            for (int i = 0; i < 90; i++) {
                if (sortedBooks[i][1] != "")
                {
                    cout << "+=========================================+" << endl;
                    cout << "Id: " << sortedBooks[i][0] << endl;
                    cout << "Title: " << sortedBooks[i][1] << endl;
                    cout << "Author: " << sortedBooks[i][2] << endl;
                    cout << "Year: " << sortedBooks[i][3] << endl;
                    cout << "Genre: " << sortedBooks[i][4] << endl;
                    cout << endl;
                    cout << "+=========================================+" << endl;
                }
            }   
        }
        int createIdPinjam() {
            id_pinjam++;
            return id_pinjam;
        }
        // Declare the type of peminjamanTree
    public:
        void loadBooks() {
            books[0][0] = "1";
            books[0][1] = "The Great Gatsby";
            books[0][2] = "F. Scott Fitzgerald";
            books[0][3] = "1925";
            books[0][4] = "Fiction";
            books[1][0] = "2";
            books[1][1] = "To Kill a Mockingbird";
            books[1][2] = "Harper Lee";
            books[1][3] = "1960";
            books[1][4] = "Fiction";
            books[2][0] = "3";
            books[2][1] = "Omedeto";
            books[2][2] = "George Orwell";
            books[2][3] = "1949";
            books[2][4] = "Fiction";
            // Initialize the rest of the array to empty strings
            for (int i = 3; i < 90; ++i) {
                books[i][0] = "";
                books[i][1] = "";
                books[i][2] = "";
                books[i][3] = "";
                books[i][4] = "";
            }
        }
        void menuSearch() {
            int input,index;
            cout << "<===================================>" << endl;
            cout << "|          Menu Search Book         |" << endl;
            cout << "====================================" << endl;
            cout << "|1. Cari buku berdasarkan judul     |" << endl;
            cout << "|2. Cari buku berdasrkan author     |" << endl;
            cout << "<===================================>" << endl;
            cout << "Input: ";
            cin >> input;
            string judul,author;
            switch (input)
            {
                case 1:
                    cin.ignore();
                    cout << "Masukkan judul buku: ";
                    getline(cin, judul);
                    index = getBookIndex(0, judul);
                    if (index == -1) {
                        cout << "Buku tidak ditemukan" << endl;
                    } else {
                        getBookInfo(index);
                    }
                    break;
                case 2:
                    cin.ignore();
                    cout << "Masukkan author buku: ";
                    getline(cin, author);
                    getBookbyAuthor(author);
                    break;
            }
        }
        void menuAddBook() {
            string judul, author, year, genre;
            cin.ignore();
            cout << "<===================================>" << endl;
            cout << "|             Add Book              |" << endl;
            cout << "====================================" << endl;
            cout << "Masukkan judul buku: ";
            getline(cin, judul);
            cout << "Masukkan author buku: ";
            getline(cin, author);
            cout << "Masukkan tahun terbit buku: ";
            getline(cin, year);
            cout << "Masukkan genre buku: ";
            getline(cin, genre);
            addBook(judul, author, year, genre);
        }
        void menuDisplayBook() {
            cout << "<===================================>" << endl;
            cout << "|         Menu Display Book         |" << endl;
            cout << "====================================" << endl;
            cout << "|1. Urutkan berdasarkan judul       |" << endl;
            cout << "|2. Urutkan berdasarkan tahun terbit|" << endl;
            cout << "<===================================>" << endl;
            cout << "Input: ";
            int input;
            cin >> input;
            switch (input)
            {
                case 1:
                    displayByName();
                    break;
                case 2:
                    displayByYear();
                    break;
            }
        }
        void menuPeminjaman() {
            int input;
            bool perulangan = true;
            while (perulangan)
            {
                cout << "<=========================>" << endl;
                cout << "|     Menu Peminjaman     |" << endl;
                cout << "==========================" << endl;
                cout << "|1. Tambah peminjaman     |" << endl;
                cout << "|2. Lihat semua peminjaman|" << endl;
                cout << "|3. Cari peminjaman       |" << endl;
                cout << "|4. Lihat tabel peminjaman|" << endl;
                cout << "|0. Kembali               |" << endl;
                cout << "<=========================>" << endl;
                int id;
                string judul, peminjam, tgl_pinjam, tgl_kembali;
                cout << "Input: ";
                cin >> input;
                if (input == 1)
                {
                    cin.ignore();
                    cout << "Masukkan judul buku: ";
                    getline(cin, judul);
                    cout << "Masukkan nama peminjam: ";
                    getline(cin, peminjam);
                    cout << "Masukkan tanggal peminjaman (dd-mm-yyyy): ";
                    getline(cin, tgl_pinjam);
                    cout << "Masukkan tanggal pengembalian (dd-mm-yyyy): ";
                    getline(cin, tgl_kembali);
                    if (getBookIndex(0, judul) == -1) {
                        cout << "Buku tidak ditemukan" << endl;
                        continue;
                    } else {
                        id = createIdPinjam();
                        Peminjaman p(id, judul, peminjam, tgl_pinjam, tgl_kembali);
                        peminjamanTree.insert(p);
                        peminjamanTree.insertHash(p);
                        
                    }
                } else if (input == 2) {
                    peminjamanTree.inorder();
                } else if (input == 3) {
                    cout << "Masukkan ID peminjaman: ";
                    cin >> id;
                    peminjamanTree.search(id);
                } else if (input == 4) {
                    peminjamanTree.displayHash();
                } else if (input == 0) {
                    perulangan = false;
                }
            }
        }
        void menuRekomendasi() {
            if (peminjamanTree.root == nullptr) {
                cout << "Belum ada peminjaman" << endl;
            } else {
                cout << "<=======================================>" << endl;
                cout << "|Rekomendasi buku berdasarkan peminjaman|" << endl;
                cout << "=========================================" << endl;
                cout << "Buku yang direkomendasikan: " << endl;
                peminjamanTree.loadReks();
                PeminjamanNode *temp = peminjamanTree.root;
                string buku[10];
                int indexBuku = 0;
                while (peminjamanTree.root != nullptr)
                {
                    buku[indexBuku] = peminjamanTree.root->peminjaman.judul_buku;
                    indexBuku++;
                    peminjamanTree.root = peminjamanTree.root->right;
                }
                for (int i = 0; i < 10; i++)
                {
                    peminjamanTree.tambahkanHubunganBuku(peminjamanTree.graph, buku[i], buku[i+1]);
                }
                
                peminjamanTree.dfs(peminjamanTree.graph, buku[0], peminjamanTree.dikunjungi);
            }
        }
};

int main(int argc, char const *argv[])
{
    system("cls");
    Perpus perpus;
    perpus.loadBooks();
    bool perulangan1 = true;
    while (perulangan1)
    {
        int input;
        cout << "<=========================>" << endl;
        cout << "|     Perpustakaan CLI    |" << endl;
        cout << "==========================" << endl;
        cout << "|1. Cari buku             |" << endl;
        cout << "|2. Lihat semua buku      |" << endl;
        cout << "|3. Tambah buku           |" << endl;
        cout << "|4. Peminjaman            |" << endl;
        cout << "|5. Rekomendasi buku      |" << endl;
        cout << "|0. Keluar                |" << endl;
        cout << "<=========================>" << endl;
        cout << "Input: ";
        cin >> input;
        switch (input) {
            case 1:
                system("cls");
                perpus.menuSearch();
                break;
            case 2:
                system("cls");
                perpus.menuDisplayBook();
                break;
            case 3:
                system("cls");
                perpus.menuAddBook();
                break;
            case 4:
                system("cls");
                perpus.menuPeminjaman();
                break;
            case 5:
                system("cls");
                perpus.menuRekomendasi();
                break;
            case 0:
                perulangan1 = false;
                break;
            default:
                break;
        }
    }
    system("cls");
    cout << "+==========================================+" << endl;
    cout << "|Terima kasih telah menggunakan program ini|" << endl;
    cout << "+==========================================+" << endl;
    return 0;
}
