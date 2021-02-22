#ifndef TRAIN_H
#define TRAIN_H

#include "../project.h"

#include "../network/network.h"
#include "../lx/lx.h"


bool train(network *w, double scale, double stochastic, EXAMPLES_COUNT sample_size, lx *x, double *avg_error); 

#endif
