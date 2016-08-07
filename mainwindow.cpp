#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

/**
 * Metodo para obtener la direccion del video
 * @brief MainWindow::SeleccionarVideo
 */
void MainWindow::SeleccionarVideo(){
    // Declara la variable con la ruta del archivo
    QString archivo = QFileDialog::getOpenFileName(this, tr("Abrir Video"),
                                                    "",
                                                    tr("Videos (*.avi *.mp4 *.mov)"));
    //Agrega la ruta del archivo
    ui->labelVideo->setText(archivo);
    ui->radioVideo->setChecked(true);
}

/**
 * Metodo para procesar el video frame a frame si ckecked==true
 * @brief MainWindow::ProcesarVideo
 * @param checked
 *
 */
void MainWindow::ProcesarVideo(bool checked){

    cv::destroyAllWindows(); // Para cerrar todas las ventanas

    cv::CascadeClassifier face_cascade;
    face_cascade.load("/home/riclab/dev/opencv/opencv-3.1.0/data/haarcascades/haarcascade_frontalface_alt.xml");

    cv::Mat frame; // Frame como array multidimencional

    if(!checked){ // Si !checked detiene el video si no lo procesa
        ui->play->setText("Iniciar video");
        cap.release();
    }else{
        ui->play->setText("Parar video");

        if(ui->radioVideo->isChecked()){ // si el "radio button" esta seleccionado ejecuta el video si no la webcam
            cap.open(ui->labelVideo->text().toStdString().c_str());
        }else{
            cap.open(0);
        }

    }

    std::vector<cv::Rect> rostros;
    cv::Mat frame_gray;

    while(checked) // bucle hasta que se precione "parar video"
    {
        cap >> frame; // obtiene un nuevo frame del video o camara
        if(frame.empty()) break; // detiene el bucle si elframe esta vacio



        cv::cvtColor( frame, frame_gray, cv::COLOR_BGR2GRAY );
        cv::equalizeHist( frame_gray, frame_gray );

        face_cascade.detectMultiScale( frame_gray, rostros, 1.1, 2, cv::CASCADE_SCALE_IMAGE, cv::Size(30, 30) );

        for(size_t i = 0; i < rostros.size(); i++ )
        {
            cv::Rect rostro_i = rostros[i];
            cv::rectangle(frame, rostro_i, CV_RGB(0, 255,0), 3);
            int pos_x = std::max(rostro_i.tl().x - 10, 0);
            int pos_y = std::max(rostro_i.tl().y - 10, 0);
            cv::putText(frame, "Rostro detectado", cv::Point(pos_x, pos_y), CV_FONT_HERSHEY_DUPLEX, 0.8 , CV_RGB(0,255,0), 1.5);
        }

        cv::namedWindow("Reproductor", cv::WINDOW_KEEPRATIO); // creamos una ventana la cual permita redimencionar
        cv::imshow("Reproductor", frame); // se muestran los frames
        char key = (char) cv::waitKey(20); //espera 20ms por la tecla ESC
        if(key == 27) break; //detiene el bucle
    }

}

void MainWindow::on_toolButton_clicked()
{
    SeleccionarVideo();
}

void MainWindow::on_actionAbrir_Video_triggered()
{
    SeleccionarVideo();
}



void MainWindow::on_play_toggled(bool checked)
{
    ProcesarVideo(checked);
}
