/*
 * FileSystem.h
 *
 *  Created on: 2012-12-11
 *      Author: king
 */

#ifndef FILESYSTEM_H_
#define FILESYSTEM_H_

#include "Common.h"

namespace LOW
{
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
		/**
		 * @brief 获取当前目录下文件列表
		 * @param OUTfileList : 文件列表
		 * */
		static void GetCurrentPathFileList(FileList& OUTfileList);

		/**
		 * @brief 获取当前工作目录
		 * */
		static void GetCurrentWorkingDir(char** OUTpath);

		/**
		 * @brief 获取当前工作目录
		 * */
		static string GetCurrentWorkingDir();

		static void GetCurrentProcessName(char** OUTname);

		static string GetCurrentProcessName();
	};
}



#endif /* FILESYSTEM_H_ */
