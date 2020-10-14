/*
* Author: Tin Huynh
* Purpose: This is a simple program to maintain student records for one semester and one course
* Each student only has three grades recorded which are two midterm and one final
* 
* Developed on Ubuntu Budgie 19.10
* Not compatible with C89 because of stdbool.h library
* Version: 1.0
*/

#ifndef _USERS_
    #define _USERS_
#include "student_database.h"
#include <stdlib.h> 
#include <stdio.h>
#include <stdbool.h> 

#define BUFFER_LENGTH 1

int authenticate(char * user_name, char * password);
void add_user();
static bool check_user(char * username);
void admin_functions();
void teacher_functions();
void client_functions();

#endif