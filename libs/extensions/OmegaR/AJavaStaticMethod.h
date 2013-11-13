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

#ifndef __cocos2d_AJavaStaticMethod__
#define __cocos2d_AJavaStaticMethod__

#include "cocos2d.h"

#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID

#include <vector>
#include <string>
#include <jni.h>
#include <jni/JniHelper.h>
#include <android/log.h>

/// This class encapsulates Java static method call.
/// Nothing bad happens if called Java method not found,
/// it just prints debug message to log and returns default value.
class AJavaStaticMethod
{
public:
    explicit AJavaStaticMethod(const char *className,
                               const char *methodName,
                               const char *signature);
    ~AJavaStaticMethod();

    std::vector<std::string> callStringVector(int, ...);
    std::string callString(int, ...);
    void callVoid(int, ...);
    bool callBool(int, ...);
    double callDouble(int, ...);
    float callFloat(int, ...);

    /// Creates future call argument from string.
    jstring arg(const std::string &string);

    /// Creates future call argument from strings list.
    jobjectArray arg(const std::vector<std::string> &list);

private:
    std::vector<jobject> m_arguments;
    cocos2d::JniMethodInfo m_methodInfo;
    bool m_isValid;
};

#endif

#endif /* defined(__cocos2d_AJavaStaticMethod__) */
