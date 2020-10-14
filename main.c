/*
* Author: Tin Huynh
* Purpose: This is a simple program to maintain student records for one semester and one course
* Each student only has three grades recorded which are two midterm and one final
* 
* Developed on Ubuntu Budgie 19.10
* Not compatible with C89 because of stdbool.h library
* Version: 1.0
*/

#include "student_database.h"
#include "users.h"
#include <stdlib.h> 
#include <stdio.h>
#include <stdbool.h> 

void main_menu();

int main (int argc, char * argv[]) {

	main_menu();

	return 0;

}

void main_menu() {
	char user_name[20];
	char password[20];
	
	char * root = "root_override"; // default account to override as a fail-safe account
	char * root_pass = "rootpass"; // default account to override
	
	printf("\n******* Welcome to Student Record System *******\n");
	printf("\n");
	printf("Username: ");
	scanf("%s", user_name);

	printf("Password: ");
	scanf("%s", password);

	if (strcmp(user_name, root) == 0 ||
		strcmp(root_pass, password) == 0) {
		admin_functions();
		return;
	}

	int authentication;
	authentication = authenticate(user_name, password);
	printf("\n");

	switch(authentication){
        case 1:
            admin_functions();
            break;
        case 2:
          	teacher_functions();
            break;
        case 3:
            client_functions();
            break;
        default:
        	printf("Your username or password does not match\n\n");
            break;
    }
    return;
}
