#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Function prototype
void student(); //View Student Portfolio
void admin(); //View Admin Portfolio
void addbook(); // Adding Book Function
void returnbook(); // Function for Return Book
void issue(); // Funtion for Issued Book
void view(); //Funtion for see all book list
void registr(); // Register Student New
void search(); // Search Book
void vieweee();
void viewcse();
void datadelet(); // Delete Data
void record();
void alldata(); // View Individual Issued Book
void viewissue(); // Funtion for Issued Book
void viewallissue(); // View all Issed Book
struct ST{ // Student Registration Structure
    char stdname[50];
    int stdid;
};
struct ISS{ // Issued Book Structure
    int id;
    char name[50];
    char bk[50];
    char isdate[50];
};
struct SI{ //Add Book Structure

    int id;
    char book[100];
    char author[100];
    char dept[20];
    char self[10];
    char date[40];
};
void viewallissue() { //Joto boi issue kora hoise shob boi er list ek sathe show korbe
    system("cls");
    struct ISS s;  // Use the correct structure name here
    FILE *fPtr;

    fPtr = fopen("issue_bin.dat", "rb"); //issue book er file open korbe
    if (fPtr == NULL) {
        printf("Error opening file for reading.\n");
        return;
    }

    while (fread(&s, sizeof(struct ISS), 1, fPtr) == 1) { //File shuru theke shesh porjonto read korbe
        if (s.id != 0) {  // Assuming '0' represents an empty record
            printf("\nID=%d, Name=%s, Book=%s, Date=%s\n", s.id, s.name, s.bk, s.isdate);
        }
    }

    fclose(fPtr);
}

void viewissue(){ //View Issued book e click korar por option show er jonno ei funtion input dewa hoise
    system("cls");
    int n;
    printf("\n  1| Show All Issued Book ");
    printf("\n  2| Show Individual Data ");
    printf("\n");
    scanf("%d",&n);
    if(n==2) alldata(); // Function call korbe
    if(n==1) viewallissue(); //Function Call korbe
}
int main() {
    struct ST newStudent;
    FILE *fle;
    fle = fopen("student_bin.dat", "rb");
    int n;
    char id[10];
    char pass[] = "weq123Admin"; // Admin Fixed Password
    char user[20];

    // Beautiful Interface Start
    printf("\n");
    printf("=================================== NOOB GLADIATORS ===================================\n");
    printf("               WELCOME TO LIBRARY MANAGEMENT SYSTEM\n");
    printf("======================================================================================\n");
    printf("                            Choose an option:\n");
    printf("                            1) Admin\n");
    printf("                            2) Student\n");
    printf("                            3) Student Registration\n");
    printf("======================================================================================\n");

    printf("\nPlease enter your choice: ");
    scanf("%d", &n);

    if (n == 2) {
        printf("\nEnter Student ID: ");
        scanf("%s", id);

        int found = 0;

        // Loop until the end of the file or until the Student is found
        while (fread(&newStudent, sizeof(struct ST), 1, fle) == 1) {
            // Check if the student ID matches
            if (newStudent.stdid == atoi(id)) {
                student();
                found = 1; // Flag indicating that the student is found
                break;
            }
        }

        fclose(fle);

        if (found == 0) {
            printf("\nStudent not found! Please check the ID and try again.\n");
        }
    } else if (n == 1) {
        printf("\nEnter Admin Password: ");
        scanf("%s", user);

        if (strcmp(user, pass) == 0) { // Admin password check
            admin();
        } else {
            printf("\nIncorrect Password! Access Denied.\n");
        }
    } else if (n == 3) {
        registr();
    } else {
        printf("\nInvalid option selected! Please restart and select a valid option.\n");
    }

    return 0;
}
void student(){ //Student Portofolio Home page
    int dec;
    while(1){
    printf("\n");
    printf("  (1) View Book \n");
    printf("  (2) Issued Book \n");
    printf("  (3) Exit \n");
    scanf("%d",&dec);
    if(dec==1) view();
    else if(dec==2) record();
    else if(dec==3) break;
    }

}
void registr() { //Resister New Struct Funtion
    struct ST new = {0, ""};
    FILE *newstd;

    newstd = fopen("student_bin.dat", "rb+");

    if (newstd == NULL) {
        newstd = fopen("student_bin.dat", "wb+");
        for (int i = 0; i < 1000; i++) { // Corrected the comment
            fwrite(&new, sizeof(struct ST), 1, newstd);
        }
    }

    printf("\nEnter Student ID : ");
    scanf("%d", &new.stdid);
    printf("\nEnter Student Name : ");
    scanf("%s", new.stdname);

    fseek(newstd, (new.stdid % 1000 - 1) * sizeof(struct ST), SEEK_SET);
    fwrite(&new, sizeof(struct ST), 1, newstd);
    printf("\nRegistration Successful!\n");


    fclose(newstd);
}


void admin() { //Admin Home page Function
    int n;
system("cls");
//This code uses preprocessor directives to include different commands based on the operating system. Let's break it down://
    while(1){
        printf("\n");
    printf("  1 | Add Book\n");
    printf("  2 | View Book List\n");
    printf("  3 | Return Book\n");
    printf("  4 | Issue Book\n");
    printf("  5 | Search Book\n");
    printf("  6 | View record of issued books\n");
    printf("  7 | Delete record from Book List\n");
    printf("  8 | Exit\n");
    scanf("%d",&n);
    if(n==8) break;
    else if(n==1) addbook();
    else if(n==2) view();
    else if(n==3) returnbook();
    else if(n==4) issue();
    else if(n==7) datadelet();
    else if(n==6) viewissue();
    else if(n==5) search();
    }
}
void alldata(){ // View  Issued Books for indibidual Student
 system("cls");
    int nm;
    struct ISS man;
    FILE *isst;

    isst = fopen("issue_bin.dat", "rb");
    if (isst == NULL) {
        printf("Error opening file for reading.\n");
        return;
    }

    printf("Enter Student ID : ");
    scanf("%d", &nm); //jei student er issue book info dekhbo tar ID

    int found = 0;

    // Loop until the end of the file or until the book is found
    while (!feof(isst)) {
        fread(&man, sizeof(struct ISS), 1, isst); //File shuru theke shesh porjonto read korbe

        // Check if the book name matches
        if (man.id==nm) {//Given ID r sathe file er id match check korbe
                printf("Book Found !!!!\n");
             printf("==================================================================================================================\n");
    printf("| %-10s | %-30s | %-20s | %-15s \n", "Student ID", "Student Name", "Book Name", "Issued Date");
    printf("==================================================================================================================\n");
    printf("| %-10d | %-30s | %-20s | %-15s \n",
                   man.id, man.name, man.bk, man.isdate);//Output show korbe
                   found = 1;
            break;
        }

        }


    fclose(isst);

    if (found==0) {
        printf("Book not found!\n");
    }
}


void record() { //View Issued Book list by Individual
   system("cls");
    int nm;
    struct ISS man;
    FILE *isst;

    isst = fopen("issue_bin.dat", "rb");
    if (isst == NULL) {
        printf("Error opening file for reading.\n");
        return;
    }

    printf("Enter Student ID : ");
    scanf("%d", &nm);//Jei student er jonno issue book dkehbo oi student er id

    int found = 0;

    // Loop until the end of the file or until the book is found
    while (!feof(isst)) {// File shuru theke shesh mean kore
        fread(&man, sizeof(struct ISS), 1, isst);//File shob read korbe

        // Check if the book name matches
        if (man.id==nm) {//ID Match hoise kina seta check korbe
                printf("Book Found !!!!\n");
             printf("==================================================================================================================\n");
    printf("| %-10s | %-30s | %-20s | %-15s \n", "Student ID", "Student Name", "Book Name", "Issued Date");
    printf("==================================================================================================================\n");
    printf("| %-10d | %-30s | %-20s | %-15s \n",
                   man.id, man.name, man.bk, man.isdate);
                   found = 1;
            break;
        }

        }


    fclose(isst);

    if (found==0) {
        printf("Book not found!\n");
    }
}


void returnbook() { //Return Issued Book Function
    system("cls");
    struct ISS book;
    FILE *dlt;
    int n;

    printf("Enter Student ID: ");
    scanf("%d", &n);//Jei student er jonno boi return korbe oi student er ID

    dlt = fopen("issue_bin.dat", "rb+");
    if (dlt == NULL) {
        printf("Error opening file for reading.\n");
        return;
    }

    int found = 0;

    // Loop until the end of the file
    while (fread(&book, sizeof(struct ISS), 1, dlt) == 1) {//File shuru theke shesh porjonto read korbe
        // Check if the student ID matches
        if (book.id == n) { //ID er sathe file er id match korbe
            fseek(dlt, -sizeof(struct ISS), SEEK_CUR);
            struct ISS emptyBook = {0, "", "", "", ""}; //oi file er data shob Zero kore dibe i mean delete kore dibe
            fwrite(&emptyBook, sizeof(struct ISS), 1, dlt);//Than oita file e write kore dibe Zero data
            found = 1;
            break;
        }
    }

    fclose(dlt);

    if (found == 0) {
        printf("Student not issued any book!\n");
    } else {
        printf("Return Successful!\n");
    }
}

void search() { //Search Book from library- Function
    system("cls");
    char nm[100];
    struct SI book;
    FILE *src;

    src = fopen("book_bin.dat", "rb");
    if (src == NULL) {
        printf("Error opening file for reading.\n");
        return;
    }

    printf("Enter Book Name : ");
    scanf("%s", nm);//Jei boi er info dekhte chai oi boi er name type er jonno/input

    int found = 0;

    // Loop until the end of the file or until the book is found
    while (!feof(src)) {//File shuru theke shesh mean kore
        fread(&book, sizeof(struct SI), 1, src);//Shuru theke shesh porjonto shob file read korbe

        // Check if the book name matches
        if (strcmp(book.book, nm) == 0) {//Boi er name match korbe read korar por
                printf("Book Found !!!!\n");
             printf("==================================================================================================================\n");
    printf("| %-10s | %-30s | %-20s | %-15s | %-10s | %-15s |\n", "Book ID", "Book Name", "Author", "Department", "Self No", "Date");
    printf("==================================================================================================================\n");
    printf("| %-10d | %-30s | %-20s | %-15s | %-10s | %-15s |\n",
                   book.id, book.book, book.author, book.dept, book.self, book.date);//Match hoye gele Output show korbe
            break;
        }

        }


    fclose(src);

    if (found==0) {
        printf("Book not found!\n");
    }
}


void view(){ //View Book List Funtion Main Page
   system("cls");
    int ans;
    printf(" 1] Electrical and Electronic Engineering\n");
    printf(" 2] Computer Science and Engineering\n");
    printf(" 3] Bachelor of Business Administration\n");
    printf(" 4] Civil Engineering\n");
    printf(" 5] Pharmacy\n");
    scanf("%d",&ans);
    if(ans==1)vieweee();
    else if(ans==2)viewcse();
    else if(ans==3)viewbba();
    else if(ans==4)viewce();
    else if(ans==5)viewpharm();
}

void addbook() { //Add Book Page Funtion
    struct SI book = {0, "", "", ""};
    FILE *fptr;

    if (fptr == NULL) {
        fptr = fopen("book_bin.dat", "wb+");
        //Assume Varsity has 5 department and 400 book can store each department//
        for (int i = 0; i < 2000; i++) {
            fwrite(&book, sizeof(struct SI), 1, fptr);
        }
    }
    if(fptr != NULL){
            system("cls");
        fptr=fopen("book_bin.dat","rb+");
        printf("\nEnter Book ID :");
        scanf("%d",&book.id);
        printf("\nEnter Book Name :");
        scanf("%s",book.book);
        printf("\nEnter Author Name :");
        scanf("%s",book.author);
        printf("\nEnter Department :");
        scanf("%s",book.dept);
        printf("\nEnter Self No :");
        scanf("%s",book.self);
        printf("\nEnter Date :");
        scanf("%s",book.date);
        fseek(fptr,(book.id-1)*sizeof(struct SI),SEEK_SET);
        fwrite(&book,sizeof(struct SI),1,fptr);//Class basic ei code shob
    }

    fclose(fptr);
}
void vieweee() { //View EEE Book List from "view"  main funtion
    system("cls");
    FILE *viu;
    struct SI book;
    viu = fopen("book_bin.dat", "rb");

    printf("====================================================================================================\n");
    printf("| %-10s | %-30s | %-20s | %-15s | %-10s | %-15s |\n", "Book ID", "Book Name", "Author", "Department", "Self No", "Date");
    printf("====================================================================================================\n");

    int startRecord = 0;  // Adjust the start record as needed
    int endRecord = 399;    // Adjust the end record as needed

    // Move the file pointer to the start record
    fseek(viu, (startRecord - 1) * sizeof(struct SI), SEEK_SET);

    // Read and display records within the specified range
    for (int i = startRecord; i <= endRecord && fread(&book, sizeof(struct SI), 1, viu) == 1; i++) {
            //ei loop 0-399 array porjonto Data read korbe ei for loop etai mean kore
        if (book.id != 0) {
            printf("| %-10d | %-30s | %-20s | %-15s | %-10s | %-15s |\n",
                   book.id, book.book, book.author, book.dept, book.self, book.date);
        }
    }

    printf("====================================================================================================\n");

    fclose(viu);
}
void viewcse() { //View CSE Book List from "view"  main funtion
    system("cls");
    FILE *viu;
    struct SI book;
    viu = fopen("book_bin.dat", "rb");

    printf("====================================================================================================\n");
    printf("| %-10s | %-30s | %-20s | %-15s | %-10s | %-15s |\n", "Book ID", "Book Name", "Author", "Department", "Self No", "Date");
    printf("====================================================================================================\n");

    int startRecord = 400;  // Adjust the start record as needed
    int endRecord = 799;    // Adjust the end record as needed

    // Move the file pointer to the start record
    fseek(viu, (startRecord - 1) * sizeof(struct SI), SEEK_SET);

    // Read and display records within the specified range
    for (int i = startRecord; i <= endRecord && fread(&book, sizeof(struct SI), 1, viu) == 1; i++) {
        if (book.id != 0) {
            printf("| %-10d | %-30s | %-20s | %-15s | %-10s | %-15s |\n",
                   book.id, book.book, book.author, book.dept, book.self, book.date);
        }
    }

    printf("====================================================================================================\n");

    fclose(viu);
}
void viewpharm() { //View Pharmacy Book List from "view"  main funtion
    system("cls");
    FILE *viu;
    struct SI book;
    viu = fopen("book_bin.dat", "rb");

    printf("====================================================================================================\n");
    printf("| %-10s | %-30s | %-20s | %-15s | %-10s | %-15s |\n", "Book ID", "Book Name", "Author", "Department", "Self No", "Date");
    printf("====================================================================================================\n");

    int startRecord = 1600;  // Adjust the start record as needed
    int endRecord = 2000;    // Adjust the end record as needed

    // Move the file pointer to the start record
    fseek(viu, (startRecord - 1) * sizeof(struct SI), SEEK_SET);

    // Read and display records within the specified range
    for (int i = startRecord; i <= endRecord && fread(&book, sizeof(struct SI), 1, viu) == 1; i++) {
        if (book.id != 0) {
            printf("| %-10d | %-30s | %-20s | %-15s | %-10s | %-15s |\n",
                   book.id, book.book, book.author, book.dept, book.self, book.date);
        }
    }

    printf("====================================================================================================\n");

    fclose(viu);
}
void viewce() { //View Civil Engineering Book List from "view"  main funtion
    system("cls");
    FILE *viu;
    struct SI book;
    viu = fopen("book_bin.dat", "rb");

    printf("====================================================================================================\n");
    printf("| %-10s | %-30s | %-20s | %-15s | %-10s | %-15s |\n", "Book ID", "Book Name", "Author", "Department", "Self No", "Date");
    printf("====================================================================================================\n");

    int startRecord = 1200;  // Adjust the start record as needed
    int endRecord = 1599;    // Adjust the end record as needed

    // Move the file pointer to the start record
    fseek(viu, (startRecord - 1) * sizeof(struct SI), SEEK_SET);

    // Read and display records within the specified range
    for (int i = startRecord; i <= endRecord && fread(&book, sizeof(struct SI), 1, viu) == 1; i++) {
        if (book.id != 0) {
            printf("| %-10d | %-30s | %-20s | %-15s | %-10s | %-15s |\n",
                   book.id, book.book, book.author, book.dept, book.self, book.date);
        }
    }

    printf("====================================================================================================\n");

    fclose(viu);
}
void viewbba() { //View BBA Book List from "view"  main funtion
    system("cls");
    FILE *viu;
    struct SI book;
    viu = fopen("book_bin.dat", "rb");

    printf("====================================================================================================\n");
    printf("| %-10s | %-30s | %-20s | %-15s | %-10s | %-15s |\n", "Book ID", "Book Name", "Author", "Department", "Self No", "Date");
    printf("====================================================================================================\n");

    int startRecord = 800;  // Adjust the start record as needed
    int endRecord = 1199;    // Adjust the end record as needed

    // Move the file pointer to the start record
    fseek(viu, (startRecord - 1) * sizeof(struct SI), SEEK_SET);

    // Read and display records within the specified range
    for (int i = startRecord; i <= endRecord && fread(&book, sizeof(struct SI), 1, viu) == 1; i++) {
        if (book.id != 0) {
            printf("| %-10d | %-30s | %-20s | %-15s | %-10s | %-15s |\n",
                   book.id, book.book, book.author, book.dept, book.self, book.date);
        }
    }

    printf("====================================================================================================\n");

    fclose(viu);
}
void datadelet(){ //Delete Book information from library system Funtion
    system("cls");
    char nm[100];
    struct SI book;
    FILE *dlt;

    dlt = fopen("book_bin.dat", "rb+");
    if (dlt == NULL) {
        printf("Error opening file for reading.\n");
        return;
    }

    printf("Enter Book Name : ");
    scanf("%s", nm);

    int found = 0;

    // Loop until the end of the file or until the book is found
    while (!feof(dlt)) {
        fread(&book, sizeof(struct SI), 1, dlt);

        // Check if the book name matches
        if (strcmp(book.book, nm) == 0) {
               fseek(dlt, -sizeof(struct SI), SEEK_CUR);
               struct SI book={0,"", "" , "" ,"",""};
               fwrite(&book,sizeof(struct SI),1,dlt);
                   found = 1;
            break;
        }

        }


    fclose(dlt);

    if (found==0) {
        printf("Issued Book not found!\n");
    }
    else{
        printf("Book Data Remove Succesfully!!!!!");
    }
}

void issue() { //Issue Book Function ,Page
    system("cls");
    char nm[100];
    struct SI book;
    struct ISS isbook;
    FILE *src;

    src = fopen("book_bin.dat", "rb");
    if (src == NULL) {
        printf("Error opening file for reading.\n");
        return;
    }

    printf("Enter Book Name : ");
    scanf("%s", nm);

    int found = 0;

    // Loop until the end of the file or until the book is found
    while (!feof(src)) {
        fread(&book, sizeof(struct SI), 1, src);

        // Check if the book name matches
        if (strcmp(book.book, nm) == 0) {
            // issue book file
            struct ISS isbook = {0, "", "", "", ""};
            FILE *fptr;

            fptr = fopen("issue_bin.dat", "rb+");
            if (fptr == NULL) {
                fptr = fopen("issue_bin.dat", "wb+");
                // do it for 2000 student
                for (int i = 0; i < 2000; i++) {
                    fwrite(&isbook, sizeof(struct ISS), 1, fptr);
                }
            }
            if (fptr != NULL) {
                system("cls");
                fptr = fopen("issue_bin.dat", "rb+");
                printf("\nEnter Student ID :");
                scanf("%d", &isbook.id);
                printf("\nEnter Student Name :");
                scanf("%s", isbook.name);
                printf("\nEnter Book Name :");
                scanf("%s", isbook.bk);
                printf("\nIssue Date :");
                scanf("%s", isbook.isdate);
                fseek(fptr, ((isbook.id%1000) - 1) * sizeof(struct ISS), SEEK_SET);
                fwrite(&isbook, sizeof(struct ISS), 1, fptr);
            }

            fclose(fptr);

            found = 1;
            break;
        }
    }

    fclose(src);

    if (found == 0) {
        printf("Book not found!\n");
    }
}
