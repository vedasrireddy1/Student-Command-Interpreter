#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>

#define MAX_ARGS 20


// STEP 5: Get a field from a CSV line

void get_field(char *line, int field_number, char *output, int size)
{
    int current_field = 0;
    int i = 0;

    char *ptr = line;

    while (*ptr != '\0' && current_field < field_number)
    {
        if (*ptr == ',')
        {
            current_field++;
        }

        ptr++;
    }

    while (*ptr != '\0' &&
           *ptr != ',' &&
           *ptr != '\n' &&
           i < size - 1)
    {
        output[i] = *ptr;
        i++;
        ptr++;
    }

    output[i] = '\0';

    // Remove leading space
    if (output[0] == ' ')
    {
        int j = 0;

        while (output[j] != '\0')
        {
            output[j] = output[j + 1];
            j++;
        }
    }
}


// STEP 5: Attendance command

void attendance()
{
    FILE *file = fopen("attendance.csv", "r");

    if (file == NULL)
    {
        perror("attendance.csv");
        return;
    }

    char line[500];
    char roll[20];

    printf("Enter Roll Number: ");
    fgets(roll, sizeof(roll), stdin);
    roll[strcspn(roll, "\n")] = '\0';

    // Skip header
    fgets(line, sizeof(line), file);

    int found = 0;

    while (fgets(line, sizeof(line), file) != NULL)
    {
        char file_roll[20];

        get_field(line, 0, file_roll, sizeof(file_roll));

        if (strcmp(file_roll, roll) == 0)
        {
            char name[100];
            char ml[20];
            char dsa[20];
            char ossp[20];
            char es[20];
            char dbms[20];
            char jl[20];

            get_field(line, 1, name, sizeof(name));
            get_field(line, 2, ml, sizeof(ml));
            get_field(line, 3, dsa, sizeof(dsa));
            get_field(line, 4, ossp, sizeof(ossp));
            get_field(line, 5, es, sizeof(es));
            get_field(line, 6, dbms, sizeof(dbms));
            get_field(line, 7, jl, sizeof(jl));

            printf("\nRoll No: %s\n", file_roll);
            printf("Name: %s\n", name);
            printf("Machine Learning: %s\n", ml);
            printf("DSA-3: %s\n", dsa);
            printf("OSSP: %s\n", ossp);
            printf("ES: %s\n", es);
            printf("DBMS: %s\n", dbms);
            printf("JL: %s\n", jl);

            found = 1;
            break;
        }
    }

    if (!found)
    {
        printf("Roll number not found.\n");
    }

    fclose(file);
}


// STEP 6: Internals command

void internals()
{
    FILE *file = fopen("internals.csv", "r");

    if (file == NULL)
    {
        perror("internals.csv");
        return;
    }

    char line[500];
    char roll[20];

    printf("Enter Roll Number: ");
    fgets(roll, sizeof(roll), stdin);
    roll[strcspn(roll, "\n")] = '\0';

    // Skip header
    fgets(line, sizeof(line), file);

    int found = 0;

    while (fgets(line, sizeof(line), file) != NULL)
    {
        char file_roll[20];

        get_field(line, 0, file_roll, sizeof(file_roll));

        if (strcmp(file_roll, roll) == 0)
        {
            char name[100];
            char ml[20];
            char dsa[20];
            char ossp[20];
            char es[20];
            char dbms[20];
            char jl[20];

            get_field(line, 1, name, sizeof(name));
            get_field(line, 2, ml, sizeof(ml));
            get_field(line, 3, dsa, sizeof(dsa));
            get_field(line, 4, ossp, sizeof(ossp));
            get_field(line, 5, es, sizeof(es));
            get_field(line, 6, dbms, sizeof(dbms));
            get_field(line, 7, jl, sizeof(jl));

            printf("\nRoll No: %s\n", file_roll);
            printf("Name: %s\n", name);
            printf("Machine Learning: %s\n", ml);
            printf("DSA-3: %s\n", dsa);
            printf("OSSP: %s\n", ossp);
            printf("ES: %s\n", es);
            printf("DBMS: %s\n", dbms);
            printf("JL: %s\n", jl);

            found = 1;
            break;
        }
    }

    if (!found)
    {
        printf("Roll number not found.\n");
    }

    fclose(file);
}


// STEP 7: CGPA command

void cgpa()
{
    FILE *file = fopen("cgpa.csv", "r");

    if (file == NULL)
    {
        perror("cgpa.csv");
        return;
    }

    char line[500];
    char roll[20];

    printf("Enter Roll Number: ");
    fgets(roll, sizeof(roll), stdin);
    roll[strcspn(roll, "\n")] = '\0';

    // Skip header
    fgets(line, sizeof(line), file);

    int found = 0;

    while (fgets(line, sizeof(line), file) != NULL)
    {
        char file_roll[20];

        get_field(line, 0, file_roll, sizeof(file_roll));

        if (strcmp(file_roll, roll) == 0)
        {
            char name[100];
            char cgpa_value[20];

            get_field(line, 1, name, sizeof(name));
            get_field(line, 2, cgpa_value, sizeof(cgpa_value));

            printf("\nRoll No: %s\n", file_roll);
            printf("Name: %s\n", name);
            printf("CGPA: %s\n", cgpa_value);

            found = 1;
            break;
        }
    }

    if (!found)
    {
        printf("Roll number not found.\n");
    }

    fclose(file);
}


// STEP 8: Student Dashboard

void student()
{
    FILE *attendance_file = fopen("attendance.csv", "r");
    FILE *internals_file = fopen("internals.csv", "r");
    FILE *cgpa_file = fopen("cgpa.csv", "r");

    if (attendance_file == NULL ||
        internals_file == NULL ||
        cgpa_file == NULL)
    {
        printf("Error: Required student data file is missing.\n");

        if (attendance_file != NULL)
            fclose(attendance_file);

        if (internals_file != NULL)
            fclose(internals_file);

        if (cgpa_file != NULL)
            fclose(cgpa_file);

        return;
    }

    char roll[20];

    printf("Enter Roll Number: ");
    fgets(roll, sizeof(roll), stdin);
    roll[strcspn(roll, "\n")] = '\0';


    // Read attendance

    char line[500];
    char student_name[100] = "";

    char ml_att[20];
    char dsa_att[20];
    char ossp_att[20];
    char es_att[20];
    char dbms_att[20];
    char jl_att[20];

    fgets(line, sizeof(line), attendance_file);

    int attendance_found = 0;

    while (fgets(line, sizeof(line), attendance_file) != NULL)
    {
        char file_roll[20];

        get_field(line, 0, file_roll, sizeof(file_roll));

        if (strcmp(file_roll, roll) == 0)
        {
            get_field(line, 1, student_name, sizeof(student_name));
            get_field(line, 2, ml_att, sizeof(ml_att));
            get_field(line, 3, dsa_att, sizeof(dsa_att));
            get_field(line, 4, ossp_att, sizeof(ossp_att));
            get_field(line, 5, es_att, sizeof(es_att));
            get_field(line, 6, dbms_att, sizeof(dbms_att));
            get_field(line, 7, jl_att, sizeof(jl_att));

            attendance_found = 1;
            break;
        }
    }


    // Read internals

    char ml_int[20];
    char dsa_int[20];
    char ossp_int[20];
    char es_int[20];
    char dbms_int[20];
    char jl_int[20];

    fgets(line, sizeof(line), internals_file);

    int internals_found = 0;

    while (fgets(line, sizeof(line), internals_file) != NULL)
    {
        char file_roll[20];

        get_field(line, 0, file_roll, sizeof(file_roll));

        if (strcmp(file_roll, roll) == 0)
        {
            get_field(line, 2, ml_int, sizeof(ml_int));
            get_field(line, 3, dsa_int, sizeof(dsa_int));
            get_field(line, 4, ossp_int, sizeof(ossp_int));
            get_field(line, 5, es_int, sizeof(es_int));
            get_field(line, 6, dbms_int, sizeof(dbms_int));
            get_field(line, 7, jl_int, sizeof(jl_int));

            internals_found = 1;
            break;
        }
    }


    // Read CGPA

    char cgpa_value[20];

    fgets(line, sizeof(line), cgpa_file);

    int cgpa_found = 0;

    while (fgets(line, sizeof(line), cgpa_file) != NULL)
    {
        char file_roll[20];

        get_field(line, 0, file_roll, sizeof(file_roll));

        if (strcmp(file_roll, roll) == 0)
        {
            get_field(line, 2, cgpa_value, sizeof(cgpa_value));

            cgpa_found = 1;
            break;
        }
    }


    if (!attendance_found || !internals_found || !cgpa_found)
    {
        printf("Roll number not found.\n");

        fclose(attendance_file);
        fclose(internals_file);
        fclose(cgpa_file);

        return;
    }


    // Display dashboard

    printf("\n");
    printf("========================================\n");
    printf("          STUDENT DASHBOARD\n");
    printf("========================================\n");

    printf("Roll No: %s\n", roll);
    printf("Name:    %s\n", student_name);
    printf("CGPA:    %s\n", cgpa_value);

    printf("\n------------- ATTENDANCE ----------------\n");

    printf("Machine Learning: %s\n", ml_att);
    printf("DSA-3:            %s\n", dsa_att);
    printf("OSSP:             %s\n", ossp_att);
    printf("ES:               %s\n", es_att);
    printf("DBMS:             %s\n", dbms_att);
    printf("JL:               %s\n", jl_att);

    printf("\n------------- INTERNALS -----------------\n");

    printf("Machine Learning: %s\n", ml_int);
    printf("DSA-3:            %s\n", dsa_int);
    printf("OSSP:             %s\n", ossp_int);
    printf("ES:               %s\n", es_int);
    printf("DBMS:             %s\n", dbms_int);
    printf("JL:               %s\n", jl_int);

    printf("========================================\n");


    fclose(attendance_file);
    fclose(internals_file);
    fclose(cgpa_file);
}


// STEP 9: Note command

// STEP 9: Note command

void note(char *args[])
{
    if (args[1] == NULL)
    {
        printf("Usage:\n");
        printf("  note add <text>\n");
        printf("  note view\n");
        printf("  note delete\n");
        return;
    }


    // note view

    if (strcmp(args[1], "view") == 0)
    {
        FILE *file = fopen("notes.txt", "r");

        if (file == NULL)
        {
            printf("No notes found.\n");
            return;
        }

        char line[500];

        printf("\n========== NOTES ==========\n");

        while (fgets(line, sizeof(line), file) != NULL)
        {
            printf("%s", line);
        }

        printf("============================\n");

        fclose(file);

        return;
    }


    // note add

    if (strcmp(args[1], "add") == 0)
    {
        if (args[2] == NULL)
        {
            printf("note add: missing text\n");
            return;
        }

        FILE *file = fopen("notes.txt", "a");

        if (file == NULL)
        {
            perror("notes.txt");
            return;
        }

        time_t current_time = time(NULL);

        char *time_string = ctime(&current_time);

        // Remove newline from timestamp
        time_string[strcspn(time_string, "\n")] = '\0';

        fprintf(file, "[%s] ", time_string);

        int i = 2;

        while (args[i] != NULL)
        {
            fprintf(file, "%s", args[i]);

            if (args[i + 1] != NULL)
            {
                fprintf(file, " ");
            }

            i++;
        }

        fprintf(file, "\n");

        fclose(file);

        printf("Note added successfully.\n");

        return;
    }


    // note delete

    if (strcmp(args[1], "delete") == 0)
    {
        FILE *file = fopen("notes.txt", "w");

        if (file == NULL)
        {
            perror("notes.txt");
            return;
        }

        fclose(file);

        printf("All notes deleted successfully.\n");

        return;
    }


    printf("Unknown note command.\n");
}
// STEP 10: Help command

void help()
{
    printf("\n========== StudentShell Commands ==========\n");

    printf("\nStudent Commands:\n");
    printf("  attendance       View attendance\n");
    printf("  internals        View internal marks\n");
    printf("  cgpa             View CGPA\n");
    printf("  student          View complete student dashboard\n");

    printf("\nNote Commands:\n");
    printf("  note add <text>  Add a note\n");
    printf("  note view        View all notes\n");
    printf("  note delete      Delete all notes\n");

    printf("\nShell Commands:\n");
    printf("  cd <directory>   Change directory\n");
    printf("  pwd              Show current directory\n");
    printf("  exit             Exit StudentShell\n");

    printf("\nLinux Commands:\n");
    printf("  Any Linux command can be executed normally.\n");

    printf("===========================================\n\n");
}

int main()
{
    char input[100];
    char *args[MAX_ARGS];

    int arg_count;

    while (1)
    {
        printf("StudentShell> ");
        fflush(stdout);

        if (fgets(input, sizeof(input), stdin) == NULL)
        {
            break;
        }

        input[strcspn(input, "\n")] = '\0';

        arg_count = 0;

        char *ptr = input;


        // STEP 2: Parse command and arguments

        while (*ptr != '\0' && arg_count < MAX_ARGS - 1)
        {
            // Skip spaces

            while (*ptr == ' ')
            {
                ptr++;
            }

            if (*ptr == '\0')
            {
                break;
            }

            // Store beginning of argument

            args[arg_count] = ptr;
            arg_count++;

            // Move until space or end

            while (*ptr != ' ' && *ptr != '\0')
            {
                ptr++;
            }

            // Replace space with '\0'

            if (*ptr == ' ')
            {
                *ptr = '\0';
                ptr++;
            }
        }

        args[arg_count] = NULL;


        if (arg_count == 0)
        {
            continue;
        }


        // STEP 3: Built-in command - exit

        if (strcmp(args[0], "exit") == 0)
        {
            break;
        }


        // STEP 3: Built-in command - pwd

        if (strcmp(args[0], "pwd") == 0)
        {
            char cwd[1024];

            if (getcwd(cwd, sizeof(cwd)) != NULL)
            {
                printf("%s\n", cwd);
            }
            else
            {
                perror("pwd");
            }

            continue;
        }


        // STEP 3: Built-in command - cd

        if (strcmp(args[0], "cd") == 0)
        {
            if (args[1] == NULL)
            {
                printf("cd: missing argument\n");
            }
            else if (chdir(args[1]) != 0)
            {
                perror("cd");
            }

            continue;
        }


        // STEP 5: Student command - attendance

        if (strcmp(args[0], "attendance") == 0)
        {
            attendance();
            continue;
        }


        // STEP 6: Student command - internals

        if (strcmp(args[0], "internals") == 0)
        {
            internals();
            continue;
        }


        // STEP 7: Student command - cgpa

        if (strcmp(args[0], "cgpa") == 0)
        {
            cgpa();
            continue;
        }


        // STEP 8: Student command - student

        if (strcmp(args[0], "student") == 0)
        {
            student();
            continue;
        }


        // STEP 9: Student command - note

        if (strcmp(args[0], "note") == 0)
        {
            note(args);
            continue;
        }
        // STEP 10: StudentShell help

        if (strcmp(args[0], "help") == 0)
        {
            help();
            continue;
        }


        // STEP 4: Execute Linux commands

        pid_t pid = fork();

        if (pid < 0)
        {
            perror("fork");
        }
        else if (pid == 0)
        {
            execvp(args[0], args);

            perror("execvp");
            return 1;
        }
        else
        {
            waitpid(pid, NULL, 0);
        }
    }

    return 0;
}