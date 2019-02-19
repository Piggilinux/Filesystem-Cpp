#include "file.h"


File::File()
{
	std::string content = "";
	std::string fileName = "";
	int blockNr = 0;
}

File::File(std::string fileName, int blockNr, std::string content)
{
	this->content = content;
	this->fileName = fileName;
	this->blockNr = blockNr;
}

File::~File()
{
}

std::string File::getFileName() const
{
	return this->fileName;
}

std::string File::getContent() const
{
	return this->content;
}

int File::getBlockNr() const
{
	return this->blockNr;
}




