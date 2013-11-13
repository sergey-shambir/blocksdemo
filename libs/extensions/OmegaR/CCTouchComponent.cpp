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

#include "CCTouchComponent.h"

namespace cocos2d {

/// Designed to remove cycle of two strong references:
/// Your layer <-> cocos2dx touch handler.
class TouchComponentPrivate :
        public cocos2d::CCObject,
        public cocos2d::CCTargetedTouchDelegate
{
    CC_SYNTHESIZE_REFERENCE(cocos2d::CCTouchDelegate, m_delegate, Delegate)
public:


    TouchComponentPrivate();
    ~TouchComponentPrivate();
    void startTouches(int priority, bool swallowTouches);
    void stopTouches();

    bool ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
    void ccTouchMoved(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
    void ccTouchEnded(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
    void ccTouchCancelled(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
};

TouchComponentPrivate::TouchComponentPrivate()
{
}

TouchComponentPrivate::~TouchComponentPrivate()
{
}

void TouchComponentPrivate::startTouches(int priority, bool swallowTouches)
{
    stopTouches();
    CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, priority, swallowTouches);
}

void TouchComponentPrivate::stopTouches()
{
    if (CCDirector::sharedDirector()->getTouchDispatcher()->findHandler(this))
        CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(this);
}

bool TouchComponentPrivate::ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
    if (m_delegate)
        return m_delegate->ccTouchBegan(pTouch, pEvent);
    return false;
}

void TouchComponentPrivate::ccTouchMoved(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
    if (m_delegate)
        m_delegate->ccTouchMoved(pTouch, pEvent);
}

void TouchComponentPrivate::ccTouchEnded(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
    if (m_delegate)
        m_delegate->ccTouchEnded(pTouch, pEvent);
}

void TouchComponentPrivate::ccTouchCancelled(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
    if (m_delegate)
        m_delegate->ccTouchCancelled(pTouch, pEvent);
}

TouchComponent::TouchComponent()
    : m_component(new TouchComponentPrivate)
    , m_priority(0)
    , m_swallowTouches(true)
{
}

TouchComponent::~TouchComponent()
{
    m_component->setDelegate(nullptr);
    m_component->stopTouches();
}

void TouchComponent::setTouchComponentDelegate(CCTouchDelegate *delegate)
{
    m_component->setDelegate(delegate);
}

void TouchComponent::setTouchComponentPriority(int priority)
{
    m_priority = priority;
}

void TouchComponent::setTouchComponentSwallow(bool swallow)
{
    m_swallowTouches = swallow;
}

void TouchComponent::setTouchComponentEnabled(bool enabled)
{
    if (enabled)
        m_component->startTouches(m_priority, m_swallowTouches);
    else
        m_component->stopTouches();
}

} // namespace cocos2d
