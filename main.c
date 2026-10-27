/*
 * ============================================================
 *  UKF COLLEGE OF ENGINEERING & TECHNOLOGY
 *  COURSE REGISTRATION SYSTEM
 * ------------------------------------------------------------
 *  File        : main.c
 *  Description : Entry point of the application. Shows the
 *                animated welcome screen once and then hands
 *                control over to the main menu loop defined
 *                in course.c. Contains no business logic of
 *                its own - only the program entry flow.
 *  Developed By: RISWANA S3 DS
 *
 *  Compile (MinGW / GCC on Windows):
 *      gcc main.c course.c -o registration.exe
 *
 *  Run:
 *      registration.exe
 * ============================================================
 */

#include "course.h"

int main(void)
{
    /* Show the animated boot-up / welcome screen */
    showWelcomeScreen();

    /* Hand over control to the main menu loop */
    mainMenu();

    return 0;
}
