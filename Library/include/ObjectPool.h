#ifndef LIBRARY_BASE_OBJECTPOOL_H
#define LIBRARY_BASE_OBJECTPOOL_H

#include "BaseType.h"
#include "Lock.h"
#include <cassert>
#include <iostream>
#include <list>
#include <vector>
#include <algorithm>
using std::cout;
using std::endl;
using std::list;
using std::vector;

namespace ZGF
{
	template <class Object>
	class ObjectPool
	{
		typedef list<Object*> ObjectList;
		typedef typename ObjectList::iterator ObjectListIter;
		typedef vector<Object*> ObjectVector;
		typedef typename ObjectVector::iterator ObjectVectorIter;
	private:

		/** ����� **/
		char* m_objectPool;
		/** �����б��� **/
		CriticalSection m_objectListLock;
		/** �����б� **/
		ObjectList m_objectList;
		/** �����б� **/
		ObjectVector m_backupVector;
		/** ���ö����� **/
		UInt32 m_usedCount;
		/** �������� **/
		UInt32 m_maxObjectBufferCount;
	public:
		ObjectPool()
		{
			m_objectPool = NULL;
			m_objectList.clear();
			m_usedCount = 0;
		}

		~ObjectPool()
		{
			Destroy();
		}

		bool Initial(UInt32 INobjectCount)
		{
			MyASSERT(INobjectCount > 0);
			m_maxObjectBufferCount = INobjectCount;
			if(m_objectPool != NULL)
			{
				Destroy();
			}
			try
			{
				m_objectPool = new char[INobjectCount * sizeof(Object)];
			}
			catch(...)
			{
				return false;
			}
			// �з�
			for(UInt32 i = 0; i < INobjectCount; ++i)
			{
				Object* pObject = (Object*)(m_objectPool + i * sizeof(Object));
				m_objectList.push_back(pObject);
				m_backupVector.push_back(pObject);
			}
			return true;
		}

		Object* GetNewObject()
		{
			Object* pObject = NULL;
			Guard<CriticalSection> monitor(&m_objectListLock);
			if(m_objectList.size())
			{
				pObject = m_objectList.front();
				m_objectList.pop_front();
				new (pObject) Object;
				++m_usedCount;

				//cout << "GetNewObject, current used :" << m_usedCount << endl;
				//cout << "Free Object Count Is : " << m_objectList.size() << endl;
			}
			else
			{
				pObject = CreateObject();
			}
			
			return pObject;
		}

		void FreeObject(Object* INobject)
		{
			if(IsInPool(INobject))
			{
				// ����
				INobject->~Object();
				Guard<CriticalSection> monitor(&m_objectListLock);
				// �����б�
				m_objectList.push_back(INobject);
				--m_usedCount;

				//cout << "Free Object Count Is : " << m_objectList.size() << endl;
				//cout << "FreeObject, current used :" << m_usedCount << endl;
			}
			else
			{
				delete INobject;

				NOTE_LOG("�����������");
			}
			
		}

		UInt32 CurrentUsedCount()
		{
			return m_usedCount;
		}

	private:
		bool IsInPool(Object* INobject)
		{
			auto it = find(m_backupVector.begin(), m_backupVector.end(), INobject);
			if(it != m_backupVector.end())
			{
				return true;
			}
			//if((int)INobject >= (int)m_objectPool && (int)INobject <= (int)(m_objectPool + (m_maxObjectBufferCount -1) * sizeof(Object)))
			//{
			//	return true;
			//}
			return false;
		}

		Object* CreateObject()
		{
			try
			{
				Object* pObject = new Object();

				return pObject;
			}
			catch(...)
			{
				return NULL;
			}
		}

		void Destroy()
		{
			//assert(m_usedCount == 0);
			// ��������Ƿ��ж����ⲿʹ��
			if(m_usedCount != 0)
			{
				//throw "destroy exception, some objects in pool is uesd outside;";
			}
			// ��������б�
			for(ObjectListIter it = m_objectList.begin(); it != m_objectList.end(); ++it)
			{
				//
			}
			m_objectList.clear();
			// ���ٶ����
			if(m_objectPool != NULL)
			{
				delete m_objectPool;
			}
		}
	};
}

#endif