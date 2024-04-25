#include <iostream>
#include <string>
#include <Windows.h>
#include <iomanip>
#include <vector>

class Book {
public:
    std::string title;
    std::string author;
    std::string genre;
    std::string description;
    bool reserved;

    Book(std::string t, std::string a, std::string g, std::string d) : title(t), author(a), genre(g), description(d), reserved(false) {}
};

class LibraryCatalog {
private:
    std::vector<Book> books;
    std::vector<Book*> reservedBooks;

public:
    void addBook(const Book& book) {
        books.push_back(book);
    }

    void displayBookInfo(const Book& book) {
        std::cout << "Название: " << book.title << std::endl;
        std::cout << "Автор: " << book.author << std::endl;
        std::cout << "Жанр: " << book.genre << std::endl;
        std::cout << "Описание: " << book.description << std::endl;
        std::cout << "Зарезервирована: " << (book.reserved ? "Да" : "Нет") << std::endl;
    }

    Book* searchBookByCriteria(const std::string& criteria) {
        for (auto& book : books) {
            if (book.title == criteria || book.author == criteria || book.genre == criteria || book.description == criteria) {
                return &book;
            }
        }
        return nullptr;
    }

    void reserveBook(Book* book) {
        if (book) {
            book->reserved = true;
            reservedBooks.push_back(book);
            std::cout << "Книга \"" << book->title << "\" успешно зарезервирована." << std::endl;
        }
        else {
            std::cout << "Книга не найдена." << std::endl;
        }
    }

    void displayReservedBooks() {
        std::cout << "Список зарезервированных книг:" << std::endl;
        for (auto& book : reservedBooks) {
            displayBookInfo(*book);
        }
    }

    void cancelReservation(Book* book) {
        if (book) {
            book->reserved = false;
            reservedBooks.erase(std::remove(reservedBooks.begin(), reservedBooks.end(), book), reservedBooks.end());
            std::cout << "Резервация книги \"" << book->title << "\" отменена." << std::endl;
        }
        else {
            std::cout << "Книга не найдена." << std::endl;
        }
    }
};

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    setlocale(LC_ALL, "Russian");
    LibraryCatalog catalog;

    while (true) {
        std::cout << "Выберите действие:" << std::endl;
        std::cout << "1. Поиск книги" << std::endl;
        std::cout << "2. Добавление книги" << std::endl;
        std::cout << "3. Отображение информации о книге" << std::endl;
        std::cout << "4. Резервирование книги" << std::endl;
        std::cout << "5. Просмотр зарезервированных книг" << std::endl;
        std::cout << "6. Отмена резервации книги" << std::endl;
        std::cout << "7. Выход" << std::endl;

        int choice;
        std::cin >> choice;

        if (choice == 1) {
            std::string criteria;
            std::cout << "Введите критерий поиска (название, автор, жанр, описание): ";
            std::cin >> criteria;
            Book* foundBook = catalog.searchBookByCriteria(criteria);
            if (foundBook) {
                catalog.displayBookInfo(*foundBook);
            }
            else {
                std::cout << "Книга не найдена." << std::endl;
            }
        }
        else if (choice == 2) {
            std::string title, author, genre, description;
            std::cout << "Введите название книги: ";
            std::cin >> title;
            std::cout << "Введите автора книги: ";
            std::cin >> author;
            std::cout << "Введите жанр книги: ";
            std::cin >> genre;
            std::cout << "Введите описание книги: ";
            std::cin >> description;

            Book newBook(title, author, genre, description);
            catalog.addBook(newBook);
            std::cout << "Книга успешно добавлена в каталог." << std::endl;
        }
        else if (choice == 3) {
            std::string criteria;
            std::cout << "Введите критерий поиска (название, автор, жанр, описание): ";
            std::cin >> criteria;
            Book* foundBook = catalog.searchBookByCriteria(criteria);
            if (foundBook) {
                catalog.displayBookInfo(*foundBook);
            }
            else {
                std::cout << "Книга не найдена." << std::endl;
            }
        }
        else if (choice == 4) {
            std::string criteria;
            std::cout << "Введите критерий поиска для резервирования книги (название, автор, жанр, описание): ";
            std::cin >> criteria;
            Book* bookToReserve = catalog.searchBookByCriteria(criteria);
            if (bookToReserve) {
                catalog.reserveBook(bookToReserve);
            }
            else {
                std::cout << "Книга не найдена." << std::endl;
            }
        }
        else if (choice == 5) {
            catalog.displayReservedBooks();
        }
        else if (choice == 6) {
            std::string criteria;
            std::cout << "Введите критерий поиска для отмены резервации книги (название, автор, жанр, описание): ";
            std::cin >> criteria;
            Book* bookToCancelReservation = catalog.searchBookByCriteria(criteria);
            if (bookToCancelReservation) {
                catalog.cancelReservation(bookToCancelReservation);
            }
            else {
                std::cout << "Книга не найдена." << std::endl;
            }
        }
        else if (choice == 7) {
            break;
        }
        else {
            std::cout << "Некорректный выбор. Пожалуйста, выберите снова." << std::endl;
        }
    }

    return 0;
}
