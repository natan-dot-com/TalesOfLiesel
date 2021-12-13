#include "./lib/backend/error_handling.h"
#include <iostream>

#define NEGATIVE_VALUE_MSG "..."
#define INVALID_MOVE_MSG "..."

Error::Error() {
	errorID = OK;
	errorMessage = "";
}

void Error::setError(unsigned int newErrorID) {
	switch (newErrorID) {
		case OK:
			errorID = OK;
			errorMessage = "";
			break;

		case ERR_NEGATIVE_VALUE:
			errorID = ERR_NEGATIVE_VALUE;
			errorMessage = NEGATIVE_VALUE_MSG;
			break;

		case ERR_INVALID_MOVE:
			errorID = ERR_INVALID_MOVE;
			errorMessage = INVALID_MOVE_MSG;
			break;

		default:
			std::cerr << "Unexpected errorID: " << newErrorID << ". Aborted" << std::endl;
			exit(1);
	}
}

std::string Error::getErrorMessage() {
	return errorMessage;
}

unsigned int Error::getErrorID() {
	return errorID;
}