#include "EnPacket.h"

namespace ZGF
{

	EnPacket::EnPacket()
	{
		m_data.clear();
		m_pos = 0;
	}

	EnPacket::EnPacket(const EnPacket& INinstance)
	{
		m_data = INinstance.m_data;
		m_pos = INinstance.m_data.size();
	}

	EnPacket::~EnPacket()
	{
		m_data.clear();
		m_pos = 0;
	}

	EnPacket& EnPacket::operator= (const EnPacket& INinstance)
	{
		m_data = INinstance.m_data;
		return *this;
	}

	void EnPacket::PushBool(bool INvalue)
	{
		PushData(&INvalue);
	}

	void EnPacket::PushChar(char INvalue)
	{
		PushData(&INvalue);
	}

	void EnPacket::PushUChar(unsigned char INvalue)
	{
		PushData(&INvalue);
	}

	void EnPacket::PushShort(short INvalue)
	{
		PushData(&INvalue);
	}

	void EnPacket::PushUShort(unsigned short INvalue)
	{
		PushData(&INvalue);
	}

	void EnPacket::PushInt(int INvalue)
	{
		PushData(&INvalue);
	}

	void EnPacket::PushUInt(unsigned int INvalue)
	{
		PushData(&INvalue);
	}

	void EnPacket::PushLong(long INvalue)
	{
		PushData(&INvalue);
	}

	void EnPacket::PushULong(unsigned long INvalue)
	{
		PushData(&INvalue);
	}

	void EnPacket::PushInt64(__int64 INvalue)
	{
		PushData(&INvalue);
	}

	void EnPacket::PushFloat(float INvalue)
	{
		PushData(&INvalue);
	}

	void EnPacket::PushDouble(double INvalue)
	{
		PushData(&INvalue);
	}

	void EnPacket::PushUInt64(unsigned __int64 INvalue)
	{
		PushData(&INvalue);
	}

	void EnPacket::PushString(const string& INdata)
	{
		PushString(INdata.c_str(), INdata.size());
	}

	void EnPacket::PushString(const char* INdata, UInt32 INdataSize)
	{
		PushData(INdata, INdataSize);
	}

	void EnPacket::Seekg(UInt32 INpos)
	{
		m_pos = INpos > m_data.size() ? m_data.size() : INpos;
	}	

	template <typename DataType>
	void EnPacket::PushData(DataType* INdata, UInt32 INdataSize /* = sizeof */)
	{
		if(m_pos == m_data.size())
		{
			m_data.append((char*)INdata, INdataSize);
			m_pos = m_data.size();
		}
		else
		{
			m_data.insert(m_pos, (char*)INdata, INdataSize);
		}
	}
}
