# Reconocimiento de gestos con OpenCV


 * ***Objeto Mat***:
 	
    * Con este objeto crearemos las imágenes que vamos a necesitar. En nuestro caso vamos a utilizar como imágenes: 
    	* **frame:** para la imagen principal (la que recoge la webcam).
    	
    	* **roi:** para la región de interés (la que nos vamos a centrar).
    	
    	* **fgMask:** para la imagen binaria.
    	
        
        
        
    		Ejmeplo de uso:
    	
    			Mat frame, roi, fgMask; 

 * ***Objeto VideoCapture***:
 	
    * Este objeto nos permite capturar imagenes desde la webcam para volcarlas sobre los objetos imágenes Mat. Además, se utiliza el método open, en el que se le pasa como parámetro un 0, para indicar que utilizaremos la webcam que viene por defecto.
    
    
    		Ejmeplo de uso:
    	
    			VideoCapture cap; 
    			cap.open(0);
