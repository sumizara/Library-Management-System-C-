#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iomanip>
using namespace std;

struct Book {
    int id;
    string title;
    string author;
    int year;
};

const string FILENAME = "library.txt";

void saveBook(const Book& b) {
    ofstream out(FILENAME, ios::app);
    out << b.id << endl;
    out << b.title << endl;
    out << b.author << endl;
    out << b.year << endl;
    out.close();
}

vector<Book> loadBooks() {
    vector<Book> books;
    ifstream in(FILENAME);
    if (!in) return books;
    Book b;
    while (in >> b.id) {
        in.ignore();
        getline(in, b.title);
        getline(in, b.author);
        in >> b.year;
        in.ignore();
        books.push_back(b);
    }
    in.close();
    return books;
}

void addBook() {
    Book b;
    cout << "Enter book ID: ";
    cin >> b.id;
    cin.ignore();
    cout << "Enter title: ";
    getline(cin, b.title);
    cout << "Enter author: ";
    getline(cin, b.author);
    cout << "Enter year: ";
    cin >> b.year;
    saveBook(b);
    cout << "Book added!\n";
}

void listBooks() {
    vector<Book> books = loadBooks();
    if (books.empty()) {
        cout << "No books found.\n";
        return;
    }
    cout << left << setw(10) << "ID" << setw(30) << "Title" << setw(20) << "Author" << "Year\n";
    for (const auto& b : books) {
        cout << left << setw(10) << b.id << setw(30) << b.title << setw(20) << b.author << b.year << endl;
    }
}

void searchBook() {
    int id;
    cout << "Enter book ID to search: ";
    cin >> id;
    vector<Book> books = loadBooks();
    for (const auto& b : books) {
        if (b.id == id) {
            cout << "Found: " << b.title << " by " << b.author << " (" << b.year << ")\n";
            return;
        }
    }
    cout << "Book not found.\n";
}

void deleteBook() {
    int id;
    cout << "Enter book ID to delete: ";
    cin >> id;
    vector<Book> books = loadBooks();
    bool found = false;
    ofstream out(FILENAME);
    for (const auto& b : books) {
        if (b.id == id) {
            found = true;
            continue;
        }
        out << b.id << endl;
        out << b.title << endl;
        out << b.author << endl;
        out << b.year << endl;
    }
    out.close();
    if (found) cout << "Book deleted.\n";
    else cout << "Book not found.\n";
}

int main() {
    int choice;
    do {
        cout << "\n--- Library Management System ---\n";
        cout << "1. Add Book\n";
        cout << "2. List All Books\n";
        cout << "3. Search Book by ID\n";
        cout << "4. Delete Book by ID\n";
        cout << "5. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;
        switch (choice) {
            case 1: addBook(); break;
            case 2: listBooks(); break;
            case 3: searchBook(); break;
            case 4: deleteBook(); break;
            case 5: cout << "Goodbye!\n"; break;
            default: cout << "Invalid choice.\n";
        }
    } while (choice != 5);
    return 0;
}
