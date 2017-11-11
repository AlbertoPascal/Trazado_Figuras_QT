#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtGui>
#include <QGraphicsEllipseItem>
#include <QPen>
#include <QPainter>
#include <QBrush>


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    QGraphicsScene * scene;
    QGraphicsScene * transformada;
    QGraphicsScene * clearscene;
    QTransform * trans;

private:
    Ui::MainWindow *ui;

    double rotacion_actual;
    double centrox, centroy;
public:
    void NLados(int lados, int r, double x, double y);
    void Pedazo_Circulo(int andulo, int radio);
    void Prisma(float largo);
    void PrismaTriangular();
    void Cono();
    void on_Transformar_clicked();
    void Cubito();


public slots:
    void Resetea(const QString & fig);
    void Operacion(const QString & oper);
    void gira();
    void actualizaLargo();
    void trasladarX();
    void trasladarY();
    void zoomIn();
    void zoomOut();
    void Reflexion_Horizontal();
    void Reflexion_Vertical();
    void actualizarLados();
    void Actualizar_Angulo();
    void actualizaRadio();

private slots:

    void on_TrasladarBTN_clicked();
    void on_Revertir_Todo_clicked();
};

#endif // MAINWINDOW_H
