#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>

using namespace std;

// Book class
class Book {
public:
    int id;
    string title;
    string author;
    bool available;

    Book(int i, string t, string a, bool av) : id(i), title(t), author(a), available(av) {}
};

// Member class
class Member {
public:
    int id;
    string name;
    vector<int> borrowedBooks;

    Member(int i, string n) : id(i), name(n) {}
};

// Library class to manage books and members
class Library {
private:
    vector<Book> books;
    vector<Member> members;
    int nextBookId = 1;
    int nextMemberId = 1;
    const string booksFile = "books.txt";
    const string membersFile = "members.txt";

    void loadBooks() {
        ifstream file(booksFile);
        if (!file) return;

        string line;
        while (getline(file, line)) {
            stringstream ss(line);
            string token;
            vector<string> parts;
            while (getline(ss, token, ',')) {
                parts.push_back(token);
            }
            if (parts.size() == 4) {
                int id = stoi(parts[0]);
                string title = parts[1];
                string author = parts[2];
                bool available = stoi(parts[3]);
                books.emplace_back(id, title, author, available);
                nextBookId = max(nextBookId, id + 1);
            }
        }
        file.close();
    }

    void loadMembers() {
        ifstream file(membersFile);
        if (!file) return;

        string line;
        while (getline(file, line)) {
            stringstream ss(line);
            string token;
            vector<string> parts;
            while (getline(ss, token, ',')) {
                parts.push_back(token);
            }
            if (parts.size() >= 2) {
                int id = stoi(parts[0]);
                string name = parts[1];
                Member member(id, name);
                for (size_t i = 2; i < parts.size(); ++i) {
                    if (!parts[i].empty()) {
                        member.borrowedBooks.push_back(stoi(parts[i]));
                    }
                }
                members.push_back(member);
                nextMemberId = max(nextMemberId, id + 1);
            }
        }
        file.close();
    }

    void saveBooks() {
        ofstream file(booksFile);
        for (const auto& book : books) {
            file << book.id << "," << book.title << "," << book.author << "," << (book.available ? 1 : 0) << endl;
        }
        file.close();
    }

    void saveMembers() {
        ofstream file(membersFile);
        for (const auto& member : members) {
            file << member.id << "," << member.name;
            for (int bookId : member.borrowedBooks) {
                file << "," << bookId;
            }
            file << endl;
        }
        file.close();
    }

public:
    Library() {
        loadBooks();
        loadMembers();
    }

    ~Library() {
        saveBooks();
        saveMembers();
    }

    void addBook(const string& title, const string& author) {
        books.emplace_back(nextBookId++, title, author, true);
        saveBooks();
        cout << "Book added successfully. ID: " << nextBookId - 1 << endl;
    }

    void removeBook(int bookId) {
        auto it = find_if(books.begin(), books.end(), [bookId](const Book& b) { return b.id == bookId; });
        if (it != books.end()) {
            // Check if borrowed
            for (const auto& member : members) {
                if (find(member.borrowedBooks.begin(), member.borrowedBooks.end(), bookId) != member.borrowedBooks.end()) {
                    cout << "Cannot remove book. It is currently borrowed." << endl;
                    return;
                }
            }
            books.erase(it);
            saveBooks();
            cout << "Book removed successfully." << endl;
        } else {
            cout << "Book not found." << endl;
        }
    }

    void registerMember(const string& name) {
        members.emplace_back(nextMemberId++, name);
        saveMembers();
        cout << "Member registered successfully. ID: " << nextMemberId - 1 << endl;
    }

    void unregisterMember(int memberId) {
        auto it = find_if(members.begin(), members.end(), [memberId](const Member& m) { return m.id == memberId; });
        if (it != members.end()) {
            if (!it->borrowedBooks.empty()) {
                cout << "Cannot unregister member. They have borrowed books." << endl;
                return;
            }
            members.erase(it);
            saveMembers();
            cout << "Member unregistered successfully." << endl;
        } else {
            cout << "Member not found." << endl;
        }
    }

    void checkoutBook(int memberId, int bookId) {
        auto bookIt = find_if(books.begin(), books.end(), [bookId](const Book& b) { return b.id == bookId; });
        if (bookIt == books.end()) {
            cout << "Book not found." << endl;
            return;
        }
        if (!bookIt->available) {
            cout << "Book is not available." << endl;
            return;
        }

        auto memberIt = find_if(members.begin(), members.end(), [memberId](const Member& m) { return m.id == memberId; });
        if (memberIt == members.end()) {
            cout << "Member not found." << endl;
            return;
        }

        memberIt->borrowedBooks.push_back(bookId);
        bookIt->available = false;
        saveBooks();
        saveMembers();
        cout << "Book checked out successfully." << endl;
    }

    void returnBook(int memberId, int bookId) {
        auto memberIt = find_if(members.begin(), members.end(), [memberId](const Member& m) { return m.id == memberId; });
        if (memberIt == members.end()) {
            cout << "Member not found." << endl;
            return;
        }

        auto borrowedIt = find(memberIt->borrowedBooks.begin(), memberIt->borrowedBooks.end(), bookId);
        if (borrowedIt == memberIt->borrowedBooks.end()) {
            cout << "Member does not have this book borrowed." << endl;
            return;
        }

        auto bookIt = find_if(books.begin(), books.end(), [bookId](const Book& b) { return b.id == bookId; });
        if (bookIt != books.end()) {
            bookIt->available = true;
        }

        memberIt->borrowedBooks.erase(borrowedIt);
        saveBooks();
        saveMembers();
        cout << "Book returned successfully." << endl;
    }

    void listBooks() {
        cout << "Books:" << endl;
        for (const auto& book : books) {
            cout << "ID: " << book.id << ", Title: " << book.title << ", Author: " << book.author
                 << ", Available: " << (book.available ? "Yes" : "No") << endl;
        }
    }

    void listMembers() {
        cout << "Members:" << endl;
        for (const auto& member : members) {
            cout << "ID: " << member.id << ", Name: " << member.name << ", Borrowed Books: ";
            for (int bookId : member.borrowedBooks) {
                cout << bookId << " ";
            }
            cout << endl;
        }
    }
};

int main() {
    Library library;
    int choice;

    while (true) {
        cout << "\nLibrary Management System\n";
        cout << "1. Add Book\n";
        cout << "2. Remove Book\n";
        cout << "3. Register Member\n";
        cout << "4. Unregister Member\n";
        cout << "5. Checkout Book\n";
        cout << "6. Return Book\n";
        cout << "7. List Books\n";
        cout << "8. List Members\n";
        cout << "9. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;
        cin.ignore(); // Clear newline

        if (choice == 1) {
            string title, author;
            cout << "Enter title: ";
            getline(cin, title);
            cout << "Enter author: ";
            getline(cin, author);
            library.addBook(title, author);
        } else if (choice == 2) {
            int bookId;
            cout << "Enter book ID: ";
            cin >> bookId;
            library.removeBook(bookId);
        } else if (choice == 3) {
            string name;
            cout << "Enter name: ";
            getline(cin, name);
            library.registerMember(name);
        } else if (choice == 4) {
            int memberId;
            cout << "Enter member ID: ";
            cin >> memberId;
            library.unregisterMember(memberId);
        } else if (choice == 5) {
            int memberId, bookId;
            cout << "Enter member ID: ";
            cin >> memberId;
            cout << "Enter book ID: ";
            cin >> bookId;
            library.checkoutBook(memberId, bookId);
        } else if (choice == 6) {
            int memberId, bookId;
            cout << "Enter member ID: ";
            cin >> memberId;
            cout << "Enter book ID: ";
            cin >> bookId;
            library.returnBook(memberId, bookId);
        } else if (choice == 7) {
            library.listBooks();
        } else if (choice == 8) {
            library.listMembers();
        } else if (choice == 9) {
            break;
        } else {
            cout << "Invalid choice." << endl;
        }
    }

    return 0;
}
