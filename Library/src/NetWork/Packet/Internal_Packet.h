#ifndef _INTERNAL_PACKET_H
#define _INTERNAL_PACKET_H

#include "Packet.h"

class Internal_PacketFactory : public PacketFactory
{
public:
	virtual Packet* MallocPakcet(int nType);
	virtual void    FreePacket(Packet*) ;
	static Internal_PacketFactory* GetInstance();
};


class PacketSetupConnecion : public Packet
{
public:
	PacketSetupConnecion(int _id,int _checksum);
	virtual bool write(SimpleBuf& pBuf);
	virtual bool read(SimpleBuf& pBuf);
	virtual void process(void*);
	virtual int  GetSize();

	int GetConID()const{return m_nConID;}
	int GetCheckSum()const{return m_nCheckSum;}
private:
	int m_nConID;
	int m_nCheckSum;
};


#endif