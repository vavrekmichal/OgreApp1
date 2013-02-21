#include "DieException.h"

//-------------------------------------------------------------------------------------
DieException::DieException(void):exceptionReason("\tBohuzel jsi prohral"){
}
//-------------------------------------------------------------------------------------
DieException::DieException(const std::string& reason):exceptionReason(reason){
}
//-------------------------------------------------------------------------------------
DieException::~DieException(void){
}


