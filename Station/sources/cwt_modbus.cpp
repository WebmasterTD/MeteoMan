#include "cwt_modbus.h"
#include <fmt/core.h>
#define SENSOR_ID       0x01
#define HUMID           0x00
#define TEMP            0x01


cwt_modbus::~cwt_modbus()
{
    if (modbus_ctx != NULL)
    {
        modbus_close(modbus_ctx);
        modbus_free(modbus_ctx);
    }
}

ReturnCode cwt_modbus::init(const std::string& sSection)
{
    m_oConfReader = INIReader(CONFIG_FILENAME);

    std::string port = m_oConfReader.Get(sSection, "port", "");
    int baud_rate = m_oConfReader.GetInteger(sSection, "baud_rate", 0);
    char parity = m_oConfReader.Get(sSection, "parity", "").c_str()[0];
    int databits = m_oConfReader.GetInteger(sSection, "databits", 0);
    int stopbits = m_oConfReader.GetInteger(sSection, "stopbits", 0);

    modbus_ctx = modbus_new_rtu(port.c_str(), baud_rate, parity, databits, stopbits);
    if (modbus_ctx == NULL)
    {
        fmt::print(stderr, "modbus_new_rtu: failed!\n");
        errno = ECONNREFUSED;
        return ReturnCode::ERROR;
    }

    if (modbus_set_slave(modbus_ctx, SENSOR_ID) == -1)
    {
        fmt::print(stderr, "Invalid slave ID: {}\n", modbus_strerror(errno));
        errno = ECONNREFUSED;
        return ReturnCode::ERROR;
    }

    if (modbus_connect(modbus_ctx) == -1)
    {
        fmt::print(stderr, "Connection failed: {}\n", modbus_strerror(errno));
        return ReturnCode::ERROR;
    }
    return ReturnCode::OK;
}

ReturnCode cwt_modbus::read_temp(float& temp)
{
    if (modbus_ctx == NULL)
    {
        return ReturnCode::ERROR;
    }
    int ret = modbus_read_registers(modbus_ctx, TEMP, 2, reg_buf);
    if (ret == -1)
    {
        fmt::print(stderr, "Read temperature registers failed: {}\n", modbus_strerror(errno));
        return ReturnCode::ERROR;
    }
    temp = (reg_buf[0] / 10.0);
    return ReturnCode::OK;
}


ReturnCode cwt_modbus::read_humid(float& humid)
{
    if (modbus_ctx == NULL)
    {
        return ReturnCode::ERROR;
    }
    int ret = modbus_read_registers(modbus_ctx, HUMID, 2, reg_buf);
    if (ret == -1)
    {
        fmt::print(stderr, "Read humidity registers failed: {}\n", modbus_strerror(errno));
        return ReturnCode::ERROR;
    }
    humid = (reg_buf[0] / 10.0);
    return ReturnCode::OK;
}