#ifndef LIBRARY_LRUCACHE_H
#define LIBRARY_LRUCACHE_H

#include <hash_map>
using stdext::hash_map;

#include <queue>
using std::queue;

template <typename TKey, typename TValue>
class LRUCache
{
	typedef hash_map<TKey, TValue> CacheMap;
	typedef CacheMap::iterator CacheMapIter;
	struct CacheNode
	{
		TKey key;
		UInt32 lastTime;
		UInt32 usedCount;
	};
	typedef queue<CacheNode> CacheNodeQueue;
private:
	CacheNodeQueue m_cacheNodeQueue;
	CacheMap m_cacheMap;
	UInt32 m_maxCacheCount;

public:
	LRUCache();

	~LRUCache();

public:
	void AddCache(TKey INkey, TValue INvalue)
	{
		// �ж��Ƿ񳬹��޶������С
		if(m_cacheMap.size() < m_maxCacheCount)
		{
			// ֱ�Ӽ���
			CacheMapIter it = m_cacheMap.find(INkey);
			if(it != m_cacheMap.end())
			{
				// INkey�Ѵ���
				return;
			}
			m_cacheMap[INkey] = INvalue;
		}
		else
		{
			// ��̭����ʹ��
			m_cacheNodeQueue.front();
		}
	};
};

#endif