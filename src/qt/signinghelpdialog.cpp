#include "signinghelpdialog.h"
#include "ui_signinghelpdialog.h"
#include "clientmodel.h"

#include "version.h"

SigningHelpDialog::SigningHelpDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SigningHelpDialog)
{
    ui->setupUi(this);
}


SigningHelpDialog::~SigningHelpDialog()
{
    delete ui;
}

void SigningHelpDialog::on_buttonBox_accepted()
{
    close();
}