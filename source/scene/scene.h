#if !defined(FRM_SCENE_H)
#define FRM_SCENE_H

#include <core/core.h>

typedef struct frm_object_t frm_object_t;
struct frm_object_t {

    vec3            position,
                    scale;
    uint16_t        flags;
    uint16_t        material_id;

    #define FRM_SDF_PRIMITIVE_SPHERE                (1<<0) // @note magnitude of scale is radius
    #define FRM_SDF_PRIMITIVE_CUBE                  (1<<1)

    #define FRM_SDF_BOOL_NEGATIVE                   (1<<2)

};
#define empty_frm_object_t                          (frm_object_t) {0}

typedef struct frm_scene_t frm_scene_t;
struct frm_scene_t {

    frm_object_t*   objects;
    uint32_t        object_count,
                    object_capacity;

    // @todo sdf functions should also be able to be loaded by file

};
#define empty_frm_scene_t                           (frm_scene_t) {0}

int32_t             frm_scene_load_from_file        (const char* file_name, frm_scene_t* out);
void                frm_scene_unload                (frm_scene_t* scene);

#endif // FRM_SCENE_H