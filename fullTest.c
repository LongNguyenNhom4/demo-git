#include <unistd.h>        /* F_OK, STDIN_FILENO, STDERR_FILENO, etc. */

#include <sys/stat.h>      /* struct stat */

#include <sys/types.h>     /* S_IFMT */

#include <stdio.h>         /* fprintf, printf, sprintf, etc. */

#include <stdlib.h>        /* exit, etc. */

#include <time.h>          /* ctime */

 
/* Define all the error messages */
char * error_msg[] = {

              "\nUsage: ./12filestat <file|dir> [<file|dir>]\n\n",

              "\nFile does not exist !!\n\n",

              "\nError doing 'stat' on file\n\n"

       };

 

/* Declare the prototype for function 'print_error' */

void print_error(int msg_num, int exit_code, int exit_flag);

 

int main(int argc, char *argv[])

{

       int i;                     /* A counter */

       mode_t file_perm;          /* File permissions */

       struct stat file_details;  /* Detailed file info */

       char success_msg[] = "\nCommand executed successfully\n\n";

      

       /* Check if correct number of arguments are supplied */

       if ( argc < 2 )      print_error(0,2,1);

      

       /* Loop through all the filenames */

       for ( i = 1; i < argc; i++ )

       {

              /* Display the filename */

              printf("\n%s\n%s\n%s\n","----------------",argv[i],"----------------");

 

              /* Check if the file exists */

              if ( access(argv[i],F_OK) == -1 )

              {

                     print_error(1,3,0);

                     continue;     /* Check the next file */

              }

             

              /* Retrieve the file details */

              if ( lstat(argv[i],&file_details) < 0 )

              {

                     print_error(2,4,0);

                     continue;     /* Check the next file */

              }

      

              /* Get the file type */

              if ( S_ISREG(file_details.st_mode) )

                     printf("File type : Regular\n");

              else if ( S_ISDIR(file_details.st_mode) )

                     printf("File type : Directory\n");

              else if ( S_ISLNK(file_details.st_mode) )

                     printf("File type : Symbolic link\n");

              else

                     printf("File type : Other");

      

              /* Get the number of links */

              printf("Number of links : %d\n", (int)file_details.st_nlink);

 

              /* Get the time of last access of the file */

              printf("Time of last access : %s", ctime(&file_details.st_atime));

 

              /* Get the file permissions */

              printf("File Permissions:\n");

              file_perm = file_details.st_mode & ~S_IFMT;

              printf("\tUser : ");

              if ( file_perm & S_IRUSR ) printf("Readable, ");

              else printf("Not readable, ");

              if ( file_perm & S_IWUSR ) printf("Writable, ");

              else printf("Not writable, ");

              if ( file_perm & S_IXUSR ) printf("Executable\n");

              else printf("Not executable\n");

              printf("\tGroup : ");

              if ( file_perm & S_IRGRP ) printf("Readable, ");

              else printf("Not readable, ");

              if ( file_perm & S_IWGRP ) printf("Writable, ");

              else printf("Not writable, ");

              if ( file_perm & S_IXGRP ) printf("Executable\n");

              else printf("Not executable\n");

              printf("\tOthers : ");

              if ( file_perm & S_IROTH ) printf("Readable, ");

              else printf("Not readable, ");

              if ( file_perm & S_IWOTH ) printf("Writable, ");

              else printf("Not writable, ");

              if ( file_perm & S_IXOTH ) printf("Executable\n");

              else printf("Not executable\n");
            
              

       }

      

       printf("%s", success_msg);

      

       return 1;

}

 

void print_error(int error_index, int exit_code, int exit_flag)

{

       fprintf(stderr, "%s\n",error_msg[error_index]);

       if (exit_flag) exit(exit_code);

}
