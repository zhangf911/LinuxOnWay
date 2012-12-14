#ifndef LIBRARY_UTIL_DLLLOADER_H
#define LIBRARY_UTIL_DLLLOADER_H

#include <string>

namespace ZGF
{
	class DllLoader
	{
	private:
		/** 动态库名称 **/
		std::string filename;
		/** 动态库入口地址 **/
		void *lptr;
		/** 最后错误状态 **/
		bool error;
	public:
		/**
		* @brief 构造函数
		* @param dll文件路径名
		* @exception 
		* @note 
		*/
		DllLoader( const char *libfilename = "" );

		/**
		* @brief 析构函数
		* @exception 
		* @note 
		*/
		~DllLoader();

		/**
		* @brief 加载动态链接库
		* @return true : 成功 false : 失败
		* @exception 
		* @note 
		*/
		bool Load();

		/**
		* @brief 卸载动态库
		* @exception 
		* @note 
		*/
		void Close();

		/**
		* @brief 获取接口地址
		* @param 接口名称
		* @return 接口地址
		* @exception 
		* @note 
		*/
		void* GetAddressForSymbol( const char *symbol );

		/**
		* @brief 获取最后错误状态
		* @return 最后错误状态
		* @exception 
		* @note 获取错误状态并重置为false
		*/
		bool Error()
		{
			bool lasterror = error;

			error = false;

			return lasterror;
		}
		
		/**
		* @brief 获取动态库名称
		* @return 动态库名称
		* @exception 
		* @note 
		*/
		std::string GetName()
		{
			return filename;
		}

	};
}

#endif