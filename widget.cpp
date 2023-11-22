#include "widget.h"
#include "ui_widget.h"
#include <QStyle>
#include <QFileDialog>
#include <QDir>
#include <QTime>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    muted = false;

    // Buttons style:
    ui->pbOpen->setIcon(style()->standardIcon(QStyle::SP_DriveCDIcon));
    ui->pbPrev->setIcon(style()->standardIcon(QStyle::SP_MediaSkipBackward));
    ui->pbPause->setIcon(style()->standardIcon(QStyle::SP_MediaPause));
    ui->pbStop->setIcon(style()->standardIcon(QStyle::SP_MediaStop));
    ui->pbNext->setIcon(style()->standardIcon(QStyle::SP_MediaSkipForward));
    ui->pbPlay->setIcon(style()->standardIcon(QStyle::SP_MediaPlay));
    ui->pbMute->setIcon(style()->standardIcon(QStyle::SP_MediaVolume));

    // Player init:
    m_player = new QMediaPlayer(this);
    m_player->setVolume(70);
    ui->lbVolume->setText(QString("Volume: ").append(QString::number(m_player->volume())));
    ui->hsVolume->setValue(m_player->volume());

    connect(m_player, &QMediaPlayer::positionChanged, this, &Widget::on_position_changed);
    connect(m_player, &QMediaPlayer::durationChanged, this, &Widget::on_duration_changed);

    // Playlist init:
    m_playlist_model = new QStandardItemModel(this);
    ui->tvPlaylist->setModel(m_playlist_model);
    m_playlist_model->setHorizontalHeaderLabels(QStringList() << "Audio track" << "File path");
    ui->tvPlaylist->hideColumn(1);
    ui->tvPlaylist->horizontalHeader()->setStretchLastSection(true);
    ui->tvPlaylist->setEditTriggers(QAbstractItemView::NoEditTriggers);

    m_playlist = new QMediaPlaylist(m_player);
    m_player->setPlaylist(m_playlist);
}

Widget::~Widget()
{
    delete m_player;
    delete ui;    
}

void Widget::on_pbOpen_clicked()
{
//    QString file = QFileDialog::getOpenFileName
//            (
//                this,
//                tr("Openfile"),
//                "C:\\Users\\ITMEDIA_PC\\music",
//                tr("Audio files (*.mp3 *.flac)")
//                );
//    ui->lbTextComposition->setText(file.split('/').last());
//    this->setWindowTitle(QString("Winamp -").append(file.split('/').last()));
//    m_player->setMedia(QUrl::fromLocalFile(file));

    QStringList files = QFileDialog::getOpenFileNames
            (
                this,
                "Open files",
                "C:\\Users\\ITMEDIA_PC\\music",
                "Audio files (*.mp3 *.flac)"
                );

    for(QString filesPath: files)
    {
            QList<QStandardItem*> items;
            items.append(new QStandardItem(QDir(filesPath).dirName()));
            items.append(new QStandardItem(filesPath));
            m_playlist_model->appendRow(items);
            m_playlist->addMedia(QUrl(filesPath));
    }
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

void Widget::on_position_changed(qint64 position)
{
    ui->hsProgress->setValue(position);
    QTime qt_position = QTime::fromMSecsSinceStartOfDay(position);
    ui->lbProgress->setText(qt_position.toString("mm:ss"));
}

void Widget::on_duration_changed(qint64 duration)
{
    ui->hsProgress->setMaximum(duration);
    QTime qt_duration = QTime::fromMSecsSinceStartOfDay(duration);
    ui->lbDuration->setText(qt_duration.toString("mm:ss"));
}


void Widget::on_hsProgress_sliderMoved(int position)
{
    m_player->setPosition(position);
}


void Widget::on_pbMute_clicked()
{
    muted = !muted;
    m_player->setMuted(muted);
    ui->pbMute->setIcon(style()->standardIcon(muted?QStyle::SP_MediaVolumeMuted:QStyle::SP_MediaVolume));
}


void Widget::on_pbPrev_clicked()
{
    m_playlist->previous();
}


void Widget::on_pbNext_clicked()
{
    m_playlist->next();
}

