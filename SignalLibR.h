/*
* maindetect.h
*
*  Created on: Jul 12, 2011
*      Author: root
*/

#ifndef MAINDETECT_H_
#define MAINDETECT_H_

#include <cstdio>
#include <cstring>
#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
//#include <string>

#include <string.h>
#include <math.h>
#include "time.h"
#include "sing.h"
#include <vector>

//#include <log4cxx/logger.h>
//#include <log4cxx/xml/domconfigurator.h>

#include <fstream>


//#include "DecompressFile.h"
using namespace std;
//using namespace log4cxx;
//using namespace log4cxx::xml;
//using namespace log4cxx::helpers;

using namespace std;
#define BUFFER_SIZE  100000 //һ�ζ�ȡ�����ݸ���
#define EQUIDIST_MS   300 //����PSD����
#define SDNNStd_L 17
#define SDNNStd_H 79
#define PNN50Std_L 8
#define PNN50Std_H 16
#define HRVIStd_L 20
#define HRVIStd_H 52
#define RMSSDStd_L 15
#define RMSSDStd_H 39
#define TPStd_L 3466-1018
#define TPStd_H 3466+1018
#define VLFStd_L 0
#define VLFStd_H 2000
#define LFStd_L 1170-416
#define LFStd_H 1170+416
#define HFStd_L 975-203
#define HFStd_H 975+203
#define LF_HF_RatioStd_L 1.5
#define LF_HF_RatioStd_H 2.0//HRVʱ�����ָ�����ֵ��Χ

#ifndef PI
#define PI 3.14159265358979323846
#endif /* PI */

//
#define TOTAL_POWER_START  0.0000
#define TOTAL_POWER_END    0.4000
#define ULF_START          0.0000
#define ULF_END            0.0030
#define VLF_START          0.0030//0<=0.04
#define VLF_END            0.0400
#define LF_START           0.0400
#define LF_END             0.1500
#define HF_START           0.1500
#define HF_END             0.4000
#define POWER_LAW_START    0.0001
#define POWER_LAW_END      0.0100 //HRVƵ��ָ�����ֵ��Χ

typedef struct _DOUB_ARR {
	double * arr;
	int count;
} DOUB_ARR;
typedef struct _LONG_ARR {
	long * arr;
	int count;
} LONG_ARR;

typedef struct _QRS_TEMP {
	double *arr;
	int QRS_len;
	int QR_len;
	int RR_mean;  // mean RR interval
}QRS_TEMP;

typedef struct _ECG_Diagnose_resultPerHour
{
	long HeartRate;    //ƽ������
	int Valid_Sample_duration;  //��Чʱ��
	long HeartNum;   //��������
	long  Abnormal_HeartNum; //�쳣��������
	long PAB_Num;   //�����粫����
	long PVB_Num;  // �����粫����

	int Insert_PVB_Num;  //�������������
	int Bigeminy_Num;   //�����ɸ���
	int Trigeminy_Num;   // �����ɸ���
	int Arrest_Num;  // ͣ������
	int Missed_Num;  //52 ©������
	int VT_Num;   //�����Ķ����ٸ���
}ECG_Diagnose_resultPerHour;

typedef struct _ECG_Diagnose_resultPerHour_ARR
{
	ECG_Diagnose_resultPerHour  *arr;
	int count;
}ECG_Diagnose_resultPerHour_ARR;


typedef struct _ECG_Diagnose_resultAll
{
	LONG_ARR Rlist;//R����λ��
	LONG_ARR RRlist;//RR���ڵ��б� ����Ϊ��λ
	LONG_ARR Noiselist;  //α���б� ��1sΪһ����λ ��1����α����0��û��

	int Arrest_Num;//51 ͣ������
	int *Arrest_posL;// ͣ��λ���б���

	int Missed_Num;//52 ©������
	int *Missed_posL;//

	int PVB_Num;//53 �����粫����
	int *PVBposL;//

	int PAB_Num;//54 �����粫����
	int *PABposL;//

	int Insert_PVB_Num;//55 �������������
	int *Insert_PVBposL;

	int VT_Num;//56 �����Ķ����ٸ���
	int *VT_posL;

	int Bigeminy_Num;//57 �����ɸ���
	int *Bigeminy_posL;

	int Trigeminy_Num;//58 �����ɸ���
	int *Trigeminy_posL;

}ECG_Diagnose_resultAll;


struct peak_buffer {
	double amp;//��ķ�ֵ
	long idx;//��ֵ���λ��
	long start;//�����ʼ��
	long end;//�����ֹ��
}; /* struct peak_buffer */

typedef struct {
	double r, i;
} complex;

typedef struct {
	int start, end;
} S_Epos;

struct AbECG {//SGSG
	string AbECGfile;//�쳣�ĵ����ݶε������ļ���
	string AbECGfileID;//�쳣�ĵ����ݶε��ϴ�ʱ��Ӧ��ID
	string AbECGType;//�쳣�ĵ����ݶ��и����쳣��λ�ã��㣩������
	string AbECGTime;//�쳣�ĵ����ݶη���ʱ�䣨�룩
};

struct ecg_result {
	long ImageNum;//4 ��ͼ�ĸ���
	long iCount;//5 ԭʼ���ݵĻ�ͼ����
	long TimeLength;//7 ԭʼ���ݵĳ��� ��

	long AbECGNum;//14 �쳣���ݻ�ͼ�ĸ���
	long HeartRate;//15 ����
	long HRLevel;//16 ����ˮƽ
	string RRfile; //RRֵ�洢���ļ���
	string RRfileID;//17RRֵ�洢�ļ��ϴ�ID
	double SDNN;//18
	long SDNNLevel;//19

	double PNN50;//20
	long PNN50Level;//21
	double HRVI;//22
	long HRVILevel;//23
	double RMSSD;//24
	long RMSSDLevel;//25
	double TP;//26
	long TPLevel;//27
	double VLF;//28
	long VLFLevel;//29
	double LF;//30
	long LFLevel;//31
	double HF;//32
	long HFLevel;//33
	double LF_HF_Ratio;//34
	long LHRLevel;//35
	double SD1;//36
	double SD2;//37
	string PSDfile;
	string PSDfileID;//38
	int ECGResult;//1�����ĵ�����쳣��0Ϊ����
	int AnalysisOk;//43 1�����ĵ����������⣬0�����ĵ����ݿ�����������
	long HeartNum;//44 ��������
	int Slowest_Beat;//45 �������ֵ
	int Slowest_Time;//46 ������ʷ���ʱ�� ��
	int Fastest_Beat;//47 ��������ֵ
	int Fastest_Time;//48 �������ʷ���ʱ�� ��

	int Polycardia;//49 1��������Ķ����٣�0��ʾ������
//	int *RR_Polycardia_posl;
	int Bradycardia;//50 1��������Ķ�������0��������
//	int *RR_Bradycardia_posl;

	int guosuNum;     //心动过速
	int *guosu_posL;  //
	int guohuanNum;   //心动过缓
	int *guohuan_posL;


	int Arrest_Num;//51 ͣ������
	int *Arrest_posL;// ͣ��λ���б���

	int Missed_Num;//52 ©������
	int *Missed_posL;//


	int Wide_Num; //SG �����������ּ�Ϊ1��������Ϊ0
	int *Wide_posL;//SG

	int flagAR;//LSJ 1����������ʲ��룬0��������


	int PVB;//53 �����粫����
	int *PVBposL;//

	int PAB;//54 �����粫����
	int *PABposL;//

	int Insert_PVBnum;//55 �������������
	int *Insert_PVBposL;

	int VT;//56 �����Ķ����ٸ���
	int *VT_posL;

	int Bigeminy_Num;//57 �����ɸ���
	int *Bigeminy_posL;

	int Trigeminy_Num;//58 �����ɸ���
	int *Trigeminy_posL;

	int Wrong_Num; //α�������ĸ���

	struct AbECG *AbECG;
	DOUB_ARR ECGlist;
	DOUB_ARR D0list;
	DOUB_ARR v1list;//��һ��ͨ������
	DOUB_ARR v2list;//�ڶ���ͨ������
	LONG_ARR v3list;//������ͨ������
	LONG_ARR Rlist;//R����λ��
	LONG_ARR RRlist;//RR���ڵ��б� ����Ϊ��λ
	LONG_ARR RRlist1;//RR���ڵ��б� ����Ϊ��λ
	LONG_ARR RRlistImg; //����˲ʱ����ͼ��ʾ�� dai

	LONG_ARR Qlist;//QRS������λ��
	LONG_ARR Slist;//QRS���յ��λ��
	LONG_ARR QRSlist;//QRS������б�
	LONG_ARR Rannolist;//ÿһ����ע�͵��б������Ӧ��ϵ������
	DOUB_ARR speclist;//PSD�����б�
	DOUB_ARR axislist;//PSD�����б�
	/*
	LONG_ARR T_peaklist;//T����ֵ��λ��
	LONG_ARR T_endlist;//T���յ��λ��
	LONG_ARR T_type;//T������̬
	DOUB_ARR T_value;//T����ֵ��ĵ�ѹֵ
	DOUB_ARR ST_value;
	LONG_ARR ST_type;


	DOUB_ARR ECGlist_com;//���ڷ�����ԭʼ�ĵ�����
*/
	LONG_ARR noiselist;//�����ж���������,5��Ϊ1����λ
	LONG_ARR noiselist_A;//�����ж��������ݣ�1��Ϊ1����λ 2012.2.14
	DOUB_ARR d2list;

	ECG_Diagnose_resultPerHour_ARR   Diagnose_resultPerHourList;
	string RannoListFile;   // �洢R��ע�͵��ļ���

	int PVBPerHour;
	int longRR;
	int turetime;
	int Dayheartrate;
	int Nightheartrate;
	int guosutime;
	int guohuantime;

};

struct ecg_info {
	double samplerate;//��ֵ�������
	double samplerate_orig;//ԭʼ������
	double gain;//�Ŵ���
	long num_samples;//ԭʼ���ݸ���
	long heartneed;//��ȡƽ��RRʱ��ѡȡ����������
	double pvpercent;//������ǰ�����ٷֱȣ�
	double papercent;//������ǰ�����ٷֱȣ�
	long arrest_time;//ͣ���ж�ʱ�������룩

	long hearthigh;//���������ֵ
	long heartlow;//��С������ֵ
	long VT_value;//���ٵ���ֵ
	long interp_factor;//������ӣ��̶�Ϊ1
	long s5;//5����Ӧ�����ݵ���
	long ms100;//100������Ӧ�����ݵ���
	long ms50;//50������Ӧ�����ݵ���
	long ms30;//30������Ӧ�����ݵ���
	long ms10;//10������Ӧ�����ݵ���
}; /* struct ch_info */

struct data_buffer {
	long num_data;//��ȡ���ݵĸ���
	long data_offset;//��ȡ���ݵ�ƫ����

	double *orig;//һ�ζ�ȡ��ԭʼ����
	double *orig00;//���е�ԭʼ����
	double *f0;
	double *f1;
	double *s1;//����R����ȡ������
	LONG_ARR noiselist;//�����ж���������,5��Ϊ1����λ
	LONG_ARR noiselist_A;//�����ж��������ݣ�1��Ϊ1����λ 2012.2.14
	DOUB_ARR d2list;

	double ecgmean;//LSJ
	double s1mean;//s1��ƽ��ֵ
	double temp_mean;//ѡȡģ���ƽ���͵ľ�ֵ
	double temp_maxdiff;//ѡȡģ�������Сֵ��
	double temp_Rvalue;
	double temp_Tvalue;
	double temp_Svalue;
	long   temp_RT;
	long   temp_RS;

	vector<double> plate_data;//

}; /* struct data_buffer */




//计算心率
int countEcgRate(int ecg[], int len, int s_rate);
//计步
struct rslt {int state,stepcount;};
struct rslt pedomain(unsigned char*datinput,int len);
float kcal(int sex,int hr,int age,float weight,float time);





class maindetect {
public:

	maindetect();
	virtual ~maindetect();
	int  GETHRVTI(long *pr,int **RRhis,int count);
	int* getposL(LONG_ARR *Rannolist,int abNum,int abtype,LONG_ARR *Rlist,double fs);
	//�õ�ÿһ���쳣�ĵ粨�ķ���ʱ��
	struct ecg_result getecgresult(double *orig00, long ecgnum, int Fs,
		int GainK);//��������������ȡ���������orig00ԭʼ���ݣ�ecgnumԭʼ���ݸ�����FS����Ƶ�ʣ�GAINK����
	DOUB_ARR readdate();//�����������Ƕ�ȡ����
	DOUB_ARR readdatetest(); 
	DOUB_ARR readfromstring();
	int GET_NEWRanno(int Ranno);
	LONG_ARR ECG_NO_NOISE(double *ecglistarr, long ecglistnum,double fs);
	LONG_ARR ECG_NO_NOISE2013(double *ecglistarr, long ecglistnum,double fs);
	void releaseecgresult();//�ͷ���Դ
	//DOUB_ARR ECG_NO_NOISE(DOUB_ARR *ecglist);
	DOUB_ARR ECG_NO_NOISE2(DOUB_ARR *ecglist);
	//DOUB_ARR ECG_NO_NOISE_A(double *ecglistarr, long ecglistnum);//2012.2.14
	LONG_ARR ECG_NO_NOISE_A(LONG_ARR *noiselist5,LONG_ARR *Rlist, LONG_ARR *Rannolist,double fs,double *ecglistarr, long ecglistnum);//2012.2.14
private:
	double calcu_MeanSquSum(double *data, int dataNum);   //�����ϱ�д�����ڼ������ݵ�ƽ��ƽ����
	void Cancel_QRST(double *QRST_Template,int TemLenth,double *data,int dataNum,int step,double *MeanSquSum_error,int *R_location);
	int calcu_QRST_TP( double *QRST_buffer, int buffer_len, int beat_num, int  QT_len, double *QRST_TP);
	int Get_QRST_Template(LONG_ARR *Rlist, LONG_ARR *RRlist,struct data_buffer *buf, double fs, long ecgnum,long RRmean, int N, double *ecgsum);  // dai huhe
	LONG_ARR ECG_NO_NOISE_A_New(LONG_ARR *noiselist5,LONG_ARR *Rlist, double ecgsum,double fs,double *ecglistarr, long ecglistnum);  //by dai
	LONG_ARR get_NEW_RRlist_New(LONG_ARR *Rlist, LONG_ARR *RRlist, LONG_ARR *Rannolist, double fs, LONG_ARR *noiselist); //dai
	LONG_ARR gethighlowheart_New(LONG_ARR *RRlist, LONG_ARR *Rlist, long heartneed, double fs, ecg_result *result, int RRmean_global)   ; //dai
	QRS_TEMP CreateQRSTempForRecAbnorlBeat( DOUB_ARR *ECG_data,LONG_ARR *RRlist, LONG_ARR *Rlist, long AbBeat_index, double fs, int beat_num, int RRmean) ;  //dai
	QRS_TEMP CreateQRSTempForRecAbnorlBeat_A( DOUB_ARR *ECG_data,LONG_ARR *RRlist, LONG_ARR *Rlist, long AbBeat_index, double fs, int beat_num, int RRmean, long *QRS_start); //dai

	int ReDiagnoseAbnomalBeat( DOUB_ARR *ECG_data,LONG_ARR *RRlist, LONG_ARR *Rlist, LONG_ARR *Rannolist, double fs, ecg_info *ci, int RRmean, LONG_ARR *Noise_Anno );   //dai
	void getposL_perHour( long ECG_Num,int fs, ECG_Diagnose_resultAll  ECG_Diagnose_resultTotal);

	DOUB_ARR ECG_NO_NOISE2_A(double *ecglistarr, long ecglistnum,double fs);//2012.2.14
	int GET_NEWRannolist_A(LONG_ARR *RRlist,LONG_ARR *QRSlist,LONG_ARR *Rlist,LONG_ARR *noiselist_A,LONG_ARR *noiselist,LONG_ARR *Rannolist, double fs, ecg_result *result);
	DOUB_ARR ECG_NOISE(DOUB_ARR *ecglist);
	//	LoggerPtr logger;
	int wideflag;//�Ƿ��Ѿ��жϳ����ڿ�
	string filePath;
	ecg_result result;//���ݷ���������ڵĽṹ��
	string getrelative(int type);//������ע�͵����ֶ�ӦΪ����

	//SG
	int GET_TEMPLATE(LONG_ARR *Rlist,LONG_ARR *Rannolist,struct data_buffer *buf);
	//ͨ��ģ����ȡ��������ֵ

	int DROP_WRONG_RLIST(LONG_ARR *Rlist,LONG_ARR *QRS_startlist, LONG_ARR *QRS_endlist,LONG_ARR *RRlist,struct data_buffer *buf,double fs,long RRmean );
	//����һЩ���жϵ�R��λ�õ�
	int GET_RRLIST_NOISELIST(LONG_ARR *Rlist, LONG_ARR *RRlist,LONG_ARR *noiselist,long RRmean,double fs,struct data_buffer *buf);
	int DROP_WRONG_RLIST1(LONG_ARR *Rlist,LONG_ARR *QRS_startlist, LONG_ARR *QRS_endlist, LONG_ARR *RRlist,struct data_buffer *buf,long RRmean);
	int GET_NEWRannolist(LONG_ARR *Rlist,LONG_ARR *Rannolist,struct data_buffer *buf,double fs,long datanum);
	//���µõ�����R����ע��(��ȥһЩα��R������������)���жϳ�α���ı䵱ǰ������ע�ͼ�ǰһ��������ע��

	int GET_NEWRannolist_NEW(LONG_ARR *Rlist,LONG_ARR *RRlist, LONG_ARR *Rannolist,
	struct data_buffer *buf, double fs, long ecgnum,long RRmean, LONG_ARR *QRSlist);
	////���µõ�����R����ע��(��ȥһЩα��R������������,������ģ���Ӧ��ֵ����ж�)
	int GET_TEMPLATE_NEW(LONG_ARR *Rlist, LONG_ARR *RRlist,struct data_buffer *buf, double fs, long ecgnum,long RRmean);
	////�õ�һ��ģ�壬����ΪFS�������ĸ������Ĳ�����ȡƽ��ֵ�õ�
	int GET_NEWRannolist_AFTER(LONG_ARR *Rlist,LONG_ARR *RRlist,LONG_ARR *Rannolist,struct data_buffer *buf,double fs);
	////��������α������Ĵ���ע�ͺ��ڴ���ͣ����©����������ж�����������Ƿ���ʵ���ڣ�������RRlist
	double get_var(vector<double> ecgvector);
	////��ȡ������


	LONG_ARR get_NEW_RRlist(LONG_ARR *Rlist,LONG_ARR *Rannolist, double fs);
	//�õ��µ�RR���ڣ�ȥ�����жϵ�R�����
	LONG_ARR get_PSD_RRlist_all(LONG_ARR *RRlist, LONG_ARR *Rannolist,
		double fs);//ȡ������5��������
	LONG_ARR get_PSD_RRlist(LONG_ARR *RRlist,LONG_ARR *PSD_Rlist,LONG_ARR *Rlist, LONG_ARR *Rannolist,
		double fs,LONG_ARR *noiselist_A);//ȡ������5��������
	//���ڽ���HRV������RR���ڣ�����������RR���ڣ�ȥ��һЩ�쳣������

	int findnextpos(LONG_ARR *Rannolist, long pos);
	int getAbecgseg(LONG_ARR Rannolist, double *orig00, long ecgnum,
		LONG_ARR *Rlist,int length,double sample);
	//�õ��쳣�ĵ����ݶΣ������쳣���ݴ洢������һ��1500����

	int storeAbecgfile(int pos, double *orig00, long ecgnum, LONG_ARR *Rlist,
	struct AbECG *AbECG, int length, int Abnum);
	//�洢�쳣�ĵ�����

	double get2double(double a);
	double getmean(LONG_ARR *list);
	double getRRmean(LONG_ARR *RRlist);
	LONG_ARR getQRSWIDTHlist(LONG_ARR *QRS_startlist, LONG_ARR *QRS_endlist,
		double fs);
	//��ȡQRS�����

	int gethighlowheart(LONG_ARR *RRlist, LONG_ARR *Rlist, long heartneed,
		double fs, ecg_result *result);
	//��ȡ����������

	int getothers(LONG_ARR *RRlist, LONG_ARR *QRSlist, LONG_ARR *Rannolist,ecg_result *result, double pvpercent,
		double papercent, long arrest_time,long VT_value,LONG_ARR *Rlist,struct data_buffer *buf);
	//��ȡ�����쳣���ĸ��������������ע��Rannolist

	int fabsint(int a);

	int pre_process_data(double **values, long num);//����HRV����
	int process_values(LONG_ARR *RRlist, LONG_ARR *Rlist, double **value,
		double samplerate_orig, double samplerate, long *real_num); //����HRV����

	LONG_ARR getRRlist(LONG_ARR *Rlist, double fs);
	LONG_ARR getRRlist_A(LONG_ARR *Rlist,LONG_ARR *Rannolist, double fs);//2012.2.15

	int getAR_high(LONG_ARR *RRlist,LONG_ARR *Rannolist, double RRmean);//�ж��Ƿ�������ɲ���

	int find_peaks(struct data_buffer *buf, double *sig_use, long start,
		long num, double threshold, double area_filt,
	struct peak_buffer **peaks, long *num_peaks, long *morph_type,
		long ms30, int allow_look_before, int allow_look_after);//��ȡR��������ֵ��
	int get_peaks(struct data_buffer *buf, double *sig_use, long start,
		long num, double threshold, double area_filt,
	struct peak_buffer **peaks, long *num_peaks, long *morph_type,/* long force_morph_type,*/
		long ms30, int allow_look_before, int allow_look_after);//����ȡR��������ֵ�����

	int get_qrs_complex(double lastR,struct data_buffer *buf, long *curr_pos,/* int ch_idx,*/
		long ms100, long ms50, long ms30, /*long force_type,*/long *QRS_START,
		long *QRS_END,int noise);
	//��ȡQRS�����յ�λ��

	int fir_filter_design(long order, double cut_low, double cut_high,
		double **b, long *num);

	int prepare_data_access(long do_interpolation, struct ecg_info *ci,
	struct data_buffer *buf);//׼��һЩ��������

	int filter(double *b, double *a, long order, double *data,
		long num_samples, int direction);
	int filtfilt(double *b, double *a, long order, double *data,
		long num_samples);
	int interp(double *in, double *out, long num_samples, long factor);//��ԭʼ��������ֵ��û�õ�

	//LSJ
	long get_data_new(/*rec_handle rh, long ch,*/long ch_pos,
	struct data_buffer *buf, long num_to_read, long interp_factor,double gain,int M_WIDTH,double H_HIGHT); 
	long look_for_next_beat(double *data, long num_data, long pos,
		double threshold, long blanktime, long ms30);//��ȡ�ض�����ԭʼ���ݣ������б任

	double get_min(double *values, long num, long *pos);
	double get_max(double *values, long num, long *pos);
	double mean(double *values, long num);
	int remove_mean(double * v, long n);

	int histogram(double *values, long num, long **hist, long *hist_start,
		long *hist_size, int bin);//������HRVָ����ȡ���
	double stddev(double *values, long num);
	double calc_sdnn(LONG_ARR *RRlist);
	double calc_pnn50(LONG_ARR *RRlist);
	double calc_rmssd(LONG_ARR *RRlist);
	double calc_hrvi(LONG_ARR *RRlist);
	int calc_poincare(LONG_ARR *RRlist, double *SD1, double *SD2);
	double calc_power(double start, double end, double sample_dist_ms,
		DOUB_ARR *axislist, long n);
	void window_hanning(double *v, long n, double *power);
	int window_data(double *v, long n,/* char *window,*/double *w_power);
	int calc_fft(double *data, long n, complex *out);
	DOUB_ARR calc_periodogram(double *values, long n, double samplefreq,/* double **spec,*/
		long *n_spec/*, int rm_mean, char *window*/);

	void getQRSlist(LONG_ARR *Rlist, LONG_ARR *QRS_startlist, LONG_ARR *QRS_endlist,
	struct ecg_info *ci, struct data_buffer *buf);
	//��ȡR��λ�ã���ͬʱ��ȡQRS����ʼ��ֹ��λ��

	int GETLONGRR(LONG_ARR *new_RRlist,LONG_ARR *Rannolist);

	int GETTRUETIMEL(LONG_ARR *noiselist_A);
	//void GETDAYNIGHT(LONG_ARR *Rlist,LONG_ARR *RRlist);
	int  GETWIDEWAVE(struct data_buffer *buf,LONG_ARR *QRSlist,LONG_ARR *Rlist,LONG_ARR *noiselist_A,int Rnumneed,int QRSwide,double percent,LONG_ARR *Rannolist);
	LONG_ARR DROP_WRONG_RLIST2013(LONG_ARR *Rlist,LONG_ARR *noiselist, LONG_ARR *QRS_startlist,LONG_ARR *QRS_endlist,LONG_ARR *Rannolist, struct data_buffer *buf,double fs, long RRmean, ecg_result *result);
	LONG_ARR ECG_NO_NOISE_A_New2013(LONG_ARR *noiselist5, double ecgsum,double fs,double *ecglistarr, long ecglistnum);
	int GET_NEWRannolist_NEW2013(LONG_ARR *Rlist, LONG_ARR *RRlist,
		LONG_ARR *Rannolist, struct data_buffer *buf, double fs, long ecgnum,
		long RRmean, LONG_ARR *QRSlist); 
	int GETPVBPERMIN(LONG_ARR *Rlist, LONG_ARR *Rannolist,int number);
	void GETguohuansuTIME(LONG_ARR *RRlist, LONG_ARR *Rannolist);
};


#endif /* MAINDETECT_H_ */
