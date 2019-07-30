#include "clickableimage.h"

ClickableImage::ClickableImage(QWidget *parent) : QLabel(parent)
{
    this->setText("lol");
}

void ClickableImage::mousePressEvent(QMouseEvent *eve )
{
    if ( eve->button() == Qt::LeftButton )
    {
        emit leftButtonPressed(this);
        this->setText("");
        this->setPixmap(QPixmap(":/krawedzie_kanciaste_elastyczna_deska.jpg"));
    }
    else if ( eve->button() == Qt::RightButton )
        emit rightButtonPressed(this);
    else if ( eve->button() == Qt::MidButton )
        emit middleButtonPressed(this);
}

void ClickableImage::mouseReleaseEvent(QMouseEvent *eve )
{
    if ( eve->button() == Qt::LeftButton )
        emit leftButtonReleased(this);
    else if ( eve->button() == Qt::RightButton )
        emit rightButtonReleased(this);
    else if ( eve->button() == Qt::MidButton )
        emit middleButtonReleased(this);
}

void ClickableImage::enterEvent(QEvent* eve)
{
    emit mouseEntered(this);
}

void ClickableImage::leaveEvent(QEvent* eve)
{
    emit mouseLeft(this);
}
