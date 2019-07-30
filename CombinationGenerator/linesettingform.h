#ifndef LINESETTINGFORM_H
#define LINESETTINGFORM_H

#include "mainwindow.h"
#include <vector>
#include <QPointF>
#include <QGraphicsItem>
#include <QGraphicsView>
#include <QPainter>
#include <QGraphicsSceneMouseEvent>
#include "QMessageBox"


namespace Ui {
class LineSettingForm;
}

class LineSettingForm : public QWidget
{
    class SquareElement : public QGraphicsItem
    {
    public:
        SquareElement(QGraphicsItem *parent, LineSettingForm *lineSettingForm, QGraphicsView *view, QPointF coordinates, quint16 reelNumber);
        QRectF boundingRect() const;
        QPainterPath shape() const;
        void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

        bool selected;

    protected:
        void mousePressEvent(QGraphicsSceneMouseEvent *event);

    private:
        QPointF coordinates;
        QGraphicsView *view;
        LineSettingForm *lineSettingForm;
        int reelNumber;
    };

    Q_OBJECT

public:
    explicit LineSettingForm(QWidget *parent = 0);
    ~LineSettingForm();
    void clearReel(int reelIndex);
    bool isEditingEnabled;

private slots:
    void lineComboBoxCurrentIndexChanged(int index);
    void addNewLinePushButtonClicked();
    void saveLinePushButtonClicked();
    void deleteLinePushButtonClicked();

    void on_buttonBox_accepted();

    void on_buttonBox_rejected();

private:
    Ui::LineSettingForm *ui;
    MainWindow *parentMdi;
    vector<vector<int>> *lines;
    vector<QGraphicsLineItem*> *lineElements;
    SquareElement *squareElementPointer;
    vector<vector<SquareElement*>> *squareElements;
    QGraphicsScene *scenePointer;
    QGraphicsView *viewPointer;
    int currentLineIndex;
    //int lineComboBoxCount;

    void updateLine();
};

#endif // LINESETTINGFORM_H
