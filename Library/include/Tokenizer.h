#ifndef LIBRARY_UTIL_TOKENIZER_H
#define LIBRARY_UTIL_TOKENIZER_H

#include <algorithm>
#include <functional>
#include <string>
#include <vector>
using namespace std;

namespace ZGF
{
	class IsDelimiter : public unary_function<char, bool>
	{
	public:
		//Constructor specifying the separators
		IsDelimiter(string const & rostr) : m_ostr(rostr) {}
		bool operator()(char c) const
		{
			return m_ostr.find(c) != string::npos;
		}

	private:
		string m_ostr;
	};

	/**
	* @class Tokenizer
 
	* @exception 
	* @note 给定终结符分割字符串为单词数组
	*/
	class Tokenizer
	{
		IsDelimiter roPred;
		vector< string> tokens_;
		void Tokenize(string const & rostr)
		{
			string::const_iterator it, itTokenEnd;
			it = itTokenEnd = rostr.begin();
			while(it != rostr.end())
			{
				while(this->roPred(*it))
					++it;
				//Find next token

				itTokenEnd = find_if(it, rostr.end(), roPred);
				//Append token to result

				if(it < itTokenEnd)
					tokens_.push_back(string(it, itTokenEnd));
				it = itTokenEnd;
			}
		}
	public:
		typedef vector<string>::iterator iterator;
		Tokenizer(string const & input, string const & delimiter) : roPred(delimiter) { Tokenize(input); }
		iterator start() { return tokens_.begin(); }
		iterator end() { return tokens_.end(); }
	};
}

#endif
