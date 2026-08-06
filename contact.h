#ifndef CONTACT_H
#define CONTACT_H

#define MAX_CONTACTS 100

typedef struct {
    char name[50];
    char phone[20];
    char email[50];
} Contact;

typedef struct {
    Contact contacts[100];
    int contactCount;
} AddressBook;

void createContact(AddressBook *addressBook);
void searchContact(AddressBook *addressBook);
void editContact(AddressBook *addressBook);
void deleteContact(AddressBook *addressBook);
void listContacts(AddressBook *addressBook);
void initialize(AddressBook *addressBook);
void saveAndExit(AddressBook *addressBook);
void saveContactsToFile(AddressBook *addressBook);
void loadContactsFromFile(AddressBook *addressBook);

int FindContact(AddressBook *addressBook, char find[],int DeletOrEdit);
int ValidateContactName(char name[]);
int ValidateContactPhone(AddressBook *addressBook, char phone[], int index);
int ValidateContactEmail(AddressBook *addressBook, char email[], int index);

#endif