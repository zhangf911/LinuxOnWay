#include "Internal_Packet.h"
#include "NetBuf.h"

enum
{
	Type_SetupConnection = 0,
};

Internal_PacketFactory* Internal_PacketFactory::GetInstance()
{
	static Internal_PacketFactory s_Instance;
	return &s_Instance;
}

Packet* Internal_PacketFactory::MallocPakcet( int nType )
{
	switch (nType)
	{
	case Type_SetupConnection:
		{
			return new PacketSetupConnecion(0,0);
		}
		break;
	default:
		break;
	}
	return NULL;
}

void Internal_PacketFactory::FreePacket( Packet* pPakcet)
{
	SAFE_DELETE(pPakcet);
}

PacketSetupConnecion::PacketSetupConnecion( int _id,int _checksum )
{
	m_type = Type_SetupConnection;
	m_nConID = _id;
	m_nCheckSum = _checksum;
}

bool PacketSetupConnecion::write( SimpleBuf& pBuf )
{
	bool bOK = pBuf.Write(&m_nConID,sizeof(m_nConID));
	bOK &= pBuf.Write(&m_nCheckSum,sizeof(m_nCheckSum));
	return bOK;
}

bool PacketSetupConnecion::read( SimpleBuf& pBuf )
{
	bool bOK = pBuf.Read(&m_nConID,sizeof(m_nConID));
	bOK &= pBuf.Read(&m_nCheckSum,sizeof(m_nCheckSum));
	return bOK;
}

void PacketSetupConnecion::process(void*)
{
}

int PacketSetupConnecion::GetSize()
{
	return sizeof(m_nConID) + sizeof(m_nCheckSum);
}
