#include <core/core.h>
#include <base/base.h>
#include <scene/scene.h>

int32_t main(int32_t argc, const char** argv) {

    err_t err           = CORE_SUCCESS;
    frm_state_t state   = empty_frm_state_t;
    if (frm_start_from_args(&err, argc, argv, &state) != EXIT_SUCCESS)
        goto l_exit;

    while (!cwindow_get_closed(&err, state.window_handle)) {

        if (cinput_get_key(&err, CORE_KEYCODE_ESC) || err != CORE_SUCCESS)
            cwindow_close(&err, state.window_handle);
        cwindow_update(&err);
    
    }

l_exit:

    ccatch(&err, frm_stop(&err, &state),
        return EXIT_FAILURE; 
    );  return EXIT_SUCCESS;

}