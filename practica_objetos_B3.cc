//**************************************************************************
// Práctica 4: Sergio Zapata de la Hoz
//**************************************************************************

#include <GL/glut.h>
#include <ctype.h>
#include <math.h>
#include <vector>
#include "objetos_B3.h"


using namespace std;

// tipos
typedef enum{CUBO, PIRAMIDE, OBJETO_PLY, ROTACION, CILINDRO, CONO, ESFERA, EXTRUSION,LAVADORA,
             MONTANA, EXCAVADORA} _tipo_objeto;
_tipo_objeto t_objeto=CUBO;
_modo   modo=POINTS;

// variables que definen la posicion de la camara en coordenadas polares
GLfloat Observer_distance;
GLfloat Observer_angle_x;
GLfloat Observer_angle_y;

// variables que controlan la ventana y la transformacion de perspectiva
GLfloat Size_x,Size_y,Front_plane,Back_plane;

// variables que determninan la posicion y tamaño de la ventana X
int Window_x=50,Window_y=50,Window_width=650,Window_high=650;


// objetos
_cubo cubo;
_piramide piramide(0.85,1.3);
_objeto_ply  ply; 
_rotacion rotacion;
_cilindro cilindro(1,2,6); 
_cono cono(1,2,6);
_esfera esfera(1,6,6);
_excavadora excavadora;
_extrusion *extrusion;
_montana montana(6,0.9, 0.8);
_lavadora lavadora;

// _objeto_ply *ply;

float giro1=0.0, giro2=0.0, giro3=0.0, alpha=0;
bool luz2_encendida = false;
int pulsar=0.0;
int paso=0;


//**************************************************************************
//
//***************************************************************************

void clean_window()
{

glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
}


//**************************************************************************
// Funcion para definir la transformación de proyeccion
//***************************************************************************

void change_projection()
{

glMatrixMode(GL_PROJECTION);
glLoadIdentity();

// formato(x_minimo,x_maximo, y_minimo, y_maximo,plano_delantero, plano_traser)
//  plano_delantero>0  plano_trasero>PlanoDelantero)
glFrustum(-Size_x,Size_x,-Size_y,Size_y,Front_plane,Back_plane);
}

//**************************************************************************
// Funcion para definir la transformación*ply1 de vista (posicionar la camara)
//***************************************************************************

void change_observer()
{

// posicion del observador
glMatrixMode(GL_MODELVIEW);
glLoadIdentity();
glTranslatef(0,0,-Observer_distance);
glRotatef(Observer_angle_x,1,0,0);
glRotatef(Observer_angle_y,0,1,0);
}

//**************************************************************************
// Funcion que dibuja los ejes utilizando la primitiva grafica de lineas
//***************************************************************************

void draw_axis()
{
	
glDisable(GL_LIGHTING);
glLineWidth(2);
glBegin(GL_LINES);
// eje X, color rojo
glColor3f(1,0,0);
glVertex3f(-AXIS_SIZE,0,0);
glVertex3f(AXIS_SIZE,0,0);
// eje Y, color verde
glColor3f(0,1,0);
glVertex3f(0,-AXIS_SIZE,0);
glVertex3f(0,AXIS_SIZE,0);
// eje Z, color azul
glColor3f(0,0,1);
glVertex3f(0,0,-AXIS_SIZE);
glVertex3f(0,0,AXIS_SIZE);
glEnd();
}


//**************************************************************************
// Funcion que dibuja los objetos
//****************************2***********************************************

void draw_objects()
{

switch (t_objeto){
	case CUBO: cubo.draw(modo,1.0,0.0,0.0,5);break;
	case PIRAMIDE: piramide.draw(modo,1.0,0.0,0.0,5);break;
        case OBJETO_PLY: ply.draw(modo,1.0,0.6,0.0,3);break;
        case ROTACION: rotacion.draw(modo,1.0,0.0,0.0,5);break;
        case CILINDRO: cilindro.draw(modo,1.0,0.0,0.0,5);break;
        case CONO: cono.draw(modo,1.0,0.0,0.0,5);break;
        case ESFERA: esfera.draw(modo,1.0,0.0,0.0,5);break;
        case EXCAVADORA: excavadora.draw(modo,1.0,0.0,0.0,5);break;
        case EXTRUSION: extrusion->draw(modo,1.0,0.0,0.0,5);break;
        case MONTANA: montana.draw(modo,0.2,0.7,0.0,1);break;
        case LAVADORA: lavadora.draw(modo, 0.5, 0.5,0.5,1);break;
	}

}

//**************************************************************************
// metodo luces
//***************************************************************************

void luces(){
    GLfloat luz_ambiente[] = {0.0,0.0,0.0,1.0},
            luz_difusa[] = {0.5,0.5,0.5,1.0},
            luz_especular[] = {1.0,1.0,1.0,1.0},
            luz_posicion[] = {10,10,10,0.1};

            GLfloat luz_ambiente2[] = {0.1,0.2,0.7,1.0},
            luz_difusa2[] = {0.1,0.5,0.7,1.0},
            luz_especular2[] = {0.0,0.3,0.7,1.0},
            luz_posicion2[] = {-10,10,10,1.0};

    glLightfv(GL_LIGHT1, GL_AMBIENT, luz_ambiente);
    glLightfv(GL_LIGHT1, GL_DIFFUSE, luz_difusa);
    glLightfv(GL_LIGHT1, GL_SPECULAR, luz_difusa);
    glLightfv(GL_LIGHT1, GL_POSITION, luz_posicion);

    glLightfv(GL_LIGHT2, GL_AMBIENT, luz_ambiente2);
    glLightfv(GL_LIGHT2, GL_DIFFUSE, luz_difusa2);
    glLightfv(GL_LIGHT2, GL_SPECULAR, luz_difusa2);
    
    glPushMatrix();
        glRotatef(alpha,0,0,1);
        glLightfv(GL_LIGHT2, GL_POSITION, luz_posicion2);
    glPopMatrix();

    if(luz2_encendida){
        glEnable(GL_LIGHT2);
    } else{
        glDisable(GL_LIGHT2);
    }

    glDisable(GL_LIGHT0);
    glEnable(GL_LIGHT1);
    
}

//**************************************************************************
//
//***************************************************************************

void draw(void)
{
clean_window();
change_observer();
luces();
draw_axis();
draw_objects();
glutSwapBuffers();
}



//***************************************************************************
// Funcion llamada cuando se produce un cambio en el tamaño de la ventana
//
// el evento manda a la funcion:
// nuevo ancho
// nuevo alto
//***************************************************************************

void change_window_size(int Ancho1,int Alto1)
{
float Aspect_ratio;

Aspect_ratio=(float) Alto1/(float )Ancho1;
Size_y=Size_x*Aspect_ratio;
change_projection();
glViewport(0,0,Ancho1,Alto1);
glutPostRedisplay();
}

//***************************************************************************
// Funcion llamada cuando se aprieta una tecla normal
//
// el evento manda a la funcion:
// codigo de la tecla
// posicion x del raton
// posicion y del raton
//***************************************************************************

void normal_key(unsigned char Tecla1,int x,int y)
{
switch (toupper(Tecla1)){
	case 'Q':exit(0);
	case '1':modo=POINTS;break;
	case '2':modo=EDGES;break;
	case '3':modo=SOLID;break;
	case '4':modo=SOLID_COLORS;break;
    case '5':modo=SOLID_COLORS_GOURAUD;break;
    case '6':modo=SOLID_PHONG_FLAT;break;
    case '7':modo=SOLID_PHONG_GOURAUD;break;
        case 'P':t_objeto=PIRAMIDE;break;
        case 'C':t_objeto=CUBO;break;
        case 'O':t_objeto=OBJETO_PLY;break;	
        case 'R':t_objeto=ROTACION;break;
        case 'L':t_objeto=CILINDRO;break;
        case 'N':t_objeto=CONO;break;
        case 'E':t_objeto=ESFERA;break;
        case 'X':t_objeto=EXTRUSION;break;
        case 'K':t_objeto=MONTANA;break;
        case 'A':t_objeto=LAVADORA;break;
        case 'Z':alpha+=5;break;
        // animacion
        case 'S':paso=1;break;
        case 'I':
            luz2_encendida = (luz2_encendida) ? false:true; break;

	}
glutPostRedisplay();
}

//***************************************************************************
// Funcion llamada cuando se aprieta una tecla especial
//
// el evento manda a la funcion:
// codigo de la tecla
// posicion x del raton
// posicion y del raton

//***************************************************************************

void special_key(int Tecla1,int x,int y)
{
switch (Tecla1){
   case GLUT_KEY_LEFT:Observer_angle_y--;break;
   case GLUT_KEY_RIGHT:Observer_angle_y++;break;
   case GLUT_KEY_UP:Observer_angle_x--;break;
   case GLUT_KEY_DOWN:Observer_angle_x++;break;
   case GLUT_KEY_PAGE_UP:Observer_distance*=1.2;break;
   case GLUT_KEY_PAGE_DOWN:Observer_distance/=1.2;break;
	
    // movimientos cajon
    case GLUT_KEY_F1:lavadora.posicion_cajon+=0.1;
        if(lavadora.posicion_cajon>lavadora.cajon_max)
            lavadora.posicion_cajon=lavadora.cajon_max; break;

    case GLUT_KEY_F2:lavadora.posicion_cajon-=0.1;
        if(lavadora.posicion_cajon<lavadora.cajon_min)
            lavadora.posicion_cajon=lavadora.cajon_min; break;
    // giros puerta
    case GLUT_KEY_F3:lavadora.giro_puerta+=2;
        if(lavadora.giro_puerta > lavadora.giro_puerta_max)
            lavadora.giro_puerta = lavadora.giro_puerta_max; break;

    case GLUT_KEY_F4:lavadora.giro_puerta-=2;
        if(lavadora.giro_puerta < lavadora.giro_puerta_min)
            lavadora.giro_puerta = lavadora.giro_puerta_min; break;
    // giro tambor
    case GLUT_KEY_F5:lavadora.giro_tambor+=1;
    if (lavadora.giro_puerta != lavadora.giro_puerta_max) {
        lavadora.giro_tambor = 0;
    } else {
        lavadora.giro_tambor+=2;
    }
    break;
    // giros ruletas
    case GLUT_KEY_F6:lavadora.giro_ruleta1+=3;
        if(lavadora.giro_ruleta1 > lavadora.giro_ruleta1_max)
            lavadora.giro_ruleta1 = lavadora.giro_ruleta1_max; break;
    case GLUT_KEY_F7:lavadora.giro_ruleta1-=3;
        if(lavadora.giro_ruleta1 < lavadora.giro_ruleta1_min)
            lavadora.giro_ruleta1 = lavadora.giro_ruleta1_min; break;
    case GLUT_KEY_F8:lavadora.giro_ruleta2+=3;
        if(lavadora.giro_ruleta2 > lavadora.giro_ruleta2_max)
            lavadora.giro_ruleta2 = lavadora.giro_ruleta2_max; break;
    case GLUT_KEY_F9:lavadora.giro_ruleta2-=3;
        if(lavadora.giro_ruleta2 < lavadora.giro_ruleta2_min)
            lavadora.giro_ruleta2 = lavadora.giro_ruleta2_min; break;
    // giros ruedas y lavadora
    case GLUT_KEY_F10:lavadora.giro_ruedas+=8;
        lavadora.posicion_lavadora_z += 0.01; break;
    case GLUT_KEY_F11:lavadora.giro_ruedas-=8;
        lavadora.posicion_lavadora_z -= 0.01; break;

	}
glutPostRedisplay();
}

//***************************************************************************
// Funcion llamada cuando se selecciona una opción del menú
//
// el evento manda a la funcion:
// entero que representa una entrada del menú 
//***************************************************************************

void menu(int key)
{

   if (key==0)
        {excavadora.giro_pala+=4;
        if (excavadora.giro_pala > excavadora.giro_pala_max)
            excavadora.giro_pala = excavadora.giro_pala_max;
        }
   if (key==1)
        {excavadora.giro_pala-=4;
        if (excavadora.giro_pala < excavadora.giro_pala_min)
            excavadora.giro_pala = excavadora.giro_pala_min;
        }
   if (key==2)
          {giro1=1.0;
           giro2=1.0;
           giro3=0.25;
           }
   if (key==3)
          {giro1=0.0;
          giro2=0.0;
          giro3=0.0;
          }
}




//***************************************************************************
// Funcion de animación automática
//***************************************************************************

void animacion(){
    switch(paso){
        case 1:lavadora.posicion_cajon+=0.05;
            if(lavadora.posicion_cajon>lavadora.cajon_max - 0.05)
                paso = 2; break;
        case 2:lavadora.posicion_cajon-=0.05;
            if(lavadora.posicion_cajon<lavadora.cajon_min + 0.05)
                paso = 3; break;
        case 3:lavadora.posicion_cajon = lavadora.cajon_min;
            paso = 4; break;
        case 4:lavadora.giro_ruleta1+=1;
            if(lavadora.giro_ruleta1 > lavadora.giro_ruleta1_max/2)
                paso = 5; break;
        case 5:lavadora.giro_ruleta2+=1;
            if(lavadora.giro_ruleta2 > lavadora.giro_ruleta2_max - 45 )
                paso = 6; break;
        case 6:lavadora.giro_puerta+=1;
            if(lavadora.giro_puerta > lavadora.giro_puerta_max -2)
                paso = 7; break;
        case 7: lavadora.giro_tambor+=1;
            if (lavadora.giro_tambor > lavadora.fin_lavado)
                paso = 8; break;
        case 8:lavadora.giro_puerta-=1;
            if(lavadora.giro_puerta < lavadora.giro_puerta_min + 2)
                paso = 9; break;
        case 9:lavadora.giro_ruleta1-=1;
            if(lavadora.giro_ruleta1 < lavadora.giro_ruleta1_min + 1)
                paso = 10; break;
        case 10:lavadora.giro_ruleta2-=1;
            if(lavadora.giro_ruleta2 < lavadora.giro_ruleta2_min + 1 )
                paso = 11; break;
        case 11: lavadora.giro_ruedas+=8; lavadora.posicion_lavadora_z += 0.01;
            if(lavadora.posicion_lavadora_z > 3)
                paso = 12; break;
        case 12: lavadora.giro_ruedas-=8; lavadora.posicion_lavadora_z -= 0.01;
         if(lavadora.posicion_lavadora_z < 0.01)
                paso = 13; break;
        case 13: break;
    }

    glutPostRedisplay();
}


//***************************************************************************
// Funcion de incializacion
//***************************************************************************

void initialize(void)
{
// se inicalizan la ventana y los planos de corte
Size_x=0.5;
Size_y=0.5;
Front_plane=1;
Back_plane=1000;

// se incia la posicion del observador, en el eje z
Observer_distance=10*Front_plane;
Observer_angle_x=0;
Observer_angle_y=0;

// se indica el color para limpiar la ventana	(r,v,a,al)
// blanco=(1,1,1,1) rojo=(1,0,0,1), ...
glClearColor(1,1,1,1);

// se habilita el z-bufer
glEnable(GL_DEPTH_TEST);
change_projection();
glViewport(0,0,Window_width,Window_high);
}


//***************************************************************************
// Programa principal
//
// Se encarga de iniciar la ventana, asignar las funciones e comenzar el
// bucle de eventos
//***************************************************************************


int main(int argc, char *argv[] )
{
 
// perfil 

vector<_vertex3f> perfil, poligono;
_vertex3f aux;

aux.x=1.0; aux.y=-1.0; aux.z=0.0;
perfil.push_back(aux);
aux.x=1.5; aux.y=0.0; aux.z=0.0;
perfil.push_back(aux);
aux.x=1.0; aux.y=1.0; aux.z=0.0;
perfil.push_back(aux);
aux.x=1.5; aux.y=1.2; aux.z=0.0;
perfil.push_back(aux);


rotacion.parametros(perfil,6,1,1,0);

aux.x=1.0; aux.y=0.0; aux.z=1.0;
poligono.push_back(aux);
aux.x=1.0; aux.y=0.0; aux.z=-1.0;
poligono.push_back(aux);
aux.x=-1.2; aux.y=0.0; aux.z=-1.0;
poligono.push_back(aux);
aux.x=-0.8; aux.y=0.0; aux.z=0.0;
poligono.push_back(aux);
aux.x=-1.2; aux.y=0.0; aux.z=1.0;
poligono.push_back(aux);

extrusion= new _extrusion(poligono, 0.25, 1.0, 0.25);

// se llama a la inicialización de glut
glutInit(&argc, argv);

// se indica las caracteristicas que se desean para la visualización con OpenGL
// Las posibilidades son:
// GLUT_SIMPLE -> memoria de imagen simple
// GLUT_DOUBLE -> memoria de imagen doble
// GLUT_INDEX -> memoria de imagen con color indizado
// GLUT_RGB -> memoria de imagen con componentes rojo, verde y azul para cada pixel
// GLUT_RGBA -> memoria de imagen con componentes rojo, verde, azul y alfa para cada pixel
// GLUT_DEPTH -> memoria de profundidad o z-bufer
// GLUT_STENCIL -> memoria de estarcido_rotation Rotation;
glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);

// posicion de la esquina inferior izquierdad de la ventana
glutInitWindowPosition(Window_x,Window_y);

// tamaño de la ventana (ancho y alto)
glutInitWindowSize(Window_width,Window_high);

// llamada para crear la ventana, indicando el titulo (no se visualiza hasta que se llama
// al bucle de eventos)
glutCreateWindow("PRACTICA - 3");

// asignación de la funcion llamada "dibujar" al evento de dibujo
glutDisplayFunc(draw);
// asignación de la funcion llamada "change_window_size" al evento correspondiente
glutReshapeFunc(change_window_size);
// asignación de la funcion llamada "normal_key" al evento correspondiente
glutKeyboardFunc(normal_key);
// asignación de la funcion llamada "tecla_Especial" al evento correspondiente
glutSpecialFunc(special_key);

 // Creamos menú
glutCreateMenu(menu);
glutAddMenuEntry("Girar pala positivo", 0);
glutAddMenuEntry("Girar pala negativo", 1);
glutAddMenuEntry("Activar animación", 2);
glutAddMenuEntry("Desactivar animación", 3);
glutAttachMenu(GLUT_LEFT_BUTTON);


glutIdleFunc(animacion);

// funcion de inicialización
initialize();

// creación del objeto ply
ply.parametros(argv[1]);

//ply = new _objeto_ply(argv[1]);

// inicio del bucle de eventos
glutMainLoop();
return 0;
}
