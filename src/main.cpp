#include <iostream>
#include <fstream>
#include <string>
using namespace std;

const int max_number = 100;

struct Date {
    int day, month, year;
};

struct Movie {
    string name_of_movie;
    float fee = 0;
    bool is_rented = false;
    int people_rent_movie = 0;
    float movie_rate = 0;
    int people_rated_movie = 0;
};

struct Customer {
    int id = 0;
    string name;
    int day_late = 0;
    int rentedMoviesCount = 0;
    string rentedMovies[max_number];
};

struct Rental {
    int customer_Id = 0;
    string movie_namee;
    int days_Rented = 0;
    Date start;
    Date returnning;
    int movie_rented = 0;
};

// ============ Global Variables ============
Movie movies[max_number];
Customer customers[max_number];
Rental rentals[max_number];
int total_customers = 0;
int total_movie = 0;
int total_rented_movie = 0;

// ============ Functions ============
void loadFromFile();
void saveToFile();
void addmovie();
void displaymovies();
void addCustomer();
void listCustomers();
void rentmovie(int customer_id, string name_of_movie, int day, int month, int year, int period);
void calculateOverdueFees(int daysLate);
void listOverdueAccounts();
void rate_of_movies(string name_of_movie);
void returnmovie(int customer_id, string name, int day, int month, int years);
void list_rentmovie();
void display_the_highest_rated_movie();
void display_the_most_rented_movies();

// ============ Implementation ============
void loadFromFile() {
    ifstream inFile("data.txt");
    if (!inFile) return;

    inFile >> total_customers >> total_movie >> total_rented_movie;
    inFile.ignore();
    for (int i = 0; i < total_customers; i++) {
        inFile >> customers[i].id;
        inFile.ignore();
        getline(inFile, customers[i].name);
        inFile >> customers[i].day_late;
        inFile >> customers[i].rentedMoviesCount;
        inFile.ignore();
        for (int j = 0; j < customers[i].rentedMoviesCount; j++) {
            getline(inFile, customers[i].rentedMovies[j]);
        }
    }

    for (int i = 0; i < total_movie; i++) {
        getline(inFile, movies[i].name_of_movie);
        inFile >> movies[i].fee;
        inFile >> movies[i].is_rented;
        inFile >> movies[i].people_rent_movie;
        inFile >> movies[i].movie_rate;
        inFile >> movies[i].people_rated_movie;
        inFile.ignore();
    }

    for (int i = 0; i < total_rented_movie; i++) {
        inFile >> rentals[i].customer_Id;
        inFile.ignore();
        getline(inFile, rentals[i].movie_namee);
        inFile >> rentals[i].days_Rented;
        inFile >> rentals[i].start.day >> rentals[i].start.month >> rentals[i].start.year;
        inFile >> rentals[i].returnning.day >> rentals[i].returnning.month >> rentals[i].returnning.year;
        inFile >> rentals[i].movie_rented;
        inFile.ignore();
    }

    inFile.close();
}

void saveToFile() {
    ofstream outFile("data.txt");
    outFile << total_customers << " " << total_movie << " " << total_rented_movie << "\n";
    for (int i = 0; i < total_customers; i++) {
        outFile << customers[i].id << "\n";
        outFile << customers[i].name << "\n";
        outFile << customers[i].day_late << "\n";
        outFile << customers[i].rentedMoviesCount << "\n";
        for (int j = 0; j < customers[i].rentedMoviesCount; j++) {
            outFile << customers[i].rentedMovies[j] << "\n";
        }
    }

    for (int i = 0; i < total_movie; i++) {
        outFile << movies[i].name_of_movie << "\n";
        outFile << movies[i].fee << "\n";
        outFile << movies[i].is_rented << "\n";
        outFile << movies[i].people_rent_movie << "\n";
        outFile << movies[i].movie_rate << "\n";
        outFile << movies[i].people_rated_movie << "\n";
    }

    for (int i = 0; i < total_rented_movie; i++) {
        outFile << rentals[i].customer_Id << "\n";
        outFile << rentals[i].movie_namee << "\n";
        outFile << rentals[i].days_Rented << "\n";
        outFile << rentals[i].start.day << " " << rentals[i].start.month << " " << rentals[i].start.year << "\n";
        outFile << rentals[i].returnning.day << " " << rentals[i].returnning.month << " " << rentals[i].returnning.year << "\n";
        outFile << rentals[i].movie_rented << "\n";
    }

    outFile.close();
}

void addmovie() {
    if (total_movie >= max_number) {
        cout << "Cannot add more movies. Storage full!" << endl;
        return;
    }
    cin.ignore();
    cout << "Enter the movie name: ";
    getline(cin, movies[total_movie].name_of_movie);
    cout << "Enter the Movie Fee: ";
    cin >> movies[total_movie].fee;
    cin.ignore();
    total_movie++;
}

void displaymovies() {
    if (total_movie == 0) {
        cout << "There isn't any movie added yet " << endl;
    }
    for (int i = 0; i < total_movie; i++) {
        cout << movies[i].name_of_movie << '\t' << movies[i].fee << "$ " << endl;
    }
}

void addCustomer() {
    if (total_customers >= max_number) {
        cout << "Cannot add more customers. Storage full!" << endl;
        return;
    }
    cout << "Enter customer ID: ";
    cin >> customers[total_customers].id;
    cin.ignore();
    cout << "Enter customer name: ";
    getline(cin, customers[total_customers].name);
    cout << "Customer added successfully!" << endl;
    total_customers++;
}

void listCustomers() {
    if (total_customers == 0) {
        cout << "No customers in the system!" << endl;
        return;
    }
    cout << "\n--- List of Customers ---" << endl;
    for (int i = 0; i < total_customers; i++) {
        cout << "ID: " << customers[i].id << endl;
        cout << "Name: " << customers[i].name << endl;
        cout << "Rented Movies: " << customers[i].rentedMoviesCount << endl;
        cout << "------------------------" << endl;
    }
}

void rentmovie(int customer_id, string name_of_movie, int day, int month, int year, int period) {
    for (int i = 0; i < total_customers; i++) {
        if (customers[i].id == customer_id) {
            for (int k = 0; k < total_movie; k++) {
                if (movies[k].is_rented && movies[k].name_of_movie == name_of_movie) {
                    cout << name_of_movie << " is not available now" << endl;
                    return;
                }
            }
            customers[i].rentedMoviesCount++;
            customers[i].rentedMovies[customers[i].rentedMoviesCount - 1] = name_of_movie;
            for (int j = 0; j < total_movie; j++) {
                if (movies[j].name_of_movie == name_of_movie) {
                    rentals[total_rented_movie].customer_Id = customer_id;
                    rentals[total_rented_movie].movie_namee = name_of_movie;
                    rentals[total_rented_movie].start.day = day;
                    rentals[total_rented_movie].start.month = month;
                    rentals[total_rented_movie].start.year = year;
                    rentals[total_rented_movie].days_Rented = period;
                    rentals[total_rented_movie].returnning.day = day + period;
                    rentals[total_rented_movie].returnning.month = month;
                    rentals[total_rented_movie].returnning.year = year;

                    while (rentals[total_rented_movie].returnning.day > 30) {
                        switch (rentals[total_rented_movie].returnning.month) {
                        case 1: case 3: case 5: case 7: case 8: case 10: case 12:
                            if (rentals[total_rented_movie].returnning.day > 31) {
                                rentals[total_rented_movie].returnning.day -= 31;
                                rentals[total_rented_movie].returnning.month++;
                            }
                            break;
                        case 4: case 6: case 9: case 11:
                            if (rentals[total_rented_movie].returnning.day > 30) {
                                rentals[total_rented_movie].returnning.day -= 30;
                                rentals[total_rented_movie].returnning.month++;
                            }
                            break;
                        case 2:
                            if (rentals[total_rented_movie].returnning.day > 28) {
                                rentals[total_rented_movie].returnning.day -= 28;
                                rentals[total_rented_movie].returnning.month++;
                            }
                            break;
                        }
                        if (rentals[total_rented_movie].returnning.month > 12) {
                            rentals[total_rented_movie].returnning.month = 1;
                            rentals[total_rented_movie].returnning.year++;
                        }
                    }

                    rentals[total_rented_movie].movie_rented++;
                    movies[j].people_rent_movie++;
                    movies[j].is_rented = true;
                    total_rented_movie++;
                    return;
                }
            }
            cout << "Movie not found!" << endl;
            return;
        }
    }
    cout << "Customer not found!" << endl;
}

void calculateOverdueFees(int daysLate) {
    if (daysLate < 0) {
        cout << "Warning: Days late cannot be negative. Setting to 0." << endl;
        daysLate = 0;
    }
    float dailyFee;
    if (daysLate <= 3) dailyFee = 1.50f;
    else if (daysLate <= 7) dailyFee = 2.00f;
    else dailyFee = 3.00f;
    float totalFee = daysLate * dailyFee;
    cout << "Daily late fee: $" << dailyFee << endl;
    cout << "Total overdue fee: $" << totalFee << endl;
}

void listOverdueAccounts() {
    if (total_customers == 0) {
        cout << "No accounts in the system." << endl;
        return;
    }
    cout << "\nOverdue Accounts:\n";
    cout << "-------------------------------------------------\n";
    cout << "Customer Name\t\tDays Late\tTotal Fee" << endl;
    cout << "-------------------------------------------------\n";
    bool foundOverdue = false;
    for (int i = 0; i < total_customers; i++) {
        if (customers[i].day_late > 0) {
            foundOverdue = true;
            float dailyFee;
            if (customers[i].day_late <= 3) dailyFee = 1.50f;
            else if (customers[i].day_late <= 7) dailyFee = 2.00f;
            else dailyFee = 3.00f;
            float totalFee = customers[i].day_late * dailyFee;
            cout << customers[i].name << "\t\t\t" << customers[i].day_late << "\t\t$" << totalFee << endl;
        }
    }
    if (!foundOverdue) cout << "No overdue accounts found." << endl;
    cout << "-------------------------------------------------\n";
}

void rate_of_movies(string name_of_movie) {
    for (int i = 0; i < total_movie; i++) {
        if (movies[i].name_of_movie == name_of_movie) {
            float rate;
            cout << "Enter rating (1-5) for " << name_of_movie << ": ";
            cin >> rate;
            if (rate >= 1 && rate <= 5) {
                movies[i].movie_rate += rate;
                movies[i].people_rated_movie++;
                cout << "Rating added successfully!" << endl;
                return;
            }
            else {
                cout << "Invalid rating. Must be between 1 and 5." << endl;
                return;
            }
        }
    }
    cout << "Movie not found." << endl;
}

void returnmovie(int customer_id, string name, int day, int month, int years) {
    for (int i = 0; i < total_rented_movie; i++) {
        if (rentals[i].movie_namee == name && rentals[i].customer_Id == customer_id) {
            int expectedReturn = rentals[i].returnning.day + (rentals[i].returnning.month * 30) + (rentals[i].returnning.year * 365);
            int actualReturn = day + (month * 30) + (years * 365);
            int daysLate = actualReturn - expectedReturn;
            for (int j = 0; j < total_customers; j++) {
                if (customers[j].id == customer_id) {
                    customers[j].day_late = daysLate > 0 ? daysLate : 0;
                    if (daysLate > 0) {
                        cout << "Late return detected." << endl;
                        calculateOverdueFees(daysLate);
                    }
                    else {
                        cout << "Returned on time." << endl;
                    }
                    for (int k = 0; k < customers[j].rentedMoviesCount; k++) {
                        if (customers[j].rentedMovies[k] == name) {
                            for (int m = k; m < customers[j].rentedMoviesCount - 1; m++) {
                                customers[j].rentedMovies[m] = customers[j].rentedMovies[m + 1];
                            }
                            customers[j].rentedMoviesCount--;
                            break;
                        }
                    }
                    break;
                }
            }
            for (int j = 0; j < total_movie; j++) {
                if (movies[j].name_of_movie == name) {
                    movies[j].is_rented = false;
                    break;
                }
            }
            for (int j = i; j < total_rented_movie - 1; j++) {
                rentals[j] = rentals[j + 1];
            }
            total_rented_movie--;
            cout << "Movie returned successfully." << endl;
            return;
        }
    }
    cout << "Rental not found." << endl;
}

void list_rentmovie() {
    if (total_rented_movie == 0) {
        cout << "No movies rented." << endl;
        return;
    }
    for (int i = 0; i < total_rented_movie; i++) {
        cout << "Movie: " << rentals[i].movie_namee
            << "\tCustomer ID: " << rentals[i].customer_Id
            << "\tDays Rented: " << rentals[i].days_Rented << endl;
    }
}

void display_the_highest_rated_movie() {
    string name_of_highest_rate;
    float highest_rate = 0;
    for (int i = 0; i < total_movie; i++) {
        if (movies[i].people_rated_movie > 0) {
            float rate = movies[i].movie_rate / movies[i].people_rated_movie;
            if (rate > highest_rate) {
                highest_rate = rate;
                name_of_highest_rate = movies[i].name_of_movie;
            }
        }
    }
    if (highest_rate != 0) {
        cout << "Highest-rated movie: " << name_of_highest_rate << " with rate: " << highest_rate << endl;
    }
    else {
        cout << "No movies rated." << endl;
    }
}

void display_the_most_rented_movies() {
    if (total_rented_movie == 0) {
        cout << "No movies rented." << endl;
        return;
    }
    for (int i = 0; i < total_movie - 1; i++) {
        for (int j = 0; j < total_movie - i - 1; j++) {
            if (movies[j].people_rent_movie < movies[j + 1].people_rent_movie) {
                Movie temp = movies[j];
                movies[j] = movies[j + 1];
                movies[j + 1] = temp;
            }
        }
    }
    cout << "Most rented movies:" << endl;
    for (int i = 0; i < total_movie; i++) {
        if (movies[i].people_rent_movie > 0) {
            cout << movies[i].name_of_movie << " Rented: " << movies[i].people_rent_movie << " times" << endl;
        }
    }
}

// ============ Main ============
int main() {
    loadFromFile();

    int choice;
    do {
        cout << "\n===== Movie Rental System =====\n";
        cout << "1. Add Movie\n";
        cout << "2. Display Movies\n";
        cout << "3. Add Customer\n";
        cout << "4. List Customers\n";
        cout << "5. Rent Movie\n";
        cout << "6. Return Movie\n";
        cout << "7. List Rented Movies\n";
        cout << "8. Rate a Movie\n";
        cout << "9. List Overdue Accounts\n";
        cout << "10. Display Highest Rated Movie\n";
        cout << "11. Display Most Rented Movies\n";
        cout << "0. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        if (choice == 1) addmovie();
        else if (choice == 2) displaymovies();
        else if (choice == 3) addCustomer();
        else if (choice == 4) listCustomers();
        else if (choice == 5) {
            int id, d, m, y, period;
            string movieName;
            cout << "Enter Customer ID: "; cin >> id;
            cin.ignore();
            cout << "Enter Movie Name: "; getline(cin, movieName);
            cout << "Enter Start Date (day month year): "; cin >> d >> m >> y;
            cout << "Enter Rental Period (days): "; cin >> period;
            rentmovie(id, movieName, d, m, y, period);
        }
        else if (choice == 6) {
            int id, d, m, y;
            string movieName;
            cout << "Enter Customer ID: "; cin >> id;
            cin.ignore();
            cout << "Enter Movie Name: "; getline(cin, movieName);
            cout << "Enter Return Date (day month year): "; cin >> d >> m >> y;
            returnmovie(id, movieName, d, m, y);
        }
        else if (choice == 7) list_rentmovie();
        else if (choice == 8) {
            string movieName;
            cin.ignore();
            cout << "Enter Movie Name: "; getline(cin, movieName);
            rate_of_movies(movieName);
        }
        else if (choice == 9) listOverdueAccounts();
        else if (choice == 10) display_the_highest_rated_movie();
        else if (choice == 11) display_the_most_rented_movies();
        else if (choice == 0) {
            saveToFile();
            cout << "Exiting... Data saved!" << endl;
        }
        else cout << "Invalid choice. Try again." << endl;

    } while (choice != 0);

    return 0;
}
