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

// the student struct is defined here so it will not be seen outside of this c file
struct student {
	long phone_number;
	char ID[10];
	char first_name[15];
	char last_name[15];
	float final_grade;
	char temp[2]; // to avoid padding error
	float grades[NUMBER_OF_GRADES]; // grades only contain 2 midterm and 1 final exam
};

void add_student() {
	// ab+ read and append the end of binary file
	// if the file does not exist, it will create the file
	FILE * out_file = fopen("database.dat", "ab+");
	if (out_file == NULL) {
		fprintf(stderr, "could not open output file\n");
		fclose(out_file);
		return;
	}
	struct student stu;

	printf("ID: ");
	scanf("%s", stu.ID);
	
	// check if the student ID is already in the system or not
	if (check_record(stu.ID)) {
		printf("There is a student with this ID in the system\n");
		printf("Please try again\n");
		printf("ID: ");
		scanf("%s", stu.ID);
		if (check_record(stu.ID)) {
			printf("There is a student with this ID in the system\n");
			printf("Too many attempt\n");
			printf("Please try again later\n");
			return;
		}
	}

	printf("First name: ");
	scanf("%s", stu.first_name);
	printf("Last name: ");
	scanf("%s", stu.last_name);
	printf("Phone Number (No space or dashes): ");
	scanf("%ld", &stu.phone_number);

	printf("Would you like to add grades now? (Yes/No)  ");
	char temp[3];
	scanf("%s", temp);
	if (strcmp(temp,"Yes") == 0 || strcmp(temp,"YES") == 0 ||
		strcmp(temp,"yes") == 0) {
		
		printf("Midterm #1: ");
		scanf("%f", &stu.grades[1]);
				
		printf("Midterm #2: ");
		scanf("%f", &stu.grades[2]);
			
		printf("Final Exam: ");
		scanf("%f", &stu.grades[3]);	
	}
	
	// final grade is set to 0 to avoid undefined behavior when called by other method
	stu.final_grade = 0.0;
	
	//write the struct to the output file and close it
	fwrite(&stu, sizeof(struct student), BUFFER_LENGTH, out_file);
	sleep(2);
	printf("\nStudent added successfully\n\n");
	fclose(out_file);
	sleep(1);
	return;
}

void update_record() {
	// r+ mode is to update a binary file
	// the file MUST exist upon calling fopen in r+ mode
	FILE * out_file = fopen("database.dat", "r+"); 
	if (out_file == NULL) {
		fprintf(stderr, "could not open input file\n");
		fclose(out_file);
		return;
	}

	struct student stu;

	printf("Please enter student ID to update the record: ");
	char student_ID[10];
	scanf("%s", student_ID);

	// check if the student ID is already in the system or not
	if (check_record(stu.ID)) {
		printf("There is a student with this ID in the system\n");
		printf("Please try again\n");
		printf("ID: ");
		scanf("%s", stu.ID);
		if (check_record(stu.ID)) {
			printf("There is a student with this ID in the system\n");
			printf("Too many attempt\n");
			printf("Please try again later\n");
			return;
		}
	}

	// loop through the file till the end to match the input student ID
	while (1) { 
		fread(&stu, sizeof(struct student), BUFFER_LENGTH, out_file);
		if(feof(out_file)) {
      		break;
    	}

		if(strcmp(student_ID,stu.ID) == 0){
			int option;
			//giving user the option what to update
			printf("What information would you like to update\n");
			printf("1. Update Student First Name\n");
			printf("2. Update Student Last Name\n");
			printf("3. Update Phone Number\n\n");
			printf("Your Choice [1-3]: ");
			
			scanf("%d",&option);

			switch(option){
        		case 1:
        			printf("\nID: %s\n", stu.ID);
            		printf("First name: ");
					scanf("%s", stu.first_name);
					printf("\n\n");
					sleep(1);
            		break;
		        case 2:
		        	printf("\nID: %s\n", stu.ID);
		          	printf("Last name: ");
					scanf("%s", stu.last_name);
					printf("\n\n");
					sleep(1);
		            break;
		        case 3:
		        	printf("\nID: %s\n", stu.ID);
		            printf("Phone Number (No space or dashes): ");
					scanf("%ld", &stu.phone_number);
					printf("\n\n");
					sleep(1);
		            break;
		        default:
		            break;
		    }
		    // reference: https://fresh2refresh.com/c-programming/c-file-handling/fseek-seek_set-seek_cur-seek_end-functions-c/
		    // -sizeof() to go back to the beginning of this struct, not the beginning of the file
		    // SEEK_CUR is to set the current position for fwrite to know where to write data to the output file
		    fseek(out_file, -sizeof(struct student), SEEK_CUR);
		    fwrite(&stu, sizeof(struct student), BUFFER_LENGTH, out_file);
   			fclose(out_file);
            return;
        }
	}

	sleep(2);
	printf("\nStudent Not Found\n\n");
	fclose(out_file);
	return;
}

void update_grades() {
	FILE * out_file = fopen("database.dat", "r+");
	if (out_file == NULL) {
		fprintf(stderr, "could not open input file\n");
		fclose(out_file);
		return;
	}

	struct student stu;

	printf("Please enter student ID to update the grades: ");
	char student_ID[10];
	scanf("%s", student_ID);

	// check if the student ID is already in the system or not
	if (check_record(stu.ID)) {
		printf("There is a student with this ID in the system\n");
		printf("Please try again\n");
		printf("ID: ");
		scanf("%s", stu.ID);
		if (check_record(stu.ID)) {
			printf("There is a student with this ID in the system\n");
			printf("Too many attempt\n");
			printf("Please try again later\n");
			return;
		}
	}

	// loop through the file till the end to match the input student ID
	while (1) { 
		fread(&stu, sizeof(struct student), BUFFER_LENGTH, out_file);
		if(feof(out_file)) {
      		break;
    	}

		if(strcmp(student_ID,stu.ID) == 0){
			int option;
			// giving user the option to what to change
			// the calculation of final grade is automatic and cannot be change directly
			// once final grade is calculated, it is considered final
			printf("What grade would you like to update\n");
			printf("1. Update Midterm #1\n");
			printf("2. Update Midterm #2\n");
			printf("3. Update Final Exam\n");
			printf("4. Update All Grades\n");
			printf("5. Calculate Final Grade\n\n");
			printf("Your Choice [1-5]: ");
			
			scanf("%d",&option);
			
			switch(option){
        		case 1:
            		printf("\nID: %s\n", stu.ID);
            		printf("Midterm #1: ");
					scanf("%f", &stu.grades[option]);
					printf("\n\n");
					sleep(1);
            		break;
		        case 2:
		          	printf("\nID: %s\n", stu.ID);
		          	printf("Midterm #2: ");
					scanf("%f", &stu.grades[option]);
					printf("\n\n");
					sleep(1);
		            break;
		        case 3:
		            printf("\nID: %s\n", stu.ID);
		            printf("Final Exam: ");
					scanf("%f", &stu.grades[option]);
					printf("\n\n");
					sleep(1);
		            break;
		        case 4:
					printf("\nID: %s\n", stu.ID);
					printf("Midterm #1: ");
					scanf("%f", &stu.grades[1]);
					printf("Midterm #2: ");
					scanf("%f", &stu.grades[2]);
					printf("Final Exam: ");
					scanf("%f", &stu.grades[3]);
					printf("\n\n");
					sleep(1);
		            break;
		        case 5:
		           	printf("\nID: %s\n", stu.ID);
		           	float temp = stu.grades[1] * MIDTERM_WEIGHT/100;
		           	temp += stu.grades[2] * MIDTERM_WEIGHT/100;
		           	temp += stu.grades[3] * FINAL_WEIGHT/100;
		           	stu.final_grade = temp;
		           	printf("\n\n");
					sleep(1);
		            break;
		        default:
		            break;
		    }
		    
		    // reference: https://fresh2refresh.com/c-programming/c-file-handling/fseek-seek_set-seek_cur-seek_end-functions-c/
		    // fseek here is to set the file position for fwrite to write data
		    // without fseek, fwrite will not know where in the file to write data 
		    // and it will mess up with binary blocks in the binary database file
		    // the result is that it will render the file unusable
		    fseek(out_file, -sizeof(struct student), SEEK_CUR);
		    fwrite(&stu, sizeof(struct student), BUFFER_LENGTH, out_file);
   			fclose(out_file);
            return;
        }
	}

	sleep(2);
	printf("\nStudent Not Found\n\n");
	fclose(out_file);
	return;
}

void check_grades() {
	// "rb" mode will open the file in binary mode to read only without changing any data
	FILE * in_file = fopen("database.dat", "rb");
	if (in_file == NULL) {
		fprintf(stderr, "could not open input file\n");
		fclose(in_file);
		return;
	}

	struct student stu;

	printf("Please enter student ID to check: ");
	char student_ID[10];
	scanf("%s", student_ID);

	// loop through the file to match the student ID input by user
	while (1) { 
		fread(&stu, sizeof(struct student), BUFFER_LENGTH, in_file);
		if(feof(in_file)) {
      		break;
    	}

		if(strcmp(student_ID,stu.ID) == 0){
			for (int i = 1; i <= NUMBER_OF_GRADES; i++) {
				if (i == 1) {
					printf("Midterm #1: %.2f\n", stu.grades[i]);
				}
				if (i == 2) {
					printf("Midterm #2: %.2f\n", stu.grades[i]);
				}
				if (i == 3) {
					printf("Final: %.2f\n", stu.grades[i]);
				}
			}
			printf("\nFinal Grade: %.2f\n\n", stu.final_grade);

   			fclose(in_file);
            return;
        }
	}

	sleep(2);
	printf("Student Not Found\n\n");
	fclose(in_file);
	return;
}

void search_student() {
	// "rb" mode will open the file in binary mode to read only without changing any data
	FILE * in_file = fopen("database.dat", "rb");
	if (in_file == NULL) {
		fprintf(stderr, "could not open input file\n");
		fclose(in_file);
		return;
	}

	struct student stu;

	printf("Please enter student ID to search: ");
	char student_ID[10];
	scanf("%s", student_ID);

	// reference: https://www.reddit.com/r/C_Programming/comments/5vhish/how_to_fread_a_binary_file_into_an_array_of/
	while (1) { 
		fread(&stu, sizeof(struct student), BUFFER_LENGTH, in_file);
		if(feof(in_file)) {
      		break;
    	}

		if(strcmp(student_ID,stu.ID) == 0){
			printf("\nID: %s", stu.ID);
    		printf("\nFirst Name: %s", stu.first_name);
    		printf("\nLast Name: %s", stu.last_name);
    		printf("\nPhone Number: %ld", stu.phone_number);
    		printf("\nFinal Grade: %.2f\n\n", stu.final_grade);
   			
   			fclose(in_file);
            return;
        }
	}

	sleep(2);
	printf("\nStudent Not Found\n\n");
	fclose(in_file);
	return;
}

void list_students() {
	// "rb" mode will open the file in binary mode to read only without changing any data
	FILE * in_file = fopen("database.dat", "rb");
	if (in_file == NULL) {
		fprintf(stderr, "could not open input file\n");
		fclose(in_file);
		return;
	}

	struct student stu;

	// loop through the file to match the student ID input by user
	while (1) { 
		fread(&stu, sizeof(struct student), BUFFER_LENGTH, in_file);
		if(feof(in_file)) {
      		break;
    	}
		printf("\nID: %s", stu.ID);
    	printf("\nFirst Name: %s", stu.first_name);
    	printf("\nLast Name: %s", stu.last_name);
    	printf("\nPhone Number: %ld", stu.phone_number);
    	printf("\nMidterm #1: %.2f", stu.grades[1]);
    	printf("\nMidterm #2: %.2f", stu.grades[2]);
    	printf("\nFinal: %.2f", stu.grades[3]);
    	printf("\nFinal Grade: %.2f\n\n", stu.final_grade);
	}

	sleep(2);
	fclose(in_file);
	return;
}

// this is a private method
// it is not meant to be called by any method outside this c file
static bool check_record(char * student_ID) {
	FILE * in_file = fopen("database.dat", "rb");
	if (in_file == NULL) {
		fprintf(stderr, "could not open input file\n");
		fclose(in_file);
		return false;
	}

	struct student stu;

	// loop through the file to match the student ID input by user
	// when found, it will return true to method calling it
	while (1) { 
		fread(&stu, sizeof(struct student), BUFFER_LENGTH, in_file);
		if(feof(in_file)) {
      		break;
    	}	

		if(strcmp(student_ID,stu.ID) == 0){
            fclose(in_file);
            return true;
        }
	}

	fclose(in_file);
	return false;
}