//
// Created by Œ‚÷æ±Û on 2018/4/25.
//


#include <uv.h>
#include <stdio.h>
#include <stdlib.h>

void open_cb(uv_fs_t* req);
void read_cb(uv_fs_t* req);

uv_fs_t open_req;
uv_fs_t read_req;
uv_fs_t close_req;

uv_buf_t iov;
char buf[1024];

void open_cb(uv_fs_t* req) {
    if (req->result < 0) {
        printf("%s\n", uv_err_name(req->result));
        uv_fs_req_cleanup(req);
        return;
    }
    uv_file fd = req->result;
    printf ("open file: %s\n", req->path);
    iov = uv_buf_init(buf, sizeof(buf));
    uv_fs_read(req->loop, &read_req, fd, &iov, 1, -1, read_cb);
    uv_fs_req_cleanup(req);
}

void read_cb(uv_fs_t* req) {
    printf("in read cb\n");
    if (req->result < 0) {
        printf("%s\n", uv_err_name(req->result));
        uv_fs_req_cleanup(req);
        return;
    } else if (req->result == 0) {
        printf("empty file\n");
        uv_fs_close(req->loop, &close_req, req->result, NULL);
        uv_fs_req_cleanup(&close_req);
        uv_fs_req_cleanup(req);
    } else {
        printf("read:%s", buf);
        uv_fs_req_cleanup(req);
    }
}

int main() {
    printf("file\n");
    uv_loop_t* loop = (uv_loop_t*)malloc(sizeof(uv_loop_t));
    uv_loop_init(loop);

    char file_path[] = "/Users/wuzhibin/dragon/abox/hello.txt";

    uv_fs_open(loop, &open_req, file_path, O_RDONLY, S_IRUSR, open_cb);

    uv_run(loop, UV_RUN_DEFAULT);
    uv_loop_close(loop);
    free(loop);
    return 0;
}
