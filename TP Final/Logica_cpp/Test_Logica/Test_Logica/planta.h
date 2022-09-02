#pragma once
void planta(void);
class Valvulas{
public:
	bool CV01 = false;
	bool CV02 = false;
	bool CV03 = false;
	bool V01 = false;
	bool V02 = false;
	bool V03 = false;
	bool V04 = false;
	bool V05 = false;
	bool V07 = false;
};
class Bombas{
public:
	bool B01 = false;
	bool B02 = false;
};
class Motores{
public:
	bool M01 = false;
	bool M03 = false;
};
class Sensores{
public:
	bool LT01 = false;
	bool FS01 = false;
	bool LSL01 = false;
	bool LSL02 = true;
	bool TT02 = false;
	int FT01 = 0;
	int TT01 = 10;
	int TT03 = 2;
	int tiempo_maduracion = 10;
};


#define VOLUMEN_LECHE 1000
#define VELOCIDAD_DE_MEZCLA 0.1
#define TEMPERATURA_ENFRIAMIENTO = 2
#define TIEMPO_DE_MADURACION = 24 //240 minutos o 24 segundos xd
#define TEMPERATURA_DE_CONGELADO = -8
#define CAUDAL_DE_INYECCION_DE_AIRE = 10
