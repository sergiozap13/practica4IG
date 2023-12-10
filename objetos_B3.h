//**************************************************************************
// Práctica 2 
//**************************************************************************

#include <vector>
#include <GL/gl.h>
#include "vertex.h"
#include <stdlib.h>


const float AXIS_SIZE=5000;
typedef enum{POINTS,EDGES,SOLID,SOLID_COLORS, SOLID_COLORS_GOURAUD
              ,SOLID_PHONG_FLAT, SOLID_PHONG_GOURAUD} _modo;

//*************************************************************************
// clase punto
//*************************************************************************

class _puntos3D
{
public:

  
	_puntos3D();
void 	draw_puntos(float r, float g, float b, int grosor);

vector<_vertex3f> vertices;
};

//*************************************************************************
// clase triángulo
//*************************************************************************

class _triangulos3D: public _puntos3D
{
public:

	_triangulos3D();
void 	draw_aristas(float r, float g, float b, int grosor);
void    draw_solido(float r, float g, float b);
void   draw_solido_brillo_plano();
void   draw_solido_brillo_suave();
void 	draw_solido_colores();
void   draw_solido_colores_vertices();
void 	draw(_modo modo, float r, float g, float b, float grosor);

/* asignación de colores */
void 	colors_random();
void 	colors_chess(float r1, float g1, float b1, float r2, float g2, float b2);
void   colors_diffuse_flat (float kr, float kg, float kb,
                             float lpx, float lpy, float lpz);
                             
void   colors_diffuse_gouraud  (float kr, float kg, float kb,
                                 float lpx, float lpy, float lpz);                            
/* calcular normales */

void    calcular_normales_caras();
void    calcular_normales_vertices();

vector<_vertex3i> caras;
vector<_vertex3f> colores_caras;
vector<_vertex3f> colores_vertices;
vector<_vertex3f> normales_caras;
vector<_vertex3f> normales_vertices;

int calcular_nc, calcular_nv;

// material
_vertex4f ambiente;
_vertex4f difuso;
_vertex4f especular;
float brillo; 

};

//*************************************************************************
// objetos o modelos
//*************************************************************************

//*************************************************************************
// clase cubo
//*************************************************************************

class _cubo: public _triangulos3D
{
public:

	_cubo(float tam=0.5);
};


//*************************************************************************
// clase piramide
//*************************************************************************

class _piramide: public _triangulos3D
{
public:

	_piramide(float tam=0.5, float al=1.0);
};

//*************************************************************************
// clase objeto ply
//*************************************************************************

class _objeto_ply: public _triangulos3D
{
public:
   _objeto_ply();

void  parametros(char *archivo);
};

//************************************************************************
// objeto por revolución
//************************************************************************


class _rotacion: public _triangulos3D
{
public:
       _rotacion();
       
void  parametros(vector<_vertex3f> perfil, int num,  
                 int tapa_in, int tapa_su, int tipo);
};

// tapa_in=0 sin tapa, tapa_in=1 con tapa
// tapa_su=0 sin tapa, tapa_su=1 con tapa
// tipo=0 revolucion normal
// tipo=1 esfera
// tipo=2 cono

//************************************************************************
// objeto por extrusión
//************************************************************************

class _extrusion: public _triangulos3D
{
public:
       _extrusion(vector<_vertex3f> poligono, float x, float y, float z);
};


//************************************************************************
// objeto por revolución especiales
//************************************************************************

 
//************************************************************************
// cilindro
//************************************************************************

class _cilindro: public _rotacion
{
public:
       _cilindro(float radio=1.0, float altura=2.0, int num=12);
};

//************************************************************************
// cono
//************************************************************************

class _cono: public _rotacion
{
public:
       _cono(float radio=1.0, float altura=2.0, int num=12);
};

//************************************************************************
// esfera
//************************************************************************

class _esfera: public _rotacion
{
public:
       _esfera(float radio=1.0, int latitud=6, int longitud=6);
};


//************************************************************************
// rotacion archivo PLY
//************************************************************************

class _rotacion_PLY: public _rotacion
{
public:
       _rotacion_PLY();
void  parametros_PLY(char *archivo, int num);
};


//************************************************************************
// objeto montaña fractal
//************************************************************************

class _montana: public _triangulos3D
{
public:
       _montana(int nivelmax, float sigma, float h);
};

// nivelmax, ha de ser par es el tamaño de la cuadrícula
// sigma, se relaciona con la altura máxima de la montaña
// h 0<=h<=1, dimensión de Hausdorff indica la forma del relieve, más suave 1



//************************************************************************
// práctica 3, objeto jerárquico articulado excavadora
//************************************************************************

//************************************************************************
// piezas
//************************************************************************

//************************************************************************
// pala
//************************************************************************

class _pala: public _triangulos3D
{
public:
      _pala(float radio=1.0, float ancho=2.0, int num=8);
};

//************************************************************************
// brazo
//************************************************************************

class _brazo: public _triangulos3D
{
public:
      _brazo();
void  draw(_modo modo, float r, float g, float b, float grosor);

float ancho;
float alto;
float fondo;

protected:
_cubo cubo;
};

//************************************************************************
// cabina
//************************************************************************

class _cabina: public _triangulos3D
{
public:
       _cabina();
void  draw(_modo modo, float r, float g, float b, float grosor);

float ancho;
float alto;
float fondo;

protected:
_cubo cubo;
};

//************************************************************************
// sustentación
//************************************************************************

class _sustentacion: public _triangulos3D
{
public:
      _sustentacion();
void  draw(_modo modo, float r, float g, float b, float grosor);
       
float ancho;
float alto;
float fondo;

float radio;

protected:
_cilindro rueda;
_cubo base;
};

//************************************************************************
// excavadora (montaje del objeto final)
//************************************************************************

class _excavadora: public _triangulos3D
{
public:
       _excavadora();
       
void  draw(_modo modo, float r, float g, float b, float grosor);

float giro_cabina;
float giro_primer_brazo;
float giro_segundo_brazo;
float giro_pala;

float giro_primer_brazo_max;
float giro_primer_brazo_min;
float giro_segundo_brazo_max;
float giro_segundo_brazo_min;
float giro_pala_max;
float giro_pala_min;

float tamanio_pala;

protected:
_pala pala;
_brazo brazo;
_cabina cabina;
_sustentacion sustentacion;
};

//************************************************************************
// práctica 3, LAVADORA
//************************************************************************

//************************************************************************
// piezas
//************************************************************************

//************************************************************************
// clase ruleta
//************************************************************************

class _ruleta : public _triangulos3D{
       public: _ruleta();
       void  draw(_modo modo, float r, float g, float b, float grosor);

       float ancho_cilindro;
       float alto_cilindro;
       float fondo_cilindro;

       float ancho_cubo;
       float alto_cubo;
       float fondo_cubo;

       protected:
       _cilindro cilindro;
       _cubo cubo;
};

//************************************************************************
// clase boton_apagado
//************************************************************************

class _boton_apagado : public _triangulos3D{
       public: _boton_apagado();
       void  draw(_modo modo, float r, float g, float b, float grosor);

       float ancho;
       float alto;
       float fondo;

       protected:
       _cilindro cilindro;
};

//************************************************************************
// clase cuerpo 
//************************************************************************
class _cuerpo : public _triangulos3D{
       public: _cuerpo();
       void  draw(_modo modo, float r, float g, float b, float grosor);

       float ancho;
       float alto;
       float fondo;

       protected:
       _cubo base;
       _cubo cubo_pequeño;
       
};
//************************************************************************
// clase cajon 
//************************************************************************
class _cajon : public _triangulos3D{
       public: _cajon();
       void  draw(_modo modo, float r, float g, float b, float grosor);

       float ancho;
       float alto;
       float fondo;

       protected:
       _cubo cubo; 
};

//************************************************************************
// clase puerta 
//************************************************************************
class _puerta : public _triangulos3D{
       public: _puerta();
       void  draw(_modo modo, float r, float g, float b, float grosor);

       float ancho_cilindro;
       float alto_cilindro;
       float fondo_cilindro;

       float ancho_cilindro2;
       float alto_cilindro2;
       float fondo_cilindro2;

       float ancho_cubo;
       float alto_cubo;
       float fondo_cubo;

       protected:
       _cilindro cilindro;
       _cilindro cilindro2;
       _cubo cubo;
};

//************************************************************************
// clase rueda 
//************************************************************************

class _rueda : public _triangulos3D{
       public: _rueda();
       void  draw(_modo modo, float r, float g, float b, float grosor);

       float ancho_cilindro;
       float alto_cilindro;
       float fondo_cilindro;
       
       float ancho_base;
       float alto_base;
       float fondo_base;

       float ancho_palo;
       float alto_palo;
       float fondo_palo;

       protected:
       _cilindro cilindro;
       _cubo palo;
       _cubo base;
};



//************************************************************************
// clase tambor 
//************************************************************************

class _tambor : public _triangulos3D{
       public: _tambor();
       void  draw(_modo modo, float r, float g, float b, float grosor);

       float ancho;
       float alto;
       float fondo;

       protected:
       _cilindro cilindro;
};

//************************************************************************
// lavadora (montaje del objeto final)
//************************************************************************
class _lavadora : public _triangulos3D{
       public: _lavadora();
       void  draw(_modo modo, float r, float g, float b, float grosor);
       // cajon y puerta
       float posicion_cajon;
       float cajon_max;
       float cajon_min;
       float giro_puerta;
       float giro_puerta_max;
       float giro_puerta_min;
       // tambor
       float giro_tambor;
       // ruletas
       float giro_ruleta1;
       float giro_ruleta1_max;
       float giro_ruleta1_min;

       float giro_ruleta2;
       float giro_ruleta2_max;
       float giro_ruleta2_min;

       float color_r_boton;
       // movimientos lavadora completa
       float posicion_lavadora_z;
       float giro_ruedas;

       // fin del lavado
       float fin_lavado;
       
       protected:
       _puerta puerta;
       _cajon cajon;
       _cuerpo cuerpo;
       _tambor tambor;
       _ruleta ruleta;
       _boton_apagado boton_apagado;
       _rueda rueda;
};