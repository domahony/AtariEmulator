/*
 * Executor.h
 *
 *  Created on: Oct 13, 2016
 *      Author: domahony
 */

#ifndef SRC_EXECUTOR_H_
#define SRC_EXECUTOR_H_

namespace process {

template <class T> struct Executor
{
	void execute() {
		process->execute();
	}

	T* process;
};

};


#endif /* SRC_EXECUTOR_H_ */
