#include "resource.h"

const char* getStatusString(Status status)
{
    switch(status)
    {
        case 0: return "Created";
        case 1: return "InProgress";
        case 2: return "Completed";
    }

    return "Unknown";
}

