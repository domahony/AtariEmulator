/*
 * BCC.h
 *
 *  Created on: May 28, 2015
 *      Author: domahony
 */

#ifndef BCC_H_
#define BCC_H_

#include "OpCode.h"

namespace cpu {

class BCC : public OpCode {
public:
	BCC() {};
	virtual ~BCC() {};
	virtual int operator()(CPU*);
	std::string mnemonic() {
		return "BCC";
	}
};

class BCS : public OpCode {
public:
	BCS() {};
	virtual ~BCS() {};
	virtual int operator()(CPU*);
	std::string mnemonic() {
		return "BCS";
	}
};

class BEQ : public OpCode {
public:
	BEQ() {};
	virtual ~BEQ() {};
	virtual int operator()(CPU*);
	std::string mnemonic() {
		return "BEQ";
	}
};

class BMI : public OpCode {
public:
	BMI() {};
	virtual ~BMI() {};
	virtual int operator()(CPU*);
	std::string mnemonic() {
		return "BMI";
	}
};

class BNE : public OpCode {
public:
	BNE() {};
	virtual ~BNE() {};
	virtual int operator()(CPU*);
	std::string mnemonic() {
		return "BNE";
	}
};

class BPL : public OpCode {
public:
	BPL() {};
	virtual ~BPL() {};
	virtual int operator()(CPU*);
	std::string mnemonic() {
		return "BPL";
	}
};

class BVC : public OpCode {
public:
	BVC() {};
	virtual ~BVC() {};
	virtual int operator()(CPU*);
	std::string mnemonic() {
		return "BVC";
	}
};

class BVS : public OpCode {
public:
	BVS() {};
	virtual ~BVS() {};
	virtual int operator()(CPU*);
	std::string mnemonic() {
		return "BVS";
	}

};

} /* namespace cpu */

#endif /* BCC_H_ */
