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

#include "BlocksApplication.h"
#include "LoadingScene.h"

using namespace cocos2d;

BlocksApplication::BlocksApplication()
{
}

bool BlocksApplication::applicationDidFinishLaunching()
{
    auto director = CCDirector::sharedDirector();
    auto glView = CCEGLView::sharedOpenGLView();
    director->setOpenGLView(glView);

    CCFileUtils::sharedFileUtils()->setSearchPaths(getSearchPaths());

    director->setAnimationInterval(1.0 / 60);
    auto scene = LoadingScene::scene();
    director->runWithScene(scene);

    return true;
}

void BlocksApplication::applicationDidEnterBackground()
{
    CCDirector::sharedDirector()->stopAnimation();
}

void BlocksApplication::applicationWillEnterForeground()
{
    CCDirector::sharedDirector()->startAnimation();
}

std::vector<std::string> BlocksApplication::getSearchPaths()
{
    const int dpi = CCDevice::getDPI();
    std::string dpiPath = "ldpi";
    if (dpi > 280) {
        dpiPath = "xhdpi";
    } else if (dpi > 200) {
        dpiPath = "hdpi";
    } else if (dpi > 140) {
        dpiPath = "mdpi";
    }
    std::vector<std::string> result;
    result.push_back(dpiPath);
    result.push_back("nodpi");

    switch (getCurrentLanguage()) {
    case kLanguageRussian:
        result.push_back("ru");
    default:
        break;
    }
    result.push_back("en");

    return result;
}
