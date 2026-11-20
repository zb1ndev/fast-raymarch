#include <core/core.h>

// @todo we need to read arguments, load scene data from files (later), generate BVHs, package UBOs and dispatch compute shaders
// @note TARGET FRAME RATE: 30fps with a complex scene

int32_t main(int32_t argc, const char** argv) {

    err_t err           = CORE_SUCCESS;
    cwindow_t handle    = CORE_CWINDOW_INVALID;
    
    int window_width    = 1920,                                         // @todo these are defaults, use -r/--resolution <width> <height> to change.
        window_height   = 1080;

    float sensitivity   = 200.0f,                                       // @todo this is a default value, use -s/--sensitivity <value> to change.
          field_of_view = 90.0f;                                        // @todo this is a default value, use -f/--fov <value> to change.

    ccatch(&err, handle = cwindow_create(&err, "fast-raymarch", (ivec2){ window_width, window_height }), 
        goto l_exit;
    );

    ccatch(&err, (void)cgraf_opengl_hook(&err, handle), 
        goto l_exit;
    );

    while (!cwindow_get_closed(&err, handle)) {

        if (cinput_get_key(&err, CORE_KEYCODE_ESC) || err != CORE_SUCCESS)
            cwindow_close(&err, handle);
        cwindow_update(&err);

    }

l_exit:

    cwindow_destroy(&err, handle);
    return err != CORE_SUCCESS 
        ? EXIT_FAILURE 
        : EXIT_SUCCESS;

}