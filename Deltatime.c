#include <stdio.h>
#include <stdlib.h>
#include <SFML/System.h>
#include "Deltatime.h"

sfClock* deltaclock;

void InitDelta() {
    deltaclock = sfClock_create();
}

void DeltaTime() {
    sfTime dtime = sfClock_getElapsedTime(deltaclock);
    delta = sfTime_asMilliseconds(dtime);
    sfClock_restart(deltaclock);
}