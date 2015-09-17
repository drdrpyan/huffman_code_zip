#ifndef ___BGM__TEMP__BITSTREAM__H___
#define ___BGM__TEMP__BITSTREAM__H___

#include <iostream>
#include <vector>
#include <list>

namespace BGM
{
	namespace temp
	{
		class BitStream
		{
		private:
			enum {BUFF_SIZE=1024};
			std::list<bool> stream;
			char buffer[1024];
		public:
			void push(bool bit)
			{
				stream.push_back(bit);
			}
			void push(std::vector<bool> code)
			{
				for(int i=0; i<code.size(); i++)
					stream.push_back(code[i]);
			}
			bool front() const
			{
				return stream.front();
			}
			bool pop()
			{
				stream.pop_front();
			}
			void print(std::ostream& os)
			{
				char c=0;
				int idx=0, buffIdx=0;
				while(stream.size() >= 8)
				{
					if(buffIdx == BUFF_SIZE)
						os.write(buffer, BUFF_SIZE);
					c = 0;
					for(idx=0; idx < 8; idx++)
					{
						c <<=1;
						if(stream.front())
							c |= 0x1;
						stream.pop_front();
					}
					buffer[buffIdx++] = c;
				}
				os.write(buffer, buffIdx);
			}

			void flush(std::ostream& os)
			{
				if(stream.size() > 8)
					return;

				int i = 0;
				char c = 0;
				while(!stream.empty())
				{
					c <<= 1;
					if(stream.front())
						c |= 0x1;
					i++;
					stream.pop_front();
				}
				for(;i<8; i++)
				{
					c <<= 1;
				}
				os.put(c);
			}
		};
	}
}
#endif
