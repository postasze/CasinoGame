#include "linesettingform.h"
#include <iostream>

using namespace std;

LineSettingForm::SquareElement::SquareElement(QGraphicsItem *parent, LineSettingForm *lineSettingForm,
    QGraphicsView *view, QPointF coordinates, quint16 reelNumber) : QGraphicsItem(parent)
{
    this->view = view;
    this->coordinates = coordinates;
    this->reelNumber = reelNumber;
    this->selected = false;
    this->lineSettingForm = lineSettingForm;
}

QRectF LineSettingForm::SquareElement::boundingRect() const
{
    return QRectF(0, 0, 49, 49);
}

QPainterPath LineSettingForm::SquareElement::shape() const
{
    QPainterPath painter;
    painter.addRect(0, 0, 49, 49);
    return painter;
}

void LineSettingForm::SquareElement::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->drawPath(shape());
    if(selected)
    {
        painter->setBrush(QBrush(Qt::red));
        painter->drawEllipse(QPoint(25, 25), 10, 10);
    }
}

void LineSettingForm::SquareElement::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if ( event->button() == Qt::LeftButton )
    {
        if(!lineSettingForm->isEditingEnabled)
            return;

        if(selected)
            return;

        this->lineSettingForm->clearReel(this->reelNumber);
        this->selected = true;
        this->lineSettingForm->updateLine();
    }
    //else if ( event->button() == Qt::RightButton );
    //else if ( event->button() == Qt::MidButton );
}
