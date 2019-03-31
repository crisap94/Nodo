///////////////////////////////////////////////////////////
//  OneWire.h
//  Implementation of the Interface OneWire
//  Created on:      28-Mar-2019 4:29:35 PM
//  Original author: Cristian Arrieta P
///////////////////////////////////////////////////////////

#if !defined(EA_CB99E855_7A64_4a5c_973B_185E342DC1CC__INCLUDED_)
#define EA_CB99E855_7A64_4a5c_973B_185E342DC1CC__INCLUDED_

class OneWire
{

public:
	OneWire() {

	}

	virtual ~OneWire() {

	}

	void begin();
	void getData();

protected:
	int pinConnection;

};
#endif // !defined(EA_CB99E855_7A64_4a5c_973B_185E342DC1CC__INCLUDED_)
