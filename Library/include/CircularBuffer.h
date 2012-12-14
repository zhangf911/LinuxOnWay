#ifndef LIBRARY_CIRCULARBUFFER_H
#define LIBRARY_CIRCULARBUFFER_H

#include "BaseType.h"

#include <iostream>
using std::cout;
using std::endl;

namespace ZGF
{
	template <typename T>
	class CircularBuffer
	{
	private:
		T* m_pBuffer;
		T* m_writePos;
		T* m_readPos;
		T* m_endPos;
		UInt32 m_size;
	public:
		CircularBuffer(UInt32 INsize) : m_size(INsize)
		{
			m_pBuffer = new T[INsize];
			m_writePos = m_pBuffer;
			m_readPos = m_pBuffer;
			m_endPos = m_pBuffer + m_size - 1;
		}

		~CircularBuffer()
		{
			m_writePos = NULL;
			m_readPos = NULL;
			m_endPos = NULL;
			delete[] m_pBuffer;
		}

	public:
		bool IsFull()
		{
			return ((m_writePos - m_pBuffer) / sizeof(T) + 1) % m_size == (m_readPos - m_pBuffer) / sizeof(T);
		};

		bool IsEmpty()
		{
			return m_readPos == m_writePos;
		};

		void Push(const T& INpData)
		{
			if(IsFull())
			{
				return;
			}

			*m_writePos = INpData;
			// ∫Û“∆

			if(m_writePos < m_endPos)
			{
				++m_writePos;
				cout << "Write Pos : " << (int)m_writePos << endl;
			}
			else
			{
				m_writePos = m_pBuffer;
				cout << "Write Pos : " << (int)m_writePos << endl;
			}
		}

		T Pop()
		{
			if(!IsEmpty())
			{
				T* pData = m_readPos;
				if(m_readPos < m_endPos)
				{
					++m_readPos;
					cout << "Read Pos : " << (int)m_readPos << endl;
				}
				else
				{
					m_readPos = m_pBuffer;
					cout << "Read Pos : " << (int)m_readPos << endl;
				}
				return *pData;
			}
		}
	};
}

#endif