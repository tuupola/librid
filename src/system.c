#include <stddef.h>
#include <stdint.h>
#include <string.h>

#include "rid/header.h"
#include "rid/system.h"

rid_error_t
rid_set_operator_location_type(rid_system_t *system, rid_operator_location_type_t type) {
    if (system == NULL) {
        return RID_ERROR_NULL_POINTER;
    }

    if (type > RID_OPERATOR_LOCATION_TYPE_RESERVED) {
        return RID_ERROR_OUT_OF_RANGE;
    }

    system->operator_location_type = (uint8_t)type;

    return RID_SUCCESS;
}

rid_operator_location_type_t
rid_get_operator_location_type(const rid_system_t *system) {
    return (rid_operator_location_type_t)system->operator_location_type;
}
