#ifndef PURCHASEDIALOG_H
#define PURCHASEDIALOG_H

#include <QDialog>
#include <QProcess>
#include <QMessageBox>
#include <QDebug>
#include <QRegExp>
#include "walletmodel.h"
#include "addressbookpage.h"


namespace Ui {
    class PurchaseDialog;
}
class ClientModel;

/** "Purchase" dialog box */
class PurchaseDialog : public QDialog
{
    Q_OBJECT

public:
    QWidget *myParent;
    explicit PurchaseDialog(QWidget *parent = 0);
    ~PurchaseDialog();
    WalletModel* walletModel;
    ClientModel* clientModel;
    void setModel(WalletModel* walletModel, ClientModel* clientModel);
 

private:
    Ui::PurchaseDialog *ui;
    QString program = "./CHBTPaygate.exe";



private slots:
    void on_buttonBox_accepted();
    void on_purchaseCHBToken_clicked();
    void on_selectReceivingAddress_clicked();
    void on_euroAmount_textChanged();
};

#endif // PURCHASEDIALOG_H