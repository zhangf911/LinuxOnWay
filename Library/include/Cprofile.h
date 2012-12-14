#ifndef LIBRARY_UTIL_CPROFILE_H
#define LIBRARY_UTIL_CPROFILE_H

#include <windows.h>
#include <string>
using namespace std;

/** �����ֵ **/
#define MAX_INT 0xffffffff
/** ������Ϣ **/
#define ERROR_STRING "Read string error!"
/** ��ֵ�໺������С **/
#define NUM_BUFFER_SIZE 32
/** �ַ�����������С **/
#define STRING_BUFFER_SIZE 256
/** ���������� **/
#define FLOAT_PRECISE 10
/** ��д�Ľ����� **/
#define RADIX_SIZE 10

/** INTPYE��ȡֵ **/
#define PROFILE_CHAR 0
#define PROFILE_UCHAR 1
#define PROFILE_SINT 2
#define PROFILE_USINT 3
#define PROFILE_INT 4
#define PROFILE_UINT 5
#define PROFILE_LONG 6
#define PROFILE_ULONG 7
#define PROFILE_FLOAT 8
#define PROFILE_DOUBLE 9
#define PROFILE_BOOL 10
#define PROFILE_STRING 11
#define PROFILE_CHARPTR 12

namespace ZGF
{
	/**
	* @class Cprofile
	* @brief �����ļ��Ķ�д
	*/
	class Cprofile
	{
	private:
		/** �����ļ����� **/
		string fileName;

	public:

		/**
		* @brief Ĭ�ϳ�ʼ��
		* @param INfileName : �����ļ�����
		* @note 
		*/
		Cprofile(const char* INfileName);

		/**
		* @brief ��ȡ�޷���������ֵ
		* @param const char* INsegName: ����
		* @param const char* INkeyName: ��ֵ��
		* @param bool* OUTvalue: ��ֵ
		* @return ����true��ʾ�ɹ�,����false��ʾʧ��
		* @note ��ȡtrue����false, ���������ʹ���������Ͷ�ȡ,ֻ�ܶ�ȡȫ����д����Сд
		*/
		bool ReadBOOL(const char* INsegName, const char* INkeyName, bool* OUTvalue);

		/**
		* @brief ��ȡ�޷����ַ���ֵ
		* @param const char* INsegName: ����
		* @param const char* INkeyName: ��ֵ��
		* @param unsigned char * OUTvalue: ��ֵ
		* @return ����true��ʾ�ɹ�,����false��ʾʧ��
		* @note 
		*/
		bool ReadUChar(const char* INsegName, const char* INkeyName, unsigned char* OUTvalue);

		/**
		* @brief ��ȡ�ַ���ֵ
		* @param const char* INsegName: ����
		* @param const char* INkeyName: ��ֵ��
		* @param char * OUTvalue: ��ֵ
		* @return ����true��ʾ�ɹ�,����false��ʾʧ��
		* @note 
		*/
		bool ReadChar(const char* INsegName, const char* INkeyName, char* OUTvalue);
		
		/**
		* @brief ��ȡ�޷��Ŷ�������ֵ
		* @param const char* INsegName: ����
		* @param const char* INkeyName: ��ֵ��
		* @param unsigned short int* OUTvalue: ��ֵ
		* @return ����true��ʾ�ɹ�,����false��ʾʧ��
		* @note 
		*/
		bool ReadUSINT(const char* INsegName, const char* INkeyName, unsigned short int* OUTvalue);
	
		/**
		* @brief ��ȡ��������ֵ
		* @param const char* INsegName: ����
		* @param const char* INkeyName: ��ֵ��
		* @param short int* OUTvalue: ��ֵ
		* @return ����true��ʾ�ɹ�,����false��ʾʧ��
		* @note 
		*/
		bool ReadSINT(const char* INsegName, const char* INkeyName, short int* OUTvalue);

		/**
		* @brief ��ȡ�޷���������ֵ
		* @param const char* INsegName: ����
		* @param const char* INkeyName: ��ֵ��
		* @param unsigned int* OUTvalue: ��ֵ
		* @return ����true��ʾ�ɹ�,����false��ʾʧ��
		* @note 
		*/
		bool ReadUINT(const char* INsegName, const char* INkeyName, unsigned int* OUTvalue);

		/**
		* @brief ��ȡ������ֵ
		* @param const char* INsegName: ����
		* @param const char* INkeyName: ��ֵ��
		* @param int* OUTvalue: ��ֵ
		* @return ����true��ʾ�ɹ�,����false��ʾʧ��
		* @note 
		*/
		bool ReadINT(const char* INsegName, const char* INkeyName, int* OUTvalue);

		/**
		* @brief ��ȡ�޷��ų�������ֵ
		* @param const char* INsegName: ����
		* @param const char* INkeyName: ��ֵ��
		* @param unsigned long* OUTvalue: ��ֵ
		* @return ����true��ʾ�ɹ�,����false��ʾʧ��
		* @note 
		*/
		bool ReadULONG(const char* INsegName, const char* INkeyName, unsigned long* OUTvalue);

		/**
		* @brief ��ȡ��������ֵ
		* @param const char* INsegName: ����
		* @param const char* INkeyName: ��ֵ��
		* @param long* OUTvalue: ��ֵ
		* @return ����true��ʾ�ɹ�,����false��ʾʧ��
		* @note 
		*/
		bool ReadLONG(const char* INsegName, const char* INkeyName, long* OUTvalue);

		/**
		* @brief ��ȡ�����ȸ����ͼ�ֵ
		* @param const char* INsegName: ����
		* @param const char* INkeyName: ��ֵ��
		* @param float* OUTvalue: ��ֵ
		* @return ����true��ʾ�ɹ�,����false��ʾʧ��
		* @note 
		*/
		bool ReadFloat(const char* INsegName, const char* INkeyName, float* OUTvalue);

		/**
		* @brief ��ȡ˫���ȸ����ͼ�ֵ
		* @param const char* INsegName: ����
		* @param const char* INkeyName: ��ֵ��
		* @param double* OUTvalue: ��ֵ
		* @return ����true��ʾ�ɹ�,����false��ʾʧ��
		* @note 
		*/
		bool ReadDouble(const char* INsegName, const char* INkeyName, double* OUTvalue);

		/**
		* @brief ��ȡ�ַ�����ֵ
		* @param const char* INsegName: ����
		* @param const char* INkeyName: ��ֵ��
		* @param string* OUTvalue: �����ַ���
		* @return ����true��ʾ�ɹ�,����false��ʾʧ��
		* @note 
		*/
		bool ReadString(const char* INsegName, const char* INkeyName, string* OUTvalue);
		
		/**
		* @brief ��ȡ�ַ�����ֵ
		* @param const char* INsegName: ����
		* @param const char* INkeyName: ��ֵ��
		* @param char** OUTvalue: �����ַ���
		* @param int* OUTstrLen: �����ַ�������
		* @return ����true��ʾ�ɹ�,����false��ʾʧ��
		* @note 
		*/
		bool ReadString(const char* INsegName, const char* INkeyName, char** OUTvalue, int* OUTstrLen);

		/**
		* @brief д���ַ������͵ļ�ֵ
		* @param const char* INsegName: ����
		* @param const char* INkeyName: ��ֵ��
		* @param const string& INstr: Ҫд����ַ���
		* @return ����true��ʾ�ɹ�,����false��ʾʧ��
		* @note 
		*/
		bool WriteKeyString(const char* INsegName, const char* INkeyName, const string& INstr);

		/**
		* @brief д���ַ������͵ļ�ֵ
		* @param const char* INsegName: ����
		* @param const char* INkeyName: ��ֵ��
		* @param const char* INstr: Ҫд����ַ���
		* @param int INsize: �ַ�������
		* @return ����true��ʾ�ɹ�,����false��ʾʧ��
		* @note 
		*/
		bool WriteKeyString(const char* INsegName, const char* INkeyName, const char* INstr, int INsize);

		/**
		* @brief д���ֵ
		* @param const char* INsegName: ����
		* @param const char* INkeyName: ��ֵ��
		* @param T INvalue: д�����ֵ
		* @param int INtype: T������
		* @param int INptrLen = 0: �ַ�������
		* @return ����true��ʾ�ɹ�,����false��ʾʧ��
		* @note 
		*/
		template<typename T>
		bool WriteKeyValue(const char* INsegName, const char* INkeyName, T INvalue, int INtype, int INptrLen = 0)
		{
			try
			{
				string strBuffer;
				strBuffer.erase();
				char str[STRING_BUFFER_SIZE];
				switch(INtype)
				{
				case PROFILE_BOOL:
					if(INvalue)
					{
						strBuffer = "TRUE";
					}
					else
					{
						strBuffer = "FALSE";
					}
					break;
				case PROFILE_CHAR:
				case PROFILE_UCHAR:
					strBuffer = INvalue;
					break;
				case PROFILE_INT:
				case PROFILE_UINT:
				case PROFILE_SINT:
				case PROFILE_USINT:
					itoa((int)INvalue, str, RADIX_SIZE);
					strBuffer = str;
					break;
				case PROFILE_LONG:
				case PROFILE_ULONG:
					ltoa((long)INvalue, str, RADIX_SIZE);
					strBuffer = str;
					break;
				case PROFILE_FLOAT:
				case PROFILE_DOUBLE:
					gcvt((double)INvalue, FLOAT_PRECISE, str);
					strBuffer = str;
					break;
				default:
					break;
				}
				if(!WritePrivateProfileString((LPCSTR)INsegName, (LPCSTR)INkeyName, (LPSTR)strBuffer.c_str(), (LPCSTR)fileName.c_str()))
				{
					return false;
				}
			}
			catch(...)
			{
				return false;
			}
			return true;
		}
	};
}


#endif