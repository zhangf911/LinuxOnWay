/*
 * LRUCache.h
 *
 *  Created on: 2012-12-17
 *      Author: king
 */

#ifndef LRUCACHE_H_
#define LRUCACHE_H_

#include <map>
using std::map;

#include <deque>
using std::deque;

template <typename TKey, typename TValue>
class LRUCache
{
	typedef std::map<TKey, TValue> CacheMap;
	typedef CacheMap::iterator CacheMapIter;
	struct CacheNode
	{
		TKey key;
		UInt32 lastTime;
		UInt32 usedCount;
	};
	typedef std::deque<CacheNode> CacheNodeQueue;
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
		// ÅÐ¶ÏÊÇ·ñ³¬¹ýÏÞ¶¨»º´æ´óÐ¡
		if(m_cacheMap.size() < m_maxCacheCount)
		{
			// Ö±½Ó¼ÓÈë
			CacheMapIter it = m_cacheMap.find(INkey);
			if(it != m_cacheMap.end())
			{
				// INkeyÒÑ´æÔÚ
				return;
			}
			m_cacheMap[INkey] = INvalue;
		}
		else
		{
			// ÌÔÌ­×îÉÙÊ¹ÓÃ
			m_cacheNodeQueue.front();
		}
	};
};


#endif /* LRUCACHE_H_ */
