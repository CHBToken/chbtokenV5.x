#ifndef SIGNFILEDIALOG_H
#define SIGNFILEDIALOG_H

#include <QDialog>
#include <QFileDialog>
#include <QMessageBox>
#include <QFileInfo>
#include <QProcess>
#include <QJsonDocument>
#include <QJsonObject>
#include <QVariantMap>
#include <QByteArray>
#include <QUuid>
#include <QTextStream>

#include "walletmodel.h"

namespace Ui {
    class SignFileDialog;
}
class ClientModel;
class OptionsModel;

/** "Upload" dialog box */
class SignFileDialog : public QDialog
{
    Q_OBJECT

public:
    QWidget* myParent;
    explicit SignFileDialog(QWidget *parent = 0);
    ~SignFileDialog();

    void setModel(WalletModel *model);
private:
    Ui::SignFileDialog *ui;
    WalletModel* model;


    QString program = "./CHBTPaygate.exe";
    QString chbtTrustCenter = "XXX";
    float spendableBalance;
    void setBalance(qint64 spendable, qint64 stake, qint64 unconfirmend, qint64 dontknow);
    bool createProcessJson(QString filename, SendCoinsRecipient sendCoinRecipient, QString transactionId, int duration);
    void processProcessJson(QString transactionId);
    int getSelectedDuration();
    float priceEuroPerYear ;
    float priceCHBTPerYear ;
    float priceEuroTotal ;
    float priceCHBTTotal;

private slots:
    void on_buttonBox_accepted();
    void on_fileSelect_clicked();
    void on_fileName_textChanged();
    void on_payAndUpload_clicked();
    void on_rB1Y_clicked();
    void on_rB2Y_clicked();
    void on_rB3Y_clicked();
    void on_rB4Y_clicked();
    void on_rB5Y_clicked();
    void on_rB6Y_clicked();
    void on_rB7Y_clicked();
    void on_rB8Y_clicked();
    void on_rB9Y_clicked();
    void on_rB10Y_clicked();
};

#endif // SIGNFILEDIALOG_H