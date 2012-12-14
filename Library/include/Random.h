#ifndef LIBRARY_RANDOM_RANDOM_H
#define LIBRARY_RANDOM_RANDOM_H

namespace ZGF
{
	//�õ�ǰ���Ӳ�������� 
	const unsigned long maxshort=65536L; 
	const unsigned long multiplier=1194211693L; 
	const unsigned long adder=12345L; 

	class RandomNumber 
	{ 
	private: 
		//������ӵ�˽�г�Ա 
		unsigned long randSeed; 
	public: 
		//���캯�� ��ȱʡֵ0��ʾϵͳ�Զ��������� 
		RandomNumber(unsigned long s=0); 
		//����0<=value�У��ò���0����ʱ�� ������һ���޷��ų�������32λ������ʾ�ӻ�׼ʱ�䣨1970.1.1.��ҹ����1904.1.1��ҹ�������Ѿ���ȥ�������� �κ�����²����������Ǿ޴���޷����ͳ�����.�������ߵ�ѡ�����Ǻ�������Ȼ����һ��ѡ������������� 
		RandomNumber::RandomNumber(unsigned long s) 
		{ 
			if(s==0) 
				randSeed=time(0);//ϵͳʱ�������� 
			else 
				randSeed=s; //�û��ṩ���� 
		} 

		//�ó����������µ��޷��ŵ����ӣ� randSeed=multiplier*randSeed+adder;
		unsigned short RandomNumber::Random(unsigned long n) 
		{ 
			randSeed=multiplier*randSeed+adder; 
			return (unsigned short)((randSeed>>16)%n); 
		} 

		double RandomNumber::fRandom(void) 
		{ 
			return Random(maxshort)/double(maxshort); 
		}
	};
}


#endif