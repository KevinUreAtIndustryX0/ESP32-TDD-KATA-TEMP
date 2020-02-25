#include <stdio.h>
#include "CmakeConfig.h"
#include "appController.h"

void app_main(void)
{
    char buffer[55];
    printf("Hello World (%s) (%s)\n", hello_world_GitTag, hello_world_buildDate(buffer));

    init();

    mainLoop();
}
