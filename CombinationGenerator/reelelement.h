#ifndef REELELEMENT_H
#define REELELEMENT_H

#include <QPointF>
#include <QGraphicsItem>
#include <QGraphicsView>
#include <QPainter>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsSimpleTextItem>
#include "reelsettingform.h"
#include "reelelement.h"

class ReelElement : public QGraphicsSimpleTextItem
{
public:
    ReelElement(QGraphicsSimpleTextItem *parent, QGraphicsView *view, ReelSettingForm *reelSettingForm,
                QPointF coordinates, bool emptyElement, quint16 reelNumber, quint16 symbol, ReelElement *previousElement);
    QRectF boundingRect() const;
    QPainterPath shape() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);

signals:
    void leftButtonPressed(ReelElement* sender);
    void rightButtonPressed(ReelElement* sender);
    void middleButtonPressed(ReelElement* sender);
    void leftButtonReleased(ReelElement* sender);
    void rightButtonReleased(ReelElement* sender);
    void middleButtonReleased(ReelElement* sender);
    void mouseEntered(ReelElement* sender );
    void mouseLeft(ReelElement* sender);

private:
    QPointF coordinates;
    bool emptyElement;
    QGraphicsView *view;
    ReelElement *previousElement;
    ReelSettingForm *reelSettingForm;
    int reelNumber;
    int symbol;
};

#endif // REELELEMENT_H
