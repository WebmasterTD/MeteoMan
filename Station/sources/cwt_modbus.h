#ifndef __CWT_MODBUS_H__
#define __CWT_MODBUS_H__
#include "meteoman.h"
#include <modbus/modbus.h>
#include <string>
#include <errno.h>

class cwt_modbus
{
private:
    modbus_t* modbus_ctx;
    uint16_t reg_buf[2];
public:
    cwt_modbus(): modbus_ctx(NULL) {};
    ~cwt_modbus();
    
    ReturnCode init(const std::string& sEction);

    ReturnCode read_temp(float& temp);
    ReturnCode read_humid(float& humid);
    ReturnCode read_all(float& humid, float& temp);
};

#endif //__CWT_MODBUS_H__