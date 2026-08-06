#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "contact.h"
#include "populate.h"

/*
Function Name : ValidateContactName
Input : charater array 
Output : if the name  is valid return 0 else return 1
Description: Validate the name if there is any numeric value are present 
*/

int ValidateContactName(char name[])
{
    //declering variable to check the valid 
    int valid = 1;

    //loop until name of i equal to null
    for(int i=0; name[i] !='\0'; i++)
    {
        //check the name of i is not alpha
        if(isalpha(name[i]) == 0 )
        {
            printf("Name should be alphabet only\n");
            valid = 0;  //valid is set to zero
            break;
        }
    }

    //if the valid is not 1 return 0 else return 1
    if(!valid)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

/*
 *  Function Name : ValidateContactPhone
 *  Input :
 *      addressBook - Pointer to AddressBook structure
 *      email[]     - Phone string to validate
 *      index       - Index to skip during duplicate checks (used in edit mode)
 *  Output :
 *      Returns 0 if the email is valid
 *      Returns 1 if the email is invalid
 *  Description :
 *      Validates the given phone string
 */

int ValidateContactPhone(AddressBook *addressBook, char phone[], int index)
{
    int valid = 1;

    //run a loop until phone of not equal to null
    for(int i=0; phone[i] !='\0'; i++)
    {
        //check the current index is contain only contain numeric characters
        if( isdigit(phone[i]) == 0 )
        {
            printf("The Phone shold contains only digits\n");
            valid = 0;
            break;
        }
    }
    //check the phone number length contain 10 digit or not
    if (strlen(phone) !=10)
    {
        printf("The Phone Number must be 10 digits \n");
        valid = 0;
    }

    //checking the phone number is already present or not
    for (int i = 0; i < addressBook->contactCount; i++)
    {
        if(i == index)
        {
            continue;
        }
        if (strcmp(addressBook->contacts[i].phone, phone) == 0)
        {
            printf("This phone number already exists\n");
            valid = 0;
            break;
        }
    }

    //if the valid is not 1 return 1 else return 0
    if(!valid)
    {
        return 1;
    }
    else
    {
        return 0;
    }
    
}

/*
 *  Function Name : ValidateContactEmail
 *  Input :
 *      addressBook - Pointer to AddressBook structure
 *      email[]     - Email string to validate
 *      index       - Index to skip during duplicate checks (used in edit mode)
 *  Output :
 *      Returns 0 if the email is valid
 *      Returns 1 if the email is invalid
 *  Description :
 *      Validates the given email string
 */


int ValidateContactEmail(AddressBook *addressBook, char email[], int index)
{
    int valid = 1;

    // Check if the first character is an alphabet
    if (!isalpha(email[0])) 
    {
        printf("First letter should be alphabet only\n");
        valid = 0;
    }

    // Check mandatory characters '@' and '.'
    if (strchr(email, '@') == NULL || strchr(email, '.') == NULL) 
    {
        printf("Email must contain '@' and '.' characters.\n");
        valid = 0;
    }

    // Ensure characters exist after the last '.'
    char *dot_position = strchr(email, '.');
    char *null_ptr = strchr(email, '\0');

    if (dot_position + 1 == null_ptr)
    {
        printf("There must be characters after '.'\n");
        valid = 0;
    }

    // Ensure '.' does not immediately follow '@'
    char *at_pos = strchr(email, '@');
    char *dot_pos = strchr(email, '.');

    if (at_pos + 1 == dot_pos)
    {
        printf("There must be characters between '@' and '.'\n");
        valid = 0;
    }

    // Check for any illegal characters in email
    for (int i = 0; email[i] != '\0'; i++)
    {
        char c = email[i];

        if (!(isalnum(c) || c == '@' || c == '.' || c == '_' || c == '-'))
        {
            printf("Email contains invalid special characters\n");
            valid = 0;
            break;
        }
    }

    // Check that email does not end with invalid characters
    char last_ch = email[strlen(email) - 1];
    if (last_ch == '@' || last_ch == '.' || last_ch == '_' || last_ch == '-')
    {
        printf("Invalid email ending\n");
        valid = 0;
    }

    // Check for duplicate email in address book (excluding the given index)
    for (int i = 0; i < addressBook->contactCount; i++)
    {
        if (i == index)
            continue;

        if (strcmp(addressBook->contacts[i].email, email) == 0)
        {
            printf("This email already exists\n");
            valid = 0;
            break;
        }
    }

    // Return validation result (0 = valid, 1 = invalid)
    if (!valid)
        return 1;
    else
        return 0;

}

/*
 *  Function Name : loadContactsFromFile
 *  Input :
 *      addressBook - Pointer to AddressBook structure
 *  Output :
 *      Loads and stores contacts from the file into the addressBook structure
 *  Description :
 *      Reads contact information from "contact.csv" and populates the
 *      address book:
 *          - First line contains contact count
 *          - Following lines contain name, phone, email in CSV format
 */

void loadContactsFromFile(AddressBook *addressBook)
{
    FILE *fp = fopen("contact.csv","r");

    //Getting contact count
    fscanf(fp, "%d\n", &addressBook->contactCount);

    //Getting contacts  from file and store into addressbook structure
    for(int i = 0; i < addressBook->contactCount; i++) 
    {
        fscanf(fp, "%[^,],%[^,],%[^\n]\n", 
            addressBook->contacts[i].name,
            addressBook->contacts[i].phone,
            addressBook->contacts[i].email);
    }

    fclose(fp);

}

void saveContactsToFile(AddressBook *addressBook)
{
    FILE *fp = fopen("contact.csv","w");

    fprintf(fp, "%d\n", addressBook->contactCount);

    for(int i = 0; i < addressBook->contactCount; i++) 
    {
        fprintf(fp, "%s,%s,%s\n",
        addressBook->contacts[i].name,
        addressBook->contacts[i].phone,
        addressBook->contacts[i].email);
    }

    fclose(fp);


}

/*
 *  Function Name : FindContact
 *
 *  Input :
 *      addressBook  - Pointer to AddressBook structure
 *      Find[]       - String to match against name or phone
 *      DeletOrEdit  - Mode selection (1 = Edit, any other value = Delete)
 *
 *  Output :
 *      Returns the index of the selected matching contact
 *      Returns -1 if no match is found or invalid choice is entered
 *
 *  Description :
 *      Searches the address book for contacts whose name or phone matches
 *      the given Find string. Displays all matching contacts in a numbered
 *      list. The user is then prompted to choose one of the matched entries
 *      for editing or deleting. The function returns the actual index of
 *      the selected contact in the AddressBook structure.
 */


int FindContact(AddressBook *addressBook, char Find[], int DeletOrEdit)
{
    // Array to store matched contact indexes
    int matchcontact[20];
    int matchcount = 0;

    // Search for matching name or phone in the address book
    for (int i = 0; i < addressBook->contactCount; i++)
    {
        if (strcmp(addressBook->contacts[i].name, Find) == 0 ||
            strcmp(addressBook->contacts[i].phone, Find) == 0)
        {
            matchcontact[matchcount] = i;
            matchcount++;
        }
    }

    // If no matches found, stop and return -1
    if (matchcount == 0)
    {
        printf("No Matching Contacts are Found\n");
        return -1;
    }

    int choice;
    int index;

    // Print table header for displaying matched contacts
    printf("-----------------------------------------------------------------------------------------\n");
    printf("%s    %-25s %-15s %-30s\n","SI", "Name", "Phone", "Email");
    printf("-----------------------------------------------------------------------------------------\n");

    // Display all matched contacts to the user
    for (int i = 0; i < matchcount; i++)
    {
        int index = matchcontact[i];

        printf("%d    %-25s %-15s %-30s\n", i + 1,
               addressBook->contacts[index].name,
               addressBook->contacts[index].phone,
               addressBook->contacts[index].email);
    }

    printf("-----------------------------------------------------------------------------------------\n\n");

    // Ask user whether they want to edit or delete the selected contact
    if (DeletOrEdit == 1)
        printf("Enter the number which you want to Edit: ");
    else
        printf("Enter the number which you want to Delete: ");
    
    scanf("%d", &choice);
    while (getchar() != '\n');   // Clear input buffer

    // Validate user choice
    if (choice > matchcount)
    {
        printf("Invalid choice\n");
        return -1;
    }
    else
    {
        // Convert user's selection to actual contact index
        index = matchcontact[choice - 1];
    }

    // Return the index of the matched contact
    return index;
}


void listContacts(AddressBook *addressBook)
{
	//list all the contacts..
    printf("-----------------------------------------------------------------------------------------\n");
    printf("%-25s %-15s %-30s\n", "Name", "Phone", "Email");
    printf("-----------------------------------------------------------------------------------------\n");


    for(int i = 0; i < addressBook->contactCount; i++) 
    {
        printf("%-25s %-15s %-30s\n",
            addressBook->contacts[i].name,
            addressBook->contacts[i].phone,
            addressBook->contacts[i].email);
    }

    printf("-----------------------------------------------------------------------------------------\n");
    printf("Total Contacts : %d\n", addressBook->contactCount);
    printf("-----------------------------------------------------------------------------------------\n");


}

void initialize(AddressBook *addressBook)
{
    addressBook->contactCount = 0;
    loadContactsFromFile(addressBook);

    if (addressBook->contactCount == 0) 
    {
        populateAddressBook(addressBook);
    }
    // Load contacts from file during initialization (After files)
    loadContactsFromFile(addressBook);
}

void saveAndExit(AddressBook *addressBook)
{
    saveContactsToFile(addressBook); // Save contacts to file
    exit(EXIT_SUCCESS);              // Exit the program
}

/*
 *  Function Name : createContact
 *  Input :
 *      addressBook - Pointer to the AddressBook structure where the new
 *                    contact will be stored
 *  Output :
 *      Adds a new contact to the address book if validations pass
 *  Description :
 *      Prompts the user to enter name, phone number, and email for a new
 *      contact. Each field goes through its respective validation function.
 *      If any validation fails, the user is given an option to retry or exit.
 *      On successful validation of all fields, the new contact is stored in
 *      the addressBook and the contactCount is incremented.
 *      If storage is full (100 contacts), the function will exit without
 *      adding a new entry.
 */

void createContact(AddressBook *addressBook)
{
    /* Define the logic to create a Contacts */

    if(addressBook->contactCount == 100)
    {
        printf("Storage is Full\n");
        return;
    }

    char name[50];
    char phone[11];
    char email[50];

    // Name validation loop
    while (1)
    {
        printf("Enter Name: ");
        scanf("%s", name);

        if (ValidateContactName(name) == 0)
        {
            break;
        }
        int choice;
        printf("Press 1 continue, or 0 to exit: ");
        scanf("%d", &choice);

        if (choice == 0)
        {
            return; 
        }
    }

    // Phone validation loop
    while (1)
    {
        printf("Enter Phone Number: ");
        scanf("%s", phone);

        if (ValidateContactPhone(addressBook, phone, -1) == 0)
        {
            break;
        }
        int choice;
        printf("Press 1 continue, or 0 to exit: ");
        scanf("%d",&choice);

        if (choice == 0)
        {
            return; 
        }
    }

    // Email validation loop
    while (1)
    {
        printf("Enter Email: ");
        scanf("%s", email);

        if (ValidateContactEmail(addressBook, email, -1) == 0)
        {
            break;
        }
        int choice;
        printf("Press 1 continue, or 0 to exit: ");
        scanf("%d", &choice);

        if (choice == 0)
        {
            return; 
        }

    }

    // Save contact
    strcpy(addressBook->contacts[addressBook->contactCount].name, name);
    strcpy(addressBook->contacts[addressBook->contactCount].phone, phone);
    strcpy(addressBook->contacts[addressBook->contactCount].email, email);

    addressBook->contactCount++;

    printf("Contact saved successfully!\n");
}

/*
 *  Function Name : searchContact
 *
 *  Input :
 *      addressBook - Pointer to the AddressBook structure to search from
 *
 *  Output :
 *      Displays matching contacts on the screen
 *
 *  Description :
 *      Allows the user to search for a contact using either a name or
 *      a phone number. 
 *
 *      - If the input contains digits → phone search
 *      - If not → name search
 *
 *      It then compares the input with each stored contact and prints all
 *      matching results. If no contact matches the given input, it prints
 *      an appropriate message.
 */

void searchContact(AddressBook *addressBook)
{
    char search[50];
    
    // Get the input from the user safely
    printf("Enter Name or Phone number to search: ");
    fgets(search, sizeof(search), stdin);
    search[strcspn(search, "\n")] = '\0';

    // Check if the user just pressed Enter
    if(strlen(search) == 0)
    {
        printf("Invalid input. Search term cannot be empty.\n");
        return;
    }

    // Determine if the search query looks like a phone number (contains digits)
    int isPhoneSearch = 0;
    for(int i = 0; search[i] != '\0'; i++) 
    { 
        if(isdigit(search[i]))
        {
            isPhoneSearch = 1;
            break;
        }
    }

    // Array to temporarily keep track of the matches we find
    int matchedIndexes[MAX_CONTACTS];
    int matchCount = 0;

    // Perform the search loop
    for (int i = 0; i < addressBook->contactCount; i++)
    {
        if (isPhoneSearch)
        {
            // For phone numbers
            if (strcmp(addressBook->contacts[i].phone, search) == 0)
            {
                matchedIndexes[matchCount++] = i;
            }
        }
        else        
        {
            // For names
            if (strcmp(addressBook->contacts[i].name, search) == 0)
            {
                matchedIndexes[matchCount++] = i;
            }
        }
    }

    // If no matches were collected, print the fallback message
    if(matchCount == 0)
    {
        printf("\nNo Matching Contacts are Found\n");
        return;
    }

    printf("\n-----------------------------------------------------------------------------------------\n");
    printf("%-5s %-25s %-15s %-30s\n", "SI", "Name", "Phone", "Email");
    printf("-----------------------------------------------------------------------------------------\n");

    for (int i = 0; i < matchCount; i++)
    {
        int idx = matchedIndexes[i];
        printf("%-5d %-25s %-15s %-30s\n", 
               i + 1,
               addressBook->contacts[idx].name,
               addressBook->contacts[idx].phone,
               addressBook->contacts[idx].email);
    }

    printf("-----------------------------------------------------------------------------------------\n");
    printf("Matches Found: %d\n", matchCount);
    printf("-----------------------------------------------------------------------------------------\n");
}

/*
 * Function name: editContact
 * Input: addressBook - Pointer to the AddressBook structure
 * Output: Update the edited contact if the validation are pass
 * Description:
 *       Prompt the user to enter name or phone number to find a contact
 *       if the contact is found Prompts the user to enter name, phone number,
 *       and email. Each field goes through its respective validation function.
 *       If any validation fails, the user is given an option to retry or exit.
 *       On successful validation of all fields, the new contact is stored in
 *       the addressBook
 */

void editContact(AddressBook *addressBook)
{
    /* Define the logic for Editcontact */
    char edit[50];

    printf("Enter a Name or Phone number you want to edit: ");
    fgets(edit, sizeof(edit), stdin);
    edit[strcspn(edit, "\n")] = '\0';

    int index = FindContact(addressBook,edit,1);

    if(index == -1)
    {
        return;
    }

    char name[50];
    char phone[20];
    char email[50];

    while (1){
        printf("Enter Name: ");
        fgets(name, sizeof(name), stdin);
        name[strcspn(name, "\n")] = '\0';

        if (ValidateContactName(name) == 0)
        {
            break;
        }

        int choose;
        printf("Press 1 continue, or 0 to exit: ");
        scanf("%d", &choose);

        if (choose == 0)
        {
            return; 
        }
    }

    // Phone validation loop
    while (1)
    {
        printf("Enter new Phone or press Enter you don't want to edit the current Phone: ");
        fgets(phone, sizeof(phone), stdin);
        phone[strcspn(phone, "\n")] = '\0';

        if(strlen(phone) == 0)
        {
            strcpy(phone,addressBook->contacts[index].phone);
            break;
        }

        if (ValidateContactPhone(addressBook, phone, index) == 0)
        {
            break;
        }
        int choose;
        printf("Press 1 continue, or 0 to exit: ");
        scanf("%d", &choose);

        if (choose == 0)
        {
            return; 
        }
    }

    // Email validation loop
    while (1)
    {
        
        printf("Enter new Email or press Enter you don't want to edit the current mail: ");
        fgets(email, sizeof(email), stdin);
        email[strcspn(email, "\n")] = '\0'; 

        if(strlen(email) == 0)
        {
            strcpy(email,addressBook->contacts[index].email);   
            break;
        }
        
        if (ValidateContactEmail(addressBook, email, index) == 0)
        {
            break;
        }

        int choose;
        
        printf("Press 1 continue, or 0 to exit: ");
        scanf("%d", &choose);

        if (choose == 0)
        {
            return; 
        }

    }

    // Save contact
    strcpy(addressBook->contacts[index].name, name);
    strcpy(addressBook->contacts[index].phone, phone);
    strcpy(addressBook->contacts[index].email, email);

     printf("Contact updated successfully\n");

}

/*
 *  Function Name : deleteContact
 *  Input :
 *      addressBook - Pointer to the AddressBook structure containing contacts
 *  Output :
 *      Deletes a selected contact from the address book
 *  Description :
 *      Prompts the user to enter a name or phone number for deletion.
 *      The function then calls FindContact() (with delete mode) to search
 *      for matching contacts and allows the user to pick the correct entry
 *      if multiple matches are found.
 *
 *      Once a valid index is returned, the contact is removed.
 *
 *      If no matching contact is found or the user enters an invalid choice,
 *      the function exits without making changes.
 */


void deleteContact(AddressBook *addressBook)
{
    /* Define the logic for Editcontact */

    char delete[50];

    printf("Enter a Name or Phone number you want to delete: ");
    fgets(delete, sizeof(delete), stdin);
    delete[strcspn(delete, "\n")] = '\0';

    int index = FindContact(addressBook, delete, 0);

    if(index == -1)
    {
        return;
    }

    for(int i=index; i<addressBook->contactCount-1; i++)
    {
        addressBook->contacts[i] = addressBook->contacts[i + 1];
    }

    addressBook->contactCount--;

    printf("Contact deleted successfully\n");
}

