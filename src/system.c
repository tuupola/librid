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

    if (type > RID_OPERATOR_LOCATION_TYPE_MAX) {
        return RID_ERROR_OUT_OF_RANGE;
    }

    system->operator_location_type = (uint8_t)type;

    return RID_SUCCESS;
}

rid_operator_location_type_t
rid_get_operator_location_type(const rid_system_t *system) {
    return (rid_operator_location_type_t)system->operator_location_type;
}

rid_error_t
rid_set_classification_type(rid_system_t *system, rid_classification_type_t type) {
    if (system == NULL) {
        return RID_ERROR_NULL_POINTER;
    }

    if (type > RID_CLASSIFICATION_TYPE_MAX) {
        return RID_ERROR_OUT_OF_RANGE;
    }

    system->classification_type = (uint8_t)type;

    return RID_SUCCESS;
}

rid_classification_type_t
rid_get_classification_type(const rid_system_t *system) {
    return (rid_classification_type_t)system->classification_type;
}

rid_error_t
rid_set_ua_classification_category(rid_system_t *system, rid_ua_classification_category_t category) {
    if (system == NULL) {
        return RID_ERROR_NULL_POINTER;
    }

    if (category > RID_UA_CLASSIFICATION_CATEGORY_MAX) {
        return RID_ERROR_OUT_OF_RANGE;
    }

    system->ua_classification_category = (uint8_t)category;

    return RID_SUCCESS;
}

rid_ua_classification_category_t
rid_get_ua_classification_category(const rid_system_t *system) {
    return (rid_ua_classification_category_t)system->ua_classification_category;
}

rid_error_t
rid_set_ua_classification_class(rid_system_t *system, rid_ua_classification_class_t class) {
    if (system == NULL) {
        return RID_ERROR_NULL_POINTER;
    }

    if (class > RID_UA_CLASSIFICATION_CLASS_MAX) {
        return RID_ERROR_OUT_OF_RANGE;
    }

    system->ua_classification_class = (uint8_t)class;

    return RID_SUCCESS;
}

rid_ua_classification_class_t
rid_get_ua_classification_class(const rid_system_t *system) {
    return (rid_ua_classification_class_t)system->ua_classification_class;
}
