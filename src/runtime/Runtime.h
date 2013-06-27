/*
 * Runtime.h
 *
 *  Created on: 2013. 6. 27.
 *      Author: gubee
 */

#ifndef RUNTIME_H_
#define RUNTIME_H_

class Runtime {
public:
    Runtime();
    ~Runtime();

    void startup();
    void shutdown();

private:
    struct Data;
    Data* m_data;
};

#endif /* RUNTIME_H_ */
