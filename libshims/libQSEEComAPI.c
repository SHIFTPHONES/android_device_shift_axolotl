#include <dlfcn.h>
#include <stdbool.h>

void *handle;

struct QSEECom_handle {
    unsigned char *ion_sbuffer;
};

struct qseecom_app_info{
    bool is_secure_app_64bit;
    uint32_t required_sg_buffer_size;
    uint8_t reserved[64];
};

struct QSEECom_ion_fd_data {
    int32_t fd;
    uint32_t cmd_buf_offset;
};

struct QSEECom_ion_fd_info {
    struct QSEECom_ion_fd_data data[4];
};

enum QSEECom_command_id {
  QSEECOM_RPMB_RESERVED_COMMAND = 0x0E,
  QSEECOM_RPMB_PROVISION_KEY_COMMAND = 0x0F,
  QSEECOM_RPMB_ERASE_COMMAND = 0x10,
  QSEECOM_RPMB_CHECK_PROV_STATUS_COMMAND = 0x1B,
  QSEECOM_FSM_LTEOTA_REQ = 0x109,
  QSEECOM_FSM_LTEOTA_REQ_RSP = 0x110,
  QSEECOM_FSM_IKE_REQ = 0x203,
  QSEECOM_FSM_IKE_REQ_RSP = 0x204,
  QSEECOM_FSM_OEM_FUSE_WRITE_ROW = 0x301,
  QSEECOM_FSM_OEM_FUSE_READ_ROW = 0x302,
  QSEECOM_FSM_ENCFS_REQ = 0x403,
  QSEECOM_FSM_ENCFS_REQ_RSP = 0x404,
  QSEECOM_RPMB_MAX_COMMAND = 0xEFFFFFFF
};

typedef int (*QSEEComStartAppFunc)(struct QSEECom_handle **, const char *, const char *, uint32_t);
typedef int (*QSEEComShutdownAppFunc)(struct QSEECom_handle **);
typedef int (*QSEEComLoadExternalElfFunc)(struct QSEECom_handle **, const char *, const char *);
typedef int (*QSEEComUnloadExternalElfFunc)(struct QSEECom_handle **);
typedef int (*QSEEComRegisterListenerFunc)(struct QSEECom_handle **, uint32_t, uint32_t,uint32_t);
typedef int (*QSEEComUnregisterListenerFunc)(struct QSEECom_handle *);
typedef int (*QSEEComSendCmdFunc)(struct QSEECom_handle *, void *, uint32_t, void *, uint32_t);
typedef int (*QSEEComSendModifiedCmdFunc)(struct QSEECom_handle *, void *, uint32_t, void *, uint32_t, struct QSEECom_ion_fd_info *);
typedef int (*QSEEComReceiveReqFunc)(struct QSEECom_handle *, void *, uint32_t);
typedef int (*QSEEComSendRespFunc)(struct QSEECom_handle *, void *, uint32_t);
typedef int (*QSEEComSendModifiedRespFunc)(struct QSEECom_handle *, void *, uint32_t, struct QSEECom_ion_fd_info *);
typedef int (*QSEEComSetBandwidthFunc)(struct QSEECom_handle *, bool);
typedef int (*QSEEComLoadQueryFunc)(struct QSEECom_handle *, char *);

typedef int (*QSEEComScaleBusBandwidthFunc)(struct QSEECom_handle *, int);
typedef int (*QSEEComGetAppInfoFunc)(struct QSEECom_handle *, struct qseecom_app_info *);
typedef int (*QSEEComStartAppV2Func)(struct QSEECom_handle **, const char *, unsigned char *, uint32_t, uint32_t);

typedef int (*QSEEComSendServiceCmdFunc)(void *, uint32_t, void *, uint32_t, enum QSEECom_command_id);

int QSEECom_start_app(struct QSEECom_handle **clnt_handle, const char *path,
            const char *fname, uint32_t sb_size) {
    int result = -1;
    handle = dlopen("libQSEEComAPI_qcom.so", RTLD_NOW);
    if (handle != NULL) {
        QSEEComStartAppFunc function = (QSEEComStartAppFunc)dlsym(handle, "QSEECom_start_app");
        result = function(clnt_handle, path, fname , sb_size);
        if (result == 133) {
            result = 0;
        }
    }
    dlclose(handle);
    return result;
}

int QSEECom_shutdown_app(struct QSEECom_handle **clnt_handle) {
    int result = -1;
    handle = dlopen("libQSEEComAPI_qcom.so", RTLD_NOW);
    if (handle != NULL) {
        QSEEComShutdownAppFunc function = (QSEEComShutdownAppFunc)dlsym(handle, "QSEECom_shutdown_app");
        result = function(clnt_handle);
    }
    dlclose(handle);
    return result;
}

int QSEECom_load_external_elf(struct QSEECom_handle **clnt_handle, const char *path,
            const char *fname) {
    int result = -1;
    handle = dlopen("libQSEEComAPI_qcom.so", RTLD_NOW);
    if (handle != NULL) {
        QSEEComLoadExternalElfFunc function = (QSEEComLoadExternalElfFunc)dlsym(handle, "QSEECom_load_external_elf");
        result = function(clnt_handle, path, fname);
    }
    dlclose(handle);
    return result;
}

int QSEECom_unload_external_elf(struct QSEECom_handle **clnt_handle) {
    int result = -1;
    handle = dlopen("libQSEEComAPI_qcom.so", RTLD_NOW);
    if (handle != NULL) {
        QSEEComUnloadExternalElfFunc function = (QSEEComUnloadExternalElfFunc)dlsym(handle, "QSEECom_unload_external_elf");
        result = function(clnt_handle);
    }
    dlclose(handle);
    return result;
}

int QSEECom_register_listener(struct QSEECom_handle **clnt_handle,
            uint32_t lstnr_id, uint32_t sb_length, uint32_t flags) {
    int result = -1;
    handle = dlopen("libQSEEComAPI_qcom.so", RTLD_NOW);
    if (handle != NULL) {
        QSEEComRegisterListenerFunc function = (QSEEComRegisterListenerFunc)dlsym(handle, "QSEECom_register_listener");
        result = function(clnt_handle, lstnr_id, sb_length, flags);
    }
    dlclose(handle);
    return result;
}

int QSEECom_unregister_listener(struct QSEECom_handle *clnt_handle) {
    int result = -1;
    handle = dlopen("libQSEEComAPI_qcom.so", RTLD_NOW);
    if (handle != NULL) {
        QSEEComUnregisterListenerFunc function = (QSEEComUnregisterListenerFunc)dlsym(handle, "QSEECom_unregister_listener");
        result = function(clnt_handle);
    }
    dlclose(handle);
    return result;
}

int QSEECom_send_cmd(struct QSEECom_handle *clnt_handle, void *send_buf,
            uint32_t sbuf_len, void *rcv_buf, uint32_t rbuf_len) {
    int result = -1;
    handle = dlopen("libQSEEComAPI_qcom.so", RTLD_NOW);
    if (handle != NULL) {
        QSEEComSendCmdFunc function = (QSEEComSendCmdFunc)dlsym(handle, "QSEECom_send_cmd");
        result = function(clnt_handle, send_buf, sbuf_len, rcv_buf, rbuf_len);
    }
    dlclose(handle);
    return result;
}

int QSEECom_send_modified_cmd(struct QSEECom_handle *clnt_handle, void *send_buf,
            uint32_t sbuf_len, void *resp_buf, uint32_t rbuf_len,
            struct QSEECom_ion_fd_info  *ifd_data) {
    int result = -1;
    handle = dlopen("libQSEEComAPI_qcom.so", RTLD_NOW);
    if (handle != NULL) {
        QSEEComSendModifiedCmdFunc function = (QSEEComSendModifiedCmdFunc)dlsym(handle, "QSEECom_send_modified_cmd");
        result = function(clnt_handle, send_buf, sbuf_len, resp_buf, rbuf_len, ifd_data);
    }
    dlclose(handle);
    return result;
}

int QSEECom_send_modified_cmd_64(struct QSEECom_handle *clnt_handle, void *send_buf,
            uint32_t sbuf_len, void *resp_buf, uint32_t rbuf_len,
            struct QSEECom_ion_fd_info  *ifd_data) {
    int result = -1;
    handle = dlopen("libQSEEComAPI_qcom.so", RTLD_NOW);
    if (handle != NULL) {
        QSEEComSendModifiedCmdFunc function = (QSEEComSendModifiedCmdFunc)dlsym(handle, "QSEECom_send_modified_cmd_64");
        result = function(clnt_handle, send_buf, sbuf_len, resp_buf, rbuf_len, ifd_data);
    }
    dlclose(handle);
    return result;
}

int QSEECom_receive_req(struct QSEECom_handle *clnt_handle,
            void *buf, uint32_t len) {
    int result = -1;
    handle = dlopen("libQSEEComAPI_qcom.so", RTLD_NOW);
    if (handle != NULL) {
        QSEEComReceiveReqFunc function = (QSEEComReceiveReqFunc)dlsym(handle, "QSEECom_receive_req");
        result = function(clnt_handle, buf, len);
    }
    dlclose(handle);
    return result;
}

int QSEECom_send_resp(struct QSEECom_handle *clnt_handle,
            void *send_buf, uint32_t len) {
    int result = -1;
    handle = dlopen("libQSEEComAPI_qcom.so", RTLD_NOW);
    if (handle != NULL) {
        QSEEComSendRespFunc function = (QSEEComSendRespFunc)dlsym(handle, "QSEECom_send_resp");
        result = function(clnt_handle, send_buf, len);
    }
    dlclose(handle);
    return result;
}

int QSEECom_send_modified_resp(struct QSEECom_handle *clnt_handle,
            void *send_buf, uint32_t len, struct QSEECom_ion_fd_info  *ifd_data) {
    int result = -1;
    handle = dlopen("libQSEEComAPI_qcom.so", RTLD_NOW);
    if (handle != NULL) {
        QSEEComSendModifiedRespFunc function = (QSEEComSendModifiedRespFunc)dlsym(handle, "QSEECom_send_modified_resp");
        result = function(clnt_handle, send_buf, len, ifd_data);
    }
    dlclose(handle);
    return result;
}

int QSEECom_send_modified_resp_64(struct QSEECom_handle *clnt_handle,
            void *send_buf, uint32_t len, struct QSEECom_ion_fd_info  *ifd_data) {
    int result = -1;
    handle = dlopen("libQSEEComAPI_qcom.so", RTLD_NOW);
    if (handle != NULL) {
        QSEEComSendModifiedRespFunc function = (QSEEComSendModifiedRespFunc)dlsym(handle, "QSEECom_send_modified_resp_64");
        result = function(clnt_handle, send_buf, len, ifd_data);
    }
    dlclose(handle);
    return result;
}

int QSEECom_set_bandwidth(struct QSEECom_handle *clnt_handle, bool high) {
    int result = -1;
    handle = dlopen("libQSEEComAPI_qcom.so", RTLD_NOW);
    if (handle != NULL) {
        QSEEComSetBandwidthFunc function = (QSEEComSetBandwidthFunc)dlsym(handle, "QSEECom_set_bandwidth");
        result = function(clnt_handle, high);
    }
    dlclose(handle);
    return result;
}

int QSEECom_app_load_query(struct QSEECom_handle *clnt_handle, char *app_name) {
    int result = -1;
    handle = dlopen("libQSEEComAPI_qcom.so", RTLD_NOW);
    if (handle != NULL) {
        QSEEComLoadQueryFunc function = (QSEEComLoadQueryFunc)dlsym(handle, "QSEECom_app_load_query");
        result = function(clnt_handle, app_name);
    }
    dlclose(handle);
    return result;
}

int QSEECom_scale_bus_bandwidth(struct QSEECom_handle *clnt_handle, int mode) {
    int result = -1;
    handle = dlopen("libQSEEComAPI_qcom.so", RTLD_NOW);
    if (handle != NULL) {
        QSEEComScaleBusBandwidthFunc function = (QSEEComScaleBusBandwidthFunc)dlsym(handle, "QSEECom_scale_bus_bandwidth");
        result = function(clnt_handle, mode);
    }
    dlclose(handle);
    return result;
}

int QSEECom_get_app_info(struct QSEECom_handle *clnt_handle, struct qseecom_app_info* info) {
    int result = -1;
    handle = dlopen("libQSEEComAPI_qcom.so", RTLD_NOW);
    if (handle != NULL) {
        QSEEComGetAppInfoFunc function = (QSEEComGetAppInfoFunc)dlsym(handle, "QSEECom_get_app_info");
        result = function(clnt_handle, info);
    }
    dlclose(handle);
    return result;
}

int QSEECom_start_app_V2(struct QSEECom_handle **clnt_handle, const char *fname, unsigned char *trustlet, uint32_t tlen, uint32_t sb_length) {
    int result = -1;
    handle = dlopen("libQSEEComAPI_qcom.so", RTLD_NOW);
    if (handle != NULL) {
        QSEEComStartAppV2Func function = (QSEEComStartAppV2Func)dlsym(handle, "QSEECom_start_app_V2");
        result = function(clnt_handle, fname, trustlet , tlen, sb_length);
        if (result == 133) {
            result = 0;
        }
    }
    dlclose(handle);
    return result;
}

int QSEECom_send_service_cmd(void *send_buf, uint32_t sbuf_len, void *resp_buf,
        uint32_t rbuf_len, enum QSEECom_command_id cmd_id) {
    int result = -1;
    handle = dlopen("libQSEEComAPI_qcom.so", RTLD_NOW);
    if (handle != NULL) {
        QSEEComSendServiceCmdFunc function = (QSEEComSendServiceCmdFunc)dlsym(handle, "QSEECom_send_service_cmd");
        result = function(send_buf, sbuf_len, resp_buf , rbuf_len, cmd_id);
    }
    dlclose(handle);
    return result;
}

