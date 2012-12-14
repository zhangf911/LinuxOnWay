/*
 * AtomicBoolean.h
 *
 *  Created on: 2012-12-14
 *      Author: king
 */

#ifndef ATOMICBOOLEAN_H_
#define ATOMICBOOLEAN_H_

#include "AtomicULong.h"

namespace LOW
{
	class AtomicBoolean
	{

	public:
		AtomicBoolean() : Value(0) {}

		AtomicBoolean(bool val)
		{
			if(val)
				Value.SetVal(1);
			else
				Value.SetVal(0);
		}

		////////////////////////////////////////////////////////////
		//bool SetVal( bool val )
		// lockless threadsafe set operation on the contained value
		//
		// Parameters
		//  bool val  -  value to be set
		//
		// Return values
		//  Returns the initial value contained
		///////////////////////////////////////////////////////////
		bool SetVal(bool val);


		///////////////////////////////////////////////////////////
		//bool GetVal()
		// non-threadsafe get operation on the contained value
		//
		// Parameters
		//  None
		//
		// Return values
		//  Returns the value contained
		//////////////////////////////////////////////////////////
		bool GetVal()
		{
			unsigned long val = 0;

			val = Value.GetVal();

			return (val & 1);
		}

	private:
		// Disabled copy constructor
		AtomicBoolean(const AtomicBoolean & other) {}

		// Disabled assignment operator
		AtomicBoolean operator=(const AtomicBoolean & other) { return *this; }

		AtomicULong Value;
	};
}


#endif /* ATOMICBOOLEAN_H_ */
