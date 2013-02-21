#ifndef __DieException_h_
#define __DieException_h_

#include <string>
#include <exception>

///Simply exception for catch Player death
class DieException : public std::exception
{
public:
	DieException(void);
	~DieException(void);
	DieException(const std::string& reason);
	std::string exceptionReason;
};

#endif // #ifndef __DieException_h_

