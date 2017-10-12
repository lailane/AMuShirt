/*
 * Copyright (C) 2009 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 */
#include <string.h>
#include <jni.h>
#include <ecg.h>
#include <android/log.h>

#include "SignalLibR.h"


#define FS "150"
#define GAIN_K "200"

/* This is a trivial JNI example where we use a native method
 * to return a new VM String. See the corresponding Java source
 * file located at:
 *
 *   apps/samples/hello-jni/project/src/com/example/hellojni/HelloJni.java
 */

jstring
Java_com_test_utils_DiagnosisNDK_stringFromJNI( JNIEnv* env, jobject thiz )
{
int i=0;
int sm=0;
int jj=1;
int mm=2;
sm = i+jj;
sm=mm+sm;

//libresult.Arrest_Num    停搏个数
//libresult.Arrest_posL   停博位置
//libresult.Missed_Num;   漏搏个数
//libresult.Missed_posL;  漏搏位置
//libresult。Wide_Num;      宽搏个数，出现即为1，不出现为0
//libresult.Wide_posL;     宽搏位置
//libresult.PVB;          室性早搏个数
//libresult.PVBposL;
//libresult.PAB;        //房性早搏个数
//libresult.PABposL;
//libresult.Insert_PVBnum;// 插入性室早个数
//libresult.Insert_PVBposL;
//libresult.VT_posL;
//libresult.Bigeminy_Num;// 二联律个数
//libresult.Bigeminy_posL;
//libresult.Trigeminy_Num;58 三联律个数
//libresult.Trigeminy_posL;
//libresult.Polycardia;//49 1代表存在心动过速，0表示不存在
//libresult.Bradycardia;//50 1代表存在心动过缓，0代表不存在
//	libresult.RRlist.arr;
//  libresult.RRList.count;

//libresult.VT;//56 室性心动过速个数

    return env->NewStringUTF("Hello from JNI !  Compiled with ABI ");
}


ecg_result libresult;
maindetect Maindetect;

jobject Java_com_test_utils_DiagnosisNDK_getEcgResult
  (JNIEnv * env, jclass clazz, jdoubleArray source, jlong length, jint s_rate)
{
	__android_log_print(ANDROID_LOG_INFO, "NDK TEST","NDK test");

	jclass cls = env->FindClass("com/test/objects/HeartRateResult");
	jmethodID id = env->GetMethodID(cls,"<init>","()V");

	jobject result = env->NewObjectA(cls,id,0);  //构造对象
	id = env->GetMethodID(cls,"setRrlist","([II)V");




	jdouble *dpointer = env->GetDoubleArrayElements(source,0);

	int i;

	libresult = Maindetect.getecgresult(dpointer, length, int(s_rate), int(200));

	env->ReleaseDoubleArrayElements(source, dpointer, 0);


	int RR_Sum = 0;
	RR_Sum= (int)libresult.RRlist.count;   // 0,RR间期总数

	int RR_speclist = libresult.speclist.count; //

	__android_log_print(ANDROID_LOG_INFO, "RRlist.count","%d", (int)libresult.RRlist.count);

	int RR_guosuNum = (int)libresult.guosuNum;
	int RR_guohuanNum = (int)libresult.guohuanNum;
	int RR_Standstill = (int)libresult.Arrest_Num; // 4,停博
	int RR_Apb = (int)libresult.PAB; // 5,房性早搏
	int RR_Pvc = (int)libresult.PVB; // 6,室性早搏,PVC
	int RR_2 = (int)libresult.Bigeminy_Num; // 7,二联律
	int RR_3 = (int)libresult.Trigeminy_Num; // 8,三联律
	int RR_Iovp = (int)libresult.Insert_PVBnum; // 9,插入性室早
	int RR_Boleakage = (int)libresult.Missed_Num; // 13,漏博
	int RR_Kuanbo = (int)libresult.Wide_Num; // 14,宽博
	int RR_pmn50 = (int)libresult.PNN50;
	int RR_sdnn =  (int)libresult.SDNN;
	int RR_hrvi =  (int)libresult.HRVI;
	double SD1 = (double)libresult.SD1;
	double SD2 = (double)libresult.SD2;

	double LF =  (double)libresult.LF;
	double HF =  (double)libresult.HF;




	jintArray data = env->NewIntArray(RR_Sum);
	jint *ipointer = env->GetIntArrayElements(data,0);

	for(i = 0; i < RR_Sum; i++)
	{
		ipointer[i] = libresult.RRlist.arr[i];
	}

	//设置R波位置

	env->CallVoidMethod(result,id,data,RR_Sum);

	env->DeleteLocalRef(data);
/*
	jmethodID id_Spec = env->GetMethodID(cls,"setSpecRrlist","([DI)V"); //画混沌图

	jdoubleArray data_spec = env->NewDoubleArray(RR_speclist);
	jdouble *fpointer = env->GetDoubleArrayElements(data_spec,0);
	for(i = 0; i<RR_speclist; i++)
	{
		fpointer[i] = libresult.speclist.arr[i];
	}

	env->CallVoidMethod(result,id_Spec,data_spec,RR_speclist);
	env->DeleteLocalRef(data_spec);
*/
//   ---------------------------------------------


	jfieldID intId = env->GetFieldID(cls,"RR_2","I");           //二联律
	env->SetIntField(result, intId, RR_2);


	intId = env->GetFieldID(cls,"RR_3","I");                    //三联律
	env->SetIntField(result, intId, RR_3);


	intId = env->GetFieldID(cls,"RR_Apb","I");                  // 房性早搏
	env->SetIntField(result, intId, RR_Apb);


	intId = env->GetFieldID(cls,"RR_Boleakage","I");            //漏博
	env->SetIntField(result, intId, RR_Boleakage);



	intId = env->GetFieldID(cls,"RR_Iovp","I");           // 插入性室早
	env->SetIntField(result, intId, RR_Iovp);

	intId = env->GetFieldID(cls,"RR_Kuanbo","I");         //宽博
	env->SetIntField(result, intId, RR_Kuanbo);

	intId = env->GetFieldID(cls,"RR_PNN50","I");
	env->SetIntField(result,intId,RR_pmn50);
	intId = env->GetFieldID(cls,"RR_Pvc","I");  // 室性早搏
	env->SetIntField(result,intId,RR_Pvc);
	intId = env->GetFieldID(cls,"RR_SDNN","I");
	env->SetIntField(result,intId,RR_sdnn);

	intId = env->GetFieldID(cls,"RR_HRVI","I");
	env->SetIntField(result,intId,RR_hrvi);

	intId = env->GetFieldID(cls,"LF","D");
	env->SetDoubleField(result,intId,LF);

	intId = env->GetFieldID(cls,"HF","D");
	env->SetDoubleField(result,intId,HF);

	intId = env->GetFieldID(cls,"SD1","D");
	env->SetDoubleField(result,intId,SD1);

	intId = env->GetFieldID(cls,"SD2","D");
	env->SetDoubleField(result,intId,SD2);

	intId = env->GetFieldID(cls,"RR_Standstill","I");    //停博
	env->SetIntField(result,intId,RR_Standstill);


	intId = env->GetFieldID(cls,"RR_Sum","I");         //RR 间期总数
	env->SetIntField(result,intId,RR_Sum);

	intId = env->GetFieldID(cls,"RR_Bradycardia","I");               //心动过缓
	env->SetIntField(result, intId, RR_guohuanNum);

	intId = env->GetFieldID(cls,"RR_Tachycardia","I");
	env->SetIntField(result,intId,RR_guosuNum);                   //心动过速


	//-------  释 放 内 存   未测试------


	return result;

}

jint Java_com_test_utils_DiagnosisNDK_getEcgHeart
  (JNIEnv * env, jclass clazz, jintArray source, jint length, jint s_rate)
{

//	__android_log_print(ANDROID_LOG_INFO, "getEcgHeart1","length= %d, s_rate=%d", length, int(s_rate));
    int len = length;
    int rate = s_rate;


	jint *ipointer = env->GetIntArrayElements(source,0);
	int csource[len];
	for(int i=0; i<len; i++)
	{
		csource[i] = ipointer[i];
	}

	env->ReleaseIntArrayElements(source, ipointer, 0);

	return  countEcgRate( csource,int(len), int(s_rate));
}





void Java_com_test_utils_DiagnosisNDK_getPedo
  (JNIEnv * env, jclass clazz, jbyteArray intdat,jint len, jintArray outData)
{

//	__android_log_print(ANDROID_LOG_INFO, "getPedo","11");



	rslt rstmp;

	jbyte *cpointer = env->GetByteArrayElements(intdat,0);

	jint *outPointer = env->GetIntArrayElements(outData,0);

//	__android_log_print(ANDROID_LOG_INFO, "getPedo","22");


	unsigned char data[len];

	for(int i=0; i<len; i++)
	{
		data[i] = (unsigned char)cpointer[i];
	}

	__android_log_print(ANDROID_LOG_INFO, "getPedo","33");




	rstmp = pedomain(data,len);

	__android_log_print(ANDROID_LOG_INFO, "getPedo","state =%d   count=%d "+rstmp.state, rstmp.stepcount);

	outPointer[0] = rstmp.state;
	outPointer[1] = rstmp.stepcount;

	env->ReleaseByteArrayElements(intdat, cpointer, 0);
	env->ReleaseIntArrayElements(outData, outPointer, 0);


}

float Java_com_test_utils_DiagnosisNDK_getkcal
  (JNIEnv * env, jclass clazz, jint sex,jint hr, jint age, jfloat weight,jfloat time)
{
	return kcal(sex, hr, age,weight,time);
}




