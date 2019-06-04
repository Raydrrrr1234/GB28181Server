#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTreeWidgetItem>

#include "GB28181Server/GB28181Server.h"
#include "EventHandle/EventHandle.h"

namespace Ui {
class MainWindow;
}

struct MessageNode
{
    QString deviceID;
    MessageType type;
    QString msgBody;
};

class MainWindow : public QMainWindow, GB28181ServerEventHandle
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

protected:
    void onDeviceRegisted(const CameraDevice &deviceNode); //�豸ע��ɹ�
    void onDeviceUpdate(const CameraDevice &deviceNode);   //�豸���£�catalog���󷵻ص��豸��Ϣ����
    void onReceiveMessage(const char *deviceID, const MessageType &type, const char *msgBody);  //���յ���Ϣ

    /// �������������������߳��е��õģ���˲����ں�����ֱ�Ӳ������棬
    /// ��Ҫת�Ƶ����̺߳����в����������źŲ۵ķ�ʽ��ת�Ƶ����߳�
signals:
    void sig_deviceRegisted(const CameraDevice &deviceNode); //�豸ע��ɹ�
    void sig_deviceUpdate(const CameraDevice &deviceNode);   //�豸���£�catalog���󷵻ص��豸��Ϣ����
    void sig_receiveMessage(const QString &deviceID, const MessageType &type, const QString &msgBody);  //���յ���Ϣ

private slots:
    void slotDeviceRegisted(const CameraDevice &deviceNode); //�豸ע��ɹ�
    void slotDeviceUpdate(const CameraDevice &deviceNode);   //�豸���£�catalog���󷵻ص��豸��Ϣ����
    void slotReceiveMessage(const QString &deviceID, const MessageType &type, const QString &msgBody);  //���յ���Ϣ

private:
    GB28181Server *mGB28181Server; //28181����

private:
    Ui::MainWindow *ui;

    ///�豸�����ĵ����˵�
    QMenu* mDevicePopMenu;
    QAction *mCatalogAction;

    ///�豸ͨ�������ĵ����˵�
    QMenu* mChannelPopMenu;
    QAction *mPlayVideoAction;

    ///���²˵���ʱ�򣬵�ǰѡ�е���Ŀ
    QTreeWidgetItem *mCurrentSelectedItem; //��¼��ǰѡ�е���Ŀ

    QList<MessageNode> mMessageList; //�յ�����Ϣ�б�

private slots:
    void slotBtnClicked(bool isChecked);
    void slotItemClicked(QTreeWidgetItem *item, int column);
    void slotActionTriggered(bool checked);

};

#endif // MAINWINDOW_H
