#pragma once
void planta(void);
class Valvulas{
public:
	bool CV01;
	bool CV02;
	bool CV03;
	bool V01 ;
	bool V02 ;
	bool V03 ;
	bool V04 ;
	bool V05 ;
	bool V07 ;
};
class Bombas{
public:
	bool B01;
	bool B02;
};
class Motores{
public:
	bool M01;
	bool M03;
};
class Sensores{
public:
	bool LT01 = false;
	bool FS01 = false;
	bool LSL01 = false;
	bool LSL02 = true;
	int FT01 = 0;
	int TT01 = 10;
	int TT02 = 12;
	int TT03 = 2;
	int tiempo_maduracion = 10;
};


#define VOLUMEN_LECHE 1000
#define VELOCIDAD_DE_MEZCLA 0.1
#define TEMPERATURA_ENFRIAMIENTO = 2
#define TIEMPO_DE_MADURACION = 24 //240 minutos o 24 segundos xd
#define TEMPERATURA_DE_CONGELADO = -8
#define CAUDAL_DE_INYECCION_DE_AIRE = 10

#define UPPER_BOUND_CAUDAL 10
#define LOWER_BOUND_CAUDAL 0
#define LIMIT_T1 15
#define LIMIT_T2 LIMIT_T1
#define LIMIT_T3 LIMIT_T1


