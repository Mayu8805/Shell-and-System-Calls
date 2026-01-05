/**
 * signalhandler.h
 *
 * Author: Igor Leeck
 * Course: CSCE 3600 - Systems Programming
 *
 * Description: Header file for signal handling functionality.
 * While this does define one function most of the functionality exists across the main and in
 * pipelining file because it is most convenient to handle it there
 */

#ifndef SIGNAL_HANDLER_H
#define SIGNAL_HANDLER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>

void ignore_signals();

#endif // !SIGNAL_HANDLER_H
