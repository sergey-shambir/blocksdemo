
#include "cocos2d.h"
#include "BlocksApplication.h"

using namespace cocos2d;

int main()
{
    // create the application instance
    BlocksApplication app;

    CCEGLView* eglView = CCEGLView::sharedOpenGLView();
    eglView->setFrameSize(640, 800);

    return CCApplication::sharedApplication()->run();
}
