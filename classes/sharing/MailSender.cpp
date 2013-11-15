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

#include "MailSender.h"

#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
#include "AJavaStaticMethod.h"
#endif

MailSender::MailSender()
    : m_isHTML(false)
{
}

void MailSender::setIsHtml(bool isHtml)
{
    m_isHTML = isHtml;
}

void MailSender::setMessage(const std::string &text)
{
    m_message = text;
}

void MailSender::setSubject(const std::string &text)
{
    m_subject = text;
}

void MailSender::setAttachment(const std::string &path)
{
    m_attachment = path;
}

void MailSender::addRecipient(const std::string &address)
{
    m_recipients.push_back(address);
}

bool MailSender::show()
{
#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
    AJavaStaticMethod method(CLASS_PLATFORM_UTILS,
                             "sendEmail",
                             "([Ljava/lang/String;Ljava/lang/String;ZLjava/lang/String;Ljava/lang/String;)Z");
    return method.callBool(0, method.arg(m_recipients), method.arg(m_message),
                           m_isHTML, method.arg(m_subject), method.arg(m_attachment));
#else
    return false;
#endif
}
