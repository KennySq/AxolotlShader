#pragma once

struct AXParser
{
	struct ByteBlock
	{
		std::vector<unsigned char> Bytes;
		size_t From;
		size_t To;

		std::string ToString() const;
		std::string ToNumericString(int base) const;
	};


public:
	AXParser(const char* path);
	~AXParser();
	static std::shared_ptr<AXParser> OpenFile(const char* path);

	inline void OffsetCorrection()
	{
		mIndex += 4 - (mIndex % 4) ;
	}

	inline void Jump(size_t offset)
	{
		mIndex += offset;
	}

	inline void Jump(size_t from, size_t offset)
	{
		mIndex = from + offset;
	}

	inline bool IsBigEndian() const
	{
		static char t = 0x01000004;

		return t == 1;
	}

	template<typename _Ty>
	_Ty Read()
	{
		assert(mIndex + sizeof(_Ty) < mSize);
		_Ty result;
		result = *reinterpret_cast<const _Ty*>(&mRaw[mIndex]);

		if (IsBigEndian() == true)
		{
		}
		else
		{
			//result = 
		}

		
		mIndex += sizeof(_Ty);

		return result;
	}

	std::string ReadString(unsigned int chunkOffset = 0)
	{
		std::string ret;

		unsigned int index = mIndex;

		while (true)
		{
			char* ch = reinterpret_cast<char*>(&mRaw[index]);

			if (*ch == 0x00)
			{
				break;
			}

			ret.push_back(*ch);

			index++;
		}

		mIndex = index + 1;

		return ret;
	}

	uint8_t ReadUint8()
	{
		return Read<uint8_t>();
	}

	uint16_t ReadUint16()
	{
		return Read<uint16_t>();
	}

	uint32_t ReadUint32()
	{
		return Read<uint32_t>();
	}
	uint64_t ReadUint64()
	{
		return Read<uint64_t>();
	}

	size_t GetByteIndex() const { return mIndex; }

private:
	char mByte;
	
	unsigned char* mRaw;
	size_t mIndex;
	size_t mSize;

	std::ifstream mFile;
};