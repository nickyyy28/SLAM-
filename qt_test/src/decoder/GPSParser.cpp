#include "decoder/GPSParser.h"

GPSParser::GPSParser() : m_buffer(new uint8_t[MAX_GPSParser_BUFFER_SIZE])
{

}

GPSParser::~GPSParser()
{
    if (m_buffer != nullptr) {
        delete[] m_buffer;
    }
    
    m_buffer = nullptr;

}

const uint16_t CRC16_TABLE[256] =
{
    0x0000, 0x1189, 0x2312, 0x329b, 0x4624, 0x57ad, 0x6536, 0x74bf,
    0x8c48, 0x9dc1, 0xaf5a, 0xbed3, 0xca6c, 0xdbe5, 0xe97e, 0xf8f7,
    0x1081, 0x0108, 0x3393, 0x221a, 0x56a5, 0x472c, 0x75b7, 0x643e,
    0x9cc9, 0x8d40, 0xbfdb, 0xae52, 0xdaed, 0xcb64, 0xf9ff, 0xe876,
    0x2102, 0x308b, 0x0210, 0x1399, 0x6726, 0x76af, 0x4434, 0x55bd,
    0xad4a, 0xbcc3, 0x8e58, 0x9fd1, 0xeb6e, 0xfae7, 0xc87c, 0xd9f5,
    0x3183, 0x200a, 0x1291, 0x0318, 0x77a7, 0x662e, 0x54b5, 0x453c,
    0xbdcb, 0xac42, 0x9ed9, 0x8f50, 0xfbef, 0xea66, 0xd8fd, 0xc974,
    0x4204, 0x538d, 0x6116, 0x709f, 0x0420, 0x15a9, 0x2732, 0x36bb,
    0xce4c, 0xdfc5, 0xed5e, 0xfcd7, 0x8868, 0x99e1, 0xab7a, 0xbaf3,
    0x5285, 0x430c, 0x7197, 0x601e, 0x14a1, 0x0528, 0x37b3, 0x263a,
    0xdecd, 0xcf44, 0xfddf, 0xec56, 0x98e9, 0x8960, 0xbbfb, 0xaa72,
    0x6306, 0x728f, 0x4014, 0x519d, 0x2522, 0x34ab, 0x0630, 0x17b9,
    0xef4e, 0xfec7, 0xcc5c, 0xddd5, 0xa96a, 0xb8e3, 0x8a78, 0x9bf1,
    0x7387, 0x620e, 0x5095, 0x411c, 0x35a3, 0x242a, 0x16b1, 0x0738,
    0xffcf, 0xee46, 0xdcdd, 0xcd54, 0xb9eb, 0xa862, 0x9af9, 0x8b70,
    0x8408, 0x9581, 0xa71a, 0xb693, 0xc22c, 0xd3a5, 0xe13e, 0xf0b7,
    0x0840, 0x19c9, 0x2b52, 0x3adb, 0x4e64, 0x5fed, 0x6d76, 0x7cff,
    0x9489, 0x8500, 0xb79b, 0xa612, 0xd2ad, 0xc324, 0xf1bf, 0xe036,
    0x18c1, 0x0948, 0x3bd3, 0x2a5a, 0x5ee5, 0x4f6c, 0x7df7, 0x6c7e,
    0xa50a, 0xb483, 0x8618, 0x9791, 0xe32e, 0xf2a7, 0xc03c, 0xd1b5,
    0x2942, 0x38cb, 0x0a50, 0x1bd9, 0x6f66, 0x7eef, 0x4c74, 0x5dfd,
    0xb58b, 0xa402, 0x9699, 0x8710, 0xf3af, 0xe226, 0xd0bd, 0xc134,
    0x39c3, 0x284a, 0x1ad1, 0x0b58, 0x7fe7, 0x6e6e, 0x5cf5, 0x4d7c,
    0xc60c, 0xd785, 0xe51e, 0xf497, 0x8028, 0x91a1, 0xa33a, 0xb2b3,
    0x4a44, 0x5bcd, 0x6956, 0x78df, 0x0c60, 0x1de9, 0x2f72, 0x3efb,
    0xd68d, 0xc704, 0xf59f, 0xe416, 0x90a9, 0x8120, 0xb3bb, 0xa232,
    0x5ac5, 0x4b4c, 0x79d7, 0x685e, 0x1ce1, 0x0d68, 0x3ff3, 0x2e7a,
    0xe70e, 0xf687, 0xc41c, 0xd595, 0xa12a, 0xb0a3, 0x8238, 0x93b1,
    0x6b46, 0x7acf, 0x4854, 0x59dd, 0x2d62, 0x3ceb, 0x0e70, 0x1ff9,
    0xf78f, 0xe606, 0xd49d, 0xc514, 0xb1ab, 0xa022, 0x92b9, 0x8330,
    0x7bc7, 0x6a4e, 0x58d5, 0x495c, 0x3de3, 0x2c6a, 0x1ef1, 0x0f78
};

const unsigned char CRC8_TABLE[256] =
{
        0x00, 0x5e, 0xbc, 0xe2, 0x61, 0x3f, 0xdd, 0x83, 0xc2, 0x9c, 0x7e, 0x20, 0xa3, 0xfd, 0x1f, 0x41,
        0x9d, 0xc3, 0x21, 0x7f, 0xfc, 0xa2, 0x40, 0x1e, 0x5f, 0x01, 0xe3, 0xbd, 0x3e, 0x60, 0x82, 0xdc,
        0x23, 0x7d, 0x9f, 0xc1, 0x42, 0x1c, 0xfe, 0xa0, 0xe1, 0xbf, 0x5d, 0x03, 0x80, 0xde, 0x3c, 0x62,
        0xbe, 0xe0, 0x02, 0x5c, 0xdf, 0x81, 0x63, 0x3d, 0x7c, 0x22, 0xc0, 0x9e, 0x1d, 0x43, 0xa1, 0xff,
        0x46, 0x18, 0xfa, 0xa4, 0x27, 0x79, 0x9b, 0xc5, 0x84, 0xda, 0x38, 0x66, 0xe5, 0xbb, 0x59, 0x07,
        0xdb, 0x85, 0x67, 0x39, 0xba, 0xe4, 0x06, 0x58, 0x19, 0x47, 0xa5, 0xfb, 0x78, 0x26, 0xc4, 0x9a,
        0x65, 0x3b, 0xd9, 0x87, 0x04, 0x5a, 0xb8, 0xe6, 0xa7, 0xf9, 0x1b, 0x45, 0xc6, 0x98, 0x7a, 0x24,
        0xf8, 0xa6, 0x44, 0x1a, 0x99, 0xc7, 0x25, 0x7b, 0x3a, 0x64, 0x86, 0xd8, 0x5b, 0x05, 0xe7, 0xb9,
        0x8c, 0xd2, 0x30, 0x6e, 0xed, 0xb3, 0x51, 0x0f, 0x4e, 0x10, 0xf2, 0xac, 0x2f, 0x71, 0x93, 0xcd,
        0x11, 0x4f, 0xad, 0xf3, 0x70, 0x2e, 0xcc, 0x92, 0xd3, 0x8d, 0x6f, 0x31, 0xb2, 0xec, 0x0e, 0x50,
        0xaf, 0xf1, 0x13, 0x4d, 0xce, 0x90, 0x72, 0x2c, 0x6d, 0x33, 0xd1, 0x8f, 0x0c, 0x52, 0xb0, 0xee,
        0x32, 0x6c, 0x8e, 0xd0, 0x53, 0x0d, 0xef, 0xb1, 0xf0, 0xae, 0x4c, 0x12, 0x91, 0xcf, 0x2d, 0x73,
        0xca, 0x94, 0x76, 0x28, 0xab, 0xf5, 0x17, 0x49, 0x08, 0x56, 0xb4, 0xea, 0x69, 0x37, 0xd5, 0x8b,
        0x57, 0x09, 0xeb, 0xb5, 0x36, 0x68, 0x8a, 0xd4, 0x95, 0xcb, 0x29, 0x77, 0xf4, 0xaa, 0x48, 0x16,
        0xe9, 0xb7, 0x55, 0x0b, 0x88, 0xd6, 0x34, 0x6a, 0x2b, 0x75, 0x97, 0xc9, 0x4a, 0x14, 0xf6, 0xa8,
        0x74, 0x2a, 0xc8, 0x96, 0x15, 0x4b, 0xa9, 0xf7, 0xb6, 0xe8, 0x0a, 0x54, 0xd7, 0x89, 0x6b, 0x35,
};

const GPSInfo* GPSParser::parse(const uint8_t* src, size_t len)
{
    if (src == nullptr)
    {
        return nullptr;
    }

    int pos[12] = { 0 }; //逗号的位置
    int start_pos = 0, end_pos = 0;
    int comma_cnt = 1;
    
    for (int i = 0 ; i < len ; ++i) {
        if (*(src + i) != '$') {
            continue;
        } else {
            char temp[5];
            std::memcpy(temp, src + i + 1, 5);
            if(!std::strcmp("GPRMC", temp)) {
                start_pos = i;
                pos[0] = 1;
                //std::cout << "解析头成功" << std::endl;
            } else {
                continue;
            }
        }

        for (int j = i ; j < len ; ++j) {
            if (*(src + j) == ',') {
                pos[comma_cnt] = j;
                comma_cnt ++;
            }

            if (comma_cnt == 12) {
                for (int k = j ; k < len ; ++k) {
                    if (*(src + k) == '*') {
                        end_pos = k;
                        //std::cout << "解析尾成功" << std::endl;
                        break;
                    }
                }

                if (end_pos != 0) {
                    break;
                }
            }
        }

        if (comma_cnt != 12 || end_pos == 0) {
            pos[0] = 0;
        }

    }

    if (!pos[0]) {
        //std::cout << "解析失败" << std::endl;
        return nullptr;
    } else {
        m_info.clear();
        //std::cout << "解析成功" << std::endl;
    }

    char crc_buff[3];
    char crc_calc[3];

    memset(crc_buff, '\0', 3);
    memset(crc_calc, '\0', 3);
    std::memcpy(crc_buff, src + end_pos + 1, 2);
    sprintf(crc_calc, "%02x", (uint8_t)GPSParser::get_CRC8(src + start_pos + 1, end_pos - start_pos - 1, 0xFF));

    

    if (strcmp(crc_calc, crc_buff) != 0) {
        std::cout << "校验失败" << std::endl;
        std::cout << "计算CRC: " << crc_calc << " ,实际CRC: " << crc_buff << std::endl;
        return nullptr;
    } else {
        //std::cout << "校验成功" << std::endl;
    }

    /* 读取UTC时间 */
    sscanf((char*)(src + pos[1] + 1), "%f", &m_info.m_UTC_timeStamp);

    /* 读取定位状态 */
    if (*(src + pos[2] + 1) == 'A') {
        m_info.m_locationStatus = GPSInfo::A;
    } else {
        m_info.m_locationStatus = GPSInfo::V;
    }

    /* 读取纬度 */
    sscanf((char*)(src + pos[3] + 1), "%f", &m_info.m_Latitude);

    /* 读取北纬南纬 */
    if (*(src + pos[4] + 1) == 'N') {
        m_info.m_latitudeType = GPSInfo::NORTHLatitude;
    } else if (*(src + pos[4] + 1) == 'S') {
        m_info.m_latitudeType = GPSInfo::SOUTHLatitude;
    } else {
        m_info.m_latitudeType = GPSInfo::NoneLatitude;
    }

    /* 读取经度 */
    sscanf((char*)(src + pos[5] + 1), "%f", &m_info.m_Longitude);

    /* 读取经度类型 */
    if (*(src + pos[6] + 1) == 'W') {
        m_info.m_longitudeType = GPSInfo::WESTLongitude;
    } else if (*(src + pos[6] + 1) == 'E') {
        m_info.m_longitudeType = GPSInfo::EASTLongitude;
    } else {
        m_info.m_longitudeType = GPSInfo::NoneLongitude;
    }

    /* 读取地面速率 */
    sscanf((char*)(src + pos[7] + 1), "%f", &m_info.m_GroundSpeed);

    /* 读取地面航向 */
    sscanf((char*)(src + pos[8] + 1), "%f", &m_info.m_GroundCourse);

    /* 读取UTC日期 */
    sscanf((char*)(src + pos[9] + 1), "%d", &m_info.m_UTC_Date);

    /* 读取磁偏角 */
    sscanf((char*)(src + pos[10] + 1), "%f", &m_info.m_MagneticDeclination);

    /* 读取磁偏角方向 */
    if (*(src + pos[11] + 1) == 'W') {
        m_info.m_magType = GPSInfo::WEST;
    } else if (*(src + pos[11] + 1) == 'E') {
        m_info.m_magType = GPSInfo::EAST;
    } else {
        m_info.m_magType = GPSInfo::None;
    }

    /*for (int i = 1 ; i <= 11 ; i++) {
        std::cout << "第" << i << "个逗号在" << pos[i] << " ,读取值为: " << *(src + pos[i]) << std::endl;
    }*/

    //std::cout << "\'$在\'" << start_pos << " 读取为: " << *(src + start_pos) << ", \'*\'在" << end_pos << " 读取值为: " << *(src + end_pos) << std::endl;

    return &this->m_info;
}

const GPSInfo* GPSParser::parse(const std::string& str)
{
    return parse((const uint8_t*)(str.c_str()), str.size());
}

uint16_t GPSParser::get_CRC16(const uint8_t *src, uint32_t len, uint16_t CRC)
{
    uint8_t chData;
    if (src == NULL) {
        return 0xFFFF;
    }
    while (len--) {
        chData = *src++;
        (CRC) = ((uint16_t) (CRC) >> 8) ^ CRC16_TABLE[((uint16_t) (CRC) ^ (uint16_t) (chData)) & 0x00ff];
    }
    return CRC;
}

uint8_t GPSParser::get_CRC8(const uint8_t* src, uint32_t len, uint8_t CRC)
{
    unsigned char ucIndex;
    while (len--) {
        ucIndex = CRC ^ (*src++);
        CRC = CRC8_TABLE[ucIndex];
    }
    return (CRC);
}

GPSInfo::GPSInfo()
{
    m_UTC_timeStamp = 0;
    m_locationStatus = GPSInfo::V;
    m_Latitude = 0;
    m_Longitude = 0;
    m_GroundSpeed = 0;
    m_GroundCourse = 0;
    m_UTC_Date = 0;
    m_MagneticDeclination = 0;
}

GPSInfo::GPSInfo(const GPSInfo& info)
{
    m_UTC_timeStamp = info.m_UTC_timeStamp;
    m_locationStatus = info.m_locationStatus;
    m_Latitude = info.m_Latitude;
    m_latitudeType = info.m_latitudeType;
    m_Longitude = info.m_Longitude;
    m_longitudeType = info.m_longitudeType;
    m_GroundSpeed = info.m_GroundSpeed;
    m_GroundCourse = info.m_GroundCourse;
    m_UTC_Date = info.m_UTC_Date;
    m_MagneticDeclination = info.m_MagneticDeclination;
    m_magType = info.m_magType;
}

const GPSInfo& GPSInfo::operator =(const GPSInfo& info)
{
    m_UTC_timeStamp = info.m_UTC_timeStamp;
    m_locationStatus = info.m_locationStatus;
    m_Latitude = info.m_Latitude;
    m_latitudeType = info.m_latitudeType;
    m_Longitude = info.m_Longitude;
    m_longitudeType = info.m_longitudeType;
    m_GroundSpeed = info.m_GroundSpeed;
    m_GroundCourse = info.m_GroundCourse;
    m_UTC_Date = info.m_UTC_Date;
    m_MagneticDeclination = info.m_MagneticDeclination;
    m_magType = info.m_magType;

    return *this;
}

GPSInfo::GPSInfo(const GPSInfo* pinfo)
{
    if (pinfo) {
        m_UTC_timeStamp = pinfo->m_UTC_timeStamp;
        m_locationStatus = pinfo->m_locationStatus;
        m_Latitude = pinfo->m_Latitude;
        m_latitudeType = pinfo->m_latitudeType;
        m_Longitude = pinfo->m_Longitude;
        m_longitudeType = pinfo->m_longitudeType;
        m_GroundSpeed = pinfo->m_GroundSpeed;
        m_GroundCourse = pinfo->m_GroundCourse;
        m_UTC_Date = pinfo->m_UTC_Date;
        m_MagneticDeclination = pinfo->m_MagneticDeclination;
        m_magType = pinfo->m_magType;
        return;
    }

    GPSInfo();
}

void GPSInfo::clear()
{
    m_UTC_timeStamp = 0;
    m_locationStatus = GPSInfo::V;
    m_Latitude = 0;
    m_Longitude = 0;
    m_GroundSpeed = 0;
    m_GroundCourse = 0;
    m_UTC_Date = 0;
    m_MagneticDeclination = 0;
}

const char* GPSInfo::toString()
{
    char buff[20];
    ss << "$GPRMC,";
    memset(buff, '\0', sizeof (buff));
    sprintf(buff, "%06d.%03d", (int)m_UTC_timeStamp, (int)((m_UTC_timeStamp - (int)m_UTC_timeStamp) * 1000));
    ss << (m_UTC_timeStamp < 0 ? "" : buff) << "," << (m_locationStatus == GPSInfo::A ? "A," : "V,");

    memset(buff, '\0', sizeof (buff));
    sprintf(buff, "%04d.%04d", (int)m_Latitude, (int)((m_Latitude - (int)m_Latitude)*10000));
    ss << (m_Latitude < 0 ? "" : buff) << "," << (m_latitudeType == GPSInfo::NORTHLatitude ? "N," : (m_latitudeType == GPSInfo::SOUTHLatitude ? "S," : ","));

    memset(buff, '\0', sizeof (buff));
    sprintf(buff, "%05d.%04d", (int)m_Longitude, (int)((m_Longitude - (int)m_Longitude)*10000));
    ss << (m_Longitude < 0 ? "" : buff ) << "," << (m_longitudeType == GPSInfo::EASTLongitude ? "E," : (m_longitudeType == GPSInfo::WESTLongitude ? "W," : ","));

    memset(buff, '\0', sizeof (buff));
    if (m_GroundSpeed < 0) {
        ss << ",";
    } else {
        sprintf(buff, "%03d.%01d", (int)m_GroundSpeed, (int)((m_GroundSpeed - (int)m_GroundSpeed)*10));
        ss << buff << ",";
    }

    memset(buff, '\0', sizeof (buff));
    if (m_GroundCourse < 0) {
        ss << ",";
    } else {
        sprintf(buff, "%03d.%01d", (int)m_GroundCourse, (int)((m_GroundCourse - (int)m_GroundCourse)*10));
        ss << buff << ",";
    }

    memset(buff, '\0', sizeof (buff));
    if (m_UTC_Date < 0) {
        ss << ",";
    } else {
        sprintf(buff, "%06d", m_UTC_Date);
        ss << buff << ",";
    }

    memset(buff, '\0', sizeof (buff));
    if (m_MagneticDeclination < 0) {
        ss << ",";
    } else {
        sprintf(buff, "%03d.%01d", (int)m_MagneticDeclination, (int)((m_MagneticDeclination - (int)m_MagneticDeclination)*10));
        ss << buff << ",";
    }

    ss << (m_magType == GPSInfo::WEST ? "W" : (m_magType == GPSInfo::EAST ? "E" : ""));

    std::string temp;

    ss >> temp;

    ss.clear();

    //std::cout << "temp: " << temp << std::endl;
    
    uint8_t crc;

    crc = GPSParser::get_CRC8((uint8_t* )(temp.c_str() + 1), temp.size() - 1, 0xFF);

    ss << temp.c_str() << "*";

    memset(buff, '\0', sizeof(buff));
    sprintf(buff, "%02x", crc);
    ss << buff;

    // ss << temp.c_str() << "*" << crc;

    ss >> str;

    ss.clear();

    return str.c_str();
}
