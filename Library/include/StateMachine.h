#ifndef LIBRARY_STATEMACHINE_H
#define LIBRARY_STATEMACHINE_H

#include "State.h"

namespace ZGF
{

	struct MsgNode;

	/**
	* @class StateMachine
	* @brief ״̬��
	**/
	template <class EntityType>
	class StateMachine
	{
	private:
		/** ������ **/
		EntityType* m_pOwner;
		/** ȫ��״̬ **/
		State<EntityType>* m_pGlobalState;
		/** ��ǰ״̬ **/
		State<EntityType>* m_pCurrentState;
		/** ǰһ״̬ **/
		State<EntityType>* m_pPreviousState;

	public:
		/**
		* @brief	���캯��
		* @param	INpOwner ������
		**/
		StateMachine(EntityType* INpOwner)
		{
			m_pOwner = INpOwner;
			m_pGlobalState = NULL;
			m_pCurrentState = NULL;
			m_pPreviousState = NULL;
		}

		/**
		* @brief	��������
		**/
		virtual ~StateMachine(){}

		/**
		* @brief	����ȫ��״̬
		* @param	INstate ״̬
		**/
		void SetGlobalState(State<EntityType>* INstate)
		{
			m_pGlobalState = INstate;
		}

		/**
		* @brief	���õ�ǰ״̬
		* @param	INstate ״̬
		**/
		void SetCurrentState(State<EntityType>* INstate)
		{
			m_pCurrentState = INstate;
		}

		/**
		* @brief	����ǰһ״̬
		* @param	INstate ״̬
		**/
		void SetPreviousState(State<EntityType>* INstate)
		{
			m_pPreviousState = INstate;
		}

		/**
		* @brief	��ȡȫ��״̬
		* @return	״̬
		**/
		State<EntityType>* GetGlobalState(void) const
		{
			return m_pGlobalState;
		}

		/**
		* @brief	��ȡ��ǰ״̬
		* @return	״̬
		**/
		State<EntityType>* GetCurrentState() const
		{
			return m_pCurrentState;
		}

		/**
		* @brief	��ȡǰһ״̬
		* @return	״̬
		**/
		State<EntityType>* GetPreviousState(void) const
		{
			return m_pPreviousState;
		}

		/**
		* @brief	����״̬��
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
		* @brief	��Ϣ����(ϵͳ��Ϣ)
		* @param	INmsgNode ��Ϣ�ṹ��
		* @return	true: �Ѵ���; false: δ����
		**/
		bool HandleMessage(const MsgNode& INmsgNode) const
		{
			// ����ǰ״̬��Ϣ
			if(m_pCurrentState && m_pCurrentState->HandleMessage(m_pOwner, INmsgNode))
			{
				return true;
			}

			// ����ȫ��״̬��Ϣ
			if(m_pGlobalState && m_pGlobalState->HandleMessage(m_pOwner, INmsgNode))
			{
				return true;
			}

			return false;
		}

		/**
		* @brief	�쳣��Ϣ����(ϵͳ��Ϣ)
		* @param	INmsgNode ��Ϣ�ṹ��
		* @return	true: �Ѵ���; false: δ����
		**/
		bool HandleExcMessage(const MsgNode& INmsgNode) const
		{
			// ����ǰ״̬��Ϣ
			if(m_pCurrentState && m_pCurrentState->HandleExcMessage(m_pOwner, INmsgNode))
			{
				return true;
			}

			// ����ȫ��״̬��Ϣ
			if(m_pGlobalState && m_pGlobalState->HandleExcMessage(m_pOwner, INmsgNode))
			{
				return true;
			}

			return false;
		}

		/**
		* @brief	��Ϣ����(�ͻ�����Ϣ)
		* @param	INmsgNode ��Ϣ�ṹ��
		* @param	INid ���
		* @return	true: �Ѵ���; false: δ����
		**/
		bool HandleMessage(const MsgNode& INmsgNode, int INid) const
		{
			// ����ǰ״̬��Ϣ
			if(m_pCurrentState && m_pCurrentState->HandleMessage(m_pOwner, INmsgNode, INid))
			{
				return true;
			}

			// ����ȫ��״̬��Ϣ
			if(m_pGlobalState && m_pGlobalState->HandleMessage(m_pOwner, INmsgNode, INid))
			{
				return true;
			}

			return false;
		}

		/**
		* @brief	�쳣��Ϣ����(�ͻ�����Ϣ)
		* @param	INmsgNode ��Ϣ�ṹ��
		* @param	INid ���
		* @return	true: �Ѵ���; false: δ����
		**/
		bool HandleExcMessage(const MsgNode& INmsgNode, int INid) const
		{
			// ����ǰ״̬��Ϣ
			if(m_pCurrentState && m_pCurrentState->HandleExcMessage(m_pOwner, INmsgNode, INid))
			{
				return true;
			}

			// ����ȫ��״̬��Ϣ
			if(m_pGlobalState && m_pGlobalState->HandleExcMessage(m_pOwner, INmsgNode, INid))
			{
				return true;
			}

			return false;
		}

		/**
		* @brief	�ı�״̬
		* @param	INpNewState ��״̬
		**/
		void ChangeState(State<EntityType>* INpNewState)
		{
			if(NULL == INpNewState)
			{
				return;
			}

			// ����״̬
			m_pPreviousState = m_pCurrentState;

			// �˳���ǰ״̬ʱ�Ĳ���
			m_pCurrentState->Exit(m_pOwner);

			// �ı䵱ǰ״̬
			m_pCurrentState = INpNewState;

			// ������״̬ʱ�Ĳ���
			m_pCurrentState->Enter(m_pOwner);
		}

		/**
		* @brief	�ָ�Ϊǰһ״̬
		**/
		void RevertToPreviousState()
		{
			ChangeState(m_pPreviousState);
		}

		/**
		* @brief	�жϵ�ǰ״̬
		* @param	INstate ״̬
		* @return	true: ��; false: ��
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