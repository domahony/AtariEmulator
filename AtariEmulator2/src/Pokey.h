/*
 * Pokey.h
 *
 *  Created on: Mar 8, 2015
 *      Author: domahony
 */

#ifndef POKEY_H_
#define POKEY_H_

#include <vector>

namespace address {

class Pokey {

public:
	Pokey();
	virtual ~Pokey();

	unsigned char read(unsigned short addr) const;
	void write(unsigned short addr, unsigned char val);

	void tick();

	bool IRQ() {
		unsigned char en = get_enabled_irq();
		unsigned char set = get_irq();

		bool ret = en & (~set);

		return ret;
	}

	enum ReadReg {
		POT0=	0x00,
		POT1=	0x01,
		POT2=	0x02,
		POT3=	0x03,
		POT4=	0x04,
		POT5=	0x05,
		POT6=	0x06,
		POT7=	0x07,
		ALLPOT=	0x08,
		KBCODE=	0x09,
		RANDOM=	0x0A,
		SERIN=	0x0D,
		IRQST=	0x0E,
		SKSTAT=	0x0F,
	};

	enum WriteReg {
		AUDF1=	0x00,
		AUDC1=	0x01,
		AUDF2=	0x02,
		AUDC2=	0x03,
		AUDF3=	0x04,
		AUDC3=	0x05,
		AUDF4=	0x06,
		AUDC4=	0x07,
		AUDCTL=	0x08,
		STIMER=	0x09,
		SKREST=	0x0A,
		POTGO=	0x0B,
		SEROUT=	0x0D,
		IRQEN=	0x0E,
		SKCTL=	0x0F,
	};

	enum IRQ_T {
		BREAK	= 7,
		K		= 6,
		SIR		= 5,
		ODN		= 4,
		XD		= 3,
		T4		= 2,
		T2		= 1,
		T1		= 0,
	};

	struct IRQEN {
		int BREAK;
		int K;
		int SIR;
		int ODN;
		int XD;
		int T1;
		int T2;
		int T4;
	};

private:
	void enable_irq(unsigned char);
	unsigned char get_irq() const;

	unsigned char get_enabled_irq() const;
	unsigned char get_set_irq() const;

	std::vector<unsigned char> reg;
	struct IRQEN irqen;
	struct IRQEN irqset;

	bool transmit_byte_ready;
	int transmit_idx;
	unsigned char transmit;

	int recieve_idx;
	unsigned char recieve;


};

} /* namespace address */

#endif /* POKEY_H_ */
