#ifndef EVENTHANDLE_H
#define EVENTHANDLE_H

#include "types.h"

#include "Device/CameraDevice.h"

class GB28181ServerEventHandle
{
    ///��������������ϵĻص�����
public:
    virtual void onDeviceRegisted(const CameraDevice &device) = 0; //�豸ע��ɹ�
    virtual void onDeviceUpdate(const CameraDevice &device) = 0;   //�豸���£�catalog���󷵻ص��豸��Ϣ����
    virtual void onReceiveMessage(const char *deviceID, const MessageType &type, const char *msgBody) = 0;  //���յ���Ϣ

};

class VideoChannelEventHandle
{
    ///��������������ϵĻص�����
public:
    virtual void onDisPlayVideoData(const uint8_t *rgb32Buffer, const int bufferSize,  const int width, const int height) = 0; //��ʾ��Ƶ����

};

#endif // EVENTHANDLE_H
