// #include <stdio.h>
// #include <stdlib.h>
// #include <glob.h>

// void setFileToCheck(char ***files, char *path)
// {
//     char **found;
//     glob_t gstruct;
//     int r;

//     r = glob(path, GLOB_ERR, NULL, &gstruct);
//     /* check for errors */
//     if (r != 0)
//     {
//         if (r == GLOB_NOMATCH)
//             fprintf(stderr, "No matches\n");
//         else
//             fprintf(stderr, "Some kinda glob error\n");
//         exit(1);
//     }

//     /* success, output found filenames */
//     printf("Found %zu filename matches\n", gstruct.gl_pathc);
//     found = gstruct.gl_pathv;
//     while (*found)
//     {
//         printf("%s\n", *found);
//         found++;
//     }
// }

// //todo a mettre dans le parsing.
// int main(int ac, char **av)
// {
//     char **files;
//     printf("%s\n", av[1]);
//     setFileToCheck(&files, av[1]);
//     return 0;
// }

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    int x;

    for (x = 0; x < argc; x++)
        printf("%d = %s\n", x, argv[x]);

    return (0);
}