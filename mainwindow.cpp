#include "mainwindow.h"
#include "ui_mainwindow.h"

using namespace std;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

bool CheckJsonValidate(const QString& in)
{
    QJsonDocument doc = QJsonDocument::fromJson(in.toUtf8());

    // check validity of the document
    if(!doc.isNull())
    {
        if(!doc.isObject())
            return false;
    }
    else
        return false;

    return true;
}

void MainWindow::on_pushButton_2_clicked()
{
    const QString jsonText = ui->textEdit->toPlainText();

    if(CheckJsonValidate(jsonText))
    {
        //save
        QString filename = QFileDialog::getSaveFileName(this, tr("Сохранить JSON файл"), "./", tr("JSON files (*.json)"));
        if (filename != "")
        {
            ofstream fileOut(filename.toStdString());
            fileOut << jsonText.toStdString();

            QMessageBox msg;
            msg.setText("Файл сохранен!");
            msg.exec();
        }
    }
    else
    {
        //errmsg
        QMessageBox msg;
        msg.setText("Ошибка синтаксиса JSON");
        msg.exec();
    }
}

void MainWindow::on_pushButton_clicked()
{
    ui->textEdit->setText("");
    download_by_url();
    get_data();
}


void MainWindow::get_data()
{
    QUrl url(ui->lineEdit->text());
    QNetworkRequest request;
    request.setUrl(url);
    //http://kappa.cs.karelia.ru/~dimitrov/cross2020/test.json
    manager->get(request);
}
void MainWindow::download_success(QNetworkReply *reply)
{
    ui->textEdit->setText(reply->readAll());
}

void MainWindow::download_by_url()
{
    manager = new QNetworkAccessManager();

    connect(manager, &QNetworkAccessManager::finished, this, &MainWindow::download_success);
}
