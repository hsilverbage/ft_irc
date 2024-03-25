
#ifndef CHANNEL_HPP
#define CHANNEL_HPP

#include <iostream>

class Channel
{
	public:

		Channel();
		~Channel();

	private:

		Channel(const Channel& rhs);
		Channel& operator=(const Channel& rhs);
};

#endif
