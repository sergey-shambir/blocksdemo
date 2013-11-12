/****************************************************************************
Copyright (c) 2012 Igor Zavorotkin
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

#ifndef __cocos2d_CCPointer__
#define __cocos2d_CCPointer__

#include "ccMacros.h"
#include "cocos2d.h"

namespace cocos2d {

/// Keeps strong reference to object.
template<typename T>
class CCPointer
{
public:
    CCPointer() :
        m_pObject(NULL)
    {
    }

    CCPointer(std::nullptr_t) :
        m_pObject(NULL)
    {
    }

    CCPointer(T* pObject) :
        m_pObject(pObject)
    {
        CC_SAFE_RETAIN(m_pObject);
    }

    CCPointer(const CCPointer& tPointer) :
        m_pObject(tPointer.m_pObject)
    {
        CC_SAFE_RETAIN(m_pObject);
    }

    ~CCPointer()
    {
        CC_SAFE_RELEASE(m_pObject);
    }

    CCPointer& operator=(T* pObject)
    {
        if (m_pObject != pObject)
        {
            CC_SAFE_RELEASE(m_pObject);
            m_pObject = pObject;
            CC_SAFE_RETAIN(m_pObject);
        }
        return *this;
    }

    CCPointer& operator=(const CCPointer& tPointer)
    {
        if (m_pObject != tPointer.m_pObject)
        {
            CC_SAFE_RELEASE(m_pObject);
            m_pObject = tPointer.m_pObject;
            CC_SAFE_RETAIN(m_pObject);
        }
        return *this;
    }

    T *data() const
    {
        return m_pObject;
    }

    bool isNull() const
    {
        return m_pObject == NULL;
    }

    /// Removes newly created object from autorelease pool.
    /// After this operation, only pointer will keep reference to object.
    void undoAutorelease()
    {
        if (m_pObject != NULL)
        {
            cocos2d::CCPoolManager::sharedPoolManager()->removeObject(m_pObject);
            m_pObject->release();
        }
    }

    T* operator->()
    {
        return m_pObject;
    }

    const T* operator->() const
    {
        return m_pObject;
    }

    operator T*() const
    {
        return m_pObject;
    }

private:
    T* m_pObject;
};

/// Does not keep any reference to object, the only goal is to init with null.
template<typename T>
class CCReference
{
public:
    CCReference(T* pObject = NULL) :
    m_pObject(pObject)
    {
    }

    CCReference &operator=(T* pObject)
    {
        if (m_pObject != pObject)
        {
            m_pObject = pObject;
        }
        return *this;
    }

    CCReference& operator=(const CCReference& tPointer)
    {
        if (m_pObject != tPointer.m_pObject)
        {
            m_pObject = tPointer.m_pObject;
        }
        return *this;
    }

    T *data() const
    {
        return m_pObject;
    }

    T* operator->()
    {
        return m_pObject;
    }

    const T* operator->() const
    {
        return m_pObject;
    }

    operator T*() const
    {
        return m_pObject;
    }

private:
    T* m_pObject;
};

} // namespace cocos2d

#define CC_PROPERTY_READONLY_STRONG(varType, varName, funName) \
protected: \
    cocos2d::CCPointer<varType> varName; \
public: \
    virtual varType* get##funName() const;

#define CC_PROPERTY_STRONG(varType, varName, funName) \
protected: \
    cocos2d::CCPointer<varType> varName; \
public: \
    virtual varType* get##funName() const; \
    virtual void set##funName(varType* var);

#define CC_SYNTHESIZE_READONLY_STRONG(varType, varName, funName) \
protected: \
    cocos2d::CCPointer<varType> varName; \
public: \
    virtual varType* get##funName() const { return varName; }

#define CC_SYNTHESIZE_STRONG(varType, varName, funName) \
protected: \
    cocos2d::CCPointer<varType> varName; \
public: \
    virtual varType* get##funName() const { return varName; } \
    virtual void set##funName(varType* var) { varName = var; }

#define CC_PROPERTY_READONLY_REFERENCE(varType, varName, funName) \
protected: \
    cocos2d::CCReference<varType> varName; \
public: \
    virtual varType* get##funName() const;

#define CC_PROPERTY_REFERENCE(varType, varName, funName) \
protected: \
    cocos2d::CCReference<varType> varName; \
public: \
    virtual varType* get##funName() const; \
    virtual void set##funName(varType* var);

#define CC_SYNTHESIZE_READONLY_REFERENCE(varType, varName, funName) \
protected: \
    cocos2d::CCReference<varType> varName; \
public: \
    virtual varType* get##funName() const { return varName; }

#define CC_SYNTHESIZE_REFERENCE(varType, varName, funName) \
protected: \
    cocos2d::CCReference<varType> varName; \
public: \
    virtual varType* get##funName() const { return varName; } \
    virtual void set##funName(varType* var) { varName = var; }

#endif /* defined(__cocos2d_CCPointer__) */
