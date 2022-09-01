#include <cstring>
#include "Foundation/Utils/StringHelper.h"

namespace Magic
{
	string StringHelper::GetFileExtName(const char *filename)
	{
		const char *pLastPoint = strrchr(filename, '.');
		if (pLastPoint)
		{
			return string(pLastPoint + 1);
		}
		return "";
	}

	StringArray StringHelper::Split(const string &str, const string &delims)
	{
		StringArray strRet;
		size_t start = 0, pos = 0;
		do
		{
			pos = str.find_first_of(delims, start);
			if (pos == start)
			{
				start = pos + 1;
			}
			else if (pos == string::npos)
			{
				strRet.push_back(str.substr(start));
				break;
			}
			else
			{
				strRet.push_back(str.substr(start, pos - start));
				start = pos + 1;
			}

			start = str.find_first_not_of(delims, start);

		} while (pos != string::npos);

		return strRet;
	}
	string StringHelper::Replace(const string &str, const string &src, const string &dst)
	{
		if (src == dst)
			return str;
		string out = str;
		size_t pos = str.find(src, 0);
		while (pos != string::npos)
		{
			out.replace(pos, src.size(), dst);
			pos = out.find(src, pos + dst.size());
		}
		return out;
	}
}