#ifndef __GPS_PARSER_H
#define __GPS_PARSER_H

#include <cstdint>
#include <cstring>
#include <cstdlib>
#include <iostream>
#include <strstream>
#include <sstream>

#define MAX_GPSParser_BUFFER_SIZE 512

class GPSInfo{
public:
    GPSInfo();
    GPSInfo(const GPSInfo& info);
    const GPSInfo& operator =(const GPSInfo& info);
    GPSInfo(const GPSInfo* pinfo);
    void clear();

    /* 将GPS信息转化为标准格式字符串 */
    const char* toString();

    typedef enum{
        A = 0,  /* 定位成功 */
        V       /* 定位异常 */
    }LocationStatus;

    typedef enum{
        EASTLongitude = 0,   /* 东经 */
        WESTLongitude,       /* 西经 */
        NoneLongitude
    }LongitudeType;

    typedef enum{
        NORTHLatitude = 0,  /* 北纬 */
        SOUTHLatitude,      /* 南纬 */
        NoneLatitude
    }LatitudeType;

    typedef enum{
        EAST = 0,
        WEST,
        None
    }MagneticDeclinationType;

    float m_UTC_timeStamp;              /* UTC 时间戳 []*/
    LocationStatus m_locationStatus;    /* 定位状态 */
    float m_Latitude;                   /* 纬度 */
    LatitudeType m_latitudeType;        /* 纬度类型 北纬南纬 */
    float m_Longitude;                  /* 经度 */
    LongitudeType m_longitudeType;      /* 经度类型 东经西经 */
    float m_GroundSpeed;                /* 地速 */
    float m_GroundCourse;               /* 地面航向 */
    int m_UTC_Date;                     /* UTC 日期 */
    float m_MagneticDeclination;        /* 磁偏角 */
    MagneticDeclinationType m_magType;  /* 磁偏角方向 西/东 */

private:
    std::stringstream ss;
    std::string str;
};

class GPSParser{
public:
    GPSParser();
    ~GPSParser();

    /* 从字符串解析数据 */
    const GPSInfo* parse(const uint8_t* src, size_t len);

    const GPSInfo* parse(const std::string& str);

    static uint16_t get_CRC16(const uint8_t *src, uint32_t len, uint16_t CRC = 0xFFFF);
    static uint8_t get_CRC8(const uint8_t* src, uint32_t len, uint8_t CRC = 0xFF);
private:
    uint8_t* m_buffer{nullptr};
    GPSInfo m_info;
};

#endif //__GPS_PARSER_H