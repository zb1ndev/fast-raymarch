#include <scene/scene.h>

int32_t frm_scene_load_from_file(const char* file_name, frm_scene_t* out) {

    if (out == NULL) {
        cdbg_err("invalid parameters");
        return EXIT_FAILURE;
    }

    if (file_name == SCENE_DEFAULT_SCENE_PATH) /* loads demo scene if no file is provided */ {

        #define INTERNAL_SDF_MATERIAL_GRID                       (0) // @note demo: use for floor
        #define INTERNAL_SDF_MATERIAL_OPAQUE                     (1) // @note demo: use for sphere 1
        #define INTERNAL_SDF_MATERIAL_MIRROR                     (2) // @note demo: use for sphere 2

        *out = (frm_scene_t) {
            .objects            = aligned_alloc(4, 2 * sizeof(frm_scene_t)),
            .object_count       = 2,
            .object_capacity    = 2
        };

        out->objects[0] = (frm_object_t) {
            .position = {-1.0f, 0.0f, 4.0f},
            .scale = {1.0f, 0.0f, 0.0f},
            .flags = FRM_SDF_PRIMITIVE_SPHERE,
            .material_id = INTERNAL_SDF_MATERIAL_OPAQUE
        };

        out->objects[2] = (frm_object_t) {
            .position = {1.0f, 0.0f, 4.0f},
            .scale = {1.0f, 0.0f, 0.0f},
            .flags = FRM_SDF_PRIMITIVE_SPHERE,
            .material_id = INTERNAL_SDF_MATERIAL_MIRROR
        };

        return EXIT_SUCCESS;

    }

    return EXIT_SUCCESS;

}

void frm_scene_unload(frm_scene_t* scene) {

    if (scene == NULL) {
        cdbg_err("invalid parameters");
        return;
    }

    scene->object_capacity  = 0;
    scene->object_count     = 0;
    
    if (scene->objects != NULL)    
        free(scene->objects);

}

