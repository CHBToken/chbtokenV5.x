#include "uploadfiledialog.h"
#include "ui_uploadfiledialog.h"
#include "clientmodel.h"
#include "walletmodel.h"
#include "optionsmodel.h"
#include "bitcoinunits.h"
#include "ui_sendcoinsentry.h"
#include "sendcoinsentry.h"
#include "aboutdialog.h"
#include "util.h"
#include "version.h"

#include "version.h"

UploadFileDialog::UploadFileDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::UploadFileDialog)
{
    myParent = parent;
    ui->setupUi(this);
    ui->payAndUpload->setEnabled(false);
    ui->activateSharingOption->setChecked(false);
    ui->passwordField1->setEnabled(false);
    ui->passwordField2->setEnabled(false);

    QObject::connect(ui->activateSharingOption, SIGNAL(clicked()), this, SLOT(on_checkBox_clicked()));
    ui->fileName->setFocus();
}

UploadFileDialog::~UploadFileDialog()
{
    delete ui;
}

void UploadFileDialog::setModel(WalletModel *model)
{
        this->model = model;

        if (model && model->getOptionsModel())
        {
            float balance = model->getBalance();
            spendableBalance = balance / 100000000;
            ui->walletBalance->setText(QString::number(spendableBalance));
            connect(model, SIGNAL(balanceChanged(qint64, qint64, qint64, qint64)), this, SLOT(setBalance(qint64, qint64, qint64, qint64)));
        }
}

void UploadFileDialog::on_activateSharingOption_clicked()
{
    ui->passwordField1->setText("");
    ui->passwordField2->setText("");

    on_fileName_textChanged();
    UpdatePasswordFields();
}

void UploadFileDialog::UpdatePasswordFields()
{
    ui->passwordField1->setEnabled(ui->activateSharingOption->isChecked());
    ui->passwordField2->setEnabled(ui->activateSharingOption->isChecked());

    if (ui->activateSharingOption->isChecked() == false)
    {
        ui->passwordField1->setStyleSheet("QLineEdit {background-color: white;}");
        ui->passwordField2->setStyleSheet("QLineEdit {background-color: white;}");
    }
    else
    {
        if (ui->passwordField1->text().length() < minPasswordLength)
        {
            ui->passwordField1->setStyleSheet("QLineEdit {background-color: lightsalmon;}");
        }
        else
        {
            ui->passwordField1->setStyleSheet("QLineEdit {background-color: white;}");
        }
        if (ui->passwordField2->text().length() < minPasswordLength)
        {
            ui->passwordField2->setStyleSheet("QLineEdit {background-color: lightsalmon;}");
        }
        else
        {
            ui->passwordField2->setStyleSheet("QLineEdit {background-color: white;}");
        }

        if (ui->passwordField1->text().length() < minPasswordLength || ui->passwordField2->text().length() < minPasswordLength || ui->passwordField1->text() != ui->passwordField2->text())
        {
            ui->passwordField2->setStyleSheet("QLineEdit {background-color: lightsalmon;}");
        }
        else
        {
            ui->passwordField2->setStyleSheet("QLineEdit {background-color: white;}");
        }
    }

    checkPayAndUploadButtonState();

}
void UploadFileDialog::on_passwordField1_textChanged()
{
    UpdatePasswordFields();
}
void UploadFileDialog::on_passwordField2_textChanged()
{
    UpdatePasswordFields();
}


void UploadFileDialog::on_buttonBox_accepted()
{
    close();
}

void UploadFileDialog::setBalance(qint64 spendable, qint64 stake, qint64 unconfirmend, qint64 dontknow)
{
    float balance = spendable;
    spendableBalance = balance / 100000000;
    ui->walletBalance->setText(QString::number(spendableBalance));
}


void UploadFileDialog::on_fileSelect_clicked()
{
    QStringList fileNames;
    QFileDialog* fileDialog = new QFileDialog();
    if (fileDialog->exec())
    {
        fileNames = fileDialog->selectedFiles();
        if (fileNames.count() != 0)
        {
            ui->fileName->setText(fileNames[0]);
        }
    }
}

void UploadFileDialog::on_rB1Y_clicked()
{
    on_fileName_textChanged();
}
void UploadFileDialog::on_rB2Y_clicked()
{
    on_fileName_textChanged();
}
void UploadFileDialog::on_rB3Y_clicked()
{
    on_fileName_textChanged();
}
void UploadFileDialog::on_rB4Y_clicked()
{
    on_fileName_textChanged();
}
void UploadFileDialog::on_rB5Y_clicked()
{
    on_fileName_textChanged();
}
void UploadFileDialog::on_rB6Y_clicked()
{
    on_fileName_textChanged();
}
void UploadFileDialog::on_rB7Y_clicked()
{
    on_fileName_textChanged();
}
void UploadFileDialog::on_rB8Y_clicked()
{
    on_fileName_textChanged();
}
void UploadFileDialog::on_rB9Y_clicked()
{
    on_fileName_textChanged();
}
void UploadFileDialog::on_rB10Y_clicked()
{
    on_fileName_textChanged();
}

void UploadFileDialog::on_fileName_textChanged()
{
    qApp->setOverrideCursor(Qt::WaitCursor);
    QCoreApplication::processEvents();
    QFileInfo fi(ui->fileName->text());
    QMessageBox msgBox;
    if (fi.exists())
    {

        ui->sizeOfFile->setText(QString::number(fi.size() / 1024 / 1024));
        ui->fileName->setStyleSheet("QLineEdit {background-color: white;}");
        int duration = getSelectedDuration();

        // Call the Backend for SignatureCost
        //SignPrice -s SizeinMB -d durationInYears -u for Upload -x for NewKey
        QStringList arguments;
        if (ui->activateSharingOption->isChecked())
        {
            arguments << "SignPrice" << "-s" << QString::number(fi.size() / 1024 / 1024) << "-d" << QString::number(duration) << "-u" << "-x";
        }
        else
        {
            arguments << "SignPrice" << "-s" << QString::number(fi.size() / 1024 / 1024) << "-d" << QString::number(duration) << "-u";
        }
        QProcess* myProcess = new QProcess(myParent);
        myProcess->start(program, arguments);
        myProcess->waitForFinished();
        int retval = myProcess->exitCode();
        QString p_stdout = myProcess->readAll();
        while (qApp->overrideCursor()) //be careful application may have been lock several times ...
            qApp->restoreOverrideCursor();
        QCoreApplication::processEvents();
        if (retval == 0)
        {
            QByteArray json_bytes = p_stdout.toLocal8Bit();
            auto json_doc = QJsonDocument::fromJson(json_bytes);
            if (!json_doc.isNull() && json_doc.isObject())
            {
                QJsonObject json_obj = json_doc.object();
                QVariantMap result = json_obj.toVariantMap();
                priceEuroPerYear = result["PriceEuroPerYear"].value<float>();
                priceCHBTPerYear = result["PriceCHBTPerYear"].value<float>();
                priceEuroTotal = result["PriceEuroTotal"].value<float>();
                priceCHBTTotal = result["PriceCHBTTotal"].value<float>();
                chbtTrustCenter = result["TargetWallet"].value<QString>();

                ui->costPerYear->setText(QString::number(priceCHBTPerYear));
                ui->totalCost->setText(QString::number(priceCHBTTotal));
                ui->totalCost->setText(QString::number(priceCHBTTotal));
                checkPayAndUploadButtonLocked = false;
                checkPayAndUploadButtonState();
            }
        }
        else
        {
            ui->payAndUpload->setEnabled(false);
            checkPayAndUploadButtonLocked = true;
        }
    }
    else
    {
        ui->fileName->setStyleSheet("QLineEdit {background-color: lightsalmon;}");
        ui->sizeOfFile->setText("");
        ui->payAndUpload->setEnabled(false);
        checkPayAndUploadButtonLocked = true;
    }
    while (qApp->overrideCursor()) //be careful application may have been lock several times ...
        qApp->restoreOverrideCursor();
    QCoreApplication::processEvents();
}

void UploadFileDialog::checkPayAndUploadButtonState()
{
    if (checkPayAndUploadButtonLocked == false)
    {
        if (

            ((spendableBalance > priceCHBTTotal) && ui->activateSharingOption->isChecked() == false) ||
            ((spendableBalance > priceCHBTTotal) && ui->activateSharingOption->isChecked() == true && 
            (ui->passwordField1->text() == ui->passwordField2->text()) && ui->passwordField1->text().length() >= minPasswordLength)
            )
            ui->payAndUpload->setEnabled(true);
        else
            ui->payAndUpload->setEnabled(false);
    }
    else
    {
        ui->payAndUpload->setEnabled(false);
    }

}

int UploadFileDialog::getSelectedDuration()
{
    int duration = 1;

    if (ui->rB1Y->isChecked())
        duration = 1;
    else if (ui->rB2Y->isChecked())
        duration = 2;
    else if (ui->rB3Y->isChecked())
        duration = 3;
    else if (ui->rB4Y->isChecked())
        duration = 4;
    else if (ui->rB5Y->isChecked())
        duration = 5;
    else if (ui->rB6Y->isChecked())
        duration = 6;
    else if (ui->rB7Y->isChecked())
        duration = 7;
    else if (ui->rB8Y->isChecked())
        duration = 8;
    else if (ui->rB9Y->isChecked())
        duration = 9;
    else if (ui->rB10Y->isChecked())
        duration = 10;

    return duration;
}

void UploadFileDialog::on_payAndUpload_clicked()
{
    if (model && model->getOptionsModel())
    {
        // priceCHBTTotal

        QList<SendCoinsRecipient> myRecipients;

        SendCoinsEntry* sendCoinEntry = new SendCoinsEntry(); // qobject_cast<SendCoinsEntry*>(ui->entries->itemAt(i)->widget());
        sendCoinEntry->setModel(this->model);

        SendCoinsRecipient recep;
        recep.address = chbtTrustCenter;
        recep.label = "CHBT TRUST CENTER PAYMENT";
        recep.amount = priceCHBTTotal * 100000000; // Convert to CHBT from internal mCHBT

        myRecipients.append(recep);
        sendCoinEntry->setValue(recep);

        QStringList formatted;
        foreach(const SendCoinsRecipient & rcp, myRecipients)
        {
            formatted.append(tr("<b>%1</b> <br/>for %2<br/>to %3").arg(BitcoinUnits::formatWithUnit(model->getOptionsModel()->getDisplayUnit(), rcp.amount), ui->fileName->text(), "CHBT Trust Center Payment"));
        }
        QMessageBox::StandardButton retval = QMessageBox::question(this, tr("Confirm send coins"),
            tr("Are you sure you want to send %1?").arg(formatted.join(tr(" and "))),
            QMessageBox::Yes | QMessageBox::Cancel,
            QMessageBox::Cancel);

        if (retval != QMessageBox::Yes)
        {
            return;
        }

        WalletModel::UnlockContext ctx(model->requestUnlock());
        if (!ctx.isValid())
        {
            // Unlock wallet was cancelled
            return;
        }

        WalletModel::SendCoinsReturn sendstatus;

        sendstatus = model->sendCoins(myRecipients);

        switch (sendstatus.status)
        {
        case WalletModel::InvalidAddress:
            QMessageBox::warning(this, tr("Send Coins"),
                tr("The recipient address is not valid, please recheck."),
                QMessageBox::Ok, QMessageBox::Ok);
            break;
        case WalletModel::InvalidAmount:
            QMessageBox::warning(this, tr("Send Coins"),
                tr("The amount to pay must be larger than 0."),
                QMessageBox::Ok, QMessageBox::Ok);
            break;
        case WalletModel::AmountExceedsBalance:
            QMessageBox::warning(this, tr("Send Coins"),
                tr("The amount exceeds your balance."),
                QMessageBox::Ok, QMessageBox::Ok);
            break;
        case WalletModel::AmountWithFeeExceedsBalance:
            QMessageBox::warning(this, tr("Send Coins"),
                tr("The total exceeds your balance when the %1 transaction fee is included.").
                arg(BitcoinUnits::formatWithUnit(model->getOptionsModel()->getDisplayUnit(), sendstatus.fee)),
                QMessageBox::Ok, QMessageBox::Ok);
            break;
        case WalletModel::DuplicateAddress:
            QMessageBox::warning(this, tr("Send Coins"),
                tr("Duplicate address found, can only send to each address once per send operation."),
                QMessageBox::Ok, QMessageBox::Ok);
            break;
        case WalletModel::TransactionCreationFailed:
            QMessageBox::warning(this, tr("Send Coins"),
                tr("Error: Transaction creation failed!"),
                QMessageBox::Ok, QMessageBox::Ok);
            break;
        case WalletModel::TransactionCommitFailed:
            QMessageBox::warning(this, tr("Send Coins"),
                tr("Error: The transaction was rejected. This might happen if some of the coins in your wallet were already spent, such as if you used a copy of wallet.dat and coins were spent in the copy but not marked as spent here."),
                QMessageBox::Ok, QMessageBox::Ok);
            break;
        case WalletModel::Aborted: // User aborted, nothing to do
            break;
        case WalletModel::OK:
            qApp->setOverrideCursor(Qt::WaitCursor);
            
            QCoreApplication::processEvents();
            createProcessJson(ui->fileName->text(), recep, sendstatus.hex, getSelectedDuration(), ui->activateSharingOption->isChecked(),ui->passwordField1->text());
            processProcessJson(sendstatus.hex);
            accept();
            while (qApp->overrideCursor()) //be careful application may have been lock several times ...
                qApp->restoreOverrideCursor();
            QCoreApplication::processEvents();
            QMessageBox::information(this, "Process completed",
                "Your signing request was processed.",
                QMessageBox::Ok,
                QMessageBox::Ok);
            break;
        }
    }
    else
    {
        QMessageBox::warning(this, tr("Send Errrors"),
            tr("Model not loaded. Please retry."),
            QMessageBox::Ok, QMessageBox::Ok);
    }
}

bool UploadFileDialog::createProcessJson(QString filename, SendCoinsRecipient sendCoinRecipient, QString transactionId, int duration, bool isShared, QString password)
{
    // sign or signencrypt
    const QString jsonRequest = "{\"process\":\"signandencrypt\",\"filename\":\"" + filename + "\",\"amount\":" + QString::number(sendCoinRecipient.amount) + ",\"label\":\"" + sendCoinRecipient.label + "\",\"transactionid\":\"" + transactionId + "\",\"duration\":" + QString::number(duration) + ",\"shared\":"+QString::number(isShared) +",\"password\":\""+password+"\"}";

    QString datadir = QString::fromStdString(GetDefaultDataDir().string());
    QFile qFile(datadir + "/" + transactionId + ".request");
    if (qFile.open(QIODevice::WriteOnly)) {
        QTextStream out(&qFile); out << jsonRequest;
        qFile.close();
        return true;
    }
    else
    {
        QMessageBox msgBox;
        {
            msgBox.setText("ERROR during SignatureRequest");
            msgBox.setInformativeText("ERROR: Can not write request file. Please check your drive space and rights.");
            msgBox.setStandardButtons(QMessageBox::Ok);
            msgBox.setDefaultButton(QMessageBox::Ok);
            msgBox.exec();
        }
        return false;
    }
}

void UploadFileDialog::processProcessJson(QString transactionId)
{
    qApp->setOverrideCursor(Qt::WaitCursor);
    QCoreApplication::processEvents();
    QString datadir = QString::fromStdString(GetDefaultDataDir().string()) + "/" + transactionId + ".request";

    QStringList arguments;
    arguments << "Sign" << "-r" << datadir;
    QProcess* myProcess = new QProcess(myParent);
    myProcess->start(program, arguments);
    myProcess->waitForFinished();
    int retval = myProcess->exitCode();
    QString p_stdout = myProcess->readAll();
    if (retval == 0)
    {
        //QFile qFile(datadir);
        //qFile.remove();      
    }

    while (qApp->overrideCursor()) //be careful application may have been lock several times ...
        qApp->restoreOverrideCursor();
    QCoreApplication::processEvents();
}



