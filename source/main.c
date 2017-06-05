#include <stdio.h>
#include <3ds.h>
#include <Python.h>
uint32_t __stacksize__ = 0x100000;
void abort() {
    printf("Aborting\n");
    for(;;);
}
int main() {
    gfxInitDefault();
    consoleInit(GFX_TOP, NULL);
    int useSD=1;
    if(romfsInit()<0) {
        printf("Failed to initialize Python: Failed to mount romfs\n");
        return;
    }
    if(sdmcInit()<0)
        useSD=0;
    printf("Python output:\n");
    Py_FrozenFlag = 1;
    Py_NoSiteFlag = 1;
    Py_DebugFlag = 1;
    Py_Initialize();
    PyRun_SimpleString("import sys");
    PyRun_SimpleString("print('Initializing Python3.7')");
    if(useSD) {
        PyRun_SimpleString("sys.path.append('sdmc:/python.zip')");
        PyRun_SimpleString("sys.path.append('sdmc:/python')");
    }

    FILE *pyinit=fopen("romfs:/init.py","rb");
    PyRun_SimpleFile(pyinit, "romfs:/init.py");

    while(aptMainLoop()) {
        hidScanInput();
        if(hidKeysDown() & KEY_START) {
            break;
        }

        gfxFlushBuffers();
        gfxSwapBuffers();
        gspWaitForVBlank();
    }
    Py_Finalize();
    gfxExit();
    return 0;
}
