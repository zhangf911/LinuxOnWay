#ifndef LIBRARY_TIMINGWHEEL_H
#define LIBRARY_TIMINGWHEEL_H

#include "BaseType.h"
#include "CircularBuffer.h"
#include <set>
using std::set;

namespace ZGF
{

	template <typename Entity>
	class TimingWheel
	{
	public:
		typedef set<Entity> WheelSlot;
		typedef WheelSlot::iterator WheelSlotIter;
	private:
		/** �̶����� **/
		UInt32 m_ticksPerWheel;
		/** �̶ȵ�λʱ�� **/
		UInt32 m_tickDuration;
		/** �̶��� **/
		CircularBuffer<WheelSlot> m_timingWheel;
	public:
		TimingWheel(UInt32 INtickDuration, UInt32 INticksPerWheel);

		~TimingWheel();
	};

}


#endif