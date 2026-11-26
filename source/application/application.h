#if !defined(FRM_APPLICATION_H)
#define FRM_APPLICATION_H

#include <core/core.h>
#include <scene/scene.h>

typedef struct frm_state_t frm_state_t;
struct frm_state_t {

    uint32_t        window_width,                   // @note use -wr/--window-resolution <width> <height> to change.
                    window_height;
    float           sensitivity,                    // @note use -se/--sensitivity <value> to change.
                    field_of_view;                  // @note use -f/--fov <value> to change.
    frm_scene_t*    current_scene;                  // @note use -sc/--scene <path> to load scene file ".sdfs"
    uint16_t        render_width,                   // @note use -rr/--render-resolution <width> <height> to change.
                    render_height,
                    max_step_count;                 // @note use -msc/--max-step-count <count> to change.
    bool            show_fps;                       // @note use -fps the show fps
    cwindow_t       window_handle;

};
#define empty_frm_state_t                           (frm_state_t) {0}

int32_t             frm_start_from_args             (err_t* err, int32_t argc, const char** argv, frm_state_t* out);
void                frm_stop                        (err_t* err, frm_state_t* state);

#endif // FRM_APPLICATION_H