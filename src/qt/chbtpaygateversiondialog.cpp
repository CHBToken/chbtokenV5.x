#include "chbtpaygateversiondialog.h"
#include "ui_chbtpaygateversiondialog.h"
#include "clientmodel.h"

#include "version.h"

CHBTPayGateVersionDialog::CHBTPayGateVersionDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CHBTPayGateVersionDialog)
{
    ui->setupUi(this);
    QString paygate = "./CHBTPaygate.exe";
    qApp->setOverrideCursor(Qt::WaitCursor);
    QCoreApplication::processEvents();
    QStringList arguments;
    arguments << "Version";
    QProcess* myProcess = new QProcess(this);
    myProcess->start(paygate, arguments);
    myProcess->waitForFinished();
    int chbtgateEnabled = myProcess->exitCode();
    QString p_stdout = myProcess->readAll();
    while (qApp->overrideCursor()) //be careful application may have been lock several times ...
        qApp->restoreOverrideCursor();
    QCoreApplication::processEvents();
    if (chbtgateEnabled == 0)
    {
        ui->chbtPaygateInfo->appendPlainText(p_stdout);
    }
    else
    {
        ui->chbtPaygateInfo->appendPlainText("Can not determine Version information");
    }

    // QPlanTextEdit
}


CHBTPayGateVersionDialog::~CHBTPayGateVersionDialog()
{
    delete ui;
}

void CHBTPayGateVersionDialog::on_buttonBox_accepted()
{
    close();
}

void CHBTPayGateVersionDialog::on_pushButton_clicked()
{
    close();
}