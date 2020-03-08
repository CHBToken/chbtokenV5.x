#ifndef UPLOADFILEDIALOG_H
#define UPLOADFILEDIALOG_H

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
    class UploadFileDialog;
}
class ClientModel;
class OptionsModel;

/** "Upload" dialog box */
class UploadFileDialog : public QDialog
{
    Q_OBJECT

public:
    QWidget* myParent;
    explicit UploadFileDialog(QWidget *parent = 0);
    ~UploadFileDialog();

    void setModel(WalletModel *model);
private:
    Ui::UploadFileDialog *ui;
    WalletModel* model;


    QString program = "./CHBTPaygate.exe";
    QString chbtTrustCenter = "XXX";
    int minPasswordLength = 8;
    float spendableBalance;
    void setBalance(qint64 spendable, qint64 stake, qint64 unconfirmend, qint64 dontknow);
    bool createProcessJson(QString filename, SendCoinsRecipient sendCoinRecipient, QString transactionId, int duration, bool isShared, QString password);
    void processProcessJson(QString transactionId);
    void UpdatePasswordFields();
    void checkPayAndUploadButtonState();
    bool checkPayAndUploadButtonLocked = true;
    int getSelectedDuration();
    float priceEuroPerYear;
    float priceCHBTPerYear;
    float priceEuroTotal;
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
    void on_activateSharingOption_clicked();
    void on_passwordField1_textChanged();
    void on_passwordField2_textChanged();
};

#endif // UPLOADFILEDIALOG_H