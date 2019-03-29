///////////////////////////////////////////////////////////
//  DataManager.h
//  Implementation of the Class DataManager
//  Created on:      28-Mar-2019 4:29:33 PM
//  Original author: Cristian Arrieta P
///////////////////////////////////////////////////////////

#if !defined(EA_542022A9_4749_4b6e_BA6F_80DFB9BB0B34__INCLUDED_)
#define EA_542022A9_4749_4b6e_BA6F_80DFB9BB0B34__INCLUDED_

#include "FactorySensorManager.h"

class DataManager
{

public:
	DataManager();
	virtual ~DataManager();
	FactorySensorManager *m_FactorySensorManager;

	float getVariableData();
	void packPayload(int type, float value);

private:
	FactorySensorManager factoryManager;
	/**
	 * Contiene la informacion ya depurada de cada una de las variables medidas en
	 * formato JSON.
	 * 
	 * Temperatura Ambiental
	 * Presion Atmosferica
	 * Temperatuira de la Bateria
	 * Luminosidad
	 * Epoch (fecha)
	 * Humedad Relativa
	 * Humedad de Suelo
	 * Temperatura de Suelo
	 * Voltaje de Panel
	 * Indice Ultravioleta
	 * Componentes organicos volatiles
	 */
	char JSONpayload;

};
#endif // !defined(EA_542022A9_4749_4b6e_BA6F_80DFB9BB0B34__INCLUDED_)
