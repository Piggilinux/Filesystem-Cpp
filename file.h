#ifndef FILE_H
#define FILE_H

#include <string>
#include <stdlib.h>
#include <vector>
#include <fstream>
#include <algorithm>


class File
{
private:
	std::string fileName;
	std::string content;
	int blockNr;
public:
	File();
	File(std::string fileName, int blockNr, std::string content);
	~File();

	std::string getFileName()const;
	std::string getContent()const;
	int getBlockNr()const;

};


#endif // !FILE_H

