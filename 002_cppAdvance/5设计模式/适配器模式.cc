#include <iostream>
#include <string>

/* 
    适配器模式：让不兼容的接口在一起工作
    电脑 =》 投影 =》 投影仪 vga hdmi typec
    适配器模式类似于显示器转换头
*/

class VGA
{
public:
	virtual void play() = 0;
};

class HDMI
{
public:
	virtual void play() = 0;
};

// 表示支持VGA接口的投影仪
class TV01 : public VGA
{
public:
	void play()
	{
		std::cout << "通过VGA接口连接投影仪，进行视频播放" << std::endl;
	}
    std::string getType() const{
        return "VGA";
    }
};

class TV02 : public HDMI
{
public:
	void play()
	{
		std::cout << "通过HDMI接口连接投影仪，进行视频播放" << std::endl;
	}
};

// 电脑类（VGA）
class Computer
{
public:
	void playVideo(VGA* pVGA)
	{
		pVGA->play();
	}
};

//添加适配器类 通过继承vga接口，实现play方法
class VGAToHDMIAdapter : public VGA
{
public:
	VGAToHDMIAdapter(HDMI* p) : pHdmi(p) {}
	void play() { pHdmi->play(); }//该方法相当于转换器，做不同接口信号转换
private:
	HDMI* pHdmi;
};

int main()
{
	Computer computer;
	computer.playVideo(new TV01());
	computer.playVideo(new VGAToHDMIAdapter(new TV02()));

	return 0;
}