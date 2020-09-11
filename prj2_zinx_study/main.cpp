#include <zinx.h>
#include <iostream>

//读标准输入， 回显到标准输出

class Echo : public AZinxHandler {
	virtual IZinxMsg * InternelHandle(IZinxMsg & _oInput) override
	{
		GET_REF2DATA(BytesMsg,input,_oInput);
		std::cout << input.szData << std::endl;

		return nullptr;
	}
	virtual AZinxHandler * GetNextHandler(IZinxMsg & _oNextMsg) override
	{
		return nullptr;
	}
} *poEcho = new Echo();



class TestStdin : public Ichannel {
	// 通过 Ichannel 继承
	virtual bool Init() override
	{
		return false;
	}
	virtual bool ReadFd(std::string & _input) override
	{
		std::cin >> _input;
		return false;
	}
	virtual bool WriteFd(std::string & _output) override
	{
		return false;
	}
	virtual void Fini() override
	{
	}
	virtual int GetFd() override
	{
		return 0;
	}
	virtual std::string GetChannelInfo() override
	{
		return std::string();
	}
	virtual AZinxHandler * GetInputNextStage(BytesMsg & _oInput) override
	{

		return poEcho;
	}
};
int main()
{
	//初始化
	ZinxKernel::ZinxKernelInit();
	TestStdin * poStdin = new TestStdin();
	ZinxKernel::Zinx_Add_Channel(*poStdin);
	ZinxKernel::Zinx_Run();
	ZinxKernel::ZinxKernelFini();
	return 0;
}