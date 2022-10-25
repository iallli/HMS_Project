#include <stdio.h>
#include <conio.h> 
#include <stdlib.h>
#include <string.h> 


/*
Functions Declaration.
*/
void clrscr()
{
    system("cls()");
}
void menu();
void pat();
void emp();
void inv();


/*
Structures.
*/
struct address
{
    int house_no;
    char street[40];
    char city[40];
    char province[40];
};
struct patient
{
    char registration_no[10];
    char patient_n[40];
    char guardian_n[40];
    char gender;
    char blood_group[3];
    int age;
    struct address patient_addr;
    char phone_n[10];
    char disease[60];
    char doctor_n[40];
    char history[200];
    char date[10];
    char treatment[40];
    char presc_med[40];
};
struct staff
{
    char patient_n[40];
    char guardian_n[40];
    int age;
    char blood_group[3];
    char gender;
    char uid[10];
    struct address b;
    char phone_n[10];
    double salary;
    char desig[40];
};
struct inventory
{
    int sno;
    char name[30];
    char dop[20];
    int qnty;
    float price;
    float amount;
};

/*
Functions Defination.
*/
void menu()
{
    char choice; // get choice from the user in char variable

    printf("\n\t\t*************************************************");
    printf("\n\t\t  *** WELCOME TO HOSPITAL MANAGEMENT SYSTEM ***");
    printf("\n\t\t*************************************************");
    printf("\n\n");
    printf("\t\t1.PATIENT");
    printf("\n\t\t2.STAFF");
    printf("\n\t\t3.INVENTORY");
    printf("\n\t\t0.EXIT");
    printf("\n\n\t\tEnter your choice: ");

    fflush(stdin);     // resolve the skipping problem of scanf() and cleans the input buffer before taking next input.
    choice = getche(); // getche is used to take a single character input from the user and display on screen.

    switch (choice)
    {
    case '1':
        pat();
        break;
    case '2':
        emp();
        break;
    case '3':
        inv();
        break;
    case '0':
        exit(1);
    default:
        printf("\n\n\t\tYou have made wrong choice. Lets start again.");
    }
}

void pat()
{

    FILE *fp, *ft; // 'fp' is used for 'pat.txt' and 'ft' is used for 'temp.txt'
    struct patient p;

    char ch, another, z;     // get choice of user in 'ch': get new choice of user to add,modify,search,list,delete in 'another':get choice of user to enter the histroy if patient have any in 'z'.
    char reg[20], pname[40]; // creates a temporary variable  'reg' to check either THIS REGISTRATION NUMBER ALREADY EXISTS or not: 'pname' is used to search the pname through the file.
    int i = 0;               // acts like flag to check the registration no of a patient

    long int recsize;            // calculates the size of the record to be used in file-operations.
    fp = fopen("pat.txt", "r+"); // Use fopen(FileName, "r+") to open an existing file for reading or writing/updating.
    if (fp == NULL)
    {
        fp = fopen("pat.txt", "w+"); // Use fopen(FileName, "w+") to create a new file for the purpose of writing/updating or reading (if there's a file by this name before this call, it will be overwritten and all data from it will be lost).
        if (fp == NULL)
        {
            puts("\nSorry!! Cannot open file"); // The puts function in C is used to write a line or string to the output stream.
            exit(1);
        }
    }
    recsize = sizeof(p); // This is the size in bytes of each element to be written
    while (1)
    {
        clrscr();
        printf("\n\n\t\t\tPATIENT");
        printf("\n\t\t1.Enter a New Entry");
        printf("\n\t\t2.Modify Existing");
        printf("\n\t\t3.Search an Entry");
        printf("\n\t\t4.Listing of records");
        printf("\n\t\t5.Delete an Entry");
        printf("\n\t\t6.Main Menu");
        printf("\n\n\t\tEnter your choice here: ");

        fflush(stdin);
        ch = getche();
        switch (ch)
        {
        case '1':
            clrscr();
            // set file position to the end of the file.
            fseek(fp, 0, SEEK_END); //'0' is the offset which specifies the no of positions to be moved, 'seek_end' means end of the file.
            another = 'Y';
            while (another == 'Y' || another == 'y')
            {
            w:
                printf("\n\n\nEnter Registration Number: ");
                scanf("%s", reg);
                rewind(fp);                            // set file pointer to the begining of the file.
                while (fread(&p, recsize, 1, fp) == 1) // fread( & structure_variable, size of (structure variable), no of records, file pointer);
                {
                    if (strcmp(p.registration_no, reg) == 0)
                    {
                        i = 1;
                        printf("\n\t\tTHIS REGISTRATION NUMBER ALREADY EXISTS. ENTER ANOTHER ONE");
                        goto w;
                    }
                }
                if (i == 0 || fread(&p, recsize, 1, fp) == 0)
                {
                    fseek(fp, 0, SEEK_END);
                    strcpy(p.registration_no, reg);
                    fflush(stdin);
                    printf("\nEnter the name of the patient: ");
                    gets(p.patient_n);
                    printf("\nEnter the name of the Guardian: ");
                    gets(p.guardian_n);
                    printf("\nEnter the gender of the patient(M.male or F.female): ");
                    scanf("%c", &p.gender);
                    fflush(stdin);
                    printf("\nEnter the Blood group of the patient: ");
                    scanf("%s", p.blood_group);
                    fflush(stdin);
                    printf("\nEnter the age of the patient: ");
                    scanf("%d", &p.age);
                    printf("\nEnter the address of the patient:\n");
                    printf("\n\tEnter the house number: ");
                    scanf("%d", &p.patient_addr.house_no);
                    fflush(stdin);
                    printf("\n\tEnter the street/colony: ");
                    scanf("%s", p.patient_addr.street);
                    printf("\n\tEnter the city: ");
                    scanf("%s", p.patient_addr.city);
                    printf("\n\tEnter the province: ");
                    scanf("%s", p.patient_addr.province);
                    printf("\nEnter the phone number of the patient: ");
                    scanf("%s", p.phone_n);
                    fflush(stdin);
                    printf("\nEnter the Disease or problem for which he/she wants treatment: ");
                    gets(p.disease);
                    printf("\nEnter the name of the Doctor to which he/she being referred: ");
                    gets(p.doctor_n);
                    printf("\nEnter the history, if any, related to treatment of the patient(If yes then write 'Y' if NO then write 'N'): ");
                    scanf("%c", &z);
                    if (z == 'N' || z == 'n')
                    {
                        fwrite(&p, recsize, 1, fp);
                        goto out;
                    }
                    else
                    {
                        fflush(stdin);
                        printf("\nHistory:");
                        gets(p.history);
                        fflush(stdin);
                        printf("\nEnter the date of treatment:");
                        scanf("%s", p.date);
                        printf("\nTreatment Given:");
                        scanf("%s", p.treatment);
                        printf("\nMedicine Prescribed:");
                        scanf("%s", p.presc_med);
                    }
                    fwrite(&p, recsize, 1, fp);
                out:
                    printf("\n----------------------------------------------------");
                    printf("\nWant to add entry of the another Patient(Y/N): ");
                    fflush(stdin);
                    another = getche();
                }
            }
            break;
        
  
        case '2':
            clrscr();
            another = 'Y';
            while (another == 'Y' || another == 'y')
            {
                printf("\nEnter the Registration number of the patient to modify: ");
                scanf("%s", reg);
                rewind(fp);

                while (fread(&p, recsize, 1, fp) == 1)
                {
                    if (strcmp(p.registration_no, reg) == 0)
                    {
                        fflush(stdin);
                        printf("\nEnter the new name of the patient: ");
                        gets(p.patient_n);
                        printf("\nEnter the new name of the Guardian: ");
                        gets(p.guardian_n);
                        printf("\nEnter the new Blood group of the patient: ");
                        scanf("%s", p.blood_group);
                        printf("\nEnter the new age of the patient: ");
                        scanf("%d", &p.age);
                        printf("\nEnter the new address of the patient:\n");
                        printf("\n\tEnter the house number: ");
                        scanf("%d", &p.patient_addr.house_no);
                        fflush(stdin);
                        printf("\n\tEnter the street: ");
                        scanf("%s", p.patient_addr.street);
                        printf("\n\tEnter the city: ");
                        scanf("%s", p.patient_addr.city);
                        printf("\n\tEnter the province: ");
                        scanf("%s", p.patient_addr.province);
                        printf("\nEnter the new phone number of the patient: ");
                        scanf("%s", p.phone_n);
                        fflush(stdin);
                        printf("enter the date of treatment given: ");
                        gets(p.date);
                        printf("\nEnter the detail of treatment given: ");
                        gets(p.treatment);
                        printf("\nEnter the medicines prescribed: ");
                        gets(p.presc_med);
                        fseek(fp, -recsize, SEEK_CUR);
                        fwrite(&p, recsize, 1, fp);
                        break;
                    }
                    else
                    printf("Does Not Exit.");
                }

                printf("\n----------------------------------------------------");
                printf("\nModify another Record(Y/N): ");
                fflush(stdin);
                another = getche();
            }
            break;
        case '3':
            clrscr();
            another = 'Y';

            while (another == 'Y' || another == 'y')
            {
                printf("\nEnter name to search: ");
                gets(pname);
                rewind(fp);
                while (fread(&p, recsize, 1, fp) == 1)
                {
                    if (strcmp(p.patient_n, pname) == 0)
                    {
                        printf("\nRegistration Number of the Patient : ");
                        puts(p.registration_no);
                        printf("\nName of the Patient : ");
                        puts(p.patient_n);
                        printf("\nName of the Guardian : ");
                        puts(p.guardian_n);
                        printf("\nAge : %d", p.age);
                        printf("\nGender : %c", p.gender);
                        printf("\nBlood group: %s", p.blood_group);
                        printf("\nAddress  : %d,%s,%s,%s", p.patient_addr.house_no, p.patient_addr.street, p.patient_addr.city, p.patient_addr.province);
                        printf("\nphone number : +91-%s", p.phone_n);
                        printf("\nDisease : %s", p.disease);
                        printf("\nEarlier History : ");
                        puts(p.history);
                        printf("\nDetails of treatment given and medicine prescribed:");
                        printf("\nDATE\t\tTREATMENT GIVEN\t\tMEDICINE PRESCRIBED\n");
                        printf("%s\t\t %s\t\t %s\n", p.date, p.treatment, p.presc_med);
                        printf("\nName of the Doctor : ");
                        puts(p.doctor_n);
                    }
                }
                printf("\n----------------------------------------------------");
                printf("\nSearch another Entry(Y/N): ");
                fflush(stdin);
                another = getche();
            }
            break;
        case '4':
            clrscr();
            rewind(fp);

            while (fread(&p, recsize, 1, fp) == 1)
            {
                printf("\nRegistration Number of the Patient : ");
                puts(p.registration_no);
                printf("\nName of the Patient : ");
                puts(p.patient_n);
                printf("\nName of the Guardian : ");
                puts(p.guardian_n);
                printf("\nAge : %d", p.age);
                printf("\nGender : %c", p.gender);
                printf("\nBlood group: %s", p.blood_group);
                printf("\nAddress  : %d,%s,%s,%s", p.patient_addr.house_no, p.patient_addr.street, p.patient_addr.city, p.patient_addr.province);
                printf("\nphone number : +91-%s", p.phone_n);
                printf("\nDisease : %s", p.disease);
                printf("\nEarlier History : ");
                puts(p.history);
                printf("\nDetails of treatment given and medicine prescribed:");
                printf("\nDATE\t\t TREATMENT GIVEN\t\t\t MEDICINE PRESCRIBED\n");
                printf("%s\t\t %s\t\t %s\n", p.date, p.treatment, p.presc_med);
                printf("\nName of the Doctor : ");
                puts(p.doctor_n);
                printf("\n----------------------------------------------------\n");
            }
            getch();
            break;
        case '5':
            clrscr();
            another = 'Y';

            while (another == 'Y' || another == 'y')
            {
                printf("\nEnter the Registration number of the Patient to be deleted: ");
                scanf("%s", reg);
                ft = fopen("temp.txt", "w+");
                rewind(fp);
                while (fread(&p, recsize, 1, fp) == 1)
                {
                    if (strcmp(p.registration_no, reg) != 0)
                        fwrite(&p, recsize, 1, ft);
                    else
                        printf("\nThe Record has been Deleted Successfully.");
                }
                fclose(fp);
                fclose(ft);
                remove("pat.txt");
                rename("temp.txt", "pat.txt");
                fp = fopen("pat.txt", "r+");
                printf("\nDelete another record?(Y/N): ");
                fflush(stdin);
                another = getche();
            }
            break;
        
        case '6':
        {
            fclose(fp);
            clrscr();

            menu();
        }
        break;
        }
    }
}

void emp()
{
    struct staff s;

    FILE *fs, *fx;

    char more, c;
    char id[20], s_patient_n[40];

    int iF = 0;
    long int recsize1;

    fs = fopen("emp.txt", "r+");
    if (fs == NULL)
    {
        fs = fopen("emp.txt", "w+");
        if (fs == NULL)
        {
            puts("\nSorry!! Cannot open file");
            exit(1);
        }
    }
    recsize1 = sizeof(s);
    while (1)
    {
        clrscr();
        printf("\n\t\t\tEMPLOYEE");
        printf("\n\t\t1.Add an Entry");
        printf("\n\t\t2.Modify Existing One");
        printf("\n\t\t3.Search an Entry");
        printf("\n\t\t4.Listing of all records");
        printf("\n\t\t5.Delete an Entry");
        printf("\n\t\t6.Main Menu");
        printf("\n\n\t\tEnter your choice here: ");
        fflush(stdin);
        c = getche();
        switch (c)
        {
        case '1':
            clrscr();
            fseek(fs, 0, SEEK_END);
            more = 'Y';
            while (more == 'Y' || more == 'y')
            {
            u:
                printf("\n\n\nEnter the UID of the Employee: ");
                scanf("%s", id);
                rewind(fs);
                while (fread(&s, recsize1, 1, fs) == 1)
                {
                    if (strcmp(s.uid, id) == 0)
                    {
                        iF = 1;
                        printf("\n\t\tTHIS UID ALREADY EXISTS. ENTER ANOTHER ONE");
                        goto u;
                    }
                }
                if (iF == 0 || fread(&s, recsize1, 1, fs) == 0)
                {
                    fseek(fs, 0, SEEK_END);
                    strcpy(s.uid, id);
                    fflush(stdin);
                    printf("\nEnter the name of the Employee: ");
                    gets(s.patient_n);
                    printf("\nEnter the name of the Guardian: ");
                    gets(s.guardian_n);
                    printf("\nEnter the gender of the patient(M.male or F.female): ");
                    scanf("%c", &s.gender);
                    printf("\nEnter the Blood group of the Employee: ");
                    scanf("%s", s.blood_group);
                    printf("\nEnter the age of the Employee: ");
                    scanf("%d", &s.age);
                    printf("\nEnter the Salary of the Employee: ");
                    scanf("%lf", &s.salary);
                    fflush(stdin);
                    printf("\nEnter the address of the Employee:\n");
                    printf("\n\tEnter the house number: ");
                    scanf("%d", &s.b.house_no);
                    fflush(stdin);
                    printf("\n\tEnter the street/colony: ");
                    scanf("%s", s.b.street);
                    fflush(stdin);

                    printf("\n\tEnter the city: ");
                    scanf("%s", s.b.city);
                    fflush(stdin);

                    printf("\n\tEnter the state: ");
                    scanf("%s", s.b.province);
                    fflush(stdin);

                    printf("\nEnter the phone number of the Employee: ");
                    scanf("%s", s.phone_n);
                    fflush(stdin);
                    printf("\nEnter the Designation: ");
                    gets(s.desig);

                    fwrite(&s, recsize1, 1, fs);
                    
                    printf("\n----------------------------------------------------");
                    printf("\nWant to add entry of the another Employee(Y/N): ");
                    fflush(stdin);
                    more = getche();
                }
            }
            break;
        
        
        
        
        
        case '2':
            clrscr();
            more = 'Y';
            while (more == 'Y' || more == 'y')
            {
                printf("\nEnter the UID of the patient to modify: ");
                scanf("%s", id);
                rewind(fs);
                while (fread(&s, recsize1, 1, fs) == 1)
                {
                    if (strcmp(s.uid, id) == 0)
                    {
                        fflush(stdin);
                        printf("\nEnter the new name of the Employee: ");
                        gets(s.patient_n);
                        printf("\nEnter the new name of the Guardian: ");
                        gets(s.guardian_n);
                        printf("\nEnter the new Blood group of the Employee: ");
                        scanf("%s", s.blood_group);
                        printf("\nEnter the new age of the Employee: ");
                        scanf("%d", &s.age);
                        fflush(stdin);
                        printf("\nEnter the new Salary of the Employee: ");
                        scanf("%lf", &s.salary);
                        fflush(stdin);
                        printf("\nEnter the new address of the Employee:\n");
                        printf("\n\tEnter the house number: ");
                        scanf("%d", &s.b.house_no);
                        fflush(stdin);
                        printf("\n\tEnter the street/colony: ");
                        scanf("%s", s.b.street);
                        fflush(stdin);
                        printf("\n\tEnter the city: ");
                        scanf("%s", s.b.city);
                        fflush(stdin);
                        printf("\n\tEnter the state: ");
                        scanf("%s", s.b.province);
                        fflush(stdin);
                        printf("\nEnter the new phone number of the Employee: ");
                        scanf("%s", s.phone_n);
                        fflush(stdin);
                        fseek(fs, -recsize1, SEEK_CUR);
                        fwrite(&s, recsize1, 1, fs);
                        break;
                    }
                }
                printf("\n----------------------------------------------------");
                printf("\nModify another Record(Y/N): ");
                fflush(stdin);
                more = getche();
            }
            break; // check
        
        case '3':
            clrscr();
            more = 'Y';
            while (more == 'Y' || more == 'y')
            {
                printf("\nEnter name to search: ");
                gets(s_patient_n);
                rewind(fs);
                while (fread(&s, recsize1, 1, fs) == 1)
                {
                    if (strcmp(s.patient_n, s_patient_n) == 0)
                    {
                        printf("\nUID of the Employee : ");
                        puts(s.uid);
                        printf("\nName of the Employee : ");
                        puts(s.patient_n);
                        printf("\nName of the Guardian : ");
                        puts(s.guardian_n);
                        printf("\nAge : %d", s.age);
                        printf("\nSalary: %lf", s.salary);
                        printf("\nGender : %c", s.gender);
                        printf("\nBlood group: %s", s.blood_group);
                        printf("\nAddress  : %d,%s,%s,%s", s.b.house_no, s.b.street, s.b.city, s.b.province);
                        printf("\nphone number : +91-%s", s.phone_n);
                        printf("\nDesignation : %s", s.desig);
                    }
                }
                printf("\n----------------------------------------------------");
                printf("\nSearch another Entry(Y/N): ");
                fflush(stdin);
                more = getche();
            }
            break; // check
        
        case '4':         
            clrscr();
            rewind(fs);
            while (fread(&s, recsize1, 1, fs) == 1)
            {
                printf("\nUID of the Employee : ");
                puts(s.uid);
                printf("\nName of the Employee : ");
                puts(s.patient_n);
                printf("\nName of the Guardian : ");
                puts(s.guardian_n);
                printf("\nAge : %d", s.age);
                printf("\nSalary: %lf", s.salary);
                printf("\nGender : %c", s.gender);
                printf("\nBlood group: %s", s.blood_group);
                printf("\nAddress  : %d,%s,%s,%s", s.b.house_no, s.b.street, s.b.city, s.b.province);
                printf("\nphone number : +91-%s", s.phone_n);
                printf("\nDesignation : %s", s.desig);
                printf("\n----------------------------------------------------\n");
            }
            getch();
            break;
        
        
        case '5':
            clrscr();
            more = 'Y';
            while (more == 'Y' || more == 'y')
            {
                printf("\nEnter the UID of the Employee to be deleted: ");
                scanf("%s", id);
                fx = fopen("tem.txt", "w+");
                rewind(fs);
                while (fread(&s, recsize1, 1, fs) == 1)
                {
                    if (strcmp(s.uid, id) != 0)
                    {
                        fwrite(&s, recsize1, 1, fx);
                    }
                    else
                        printf("\nThe Record has been Deleted Successfully.");
                }
                fclose(fs);
                fclose(fx);
                remove("emp.txt");
                rename("tem.txt", "emp.txt");
                fs = fopen("emp.txt", "r+");
                printf("\nDelete another record?(Y/N): ");
                fflush(stdin);
                more = getche();
            } // check
        
    
        case '6':
        {
            fclose(fs);
            clrscr();
            menu();
        }
        break;
        }
    }
}

void inv()
{
    FILE *fi, *fy;
    char a, m;
    char i_name[40];
    int iF = 0, j = 1;
    long int recsize2;
    struct inventory v;
    fi = fopen("inv.txt", "rb+");
    if (fi == NULL)
    {
        fi = fopen("inv.txt", "wb+");
        if (fi == NULL)
        {
            puts("\nSorry!! Cannot open file");
            exit(1);
        }
    }
    recsize2 = sizeof(v);
    while (1)
    {
        clrscr();
        printf("\n\t\t\tINVENTORY");
        printf("\n\t\t1.Add an Entry for Item");
        printf("\n\t\t2.Modify Existing Entry");
        printf("\n\t\t3.Search an Entry");
        printf("\n\t\t4.Listing of all Entries");
        printf("\n\t\t5.Delete an Entry");
        printf("\n\t\t6.Main Menu");
        printf("\n\n\t\tEnter your choice here: ");
        fflush(stdin);
        m = getche();
        switch (m)
        {
        case '1':
            clrscr();
            fseek(fi, 0, SEEK_END);
            a = 'Y';
            while (a == 'Y' || a == 'y')
            {
            x:
                printf("\n\n\nEnter the Name of the Item: ");
                scanf("%s", i_name);
                rewind(fi);
                while (fread(&v, recsize2, 1, fi) == 1)
                {
                    if (strcmp(v.name, i_name) == 0)
                    {
                        iF = 1;
                        printf("\n\t\tTHIS ITEM ALREADY EXISTS. ENTER ANOTHER ONE");
                        goto x;
                    }
                }
                if (iF == 0 || fread(&v, recsize2, 1, fi) == 0)
                {
                    fseek(fi, 0, SEEK_END);
                    strcpy(v.name, i_name);
                    fflush(stdin);
                    printf("\nEnter the Date of purchase: ");
                    scanf("%s", v.dop);
                    fflush(stdin);
                    printf("\nEnter the Quantity of the Item: ");
                    scanf("%d", &v.qnty);
                    fflush(stdin);
                    printf("\nEnter the price of One Item: ");
                    scanf("%f", &v.price);
                    fflush(stdin);
                    v.amount = v.qnty * v.price;
                    printf("\nThe amount of %d %s is = %f", v.qnty, v.name, v.amount);
                    fwrite(&v, recsize2, 1, fi);
                    printf("\n----------------------------------------------------");
                    printf("\nWant to add entry of the another Item(Y/N): ");
                    fflush(stdin);
                    a = getche();
                }
            }
            break;
        case '2':
            clrscr();
            a = 'Y';
            while (a == 'Y' || a == 'y')
            {
                printf("\nEnter the name of the item to modify: ");
                scanf("%s", i_name);
                rewind(fi);
                while (fread(&v, recsize2, 1, fi) == 1)
                {
                    if (strcmp(v.name, i_name) == 0)
                    {
                        fflush(stdin);
                        printf("\nEnter the new name of the Item: ");
                        gets(v.name);
                        printf("\nEnter the new Date of purchase: ");
                        scanf("%s", v.dop);
                        fflush(stdin);
                        printf("\nEnter the new Quantity of the Item: ");
                        scanf("%d", &v.qnty);
                        fflush(stdin);
                        printf("\nEnter the new price of One Item: ");
                        scanf("%f", &v.price);
                        fflush(stdin);
                        v.amount = v.qnty * v.price;
                        printf("\nThe new amount of %d %s is = %f", v.qnty, v.name, v.amount);
                        fseek(fi, -recsize2, SEEK_CUR);
                        fwrite(&v, recsize2, 1, fi);
                        break;
                    }
                }
                printf("\n----------------------------------------------------");
                printf("\nModify another Record(Y/N): ");
                fflush(stdin);
                a = getche();
            }
            break;
        case '3':
            clrscr();
            a = 'Y';
            while (a == 'Y' || a == 'y')
            {
                printf("\nEnter name of item to search: ");
                gets(i_name);
                rewind(fi);
                while (fread(&v, recsize2, 1, fi) == 1)
                {
                    if (strcmp(v.name, i_name) == 0)
                    {
                        printf("\nThe Name of the Item: ");
                        puts(v.name);
                        printf("\nEnter the Date of purchase: %s", v.dop);
                        printf("\nQuantity of the Item: %d", v.qnty);
                        printf("\nPrice of One Item: %f", v.price);
                        v.amount = v.qnty * v.price;
                        printf("\nThe amount of %d %s is = %f", v.qnty, v.name, v.amount);
                    }
                }
                printf("\n----------------------------------------------------");
                printf("\nSearch another Entry(Y/N): ");
                fflush(stdin);
                a = getche();
            }
            break; // check
        case '4':
            clrscr();
            printf("S.No.\t ITEM\t DOP\t QUANTITY\tPRICE\t\t AMOUNT\n");
            printf("-----------------------------------------------------------------------------\n");
            rewind(fi);
            while (fread(&v, recsize2, 1, fi) == 1)
            {
                printf("%d\t %s\t %s\t %d\t\t Rs.%f\t Rs.%f\n", j, v.name, v.dop, v.qnty, v.price, v.amount);
                j++;
            }
            getch();
            break;
        case '5':
            clrscr();
            a = 'Y';
            while (a == 'Y' || a == 'y')
            {
                printf("\nEnter the name of the Item to be deleted: ");
                scanf("%s", i_name);
                fy = fopen("temporary.txt", "wb+");
                rewind(fi);
                while (fread(&v, recsize2, 1, fi) == 1)
                {
                    if (strcmp(v.name, i_name) != 0)
                        fwrite(&v, recsize2, 1, fy);
                    else
                        printf("\nThe Record has been Deleted Successfully.");
                }
                fclose(fi);
                fclose(fy);
                remove("inv.txt");
                rename("temporary.txt", "inv.txt");
                fi = fopen("inv.txt", "rb+");
                printf("\nDelete another record?(Y/N): ");
                fflush(stdin);
                a = getche();
            }
        case '6':
        {
            fclose(fi);
            clrscr();
            menu();
        }
        break;
        }
    }
}



/*
Main Function.
*/
int main()
{
    menu();
}
