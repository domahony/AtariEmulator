/*
 * BCC.h
 *
 *  Created on: May 28, 2015
 *      Author: domahony
 */

#ifndef BCC_H_
#define BCC_H_

#include "OpCode.h"
#include <sstream>

namespace cpu {

class BranchOp : public OpCode {
public:
	BranchOp() : addr(0), bit(0), offset(0), flags(0) {}
	virtual ~BranchOp();

	virtual std::string _mnemonic() = 0;

	std::string mnemonic() {
		std::stringstream ret;
		ret << _mnemonic() << " " << (bit ? "1":"0") << " " << std::hex << offset << " " << offset + addr;
		return ret.str();
	}

protected:
	unsigned short addr;
	char offset;
	bool bit;
	unsigned char flags;

};

class BCC : public BranchOp {
public:
	BCC() {};
	virtual ~BCC() {};
	virtual int operator()(CPU*);
	std::string _mnemonic() {
		return "BCC C";
	}
};

class BCS : public BranchOp {
public:
	BCS() {};
	virtual ~BCS() {};
	virtual int operator()(CPU*);
	std::string _mnemonic() {
		return "BCS C";
	}
};

class BEQ : public BranchOp {
public:
	BEQ() {};
	virtual ~BEQ() {};
	virtual int operator()(CPU*);
	std::string _mnemonic() {
		return "BEQ Z";
	}
};

class BMI : public BranchOp {
public:
	BMI() {};
	virtual ~BMI() {};
	virtual int operator()(CPU*);
	std::string _mnemonic() {
		return "BMI N";
	}
};

class BNE : public BranchOp {
public:
	BNE() {};
	virtual ~BNE() {};
	virtual int operator()(CPU*);
	std::string _mnemonic() {
		return "BNE Z";
	}
private:
	std::string str;
};

class BPL : public BranchOp {
public:
	BPL() {};
	virtual ~BPL() {};
	virtual int operator()(CPU*);
	std::string _mnemonic() {
		return "BPL N";
	}
};

class BVC : public BranchOp {
public:
	BVC() {};
	virtual ~BVC() {};
	virtual int operator()(CPU*);
	std::string _mnemonic() {
		return "BVC V";
	}
};

class BVS : public BranchOp {
public:
	BVS() {};
	virtual ~BVS() {};
	virtual int operator()(CPU*);
	std::string _mnemonic() {
		return "BVS V";
	}

};

} /* namespace cpu */

#endif /* BCC_H_ */
