# StudentDatabase

********Student_Database*********
The student database is preloaded with some students below

---Student 1---
ID: 001
First name: John
Last name: Doe
Phone number: 123
Midterm #1: 95
Midterm #2: 90
Final Exam: 96

---Student 2---
ID: 002
First name: Sophia
Last name: Amazon
Phone number: 112233
Midterm #1: 85
Midterm #2: 87
Final Exam: 92

********User_Database************
There are three types of account who can access the student database.  Each type of account will have a test account for testing purposes
0. Root: this is the default account which is created as a fail-safe account
	ID: root_override
	Pass: rootpass
1. Admin: will have all the privileges and access to all the records and functions
	ID: admin
	Pass: password
2. Teacher: will have less privileges compared to Admin accounts
	ID: teacher01
	Pass: gsu001
3. Client: this type of account is for parents and students. They will only have access to their own record with their student ID and nothing else.
	ID: client01
	Pass: student
