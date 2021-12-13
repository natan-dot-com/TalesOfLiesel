#ifndef _ERROR_HANDLING_H_
#define _ERROR_HANDLING_H_

#include <string>

typedef enum _ErrorMap {
	OK = 0,
	ERR_NEGATIVE_VALUE,
	ERR_INVALID_MOVE,
} ErrorMap;

class Error {
private:
	unsigned int errorID;
	std::string errorMessage;

public:
	Error();
	
	void setError(unsigned int newErrorID);
	std::string getErrorMessage();
	unsigned int getErrorID();
};

#endif