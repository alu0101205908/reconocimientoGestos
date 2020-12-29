# Reconocimiento de gestos con OpenCV (SIPC)


 * ***Objeto Mat:***
 	
    * Con este objeto crearemos las imágenes que vamos a necesitar. En nuestro caso vamos a utilizar como imágenes: 
    	* **frame:** para la imagen principal (la que recoge la webcam).
    	
    	* **roi:** para la región de interés (la que nos vamos a centrar).
    	
    	* **fgMask:** para la imagen binaria.
    	  
    * Ejemplo de uso:
    	
    		Mat frame, roi, fgMask; 


 * ***Objeto VideoCapture:***
 	
    * Este objeto nos permite capturar imagenes desde la webcam para volcarlas sobre los objetos imágenes Mat. Además, se utiliza el método open, en el que se le pasa como parámetro un 0, para indicar que utilizaremos la webcam que viene por defecto.
     
    * Ejemplo de uso:
    	
    		VideoCapture cap; 
    		cap.open(0);
            
            
* ***Objeto Rect:***
 	
    * Este objeto nos permite crear un rectangulo. En nuestro caso l vamos a utilizar para seleccionar la región de interés. A este objeto se le pasa como paramétros las coordenas x e y de la esquina superior izquierda del rectangulo (tomadas desde la esquina superior izquierda de la imagen), además, se debe incluir las dimensiones del mismo (largo y ancho).
     
    * Ejemplo de uso:
    	
    		Rect rect(400,100,200,200);
      
      
* ***Matriz de puntos:***
 	
    * Para recoger el contorno de la mano, vamos a utilizar una matriz de puntos (x, y). Point es un tipo de dato que viene incluido en la libreria ed OpenCV.
     
    * Ejemplo de uso:
    	
    		vector<vector<Point>> contours;
      
      
* ***Función búsqueda de contornos (findContours):***
 	
    * Utilizamos la mascara binaria creada para bordear los objetos con pixeles distintos a 0, obteniendo el contorno y almacenándolo en nuestra matriz de puntos (contours). A esta función se le pasa como parámetros:
    	* **fgMask:** Imagen binaria de la región de interés.
    	* **contours:** Matriz de puntos.
    	* **RETR_EXTERNAL:** Para recuperar solo los contornos extremos exteriores.
    	* **CHAIN_APPROX_SIMPLE:** Comprimimos segmentos horizontales, verticales y diagonales y deja solo sus puntos finales.
     
    * Ejemplo de uso:
    	
    		findContours(fgMask,contours,RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);
       
       
 * ***Función dibujar contornos (drawContours):***
 	
    * Dibujamos en la imagen que queramos los contornos almacenados en nuestra matriz de  de puntos (que contiene los contornos):
    	* **roi:** Imagen donde vamos a dibujar el contorno.
    	* **contours:** Matriz de puntos que contiene el contorno.
    	* **-1:** Se dibujan todos los contornos. 
    	* **Scalar(0,255,0):** Color que tendrá el contorno, en este caso verde (BGR).
    	* **5:** Grosor del contorno.
     
    * Ejemplo de uso:
    	
    		drawContours(roi, contours, -1, Scalar(0,255,0),5);
      
      
  * ***Función calcular malla convexa (convexHull):***
 	
    * Calculamos la malla convexa a partir del índice del contorno dado y lo guardamos en el vector de malla convexa. A esta función se le pasa como parámetros:
    	* **contours[i]:** índice del contorno.
    	* **hull:** Vector de enteros que va a contener la malla convexa a través de los índices de los contornos.
     
    * Ejemplo de uso:
    	
    		convexHull(contours[i], hull);
      
      
 * ***Función defectos de convexidad (convexityDefects):***
 
    * Almacenamos en un vector tipo Vect4i la malla convexa y los índices de los contornos. A esta función se le pasa como parámetros:
      * **contours[i]:** índice del contorno.
      * **hull:** Vector de enteros que va a contener la malla convexa.
      * **defects:** Vector de tipo Vect4i que va a contener la malla convexa y los contornos.
     
    * Ejemplo de uso:
    	
    	  convexityDefects(contours[i], hull, defects);
      
      
 * ***Círculo (defecto de convexidad):***
 	
    * Para mostrar un defecto de convexidad utilizamos una función de la librería de openCV denominada circle. A esta función se le pasa como parámetros:
    	* **roi:** Imagen en la que se va a mostrar el círculo.
    	* **f:** El punto más lejano, que será el centro.
    	* **5:Radio del círculo** 
    	* **Scalar(0,0,255):** Color que tendrá el círculo, en este caso rojo (BGR).
    	* **-1:** Se rellena todo el área del círculo.
     
    * Ejemplo de uso:
    	
    		circle(roi, f, 5, Scalar(0, 0, 255), -1);
        
        
  * ***Línea (defecto de convexidad):***
 	
    * Para mostrar un defecto de convexidad utilizamos una función de la librería de openCV denominada circle. A esta función se le pasa como parámetros:
    	* **roi:** Imagen en la que se va a mostrar el círculo.
    	* **s:** El punto inicial de la  línea.
    	* **e:** El punto final  de la  línea.
    	* **Scalar(0,0,255):** Color que tendrá la línea, en este caso azul (BGR).
    	* **2:** Grosor de la línea.
     
    * Ejemplo de uso:
    	
    		line(roi, s, e, Scalar(255, 0, 0), 2);
          
          
 * ***Función texto sobre imagen (putText):***
 	
    * Para pintar sobre la imagen un texto en tiempo real (como un cout), openCV ofrece la función putText, que es la que utilizo para mostrar el número de dedos levantados y para mostar el nombre del gesto que se está haciendo. A esta función se le pasa como parámetros:
    	* **frame:** Imagen en la que se va a mostrar la string de información.
    	* **str:** String con el contenido a mostrar.
    	* **Point(400, 50):** El punto donde comienza el texto en la imagen.
    	* **FONT_HERSHEY_DUPLEX:** Tipo de fuente.
    	* **Scalar(0,255,0):** Color que tendrán las letras y números, en este caso verde (BGR).
    	* **2:** Grosor de la fuente.
     
    * Ejemplo de uso:
    	
    		putText(frame, "1", Point(400, 50), FONT_HERSHEY_DUPLEX, 1.0, Scalar(0,255,0), 2);
