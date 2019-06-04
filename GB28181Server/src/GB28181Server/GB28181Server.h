#ifndef GB28181SERVER_H
#define GB28181SERVER_H

#include <stdio.h>
#include <string>
#include <list>
#include <map>
#include <thread>

#include <eXosip2/eXosip.h>

#include "types.h"
#include "Device/CameraDevice.h"
#include "RtpReciever/RtpReciever.h"

class GB28181ServerEventHandle;

class GB28181Server
{
public:
    GB28181Server();

    /**
     * @brief setEventHandle ���ûص�����
     * @param handle
     */
    void setEventHandle(const GB28181ServerEventHandle *handle){mGB28181ServerEventHandle = (GB28181ServerEventHandle *)handle;}

    /**
     * @brief setLocalIp ���ñ���IP����IP�������������ʱ��д��source�����IP��
     * @param ip
     * @param port
     */
    void setLocalIp(const char *ip, const int &port);

    /**
     * @brief setGBServerInfo ����GB��������Ϣ
     * @param sipId    [in] ip��ַ
     * @param passwd   [in] ����
     * @param realm    [in] ��
     */
    void setGBServerInfo(const char *sipId, const char *passwd, const char *realm);

    void start();
    void stop();

    void doSendCatalog(const CameraDevice &device);
    void doSendInvitePlay(const VideoChannel *channelNode);

    std::list<CameraDevice> getDeviceList(){return mDeviceList;}

    ///����ssrc���Ҷ�Ӧ��videoChannel
    VideoChannel* getVideoChannel(int ssrc);

protected:
    void run(); //�߳�ִ�к���

private:
    char SERVER_SIP_ID[256];
    char GB_PASSWORD[36];
    char GB_REALM[36];

    char LOCAL_IP[36];
    int LOCAL_PORT;

    int SN = 1;
    struct eXosip_t *eCtx;

    RtpReciever *mRtpReciever; //����rtp�����߳�

    bool mIsStop;          //�Ƿ��յ�ֹͣ����
    bool mIsThreadRunning; //�����Ƿ�������

    std::map<int, VideoChannel*>  mDeviceVideoChannelMap; //rtp invite��ssrc��ChannelNode��ӳ���
    std::list<CameraDevice> mDeviceList; //�豸�б�

    void Register401Unauthorized(struct eXosip_t * peCtx, eXosip_event_t *je);
    void RegisterSuccess(struct eXosip_t * peCtx,eXosip_event_t *je);
    void RegisterFailed(struct eXosip_t * peCtx,eXosip_event_t *je);

    void Response(struct eXosip_t * peCtx,eXosip_event_t *je, int value); //�����������
    void Response403(struct eXosip_t * peCtx,eXosip_event_t *je); //��403
    void Response200(struct eXosip_t * peCtx,eXosip_event_t *je); //��200OK

    void ResponseCallAck(struct eXosip_t * peCtx, eXosip_event_t *je);

    int SendQueryCatalog(struct eXosip_t *peCtx , CameraDevice deviceNode); //�����豸Ŀ¼

    //������Ƶ��Ϣ��SDP��Ϣ
    int SendInvitePlay(struct eXosip_t *peCtx, const VideoChannel *channelNode);

    ///����invite�������
    bool setCallFinished(int callId);

    ///��������������ϵĻص�����
private:
    GB28181ServerEventHandle *mGB28181ServerEventHandle; //�ص����� ���ڴ�����Ϣ������

    void deviceRegisted(const CameraDevice &device); //�豸ע��ɹ�
    void deviceUpdate(const CameraDevice &device);   //�豸���£�catalog���󷵻ص��豸��Ϣ����
    void receiveMessage(const char *deviceID, const MessageType &type, const char *msgBody);  //���յ���Ϣ

};

#endif // GB28181SERVER_H
