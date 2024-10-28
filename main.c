#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_USERS 100
#define MAX_BOOKS 100
#define MAX_MEMBERS 100
#define MAX_TRANSACTIONS 100

typedef struct {
    char username[50];
    char password[50];
    char role[10];  
} User;

typedef struct {
    char title[100];
    char author[50];
    char genre[30];
    char ISBN[20];
    int available;
} Book;

typedef struct {
    char name[50];
    char contact[50];
    int membershipStatus;
} Member;

typedef struct {
    char username[50];
    char ISBN[20];
    char borrowDate[20];
    char returnDate[20];
    int fine;
} Transaction;

User users[MAX_USERS];
Book books[MAX_BOOKS];
Member members[MAX_MEMBERS];
Transaction transactions[MAX_TRANSACTIONS];

int userCount = 0, bookCount = 0, memberCount = 0, transactionCount = 0;

void saveData();
void loadData();
void mainMenu();
void registerUser();
void loginUser();
void resetPassword();
void addBook();
void deleteBook();
void updateBook();
void searchBooks();
void addMember();
void deleteMember();
void updateMember();
void viewMembers();
void borrowBook();
void returnBook();
void trackBorrowedBooks();
void calculateFine();
void currentDate(char* buffer);
int daysBetween(const char* date1, const char* date2);
void librarianMenu();
void memberMenu();

int main() {
    loadData();
    mainMenu();
    saveData();
    return 0;
}

void saveData() {
    FILE *file;

    file = fopen("users.txt", "w");
    for (int i = 0; i < userCount; i++) {
        fprintf(file, "%s %s %s\n", users[i].username, users[i].password, users[i].role);
    }
    fclose(file);

    file = fopen("books.txt", "w");
    for (int i = 0; i < bookCount; i++) {
        fprintf(file, "%s %s %s %s %d\n", books[i].title, books[i].author, books[i].genre, books[i].ISBN, books[i].available);
    }
    fclose(file);

    file = fopen("members.txt", "w");
    for (int i = 0; i < memberCount; i++) {
        fprintf(file, "%s %s %d\n", members[i].name, members[i].contact, members[i].membershipStatus);
    }
    fclose(file);

    file = fopen("transactions.txt", "w");
    for (int i = 0; i < transactionCount; i++) {
        fprintf(file, "%s %s %s %s %d\n", transactions[i].username, transactions[i].ISBN, transactions[i].borrowDate, transactions[i].returnDate, transactions[i].fine);
    }
    fclose(file);
}

void loadData() {
    FILE *file;
    
    file = fopen("users.txt", "r");
    while (fscanf(file, "%s %s %s", users[userCount].username, users[userCount].password, users[userCount].role) != EOF) {
        userCount++;
    }
    fclose(file);

    file = fopen("books.txt", "r");
    while (fscanf(file, "%s %s %s %s %d", books[bookCount].title, books[bookCount].author, books[bookCount].genre, books[bookCount].ISBN, &books[bookCount].available) != EOF) {
        bookCount++;
    }
    fclose(file);

    file = fopen("members.txt", "r");
    while (fscanf(file, "%s %s %d", members[memberCount].name, members[memberCount].contact, &members[memberCount].membershipStatus) != EOF) {
        memberCount++;
    }
    fclose(file);

    file = fopen("transactions.txt", "r");
    while (fscanf(file, "%s %s %s %s %d", transactions[transactionCount].username, transactions[transactionCount].ISBN, transactions[transactionCount].borrowDate, transactions[transactionCount].returnDate, &transactions[transactionCount].fine) != EOF) {
        transactionCount++;
    }
    fclose(file);
}

void mainMenu() {
    int choice;
    do {
        printf("Library Management System\n");
        printf("1. Register\n");
        printf("2. Login\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                registerUser();
                break;
            case 2:
                loginUser();
                break;
            case 3:
                saveData();
                exit(0);
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 3);
}

void registerUser() {
    User newUser;
    printf("Register a new user\n");
    printf("Enter username: ");
    scanf("%s", newUser.username);
    printf("Enter password: ");
    scanf("%s", newUser.password);
    printf("Enter role (librarian/member): ");
    scanf("%s", newUser.role);

    users[userCount++] = newUser;
    printf("User registered successfully.\n");
}

void loginUser() {
    char username[50], password[50];
    printf("Login\n");
    printf("Enter username: ");
    scanf("%s", username);
    printf("Enter password: ");
    scanf("%s", password);

    for (int i = 0; i < userCount; i++) {
        if (strcmp(users[i].username, username) == 0 && strcmp(users[i].password, password) == 0) {
            if (strcmp(users[i].role, "librarian") == 0) {
                librarianMenu();
            } else {
                memberMenu();
            }
            return;
        }
    }
    printf("Invalid username or password.\n");
}

void resetPassword() {
    char username[50], oldPassword[50], newPassword[50], confirmPassword[50];
    printf("Reset Password\n");
    printf("Enter your username: ");
    scanf("%s", username);

    int found = 0;
    for (int i = 0; i < userCount; i++) {
        if (strcmp(users[i].username, username) == 0) {
            found = 1;
            printf("Enter your current password: ");
            scanf("%s", oldPassword);

            if (strcmp(users[i].password, oldPassword) == 0) {
                printf("Enter new password: ");
                scanf("%s", newPassword);
                printf("Confirm new password: ");
                scanf("%s", confirmPassword);

                if (strcmp(newPassword, confirmPassword) == 0) {
                    strcpy(users[i].password, newPassword); 
                    printf("Password reset successfully.\n");
                } else {
                    printf("New password and confirmation do not match. Try again.\n");
                }
            } else {
                printf("Current password is incorrect. Try again.\n");
            }
            break;
        }
    }

    if (!found) {
        printf("Username not found.\n");
    }
}

void addBook() {
    Book newBook;
    printf("Add a new book\n");
    printf("Enter title: ");
    scanf(" %[^\n]%*c", newBook.title);
    printf("Enter author: ");
    scanf(" %[^\n]%*c", newBook.author);
    printf("Enter genre: ");
    scanf(" %[^\n]%*c", newBook.genre);
    printf("Enter ISBN: ");
    scanf(" %[^\n]%*c", newBook.ISBN);
    newBook.available = 1;

    books[bookCount++] = newBook;
    printf("Book added successfully.\n");
}

void deleteBook() {
    char ISBN[20];
    printf("Delete a book\n");
    printf("Enter ISBN: ");
    scanf("%s", ISBN);

    for (int i = 0; i < bookCount; i++) {
        if (strcmp(books[i].ISBN, ISBN) == 0) {
            for (int j = i; j < bookCount - 1; j++) {
                books[j] = books[j + 1];
            }
            bookCount--;
            printf("Book deleted successfully.\n");
            return;
        }
    }
    printf("Book not found.\n");
}

void updateBook() {
    char ISBN[20];
    printf("Update book details\n");
    printf("Enter ISBN: ");
    scanf("%s", ISBN);

    for (int i = 0; i < bookCount; i++) {
        if (strcmp(books[i].ISBN, ISBN) == 0) {
            printf("Enter new title: ");
            scanf(" %[^\n]%*c", books[i].title);
            printf("Enter new author: ");
            scanf(" %[^\n]%*c", books[i].author);
            printf("Enter new genre: ");
            scanf(" %[^\n]%*c", books[i].genre);
            books[i].available = 1;

            printf("Book details updated successfully.\n");
            return;
        }
    }
    printf("Book not found.\n");
}

void searchBooks() {
    char query[100];
    printf("Search books\n");
    printf("Enter title, author, genre, or ISBN: ");
    scanf(" %[^\n]%*c", query);

    for (int i = 0; i < bookCount; i++) {
        if (strstr(books[i].title, query) || strstr(books[i].author, query) || strstr(books[i].genre, query) || strstr(books[i].ISBN, query)) {
            printf("Title: %s, Author: %s, Genre: %s, ISBN: %s, Available: %d\n", books[i].title, books[i].author, books[i].genre, books[i].ISBN, books[i].available);
        }
    }
}

void addMember() {
    Member newMember;
    printf("Add a new member\n");
    printf("Enter name: ");
    scanf(" %[^\n]%*c", newMember.name);
    printf("Enter contact: ");
    scanf("%s", newMember.contact);
    newMember.membershipStatus = 1;

    members[memberCount++] = newMember;
    printf("Member added successfully.\n");
}

void deleteMember() {
    char name[50];
    printf("Delete a member\n");
    printf("Enter name: ");
    scanf(" %[^\n]%*c", name);

    for (int i = 0; i < memberCount; i++) {
        if (strcmp(members[i].name, name) == 0) {
            for (int j = i; j < memberCount - 1; j++) {
                members[j] = members[j + 1];
            }
            memberCount--;
            printf("Member deleted successfully.\n");
            return;
        }
    }
    printf("Member not found.\n");
}

void updateMember() {
    char name[50];
    printf("Update member details\n");
    printf("Enter name: ");
    scanf(" %[^\n]%*c", name);

    for (int i = 0; i < memberCount; i++) {
        if (strcmp(members[i].name, name) == 0) {
            printf("Enter new contact: ");
            scanf("%s", members[i].contact);
            members[i].membershipStatus = 1;

            printf("Member details updated successfully.\n");
            return;
        }
    }
    printf("Member not found.\n");
}

void viewMembers() {
    printf("View all members\n");
    for (int i = 0; i < memberCount; i++) {
        printf("Name: %s, Contact: %s, Membership Status: %d\n", members[i].name, members[i].contact, members[i].membershipStatus);
    }
}

void borrowBook() {
    Transaction newTransaction;
    printf("Borrow a book\n");
    printf("Enter your username: ");
    scanf("%s", newTransaction.username);
    printf("Enter ISBN of the book: ");
    scanf("%s", newTransaction.ISBN);

    int foundBook = 0;
    for (int i = 0; i < bookCount; i++) {
        if (strcmp(books[i].ISBN, newTransaction.ISBN) == 0 && books[i].available > 0) {
            books[i].available--;
            foundBook = 1;
            break;
        }
    }

    if (!foundBook) {
        printf("Book not available.\n");
        return;
    }

    currentDate(newTransaction.borrowDate);
    strcpy(newTransaction.returnDate, "N/A");
    newTransaction.fine = 0;

    transactions[transactionCount++] = newTransaction;
    printf("Book borrowed successfully.\n");
}

void returnBook() {
    char username[50], ISBN[20];
    printf("Return a book\n");
    printf("Enter your username: ");
    scanf("%s", username);
    printf("Enter ISBN of the book: ");
    scanf("%s", ISBN);

    for (int i = 0; i < transactionCount; i++) {
        if (strcmp(transactions[i].username, username) == 0 && strcmp(transactions[i].ISBN, ISBN) == 0 && strcmp(transactions[i].returnDate, "N/A") == 0) {
            currentDate(transactions[i].returnDate);
            printf("Book returned successfully.\n");

            for (int j = 0; j < bookCount; j++) {
                if (strcmp(books[j].ISBN, ISBN) == 0) {
                    books[j].available++;
                    break;
                }
            }
            return;
        }
    }
    printf("No record of borrowed book found.\n");
}

void trackBorrowedBooks() {
    printf("Borrowed books list\n");
    for (int i = 0; i < transactionCount; i++) {
        if (strcmp(transactions[i].returnDate, "N/A") == 0) {
            printf("Username: %s, ISBN: %s, Borrow Date: %s, Fine: %d\n", transactions[i].username, transactions[i].ISBN, transactions[i].borrowDate, transactions[i].fine);
        }
    }
}

void calculateFine() {
    char today[20];
    currentDate(today);

    for (int i = 0; i < transactionCount; i++) {
        if (strcmp(transactions[i].returnDate, "N/A") == 0) {
            int days = daysBetween(transactions[i].borrowDate, today);
            if (days > 14) {
                transactions[i].fine = (days - 14) * 10;
                printf("User: %s, Book: %s, Overdue: %d days, Fine: %d\n", transactions[i].username, transactions[i].ISBN, days - 14, transactions[i].fine);
            }
        }
    }
}

void currentDate(char* buffer) {
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    sprintf(buffer, "%04d-%02d-%02d", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday);
}

int daysBetween(const char* date1, const char* date2) {
    struct tm tm1 = {0}, tm2 = {0};
    sscanf(date1, "%d-%d-%d", &tm1.tm_year, &tm1.tm_mon, &tm1.tm_mday);
    sscanf(date2, "%d-%d-%d", &tm2.tm_year, &tm2.tm_mon, &tm2.tm_mday);

    tm1.tm_year -= 1900;
    tm1.tm_mon -= 1;
    tm2.tm_year -= 1900;
    tm2.tm_mon -= 1;

    time_t t1 = mktime(&tm1);
    time_t t2 = mktime(&tm2);

    return (int)difftime(t2, t1) / (60 * 60 * 24);
}

void librarianMenu() {
    int choice;
    do {
        printf("Librarian Menu\n");
        printf("1. Add Book\n");
        printf("2. Delete Book\n");
        printf("3. Update Book\n");
        printf("4. Search Books\n");
        printf("5. Add Member\n");
        printf("6. Delete Member\n");
        printf("7. Update Member\n");
        printf("8. View Members\n");
        printf("9. Track Borrowed Books\n");
        printf("10. Calculate Fine\n");
        printf("11. Reset Password\n");
        printf("12. Logout\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                addBook();
                break;
            case 2:
                deleteBook();
                break;
            case 3:
                updateBook();
                break;
            case 4:
                searchBooks();
                break;
            case 5:
                addMember();
                break;
            case 6:
                deleteMember();
                break;
            case 7:
                updateMember();
                break;
            case 8:
                viewMembers();
                break;
            case 9:
                trackBorrowedBooks();
                break;
            case 10:
                calculateFine();
                break;
            case 11:
                resetPassword();
                break;
            case 12:
                printf("Logging out...\n");
                return;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 12);
}

void memberMenu() {
    int choice;
    do {
        printf("Member Menu\n");
        printf("1. Search Books\n");
        printf("2. Borrow Book\n");
        printf("3. Return Book\n");
        printf("4. Track Borrowed Books\n");
        printf("5. Logout\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                searchBooks();
                break;
            case 2:
                borrowBook();
                break;
            case 3:
                returnBook();
                break;
            case 4:
                trackBorrowedBooks();
                break;
            case 5:
                printf("Logging out...\n");
                return;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 5);
}
