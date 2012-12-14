#ifndef LIBRARY_STATE_H
#define LIBRARY_STATE_H

namespace ZGF
{

	enum TMsg
	{
		/** 默认超时时间：单位为秒 **/
		Default_Time_Out = 20,
	};

	struct MsgNode;

	template <class EntityType>
	class State
	{
	public:
		/**
		* @brief 进入状态
		**/
		virtual void Enter(EntityType* INentity) = 0;

		/**
		* @brief 执行事务
		**/
		virtual bool Execute(EntityType* INentity) = 0;

		/**
		* @brief 退出状态
		**/
		virtual void Exit(EntityType* INentity) = 0;

		/**
		* @brief 正常消息处理
		* @param INentity 对象实体
		* @param INmsgNode 消息包
		**/
		virtual bool HandleMessage(EntityType* INentity, const MsgNode& INmsgNode) = 0;

		/**
		* @brief 异常消息处理
		* @param INentity 对象实体
		* @param INmsgNode 消息包
		**/
		virtual bool HandleExMessage(EntityType* INentity, const MsgNode& INmsgNode) = 0;

		/**
		* @brief 获取状态编号
		**/
		virtual int GetStateID() = 0;
	};

}

#endif