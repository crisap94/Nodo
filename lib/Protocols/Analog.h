///////////////////////////////////////////////////////////
//  Analog.h
//  Implementation of the Interface Analog
//  Created on:      28-Mar-2019 4:29:32 PM
//  Original author: Cristian Arrieta P
///////////////////////////////////////////////////////////

#if !defined(EA_AE86ED43_B1FA_4da5_9E4D_B6A47B71A57B__INCLUDED_)
#define EA_AE86ED43_B1FA_4da5_9E4D_B6A47B71A57B__INCLUDED_

class Analog
{

public:
	Analog() {

	}

	virtual ~Analog() {

	}

protected:
	int pinConnection;
	int samplingInterval;

};
#endif // !defined(EA_AE86ED43_B1FA_4da5_9E4D_B6A47B71A57B__INCLUDED_)
