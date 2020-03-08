#ifndef SIGNINGHELPDIALOG_H
#define SIGNINGHELPDIALOG_H

#include <QDialog>

namespace Ui {
    class SigningHelpDialog;
}
class ClientModel;

/** "Signing Help" dialog box */
class SigningHelpDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SigningHelpDialog(QWidget *parent = 0);
    ~SigningHelpDialog();

    void setModel(ClientModel *model);
private:
    Ui::SigningHelpDialog *ui;

private slots:
    void on_buttonBox_accepted();
};

#endif // SIGNINGHELPDIALOG_H