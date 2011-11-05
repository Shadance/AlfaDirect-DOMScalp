#ifndef ADMAINWINDOW_H
#define ADMAINWINDOW_H

#include "ui_ADMainWindow.h"
#include <QMainWindow>

#include <ADConnection.h>
#include <ADSubscription.h>
#include <ADOrder.h>

class QStandardItemModel;

class ADMainWindow : public QMainWindow, public Ui::ADMainWindow
{
    Q_OBJECT
public:
    ADMainWindow ( const QString& login,
                   const QString& passwd,
                   const QString& accCode,
                   const QString& papCode );

private:
    friend class ADTableView;
    void setupModel ();
    void setupViews ();

    void closeEvent ( QCloseEvent* );
    void keyPressEvent ( QKeyEvent* );
    void mousePressEventADTableView ( ADTableView*, QMouseEvent* );
    void keyPressEventADTableView (  ADTableView* view, QKeyEvent* ke );

private slots:
    void onConnectClick ();
    void onConnectionStateChanged ( ADConnection::State );
    void onQuoteReceived ( int paperNo, ADConnection::Subscription::Type );
    void onHistoricalQuotesReceived ( ADConnection::Request, QVector<ADConnection::HistoricalQuote> );
    void onPositionChanged ( QString accCode, QString paperCode, int paperNo );
    void onOrderStateChanged ( ADConnection::Order,
                               ADConnection::Order::State,
                               ADConnection::Order::State );
    void onOrderOperationResult ( ADConnection::Order,
                                  ADConnection::Order::Operation,
                                  ADConnection::Order::OperationResult );
    void onTrade ( ADConnection::Order, quint32 qty );
    void onEverySecond ();

private:
    QStandardItemModel* m_sellersTableModel;
    QStandardItemModel* m_buyersTableModel;
    ADConnection m_adConnect;
    ADConnection::Subscription m_sub;
    QString m_login;
    QString m_passwd;
    QString m_accCode;
    QString m_papCode;
    int m_papNo;
    QTimer m_everySecondTimer;
    QList<ADConnection::Order> m_sellOrders;
    QList<ADConnection::Order> m_buyOrders;
    qint32 m_pos;
};



#endif // ADMAINWINDOW_H