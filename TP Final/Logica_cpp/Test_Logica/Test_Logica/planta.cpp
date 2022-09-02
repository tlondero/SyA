#include "planta.h"
#include <thread>
#include <iostream>
extern bool s_finished;



extern Sensores mySensors = Sensores();

void planta(void) {
	using namespace std::literals::chrono_literals;
	using namespace std;

	Motores myMotors = Motores();
	Valvulas myValves = Valvulas();
	Bombas myPumps = Bombas();

	static bool condiciones_iniciales = true;
	static bool comienzo_llenacion_tanque = false;
	static bool comienzo_mezcla_ingredientes = false;
	static bool comienzo_maduracion = false;
	static bool comienzo_congelado = false;
	static bool PID1 = false;
	static bool PID2 = false;
	static bool PID3 = false;

	while (!s_finished) {
		std::this_thread::sleep_for(5s);
		cout << "-----------------------------------------------------------" << endl;
		if (condiciones_iniciales) {
			cout << "Condiciones inciales ok, avanzando de etapa" << endl;
			comienzo_llenacion_tanque = true;
			condiciones_iniciales = false;
		}
		if (comienzo_llenacion_tanque) {
			if (!mySensors.LT01) {
				myValves.V01 = true;
				cout << "Ingreso de leche al tanque" << endl;
			}
			else {
				cout << "Tanque lleno de leche" << endl;
				comienzo_mezcla_ingredientes = true;
				myValves.V01 = false;
				comienzo_llenacion_tanque = false;
			}
		}
		if (comienzo_mezcla_ingredientes) {
			cout << "Etapa Mezcla de ingredientes." << endl;
			cout << "Valvula V02, V03 y bomba B02 abiertas-prendidas" << endl;
			myValves.V02 = true;
			myValves.V03 = true;
			myPumps.B02 = true;
			if (mySensors.FS01 && mySensors.LSL02) {
				cout << "FS01 detecto flujo y aun no se vacio la tolba, aunque fue abierta" << endl;
				myValves.V04 = true;
			}
			if (!mySensors.LSL02) {
				cout << "Tolba vacia, y agitador M01 prendido en enfriamiento" << endl;
				myMotors.M01 = true;
				myValves.V04 = false;
			}
			if (myMotors.M01) {
				//Aca se activa el PID
				cout << "Se activo lazo PID para temperatura TT01" << endl;
				PID1 = true;
				if (mySensors.TT01 == 2) {
					cout << "Temperatura target Alcanzada" << endl;
					PID1 = false;
					myPumps.B02 = false;
					myValves.V02 = false;
					myValves.V03 = false;
					myValves.CV01 = false;
					cout << "Se detuvo el lazo PID1 y se apaga-cierra B02, V02 y V03." << endl;
					comienzo_maduracion = true;
					comienzo_mezcla_ingredientes = false;
				}
				else {
					myValves.CV01 = true;
					cout << "Realizando cambios en CV01 para alcanzar temperatura" << endl;
					cout << "temperatura acutal " << mySensors.TT01-- << endl;
				}
				//
			}
		}
		if (comienzo_maduracion) {
			static int t = 0;
			cout << "Comienzo manduracion" << endl;
			myMotors.M01 = true;
			cout << "Motor M01 puesto a velocidad maduracion" << endl;
			if (mySensors.tiempo_maduracion == t) {
				cout << "Tiempo de maduracion transcurrido" << endl;
				myMotors.M01 = false;
				comienzo_congelado = true;
				comienzo_maduracion = false;
			}
			else {
				cout << "Tiempo: " << t++ << endl;;
			}
		}
		if (comienzo_congelado) {
			cout << "Etapa Congelado" << endl;
			cout << "Agitador prendido y valvulas V05, V07 abiertas" << endl;
			myMotors.M01 = true;
			myValves.V05 = true;
			myValves.V07 = true;
			cout << "Bomba B01 y Motor M03 prendido" << endl;
			myPumps.B01 = true;
			myMotors.M03 = true;
			//Aca se activa el PID3
			cout << "Se activo lazo PID para temperatura TT03" << endl;
			PID3 = true;
			if (mySensors.TT03 == -8) {
				cout << "Temperatura target Alcanzada" << endl;
			}
			else {
				myValves.CV03 = true;
				cout << "Realizando cambios en CV02 para alcanzar temperatura" << endl;
				cout << "temperatura acutal " << mySensors.TT03-- << endl;
			}//

			//Aca se activa el PID2
			cout << "Se activo lazo PID para caudal de aire congelador" << endl;
			PID2 = true;
			if (mySensors.FT01 == 5) {
				cout << "Caudal de aire target alcanzado" << endl;
			}
			else {
				myValves.CV02 = true;
				cout << "Realizando cambios en CV02 para alcanzar caudal de aire" << endl;
				cout << "caudal acutal " << mySensors.FT01++ << endl;
			}//
			if (mySensors.LSL01) {
				cout << "Tanque vacio, llenado completo" << endl;
				PID2 = false;
				PID3 = false;
				cout << "PIDS apagados, Valvuals CV03 y CV02 cerradas, apagado M01 B01 y M03" << endl;
				comienzo_congelado = false;
				myValves.CV03 = false;
				myValves.CV02 = false;
				myMotors.M01 = false;
				myPumps.B01 = false;
				myMotors.M03 = false;
				myValves.V07 = false;
			}

		}


	}
}