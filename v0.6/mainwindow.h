#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "connecteddialog.h"
#include "progressdialog.h"
#include "listeners.h"

#include <QCloseEvent>

#include <QSystemTrayIcon>
#include <QIcon>

#include <QLabel>
#include <QTextEdit>
#include <QLineEdit>
#include <QPushButton>

#include <QtNetwork>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);

    ~MainWindow();

    void            RegisterOnServer(const QString &_url);
    void            InitServer(int _port);
    void            InitClient(const QString &_ip,int _port);

    QTcpServer      *server;
    QTcpSocket      *client;
    QTcpSocket      *firstSocket;
    ConnectedDialog *conui;
    ProgressDialog  *progress;
    QAction         *actionRestore;
    QAction         *actionQuit;
    QAction         *actionConnection;
    QAction         *actionDisconnect;
    QAction         *actionAbout;
    QLabel          *TypeLabel;
    QLabel          *statusLabel;
    QTextEdit       *workEdit;
    QLineEdit       *messageEdit;
    QPushButton     *SendButton;
    bool            isconnectionclosed;
    QString         Host;
    QString         Password;
    QString         IP;
    int             Port;
    QSystemTrayIcon *tray;
    QMenu           *trayMenu;
    QMenu           *menuHelp;
private:
    Ui::MainWindow  *ui;

    QNetworkAccessManager *manager;
    bool downloaderror;
    bool isserver;
    class Listeners *listener;
protected:
    void closeEvent(QCloseEvent *event);
    void changeEvent(QEvent *event);
private slots:
    void stateChanged(QAbstractSocket::SocketState state);
    void Read();
    void ClientConnected();
    void ClientDisconnected();
    void hostFound();

    void on_DownloadError(QNetworkReply::NetworkError code);
    void on_DownloadFinished(QNetworkReply * reply);
public slots:
    void ConnectionListener();
    void ConnectionType(bool _server);
};

#endif // MAINWINDOW_H
