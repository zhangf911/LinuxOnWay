#ifndef LIBRARY_UTIL_COMPILEHELPER_H
#define LIBRARY_UTIL_COMPILEHELPER_H

#ifdef _DEBUG
#define CONFIG "Debug"
#else
#define CONFIG "Release"
#endif

#ifdef X64
#define ARCH "X64"
#else
#define ARCH "X86"
#endif

#ifdef _MSC_VER
#define COMPILER COMPILER_MICROSOFT

#if COMPILER == COMPILER_MICROSOFT
#define I64FMT "%016I64X"
#define I64FMTD "%I64u"
#define SI64FMTD "%I64d"
#define snprintf _snprintf
#define atoll __atoi64
#else
#define stricmp strcasecmp
#define strnicmp strncasecmp
#define I64FMT "%016llX"
#define I64FMTD "%llu"
#define SI64FMTD "%lld"
#endif


// fast int abs
static inline int int32abs(const int value)
{
	return (value ^ (value >> 31)) - (value >> 31);
}

// fast int abs and recast to unsigned
static inline unsigned int int32abs2uint32(const int value)
{
	return (unsigned int)(value ^ (value >> 31)) - (value >> 31);
}

/// Fastest Method of float2int32
static inline int float2int32(const float value)
{
#if !defined(X64) && COMPILER == COMPILER_MICROSOFT && !defined(USING_BIG_ENDIAN)
	int i;
	__asm
	{
		fld value
			frndint
			fistp i
	}
	return i;
#else
	union { int asInt[2]; double asDouble; } n;
	n.asDouble = value + 6755399441055744.0;

	return n.asInt [0];
#endif
}

/// Fastest Method of long2int32
static inline int long2int32(const double value)
{
#if !defined(X64) && COMPILER == COMPILER_MICROSOFT && !defined(USING_BIG_ENDIAN)
	int i;
	__asm
	{
		fld value
			frndint
			fistp i
	}
	return i;
#else
	union { int asInt[2]; double asDouble; } n;
	n.asDouble = value + 6755399441055744.0;

	return n.asInt [0];
#endif
}

#endif

#endif