#ifndef FILESYSTEM_H
#define FILESYSTEM_H

#include <sstream>
#include "memblockdevice.h"
#include "directory.h"

class FileSystem
{
private:
    MemBlockDevice mMemblockDevice;
    // Here you can add your own data structures
	Directory root;

public:
    FileSystem();
    ~FileSystem();

    /* These API functions need to be implemented
	   You are free to specify parameter lists and return values
    */

	bool createImage(std::string fileName);
	bool restoreImage(std::string fileName);

	std::string cp(std::string &path, std::string fileName, std::string newFileName);
	std::string format();

    /* This function creates a file in the filesystem */
    //createFile(...)
	void createFile(std::string &path, std::string name, std::string fileContent);
	


    /* Creates a folder in the filesystem */
    // createFolderi(...);
	void mkdir(std::string &path, std::string &name);// &name??

    /* Removes a file in the filesystem */
    // removeFile(...);
	bool rm(std::string &path, std::string fileName);

    /* Removes a folder in the filesystem */
    // removeFolder(...);
	

    /* Function will move the current location to a specified location in the filesystem */
    // goToFolder(...);
	bool FileSystem::cd(std::string & path);

    /* This function will get all the files and folders in the specified folder */
    // listDir(...);
	std::string ls(std::string currentDirectory);

    /* Add your own member-functions if needed */
	std::string cat(std::string &path, std::string fileName);


};

#endif // FILESYSTEM_H
