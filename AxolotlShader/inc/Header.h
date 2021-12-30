#pragma once
struct AXParser;
struct Header
{
	Header(std::shared_ptr<AXParser> parser);
private:
	std::shared_ptr<AXParser> mParser;

	std::string mNextChunk;
};
