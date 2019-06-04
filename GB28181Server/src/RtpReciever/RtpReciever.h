#ifndef RTPRECEIVER_H
#define RTPRECEIVER_H

#include <stdint.h>
#include <string.h>
#include <iostream>

#define MEDIASERVER_RTP_PORT 8000

class RtpReciever
{
public:
    RtpReciever();
    ~RtpReciever();

public:
    void start();

    void stop(bool isWait = false);

protected:
    bool mIsStop;
    bool mIsThreadRunning;

    void run();

public:
    /**
     * @brief GetH264FromPs   rtp����h264��Ƶ��Ϣ
     * @param buffer          ����rtp���ݣ������ps��װ��
     * @param length          ����
     * @param h264Buffer      �����h264����
     * @param h264length_out
     * @return
     */
    static int GetH264FromPs(char* buffer, int length, char *h264Buffer, int *h264length_out);


};

#endif // RTPRECEIVER_H
