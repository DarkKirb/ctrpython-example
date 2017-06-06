#include <Python.h>
#undef socklen_t
#include <3ds.h>
static PyObject * svc_control_memory(PyObject *self, PyObject *args) {
    uint32_t addr_out, addr0, addr1, size;
    MemOp op;
    MemPerm perm;

    if(!PyArg_ParseTuple(args, "IIIII", &addr0, &addr1, &size, &op, &perm))
        return NULL;
    Result res = svcControlMemory(&addr_out, addr0, addr1, size, op, perm);

    return Py_BuildValue("(iI)", res, addr_out);
}

static PyObject * svc_control_process_memory(PyObject *self, PyObject *args) {
    Handle process;
    uint32_t addr0, addr1, size, type, perm;

    if(!PyArg_ParseTuple(args, "IIIIII", &process, &addr0, &addr1, &size, &type, &perm))
        return NULL;
    Result res = svcControlProcessMemory(process, addr0, addr1, size, type, perm);

    return Py_BuildValue("i", res);
}

static PyObject * svc_create_memory_block(PyObject *self, PyObject *args) {
    Handle memblock;
    uint32_t addr, size;
    MemPerm my_perm, other_perm;

    if(!PyArg_ParseTuple(args, "IIII", &addr, &size, &my_perm, &other_perm))
        return NULL;
    Result res = svcCreateMemoryBlock(&memblock, addr, size, my_perm, other_perm);

    return Py_BuildValue("iI", res, memblock);
}

static PyObject * svc_map_memory_block(PyObject *self, PyObject *args) {
    Handle memblock;
    uint32_t addr;
    MemPerm my_perm, other_perm;

    if(!PyArg_ParseTuple(args, "IIII", &memblock, &addr, &my_perm, &other_perm))
        return NULL;
    Result res = svcMapMemoryBlock(memblock, addr, my_perm, other_perm);

    return Py_BuildValue("i", res);
}

static PyObject * svc_map_process_memory(PyObject *self, PyObject *args) {
    Handle process;
    uint32_t destAddress, size;

    if(!PyArg_ParseTuple(args, "III", &process, &destAddress, &size))
        return NULL;
    Result res = svcMapProcessMemory(process, destAddress, size);

    return Py_BuildValue("i", res);
}

static PyObject * svc_unmap_process_memory(PyObject *self, PyObject *args) {
    Handle process;
    uint32_t destAddress, size;

    if(!PyArg_ParseTuple(args, "III", &process, &destAddress, &size))
        return NULL;
    Result res = svcUnmapProcessMemory(process, destAddress, size);

    return Py_BuildValue("i", res);
}

static PyObject * svc_unmap_memory_block(PyObject *self, PyObject *args) {
    Handle process;
    uint32_t addr;

    if(!PyArg_ParseTuple(args, "II", &process, &addr))
        return NULL;
    Result res = svcUnmapMemoryBlock(process, addr);

    return Py_BuildValue("i", res);
}

static PyObject * svc_start_inter_process_dma(PyObject *self, PyObject *args) {
    Handle dma, dstProcess;
    void *dst;
    Handle srcProcess;
    void *src;
    uint32_t size;
    void *dmaConfig;

    if(!PyArg_ParseTuple(args, "IIIIII", &dstProcess, &dst, &srcProcess, &src, &size, &dmaConfig))
        return NULL;
    Result res = svcStartInterProcessDma(&dma, dstProcess, dst, srcProcess, src, size, dmaConfig);

    return Py_BuildValue("(iI)", res, dma);
}

static PyObject * svc_stop_dma(PyObject *self, PyObject *args) {
    Handle dma;

    if(!PyArg_ParseTuple(args, "I", &dma))
        return NULL;
    Result res = svcStopDma(dma);

    return Py_BuildValue("i", res);
}

static PyObject * svc_query_memory(PyObject *self, PyObject *args) {
    MemInfo info;
    PageInfo out;
    uint32_t addr;

    if(!PyArg_ParseTuple(args, "I", &addr))
        return NULL;
    Result res = svcQueryMemory(&info, &out, addr);

    return Py_BuildValue("(i(IIII)I)", res, info.base_addr, info.size, info.perm, info.state, out.flags);
}

static PyObject * svc_query_process_memory(PyObject *self, PyObject *args) {
    MemInfo info;
    PageInfo out;
    Handle process;
    uint32_t size;

    if(!PyArg_ParseTuple(args, "II", &process, &size))
        return NULL;
    Result res = svcQueryProcessMemory(&info, &out, process, size);

    return Py_BuildValue("(i(IIII)I)", res, info.base_addr, info.size, info.perm, info.state, out.flags);
}

static PyObject * svc_invalidate_process_data_cache(PyObject *self, PyObject *args) {
    Handle process;
    void *addr;
    uint32_t size;

    if(!PyArg_ParseTuple(args, "III", &process, &addr, &size))
        return NULL;
    Result res = svcInvalidateProcessDataCache(process, addr, size);

    return Py_BuildValue("i", res);
}

static PyObject * svc_store_process_data_cache(PyObject *self, PyObject *args) {
    Handle process;
    void *addr;
    uint32_t size;

    if(!PyArg_ParseTuple(args, "III", &process, &addr, &size))
        return NULL;
    Result res = svcStoreProcessDataCache(process, addr, size);

    return Py_BuildValue("i", res);
}

static PyObject * svc_flush_process_data_cache(PyObject *self, PyObject *args) {
    Handle process;
    void *addr;
    uint32_t size;

    if(!PyArg_ParseTuple(args, "III", &process, &addr, &size))
        return NULL;
    Result res = svcFlushProcessDataCache(process, addr, size);

    return Py_BuildValue("i", res);
}

static PyObject * svc_open_process(PyObject *self, PyObject *args) {
    Handle process;
    uint32_t processID;

    if(!PyArg_ParseTuple(args, "I", &processID))
        return NULL;

    Result res = svcOpenProcess(&process, processID);

    return Py_BuildValue("(iI)", res, process);
}

static PyObject * svc_exit_process(PyObject *self, PyObject *args) {
    Py_Finalize();
    svcExitProcess();
}

static PyObject * svc_terminate_process(PyObject *self, PyObject *args) {
    Handle process;

    if(!PyArg_ParseTuple(args, "I", &process))
        return NULL;
    Result res = svcTerminateProcess(process);

    return Py_BuildValue("i", process);
}

static PyObject * svc_get_process_id(PyObject *self, PyObject *args) {
    uint32_t out;
    Handle handle;

    if(!PyArg_ParseTuple(args, "I", &handle))
        return NULL;
    Result res = svcGetProcessId(&out, handle);

    return Py_BuildValue("(iI)", res, out);
}

static PyObject * svc_get_process_list(PyObject *self, PyObject *args) {
    int32_t processCount;
    uint32_t *processIds = malloc(257*sizeof(int)); //Shouldn't be larger than this.
    Result res = svcGetProcessList(&processCount, processIds, 256);
    PyObject *pidlist = PyList_New(0);

    for(int i=0;i<(processCount>256)?256:processCount; i++) {
        PyObject * pid = PyLong_FromLong(processIds[i]);
        PyList_Append(pidlist, pid);
        Py_DECREF(pid);
    }
    free(processIds);

    PyObject *r = Py_BuildValue("(iO)", res, pidlist);
    Py_DECREF(pidlist);
    return r;
}
static PyObject * svc_get_thread_list(PyObject *self, PyObject *args) {
    int32_t threadCount;
    uint32_t *threadIds = malloc(257*sizeof(int));
    Handle process;

    if(!PyArg_ParseTuple(args, "I", &process)) {
        free(threadIds);
        return NULL;
    }
    Result res = svcGetThreadList(&threadCount, threadIds, 256, process);
    PyObject *tidlist = PyList_New(0);

    for(int i=0;i<(threadCount>256)?256:threadCount; i++) {
        PyObject *tid = PyLong_FromLong(threadIds[i]);
        PyList_Append(tidlist, tid);
        Py_DECREF(tid);
    }
    free(threadIds);

    PyObject *r = Py_BuildValue("(iO)", res, tidlist);
    Py_DECREF(tidlist);
    return r;
}

static PyObject * svc_create_port(PyObject *self, PyObject *args) {
    Handle portServer, portClient;
    char* name;
    int maxSessions;

    if(!PyArg_ParseTuple(args, "si", &name, &maxSessions))
        return NULL;
    Result res = svcCreatePort(&portServer, &portClient, name, maxSessions);

    return Py_BuildValue("(iII)", res, portServer, portClient);
}

static PyObject * svc_connect_to_port(PyObject *self, PyObject *args) {
    Handle out;
    char* name;

    if(!PyArg_ParseTuple(args, "s", &name))
        return NULL;
    Result res = svcConnectToPort(&out, name);

    return Py_BuildValue("(iI)", res, out);
}

static PyObject * svc_create_code_set(PyObject *self, PyObject *args) {
    Handle out;
    CodeSetInfo info;
    void *code_ptr;
    void *ro_ptr;
    void *data_ptr;
    char *name;

    if(!PyArg_ParseTuple(args, "sIIIIIIIIIKIII", &name, &(info.text_addr), &(info.text_size), &(info.ro_addr), &(info.ro_size), &(info.rw_addr), &(info.rw_size), &(info.text_size_total), &(info.ro_size_total), &(info.rw_size_total), &(info.program_id), &code_ptr, &ro_ptr, &data_ptr))
        return NULL;
    memcpy(&(info.name), name, 8);
    Result res = svcCreateCodeSet(&out, &info, code_ptr, ro_ptr, data_ptr);

    return Py_BuildValue("(iI)", res, out);
}

static PyObject * svc_create_process(PyObject *self, PyObject *args) {
    Handle out;
    Handle codeset;
    uint32_t *arm11kernelcaps;
    uint32_t arm11kernelcaps_num;
    PyObject *caplist;

    if(!PyArg_ParseTuple(args, "IO!", &codeset, PyList_Type, &caplist))
        return NULL;
    arm11kernelcaps_num=PyList_Size(caplist);
    arm11kernelcaps=malloc(arm11kernelcaps_num*sizeof(int));
    for(uint32_t i=0;i<arm11kernelcaps_num;i++) {
        PyObject *j = PyList_GetItem(caplist, i);
        arm11kernelcaps[i] = (int)(PyLong_AsLong(j));
        Py_DECREF(j);
    }
    Result res = svcCreateProcess(&out, codeset, arm11kernelcaps, arm11kernelcaps_num);
    free(arm11kernelcaps);
    return Py_BuildValue("(iI)", res, out);
}
/*
static PyObject * svc_get_process_affinity_mask(PyObject *self, PyObject *args) {
    uint8_t out;
    Handle process;
    int processorcount;

    if(!PyArg_ParseTuple(args, "Ii", &process, &processorcount))
        return NULL;
    Result res = svcGetProcessAffinityMask(&out, process, processorcount);

    return Py_BuildValue("(iB)", res, out);
}
*/
static PyObject * svc_get_process_ideal_processor(PyObject *self, PyObject *args) {
    int32_t processorid;
    Handle process;

    if(!PyArg_ParseTuple(args, "I", &process))
        return NULL;
    Result res = svcGetProcessIdealProcessor(&processorid, process);

    return Py_BuildValue("(iI)", res, processorid);
}

static PyObject * svc_set_process_ideal_processor(PyObject *self, PyObject *args) {
    int processorid;
    Handle process;

    if(!PyArg_ParseTuple(args, "II", &process, &processorid))
        return NULL;
    Result res = svcSetProcessIdealProcessor(process, processorid);

    return Py_BuildValue("i", res);
}

static PyObject * svc_run(PyObject *self, PyObject *args) {
    Handle process;
    StartupInfo info;

    if(!PyArg_ParseTuple(args, "III", &process, &(info.priority), &(info.stack_size)))
        return NULL;
    Result res = svcRun(process, &info);

    return Py_BuildValue("i", res);
}
// TODO threading is not supported – add here

static PyObject * svc_get_processor_id(PyObject *self, PyObject *args) {
    return Py_BuildValue("i", svcGetProcessorID());
}

//TODO svcGetResourceLimit *

//TODO synchronization

static PyObject * svc_create_timer(PyObject *self, PyObject *args) {
    Handle timer;
    ResetType reset_type;

    if(!PyArg_ParseTuple(args, "I", &reset_type))
        return NULL;
    Result res = svcCreateTimer(&timer, reset_type);

    return Py_BuildValue("(iI)", res, timer);
}

static PyObject * svc_set_timer(PyObject *self, PyObject *args) {
    Handle timer;
    int64_t initial;
    int64_t interval;

    if(!PyArg_ParseTuple(args, "ILL", &timer, &initial, &interval))
        return NULL;
    Result res = svcSetTimer(timer, initial, interval);

    return Py_BuildValue("i", res);
}

static PyObject * svc_cancel_timer(PyObject *self, PyObject *args) {
    Handle timer;

    if(!PyArg_ParseTuple(args, "I", &timer))
        return NULL;
    Result res = svcCancelTimer(timer);

    return Py_BuildValue("i", res);
}

static PyObject * svc_clear_timer(PyObject *self, PyObject *args) {
    Handle timer;

    if(!PyArg_ParseTuple(args, "I", &timer))
        return NULL;
    Result res = svcClearTimer(timer);

    return Py_BuildValue("i", res);
}

static PyObject * svc_get_system_tick(PyObject *self, PyObject *args) {
    return PyLong_FromUnsignedLong(svcGetSystemTick());
}

static PyObject * svc_close_handle(PyObject *self, PyObject *args) {
    Handle handle;

    if(!PyArg_ParseTuple(args, "I", &handle))
        return NULL;
    Result res = svcCloseHandle(handle);

    return Py_BuildValue("i", res);
}

static PyObject * svc_duplicate_handle(PyObject *self, PyObject *args) {
    Handle out;
    Handle in;

    if(!PyArg_ParseTuple(args, "I", &in))
        return NULL;
    Result res = svcDuplicateHandle(&out, in);

    return Py_BuildValue("(iI)", res, out);
}

static PyObject * svc_break(PyObject *self, PyObject *args) {
    UserBreakType reason;

    if(!PyArg_ParseTuple(args, "I", &reason))
        return NULL;
    svcBreak(reason);
    Py_RETURN_NONE;
}
static PyMethodDef SVCMethods[] = {
    {"control_memory", svc_control_memory, METH_VARARGS, ""},
    {"control_process_memory", svc_control_process_memory, METH_VARARGS, ""},
    {"create_memory_block", svc_create_memory_block, METH_VARARGS, ""},
    {"map_memory_block", svc_map_memory_block, METH_VARARGS, ""},
    {"map_process_memory", svc_map_process_memory, METH_VARARGS, ""},
    {"unmap_process_memory", svc_unmap_process_memory, METH_VARARGS, ""},
    {"unmap_memory_block", svc_unmap_memory_block, METH_VARARGS, ""},
    {"start_inter_process_dma", svc_start_inter_process_dma, METH_VARARGS, ""},
    {"stop_dma", svc_stop_dma, METH_VARARGS, ""},
    {"query_memory", svc_query_memory, METH_VARARGS, ""},
    {"query_process_memory", svc_query_process_memory, METH_VARARGS, ""},
    {"invalidate_process_data_cache", svc_invalidate_process_data_cache, METH_VARARGS, ""},
    {"store_process_data_cache", svc_store_process_data_cache, METH_VARARGS, ""},
    {"flush_process_data_cache", svc_flush_process_data_cache, METH_VARARGS, ""},
    {"open_process", svc_open_process, METH_VARARGS, ""},
    {"exit_process", svc_exit_process, METH_VARARGS, ""},
    {"terminate_process", svc_terminate_process, METH_VARARGS, ""},
    {"get_process_id", svc_get_process_id, METH_VARARGS, ""},
    {"get_process_list", svc_get_process_list, METH_VARARGS, ""},
    {"get_thread_list", svc_get_thread_list, METH_VARARGS, ""},
    {"create_port", svc_create_port, METH_VARARGS, ""},
    {"connect_to_port", svc_connect_to_port, METH_VARARGS, ""},
    {"create_code_set", svc_create_code_set, METH_VARARGS, ""},
    {"create_process", svc_create_process, METH_VARARGS, ""},
    {"get_process_ideal_processor", svc_get_process_ideal_processor, METH_VARARGS, ""},
    {"set_process_ideal_processor", svc_set_process_ideal_processor, METH_VARARGS, ""},
    {"run", svc_run, METH_VARARGS, ""},
    {"get_processor_id", svc_get_processor_id, METH_VARARGS, ""},
    {"create_timer", svc_create_timer, METH_VARARGS, ""},
    {"set_timer", svc_set_timer, METH_VARARGS, ""},
    {"cancel_timer", svc_cancel_timer, METH_VARARGS, ""},
    {"clear_timer", svc_clear_timer, METH_VARARGS, ""},
    {"get_system_tick", svc_get_system_tick, METH_VARARGS, ""},
    {"close_handle", svc_close_handle, METH_VARARGS, ""},
    {"duplicate_handle", svc_duplicate_handle, METH_VARARGS, ""},
    {"_break", svc_break, METH_VARARGS, ""},
    {NULL, NULL, NULL, NULL}
};
static PyModuleDef svcmodule = {
    PyModuleDef_HEAD_INIT,
    "svc",
    NULL,
    -1,
    SVCMethods
};
PyMODINIT_FUNC
PyInit_svc() {
    PyObject *m;
    m=PyModule_Create(&svcmodule);
    if(m==NULL)
        return m;
    return m;
}


