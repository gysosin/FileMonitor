#include "Filter.h"

PFLT_FILTER FilterHandle = NULL;

CONST FLT_OPERATION_REGISTRATION Callbacks[] = {
    { IRP_MJ_CREATE, 0, PreOperationCallback, nullptr },
    { IRP_MJ_READ, 0, PreOperationCallback, nullptr },
    { IRP_MJ_WRITE, 0, PreOperationCallback, nullptr },
    { IRP_MJ_SET_INFORMATION, 0, PreOperationCallback, nullptr },
    { IRP_MJ_OPERATION_END }
};

CONST FLT_REGISTRATION FilterRegistration = {
    sizeof(FLT_REGISTRATION),
    FLT_REGISTRATION_VERSION,
    0,
    nullptr,
    Callbacks,
    Unload,
    InstanceSetup,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    nullptr
};

NTSTATUS
Unload(
    _In_ FLT_FILTER_UNLOAD_FLAGS Flags
)
{
    UNREFERENCED_PARAMETER(Flags);
    FltUnregisterFilter(FilterHandle);
    DbgPrint("FileMonitor: Unloaded\n");
    return STATUS_SUCCESS;
}

NTSTATUS
InstanceSetup(
    _In_ PCFLT_RELATED_OBJECTS FltObjects,
    _In_ FLT_INSTANCE_SETUP_FLAGS Flags,
    _In_ DEVICE_TYPE VolumeDeviceType,
    _In_ FLT_FILESYSTEM_TYPE VolumeFilesystemType
)
{
    UNREFERENCED_PARAMETER(FltObjects);
    UNREFERENCED_PARAMETER(Flags);
    UNREFERENCED_PARAMETER(VolumeDeviceType);
    UNREFERENCED_PARAMETER(VolumeFilesystemType);
    return STATUS_SUCCESS;
}

FLT_PREOP_CALLBACK_STATUS
PreOperationCallback(
    _Inout_ PFLT_CALLBACK_DATA Data,
    _In_ PCFLT_RELATED_OBJECTS FltObjects,
    _Outptr_result_maybenull_ PVOID* CompletionContext
)
{
    UNREFERENCED_PARAMETER(CompletionContext);
    UNREFERENCED_PARAMETER(FltObjects);

    PFLT_FILE_NAME_INFORMATION nameInfo;

    if (NT_SUCCESS(FltGetFileNameInformation(Data, FLT_FILE_NAME_NORMALIZED | FLT_FILE_NAME_QUERY_DEFAULT, &nameInfo))) {
        FltParseFileNameInformation(nameInfo);
        DbgPrint("FileMonitor: Operation %u on %wZ\n", Data->Iopb->MajorFunction, &nameInfo->Name);
        FltReleaseFileNameInformation(nameInfo);
    }

    return FLT_PREOP_SUCCESS_NO_CALLBACK;
}
