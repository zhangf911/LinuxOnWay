#ifndef LIBRARY_STATE_H
#define LIBRARY_STATE_H

namespace ZGF
{

	enum TMsg
	{
		/** Ĭ�ϳ�ʱʱ�䣺��λΪ�� **/
		Default_Time_Out = 20,
	};

	struct MsgNode;

	template <class EntityType>
	class State
	{
	public:
		/**
		* @brief ����״̬
		**/
		virtual void Enter(EntityType* INentity) = 0;

		/**
		* @brief ִ������
		**/
		virtual bool Execute(EntityType* INentity) = 0;

		/**
		* @brief �˳�״̬
		**/
		virtual void Exit(EntityType* INentity) = 0;

		/**
		* @brief ������Ϣ����
		* @param INentity ����ʵ��
		* @param INmsgNode ��Ϣ��
		**/
		virtual bool HandleMessage(EntityType* INentity, const MsgNode& INmsgNode) = 0;

		/**
		* @brief �쳣��Ϣ����
		* @param INentity ����ʵ��
		* @param INmsgNode ��Ϣ��
		**/
		virtual bool HandleExMessage(EntityType* INentity, const MsgNode& INmsgNode) = 0;

		/**
		* @brief ��ȡ״̬���
		**/
		virtual int GetStateID() = 0;
	};

}

#endif