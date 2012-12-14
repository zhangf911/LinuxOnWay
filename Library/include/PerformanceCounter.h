#ifndef LIBRARY_UTIL_PERFORMANCECOUNTER_H
#define LIBRARY_UTIL_PERFORMANCECOUNTER_H

namespace ZGF
{
	class PerformanceCounter
	{
	public:
		PerformanceCounter();

		~PerformanceCounter(){}

		/**
		* @brief 获取当前CPU使用率
		* @return 当前CPU使用率
		* @exception 
		* @note CPU使用百分比
		*/
		float GetCurrentCPUUsage();

		/**
		* @brief 获取当前内存占用
		* @return 当前内存占用字节数
		* @exception 
		* @note 单位为字节
		*/
		float GetCurrentRAMUsage();

	private:
		unsigned long cpu_count;             // The number of CPUs in this system  ( CPU cores count as separate CPUs )
		unsigned long long last_update;           // The time the last sample was created
		unsigned long long last_cpu_usage;   // The last sample of CPU usage
	};

}


#endif