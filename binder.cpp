/* -*- mode: C++; c-basic-offset: 4; indent-tabs-mode: nil -*-
   vi:ai:tabstop=8:shiftwidth=4:softtabstop=4:expandtab
*/

/*
 * Author: Gabriel Burca <gburca dash binder at ebixio dot com>
 *
 * Sample code for using binders in Android from C++
 *
 * The Demo service provides 3 operations: push(), alert(), add(). See
 * the IDemo class documentation to see what they do.
 *
 * Both the server and client code are included below.
 *
 * To view the log output:
 *      adb logcat -v time binder_demo:* *:S
 *
 * To run, create 2 adb shell sessions. In the first one run "binder" with no
 * arguments to start the service. In the second one run "binder N" where N is
 * an integer, to start a client that connects to the service and calls push(N),
 * alert(), and add(N, 5).
 */

#define LOG_TAG "binder_demo"

/* For relevant code see:
    frameworks/native/{include,libs}/binder/{IInterface,Parcel}.{h,cpp}
    system/core/include/utils/{Errors,RefBase}.h
 */

#include <stdlib.h>
#include <stdio.h>

#include <utils/RefBase.h>
#include <utils/Log.h>
#include <binder/TextOutput.h>

#include <binder/IInterface.h>
#include <binder/IBinder.h>
#include <binder/ProcessState.h>
#include <binder/IServiceManager.h>
#include <binder/IPCThreadState.h>

using namespace android;


#define INFO(...) \
    do { \
        printf(__VA_ARGS__); \
        printf("\n"); \
        ALOGD(__VA_ARGS__); \
    } while(0)

void assert_fail(const char *file, int line, const char *func, const char *expr) {
    INFO("assertion failed at file %s, line %d, function %s:",
            file, line, func);
    INFO("%s", expr);
    abort();
}

#define ASSERT(e) \
    do { \
        if (!(e)) \
            assert_fail(__FILE__, __LINE__, __func__, #e); \
    } while(0)


// Where to print the parcel contents: aout, alog, aerr. alog doesn't seem to work.
#define PLOG aout




int main(int argc, char **argv) {

    sp<IServiceManager> sm = defaultServiceManager();
    ASSERT(sm != 0);
    sp<IBinder> binder = sm->getService(String16("isms"));
    ASSERT(binder != 0);
     if(binder != 0)
       {
            printf("binder get ok");
        }
     else{
             printf("binder get wrong");}

     Parcel data, reply;
     data.writeInterfaceToken(String16("com.android.internal.telephony.ISms"));
     data.writeString16(String16("com.example.luoge.sendsms"));
     data.writeString16(String16("15555215556"));
     data.writeString16(String16("5554"));
     data.writeString16(String16("send sms by binder"));
     data.writeInt32(0);
     data.writeInt32(0);
 
     binder->transact(5, data, &reply, IBinder::FLAG_ONEWAY);    // asynchronous call

     reply.print(PLOG); endl(PLOG);
     int32_t res=-1;
     status_t status = reply.readInt32(&res);
     ALOGD(" (res: %i )  (status: %i)", res, status);



   
   

    return 0;
}


