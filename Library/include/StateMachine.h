#ifndef LIBRARY_STATEMACHINE_H
#define LIBRARY_STATEMACHINE_H

#include "State.h"

namespace ZGF
{

	struct MsgNode;

	/**
	* @class StateMachine
	* @brief 状态机
	**/
	template <class EntityType>
	class StateMachine
	{
	private:
		/** 所有者 **/
		EntityType* m_pOwner;
		/** 全局状态 **/
		State<EntityType>* m_pGlobalState;
		/** 当前状态 **/
		State<EntityType>* m_pCurrentState;
		/** 前一状态 **/
		State<EntityType>* m_pPreviousState;

	public:
		/**
		* @brief	构造函数
		* @param	INpOwner 所有者
		**/
		StateMachine(EntityType* INpOwner)
		{
			m_pOwner = INpOwner;
			m_pGlobalState = NULL;
			m_pCurrentState = NULL;
			m_pPreviousState = NULL;
		}

		/**
		* @brief	析构函数
		**/
		virtual ~StateMachine(){}

		/**
		* @brief	设置全局状态
		* @param	INstate 状态
		**/
		void SetGlobalState(State<EntityType>* INstate)
		{
			m_pGlobalState = INstate;
		}

		/**
		* @brief	设置当前状态
		* @param	INstate 状态
		**/
		void SetCurrentState(State<EntityType>* INstate)
		{
			m_pCurrentState = INstate;
		}

		/**
		* @brief	设置前一状态
		* @param	INstate 状态
		**/
		void SetPreviousState(State<EntityType>* INstate)
		{
			m_pPreviousState = INstate;
		}

		/**
		* @brief	获取全局状态
		* @return	状态
		**/
		State<EntityType>* GetGlobalState(void) const
		{
			return m_pGlobalState;
		}

		/**
		* @brief	获取当前状态
		* @return	状态
		**/
		State<EntityType>* GetCurrentState() const
		{
			return m_pCurrentState;
		}

		/**
		* @brief	获取前一状态
		* @return	状态
		**/
		State<EntityType>* GetPreviousState(void) const
		{
			return m_pPreviousState;
		}

		/**
		* @brief	更新状态机
		**/
		void Update() const
		{
			if(m_pGlobalState)
			{
				m_pGlobalState->Execute(m_pOwner);
			}

			if(m_pCurrentState)
			{
				m_pCurrentState->Execute(m_pOwner);
			}
		}

		/**
		* @brief	消息处理(系统消息)
		* @param	INmsgNode 消息结构体
		* @return	true: 已处理; false: 未处理
		**/
		bool HandleMessage(const MsgNode& INmsgNode) const
		{
			// 处理当前状态消息
			if(m_pCurrentState && m_pCurrentState->HandleMessage(m_pOwner, INmsgNode))
			{
				return true;
			}

			// 处理全局状态消息
			if(m_pGlobalState && m_pGlobalState->HandleMessage(m_pOwner, INmsgNode))
			{
				return true;
			}

			return false;
		}

		/**
		* @brief	异常消息处理(系统消息)
		* @param	INmsgNode 消息结构体
		* @return	true: 已处理; false: 未处理
		**/
		bool HandleExcMessage(const MsgNode& INmsgNode) const
		{
			// 处理当前状态消息
			if(m_pCurrentState && m_pCurrentState->HandleExcMessage(m_pOwner, INmsgNode))
			{
				return true;
			}

			// 处理全局状态消息
			if(m_pGlobalState && m_pGlobalState->HandleExcMessage(m_pOwner, INmsgNode))
			{
				return true;
			}

			return false;
		}

		/**
		* @brief	消息处理(客户端消息)
		* @param	INmsgNode 消息结构体
		* @param	INid 编号
		* @return	true: 已处理; false: 未处理
		**/
		bool HandleMessage(const MsgNode& INmsgNode, int INid) const
		{
			// 处理当前状态消息
			if(m_pCurrentState && m_pCurrentState->HandleMessage(m_pOwner, INmsgNode, INid))
			{
				return true;
			}

			// 处理全局状态消息
			if(m_pGlobalState && m_pGlobalState->HandleMessage(m_pOwner, INmsgNode, INid))
			{
				return true;
			}

			return false;
		}

		/**
		* @brief	异常消息处理(客户端消息)
		* @param	INmsgNode 消息结构体
		* @param	INid 编号
		* @return	true: 已处理; false: 未处理
		**/
		bool HandleExcMessage(const MsgNode& INmsgNode, int INid) const
		{
			// 处理当前状态消息
			if(m_pCurrentState && m_pCurrentState->HandleExcMessage(m_pOwner, INmsgNode, INid))
			{
				return true;
			}

			// 处理全局状态消息
			if(m_pGlobalState && m_pGlobalState->HandleExcMessage(m_pOwner, INmsgNode, INid))
			{
				return true;
			}

			return false;
		}

		/**
		* @brief	改变状态
		* @param	INpNewState 新状态
		**/
		void ChangeState(State<EntityType>* INpNewState)
		{
			if(NULL == INpNewState)
			{
				return;
			}

			// 保存状态
			m_pPreviousState = m_pCurrentState;

			// 退出当前状态时的操作
			m_pCurrentState->Exit(m_pOwner);

			// 改变当前状态
			m_pCurrentState = INpNewState;

			// 进入新状态时的操作
			m_pCurrentState->Enter(m_pOwner);
		}

		/**
		* @brief	恢复为前一状态
		**/
		void RevertToPreviousState()
		{
			ChangeState(m_pPreviousState);
		}

		/**
		* @brief	判断当前状态
		* @param	INstate 状态
		* @return	true: 是; false: 否
		**/
		bool IsInState(State<EntityType>* INstate) const
		{
			if(m_pCurrentState->GetStateID() == INstate->GetStateID())
			{
				return true;
			}

			return false;
		}
	};
}


#endif