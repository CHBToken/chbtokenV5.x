#include "viewdocumentsdialog.h"
#include "ui_viewdocumentsdialog.h"
#include "clientmodel.h"
#include "util.h"

#include "version.h"


void ViewDocumentsDialog::on_tableViewDocuments_doubleClicked(const QModelIndex& index)
{
    QString filename = ui->tableViewDocuments->model()->data(ui->tableViewDocuments->model()->index(index.row(), 2)).toString();
    QString hash = ui->tableViewDocuments->model()->data(ui->tableViewDocuments->model()->index(index.row(), 3)).toString();
    QString valu = ui->tableViewDocuments->model()->data(ui->tableViewDocuments->model()->index(index.row(), index.column())).toString();
    QString cryptFile = ui->tableViewDocuments->model()->data(ui->tableViewDocuments->model()->index(index.row(), 4)).toString();
    QString sharedCryptFile = ui->tableViewDocuments->model()->data(ui->tableViewDocuments->model()->index(index.row(), 5)).toString();

    //QMessageBox::StandardButton retval = QMessageBox::information(this, "DEBUG OUTPUT",
    //    "Col: " + QString::number(index.column()) + " Row:" + QString::number(index.row()) + " => " + valu + " => Hash: " + hash + " => filename: " + filename
    //,
    //QMessageBox::Ok);
    if (index.column() == 2)
    {
        // Start the explorer with the data file
        QString filepath = QString::fromStdString(GetDefaultTrustCenterPath().string()) + "\\Fs\\" + hash;
        QDesktopServices::openUrl(QUrl::fromLocalFile(filepath));
    }
    if (index.column() == 3)
    {
        qApp->setOverrideCursor(Qt::WaitCursor);
        QCoreApplication::processEvents();
        QStringList arguments;
        arguments << "Signature" << "-h" << hash;
        QProcess* myProcess = new QProcess(myParent);
        myProcess->start(program, arguments);
        myProcess->waitForFinished();
        int retval = myProcess->exitCode();
        QString p_stdout = myProcess->readAll();
        while (qApp->overrideCursor()) //be careful application may have been lock several times ...
            qApp->restoreOverrideCursor();
        QCoreApplication::processEvents();
    }
    if (index.column() == 4 && cryptFile != "NO")
    {
        // Start the explorer with the data file
        QString filepath = QString::fromStdString(GetDefaultTrustCenterPath().string()) + "\\Fs\\" + hash;
        QDesktopServices::openUrl(QUrl::fromLocalFile(filepath));
    }
    if (index.column() == 5 && sharedCryptFile != "NO")
    {
        // Start the explorer with the data file
        QString filepath = QString::fromStdString(GetDefaultTrustCenterPath().string()) + "\\Fs\\" + hash;
        QDesktopServices::openUrl(QUrl::fromLocalFile(filepath));
    }
}

ViewDocumentsDialog::ViewDocumentsDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ViewDocumentsDialog)
{
    myParent = parent;
    ui->setupUi(this);
    ui->RenewTime->setEnabled(false);

    ui->tableViewDocuments->setColumnCount(6);
    ui->tableViewDocuments->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableViewDocuments->setEditTriggers(QAbstractItemView::NoEditTriggers);


    // Call the gateway
    qApp->setOverrideCursor(Qt::WaitCursor);
    QCoreApplication::processEvents();
    QStringList arguments;
    arguments << "Database" << "-r" ;
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
        if (!json_doc.isNull() && json_doc.isArray())
        {
            auto json_array = json_doc.array();
            int recordCount = json_array.count();
            ui->tableViewDocuments->setRowCount(recordCount);
            int ii = 0;
            for (QJsonValueRef e : json_array)
            {
                auto varObject = e.toObject();
                QVariantMap variantMap = varObject.toVariantMap();

                auto a1 = variantMap["Filename"].value<QString>();
                auto a2 = variantMap["Hash"].value<QString>();
                auto a3 = variantMap["TransactionId"].value<QString>();
                auto a4 = variantMap["CHBTCost"].value<QString>();
                auto a5 = variantMap["EURCost"].value<QString>();
                auto a6 = variantMap["CreateDate"].value<QString>();
                auto a7 = variantMap["Duration"].value<QString>();
                auto a8 = variantMap["CryptoContainer"].value<QString>();
                auto a9 = variantMap["CryptoContainerShared"].value<QString>();
                ui->tableViewDocuments->setItem(ii, 0, new QTableWidgetItem(a6)); // Signing Date
                ui->tableViewDocuments->setItem(ii, 1, new QTableWidgetItem(a7)); // End Date
                ui->tableViewDocuments->setItem(ii, 2, new QTableWidgetItem(a1)); // File Name
                ui->tableViewDocuments->setItem(ii, 3, new QTableWidgetItem(a2)); // SignedHash
                if(a8=="")
                    ui->tableViewDocuments->setItem(ii, 4, new QTableWidgetItem("NO")); // IsUploaded
                else
                    ui->tableViewDocuments->setItem(ii, 4, new QTableWidgetItem(a8)); // IsUploaded
                if(a9 == "")
                    ui->tableViewDocuments->setItem(ii, 5, new QTableWidgetItem("NO")); // HasSharedSecret
                else
                    ui->tableViewDocuments->setItem(ii, 5, new QTableWidgetItem(a9)); // HasSharedSecret

                ii++;
            }
        }
    }
    else
    {
        //ui->payAndUpload->setEnabled(false);
    }


    //for (int ii = 0; ii < 30; ii++)
    //{
    //    ui->tableViewDocuments->setItem(ii, 0, new QTableWidgetItem("Hello #1"));
    //    ui->tableViewDocuments->setItem(ii, 1, new QTableWidgetItem("Hello #2"));
    //    ui->tableViewDocuments->setItem(ii, 2, new QTableWidgetItem("Hello #3"));
    //    ui->tableViewDocuments->setItem(ii, 3, new QTableWidgetItem("Hello #4"));
    //    ui->tableViewDocuments->setItem(ii, 4, new QTableWidgetItem("Hello #5"));
    //    ui->tableViewDocuments->setItem(ii, 5, new QTableWidgetItem("Hello #6"));
    //}
}


ViewDocumentsDialog::~ViewDocumentsDialog()
{
    delete ui;
}

void ViewDocumentsDialog::on_buttonBox_accepted()
{
    close();
}

void ViewDocumentsDialog::on_pushButton_clicked()
{
    close();
}
