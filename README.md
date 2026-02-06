# Movie Rental System 🎬

A **C++ project** to manage a **movie rental store**, including customers, movies, rentals, returns, overdue fees, and movie ratings.

---

## Features

- Add and list **customers** and their rented movies  
- Add and list **movies** with fees and rental status  
- **Rent movies** with rental period and fees  
- **Return movies** and calculate overdue fees  
- Display **overdue accounts**  
- Display **most rented movies**  
- Rate movies and show **highest-rated movies**  
- Data is saved and loaded automatically using files  

---

## Structure

- **Customer**: ID, name, rented movies, days late  
- **Movie**: name, rental fee, rental status, rental count, rating info  
- **Rental**: customer ID, movie name, rental period, start & return dates  

All data is handled using **arrays**, **structs**, and **functions**.

---

## How to Run

1. Open the project in a **C++ IDE** or compiler  
2. Compile and run  
3. Use the **menu** to manage movies, customers, rentals, returns, and ratings  

All data is loaded from `data.txt` at startup and saved automatically on exit.

---

## Link to Code

[View Source Code](https://github.com/ahmedsherifff4/Liner-Follower-Robot/blob/main/src/main.cpp)
