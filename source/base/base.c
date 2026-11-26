#include <base/base.h>

#define FRM_HELP_STRING "fast-raymarching -- help:\n"\
                        "\t-h/--help                                    Prints Help Page\n"\
                        "\t-wr/--window-resolution <width> <height>     Sets the target window resolution\n"\
                        "\t-se/--sensitivity <value>                    Sets the mouse look sensitivity\n"\
                        "\t-f/--fov <value>                             Sets the camera field of view\n"\
                        "\t-sc/--scene <path>                           Sets the target scene to one stored in the '.frm' file located at <path>\n"\
                        "\t-rr/--render-resolution <width> <height>     Sets the target render resolution\n"\
                        "\t-msc/--max-step-count <value>                Sets the max number of raymarch steps\n"\
                        "\t-fps/--fps                                   Enables the stdout fps counter\n\n"\

typedef enum frm_arg_t frm_arg_t;
enum frm_arg_t {

    FRM_ARG_INVALID                 = 0,

    FRM_ARG_HELP,                   // @note Prints the help page
    FRM_ARG_WINDOW_RESOLUTION,      // @note Sets the target window resolution
    FRM_ARG_SENSITIVITY,            // @note Sets the mouse look sensitivity
    FRM_ARG_FOV,                    // @note Sets the camera field of view
    FRM_ARG_SCENE,                  // @note Sets the target scene to one stored in the '.frm' file located at <path>
    FRM_ARG_RENDER_RESOLUTION,      // @note Sets the target render resolution
    FRM_ARG_MAX_STEP_COUNT,         // @note Sets the max number of raymarch steps
    FRM_ARG_FPS,                    // @note Enables the stdout fps counter\n

    FRM_ARG_COUNT

};

internal const char* arg_type_strings[FRM_ARG_COUNT*2] = {
    
    "-h", "-wr", "-se", "-f", "-sc", "-rr", "-msc", "-fps", "--help", 
    "--window-resolution", "--sensitivity", "--fov", "--scene", 
    "--render-resolution", "--max-step-count", "--fps" 

};

internal frm_arg_t frm_get_arg_type(const char* arg, bool is_verbose) {

    for (frm_arg_t arg_i = FRM_ARG_INVALID; arg_i < FRM_ARG_COUNT; arg_i++)
        if (strcmp(arg, arg_type_strings[arg_i+(is_verbose?FRM_ARG_COUNT:0)]) == 0)
            return arg_i+1;
    return FRM_ARG_INVALID;

}

internal int32_t frm_parse_argument(int32_t current_arg, bool is_verbose, int32_t argc, const char** argv, frm_state_t* out) {
    
    // @note INTENTIONAL: consumes the invalid argument
    if (current_arg < 1 || argv == NULL || out == NULL) {
        cdbg_err("invalid arguments");
        return EXIT_FAILURE; 
    }

    frm_arg_t arg_type = frm_get_arg_type(argv[current_arg], is_verbose);    
    if (arg_type == FRM_ARG_INVALID) {
        cdbg_err("invalid arguments");
        return EXIT_FAILURE; 
    }

    switch (arg_type) {

        case FRM_ARG_HELP:
        
            printf(FRM_HELP_STRING);
            return 1;

        case FRM_ARG_WINDOW_RESOLUTION:
            
            if (current_arg + 3 > argc) {
                cdbg_err("invalid argument parameters\n\n"FRM_HELP_STRING);
                return EXIT_FAILURE; 
            }
            
            out->window_width   = atoi(argv[current_arg+1]), 
            out->window_height  = atoi(argv[current_arg+2]);
            cdbg_logf("window resolution: %u, %u", out->window_width, out->window_height);

            return 3;
    
        case FRM_ARG_SENSITIVITY:

            if (current_arg + 2 > argc) {
                cdbg_err("invalid argument parameters\n\n"FRM_HELP_STRING);
                return EXIT_FAILURE; 
            }
            
            out->sensitivity    = atof(argv[current_arg+1]);
            cdbg_logf("sensitivity: %u", out->sensitivity);

            return 2;

        case FRM_ARG_FOV:

            if (current_arg + 2 > argc) {
                cdbg_err("invalid argument parameters\n\n"FRM_HELP_STRING);
                return EXIT_FAILURE; 
            }

            out->field_of_view  = atof(argv[current_arg+1]);
            cdbg_logf("field of view: %u", out->field_of_view);

            return 2;

        case FRM_ARG_SCENE:

            if (current_arg + 2 > argc) {
                cdbg_err("invalid argument parameters\n\n"FRM_HELP_STRING);
                return EXIT_FAILURE; 
            }

            out->target_scene = argv[current_arg+1];
            cdbg_logf("scene: %s", out->target_scene);

            return 2;

        case FRM_ARG_RENDER_RESOLUTION:

            if (current_arg + 3 > argc) {
                cdbg_err("invalid argument parameters\n\n"FRM_HELP_STRING);
                return EXIT_FAILURE; 
            }

            out->render_width   = atoi(argv[current_arg+1]), 
            out->render_height  = atoi(argv[current_arg+2]);
            cdbg_logf("render resolution: %u, %u", out->render_width, out->render_height);

            return 3;

        case FRM_ARG_MAX_STEP_COUNT:

            if (current_arg + 2 > argc) {
                cdbg_err("invalid argument parameters\n\n"FRM_HELP_STRING);
                return EXIT_FAILURE; 
            }

            out->max_step_count = (uint16_t)atoi(argv[current_arg+1]);
            cdbg_logf("max step count: %u", out->max_step_count);

            return 2;

        case FRM_ARG_FPS:

            out->show_fps = true;
            cdbg_log("show fps: enabled");
            return 1;

    }
    
}

int32_t frm_start_from_args(err_t* err, int32_t argc, const char** argv, frm_state_t* out) {

    if (argc <= 0 || argv == NULL || out == NULL) {
        cdbg_err("invalid arguments");
        return EXIT_FAILURE;
    }

    *out = (frm_state_t) {

        .window_width   = 1920,
        .window_height  = 1080,
        .sensitivity    = 200.0f,
        .field_of_view  = 90.0f,
        .target_scene   = NULL,
        .render_width   = 1280,
        .render_height  = 720,
        .max_step_count = 1000,
        .show_fps       = false,
        .window_handle  = CORE_CWINDOW_INVALID
        
    };

    int32_t current_argument = 1;
    while ((argc - current_argument) > 0) {

        size_t arg_length = strlen(argv[current_argument]);
        if (arg_length < 2 || argv[current_argument][0] != '-') {
            cdbg_errf("invalid argument at position: %ld", current_argument++);
            continue;
        }
        
        bool verbose = (argv[current_argument][1] == '-');
        current_argument += frm_parse_argument(current_argument, verbose, argc, argv, out);

    }

    ccatch(err, out->window_handle = cwindow_create (
        err, "fast-raymarch", 
        (ivec2){out->window_width, out->window_height}
    ), goto l_exit; );

    ccatch(err, (void)cgraf_opengl_hook(err, out->window_handle), goto l_exit; );

l_exit:

    return (*err) != CORE_SUCCESS 
        ? EXIT_FAILURE
        : EXIT_SUCCESS;

}

void frm_stop(err_t* err, frm_state_t* state) {

    cwindow_close(err, state->window_handle);

}

char* frm_open_and_read_file(const char* file_path, uint32_t* size_out) {

    FILE* file = fopen(file_path, "rb");
    if (file == NULL) {
        cdbg_errf("failed to open %s", file_path);
        return NULL;
    }

    struct stat fd_stat;
    int fd = fileno(file);
    if (fstat(fd, &fd_stat) < 0) {
        cdbg_errf("failed to get file size %s", file_path);
        fclose(file);
        return NULL;
    }

    *size_out = fd_stat.st_size;
    char* result = mmap(NULL, fd_stat.st_size, PROT_READ, MAP_PRIVATE, fd, 0);
    fclose(file);

    if (result == MAP_FAILED) {
        cdbg_err("failed to read shader file");
        return NULL;
    }

    return result;

}

void frm_close_file(char* data, uint32_t size) { munmap(data, size); }