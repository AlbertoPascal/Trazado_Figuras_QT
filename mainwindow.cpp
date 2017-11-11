#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QScrollBar>
#include <QtAlgorithms>
#include <string>
MainWindow::MainWindow(QWidget *parent) :

    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);


    scene = new QGraphicsScene();
    transformada = new QGraphicsScene();
    clearscene = new QGraphicsScene();
    ui->GradosLB_2->setVisible(false);
    ui->GradosTB->setVisible(false);
    ui->ZOOMINTB->setVisible(false);
    ui->ZOOMOUTTB->setVisible(false);
    ui->EscalaLB->setVisible(false);
    ui->Centrolabel->setVisible(false);
    ui->centroX->setVisible(false);
    ui->centroY->setVisible(false);
    ui->centroX_2->setVisible(false);
    ui->centroY_2->setVisible(false);

    Resetea(ui->centroX->text());
    Resetea(ui->centroY->text());
    Resetea(ui->ZOOMINTB->text());
    Resetea(ui->ZOOMOUTTB->text());
    connect(ui->polyEdit,SIGNAL(textChanged(QString)),this,SLOT(actualizarLados()));
    connect(ui->arcEdit,SIGNAL(textChanged(QString)),this,SLOT(Actualizar_Angulo()));
    connect(ui->RadioTB,SIGNAL(textChanged(QString)),this,SLOT(actualizaRadio()));
    connect(ui->centroX, SIGNAL(returnPressed()),this,SLOT(trasladarX()));
    connect(ui->centroX, SIGNAL(returnPressed()),this,SLOT(trasladarY()));
    connect(ui->ZOOMINTB, SIGNAL(returnPressed()),this,SLOT(zoomIn()));
    connect(ui->ZOOMOUTTB, SIGNAL(returnPressed()),this,SLOT(zoomOut()));


    scene->setSceneRect(0,0,500,500);
    transformada->setSceneRect(0,0,500,500);
    clearscene->setSceneRect(0,0,500,500);

    Resetea(ui->FiguraCB->currentText());
    Resetea(ui->TransCB->currentText());
    Resetea(ui->GradosTB->text());
    connect(ui->largo,SIGNAL(returnPressed()),this,SLOT(actualizaLargo()));
    connect(ui->FiguraCB,SIGNAL(currentIndexChanged(const QString&)),this,SLOT(Resetea (const QString&)));
    connect(ui->TransCB,SIGNAL(currentIndexChanged(const QString&)), this, SLOT(Operacion (const QString&)));
    connect(ui->GradosTB,SIGNAL(returnPressed()), this, SLOT(gira()));


    ui->graphicsView->setScene(scene);
    ui->graphicsView2->setScene(transformada);


    ui->Revertir_Todo->setVisible(false);
    ui->TrasladarBTN->setVisible(false);
    Resetea(ui->FiguraCB->currentText());
    centrox=0;
    centroy=0;
    ui->GradosTB->setText("0");
    ui->ZOOMINTB->setText("0");
    ui->ZOOMOUTTB->setText("0");
    Resetea(ui->ZOOMINTB->text());
    Resetea(ui->ZOOMOUTTB->text());
    Resetea(ui->GradosTB->text());
    Resetea(ui->centroX->text());
    Resetea(ui->centroY->text());
    Resetea(ui->FiguraCB->currentText());


}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::Operacion(const QString &oper)
{
    QStringList transformaciones;
    ui->centroX->setVisible(false);
    ui->centroY->setVisible(false);
    ui->centroX_2->setVisible(false);
    ui->centroY_2->setVisible(false);
    ui->ZOOMINTB->setVisible(false);
    ui->ZOOMOUTTB->setVisible(false);
    ui->EscalaLB->setVisible(false);
    ui->GradosLB_2->setVisible(false);
    ui->Centrolabel->setVisible(false);
    transformaciones<<"Rotación"<<"Traslación"<<"Zoom In"<<"Zoom Out"<<"Reflexión Vertical"<<"Reflexión Horizontal"<<"Seleccione Transformación";
    int op = 0;
    for(int x=0; x<7; x++)
    {
        if(transformaciones[x]==oper)
        {
            op=x;
            break;
        }
    }
    if(op==6)
    {
       ui->centroX->setVisible(false);
       ui->centroY->setVisible(false);
       ui->centroX_2->setVisible(false);
       ui->centroY_2->setVisible(false);
       ui->ZOOMINTB->setVisible(false);
       ui->ZOOMOUTTB->setVisible(false);
       ui->EscalaLB->setVisible(false);
       ui->GradosLB_2->setVisible(false);
       ui->Centrolabel->setVisible(false);
       ui->GradosTB->setVisible(false);
       ui->Revertir_Todo->setVisible(true);
       ui->TrasladarBTN->setVisible(false);

    }
    else if(op==0)
    {
        ui->GradosLB_2->setVisible(true);
        ui->GradosTB->setVisible(true);
        ui->centroX->setVisible(false);
        ui->centroY->setVisible(false);
        ui->centroX_2->setVisible(false);
        ui->centroY_2->setVisible(false);
        ui->ZOOMINTB->setVisible(false);
        ui->ZOOMOUTTB->setVisible(false);
        ui->EscalaLB->setVisible(false);
        ui->Centrolabel->setVisible(false);
        ui->Revertir_Todo->setVisible(true);
        ui->TrasladarBTN->setVisible(false);
    }
    else if(op==1) //Traslación
    {
        ui->GradosLB_2->setVisible(false);
        ui->GradosTB->setVisible(false);
        ui->ZOOMINTB->setVisible(false);
        ui->ZOOMOUTTB->setVisible(false);
        ui->EscalaLB->setVisible(false);
        ui->Centrolabel->setVisible(true);
        ui->centroX->setVisible(true);
        ui->centroY->setVisible(true);
        ui->centroX_2->setVisible(true);
        ui->centroY_2->setVisible(true);
        ui->Revertir_Todo->setVisible(true);
        ui->TrasladarBTN->setVisible(true);

    }
    else if(op==2) //zoom in
    {
        ui->Revertir_Todo->setVisible(true);
        ui->TrasladarBTN->setVisible(false);
       ui->GradosLB_2->setVisible(false);
       ui->GradosTB->setVisible(false);
       ui->ZOOMINTB->setVisible(true);
       ui->ZOOMOUTTB->setVisible(false);
       ui->EscalaLB->setVisible(true);
       ui->Centrolabel->setVisible(false);
       ui->centroX->setVisible(false);
       ui->centroY->setVisible(false);
       ui->centroX_2->setVisible(false);
       ui->centroY_2->setVisible(false);
    }
    else if(op==3)//zoom out
    {
        ui->Revertir_Todo->setVisible(true);
        ui->TrasladarBTN->setVisible(false);
        ui->GradosLB_2->setVisible(false);
        ui->GradosTB->setVisible(false);
        ui->ZOOMINTB->setVisible(false);
        ui->ZOOMOUTTB->setVisible(true);
        ui->EscalaLB->setVisible(true);
        ui->Centrolabel->setVisible(false);
        ui->centroX->setVisible(false);
        ui->centroY->setVisible(false);
        ui->centroX_2->setVisible(false);
        ui->centroY_2->setVisible(false);
    }
    else if(op==4) //reflexion vertical
    {
        ui->Revertir_Todo->setVisible(true);
        ui->TrasladarBTN->setVisible(false);
        ui->GradosLB_2->setVisible(false);
        ui->GradosTB->setVisible(false);
        ui->ZOOMINTB->setVisible(false);
        ui->ZOOMOUTTB->setVisible(false);
        ui->EscalaLB->setVisible(false);
        ui->Centrolabel->setVisible(false);
        ui->centroX->setVisible(false);
        ui->centroY->setVisible(false);
        ui->centroX_2->setVisible(false);
        ui->centroY_2->setVisible(false);
        Reflexion_Vertical();
    }
    else if(op==5)// reflexion horizontal
    {
        ui->Revertir_Todo->setVisible(true);
        ui->TrasladarBTN->setVisible(false);
        ui->GradosLB_2->setVisible(false);
        ui->GradosTB->setVisible(false);
        ui->ZOOMINTB->setVisible(false);
        ui->ZOOMOUTTB->setVisible(false);
        ui->EscalaLB->setVisible(false);
        ui->Centrolabel->setVisible(false);
        ui->centroX->setVisible(false);
        ui->centroY->setVisible(false);
        ui->centroX_2->setVisible(false);
        ui->centroY_2->setVisible(false);
        Reflexion_Horizontal();
    }
}

void MainWindow::NLados(int lados, int r, double x, double y)
{
    float CoordenadasX[lados];
    float CoordenadasY[lados];

    float angulo = (float)360.0/(float)lados;
    float anguloActual = 0;
    float rad = 3.1416 / (float)180;
    angulo *= rad;

    for(int i = 0; i < lados; ++i)
    {
        CoordenadasX[i] = (r * cos(anguloActual)+x);
        CoordenadasY[i] = (r * sin(anguloActual)+y );


        anguloActual += angulo;
    }
    for(int x=1; x<lados; x++)
    {
        scene->addLine(CoordenadasX[x-1], CoordenadasY[x-1], CoordenadasX[x], CoordenadasY[x]);
        transformada->addLine(CoordenadasX[x-1]+centrox, CoordenadasY[x-1]+centroy, CoordenadasX[x]+centrox, CoordenadasY[x]+centroy);
    }
    scene->addLine(CoordenadasX[0], CoordenadasY[0], CoordenadasX[lados-1], CoordenadasY[lados-1]);
    transformada->addLine(CoordenadasX[0]+centrox, CoordenadasY[0]+centroy, CoordenadasX[lados-1]+centrox, CoordenadasY[lados-1]+centroy);


}

void MainWindow::Pedazo_Circulo(int angulo, int radio)
{
    //int anguloinicial = 0;
    double xfinal=0;
    //int original_radianes = (angulo*2*3.241592)/360;

    if(angulo>=0 && angulo<=90)
    {
        float angulo_radianes= (angulo*2*3.141592)/360;
        xfinal = sin(angulo_radianes) * radio;
        for(float x=0; x<=xfinal; x+=0.01)
        {
            double y = sqrt((radio*radio)-(x*x));
            scene->addLine(x+250,y+250,x+250,y+250);
            transformada->addLine(x+250+centrox,y+250+centroy,x+250+centrox,y+250+centroy);
        }
    }
    else if(angulo >90 && angulo<=180)
    {
        float angulo_radianes1= (90*2*3.141592)/360;
        xfinal = sin(angulo_radianes1) * radio;

        float angulo_radianes2 = ((angulo-90)*2*3.141592)/360;
        float xfinal2 = sin(angulo_radianes2) * radio;
        xfinal2=xfinal - xfinal2;
        for(float x=0; x<=xfinal; x+=0.01)
        {
            double y = sqrt((radio*radio)-(x*x));
            scene->addLine(x+250,y+250,x+250,y+250);
            transformada->addLine(x+250+centrox,y+250+centroy,x+250+centrox,y+250+centroy);

        }
        while(xfinal2<=xfinal)
        {
            double y = sqrt((radio*radio)-(xfinal2*xfinal2));
            scene->addLine(xfinal2+250,250-y,xfinal2+250,250-y);
             transformada->addLine(xfinal2+250+centrox,250-y+centroy,xfinal2+250+centrox,250-y+centroy);
            xfinal2=xfinal2+0.01;
        }


    }
    else if(angulo>180 && angulo <=270)
    {
        float angulo_radianes1= (90*2*3.141592)/360;
        xfinal = sin(angulo_radianes1) * radio;

        float angulo_radianes2 = ((90)*2*3.141592)/360;
        float xfinal2 = sin(angulo_radianes2) * radio;
        xfinal2=xfinal - xfinal2;
        for(float x=0; x<=xfinal; x+=0.01)
        {
            double y = sqrt((radio*radio)-(x*x));
            scene->addLine(x+250,y+250,x+250,y+250);
            transformada->addLine(x+250+centrox,y+250+centroy,x+250+centrox,y+250+centroy);

        }
        while(xfinal2<=xfinal)
        {
            double y = sqrt((radio*radio)-(xfinal2*xfinal2));
            scene->addLine(xfinal2+250,250-y,xfinal2+250,250-y);
            transformada->addLine(xfinal2+250+centrox,250-y+centroy,xfinal2+250+centrox,250-y+centroy);
            xfinal2=xfinal2+0.01;
        }
        float angulo_radianes3 =  (angulo-180)*2*3.141592/360;
        float xfinal3 = (-1)*sin(angulo_radianes3) * radio;
        for(float x=xfinal3; x<=0; x+=0.01)
        {
            double y = sqrt((radio*radio)-(x*x));
            scene->addLine(250+x,250-y,250+x,250-y);
            transformada->addLine(250+x+centrox,250-y+centroy,250+x+centrox,250-y+centroy);

        }
    }
    else
    {
        float angulo_radianes1= (90*2*3.141592)/360;
        xfinal = sin(angulo_radianes1) * radio;

        float angulo_radianes2 = ((90)*2*3.141592)/360;
        float xfinal2 = sin(angulo_radianes2) * radio;
        xfinal2=xfinal - xfinal2;
        for(float x=0; x<=xfinal; x+=0.01)
        {
            double y = sqrt((radio*radio)-(x*x));
            scene->addLine(x+250,y+250,x+250,y+250);
            scene->addLine(250-x, 250-y,250-x,250-y);
            transformada->addLine(x+250+centrox,y+250+centroy,x+250+centrox,y+250+centroy);
            transformada->addLine(250-x+centrox, 250-y+centroy,250-x+centrox,250-y+centroy);

        }
        while(xfinal2<=xfinal)
        {
            double y = sqrt((radio*radio)-(xfinal2*xfinal2));
            scene->addLine(xfinal2+250,250-y,xfinal2+250,250-y);
            transformada->addLine(xfinal2+250+centrox,250-y+centroy,xfinal2+250+centrox,250-y+centroy);

            xfinal2=xfinal2+0.01;
        }
        float angulo_radianesfinal=(angulo-270)*2*3.141592/360;
        float xfinalfinal=sin(angulo_radianesfinal)*radio;

        for(float x=0; x<=xfinalfinal; x+=0.01)
        {
            double y = sqrt((radio*radio)-(x*x));

            scene->addLine(250-x, 250+y,250-x,250+y);
            transformada->addLine(250-x+centrox, 250+y+centroy,250-x+centrox,250+y+centroy);

        }

    }





}

void MainWindow::Cono()
{
    transformada->addEllipse(250+centrox,250+centroy,50,25);
    transformada->addLine(250+centrox,262.5+centroy,275+centrox,350+centroy);
    transformada->addLine(300+centrox,262.5+centroy,275+centrox,350+centroy);

    scene->addEllipse(250,250,50,25);
    scene->addLine(250,262.5,275,350);
    scene->addLine(300,262.5,275,350);
}

void MainWindow::Cubito()
{
    NLados(4,50,250,250);
    NLados(4,50,200,275);
    transformada->addLine(250+centrox,275+centroy,300+centrox,250+centroy);
    transformada->addLine(200+centrox,225+centroy,250+centrox,200+centroy);
    transformada->addLine(150+centrox,275+centroy,200+centrox,250+centroy);
    transformada->addLine(200+centrox,325+centroy,250+centrox,300+centroy);
    scene->addLine(250,275,300,250);
    scene->addLine(200,225,250,200);
    scene->addLine(150,275,200,250);
    scene->addLine(200,325,250,300);

    ui->graphicsView->rotate(45);
    ui->graphicsView2->rotate(45);
    rotacion_actual += 45;


}

void MainWindow::Prisma(float largo)
{
    NLados(4,50,250+largo,250);
    NLados(4,50,200,275);
    scene->addLine(250,275,300+largo,250);
    scene->addLine(200,225,250+largo,200);
    scene->addLine(150,275,200+largo,250);
    scene->addLine(200,325,250+largo,300);
    transformada->addLine(250+centrox,275+centroy,300+centrox+largo,250+centroy);
    transformada->addLine(200+centrox,225+centroy,250+centrox+largo,200+centroy);
    transformada->addLine(150+centrox,275+centroy,200+centrox+largo,250+centroy);
    transformada->addLine(200+centrox,325+centroy,250+centrox+largo,300+centroy);

    ui->graphicsView->rotate(45);
    ui->graphicsView2->rotate(45);
    rotacion_actual+=45;
}

void MainWindow::PrismaTriangular()
{
    int extra=25;
    NLados(3,50,250,200);
    NLados(3,50,200,275);
    scene->addLine(175,230,225,155);
    scene->addLine(250,275,300,200);
    scene->addLine(172,320,225,240);

    transformada->addLine(175+centrox,230+centroy,225+centrox,centroy+155);
    transformada->addLine(250+centrox,centroy+275,centrox+300,centroy+200);
    transformada->addLine(172+centrox,320+centroy,225+centrox,centroy+240);
    ui->graphicsView2->rotate(30);


}

void MainWindow::Resetea(const QString & figura)
{

    qDeleteAll(scene->items());
    qDeleteAll(transformada->items());
    ui->graphicsView2->setScene(clearscene);
    ui->graphicsView2->setScene(transformada);
    ui->graphicsView2->resetTransform();
    ui->graphicsView->setScene(clearscene);
    ui->graphicsView->setScene(scene);
    ui->graphicsView->resetTransform();



    QStringList opciones;
    opciones<<"Arco"<<"Prisma Triangular"<< "Cubo"<< "Polígono"<< "Cono"<< "Prisma Rectangular";

    int op=70;
    for(int x=0; x<6;x++)
    {
        if(figura==opciones[x])
        {
            op=x;
        }
    }
    ui->GradosTB->setText("0");

    if(op==0)
    {
        ui->polyEdit->setVisible(false);
        ui->arcEdit->setVisible(true);
        ui->GradosLB->setVisible(true);
        ui->LadosLB->setVisible(false);
        ui->Radio_label->setVisible(true);
        ui->RadioTB->setVisible(true);
        int r = ui->RadioTB->text().toInt();
        Pedazo_Circulo(ui->arcEdit->text().toInt(), r);
    }
    else if(op==1)
    {
        ui->polyEdit->setVisible(false);
        ui->arcEdit->setVisible(false);
        ui->GradosLB->setVisible(false);
        ui->LadosLB->setVisible(false);
        ui->largo->setVisible(true);
        ui->largolabel->setVisible(true);
        ui->Radio_label->setVisible(false);
        ui->RadioTB->setVisible(false);
        PrismaTriangular();
    }
    else if(op==2)
    {
        ui->polyEdit->setVisible(false);
        ui->arcEdit->setVisible(false);
        ui->GradosLB->setVisible(false);
        ui->LadosLB->setVisible(false);
        ui->largo->setVisible(false);
        ui->largolabel->setVisible(false);
        ui->Radio_label->setVisible(false);
        ui->RadioTB->setVisible(false);

        Cubito();
    }
    else if(op==3)
    {
        ui->largo->setVisible(false);
        ui->largolabel->setVisible(false);
        ui->polyEdit->setVisible(true);
        ui->arcEdit->setVisible(false);
        ui->RadioTB->setVisible(true);
        ui->GradosLB->setVisible(false);
        ui->LadosLB->setVisible(true);
        ui->Radio_label->setVisible(true);


        int n = ui->polyEdit->text().toInt();
        int r = ui->RadioTB->text().toInt();

        NLados(n,r,250, 250);

    }
    else if(op==4)
    {
        ui->polyEdit->setVisible(false);
        ui->arcEdit->setVisible(false);
        ui->GradosLB->setVisible(false);
        ui->LadosLB->setVisible(false);
        ui->largo->setVisible(true);
        ui->largolabel->setVisible(true);
        ui->Radio_label->setVisible(false);
        ui->RadioTB->setVisible(false);
        Cono();
    }
    else if(op==5)
    {
        ui->polyEdit->setVisible(false);
        ui->arcEdit->setVisible(false);
        ui->GradosLB->setVisible(false);
        ui->LadosLB->setVisible(false);
        ui->largo->setVisible(true);
        ui->largolabel->setVisible(true);
        ui->Radio_label->setVisible(false);
        ui->RadioTB->setVisible(false);
        Prisma(ui->largo->text().toFloat());

    }
    else
    {
        ui->polyEdit->setVisible(false);
        ui->LadosLB->setVisible(false);
        ui->arcEdit->setVisible(false);
        ui->GradosLB->setVisible(false);
        ui->largo->setVisible(false);
        ui->largolabel->setVisible(false);
        ui->Radio_label->setVisible(false);
        ui->RadioTB->setVisible(false);

    }




}

void MainWindow::gira()
{

        double grados= ui->GradosTB->text().toDouble();
        ui->graphicsView2->rotate(grados);

        rotacion_actual += grados;


    if(ui->GradosTB->text().toDouble()==0)
    {
        ui->graphicsView2->rotate(-rotacion_actual);
        rotacion_actual=0;


    }
}
void MainWindow::trasladarX()
{
    centrox = ui->centroX->text().toDouble();

}
void MainWindow::trasladarY()
{
    centroy= ui->centroY->text().toDouble();


}

void MainWindow::zoomIn()
{
    ui->graphicsView2->scale(1/(1-ui->ZOOMINTB->text().toDouble()),1/(1-ui->ZOOMINTB->text().toDouble()));
}

void MainWindow::zoomOut()
{
    ui->graphicsView2->scale(1-ui->ZOOMOUTTB->text().toDouble(),(1-ui->ZOOMOUTTB->text().toDouble()));
}

void MainWindow::Reflexion_Horizontal()
{
    ui->graphicsView2->scale(-1, 1);
}

void MainWindow::Reflexion_Vertical()
{
    ui->graphicsView2->scale(1, -1);
}

void MainWindow::actualizarLados()
{
    Resetea(ui->FiguraCB->currentText());
}

void MainWindow::Actualizar_Angulo()
{
    Resetea(ui->FiguraCB->currentText());
}
void MainWindow:: actualizaRadio()
{
    Resetea(ui->FiguraCB->currentText());
}
void MainWindow:: actualizaLargo()
{
    Resetea(ui->FiguraCB->currentText());
}


void MainWindow::on_TrasladarBTN_clicked()
{
    trasladarX();
    trasladarY();
    Resetea(ui->centroX->text());
    Resetea(ui->centroY->text());
    Resetea(ui->FiguraCB->currentText());
}

void MainWindow::on_Revertir_Todo_clicked()
{
    centrox=0;
    centroy=0;
    ui->GradosTB->setText("0");
    ui->ZOOMINTB->setText("0");
    ui->ZOOMOUTTB->setText("0");
    Resetea(ui->ZOOMINTB->text());
    Resetea(ui->ZOOMOUTTB->text());
    Resetea(ui->GradosTB->text());
    Resetea(ui->centroX->text());
    Resetea(ui->centroY->text());
    Resetea(ui->FiguraCB->currentText());
}
