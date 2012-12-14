#ifndef LIBRARY_UTIL_SYSTEMINFO_H
#define LIBRARY_UTIL_SYSTEMINFO_H

namespace ZGF{
	
	class SystemInfo
	{
	public:
		/**
		* @brief ���ص�ǰϵͳCPU����
		* @return ��ǰϵͳCPU����
		* @exception 
		* @note 
		*/
		static long GetCPUCount();

		/**
		* @brief ��ȡ���ý��̵�CPUռ��ʱ��
		* @return ���ý��̵�CPUռ��ʱ��
		* @exception 
		* @note ʱ������ں�ʱ����û�ʱ�䣬ʱ�䵥λΪ΢��
		*/
		static unsigned long long GetCPUUsage();

		/**
		* @brief ��ȡ���ý��̵�RAMʹ����
		* @return ���ý���ʹ�õ��ڴ��ֽ���
		* @exception 
		* @note 
		*/
		static unsigned long long GetRAMUsage();

		/**
		* @brief ��ȡ��ĳ���㿪ʼ�߹���ʱ��
		* @return �ӹ�ȥĳ���㿪ʼ�����ڵĺ�����
		* @exception 
		* @note ��λΪ����
		*/
		static unsigned long long GetTickCount();
	};
}

#endif
