/*
* Author: Tin Huynh
* Purpose: This is a simple program to maintain student records for one semester and one course
* Each student only has three grades recorded which are two midterm and one final
* 
* Developed on Ubuntu Budgie 19.10
* Not compatible with C89 because of stdbool.h library
* Version: 1.0
*/

#ifndef _STU_DB_
    #define _STU_DB_
#include "users.h"
#include <inttypes.h>
#include <stdlib.h> 
#include <stdio.h>
#include <string.h>
#include <stdbool.h> 
#include <unistd.h>

#define BUFFER_LENGTH 1
#define NUMBER_OF_GRADES 3
#define MIDTERM_WEIGHT 30
#define FINAL_WEIGHT 40

void add_student();
void update_record();
void update_grades();
void check_grades();
void search_student();
void list_students();
static bool check_record(char * student_ID);


#endif