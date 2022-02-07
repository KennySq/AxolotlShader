#include<Util.h>
#include<string>

#include<AXParser.h>
#include<AXBytecode.h>

#pragma comment(lib, "AxolotlShader.lib")

int main()
{
	std::shared_ptr<AXBytecode> bytecode = std::make_shared<AXBytecode>("C:/Users/odess/Documents/AxolotlShader/AxolotlShader/resource/sample.o");

	return 0;
}