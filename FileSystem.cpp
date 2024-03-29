#include"FileSystem.h"
#include<unistd.h>
#include<dirent.h>
#include<iostream>

namespace LOW
{
	void FileSystem::GetCurrentPathFileList(FileList& OUTfileList)
	{
		char curPath[260] = "\0";
		if(getcwd(curPath, 260) == NULL)
		{
			return;
		}
		DIR* pDir = opendir(curPath);
		if(pDir == NULL)
		{
			return;
		}
		struct dirent* dirp;
		while((dirp = readdir(pDir)) != NULL)
		{
			FileData data;
			data.fileName = dirp->d_name;
			OUTfileList.push_back(data);

			std::cout << "\t" << data.fileName;
		}
		std::cout << std::endl;
	}

	void FileSystem::GetCurrentWorkingDir(char** OUTpath)
	{

	}

	string FileSystem::GetCurrentWorkingDir()
	{
		string path;

		return path;
	}

	void FileSystem::GetCurrentProcessName(char** OUTname)
	{

	}

	string FileSystem::GetCurrentProcessName()
	{
		string processName;

		return processName;
	}
}

