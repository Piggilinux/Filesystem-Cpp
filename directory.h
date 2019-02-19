#ifndef directory_h
#define directory_h

#include "file.h"

class Directory
{
private:
	std::string directoryParent;
	std::string directoryName;
	std::vector<File> files;
	std::vector<Directory> directories;
	int counter;
	int counter2;
	int currentPos;
	bool isPathTrue; 

public:

	//Directory();
	Directory(std::string directoryName = "", std::string directoryParent = "");
	virtual ~Directory();

	bool format();
	bool createDirectory(std::string &path, std::string &name);
	std::string getDirName();
	std::string getdirParent();
	std::string showDirInfo(std::string &currentDir);

	bool createFile(std::string &path, std::string fileName, int blockNr, std::string fileContent);

	Directory* Directory::findThisDirectory(const std::string &path);
	bool Directory::enterDirectory(const std::string &path);
	int findFile(std::string &path, std::string fileName);
	int removeFile(std::string &path, int blockNr);
	void writeToFile(std::string &file, Directory root);

};
#endif // !directory_h

