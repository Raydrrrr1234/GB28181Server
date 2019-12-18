#ifndef VIDEOCHANNEL_H
#define VIDEOCHANNEL_H

#include <stdint.h>
#include <stdio.h>
#include <list>

#include "Mutex/Mutex.h"
#include "Thread/DataListThread.h"

extern "C"
{
    #include "libavcodec/avcodec.h"
    #include "libavformat/avformat.h"
    #include <libavutil/time.h>
    #include "libavutil/pixfmt.h"
    #include "libswscale/swscale.h"
    #include "libswresample/swresample.h"
    #include "libavutil/imgutils.h"
}

class VideoChannelEventHandle;

struct RtpDataNode
{
    uint8_t * buffer;
    int size;
    long time;
    bool isLostPacket; //�Ƿ�֡��

    RtpDataNode()
    {
        buffer = NULL;
        size = 0;
        time = 0;
        isLostPacket = false;
    }
};

///ͨ�����ݣ����������Ҫͨ��catalog���ȡ���ģ������Ͼ��������һ��ͨ��
class VideoChannel : public DataListThread<RtpDataNode>
{
public:
    VideoChannel();
    ~VideoChannel();

    /**
     * @brief setEventHandle ���ûص�����
     * @param handle
     */
    void setEventHandle(const VideoChannelEventHandle *handle){mVideoChannelEventHandle = (VideoChannelEventHandle *)handle;}

    ///����rtp���ݵȴ�����
    void inputRtpBuffer(uint8_t *buffer, int size, uint32_t sequenceNumber, bool isLastPacket);

    void setCallId(int callId){mCallId = callId;}
    int getCallId(){return mCallId;}

protected:
    void threadStart();
    void threadStop();
    void dealwithDataNode(const RtpDataNode &node);

public:
    int RtpSSRC; //rtp��ݱ�־������invite�����������ֶ��rtp����
    std::string DeviceName;
    std::string DeviceID;
    std::string IPAddress;
    int Port;
    std::string Status;

private:
    int mCallId; //����invite��call id, ��id��Ϊ-1 ˵�����ڷ���invite���󣬷���invite�����У������ٴη���invite���󣬷���������⡣

    uint32_t mReceiveRtpTime;     //���յ�rtp���ݵ�ʱ��(�����ж�rtp���ݽ����Ƿ�ʱ��)

    bool mIsCurrentFrameLostPacket;
    uint32_t mLastSequenceNumber; //��һ�ε�rtp���

    uint8_t *mRtpBuffer; //���RTP�յ���PS��
    int mRtpBufferSize;

    ///ffmpeg������ز���
    AVCodec *pCodec;
    AVCodecContext *pCodecCtx;
    AVFrame * pFrameRGB;
    AVFrame * pFrame;
    AVPacket packet;

    SwsContext * img_convert_ctx;
    uint8_t *out_buffer_rgb;
    int numBytes_rgb;

    char *mH264buf;

    bool mIsLastKeyFrameLostPacket; //��һ��I֡�Ƿ񶪰��ˣ��ǵĻ�����������֡���п��ܻ��� ���������е�֡�� ����������
    bool mIsKeyFrameGetted; //������¼I֡�Ƿ��ȡ���� �������õ���h264֡

    bool openH264Decoder();
    void closeH264Decoder();

    void decodeH264Buffer(uint8_t *buffer, int size, bool isLostPacket);

    ///��������������ϵĻص�����
private:
    VideoChannelEventHandle *mVideoChannelEventHandle; //�ص����� ���ڴ�����Ϣ������

    void dealWithRgb32Frame(const uint8_t *rgb32Buffer, const int bufferSize,  const int width, const int height, const bool isLostPacket, const bool isKeyFrame); //��ʾ��Ƶ����

};

#endif // VIDEOCHANNEL_H
