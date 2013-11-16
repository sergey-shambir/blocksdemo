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

#include "BreakpadUploader.h"
#include "SystemUtils.h"
#include "ExtraFileUtils.h"
#include "MailSender.h"

using namespace cocos2d;

BreakpadUploader::BreakpadUploader()
    : m_uploadMethod(Automatic)
{
}

void BreakpadUploader::setMailRecipient(const std::string &address)
{
    m_mailRecipient = address;
}

void BreakpadUploader::run()
{
    for (const auto &path : getWritableDirContent(".dmp.gz")) {
        ExtraFileUtils::removeFile(path);
    }

    std::string firstPath;
    for (const auto &path : getWritableDirContent(".dmp")) {
        if (firstPath.empty())
            firstPath = path;
        else
            ExtraFileUtils::removeFile(path);
    }
    if (firstPath.empty())
        return;

    if (mergeDumpAndMetaInfoToGzip(firstPath))
        upload(firstPath + ".gz");
}

/// This function compresses minidump to reduce it's size and attach additional information.
bool BreakpadUploader::mergeDumpAndMetaInfoToGzip(const std::string &dumpPath)
{
    const std::string infoPath = dumpPath + ".info";
    CCPointer<CCDictionary> info = new CCDictionary();
    info->release();

    if (CCApplication::sharedApplication()->getTargetPlatform() == kTargetAndroid) {
        info->setObject(ccs(SystemUtils::getApkVersion()), "Game Version");
        info->setObject(ccs(SystemUtils::getApkVersionCode()), "APK versionCode");
    }
    info->setObject(ccs(SystemUtils::getSystemVersion()), "System version");

    bool ret = false;
    do {
        ret = info->writeToFile(infoPath.c_str());
        CC_BREAK_IF(!ret);

        const std::string destPath = dumpPath + ".gz";
        gzFile dest = gzopen(destPath.c_str(), "w");
        ret = (dest != nullptr);
        CC_BREAK_IF(!ret);

        addFileToOpenedGzip(dumpPath, dest);
        gzwrite(dest, "\n\n", 2);
        addFileToOpenedGzip(infoPath, dest);
        ret = (Z_OK == gzclose(dest));
    } while (0);

    ExtraFileUtils::removeFile(infoPath);
    ExtraFileUtils::removeFile(dumpPath);
    return ret;
}

void BreakpadUploader::addFileToOpenedGzip(const std::string &path, gzFile dest)
{
    FILE *source = fopen(path.c_str(), "r");
    if (!source)
    {
        CCLOG("BreakpadUploader error: no file %s", path.c_str());
        return;
    }
    char buffer[4096];

    for (;;) {
        size_t numread = fread(buffer, sizeof(char), 4096, source);
        if (numread == 0)
            break;
        gzwrite(dest, buffer, numread);
    }
    fclose(source);
}

std::vector<std::string> BreakpadUploader::getWritableDirContent(const std::string &suffix)
{
    return std::move(ExtraFileUtils::getDirectoryContent(CCFileUtils::sharedFileUtils()->getWritablePath(), suffix));
}

void BreakpadUploader::upload(const std::string &gzipPath)
{
    if (m_uploadMethod == Automatic || m_uploadMethod == Email) {
        MailSender sender;
        sender.setSubject("Crash in " + SystemUtils::getApkName());
        sender.setMessage("Hi, dear developer!\n\n"
                          + SystemUtils::getApkName() + " just crashed for me,"
                          " can you please fix this issue?\n"
                          "Steps to reproduce crash:\n");
        sender.setAttachment(gzipPath);
        if (!m_mailRecipient.empty()) {
            sender.addRecipient(m_mailRecipient);
        }
        sender.show();
    }
    // TODO: implement uploading to Amazon S3.
}
