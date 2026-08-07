# 📒 Address Book Management System (C)

A console-based **Address Book Management System** developed in **C** that allows users to manage contacts efficiently. The application supports creating, searching, editing, deleting, and listing contacts with proper input validation and file-based data persistence.

---

## 🚀 Features

* ➕ Create new contacts
* 🔍 Search contacts by name or phone number
* ✏️ Edit existing contacts
* 🗑️ Delete contacts
* 📋 Display all contacts
* 💾 Save contacts to a CSV file
* 📂 Load contacts automatically on startup
* ✅ Name, phone number, and email validation
* 🚫 Duplicate phone number and email detection

---

## 🛠️ Technologies Used

* C Programming
* Standard C Libraries

  * stdio.h
  * stdlib.h
  * string.h
  * ctype.h
* File Handling (CSV)

---

## 📁 Project Structure

```
AddressBook/
│── main.c
│── contact.c
│── contact.h
│── populate.c
│── populate.h
│── contact.csv
│── README.md
```

---

## 📌 Menu

```
Address Book Menu

1. Create Contact
2. Search Contact
3. Edit Contact
4. Delete Contact
5. List All Contacts
6. Save and Exit
```

---

## ✅ Validations

### Name

* Only alphabetic characters are allowed.

### Phone Number

* Must contain exactly 10 digits.
* Duplicate phone numbers are not allowed.

### Email

* Must start with an alphabet.
* Must contain '@' and '.'.
* Invalid special characters are rejected.
* Duplicate email addresses are not allowed.

---

## 💾 Data Storage

All contacts are stored in a **contact.csv** file.

The application:

* Loads contacts automatically during startup.
* Saves all contacts before exiting.

---

## ▶️ How to Run

Compile the project:

```bash
gcc main.c contact.c populate.c -o addressbook
```

Run:

```bash
./addressbook
```

For Windows:

```bash
addressbook.exe
```

---

## 📸 Project Highlights

* User-friendly menu-driven interface
* Modular programming approach
* File handling using CSV
* Input validation
* Duplicate record prevention
* Simple and clean console application

---

## 📚 Learning Outcomes

This project helped in understanding:

* Structures in C
* Functions
* Arrays
* String manipulation
* File handling
* Data validation
* Modular programming
* CRUD operations
* Menu-driven application development

---

## 👨‍💻 Author

**Vengadesh**
