/******************************************************************************/
/* User Level #define Macros                                                  */
/******************************************************************************/

/* TODO Application specific user parameters used in user.c may go here */

/******************************************************************************/
/* User Function Prototypes                                                   */
/******************************************************************************/

/* TODO User level functions prototypes (i.e. InitApp) go here */
//#define _DEBUG

#ifndef USER_H
#define USER_H
void InitApp(void);         /* I/O and Peripheral Initialization */

void intToString( int val, char *buf, int size );
#endif