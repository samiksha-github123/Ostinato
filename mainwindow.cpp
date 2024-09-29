#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFile>
#include <QFileDialog>
#include <QTextStream>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setCentralWidget(ui->textEdit);

    if (file_path.isEmpty()) {
        setWindowTitle("MyNotepad");
    } else {
        QFileInfo fileInfo(file_path);
        setWindowTitle(fileInfo.fileName() + " - MyNotepad");
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionNew_triggered()
{

    if (!ui->textEdit->toPlainText().isEmpty()) {
        QMessageBox::StandardButton reply;
        reply = QMessageBox::question(this, "New Document","There is unsaved text in the current document. Do you want to create a new document in a separate window?",QMessageBox::Yes | QMessageBox::No);

        if (reply == QMessageBox::Yes) {
               MainWindow *newWindow = new MainWindow();
                newWindow->show();
        } else {
                file_path = "";
                ui->textEdit->setText("");

                if (file_path.isEmpty()) {
                    setWindowTitle("MyNotepad");
                } else {
                    QFileInfo fileInfo(file_path);
                    setWindowTitle(fileInfo.fileName() + " - MyNotepad");
                }    if (file_path.isEmpty()) {
                    setWindowTitle("MyNotepad");
                } else {
                    QFileInfo fileInfo(file_path);
                    setWindowTitle(fileInfo.fileName() + " - MyNotepad");
                }
        }
    } else {

            file_path = "";
            ui->textEdit->setText("");

            if (file_path.isEmpty()) {
                setWindowTitle("MyNotepad");
            } else {
                QFileInfo fileInfo(file_path);
                setWindowTitle(fileInfo.fileName() + " - MyNotepad");
            }
        }
}


void MainWindow::on_actionOpen_triggered()
{
    QString file_name = QFileDialog::getOpenFileName(this,"Open the file");
    QFile file(file_name);
    file_path=file_name;
    if(!file.open(QFile::ReadOnly | QFile::Text)){
        QMessageBox::warning(this,"..","file not open");
        return;
    }
    QTextStream in (&file);
    QString text = in.readAll();
    ui->textEdit->setText(text);
    file.close();

    if (file_path.isEmpty()) {
        setWindowTitle("MyNotepad");
    } else {
        QFileInfo fileInfo(file_path);
        setWindowTitle(fileInfo.fileName() + " - MyNotepad");
    }
}


void MainWindow::on_actionSave_triggered()
{

    if (file_path.isEmpty()){
        on_actionSave_As_triggered();
        return;
    }
    QFile file(file_path);
    if(!file.open(QFile::WriteOnly | QFile::Text)){
        QMessageBox::warning(this,"..","file not open");
        return;
    }
    QTextStream out (&file);
    QString text = ui->textEdit->toPlainText();
    out<<text;
    file.flush();
    file.close();

    if (file_path.isEmpty()) {
        setWindowTitle("MyNotepad");
    } else {
        QFileInfo fileInfo(file_path);
        setWindowTitle(fileInfo.fileName() + " - MyNotepad");
    }
}


void MainWindow::on_actionSave_As_triggered()
{
    QString file_name = QFileDialog::getSaveFileName(this,"Open the file");
    QFile file(file_name);
    file_path=file_name;;
    if(!file.open(QFile::WriteOnly | QFile::Text)){
        QMessageBox::warning(this,"..","file not open");
        return;
    }
    QTextStream out (&file);
    QString text = ui->textEdit->toPlainText();
    out<<text;
    file.flush();
    file.close();

    if (file_path.isEmpty()) {
        setWindowTitle("MyNotepad");
    } else {
        QFileInfo fileInfo(file_path);
        setWindowTitle(fileInfo.fileName() + " - MyNotepad");
    }
}


void MainWindow::on_actionExit_triggered()
{
    QApplication::quit();
}


void MainWindow::on_actionCut_triggered()
{
    ui->textEdit->cut();
}


void MainWindow::on_actionCopy_triggered()
{
    ui->textEdit->copy();
}


void MainWindow::on_actionPaste_triggered()
{
    ui->textEdit->paste();
}


void MainWindow::on_actionRedo_triggered()
{
    ui->textEdit->redo();
}


void MainWindow::on_actionUndo_triggered()
{
    ui->textEdit->undo();
}

