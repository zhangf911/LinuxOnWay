#ifndef LIBRARY_BASE_SORT_H
#define LIBRARY_BASE_SORT_H

#include <math.h>
#include "BaseType.h"

namespace ZGF
{
	template<class DataType>
	bool Compare(DataType INleft, DataType INright)
	{
		if(INleft < INright)
		{
			return true;
		}

		return false;
	}

	template<class DataType>
	void swap(DataType* INleft, DataType* INright)
	{
		DataType temp = *INleft;
		*INleft = *INright;
		*INright = temp;
	}

	template<class DataType>
	void InsertSort(DataType* INdata, UInt32 INdataSize)
	{
		for(UInt32 i = 1; i < INdataSize; ++i)
		{
			DataType temp = INdata[i];
			//UInt index = i;
			Int32 k = i - 1;
			for(; k >= 0; --k)
			{
				if(temp < INdata[k])
				{
					INdata[k + 1] = INdata[k];
				}
				else
				{
					break;
				}
			}
			INdata[k + 1] = temp;
		}
	}

	template<class DataType>
	void SelectSort(DataType* INdata, UInt32 INdataSize)
	{
		for(UInt32 i = 0; i < INdataSize -1; ++i)
		{
			DataType temp = INdata[i];
			UInt32 pos = i;
			for(UInt32 k = i + 1; k < INdataSize; ++k)
			{
				if(temp > INdata[k])
				{
					temp = INdata[k];
					pos = k;
				}
			}
			swap(&INdata[i], &INdata[pos]);
		}
	}


	template<class DataType>
	void Merge(DataType* INdata, UInt32 INstart, UInt32 INmiddle, UInt32 INend)
	{
		UInt32 leftSize = INmiddle - INstart + 1;
		UInt32 rightSize = INend - INmiddle;

		DataType* leftArr = new DataType[leftSize];
		DataType* rightArr = new DataType[rightSize];

		for(UInt32 i = 0; i < leftSize; ++i)
		{
			leftArr[i] = INdata[INstart + i];
		}

		for(UInt32 k = 0; k < rightSize; ++k)
		{
			rightArr[k] = INdata[INmiddle + k + 1];
		}

		UInt32 pos = INstart;
		UInt32 i = 0, k = 0;
		for(; i < leftSize && k < rightSize;)
		{
			if(leftArr[i] <= rightArr[k])
			{
				INdata[pos++] = leftArr[i++];
			}
			else
			{
				INdata[pos++] = rightArr[k++];
			}
		}

		if(i == leftSize)
		{
			for(; k < rightSize;)
			{
				INdata[pos++] = rightArr[k++];
			}
		}
		else
		{
			for(; i < leftSize;)
			{
				INdata[pos++] = leftArr[i++];
			}
		}
	}

	template<class DataType>
	void CombineSort(DataType* INdata, UInt32 INstart, UInt32 INend)
	{
		if(INstart < INend)
		{
			UInt32 middle = (INstart + INend) / 2;
			CombineSort(INdata, INstart, middle);
			CombineSort(INdata, middle + 1, INend);
			Merge(INdata, INstart, middle, INend);
		}
	}

	template<class DataType>
	void InsertSortByRecursive(DataType* INdata, UInt32 INdataSize)
	{
		if(INdataSize == 1)
		{
			return;
		}
		else
		{
			InsertSortByRecursive(INdata, INdataSize - 1);
			DataType key = INdata[INdataSize - 1];
			Int32 i = INdataSize - 2;
			for(; i >= 0; --i)
			{
				if(key < INdata[i])
				{
					INdata[i + 1] = INdata[i];
				}
				else
				{
					break;
				}
			}
			INdata[i + 1] = key;
		}
	}

	typedef UInt32 pos_t;

	template <class DataType>
	UInt32 BinarySearch(DataType* INdata, UInt32 INsize, DataType INvalue)
	{
		UInt32 start = 0;
		UInt32 end = INsize - 1;
		UInt32 middle = (start + end) / 2;
		UInt32 pos = INsize;
		while(true) 
		{
			if(INdata[middle] == INvalue)
			{
				// 找到
				pos = middle;
				break;
			}
			else if(INdata[middle] > INvalue)
			{
				end = middle - 1;
			}
			else
			{
				start = middle + 1;
			}

			if(start > end)
			{
				// 未找到
				break;
			}

			middle = (start + end) / 2;
		}
		return pos + 1;
	}

#define PIN 0.0000001

	UInt32 BinarySearch(float* INdata, UInt32 INsize, float INvalue)
	{
		UInt32 start = 0;
		UInt32 end = INsize - 1;
		UInt32 middle = (start + end) / 2;
		UInt32 pos = INsize;
		while(true) 
		{
			if(abs(INdata[middle] - INvalue) < PIN)
			{
				// 找到
				pos = middle;
				break;
			}
			else if(INdata[middle] > INvalue)
			{
				end = middle - 1;
			}
			else
			{
				start = middle + 1;
			}

			if(start > end)
			{
				// 未找到
				break;
			}

			middle = (start + end) / 2;
		}
		return pos + 1;
	}
}



#endif