#include <uv.h>
#include <stdio.h>
#include <stdlib.h>


void wait_for_idle(uv_idle_t* idle) {
    static int ct = 0;
    printf ("idle --- \n");
    if (ct++ > 10) {
        printf ("idle now quit\n");
        uv_idle_stop(idle);
    }
}

int main() {

    uv_loop_t* loop = (uv_loop_t*)malloc(sizeof(uv_loop_t));
    uv_loop_init(loop);

    uv_idle_t idle;
    uv_idle_init(loop, &idle);

    int code = uv_idle_start(&idle, wait_for_idle);
    printf("first loop\ngood luck\n");
    uv_run(loop, UV_RUN_DEFAULT);
    printf("never happen\n");
    uv_loop_close(loop);
    free(loop);

    return 0;
}