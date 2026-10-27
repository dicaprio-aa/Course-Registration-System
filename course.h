/*
 * ============================================================
 *  UKF COLLEGE OF ENGINEERING & TECHNOLOGY
 *  COURSE REGISTRATION SYSTEM
 * ------------------------------------------------------------
 *  File        : course.h
 *  Description : Header file containing all structure
 *                definitions, macro constants, global file
 *                names and function prototypes used across
 *                the project.
 *  Developed By: RISWANA S3 DS
 * ============================================================
 */

#ifndef COURSE_H
#define COURSE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <windows.h>
#include <conio.h>

/* ------------------------------------------------------------
 *  MACRO CONSTANTS
 * ------------------------------------------------------------ */
#define STUDENT_FILE        "students.dat"
#define FACULTY_FILE        "faculty.dat"
#define COURSE_FILE         "courses.dat"
#define REGISTRATION_FILE   "registrations.dat"

#define MAX_LEN_REG         20
#define MAX_LEN_NAME        50
#define MAX_LEN_DEPT        50
#define MAX_LEN_PHONE       15
#define MAX_LEN_EMAIL       50
#define MAX_LEN_PASS        20
#define MAX_LEN_CODE        10
#define MAX_LEN_FACID       20

#define ADMIN_USERNAME      "admin"
#define ADMIN_PASSWORD      "admin123"

#define TRUE  1
#define FALSE 0

/* ------------------------------------------------------------
 *  STRUCTURE DEFINITIONS
 * ------------------------------------------------------------ */

/* Student record structure */
typedef struct
{
    char regno[MAX_LEN_REG];
    char name[MAX_LEN_NAME];
    char dept[MAX_LEN_DEPT];
    int  semester;
    char phone[MAX_LEN_PHONE];
    char email[MAX_LEN_EMAIL];
    char password[MAX_LEN_PASS];
    int  isActive;               /* soft-delete / active flag */
} Student;

/* Faculty record structure */
typedef struct
{
    char facid[MAX_LEN_FACID];
    char name[MAX_LEN_NAME];
    char dept[MAX_LEN_DEPT];
    char password[MAX_LEN_PASS];
} Faculty;

/* Course record structure */
typedef struct
{
    char code[MAX_LEN_CODE];
    char name[MAX_LEN_NAME];
    int  semester;
    int  credits;
    char facid[MAX_LEN_FACID];   /* faculty id assigned to course */
    int  maxSeats;
    int  availSeats;
    int  isActive;               /* soft-delete flag */
} Course;

/* Registration record structure */
typedef struct
{
    char regno[MAX_LEN_REG];
    char code[MAX_LEN_CODE];
    char dateTime[30];
    int  isActive;               /* becomes FALSE when dropped */
} Registration;

/* ============================================================
 *  FUNCTION PROTOTYPES
 * ============================================================ */

/* ---------------- Utility / UI functions ---------------- */
void clearScreen(void);
void pauseScreen(void);
void printLine(char ch, int len);
void printCentered(const char *text, int width);
void getCurrentDateTimeStr(char *buffer);
void showWelcomeScreen(void);
void showMainHeader(const char *title);
void printSuccess(const char *msg);
void printError(const char *msg);
void printInfo(const char *msg);
void flushInputBuffer(void);
void getHiddenPassword(char *password, int maxLen);
void mainMenu(void);
void aboutUKF(void);

/* ---------------- Validation functions ---------------- */
int isValidSemester(int sem);
int isValidPhone(const char *phone);
int isValidEmail(const char *email);
int isValidPasswordFormat(const char *password);
int isDuplicateRegNo(const char *regno);
int isDuplicateFacultyId(const char *facid);
int isDuplicateCourseCode(const char *code);

/* ---------------- Student module functions ---------------- */
void studentPortal(void);
void studentRegister(void);
int  studentLogin(Student *s);
void studentDashboard(Student *s);
void viewProfile(Student s);
void viewAvailableCourses(void);
void registerCourseForStudent(Student s);
void dropCourseForStudent(Student s);
void myRegisteredCourses(Student s);
void totalCredits(Student s);
void changeStudentPassword(Student *s);

/* ---------------- Faculty module functions ---------------- */
void facultyPortal(void);
int  facultyLogin(Faculty *f);
void facultyDashboard(Faculty f);
void viewAssignedCourses(Faculty f);
void viewRegisteredStudentsForFaculty(Faculty f);

/* ---------------- Admin module functions ---------------- */
void adminPortal(void);
int  adminLogin(void);
void adminDashboard(void);
void addCourse(void);
void updateCourse(void);
void deleteCourse(void);
void viewCourses(void);
void addFaculty(void);
void viewFaculty(void);
void viewStudents(void);
void registrationReport(void);

/* ---------------- Registration helper functions ---------------- */
int  isAlreadyRegistered(const char *regno, const char *code);
int  countActiveRegistrationsForCourse(const char *code);
int  getCourseByCode(const char *code, Course *outCourse);
int  updateCourseRecord(Course c);
int  getFacultyById(const char *facid, Faculty *outFaculty);

#endif /* COURSE_H */
