/********************************************************************
*   Group:A2
*   Team:08
*   Date: 26-07-2025
*   Assignment-1B
*
*   Name: Partha Roy ,      Roll-302411001004 
*   Name: Bikram Sarkar ,   Roll-302411001008
*   Name: Bikram Dutta,     Roll-002311001071
*   
*
*Output:-
*
*   === Environment Variable Manager ===
*   -> Press 1 to show an environment variable
*   -> Press 2 to update/set an environment variable
*   -> Press 0 to exit
*   Enter your choice: 1
*   Enter the name of the environment variable: HOME
*   Value of 'HOME': /home/usr/student/ug/yr23/be23L04
*
*   === Environment Variable Manager ===
*   -> Press 1 to show an environment variable
*   -> Press 2 to update/set an environment variable
*   -> Press 0 to exit
*   Enter your choice: 1
*   Enter the name of the environment variable: HOST
*   Environment variable 'HOST' not found.

*   === Environment Variable Manager ===
*   -> Press 1 to show an environment variable
*   -> Press 2 to update/set an environment variable
*   -> Press 0 to exit
*   Enter your choice: ARCH
*   Enter the name of the environment variable: Environment variable 'ARCH' not found.

*   === Environment Variable Manager ===
*   -> Press 1 to show an environment variable
*   -> Press 2 to update/set an environment variable
*   -> Press 0 to exit
*   Enter your choice: DISPLAY
*   Enter the name of the environment variable: Environment variable 'DISPLAY' not found.

*   === Environment Variable Manager ===
*   -> Press 1 to show an environment variable
*   -> Press 2 to update/set an environment variable
*   -> Press 0 to exit
*   Enter your choice: PRINTER
*   Enter the name of the environment variable: Environment variable 'PRINTER' not found.

*   === Environment Variable Manager ===
*   -> Press 1 to show an environment variable
*   -> Press 2 to update/set an environment variable
*   -> Press 0 to exit
*   Enter your choice: PATH
*   Enter the name of the environment variable: Value of 'PATH': /usr/lib64/qt-3.3/bin:/usr/local/bin:/usr/bin:/usr/local/sbin:/usr/sbin:/home/usr/student/ug/yr23/be23L04/.local/
bin:/home/usr/student/ug/yr23/be23L04/bin

*   === Environment Variable Manager ===
*   -> Press 1 to show an environment variable
*   -> Press 2 to update/set an environment variable
*   -> Press 0 to exit
*   Enter your choice: 2
*   Enter the name of the environment variable to set: OS_LAB
*   Enter the path to assign to 'OS_LAB': /home/usr/student/ug/yr23/be23L04/OS_LAB/
*   Enter overwrite flag (1 to overwrite, 0 to skip if exists): 1
*   Environment variable 'OS_LAB' set to '/home/usr/student/ug/yr23/be23L04/OS_LAB/' successfully.

*   === Environment Variable Manager ===
*   -> Press 1 to show an environment variable
*   -> Press 2 to update/set an environment variable
*   -> Press 0 to exit
*   Enter your choice: 1
*   Enter the name of the environment variable: OS_LAB
*   Value of 'OS_LAB': /home/usr/student/ug/yr23/be23L04/OS_LAB/

*   === Environment Variable Manager ===
*   -> Press 1 to show an environment variable
*   -> Press 2 to update/set an environment variable
*   -> Press 0 to exit
*   Enter your choice: 2
*   Enter the name of the environment variable to set: MY_HOME_DIR
*   Enter the path to assign to 'MY_HOME_DIR': /home/usr/student/ug/yr23/be23L04
*   Enter overwrite flag (1 to overwrite, 0 to skip if exists): 1
*   Environment variable 'MY_HOME_DIR' set to '/home/usr/student/ug/yr23/be23L04' successfully.

*   === Environment Variable Manager ===
*   -> Press 1 to show an environment variable
*   -> Press 2 to update/set an environment variable
*   -> Press 0 to exit
*   Enter your choice: 1
*   Enter the name of the environment variable: MY_HOME_DIR
*   Value of 'MY_HOME_DIR': /home/usr/student/ug/yr23/be23L04

*   === Environment Variable Manager ===
*   -> Press 1 to show an environment variable
*   -> Press 2 to update/set an environment variable
*   -> Press 0 to exit
*   Enter your choice: 0

*********************************************************************/

#include <stdio.h>
#include <stdlib.h>

int main() {
    // Infinite loop to run the bin until we want to exit
    while (1) {
        printf("\n=== Environment Variable Manager ===\n");
        printf("-> Press 1 to show an environment variable\n");
        printf("-> Press 2 to update/set an environment variable\n");
        printf("-> Press 0 to exit\n");
        printf("Enter your choice: ");

        int option;
        scanf("%d", &option);

        switch (option) {
            case 1: {
                // getenv() call
                char env[256];
                printf("Enter the name of the environment variable: ");
                scanf("%s", env);
                char* result = getenv(env);
                if (result != NULL) {
                    printf("Value of '%s': %s\n", env, result);
                } else {
                    printf("Environment variable '%s' not found.\n", env);
                }
                break;
            }

            case 2: {
                //setenv() call
                char var[256];
                char path[256];
                int val;

                printf("Enter the name of the environment variable to set: ");
                scanf("%s", var);
                printf("Enter the path to assign to '%s': ", var);
                scanf("%s", path);
                printf("Enter overwrite flag (1 to overwrite, 0 to skip if exists): ");
                scanf("%d", &val);
                
                if (val == 0 || val == 1) {
                    //0 â†’ do not overwrite the variable if it already exists1 â†’ overwrite the variable if it already exists
                    if (setenv(var, path, val) == 0) {
                        printf("Environment variable '%s' set to '%s' successfully.\n", var, path);
                    } else {
                        perror("Error setting environment variable");
                    }
                } else {
                    printf("Invalid overwrite value. Please enter 0 or 1.\n");
                }
                break;
            }

            case 0:
                //Exit from the programme
                printf("Exiting the program. Goodbye!\n");
                return 0;


                //If wrong input provided
            default:
                printf("Invalid option. Please choose 0, 1, or 2.\n");
        }
    }

    return 0;
}