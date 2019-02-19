
#include "filesystem.h"

FileSystem::FileSystem() 
{
	//this->mMemblockDevice = MemBlockDevice();
	//this->root = Directory();
	this->format();
}

FileSystem::~FileSystem() 
{

}

bool FileSystem::createImage(std::string fileName)
{
	bool value = false;
	std::string name = fileName + ".txt";

	std::ofstream file;
	file.open(name);
	file.close();
	this->root.writeToFile(name, this->root);
	

	return value;
}

bool FileSystem::restoreImage(std::string fileName)
{
	std::ifstream readImage(fileName + ".txt");

	std::string path = "";
	std::string newFileName = ""; 
	std::string dirName = "";
	std::string content = ""; 
	std::string currentDir = "/"; 

	int nrOfFiles = 0;
	int nrOfDir = 1;

	bool fileIsRead = true;

	if (readImage)
	{
		while (!readImage.eof()) // eof == end of file
		{
			getline(readImage, path);
			readImage >> nrOfFiles;
			readImage.ignore();

			
			if (path[0] == '/')
			{
				currentDir = path.substr(0, path.find_last_of('/'));

				dirName = currentDir.substr(currentDir.find_last_of('/') + 1, currentDir.length());
				currentDir = path.substr(0, path.length() - dirName.length() - 1);

				this->mkdir(currentDir, dirName);
			}
		
			for (int i = 0; i < nrOfFiles; i++)
			{

				currentDir = path;
				getline(readImage, newFileName);

				if (newFileName.find_last_of('/') == newFileName.npos && newFileName.find("*") == newFileName.npos)
				{
					getline(readImage, content);

					if (content.find("*") != content.npos)
					{
						content = content.substr(1, content.length());
						this->createFile(currentDir, newFileName, content); 
					}
				}

			}
		}
		readImage.close();
	}
	else
	{
		fileIsRead = false;
	}

	return fileIsRead;

}

std::string FileSystem::cp(std::string & path, std::string fileName, std::string newFileName)
{
	int blockNr = this->root.findFile(path, fileName);
	std::string newContent;
	std::string returnvalue = "Could not copy file..";
	if (blockNr != -1)
	{
		newContent = this->mMemblockDevice.readBlock(blockNr).toString();
		createFile(path, newFileName, newContent);
		returnvalue = "File copied!";
	}

	return returnvalue;
}

std::string FileSystem::format()
{
	this->root.format();

	return "Now Formated.";
}

void FileSystem::createFile(std::string & path, std::string name, std::string fileContent)
{
	int count = mMemblockDevice.getCount();
	int blockSize = 512;

	this->root.createFile(path, name, count, fileContent);
	fileContent.resize(blockSize); // måste blocken vara fyllda??

	this->mMemblockDevice.writeBlock(count, fileContent);
	
}

void FileSystem::mkdir(std::string &path, std::string &name)
{
	this->root.createDirectory(path, name);
}

bool FileSystem::rm(std::string & path, std::string fileName)
{
	bool removed = false;
	int blockNr = this->root.findFile(path, fileName);

	if (blockNr != -1)
	{
		this->root.removeFile(path, blockNr);
		this->mMemblockDevice.subCount();
	}

	return removed;
}

std::string FileSystem::ls(std::string currentDirectory)
{
	return this->root.showDirInfo(currentDirectory);
}

std::string FileSystem::cat(std::string & path, std::string fileName)
{
	int blockNr = this->root.findFile(path, fileName);
	Block printBlock;
	std::string stringReturn = "Could not find file..";

	if (blockNr != -1)
	{
		printBlock = this->mMemblockDevice.readBlock(blockNr);
		stringReturn = printBlock.toString();
	}

	return stringReturn;
}

bool FileSystem::cd(std::string & path)
{
	bool value = false;
	if (this->root.enterDirectory(path) == true) {
		value = true;
	}

	return value;
}


/* Please insert your code */