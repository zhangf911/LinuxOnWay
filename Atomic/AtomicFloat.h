/*
 * AtomicFloat.h
 *
 *  Created on: 2012-12-14
 *      Author: king
 */

#ifndef ATOMICFLOAT_H_
#define ATOMICFLOAT_H_

#include "AtomicULong.h"

namespace LOW
{
	////////////////////////////////////////////////
	//class AtomicFloat
	//  Stores a Float atomically.
	//  Implemented using AtomicULong.
	//
	////////////////////////////////////////////////
	class AtomicFloat
	{
	public:
		AtomicFloat() : Value(0) {}

		AtomicFloat(float InitialValue)
		{
			unsigned long iv = *(reinterpret_cast< unsigned long* >(&InitialValue));
			Value.SetVal(iv);
		}


		////////////////////////////////////////////////////////////
		//float SetVal( float NewValue )
		// lockless threadsafe set operation on the contained value
		//
		// Parameters
		//  float val  -  value to be set
		//
		// Return values
		//  Returns the initial value contained
		///////////////////////////////////////////////////////////
		float SetVal(float NewValue);


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
		float GetVal();

	private:
		// Disabled copy constructor
		AtomicFloat(const AtomicFloat & other) {}

		// Disabled assignment operator
		AtomicFloat operator=(const AtomicFloat & other) { return *this; }

		AtomicULong Value;
	};
}


#endif /* ATOMICFLOAT_H_ */
