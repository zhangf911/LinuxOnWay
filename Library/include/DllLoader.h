#ifndef LIBRARY_UTIL_DLLLOADER_H
#define LIBRARY_UTIL_DLLLOADER_H

#include <string>

namespace ZGF
{
	class DllLoader
	{
	private:
		/** ��̬������ **/
		std::string filename;
		/** ��̬����ڵ�ַ **/
		void *lptr;
		/** ������״̬ **/
		bool error;
	public:
		/**
		* @brief ���캯��
		* @param dll�ļ�·����
		* @exception 
		* @note 
		*/
		DllLoader( const char *libfilename = "" );

		/**
		* @brief ��������
		* @exception 
		* @note 
		*/
		~DllLoader();

		/**
		* @brief ���ض�̬���ӿ�
		* @return true : �ɹ� false : ʧ��
		* @exception 
		* @note 
		*/
		bool Load();

		/**
		* @brief ж�ض�̬��
		* @exception 
		* @note 
		*/
		void Close();

		/**
		* @brief ��ȡ�ӿڵ�ַ
		* @param �ӿ�����
		* @return �ӿڵ�ַ
		* @exception 
		* @note 
		*/
		void* GetAddressForSymbol( const char *symbol );

		/**
		* @brief ��ȡ������״̬
		* @return ������״̬
		* @exception 
		* @note ��ȡ����״̬������Ϊfalse
		*/
		bool Error()
		{
			bool lasterror = error;

			error = false;

			return lasterror;
		}
		
		/**
		* @brief ��ȡ��̬������
		* @return ��̬������
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