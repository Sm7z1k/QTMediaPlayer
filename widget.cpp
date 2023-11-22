#include "widget.h"
#include "ui_widget.h"
#include <QStyle>
#include <QFileDialog>
#include <QDir>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    // Buttons style:
    ui->pbOpen->setIcon(style()->standardIcon(QStyle::SP_DriveCDIcon));
    ui->pbPrev->setIcon(style()->standardIcon(QStyle::SP_MediaSkipBackward));
    ui->pbPause->setIcon(style()->standardIcon(QStyle::SP_MediaPause));
    ui->pbStop->setIcon(style()->standardIcon(QStyle::SP_MediaStop));
    ui->pbNext->setIcon(style()->standardIcon(QStyle::SP_MediaSkipForward));
    ui->pbPlay->setIcon(style()->standardIcon(QStyle::SP_MediaPlay));

    // Player init:
    m_player = new QMediaPlayer(this);
    m_player->setVolume(70);
    ui->lbVolume->setText(QString("Volume: ").append(QString::number(m_player->volume())));
    ui->hsVolume->setValue(m_player->volume());
}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_pbOpen_clicked()
{
    QString file = QFileDialog::getOpenFileName
            (
                this,
                tr("Openfile"),
                "C:\\Users\\ITMEDIA_PC\\music",
                tr("Audio files (*.mp3 *.flac)")
                );
    ui->lbTextComposition->setText(file);
    m_player->setMedia(QUrl::fromLocalFile(file));
}

void Widget::on_hsVolume_valueChanged(int value)
{
    m_player->setVolume(value);
    ui->lbVolume->setText(QString("Volume: ").append(QString::number(m_player->volume())));
}

void Widget::on_pbPlay_clicked()
{
    m_player->play();
}

