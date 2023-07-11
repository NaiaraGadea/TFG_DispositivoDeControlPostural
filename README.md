<image src="/img/cabeceraSalud.jpg"  width="900">
  
  
# Dispositivo de Control Postural  (2023)

### Alumna: **Naiara Gadea Rodríguez Gómez**  

Este repositorio recoge los documentos del Trabajo de Fin de Grado del grado en Ingeniería de la Salud de la [Universidad de Burgos](https://www.ubu.es/). En este repositorio se puede seguir el desarrollo del TFG, cuyo objetivo es el desarrollo de un dispositivo de control postural.

## **Resumen**
Este trabajo se centra en la búsqueda de una solución a una necesidad real con el fin de la creación de un dispositivo de control postural para el apoyo de la mejora de la postura en diferentes colectivos. Durante el desarrollo del proyecto se han estudiado los aspectos teóricos de la postura y el control postural. Por otro lado, se ha indagado en las distintas soluciones disponibles en el mercado actual con el fin de predefinir las características básicas que debería tener el dispositivo ideado. 

Tras la obtención de la idea, se ha realizado una búsqueda de los posibles componentes y se han sopesado los componentes a incluir. Se han creado dos versiones del prototipo. En la primera versión se emplea un sensor de inclinación muy sencillo y en la segunda versión se utiliza un sensor MPU más complejo que ofrece más precisión y mayores posibilidades. En el proyecto también se propone un prototipo de interfaz de una aplicación de interacción usuario-dispositivo.

La última versión del prototipo consigue un correcto control postural. Sin embargo, al tratarse de un prototipo, existen varios puntos de mejora y en el proyecto se ofrecen diferentes líneas para seguir el proyecto en un futuro.


## **Abstract**
This work focuses on finding a solution to a real need in order to create a postural control device to support posture improvement in different groups. During the development of the project, the theoretical aspects of posture and postural control were studied. On the other hand, we have investigated the different solutions available in the current market in order to specify the basic features that the device should have. 

After obtaining the idea, a search of the possible components was made and the components to be incuded were weighed. Two versions of the prototype have been created. The first version uses a very simple tilt sensor and the second version uses a more complex MPU sensor that offers more precision and greater possibilities. The project also proposes a prototype app interface for well user-device interaction.

The latest version of the prototype achieves correct postural control. However, the fact of being a prototype, there are several points of improvement. Different lines have been included to further develop and improve the project in the future.

## **Introducción**
Este trabajo surge de una visita a la [Asociación Parkinson Burgos](https://parkinsonburgos.org/) donde nos dieron a conocer su trabajo allí y varios problemas con los que se encontraban durante la realización del mismo. Una de las dificultades comunicadas era la de tener que estar en constante supervisión de que las personas con parkinson adoptaran mientras caminaban una postura correcta, puesto que en muchos casos no se daban cuenta por sí mismos que habían adoptado posturas incorrectas durante el desarrollo de la actividad. Por ello, la principal motivación que se persigue en este proyecto es la búsqueda de una solución sencilla, accesible y  a esta necesidad.


## **Objetivos**

Inicialmente, se plantean una serie de objetivos, para los cuales se obtendrá respuesta tras el análisis correspondiente de los datos:

1.  Comprender los fundamentos básicos de la postura, los beneficios de una postura natural correcta y sus modificaciones a lo largo de la vida o por la realización de ciertas actividades.
2. Comprender el proceso completo desde la comunicación de una necesidad real y el desarrollo y creación de una idea.
3. Estudio de los dispositivos actuales destinados al control postural y sus posibilidades.
4. Análisis de dispositivos y componentes que puedan ser empleados en el desarrollo del dispositivo de control postural ideado del proyecto.
5. Creación de uno o varios prototipos del dispositivo de control postural que avisen en caso de que el usuario se encuentre posicionado en una mala postura que sea sencillo, completo y de bajo coste.
6. El dispositivo tendrá la finalidad de mejorar la postura mediante aprendizaje dinámico basado en biofeedback.
7. Creación de un prototipo de interfaz que facilite la interacción del usuario con el dispositivo.
8. Aunar los conocimientos sanitarios y técnicos adquiridos a lo largo del grado en Ingeniería de la salud.
9. Análisis de costes y viabilidad legal del dispositivo propuesto.
10. Uso de herramientas como [GitHub](https://github.com/) o [Trello](https://trello.com/) para el seguimiento de los documentos del trabajo al igual que para la recopilación del código de los programas y documentos realizados en el proyecto.
11. Emplear [Overleaf](https://www.overleaf.com/) como editor LaTex para la creación de los documentos entregables.
12. Emplear el entorno de [Arduino](https://www.arduino.cc/) para la creación del prototipo.
13. El dispositivo ideado tiene la finalidad de ayudar a distintos colectivos.
14. Realizar un trabajo reproducible en el futuro para que otras personas puedan realizar los prototipos gracias a los datos y conocimientos desarrollados en el proyecto.
15. Demostrar que es posible dar soluciones técnicas desde la titulación de Ingeniería de la Salud a distintos perfiles de personas, incluyendo asociaciones de personas con discapacidad como puede ser la [Asociación Parkinson Burgos](https://parkinsonburgos.org/), gracias a la realización de trabajos de fin de grado con fines sociales.

## **Contenidos del repositorio**
En el repositorio encontraremos los siguientes ficheros y directorios:
- **Carpeta img**: carpeta dónde se incluyen todas las imágenes que se ha empleado en el desarrollo del proyecto.
- **Carpeta tex**: carpeta que incluye todos los capítulos de la memoria.
  - 1_objetivos.tex: documento LaTex que contiene la información acerca de los objetivos.
  - 2_introduccion.tex: documento LaTex que contiene la información acerca de la introducción del trabajao, se incluyen conceptos teóricos básicos y el estado del arte.
  - 3_metodologia.tex: documento LaTex que contiene la información acerca de la metodología empleada, dónde se incluyen descripción de los datos con los que se trabajan y técnicas y herramientas.
  - 4_conclusiones.tex: documento LaTex que contiene las conclusiones del proyecto, se puede encontrar un resumen de resultados, discusión y aspectos relevantes.
  - 5_lineas_futuras.tex: documento LaTex que contiene la información acerca de las líneas de trabajo futuras.
  - A_planificacion.tex: documento LaTex que contiene información del anexo A, donde se incluye la planificación temporal, la planificación económica y la viabilidad legal en España del trabajo.
  - B_manual_usuario.tex: documento LaTex que contiene la información del anexo B que incluye los requisitos funcionales y no funcionales, la instalación y puesta en marcha y manuales o demostraciones prácticas.
  - C_manual_programador.tex: documento LaTex que contiene la información del anexo C que contiene la estructura de los directorios entregados, la información acerca de la ejecución del proyecto y las instrucciones de mejora del proyecto.
  - D_datos.tex: documento LaTex que contiene la información acerca de los datos utilizados en el proyecto.
  - E_diseno.tex: documento LaTex que contiene la información acerca del diseño del prototipo realizado.
  - F_requisitos.tex: documento LaTex que contiene la información acerca los casos de uso definidos.
  - G_experimental.tex: documento LaTex que contiene la información acerca del estudio experimental realizado.
  - readme.txt: documento de información de la carpeta.
- **Carpeta videos**: carpeta dónde se encuentran los vídeos de demostración del proyecto.
  - DemostracionV1: Vídeo de la demostración de la primera versión del prototipo.
  - DemostracionV2: Vídeo de la demostración de la segunda versión del prototipo.
- **Carpeta memoria_PDF**: carpeta dónde se encuentran los documentos PDF de la memoria.
  - memoria_NaiaraRodriguez.pdf: documento PDF que contiene la memoria completa.
  - anexos_NaiaraRodriguez.pdf: documento PDF que contiene los anexos completos.
  - PresentacionTFG_NaiaraRodriguez.pdf: documento PDF que contiene la presentacion realizada para la defensa del proyecto.
- **Carpeta Arduino**: carpeta dónde se encuentran los programas de Arduino empleados en las distintas versiones del prototipo del proyecto.
  - ProgramaV1.ino: Programa que se ha de cargar en la placa de Arduino de la primera versión del prototipo del dispositivo de control postural, dónde se emplea el sensor SW520D.
  - ProgramaV2.ino: Programa que se ha de cargar en la placa de Arduino de la segunda versión del prototipo del dispositivo de control postural, dónde se emplea el módulo MPU-6050.
- **README.md**: archivo de presentación del repositorio de GitHub.
- **anexos.tex**: archivo LaTex que contiene la estructura del documento pdf de los anexos.
- **bibliografia.bib**: archivo que recoge la bibliografía de la memoria.
- **bibliografiaAnexos.bib**: archivo que recoge la bibliografía de los anexos.
- **memoria.tex**: archivo LaTex que contiene la estructura del documento de la memoria.
