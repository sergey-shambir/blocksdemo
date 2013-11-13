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

#include "AJavaStaticMethod.h"

#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR, "BlocksDemo", __VA_ARGS__)

#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID

using namespace cocos2d;

AJavaStaticMethod::AJavaStaticMethod(const char *className,
                                     const char *methodName,
                                     const char *signature)
: m_isValid(false)
{
    m_isValid = JniHelper::getStaticMethodInfo(m_methodInfo,
                                               className,
                                               methodName,
                                               signature);
    if (!m_isValid) {
        LOGE("%s %d: failed to get m_methodInfo for method %s::%s%s", __FILE__, __LINE__, className, methodName, signature);
    }
}

AJavaStaticMethod::~AJavaStaticMethod()
{
    if (m_isValid) {
        for (jobject object : m_arguments)
        {
            m_methodInfo.env->DeleteLocalRef(object);
        }
        m_methodInfo.env->DeleteLocalRef(m_methodInfo.classID);
    }
}

std::vector<std::string> AJavaStaticMethod::callStringVector(int dummy, ...)
{
    std::vector<std::string> result;
    if (m_isValid) {
        va_list args;
        va_start(args, dummy);
        auto content = (jobjectArray)m_methodInfo.env->CallStaticObjectMethodV(m_methodInfo.classID, m_methodInfo.methodID, args);
        va_end(args);

        const int length = m_methodInfo.env->GetArrayLength(content);
        for (int i = 0; i < length; ++i)
        {
            jstring jFileName = (jstring)m_methodInfo.env->GetObjectArrayElement(content, i);
            if (const char *fileName = m_methodInfo.env->GetStringUTFChars(jFileName, NULL))
            {
                result.push_back(fileName);
                m_methodInfo.env->ReleaseStringUTFChars(jFileName, fileName);
            }
            m_methodInfo.env->DeleteLocalRef(jFileName);
        }
    }
    return result;
}

std::string AJavaStaticMethod::callString(int dummy, ...)
{
    std::string result;
    if (m_isValid) {
        va_list args;
        va_start(args, dummy);
        jstring javaResult = (jstring)m_methodInfo.env->CallStaticObjectMethodV(m_methodInfo.classID, m_methodInfo.methodID, args);
        result = JniHelper::jstring2string(javaResult);
        m_methodInfo.env->DeleteLocalRef(javaResult);
        va_end(args);
    }
    return result;
}

void AJavaStaticMethod::callVoid(int dummy, ...)
{
    if (m_isValid) {
        va_list args;
        va_start(args, dummy);
        m_methodInfo.env->CallStaticVoidMethodV(m_methodInfo.classID, m_methodInfo.methodID, args);
        va_end(args);
    }
}

bool AJavaStaticMethod::callBool(int dummy, ...)
{
    bool result = false;
    if (m_isValid) {
        va_list args;
        va_start(args, dummy);
        result = m_methodInfo.env->CallStaticBooleanMethodV(m_methodInfo.classID, m_methodInfo.methodID, args);
        va_end(args);
    }
    return result;
}

double AJavaStaticMethod::callDouble(int dummy, ...)
{
    double result = 0.0;
    if (m_isValid) {
        va_list args;
        va_start(args, dummy);
        result = m_methodInfo.env->CallStaticDoubleMethodV(m_methodInfo.classID, m_methodInfo.methodID, args);
        va_end(args);
    }
    return result;
}

float AJavaStaticMethod::callFloat(int dummy, ...)
{
    float result = 0.0;
    if (m_isValid) {
        va_list args;
        va_start(args, dummy);
        result = m_methodInfo.env->CallStaticFloatMethodV(m_methodInfo.classID, m_methodInfo.methodID, args);
        va_end(args);
    }
    return result;
}

jstring AJavaStaticMethod::arg(const std::string &string)
{
    if (m_isValid) {
        jstring result = m_methodInfo.env->NewStringUTF(string.c_str());
        if (result == 0) {
            throw std::bad_alloc();
        }
        m_arguments.push_back(result);
        return result;
    }
    return nullptr;
}

jobjectArray AJavaStaticMethod::arg(const std::vector<std::string> &list)
{
    if (m_isValid) {
       jobjectArray result = (jobjectArray)m_methodInfo.env->NewObjectArray(
                    list.size(),
                    m_methodInfo.env->FindClass("java/lang/String"),
                    m_methodInfo.env->NewStringUTF(""));
       if (result == 0) {
           throw std::bad_alloc();
       }

       for (size_t i = 0; i < list.size(); ++i) {
           jstring converted = m_methodInfo.env->NewStringUTF(list[i].c_str());
           if (converted == 0) {
               throw std::bad_alloc();
           }
           m_arguments.push_back(converted);
           m_methodInfo.env->SetObjectArrayElement(result, i, converted);
       }

       m_arguments.push_back(result);
       return result;
    }
    return nullptr;
}

#endif
