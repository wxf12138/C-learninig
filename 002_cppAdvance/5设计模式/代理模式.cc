#include <iostream>
#include <memory>
using namespace std;
/*
    代理模式Proxy：通过代理类，来控制实际对象的访问权限
    客户    助理Proxy   老板 委托类
*/

class VideoSite
{
public:
    virtual void freeVideo() = 0;
    virtual void vipVideo() = 0;
    virtual void payVideo() = 0;
};

class FixBugVideoSite : public VideoSite
{
public:
    void freeVideo()
    {
        cout << "免费视频" << endl;
    }
    void vipVideo()
    {
        cout << "会员视频" << endl;
    }
    void payVideo()
    {
        cout << "付费视频" << endl;
    }
};

class FreeVideoSiteProxy : public VideoSite
{
public:
    FreeVideoSiteProxy()
    {
        pVideo = new FixBugVideoSite();
    }
    virtual void freeVideo()
    {
        pVideo->freeVideo(); // 实际访问
    }
    virtual void vipVideo()
    {
        cout << "代理类控制访问权限" << endl;
    }
    virtual void payVideo()
    {
        cout << "代理类控制访问权限" << endl;
    }
    ~FreeVideoSiteProxy()
    {
        delete pVideo;
    }
private:
    VideoSite *pVideo;
};

class VIPVideoSiteProxy : public VideoSite
{
public:
    VIPVideoSiteProxy()
    {
        pVideo = new FixBugVideoSite();
    }
    virtual void freeVideo()
    {
        pVideo->freeVideo();
    }
    virtual void vipVideo()
    {
        pVideo->vipVideo(); // 实际访问
    }
    virtual void payVideo()
    {
        cout << "代理类控制访问权限" << endl;
    }
private:
    VideoSite *pVideo;
};

void watchMovie(unique_ptr<VideoSite> &p)
{
    p->freeVideo();
    p->vipVideo();
    p->payVideo();
}
int main()
{
    unique_ptr<VideoSite> p1(new FreeVideoSiteProxy()) ;
    unique_ptr<VideoSite> p2(new VIPVideoSiteProxy()) ;

    watchMovie(p1);
    watchMovie(p2);
    return 0;
}