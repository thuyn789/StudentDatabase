/*
* Author: Tin Huynh
* Purpose: This is a simple program to maintain student records for one semester and one course
* Each student only has three grades recorded which are two midterm and one final
* 
* Developed on Ubuntu Budgie 19.10
* Not compatible with C89 because of stdbool.h library
* Version: 1.0
*/

#include "users.h"

struct account {
    char user_name[20];
    char password[20];
    int type;
};

int authenticate(char * user_name, char * password) {
    FILE * in_file = fopen("user_database.dat", "rb");
    if (in_file == NULL) {
        fprintf(stderr, "could not open input file\n");
        fclose(in_file);
        return -1;
    }

    struct account acc;
    int authentication = -2;

    while (1) { 
        fread(&acc, sizeof(struct account), BUFFER_LENGTH, in_file);
        if(feof(in_file)) {
            break;
        }   

        if(strcmp(user_name,acc.user_name) == 0 && strcmp(password,acc.password) == 0){
            authentication = acc.type;
        }
    }
    fclose(in_file);
    printf("\n");

    return authentication;
}

void add_user() {
    // ab+ read and append the end of binary file
    // if the file does not exist, it will create the file
    FILE * out_file = fopen("user_database.dat", "ab+");
    if (out_file == NULL) {
        fprintf(stderr, "could not open output file\n");
        fclose(out_file);
        return;
    }
    struct account acc;

    printf("Username: ");
    scanf("%s", acc.user_name);
    
    // check if the username is already in the system or not
    if (check_user(acc.user_name)) {
        printf("This username is used\n");
        printf("Please try again\n\n");
        printf("Username: ");
        scanf("%s", acc.user_name);
        if (check_user(acc.user_name)) {
            printf("This username is used\n");
            printf("Too many attempt\n");
            printf("Please try again later\n\n");
            return;
        }
    }
    
    printf("Password: ");
    scanf("%s", acc.password);

    printf("Account type [1-3]: ");
    scanf("%d", &acc.type);

    fwrite(&acc, sizeof(struct account), BUFFER_LENGTH, out_file);
    sleep(2);
    printf("User added successfully\n");
    printf("\n");

    fclose(out_file);

    return;
}

static bool check_user(char * username) {
    FILE * in_file = fopen("user_database.dat", "rb");
    if (in_file == NULL) {
        fprintf(stderr, "could not open input file\n");
        fclose(in_file);
        return false;
    }
    struct account acc;

    while (1) { 
        fread(&acc, sizeof(struct account), BUFFER_LENGTH, in_file);
        if(feof(in_file)) {
            break;
        }   

        if(strcmp(username,acc.user_name) == 0){
            fclose(in_file);
            return true;
        }
    }
    fclose(in_file);
    return false;
}

void admin_functions() {
	bool done = false;
	while (!done) {
		int option = 0;
		printf("******* Welcome to Student Record System *******\n");
		printf("    (Choose one of the following options)\n");
		printf("\n");
		printf("1. Add Student\n");
		printf("2. Update Student Information\n");
		printf("3. Update Grades\n");
		printf("4. Check Grades\n");
		printf("5. Search Student\n");
		printf("6. List All Students\n");
        printf("7. ADD USER\n");
		printf("8. Exit\n");
		printf("\n");

		printf("Your Choice [1-8]: ");

		scanf("%d",&option);
        printf("\n");
		switch(option){
            case 1:
                add_student(); 
                break;
            case 2:
            	update_record();
                break;
            case 3:
                update_grades();
                break;
            case 4:
            	check_grades();
                break;
            case 5:
                search_student();
                break;
            case 6:
            	list_students();
            	break; 
            case 7:
                add_user();
                break;
            case 8:
                done = true;
                break;
            default:
                break;
        }
	}
}

void teacher_functions() {
    bool done = false;
    while (!done) {
        int option = 0;
        printf("******* Welcome to Student Record System *******\n");
        printf("    (Choose one of the following options)\n");
        printf("\n");

        printf("1. Update Grades\n");
        printf("2. Check Grades\n");
        printf("3. Search Student\n");
        printf("4. List All Students\n");
        printf("5. Exit\n");
        printf("\n");

        printf("Your Choice [1-5]: ");
        
        scanf("%d",&option);
        printf("\n");
        switch(option){
            case 1:
                update_grades();
                break;
            case 2:
                check_grades();
                break;
            case 3:
                search_student(); 
                break;
            case 4:
                list_students();
                break; 
            case 5:
                done = true; 
                break;
            default:
                break;
        }
    }
}

void client_functions() {
    bool done = false;
    while (!done) {
        int option = 0;
        printf("******* Welcome to Student Record System *******\n");
        printf("    (Choose one of the following options)\n");
        printf("\n");

        printf("1. Check Grades\n");
        printf("2. Search Student\n");
        printf("3. Exit\n");
        printf("\n");

        printf("Your Choice [1-3]: ");

        scanf("%d",&option);
        printf("\n");
        switch(option){
            case 1:
                check_grades();
                break;
            case 2:
                search_student();
                break;
            case 3:
                done = true;
                break;
            default:
                break;
        }
    }
}
