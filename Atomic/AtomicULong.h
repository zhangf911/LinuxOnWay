/*
 * AtomicULong.h
 *
 *  Created on: 2012-12-14
 *      Author: king
 */

#ifndef ATOMICULONG_H_
#define ATOMICULONG_H_

namespace LOW
{
	class AtomicULong
	{
	public:
		AtomicULong() { Value = 0; }

		AtomicULong(unsigned long InitialValue) { Value = InitialValue; }

		unsigned long SetVal(unsigned long NewValue);

		unsigned long GetVal() { return Value; }


	private:
		// Disabled copy constructor
		AtomicULong(const AtomicULong & other) {}

		// Disabled assignment operator
		AtomicULong operator=(AtomicULong & other) { return *this; }

	protected:

	#ifdef WIN32
		__declspec(align(4))  volatile unsigned long Value;
	#else
		volatile unsigned long Value;
	#endif
	};
}


#endif /* ATOMICULONG_H_ */
