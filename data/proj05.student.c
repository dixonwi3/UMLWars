/******************************************************************************
   Anthony Miller
   CSE 325: Project #4
   Purpose:  Demonstrate operations capable through command line prompts,
             displaying username and environment variables upon request.

******************************************************************************/

#include <string>
#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <map>


#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>


#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include <math.h>
#include <time.h>


using namespace std;


//  Remarks:
//  Recognize following commands:
//  halt    ; terminate shell process
//  help    ; display these commands
//  date    ; display current date and time
//  env     ; display environment variables
//  path    ; display current search path
//  cwd     ; display abs pathname of cwd
//  cd      ; manage cwd
//  set     ; manage env
//  import  ; accept file of args

//  Helper function declarations
void GetCommand(char *uName);
int ProcessCommand(vector<string> uArgVec, int progCounter, string argStr);
int Help();
int Date();
int Env();
int Path();
int Cwd();
int Cd(vector<string> uArgVec);
int Set(vector<string> uArgVec);
int Import(vector<string> uArgVec);
void *CallSys(void *Args);



//  Constant/Globals
const int B_MAX = 128;
int progCounter = 1;

//  Environment
extern char **environ;


/*---------------------------------------------------------------------------
Name:  main
Purpose:  take in input command tokens service functions and provide errors
Receive:  argument tokens
Return:   0 if successful
---------------------------------------------------------------------------*/
int main()
{
    //  Declare variables
    //  User currently logged in
    char *uName;
    uName = getlogin();
    //int progCounter = 1;
    GetCommand(uName);
}


/*---------------------------------------------------------------------------
Name:     GetCommand
Purpose:  Provides styled line prompt and takes in user input in loop format
Receive:  Commands via the command line prompt
Return:   nothing
---------------------------------------------------------------------------*/
void GetCommand(char *uName)
{

    //  Build a map of commands in order to check if it is a valid (user input) minishell statement
    map<string, int> COMMAND;
    COMMAND["halt"] = 1;
    COMMAND["help"] = 2;
    COMMAND["date"] = 3;
    COMMAND["env"] = 4;
    COMMAND["path"] = 5;
    COMMAND["cwd"] = 6;
    COMMAND["cd"] = 7;
    COMMAND["set"] = 8;
    COMMAND["import"] = 9;



    //  Output prompt
    cout << "[" << progCounter << " " << uName << "] ";

    //  Get the line of commands
    string line;
    getline(cin, line);

    //  Convert to string stream
    stringstream uArgs(line);
    vector<string> uArgVec;
    string temp;
    string argStr = "";


    //  Populate vector of arguments
    while (getline(uArgs, temp, ' '))
    {
        argStr += temp;
        argStr += " ";

        uArgVec.push_back(temp);
    }


    //  Get number of arguments
    int uArgCount = uArgVec.size();




    //  loop for processing command line arguments
    if (uArgCount > 0)
    {
        //  Define our flag variable
        int returnFlag;


        //  Pass the vector of arguments into the switch statement
        returnFlag = ProcessCommand(uArgVec, progCounter, argStr);

        if( (COMMAND[uArgVec[0]]  < 1) | (COMMAND[uArgVec[0]] > 9) )
        {
            cout << "Error: Invalid argument(s) provided, command execution unsuccessful." << endl;
            uArgVec.clear();
            GetCommand(uName);
        }


        //  halt thrown
        if (returnFlag == 2)
        {
            exit(0);
        }

        //  Error thrown
        else if (returnFlag == 1)
        {
            cout << "Error: Invalid argument(s) provided, command execution unsuccessful." << endl;
            uArgVec.clear();
            GetCommand(uName);
        }

        //  Success thrown
        else if (returnFlag == 0)
        {
            uArgVec.clear();
            progCounter+=1;
            GetCommand(uName);
        }
    }
    else
    {

        cout << "Error: Invalid Number of Arguments Provided." << endl;
        uArgVec.clear();
        GetCommand(uName);
    }
}


/*---------------------------------------------------------------------------
Name:     ProcessCommand
Purpose:  Assess command line input argument, and execute or show errors
Receive:  Commands via the command line prompt
Return: flag 0, 1 or 2, where 0 is success, 1 is error thrown (no seq inc) and 2 is end program
---------------------------------------------------------------------------*/
int ProcessCommand(vector<string> uArgVec, int progCounter, string argStr)
{
    //  Build a map of commands in order to implement switch statement
    map<string, int> COMMAND;
    COMMAND["halt"] = 1;
    COMMAND["help"] = 2;
    COMMAND["date"] = 3;
    COMMAND["env"] = 4;
    COMMAND["path"] = 5;
    COMMAND["cwd"] = 6;
    COMMAND["cd"] = 7;
    COMMAND["set"] = 8;
    COMMAND["import"] = 9;

    string argument = uArgVec[0];

    //cout << "THIS IS ARGUMENT: " << "|xxx|" << argument << "|yyy|" << endl;
    //cout << endl;
    //cout << endl;

    switch (COMMAND[argument])
    {
        //  0:  halt command invoked
        case (1):
            cout << "halting" << endl;
            return 2;

        //  2:  help command invoked
        case (2):
            //cout << "help" << endl;
            return(Help());

        //  3:  date command invoked
        case (3):
            //cout << "date" << endl;
            return(Date());

        //  4:  env command invoked
        case (4):
            //cout << "env" << endl;
            return(Env());

        //  5:  path command invoked
        case (5):
            //cout << "path" << endl;
            return(Path());

        //  6:  cwd command invoked
        case (6):
            //cout << "cwd" << endl;
            return(Cwd());

        //  7:  cd command invoked
        case (7):
            //cout << "cd" << endl;
            return(Cd(uArgVec));

        //  8:  set command invoked
        case (8):
            //cout << "set" << endl;
            return(Set(uArgVec));

        //  9:  import command invoked
        case (9):
            //cout << "import" << endl;
            return(Import(uArgVec));

        //  0: Something outside of scope of this program
        case(0):

            // Create our variable used to reference thread system call is taking place in
            pthread_t thread;

            if ( pthread_create(&thread, NULL, CallSys, (void *) argStr.c_str() ) )
            {
                cout << "ERROR CREATING THREAD. EXITING WITH ERROR CODE -1" << endl;
                exit(-1);
            }

            if(pthread_join(thread, NULL) != 0)
            {
                cout << "ERROR JOINING THREADS. EXITING WITH ERROR CODE -2" << endl;
            }

            //Return success flag
            return 0;

        //  Default: no command found that fits
        default:
            cout << "Unrecognized command input provided. "
                    "Enter command <help> for list of commands." << endl;
            //  Return error flag
            return 1;

    }
}


/*---------------------------------------------------------------------------
Name:     Help
Purpose:  Print all possible commands and following configurations for commands
Receive:  Nothing
Return:   0 for success
---------------------------------------------------------------------------*/
int Help()
{
    cout << "Below is a list of commands possible in this program." << endl;

    cout << " halt          : exits the program." << endl;

    cout << " help          : lists commands possible in this program." << endl;

    cout << " date          : display the current date and time." << endl;

    cout << " env           : display the user's environment variables in a readable format." << endl;

    cout << " path          : display the current search path." << endl;

    cout << " cwd           : display the absolute pathname of the current working directory." << endl;

    cout << " import <FILE> : read commands from provided file if it exists." << endl;

    cout << " cd            : manage the current working directory." << endl;
    cout << "   <cd> without any commands will reset to the user home directory." << endl;
    cout << "   <cd DIR> will reset the current working directory to be 'DIR', where that token may be absolute or relative." << endl;
    cout << "   <cd ~USER> will reset the current working directory to be the home directory of user with username USER." << endl;

    cout << endl;

    cout << " set           : manage environment variables." << endl;
    cout << "   <set VAR VALUE> will set the environment variable VAR to the character string VALUE. Will add VAR to environment variables if it does not exist." << endl;
    cout << "   <set VAR> will remove VAR from environment variables if it does exist." << endl;


    return 0;
}


/*---------------------------------------------------------------------------
Name:     Date
Purpose:  Print the current local time and date
Receive:  Nothing
Return:   0 for success
---------------------------------------------------------------------------*/
int Date()
{
    //  Initialize variables
    time_t currTime;
    char* timeString;

    //  Obtain time and build output string
    currTime = time(NULL);
    //  Convert to local
    timeString = ctime(&currTime);

    //  Print it
    printf("Local date and time:  %s", timeString);

    //  Return successful execution flag
    return 0;
}


/*---------------------------------------------------------------------------
Name:     Env
Purpose:  Print the current user environment variables
Receive:  Nothing
Return:   0 for success
---------------------------------------------------------------------------*/
int Env()
{
    unsigned int I = 0;
    //  Loop until no environment variables are left to print
    while(environ[I] != NULL)
    {
        cout << environ[I] << endl;
        I++;
    }

    //  Return successful execution flag
    return 0;
}


/*---------------------------------------------------------------------------
Name:     Path
Purpose:  Print the current search paths for user.
Receive:  Nothing
Return:   0 for success
---------------------------------------------------------------------------*/
int Path()
{
    //char pathString[B_MAX] = ;
    char *token = strtok(getenv("PATH"), ":");

    cout << "Current Search Path(s): " << endl;
    while (token != NULL)
    {
        cout << token << endl;
        token = strtok(NULL, ":");
    }

    cout << "--- END OF SEARCH PATH DISPLAY --- " << endl;
    //  Return successful execution flag
    return 0;
}


/*---------------------------------------------------------------------------
Name:     Cwd
Purpose:  Print user current working directory
Receive:  Nothing
Return:   0 for success
---------------------------------------------------------------------------*/
int Cwd()
{
    char cwd[B_MAX];

    if (getcwd(cwd, B_MAX) == NULL)
    {
        perror("getcwd() function error.");
        return 1;
    }
    else
    {
        cout << "Current Working Directory: " << endl;
        cout << cwd << endl;
    }

    //  Return successful execution flag
    return 0;
}


/*---------------------------------------------------------------------------
Name:     Cd(vector<string>)
Purpose:  Assess command input, given it is a cd command with additional arguments. execute or show errors
Receive:  Vector of all commands provided on the line after cd token
Return:   flag 0 or 1, where 0 is success, 1 is error thrown (no seq inc)
---------------------------------------------------------------------------*/
int Cd(vector<string> uArgVec)
{
    //  Initialize string for call to chdir
    string dir = "";

    //  Second token in cd command call
    if ( uArgVec.size() == 2 && uArgVec[0] == "cd" )
    {
        //  Set second token to target directory
        string targetDir = uArgVec[1];

        //  cd ~USER case
        if ( targetDir[0] == '~' )
        {
            //  Add forward slash to directory passed to chdir
            dir += "/user/";
            targetDir.erase(0, 1);
            dir += targetDir;
        }
        else
        {
            dir += targetDir;
        }
    }
    //  Just a standalone cd call
    else if (uArgVec.size() == 1 && uArgVec[0] == "cd")
    {
        dir += "/user/";
        dir += getlogin();

    }
    //  This is an invalid call
    else
    {
        return 1;
    }

    //  Print for testing
    cout << "Target Directory, before chdir call: " << dir << endl;

    //  Call c_str on the directory string we built
    //  Pass to chdir
    chdir(dir.c_str());

    //  Test to ensure that the directory exists and was able to be moved into
    char cwd[B_MAX];

    if ( getcwd(cwd, B_MAX) != dir )
    {
        cout << "they didn't match." << endl;
        cout << "getcwd returned: " << getcwd(cwd, B_MAX) << endl;
        cout << "dir returned: " << dir << endl;
    }

    return 0;
}


/*---------------------------------------------------------------------------
Name:     Set(vector<string>)
Purpose:  Manage the current user environment variables
Receive:  Vector of all commands provided on the line after set token (var, value)
Return:   flag 0 or 1, where 0 is success, 1 is error thrown (no seq inc)
---------------------------------------------------------------------------*/
int Set(vector<string> uArgVec)
{
    //  Initialize string for call to setenv
    string targetVar = "";
    string targetVal = "";

    //  We will put the return flag in here
    int result;

    //  Two token set command call; unsets VAR from env deleting it
    if ( uArgVec.size() == 2 && uArgVec[0] == "set" )
    {
        //  Get the target variable
        targetVar += uArgVec[1];

        //  Turn it into appropriate type for unset
        char * inputVar = new char [targetVar.length()+1];
        strcpy(inputVar, targetVar.c_str());

        //  Invoke unsetenv on target variable
        result = unsetenv(inputVar);
    }
    //  Three token set command call; set VAR VALUE
    else if ( uArgVec.size() == 3 && uArgVec[0] == "set" )
    {
        //  Get the target variable
        targetVar += uArgVec[1];

        //  Turn it into appropriate type for unset
        char * inputVar = new char [targetVar.length()+1];
        strcpy(inputVar, targetVar.c_str());

        //  Get the target variable new value
        targetVal += uArgVec[2];

        //  Turn it into appropriate type for unset
        char * inputVal = new char [targetVal.length()+1];
        strcpy(inputVal, targetVal.c_str());

        result = setenv(inputVar, inputVal, 1);
    }
    //  Something is wrong with number of arguments provided, return error
    else
    {
        cout << "Unrecognized number of arguments for command provided. "
                "Enter command <help> for list of commands." << endl;
        return 1;
    }


    //  Check result
    if (result == 0)
    {
        return 0;
    }
    else
    {
        if (uArgVec.size() == 3)
        {
            perror("setenv");
        }
        else
        {
            perror("unsetenv");
        }
        return 1;
    }
}


/*---------------------------------------------------------------------------
Name:     Import(vector<string>)
Purpose:  Read commands from provided file
Receive:  Vector of all commands provided on the line after import token (filename)
Return:   flag 0 or 1,  where 0 is success, 1 is error thrown (no seq inc)
---------------------------------------------------------------------------*/
int Import( vector<string> uArgVec)
{
    //  Count how many system calls we make in here
    int i = 0;

    //  Default case
    if (uArgVec[0] == "import" && uArgVec.size() == 2)
    {
        //  Get the file name to be executed
        string fileName = uArgVec[1];

        //  open the file,
        ifstream fp(fileName);

        //  Create string variable to hold onto each system call
        string argStr;


        //  We pass an empty vector to process command, guaranteed to hit default case
        vector <string> argVec;

        //  Check if our file is valid for reading
        if (fp.is_open())
        {
            //  Iterate line by line of input file, attempt to execute each
            while ( getline(fp, argStr) )
            {
                cout << endl;

                cout << "-> " << argStr << endl;

                if(!fp.eof())
                {
                    argStr.erase(argStr.length() - 1 , 1);
                }

                argVec.push_back(argStr);
                auto returnFlag = ProcessCommand(argVec, argVec.size(), argStr);
                argVec.clear();
                if (returnFlag == 0)
                {
                    i++;
                }
                //  halt thrown
                else if (returnFlag == 2)
                {
                    exit(0);
                }

            }
        }
        fp.close();
    }
    else
    {
        cout << "Unrecognized number of arguments for command provided. "
                "Enter command <help> for list of commands." << endl;
        return 1;

    }
    progCounter = progCounter + (i - 1);
    return 0;

}


/*---------------------------------------------------------------------------
Name:     CallSys
Purpose:  Make a system call to execute commands outside of the scope of this program.
Receive:  Void pointer to arguments
Return:   Nothing
---------------------------------------------------------------------------*/
void* CallSys(void *Args)
{
    //  Make system call with input argument
    system( (char*)Args );

    //  Exit the thread we just made system call in
    pthread_exit(NULL);
}