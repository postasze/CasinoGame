#include "reelelement.h"
#include <iostream>

using namespace std;

ReelElement::ReelElement(QGraphicsSimpleTextItem *parent, QGraphicsView *view, ReelSettingForm *reelSettingForm,
             QPointF coordinates, bool emptyElement, quint16 reelNumber, quint16 symbol, ReelElement *previousElement) : QGraphicsSimpleTextItem("", parent)
{
    this->view = view;
    this->coordinates = coordinates;
    this->emptyElement = emptyElement;
    this->reelSettingForm = reelSettingForm;
    this->reelNumber = reelNumber;
    this->symbol = symbol;
    this->previousElement = previousElement;
}

QRectF ReelElement::boundingRect() const
{
    return QRectF(0, 0, 49, 49);
}

QPainterPath ReelElement::shape() const
{
    QPainterPath painter;
    painter.addRect(0, 0, 49, 49);
    return painter;
}

void ReelElement::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    if(emptyElement)
        painter->fillPath(shape(), Qt::yellow);
    else
        painter->fillPath(shape(), Qt::green);
    painter->drawPath(shape());

    if(!emptyElement)
        painter->drawText(19, 30, QString::number(symbol));
}

void ReelElement::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    ReelElement *reelElementPointer;

    if ( event->button() == Qt::LeftButton )
    {
        //emit leftButtonPressed(this);
        if(emptyElement)
        {
            this->view->resize(50, this->view->height() + 50);
            this->view->setSceneRect(0, 0, 50, this->view->height());
            reelElementPointer = new ReelElement(nullptr, view, reelSettingForm, coordinates, false, reelNumber, reelSettingForm->currentSymbol, nullptr);
            reelElementPointer->previousElement = this->previousElement;
            reelElementPointer->setY(this->y());
            this->previousElement = reelElementPointer;
            this->setY(this->y() + 50);
            //this->coordinates.setY(this->coordinates.y() + 50);
            this->view->scene()->addItem(reelElementPointer);
            reelSettingForm->reels->at(reelNumber).push_back(reelSettingForm->currentSymbol);
            //std::cout << coordinates.x() << " " << coordinates.y() << std::endl;
            //lastElement = false;
            //if(previousElement != nullptr)
            //    previousElement->lastElement = true;
        }
    }
    else if ( event->button() == Qt::RightButton )
        if(emptyElement)
        {
            if(this->previousElement == nullptr)
                return;

            this->view->resize(50, this->view->height() - 50);
            this->view->setSceneRect(0, 0, 50, this->view->height());
            reelElementPointer = this->previousElement->previousElement;
            this->view->scene()->removeItem(this->previousElement);
            this->previousElement->~QGraphicsItem();
            free(this->previousElement);
            this->previousElement = reelElementPointer;
            this->setY(this->y() - 50);
            reelSettingForm->reels->at(reelNumber).pop_back();
        }
        //emit rightButtonPressed(this);

    else if ( event->button() == Qt::MidButton )
        ;//emit middleButtonPressed(this);
}
