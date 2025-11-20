//In the name of Allah who is the most merciful
//comments are added by us for our own understanding.
#include <stdio.h>
#include <string.h>
//defining in the start so it isnt complex to use later on
#define MAX_PATIENTS 100
#define MAX_STAFF 50
#define MAX_DOCTORS 50
//struct will help us create blueprints for one time so we don't have to write it again and again
//kinda like OOPS but does not have all the functions of OOPS
struct Patient {
    int id;
    char name[30];
    int age;
    char disease[50];
    char department[30];
    float bill;
    int admitted;
};

struct Staff {
    int id;
    char name[30];
    char role[30];
    float salary;
};

struct Doctor {
    int id;
    char name[30];
    char department[30];
};

struct Patient patients[MAX_PATIENTS];
struct Staff staffList[MAX_STAFF];
struct Doctor doctorList[MAX_DOCTORS];

int patientCount=0;
int staffCount=0;
int doctorCount=0;

int login();
void adminMenu();
void doctorMenu();
void staffMenu();

void addPatient();
void viewPatients();
void searchPatient();
void dischargePatient();
void calculateBill();
void addStaff();
void viewStaff();

void doctorViewPatients();
void doctorSearchPatient();
void viewStaffSelf();
//login function
int login() {
    char username[20];
    char password[20];
    int role=0;

    while(role==0) {
        printf("\n==============================\n");
        printf("         LOGIN PORTAL        \n");
        printf("==============================\n");

        printf("Enter Username: ");
        scanf("%s",username);

        printf("Enter Password: ");
        scanf("%s",password);

        if(strcmp(username,"admin")==0 && strcmp(password,"123")==0) {
            printf("\nLogin Successful! Welcome Admin.\n");
            role=1;
        }
        else if(strcmp(username,"doctor")==0 && strcmp(password,"456")==0) {
            printf("\nLogin Successful! Welcome Doctor.\n");
            role=2;
        }
        else if(strcmp(username,"staff")==0 && strcmp(password,"789")==0) {
            printf("\nLogin Successful! Welcome Staff.\n");
            role=3;
        }
        else {
            printf("\nInvalid login! Please try again.\n");
        }
    }
    return role;
    //admin--123
    //doctor--456
    //staff--789
}
//if one logs in in the admin then will run this
void adminMenu() {
    int choice;

    do {
        printf("\n\n======= ADMIN MENU =======\n");
        printf("1. Add Patient\n");
        printf("2. View All Patients\n");
        printf("3. Search Patient\n");
        printf("4. Discharge Patient\n");
        printf("5. Calculate Bill\n");
        printf("6. Add Staff\n");
        printf("7. View Staff\n");
        printf("0. Logout\n");
        printf("Enter choice: ");
        scanf("%d",&choice);

        switch(choice) {
            case 1: addPatient(); break;
            case 2: viewPatients(); break;
            case 3: searchPatient(); break;
            case 4: dischargePatient(); break;
            case 5: calculateBill(); break;
            case 6: addStaff(); break;
            case 7: viewStaff(); break;
            case 0: printf("\nLogged out.\n"); break;
            default: printf("Invalid choice!\n");
        }

    } while(choice!=0);
}
//when we want to admit a new patient
void addPatient() {
    if(patientCount>=MAX_PATIENTS) {
        printf("Patient list full!\n");
        return;
    }

    struct Patient p;//p is the alias/object so we dont write patient everytime
    p.id=patientCount+1;
    p.bill=0;
    p.admitted=1;

    printf("\nEnter Patient Name: ");
    scanf("%s",p.name);
    printf("Enter Age: ");
    scanf("%d",&p.age);
    printf("Enter Disease: ");
    scanf("%s",p.disease);
    printf("Enter Department: ");
    scanf("%s",p.department);

    patients[patientCount]=p;
    patientCount++;

    printf("\nPatient Added Successfully! Assigned ID: %d\n",p.id);
}
//will help view the number of patients with their details
void viewPatients() {
    if(patientCount==0) {
        printf("\nNo patients found!\n");
        return;
    }

    printf("\n----- PATIENT LIST -----\n");
    for(int i=0;i<patientCount;i++) {
        printf("\nID: %d\nName: %s\nAge: %d\nDisease: %s\nDepartment: %s\nBill: %.2f\nStatus: %s\n",
            patients[i].id,patients[i].name,patients[i].age,patients[i].disease,
            patients[i].department,patients[i].bill,
            patients[i].admitted ? "Admitted" : "Discharged");
    }
}
//if any specifice patient's detail is needed then this will help
void searchPatient() {
    int id,found=0;
    printf("\nEnter Patient ID to search: ");
    scanf("%d",&id);

    for(int i=0;i<patientCount;i++) {
        if(patients[i].id==id) {
            printf("\nRecord Found!\n");
            printf("Name: %s\nAge: %d\nDisease: %s\nDepartment: %s\nBill: %.2f\nStatus: %s\n",
                patients[i].name,patients[i].age,patients[i].disease,
                patients[i].department,patients[i].bill,
                patients[i].admitted ? "Admitted" : "Discharged");
            found=1;
            break;
        }
    }
    if(!found) printf("\nPatient Not Found!\n");
}
//if we want to remove patient, this will run
void dischargePatient() {
    int id,found=0;
    printf("\nEnter Patient ID to discharge: ");
    scanf("%d",&id);

    for(int i=0;i<patientCount;i++) {
        if(patients[i].id==id) {
            patients[i].admitted=0;
            printf("\nPatient Discharged Successfully!\n");
            found=1;
            break;
        }
    }
    if(!found) printf("\nInvalid Patient ID!\n");
}
//this will help calculating the bill of the patient when he is discharged
void calculateBill() {
    int id;
    float room,test,medicine,fee;

    printf("\nEnter Patient ID: ");
    scanf("%d",&id);

    for(int i=0;i<patientCount;i++) {
        if(patients[i].id==id) {
            printf("\nEnter Room Charges: ");
            scanf("%f",&room);
            printf("Enter Lab Test Charges: ");
            scanf("%f",&test);
            printf("Enter Medicine Charges: ");
            scanf("%f",&medicine);
            printf("Enter Doctor Fee: ");
            scanf("%f",&fee);

            patients[i].bill=room+test+medicine+fee;
            printf("\nTotal Bill Updated Successfully! Final Bill = %.2f\n",patients[i].bill);
            return;
        }
    }
    printf("\nPatient Not Found!\n");
}
//if new staff has to be admitted, this will help do that
void addStaff() {
    if(staffCount>=MAX_STAFF) {
        printf("Staff list full!\n");
        return;
    }

    struct Staff s;
    s.id=staffCount+1;

    printf("\nEnter Staff Name: ");
    scanf("%s",s.name);
    printf("Enter Role: ");
    scanf("%s",s.role);
    printf("Enter Salary: ");
    scanf("%f",&s.salary);

    staffList[staffCount]=s;
    staffCount++;

    printf("\nStaff Added Successfully! Assigned ID: %d\n",s.id);
}
//this will show the list of all the staff members present in the hospital with their details
void viewStaff() {
    if(staffCount==0) {
        printf("\nNo staff found!\n");
        return;
    }

    printf("\n----- STAFF LIST -----\n");
    for(int i=0;i<staffCount;i++) {
        printf("\nID: %d\nName: %s\nRole: %s\nSalary: %.2f\n",
            staffList[i].id,staffList[i].name,staffList[i].role,staffList[i].salary);
    }
}
//this is the doctor's menu from login
void doctorMenu() {
    int choice;

    do {
        printf("\n\n======= DOCTOR MENU =======\n");
        printf("1. View All Patients\n");
        printf("2. Search Patient\n");
        printf("0. Logout\n");
        printf("Enter choice: ");
        scanf("%d",&choice);

        switch(choice) {
            case 1: doctorViewPatients(); break;
            case 2: doctorSearchPatient(); break;
            case 0: printf("\nLogged out.\n"); break;
            default: printf("Invalid choice!\n");
        }

    } while(choice!=0);
}
//same as previous view patients functions that will show all patients with details
void doctorViewPatients() {
    viewPatients();
}
//same as previous searc patients fuction that will allow to search individual patients
void doctorSearchPatient() {
    searchPatient();
}
//this is the staff's menu from login
void staffMenu() {
    int choice;

    do {
        printf("\n\n======= STAFF MENU =======\n");
        printf("1. View Staff Details\n");
        printf("0. Logout\n");
        printf("Enter choice: ");
        scanf("%d",&choice);

        switch(choice) {
            case 1: viewStaffSelf(); break;
            case 0: printf("\nLogged out.\n"); break;
            default: printf("Invalid choice!\n");
        }

    } while(choice!=0);
}
//view staff function from before to see all the current admitted staff
void viewStaffSelf() {
    viewStaff();
}
//main body
int main(){
    int role=login();

    if(role==1)
        adminMenu();
    else if(role==2)
        doctorMenu();
    else
        staffMenu();

    printf("\nThank You for using HMS created by Nehan Malik and Zainab Zehra!\n");
    return 0;
}

