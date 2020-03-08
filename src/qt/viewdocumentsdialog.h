#ifndef VIEWDOCUMENTSDIALOG_H
#define VIEWDOCUMENTSDIALOG_H

#include <QDialog>
#include <QMessageBox>
#include <QProcess>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QVariantMap>
#include <QByteArray>
#include <QUuid>
#include <QTextStream>
#include <QMessageBox>
#include <QUrl>
#include <QDesktopServices>

namespace Ui {
    class ViewDocumentsDialog;
}
class ClientModel;

/** "Upload" dialog box */
class ViewDocumentsDialog : public QDialog
{
    Q_OBJECT

public:
    QWidget* myParent;
    explicit ViewDocumentsDialog(QWidget *parent = 0);
    ~ViewDocumentsDialog();

    void setModel(ClientModel *model);
private:
    Ui::ViewDocumentsDialog *ui;
    QString program = "./CHBTPaygate.exe";

private slots:
    void on_buttonBox_accepted();
    void on_pushButton_clicked();
    void on_tableViewDocuments_doubleClicked(const QModelIndex& index);
};

#endif // VIEWDOCUMENTSDIALOG_H