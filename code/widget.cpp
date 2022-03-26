#include "widget.h"
#include "ui_widget.h"

#include <iostream> // c++
#include <ctime> // aleatorio cada vez que se ejecuta

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    //Nombre de ventana
    setWindowTitle("Proyecto Discreta");

    // Creacion objeto (escena)
    view = ui->GraficoHasse;
    scene = new QGraphicsScene(this);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_generarTyH_clicked()
{

    int N, fila; // Valor para almacenar tareas
    N = ui->CantT->value(); // guardamos datos en variable

    // Limpiar pantalla

    scene->clear();
    //view->items().clear();
    scene->update();
    view->update();

    // Herramientas para grafico
    QPen blackPen(Qt::black);

    // Colores para el dibujo de diagrama
    QBrush colors[12] = { Qt::red, Qt::white, Qt::blue, Qt::yellow, Qt::green, Qt::gray, Qt::cyan, Qt::darkGreen,
                          Qt::magenta,  Qt::darkBlue, Qt::darkRed, Qt::darkYellow};

    // ---------------------------------------------------------------------------------------------------------

    //Solo dibujar si cumple la condición
    if(N >= MIN && N <= MAX)
    {
        // Eliminar tabla cada vez que se ejecuta
        while(ui->tablaTareas->rowCount() > 0)
            ui->tablaTareas->removeRow(0);


//        scene->clear();

        // Para valores aleatorios
        srand(time(0));

        // Declarar arreglo con tamaño N X N
        int matrizT[N][N];

        // Generar matriz con datos
        for(int i = 0; i < N; ++i)
        {
            int limite; // Limite para la impresión
            if(i == 0)
                limite = 0;
            else
                limite = rand() % (i) + 1; // Valore que van desde 1 < N

            for(int j = 0; j < limite; ++j)
            {
                if(i == 0) matrizT[i][j] = 0;
                else
                {
                    // Para la precedencia de las tareas
                    int randomInicial = rand() % (i) + 1;
                    if(j == 0) // primera posicion en la fila en la que estoy
                        matrizT[i][j] = randomInicial;
                    else if(matrizT[i][j - 1] < limite) // cuando sea menor al limite
                            matrizT[i][j] = matrizT[i][j - 1] + 1; // para que sean precedentes
                        else
                            matrizT[i][j] = 0;

                }
            }
            while(limite <= N)
            {
                matrizT[i][limite] = 0;
                limite++;
            }

            for(int j = 0; j < N; ++j)
            {
                int aux = matrizT[i][j];
                if(aux == 0)
                    matrizT[i][j + 1] = 0;
            }
        }

        // Tiempo para cada tarea
        int tiempoT[N];
        for (int i = 0; i < N; i++)
            tiempoT[i] = rand() % (N) + 1;

        ui->tablaTareas->setColumnCount(4); // Asignar columnas
        QStringList headers; // Creamos variable para almacenar headers de la tabla
        headers << "Tareas" << "Tareas inmediatamente precedentes" << "Tiempo para realizar una tarea" << "Color";
        ui->tablaTareas->setHorizontalHeaderLabels(headers);
        ui->tablaTareas->setColumnWidth(0, 180); // Asignamos tamaños
        ui->tablaTareas->setColumnWidth(1, 400);
        ui->tablaTareas->setColumnWidth(2, 200);

    //----------------------------------------------------------------------------------------

        QStringList headersRows;

        QString list; // almacenar todo el array para ubicarlo en la tabla
        // Imprimir datos
        for(int i = 0; i < N; ++i) // genera tabla con valores
        {
            list = "";
            headersRows << " - ";
            ui->tablaTareas->insertRow(ui->tablaTareas->rowCount()); // agregar fila al final
            fila = ui->tablaTareas->rowCount() - 1; // ultima fila
            for(int j = 0; j < N; ++j)
            {
                if(matrizT[i][j] == 0) continue; // al llegar a 0 dejamos de almacenar en el string
                else
                {
                    list += (QString::number(matrizT[i][j])); // formar arrar string con valores
                    list += " , ";
                }

            }
            QTableWidgetItem* CList = new QTableWidgetItem(list);
            CList->setTextAlignment(Qt::AlignCenter);
            ui->tablaTareas->setItem(fila, TPRECEDENTES, CList); // insertar tareas precedentes

            QTableWidgetItem* CNumber = new QTableWidgetItem(QString::number(i + 1));
            CNumber->setTextAlignment(Qt::AlignCenter);
            ui->tablaTareas->setItem(fila, TNUMERO, CNumber); // insertar numero de tarea
            ui->tablaTareas->setVerticalHeaderLabels(headersRows);

            QTableWidgetItem* CTime = new QTableWidgetItem(QString::number(tiempoT[i]) + " horas"); // insertar tiempo
            CTime->setTextAlignment(Qt::AlignCenter);
            ui->tablaTareas->setItem(fila, TTIEMPO, CTime);

            QTableWidgetItem* color = new QTableWidgetItem(QString::number(i + 1)); // insertar nombre color
            color->setTextAlignment(Qt::AlignCenter);
            ui->tablaTareas->setItem(fila, COLOR, color);
            ui->tablaTareas->item(i, COLOR)->setBackground(colors[i]);

        }

        // i = 0 => Tarea 1

        QRect rect; // CUADRO DE TAREA
        int width = 80;
        int height = 40;

        // de GraphicsView
        int alto = ui->GraficoHasse->height();

        // coordenada de cada cuadro
        std::vector<std::vector<int>> posiciones;

        // Posicionar cuadros y guardar ubicaciones x, y, e N°Colum
        for(int i = 0; i < N; ++i)
        {
            std::vector<int>* aux = new std::vector<int>; // creas par ordenado de coodenadas
            if(i == 0)
            {
                rect = QRect(0, 0, width, height); // ubicar coordenadas
                rect.moveTop((alto / 2) + (rect.height() / 2)); // moverlo hacia arriba para mejor orden

                rectangle = scene->addRect(rect, blackPen, colors[i]);

                aux->push_back(rect.x());
                aux->push_back(rect.y());
                aux->push_back(0);
                posiciones.push_back(*aux);

            }
            else
            {                                    

                rect = QRect(matrizT[i][0] * 130, 0, width, height);
                rect.moveTop(/*(alto / 2)*/ /*(rect.height() / 2) */(i * 50));

                rectangle = scene->addRect(rect, blackPen, colors[i]);

                aux->push_back(rect.x());
                aux->push_back(rect.y());
                aux->push_back(matrizT[i][0]);
                posiciones.push_back(*aux);
            }
        }

        QLine line;
        int posX = 0, posY = 0;
        int column = 0;

        //conectar cuadros
        for(int i = 0; i < N; ++i)
        {
            // Texto cuadro
            QGraphicsSimpleTextItem* tarea = new QGraphicsSimpleTextItem();

            posX = posiciones[i][0];
            posY = posiciones[i][1];

            tarea->setText("Tarea " + QString::number(i + 1) + "\n" + QString::number(tiempoT[i]) + " horas"  );
            tarea->setFont(QFont("Calibri", 12, -1, false));
            tarea->setPos(posX + 2 + (width / 6),  posY);
            scene->addItem(tarea);

           for(int j = 0; j < N; ++j)
           {
                column = matrizT[i][0]; // almacena columna de nodo actual ( primer elemento de la fila)

               // Relación para la conexión
               if(matrizT[i][j] != 0)
               {
                   if(column == posiciones[matrizT[i][j] - 1][2]) // si son de la misma columnas
                   {
                       line = QLine(posX + (width / 2), posY, posiciones[matrizT[i][j] - 1][0] + (width / 2), posiciones[matrizT[i][j] - 1][1] + height);
                       scene->addLine(line);
                   }
                   else // diferentes columnas
                   {
                       if(column < posiciones[matrizT[i][j] - 1][2])
                            line = QLine(posX + width, posY + (height / 2) , posiciones[matrizT[i][j] - 1][0], posiciones[matrizT[i][j] - 1][1] + (height / 2));
                       else
                            line = QLine(posX, posY + (height / 2) , posiciones[matrizT[i][j] - 1][0] + width, posiciones[matrizT[i][j] - 1][1] + (height / 2));
                        scene->addLine(line);
                   }
               } else break;
           }
        }

        // Imprimir matriz por consola

        std::cout << "MatrizT: \n";
        for(int i = 0; i < N; ++i)
        {
            for(int j = 0; j < N; ++j)
                std::cout << matrizT[i][j] << " ";
            std::cout << "\n";
         }
        std::cout << "\n";
        std::cout << "\n";

        // Mostrar grafico
        view->setScene(scene);

    } else return;


}


