/*
 * FileSystem.h
 *
 *  Created on: 2012-12-11
 *      Author: king
 */

#ifndef FILESYSTEM_H_
#define FILESYSTEM_H_

#include<string>
using std::string;

#include<vector>
using std::vector;

#include<list>
using std::list;

struct FileData
{
	// 文件名
	string fileName;
};

typedef vector<FileData> FileVector;
typedef list<FileData> FileList;

class FileSystem
{
public:
	static void GetCurrentPathFileList(FileList& OUTfileList);


};


#endif /* FILESYSTEM_H_ */
