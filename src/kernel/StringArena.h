/*
 * StringArena.h
 *
 *  Created on: 2013. 7. 18.
 *      Author: gubee
 */

#ifndef STRINGARENA_H_
#define STRINGARENA_H_

namespace internals {
    char* StringArena_new(int size);
    void StringArena_delete();
}

#endif /* STRINGARENA_H_ */
