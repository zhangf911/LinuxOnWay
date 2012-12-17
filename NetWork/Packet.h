/*
 * Packet.h
 *
 *  Created on: 2012-12-17
 *      Author: king
 */

#ifndef PACKET_H_
#define PACKET_H_

struct SimpleBuf;

#define Packet_Prefix 0x20129011

struct Head
{
//	int nPrefiex;
	int nSize;
//	int nType;
};

class Packet
{
public:
	int GetType()const {return m_type;}
protected:
	int m_type;
public:
	virtual int  GetSize() = 0;
	virtual bool write(SimpleBuf& pBuf) = 0;
	virtual bool read(SimpleBuf& pBuf) = 0;
	virtual void process(void*) = 0;
};

class PacketFactory
{
public:
	virtual Packet* MallocPakcet(int nType) = 0;
	virtual void    FreePacket(Packet*) = 0;
};

#endif /* PACKET_H_ */
