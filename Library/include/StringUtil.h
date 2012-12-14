#ifndef LIBRARY_STRING_UTIL_H
#define LIBRARY_STRING_UTIL_H

#include "Singleton.h"

#include <string>

namespace ZGF
{
	class StringUtil : public Singleton<StringUtil>
	{
		friend class Singleton<StringUtil>;
	public:
		static void Tolower(std::string & str)
		{
			for(size_t i = 0; i < str.length(); ++i)
				str[i] = (char)tolower(str[i]);
		}

		static void ToUpper(std::string & str)
		{
			for(size_t i = 0; i < str.length(); ++i)
				str[i] = (char)toupper(str[i]);
		}

		template <char INsplitchar>
		static bool NotSplitchar(char INchar)
		{
			return (INchar != INsplitchar) ? true : false;
		}

		template <char INsplitchar>
		static bool Splitchar(char INchar)
		{
			return (INchar == INsplitchar) ? true : false;
		}

		template<char INsplitchar>
		static void Split(const string &s, vector<string>& OUTtargetVector)   
		{  
			typedef string::const_iterator iter;

			iter i = s.begin();   
			while (i != s.end()) {   
				i = find_if(i, s.end(), NotSplitchar<INsplitchar>);   

				iter j = find_if(i, s.end(), Splitchar<INsplitchar>);   

				// »ñÈ¡×Ö·û´®
				if (i != j) {
					OUTtargetVector.push_back(string(i, j));   
					i = j;   
				}
			}
		}

		static unsigned int MakeIP(const char* str)
		{
			unsigned int bytes[4];
			unsigned int res;
			if(sscanf(str, "%u.%u.%u.%u", &bytes[0], &bytes[1], &bytes[2], &bytes[3]) != 4)
				return 0;

			res = bytes[0] | (bytes[1] << 8) | (bytes[2] << 16) | (bytes[3] << 24);
			return res;
		}
	private:

		StringUtil(){};

		~StringUtil(){};

		StringUtil(const StringUtil& INinstance);
	};
}



#endif