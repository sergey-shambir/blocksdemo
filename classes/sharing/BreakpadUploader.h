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

#ifndef BREAKPADCOMPRESSOR_H
#define BREAKPADCOMPRESSOR_H

#include "cocos2d_game.h"
#include "zlib.h"

class BreakpadUploader
{
public:
    enum UploadMethod {
        Automatic, ///< detect suitable method automatically.
        Email,
        AmazonS3
    };

    BreakpadUploader();

    void setMailRecipient(const std::string &address);
    void run();

private:
    bool mergeDumpAndMetaInfoToGzip(const std::string &dumpPath);
    void addFileToOpenedGzip(const std::string &path, gzFile dest);
    std::vector<std::string> getWritableDirContent(const std::string &suffix);
    void upload(const std::string &gzipPath);

    UploadMethod m_uploadMethod;
    std::string m_mailRecipient;
};

#endif // BREAKPADCOMPRESSOR_H
