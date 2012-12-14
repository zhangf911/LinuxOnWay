#ifndef LIBRARY_UTIL_ATOMICULONG_H
#define LIBRARY_UTIL_ATOMICULONG_H

namespace ZGF
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

#endif
