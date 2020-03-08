#include "purchasedialog.h"
#include "ui_purchasedialog.h"
#include "clientmodel.h"
#include "base58.h"

#include "addressbookpage.h" 


#include "version.h"

PurchaseDialog::PurchaseDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PurchaseDialog)
{
    myParent = parent;
    ui->setupUi(this);
}


PurchaseDialog::~PurchaseDialog()
{
    delete ui;
}

void PurchaseDialog::setModel(WalletModel* walletModel, ClientModel* clientModel)
{
    this->walletModel = walletModel;
    this->clientModel = clientModel;
}



void PurchaseDialog::on_buttonBox_accepted()
{
    close();
}



void PurchaseDialog::on_selectReceivingAddress_clicked()
{
    AddressBookPage* addressBookPage = new AddressBookPage(AddressBookPage::ForSelecting, AddressBookPage::SelectionTab, this);
    addressBookPage->setModel(walletModel->getAddressTableModel());
    addressBookPage->exec(); 

    ui->receivingAddress->setText(addressBookPage->selectedAddress);
}

void PurchaseDialog::on_purchaseCHBToken_clicked()
{
    QMessageBox msgBox;

    // Validate Entires
    //CBitcoinAddress addressParsed(address.toStdString());
    
    CBitcoinAddress addressParsed(ui->receivingAddress->text().toLocal8Bit().constData());
    if(!(addressParsed.IsValid()))
    {
        msgBox.setText("The address is not valid. ");
        msgBox.setInformativeText("Please check your address?");
        msgBox.setStandardButtons(QMessageBox::Ok);
        msgBox.setDefaultButton(QMessageBox::Ok);    
        msgBox.exec();    
        return;
    }
    int purchaseAmount = ui->euroAmount->text().toInt();
    if(purchaseAmount < 10 || purchaseAmount > 500)
    {
        msgBox.setText("The purchase amount it not valid. ");
        msgBox.setInformativeText("Please enter a valid amount?");
        msgBox.setStandardButtons(QMessageBox::Ok);
        msgBox.setDefaultButton(QMessageBox::Ok);    
        msgBox.exec();    
        return;
    }    
    QString eMail = ui->enterEmailAddress->text();
    QString eMailVerify = ui->reEnterEmailAddress->text();
    if (eMail != eMailVerify)
    {
        msgBox.setText("EMail Address not equal. ");
        msgBox.setInformativeText("EMail Address are not equal. Please verify!");
        msgBox.setStandardButtons(QMessageBox::Ok);
        msgBox.setDefaultButton(QMessageBox::Ok);
        msgBox.exec();
        return;
    }

    QRegExp mailREX("\\b[A-Z0-9._%+-]+@[A-Z0-9.-]+\\.[A-Z]{2,4}\\b");
    mailREX.setCaseSensitivity(Qt::CaseInsensitive);
    mailREX.setPatternSyntax(QRegExp::RegExp);
    if(mailREX.exactMatch(eMail) == false)
    {
        msgBox.setText("EMail Address not valid. ");
        msgBox.setInformativeText("EMail Address not valid. Please check!");
        msgBox.setStandardButtons(QMessageBox::Ok);
        msgBox.setDefaultButton(QMessageBox::Ok);
        msgBox.exec();
        return;
    }

    QStringList arguments;
    arguments << "Payment" << "-a" << ui->euroAmount->text() << "-m" << eMail << "-w" << ui->receivingAddress->text();
    QProcess *myProcess = new QProcess(myParent);
    myProcess->start(program, arguments);
    myProcess->waitForFinished();
    int retval = myProcess->exitCode();

    if (retval == 0)
    {
        msgBox.setText("Your payment has been processed. ");
        msgBox.setInformativeText("Please check your accounts?");
        msgBox.setStandardButtons(QMessageBox::Ok);
        msgBox.setDefaultButton(QMessageBox::Ok);
        msgBox.exec();
        close();
    }
    else
    {
        msgBox.setText("Your payment has NOT been processed. ");
        msgBox.setInformativeText("Please retry payment or contact support for details.");
        msgBox.setStandardButtons(QMessageBox::Ok);
        msgBox.setDefaultButton(QMessageBox::Ok);
        msgBox.exec();
    }
}

void PurchaseDialog::on_euroAmount_textChanged()
{
    qApp->setOverrideCursor(Qt::WaitCursor);
    QCoreApplication::processEvents();

    int euroAmount = ui->euroAmount->text().toInt();
    QStringList arguments;
    arguments << "Price" << "-a" << ui->euroAmount->text();
    QProcess* myProcess = new QProcess(myParent);
    myProcess->start(program, arguments);
    myProcess->waitForFinished();
    int retval = myProcess->exitCode();
    QString p_stdout = myProcess->readAll();

    if (retval == 0)
    {
        ui->chbtokenAmount->setText(p_stdout);
    }
    else
    {
        ui->chbtokenAmount->setText("");
    }

    while (qApp->overrideCursor()) //be careful application may have been lock several times ...
        qApp->restoreOverrideCursor();
    QCoreApplication::processEvents();


}

