#include "directory.h"
#include <iostream>

//Directory::Directory()
//{
//	this->directoryName = "Root";
//	this->counter = 0;
//	this->currentPos = 0;
//	this->isPathTrue = false;
//	this->directories.push_back(Directory("/", ""));
//
//}

Directory::Directory(std::string directoryName, std::string directoryParent)
{
	this->directoryName = directoryName;
	this->directoryParent = directoryParent;
	this->isPathTrue = false;
	this->counter = 0;
	this->counter2 = 0;

}

Directory::~Directory()
{
}

bool Directory::format()
{
	std::vector<Directory> newRoot;
	this->directories = newRoot;
	std::vector<File> newRootFile;
	this->files = newRootFile;
	this->directories.push_back(Directory("/", ""));

	return true;
}

bool Directory::createDirectory(std::string &path, std::string &name)
{

	Directory *tempPtr;
	tempPtr = findThisDirectory(path);

	if (this->isPathTrue == true) 
	{
		tempPtr->directories.push_back(Directory(name + "/", path));
		tempPtr->counter++;
	}

	return this->isPathTrue;
}

std::string Directory::getDirName()
{
	return this->directoryName;
}

std::string Directory::getdirParent()
{
	return this->directoryParent;
}

std::string Directory::showDirInfo(std::string &currentDir)
{
	Directory *tempPtr = findThisDirectory(currentDir);
	std::string str = "";

	for (int i = 0; i < tempPtr->directories.size(); i++)
	{
		str = str + tempPtr->directories.at(i).getDirName();
		str[(str.length() - 1)] = ' ';
	}
	
	for (int i = 0; i < tempPtr->files.size(); i++)
	{
		str = str + " " + tempPtr->files.at(i).getFileName();

	}
	
	return str;
}

bool Directory::createFile(std::string & path, std::string fileName, int blockNr, std::string fileContent)
{
	bool value = false;
	Directory *tempPtr = findThisDirectory(path);

	tempPtr->files.push_back(File(fileName, blockNr, fileContent));
	tempPtr->counter2++;

	return value;
}


Directory * Directory::findThisDirectory(const std::string & path)
{
	
	std::string currentDir = "";
	std::vector<Directory> *checkWalker = nullptr;
	Directory *returnDir = nullptr;
	checkWalker = &this->directories;
	int vectorPos = 0;
	bool exist = false;
	int startPos = 0;
	int endPos = 0;
	std::string pathFound = "";


	for (int i = 0; i < path.length(); i++) 
	{
		if (path[i] == '/') //kollar efter '/' i våran "väg" vi letar efter ( går den ifrån root?)
		{	
			std::string currentDir;
			
			endPos = i + 1;
			for (int k = startPos; k < endPos; k++)
			{
				currentDir = currentDir + path[k];
			}
			startPos = endPos;
			

			for (int k = 0; k < checkWalker->size(); k++) // Gå igenom våran directories-vector
			{
				if (checkWalker->at(k).getDirName() == currentDir) //om vector på plats x == curdir
				{
					vectorPos = k;
					exist = true;
					pathFound = pathFound + checkWalker->at(k).getDirName();	
				}
			}
			
			if (exist == true)
			{
				exist = false;
				if (pathFound == path)
				{
					this->isPathTrue = true;
					returnDir = &checkWalker->at(vectorPos);
					//std::cout << "returnDir" << returnDir->getDirName() << std::endl;
				}
				checkWalker = &checkWalker->at(vectorPos).directories;
			}
			
		}
	}
	return returnDir;
	//return &checkWalker->at(vectorPos);

}

bool Directory::enterDirectory(const std::string &path)
{
	this->isPathTrue = false;
	bool value = false;
	Directory *tempPtr;

	tempPtr = findThisDirectory(path);

	if (this->isPathTrue == true) {
		value = true;
	}

	return value;
}

int Directory::findFile(std::string & path, std::string fileName)
{
	Directory *tempPtr = findThisDirectory(path);
	int place = -1;

	if (this->isPathTrue == true)
	{
		for (int i = 0; i < tempPtr->files.size(); i++)
		{
			if (fileName == tempPtr->files.at(i).getFileName())
			{
				place = tempPtr->files.at(i).getBlockNr();
			}

		}
	}

	return place;
}

int Directory::removeFile(std::string & path, int blockNr)
{
	Directory *tempPtr = findThisDirectory(path);

	if (blockNr != -1)
	{
		tempPtr->files.erase((tempPtr->files.begin() + blockNr)); 															  
	}
	return blockNr;
}

// Klar
void Directory::writeToFile(std::string & name, Directory root)
{
	std::ofstream file(name, std::ios_base::app); // ios_base::app forsätter skriva från där den senast skrev.

	int rootDirSize = root.directories.size();

	for (int i = 0; i < rootDirSize; i++)
	{
		file << root.directories.at(i).getdirParent() << root.directories.at(i).getDirName() << std::endl;
		file << root.directories.at(i).counter2 << std::endl;

		int rootDirFileSize = root.directories.at(i).files.size();

		for (int k = 0; k < rootDirFileSize; k++)
		{
			file << root.directories.at(i).files.at(k).getFileName() << std::endl;
			file << "*" << root.directories.at(i).files.at(k).getContent() << std::endl;
		}
		writeToFile(name, root.directories.at(i));
	}
	file.close();
} 



