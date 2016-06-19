/* joetest.c

   By Michael W. Maher
   Version 1.0 6/30/93
   
   Description: This program will scan the Unix OS for account names in search
   		of user accounts that have:
   		
   		- no password
   		- a password that is the same as the account name
   		- a password that is the same as the account name backward
   	
   		The name of each problem user account encountered is listed.
   		
   Returns:	The number of problem accounts encountered.		
   		
   Compatibility: ANSI C on Unix system
   
*/

/* include files */
#include<stdio.h>
#include<string.h>
#include<pwd.h>
#include<unistd.h>
#include"../projects/string2.h"
#include"../projects/string2.c"

/* function prototypes */
int main(int argc, char **argv);


int main(int argc, char **argv)
   {
   int    found = 0;
   struct passwd *pw;
   char *result;
    
   if (argc > 1)
     {
     printf("\njoetest.c by Michael W. Maher"
            "\nVersion 1.0: 6/29/93"
            "\nUSAGE: joetest"
            "\nDescription: Searches for Unix user accounts without a password,"
            "\n             a password that is the same as the account name"
            "\n             (these are often called 'joes') and a password that"
            "\n             is the account name backwards.\n");
     }
   while(pw = getpwent())
     {
     /* test for no password */
     if (pw->pw_passwd[0] == 0)
       {
       printf("%s has no password\n", pw->pw_name);
       found++;
       continue;
       }
     /* test for password that is a joe */
     result = crypt(pw->pw_name, pw->pw_passwd);
     if(!strcmp(result, pw->pw_passwd))
       {
       printf("%s is a joe\n", pw->pw_name);
       found++;
       continue;
       }
     /* test for a reverse joe - password is name spelled backward */
     result = crypt(str_rev(pw->pw_name), pw->pw_passwd);
     if(!strcmp(result, pw->pw_passwd))
       {
       printf("%s is a reverse joe\n", str_rev(pw->pw_name));
       found++;
       continue;
       }
     }
   return(found);
   }
