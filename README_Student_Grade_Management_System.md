# Student Grade Management System

A menu-driven C project that stores student records using structures and an array.

## Features
- Add student records (roll number, name, and marks in five subjects)
- Calculate total marks, average, and grade automatically
- Display all student records
- Search for a student by roll number
- View the total number of students
- Validate duplicate roll numbers and marks outside 0–100

## Concepts used
- Structures
- Arrays
- Functions
- Loops and conditional statements
- String handling and input validation

## Grade scale
| Average | Grade |
|---|---|
| 90–100 | A+ |
| 80–89.99 | A |
| 70–79.99 | B |
| 60–69.99 | C |
| 50–59.99 | D |
| Below 50 | F |

## Compile and run
Using GCC:
```bash
gcc student_grade_management.c -o student_grade_management
./student_grade_management
```
On Windows with GCC:
```bash
gcc student_grade_management.c -o student_grade_management.exe
student_grade_management.exe
```

## Storage note
Records are stored in memory while the program is running. They are not retained after the program exits.

## Student details
- Name: Sonakshi priya
- UID: 26bcd10329
- Section: 4B
