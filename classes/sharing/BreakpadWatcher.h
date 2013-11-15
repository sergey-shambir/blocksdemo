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

#ifndef BREAKPADWATCHER_H
#define BREAKPADWATCHER_H

#include "cocos2d_game.h"
#include <memory>

#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
#include "exception_handler.h"
#include "minidump_descriptor.h"
#endif

class BreakpadWatcher
{
    CC_DISABLE_COPY(BreakpadWatcher)
public:
    BreakpadWatcher();
    ~BreakpadWatcher();

private:
#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
    std::unique_ptr<google_breakpad::MinidumpDescriptor> m_minidumpDescriptor;
    std::unique_ptr<google_breakpad::ExceptionHandler> m_exceptionHandler;
#endif
};

#endif // BREAKPADWATCHER_H
