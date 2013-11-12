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

#ifndef __cocos2d_CCTouchComponent__
#define __cocos2d_CCTouchComponent__

#include "cocos2d.h"
#include "CCPointer.h"

namespace cocos2d {

class TouchComponentPrivate;

class TouchComponent
{
    CC_DISABLE_COPY(TouchComponent)
public:
    TouchComponent();
    ~TouchComponent();

    void setTouchDelegate(cocos2d::CCTouchDelegate *delegate);
    void setTouchPriority(int priority);
    void setSwallowTouches(bool swallow);

    /// If true passed, than starts listen touches with current priority
    /// and swallow touches settings.
    void setTouchesEnabled(bool enabled);

private:
    CCPointer<TouchComponentPrivate> m_component;
    int m_priority;
    bool m_swallowTouches;
};

} // namespace cocos2d

#endif /* defined(__cocos2d_CCTouchComponent__) */
