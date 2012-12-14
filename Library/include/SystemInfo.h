#ifndef LIBRARY_UTIL_SYSTEMINFO_H
#define LIBRARY_UTIL_SYSTEMINFO_H

namespace ZGF{
	
	class SystemInfo
	{
	public:
		/**
		* @brief 返回当前系统CPU数量
		* @return 当前系统CPU数量
		* @exception 
		* @note 
		*/
		static long GetCPUCount();

		/**
		* @brief 获取调用进程的CPU占用时间
		* @return 调用进程的CPU占用时间
		* @exception 
		* @note 时间包括内核时间和用户时间，时间单位为微妙
		*/
		static unsigned long long GetCPUUsage();

		/**
		* @brief 获取调用进程的RAM使用量
		* @return 调用进程使用的内存字节数
		* @exception 
		* @note 
		*/
		static unsigned long long GetRAMUsage();

		/**
		* @brief 获取自某个点开始走过的时间
		* @return 从过去某个点开始到现在的毫秒数
		* @exception 
		* @note 单位为毫秒
		*/
		static unsigned long long GetTickCount();
	};
}

#endif
