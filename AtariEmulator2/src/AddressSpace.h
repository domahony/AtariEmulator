/*
 * AddressSpace.h
 *
 *  Created on: Mar 4, 2015
 *      Author: domahony
 */

#ifndef ADDRESSSPACE_H_
#define ADDRESSSPACE_H_

#include <memory>
#include <vector>
#include "RAM.h"
#include "ROM.h"
#include "GTIA.h"
#include "Pokey.h"
#include "PIA.h"
#include "ANTIC.h"

namespace video {
	class Video;
}

namespace address {

class AddressSpace {

public:
	AddressSpace(video::Video*);

	unsigned char read(const unsigned short) const;
	void write(unsigned short, unsigned char);
	void tick() {
		antic->tick(this);
		pokey->tick();
	}

	virtual ~AddressSpace();

	std::shared_ptr<ANTIC> get_antic() const {
		return antic;
	}

	std::shared_ptr<Pokey> get_pokey() const {
		return pokey;
	}

	void dump_ram();

private:

	std::shared_ptr<RAM> ram;
	std::shared_ptr<RAM> ramB;
	std::shared_ptr<ROM> cartridgeB;
	std::shared_ptr<ROM> cartridgeA;
	std::shared_ptr<GTIA> gtia;
	std::shared_ptr<Pokey> pokey;
	std::shared_ptr<PIA> pia;
	std::shared_ptr<ANTIC> antic;
	std::shared_ptr<ROM> os;

};


} /* namespace cpu */

#endif /* ADDRESSSPACE_H_ */

