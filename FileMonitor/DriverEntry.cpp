#include "Filter.h"

extern "C"
NTSTATUS
DriverEntry(
    _In_ PDRIVER_OBJECT DriverObject,
    _In_ PUNICODE_STRING RegistryPath
)
{
    UNREFERENCED_PARAMETER(RegistryPath);

    NTSTATUS status = FltRegisterFilter(DriverObject, &FilterRegistration, &FilterHandle);
    if (NT_SUCCESS(status)) {
        status = FltStartFiltering(FilterHandle);
        if (!NT_SUCCESS(status)) {
            FltUnregisterFilter(FilterHandle);
        }
    }

    DbgPrint("FileMonitor: Driver loaded\n");
    return status;
}
