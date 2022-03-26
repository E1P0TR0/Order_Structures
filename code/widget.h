#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QTableWidgetItem> // Para tabla
#include <QGraphicsScene> // Para Diagrama
#include <QGraphicsView> // Para Diagrama
#include <QGraphicsItem> // Para Diagrama
#include <QStyleOptionGraphicsItem>
#include <QFont> // Tipo de letra para texto

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

    // Dibujar graficos al presionar boton
    void on_generarTyH_clicked();

private:
    Ui::Widget *ui; // obj general
    QGraphicsScene *scene; // obj para grafico
    QGraphicsView *view; // obj para grafico
    QGraphicsRectItem *rectangle; // obj para cuadros
    // para la tabla
    enum Headers { TNUMERO, TPRECEDENTES, TTIEMPO, COLOR };
    // restriccioness
    enum { MIN = 8, MAX = 12};
};
#endif // WIDGET_H
