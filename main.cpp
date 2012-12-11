/*
 * main.cpp
 *
 *  Created on: 2012-12-11
 *      Author: king
 */
#include"FileSystem.h"

#include<iostream>
using std::cin;
using std::cout;
using std::endl;

int main(int argc, char* argv[])
{
	FileList curPathFileList;
	FileSystem::GetCurrentPathFileList(curPathFileList);

	for(FileList::iterator it = curPathFileList.begin(); it != curPathFileList.end(); ++it)
	{
		cout << it->fileName << endl;
	}
	return 0;
}


