#include <iostream>
#include <sstream>
#include "filesystem.h"
#include "crtdbg.h"

const int MAXCOMMANDS = 8;
const int NUMAVAILABLECOMMANDS = 15;

std::string availableCommands[NUMAVAILABLECOMMANDS] = {
    "quit","format","ls","create","cat","createImage","restoreImage",
    "rm","cp","append","mv","mkdir","cd","pwd","help"
};

/* Takes usercommand from input and returns number of commands, commands are stored in strArr[] */
int parseCommandString(const std::string &userCommand, std::string strArr[]);
int findCommand(std::string &command);
bool quit();
std::string help();

/* More functions ... */

int main(void) {

	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	FileSystem fs;
	Directory dir;
	std::string name;
	int whichFile = 0;
	

	std::string userCommand, commandArr[MAXCOMMANDS];
	std::string user = "user@DV1492";    // Change this if you want another user to be displayed
	std::string currentDir = "/";    // current directory, used for output

    bool bRun = true;

    do {
        std::cout << user << ":" << currentDir << "$ ";
        getline(std::cin, userCommand);

        int nrOfCommands = parseCommandString(userCommand, commandArr);
        if (nrOfCommands > 0) {

            int cIndex = findCommand(commandArr[0]);
            switch(cIndex) {

			case 0: //quit
				bRun = quit();                
                break;
            case 1: // format
				std::cout << fs.format() << std::endl;
                break;
            case 2: // ls
			{
				std::cout << "Listing directory" << std::endl;
				std::cout << fs.ls(currentDir) << std::endl;

			}
                break;
            case 3: // create
			{
				std::string fileName = userCommand.substr(7, userCommand.length());

				std::string inputData = "";
				std::cout << "Input text: ";
				getline(std::cin, inputData);
				fs.createFile(currentDir, fileName, inputData);

			}
                break;
            case 4: // cat
			{
				std::string fileName = userCommand.substr(4, userCommand.length());
				std::cout << fs.cat(currentDir, fileName) << std::endl;
			}
                break;
            case 5: // createImage
			{
				std::string fileName = userCommand.substr(12, userCommand.length());
				fs.createImage(fileName);
			}
                break;
            case 6: // restoreImage
			{
				std::string fileName = userCommand.substr(13, userCommand.length());
				
				if (fs.restoreImage(fileName) == true)
				{
					std::cout << "Image Restored!\n" << std::endl;
				}
				else
				{
					std::cout << "File not found.." << std::endl;
				}
			}
                break;
            case 7: // rm
			{
				std::string fileName = userCommand.substr(3, userCommand.length());
				fs.rm(currentDir, fileName);

			}
                break;
            case 8: // cp
			{
				std::string fileName = userCommand.substr(3, userCommand.length());
			
				std::size_t spacePos = fileName.find(32); // 32 == space i ascii
				std::string newFileName = fileName.substr((spacePos + 1), fileName.length());
				std::string oldFileName = fileName.substr(0, spacePos); 
				
				std::cout << fs.cp(currentDir, oldFileName, newFileName) << std::endl;
			}
                break;
            case 9: // append
                break;
            case 10: // mv
                break;
            case 11: // mkdir
			{
				std::string name = userCommand.substr(6, userCommand.length());
				fs.mkdir(currentDir, name);
			
			}
                break;
            case 12: // cd
			{
				// OBS! '/' måste skrivas efter directory-namn t.ex "dirName/"

				std::string subStr = currentDir + userCommand.substr(3, userCommand.length() - 3);
				std::string subStr2 = userCommand.substr(3, userCommand.length() - 3);

				 if (fs.cd(subStr) ==  true) 
				 {
					name = userCommand.substr(3, userCommand.length());
					currentDir = subStr;

					std::cout << "Entering directory \n" << std::endl;
					std::cout << currentDir << std::endl;
				}
				 else if (fs.cd(subStr2) == true)
				 {
					 currentDir = subStr2;
				 }
				 else
				 {
					 std::cout << "Could not find directory.." << std::endl;
				 }
		
			}
			
                break;
            case 13: // pwd
				std::cout << "Printing directory\n" << currentDir << std::endl;
			

                break;
            case 14: // help
                std::cout << help() << std::endl;
                break;
            default:
                std::cout << "Unknown command: " << commandArr[0] << std::endl;
            }
        }
    } while (bRun == true);

    return 0;
}

int parseCommandString(const std::string &userCommand, std::string strArr[]) {
    std::stringstream ssin(userCommand);
    int counter = 0;
    while (ssin.good() && counter < MAXCOMMANDS) {
        ssin >> strArr[counter];
        counter++;
    }
    if (strArr[0] == "") {
        counter = 0;
    }
    return counter;
}
int findCommand(std::string &command) {
    int index = -1;
    for (int i = 0; i < NUMAVAILABLECOMMANDS && index == -1; ++i) {
        if (command == availableCommands[i]) {
            index = i;
        }
    }
    return index;
}

bool quit() {
	std::cout << "Exiting\n";
	return false;
}

std::string help() {
    std::string helpStr;
    helpStr += "OSD Disk Tool .oO Help Screen Oo.\n";
    helpStr += "-----------------------------------------------------------------------------------\n" ;
    helpStr += "* quit:                             Quit OSD Disk Tool\n";
    helpStr += "* format;                           Formats disk\n";
    helpStr += "* ls     <path>:                    Lists contents of <path>.\n";
    helpStr += "* create <path>:                    Creates a file and stores contents in <path>\n";
    helpStr += "* cat    <path>:                    Dumps contents of <file>.\n";
    helpStr += "* createImage  <real-file>:         Saves disk to <real-file>\n";
    helpStr += "* restoreImage <real-file>:         Reads <real-file> onto disk\n";
    helpStr += "* rm     <file>:                    Removes <file>\n";
    helpStr += "* cp     <source> <destination>:    Copy <source> to <destination>\n";
    helpStr += "* append <source> <destination>:    Appends contents of <source> to <destination>\n";
    helpStr += "* mv     <old-file> <new-file>:     Renames <old-file> to <new-file>\n";
    helpStr += "* mkdir  <directory>:               Creates a new directory called <directory>\n";
    helpStr += "* cd     <directory>:               Changes current working directory to <directory>\n";
    helpStr += "* pwd:                              Get current working directory\n";
    helpStr += "* help:                             Prints this help screen\n";
    return helpStr;
}

/* Insert code for your shell functions and call them from the switch-case */
