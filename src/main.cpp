#include <iostream>
#include <stdlib.h>
#include <string>
#include <fstream>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/video.hpp>


using namespace cv;
using namespace std;


/* Función para el reconocimiento de gestos. Dependiendo de si hay x dedos levantados y en ángulo está comprendido entre dos valores
   de ángulos, corresponderá con uno de los tres gestos que puede reconocer. */

void fGestos(int cont, double angulo, Mat img) {


   if ((cont == 2) && ((angulo >= 50.0)  && (angulo < 65.0))) {

       putText(img, "PAZ", Point(450, 50), FONT_HERSHEY_DUPLEX, 1.0, Scalar(0,255,0), 2);
   }
   else if ((cont == 2) && ((angulo >= 11.0) && (angulo < 20.0))) {

       putText(img, "OK", Point(450, 50), FONT_HERSHEY_DUPLEX, 1.0, Scalar(0,255,0), 2);
   }
   else if ((cont == 2) && ((angulo >= 65.0) && (angulo < 75.0))) {

       putText(img, "ALIEN", Point(450, 50), FONT_HERSHEY_DUPLEX, 1.0, Scalar(0,255,0), 2);
   }
}


/* Función para devolver el ángulo que forman el vector entre el punto inicial con el punto más lejano, y el vector entre 
   el punto final con el punto más lejano. */

double angle(Point s, Point e, Point f) {

    double v1[2],v2[2];
    v1[0] = s.x - f.x;
    v1[1] = s.y - f.y;
    v2[0] = e.x - f.x;
    v2[1] = e.x - f.x;
    double ang1 = atan2(v1[1], v1[0]);
    double ang2 = atan2(v2[1], v2[0]);

    double ang = ang1 - ang2;
    if (ang > CV_PI) ang -= 2*CV_PI;
    if (ang < -CV_PI) ang += 2*CV_PI;


    return ang*180/CV_PI;
}


int main(int argc, char* argv[]) {

    Mat frame,roi,fgMask;
        	
    VideoCapture cap;
    cap.open(0);
    if (!cap.isOpened()) {
        printf("Error opening cam\n");
        return -1;
    }

    vector<vector<Point>> contours;


    // Creamos un puntero que apunte al objeto que sustrae el fondo.
        
    Ptr<BackgroundSubtractor> pBackSub=createBackgroundSubtractorMOG2();


    /* Creamos 2 ventanas. Una para captar la imagen de la webcam y otra para pintar en negro 
       el fondo, y en blanco la parte frontal */
        
    namedWindow("Original");
    namedWindow("Binaria");

	
    Rect rect(400,100,200,200);
        

    double x = -1;
    bool gestos = false;

    while(true) {

	vector<int> hull;
	vector<Vec4i> defects;
	int contador = 1;
	float depth;
        double ang;
	Point s, e, f;
	Rect boundRect;
	stringstream ss;
	string str;
	

	// Capaturamos la imagen de la webcam y la volcamos en nuestra imagen "frame".
                
        cap>>frame;


	// Volteamos la imagen "frame". 

	flip(frame,frame,1);


	// Copiamos en la imagen roi los pixeles seleccioandos dentro de la imagen frame destinados a la ROI.

	frame(rect).copyTo(roi);

	
	// Dibujamos en la ventana "frame" el rectangulo de la ROI.
	rectangle(frame, rect,Scalar(255,0,0));


	int c = waitKey(40);


	// Congelamos el fondo.

        if ((char)c =='b') { x = 0;}
		

	// Activamos gestos.

	if ((char)c =='r') { gestos = true;}
		

	// Desactivamos gestos.

	if ((char)c =='n') { gestos = false;}


        pBackSub->apply(roi, fgMask, x);
	imshow("Binaria",fgMask);


        findContours(fgMask,contours,RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);
        drawContours(roi, contours, -1, Scalar(0,255,0),5);
		

        for (size_t i = 0; i < contours.size(); i++) {

            convexHull(contours[i], hull);
	    sort(hull.begin(),hull.end(),greater <int>());
			
	    convexityDefects(contours[i], hull, defects);
                
	    for (int j = 0; j < defects.size(); j++) {

                s = contours[i][defects[j][0]];
                e = contours[i][defects[j][1]];
                f = contours[i][defects[j][2]];
                        	
		depth = (float)defects[j][3] / 256.0;
                ang = angle(s,e,f);

		boundRect = boundingRect(contours[i]);
		rectangle(roi, boundRect, Scalar(0,255,255), 3);

  		if ((ang < 90.0) && (depth > 40.0)) {
				    
		    circle(roi, f,5,Scalar(0,0,255),-1);
                    line(roi,s,e,Scalar(255,0,0),2);
		    contador = contador + 1;

		    if (gestos == true) {
				  
   		        fGestos(contador, ang, frame);
		    }
		    else {

			 str.erase();
			 ss << contador;
			 str = ss.str();
			 putText(frame, "1", Point(400, 50), FONT_HERSHEY_DUPLEX, 1.0, Scalar(0,255,0), 2);
			 putText(frame, str, Point(420, 50), FONT_HERSHEY_DUPLEX, 1.0, Scalar(0,255,0), 2);
		    }
		}
		else if (contador == 1 && (boundRect.height > 140) && (gestos == false)) {

		    putText(frame, "1", Point(400, 50), FONT_HERSHEY_DUPLEX, 1.0, Scalar(0,255,0), 2);
		}
            }
	
	}


	imshow("Operaciones", roi);
        imshow("Original",frame);

        if ((char)c =='q') break;
    }

    cap.release();
    destroyAllWindows();
}
