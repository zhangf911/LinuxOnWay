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
		* @brief ��ȡ��ǰCPUʹ����
		* @return ��ǰCPUʹ����
		* @exception 
		* @note CPUʹ�ðٷֱ�
		*/
		float GetCurrentCPUUsage();

		/**
		* @brief ��ȡ��ǰ�ڴ�ռ��
		* @return ��ǰ�ڴ�ռ���ֽ���
		* @exception 
		* @note ��λΪ�ֽ�
		*/
		float GetCurrentRAMUsage();

	private:
		unsigned long cpu_count;             // The number of CPUs in this system  ( CPU cores count as separate CPUs )
		unsigned long long last_update;           // The time the last sample was created
		unsigned long long last_cpu_usage;   // The last sample of CPU usage
	};

}


#endif