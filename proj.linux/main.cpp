
#include "cocos2d.h"
#include "BlocksApplication.h"

using namespace cocos2d;

int main()
{
    CCEGLView *view = new CCEGLView();
    view->setFrameSize(1000, 800);

    BlocksApplication app;
    return app.run();
}
