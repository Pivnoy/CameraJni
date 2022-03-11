#include <jni.h>
#include <string>
#include <iostream>

#include <camera/NdkCameraManager.h>
#include <camera/NdkCameraMetadata.h>
#include <camera/NdkCameraDevice.h>
#include <media/NdkImageReader.h>
#include <android/native_window_jni.h>


ACameraManager *cameraManager = nullptr;
ACameraDevice * cameraDev  = nullptr;

static ACameraOutputTarget* textureTarget = nullptr;

static ACaptureRequest* request = nullptr;

static ANativeWindow* textureWindow = nullptr;

static ACameraCaptureSession* textureSession = nullptr;

static ACaptureSessionOutput* textureOutput = nullptr;

#ifdef WITH_IMAGE_READER
static ANativeWindow* imageWindow = nullptr;

static ACameraOutputTarget* imageTarget = nullptr;

static AImageReader* imageReader = nullptr;

static ACaptureSessionOutput* imageOutput = nullptr;
#endif

static ACaptureSessionOutput* output = nullptr;

static ACaptureSessionOutputContainer* outputs = nullptr;



std::string getBackFacingCamId(ACameraManager *cameraManager)
{
    ACameraIdList *cameraIds = nullptr;
    ACameraManager_getCameraIdList(cameraManager, &cameraIds);

    std::string backId;

    for (int i = 0; i < cameraIds->numCameras; ++i)
    {
        const char *id = cameraIds->cameraIds[i];

        ACameraMetadata *metadataObj;
        ACameraManager_getCameraCharacteristics(cameraManager, id, &metadataObj);

        ACameraMetadata_const_entry lensInfo = {0};
        ACameraMetadata_getConstEntry(metadataObj, ACAMERA_LENS_FACING, &lensInfo);

        auto facing = static_cast<acamera_metadata_enum_android_lens_facing_t>(
                lensInfo.data.u8[0]);

        // Found a back-facing camera?
        if (facing == ACAMERA_LENS_FACING_BACK)
        {
            backId = id;
            break;
        }
    }

    ACameraManager_deleteCameraIdList(cameraIds);

    return backId;
}

extern "C" JNIEXPORT jstring JNICALL
Java_com_example_camerajni_MainActivity_stringFromJNI(
        JNIEnv* env,
        jobject /* this */) {
    std::string hello = "React Native syn sobaku";
    return env->NewStringUTF(hello.c_str());
}

static void onDisconnected(void* context, ACameraDevice* device)
{

}

static void onError(void* context, ACameraDevice* device, int error)
{

}

ACameraDevice_stateCallbacks cameraDeviceCallbacks = {
        .context = nullptr,
        .onDisconnected = onDisconnected,
        .onError = onError,
};

static camera_status_t initCam()
{
    cameraManager = ACameraManager_create();
    auto id = getBackFacingCamId(cameraManager);
    return ACameraManager_openCamera(cameraManager, id.c_str(), &cameraDeviceCallbacks, &cameraDev);
}

extern "C" JNIEXPORT jstring JNICALL
Java_com_example_camerajni_MainActivity_getCum(
        JNIEnv* env,
        jobject /* this */) {

    initCam();
    ACameraDevice_request_template t = TEMPLATE_RECORD;
    ACaptureRequest * pRequest = nullptr;
    const ACameraDevice * y = cameraDev;
    camera_status_t stat = ACameraDevice_createCaptureRequest(y, t, &pRequest);
    return env->NewStringUTF(std::to_string(stat).c_str());

}

