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
		// 判断是否超过限定缓存大小
		if(m_cacheMap.size() < m_maxCacheCount)
		{
			// 直接加入
			CacheMapIter it = m_cacheMap.find(INkey);
			if(it != m_cacheMap.end())
			{
				// INkey已存在
				return;
			}
			m_cacheMap[INkey] = INvalue;
		}
		else
		{
			// 淘汰最少使用
			m_cacheNodeQueue.front();
		}
	};
};

#endif