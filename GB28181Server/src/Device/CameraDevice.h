#ifndef CAMERADEVICE_H
#define CAMERADEVICE_H

#include <stdint.h>
#include <stdio.h>
#include <list>

#include "VideoChannel.h"

///�豸���ݣ�ͨ��ע�������ȡ������Ϣ
struct CameraDevice
{
    std::string DeviceID;
    std::string IPAddress;
    int Port;

    std::list<VideoChannel*> channelList; //һ��ͨ����Ӧһ·��Ƶ����һ����������ж��ͨ��

    bool operator == (CameraDevice node)//��������������ľ���ʵ��
    {
        bool isSame = false;

        if ((node.DeviceID.compare(this->DeviceID) == 0) && (node.IPAddress.compare(this->IPAddress) == 0))
        {
            isSame = true;
        }

        return isSame;
    }
};

#endif // CAMERADEVICE_H
