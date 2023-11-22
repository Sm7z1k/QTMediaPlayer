#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QMediaPlayer>
#include <QMediaPlaylist>
#include <QStandardItemModel>

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private slots:
    void on_pbOpen_clicked();

    void on_hsVolume_valueChanged(int value);

    void on_pbPlay_clicked();

    void on_position_changed(qint64 position);

    void on_duration_changed(qint64 duration);

    void on_hsProgress_sliderMoved(int position);

    void on_pbMute_clicked();

    void on_pbPrev_clicked();

    void on_pbNext_clicked();

private:
    Ui::Widget *ui;

    QMediaPlayer* m_player;

    bool muted;

    QMediaPlaylist* m_playlist;

    QStandardItemModel* m_playlist_model;
};
#endif // WIDGET_H
