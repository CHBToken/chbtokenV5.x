#ifndef CHBTPAYGATEVERSIONDIALOG_H
#define CHBTPAYGATEVERSIONDIALOG_H

#include <QDialog>
#include <QProcess>

namespace Ui {
    class CHBTPayGateVersionDialog;
}
class ClientModel;

/** "CHBT PayGate Version Help" dialog box */
class CHBTPayGateVersionDialog : public QDialog
{
    Q_OBJECT

public:
    explicit CHBTPayGateVersionDialog(QWidget *parent = 0);
    ~CHBTPayGateVersionDialog();

    void setModel(ClientModel *model);
private:
    Ui::CHBTPayGateVersionDialog *ui;

private slots:
    void on_buttonBox_accepted();
    void on_pushButton_clicked();
};

#endif // CHBTPAYGATEVERSIONDIALOG_H