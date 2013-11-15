/****************************************************************************
Copyright (c) 2013 Omega-R company <omega-r.com>

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
****************************************************************************/

#include "ExtraFileUtils.h"

#if CC_TARGET_PLATFORM == CC_PLATFORM_LINUX
#include <dirent.h>
#include <unistd.h>
#include <stdio.h>

#elif CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
#include <dirent.h>
#endif

namespace {

class DirRAII
{
    DIR *d;
public:
    DirRAII(DIR *dir)
        : d(dir)
    {
    }

    ~DirRAII()
    {
        if (d)
            closedir(d);
    }

    operator DIR *() const
    {
        return d;
    }
};

}

std::vector<std::string> ExtraFileUtils::getDirectoryContent(const std::string &path,
                                                             const std::string &suffix)
{
    std::vector<std::string> ret;
#if CC_TARGET_PLATFORM == CC_PLATFORM_LINUX || CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
    do {
        CC_BREAK_IF(path.empty());
        std::string fixedPath = path;
        if (fixedPath.back() != '/')
            fixedPath += '/';

        DirRAII dir = opendir(fixedPath.c_str());
        CC_BREAK_IF(dir == NULL);

        for (;;) {
            dirent *entry = readdir(dir);
            CC_BREAK_IF(entry == NULL);
            if (DT_REG == entry->d_type) {
                std::string file = fixedPath + entry->d_name;
                size_t pos = file.find(suffix);
                if (pos + suffix.size() == file.size()) {
                    ret.push_back(file);
                }
            }
        }
    } while (0);
#endif
    return ret;
}

void ExtraFileUtils::removeFile(const std::string &path)
{
    if (0 != remove(path.c_str())) {
        CCLOG("Failed to remove file '%s'.", path.c_str());
    }
}
