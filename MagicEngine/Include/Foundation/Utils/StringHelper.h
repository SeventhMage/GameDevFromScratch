#ifndef _MAGIC_STRING_HELPER_H_
#define _MAGIC_STRING_HELPER_H_

#include <string>
#include <vector>

using namespace std;

namespace Magic
{
	typedef vector<string> StringArray;
	class StringHelper
	{
	public:

		static string GetFileExtName(const char *filename);
		static StringArray Split(const string &str, const string &delims);
		static string Replace(const string &str, const string &src, const string &dst);
	};
}


#endif