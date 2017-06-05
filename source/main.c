#include <stdio.h>
char stack_top[0x100000];
#include <3ds.h>
#include <Python.h>
uint32_t old_sp;
void abort() {
    printf("Aborting\n");
    for(;;);
}
int main2() {
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
int main() {
    char *s=stack_top;
    uint32_t t=(uint32_t)(s)+0x100000;
    asm volatile("mov %0, sp" : "=r"(old_sp));
    asm volatile("mov sp, %0" ::"r"(t));
    main2();
    asm volatile("mov sp, %0":: "r"(old_sp));
}
