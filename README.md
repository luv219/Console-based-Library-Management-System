Library Management System
Overview
This is a console-based Library Management System implemented in C++. The application allows librarians to manage a small library's inventory, including adding and removing books, registering and unregistering members, and handling book checkouts and returns. All data is persisted to local files (books.txt and members.txt) for durability.
Features

Add Book: Add a new book with a title and author to the library inventory.
Remove Book: Remove a book by its ID, provided it is not currently borrowed.
Register Member: Register a new library member with a name and assign a unique ID.
Unregister Member: Remove a member by their ID, provided they have no borrowed books.
Checkout Book: Allow a member to borrow a book, marking it as unavailable.
Return Book: Allow a member to return a borrowed book, making it available again.
List Books: Display all books with their ID, title, author, and availability status.
List Members: Display all members with their ID, name, and borrowed book IDs.
Data Persistence: Books and member data are saved to books.txt and members.txt files.

Prerequisites

A C++ compiler (e.g., g++, clang++)
Standard C++ library (C++11 or later)

Installation

Clone the repository:git clone <repository-url>
cd library-management-system


Compile the code:g++ -o library library.cpp


Run the executable:./library



Usage
Upon running the program, a menu is displayed with the following options:

Add Book
Remove Book
Register Member
Unregister Member
Checkout Book
Return Book
List Books
List Members
Exit

Follow the prompts to interact with the system. For example:

To add a book, select option 1, then enter the title and author.
To checkout a book, select option 5, then provide the member ID and book ID.

File Structure

library.cpp: The main source code for the application.
books.txt: Stores book data (ID, title, author, availability).
members.txt: Stores member data (ID, name, borrowed book IDs).
README.md: This file.

Data Persistence

Books: Saved in books.txt with format ID,Title,Author,Availability (e.g., 1,The Great Gatsby,F. Scott Fitzgerald,1).
Members: Saved in members.txt with format ID,Name,BorrowedBookIDs (e.g., 1,John Doe,2,3).
Files are automatically created/updated when the program runs and exits.

Example
Library Management System
1. Add Book
2. Remove Book
3. Register Member
4. Unregister Member
5. Checkout Book
6. Return Book
7. List Books
8. List Members
9. Exit
Enter choice: 1
Enter title: 1984
Enter author: George Orwell
Book added successfully. ID: 1

Notes

Book and member IDs are auto-generated and unique.
A book cannot be removed if it is borrowed.
A member cannot be unregistered if they have borrowed books.
The program checks for valid inputs but assumes correct data types (e.g., integers for IDs).

Contributing
Contributions are welcome! Please fork the repository and create a pull request with your changes. Ensure your code follows the existing style and includes appropriate comments.
License
This project is licensed under the MIT License. See the LICENSE file for details.
