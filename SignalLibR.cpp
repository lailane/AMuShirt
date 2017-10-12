/*
* maindetect.cpp
*
*  Created on: Jul 12, 2011
*      Author: root
*/

//#include <stdafx.h>

#include "SignalLibR.h"
#include <time.h>
#include<sys/time.h>
#include <math.h>
#include <math.h>

#define NOISE_TIME 5
#define NOISE_TIME_A 1
#define QR_len_global  0.06     // 0.1s
#define RS_len_global  0.06
/*
extern double valuesu;
extern double valuesb;
extern double valuesa;
extern double valuevt;
extern double valuepa;
extern double valuepv;
extern double valuefs;
extern double valuegain;

*/

#include <android/log.h>

double valuesu = 105;
double valuesb = 50.0;
double valuesa = 2;
double valuevt = 130;
double valuepa = 15;
double valuepv = 10;
double valuefs =250;
double valuegain =384;

//namespace MiningServer {

maindetect::maindetect(/*string rawDataFile*/) {
	// TODO Auto-generated constructor stub
	//filePath = rawDataFile;
	//logger = Logger::getLogger("main");
}

maindetect::~maindetect() {
	// TODO Auto-generated destructor stub
}

double maindetect::get2double(double a) {
	a = ((double) ((int) (a * 100))) / 100;
	return a;
}
/**
DOUB_ARR maindetect::readfromstring() {
string ecgecg;
DOUB_ARR ECGlist;
ECGlist.count = 0;
DecompressFile decompressfile(filePath);//DecompressFile,then put in ecgecg
ecgecg = decompressfile.Decompress();
if (ecgecg == "0") {
LOG4CXX_ERROR(logger, "decompress file error...");//LSJ
return ECGlist;
} else {
LOG4CXX_DEBUG(logger, "decompress file and store in a string...");
}

vector<double> ecgvector;
string::size_type npos1 = ecgecg.find("\n", 0);
int i = 0;
while (npos1 < ecgecg.npos) {
string::size_type npos2 = ecgecg.find("\n", npos1 + 1);
string str = ecgecg.substr(npos1 + 1, (npos2 - npos1 - 1));
ecgvector.push_back(atof(const_cast<const char *> (str.c_str())));
npos1 = npos2;
i++;
}

ofstream ofs;
ofs.open("/tmp/ecgrawdata.txt", ostream::app);
//std::cout << "ECGlist.count***ECGlist.count***" << i << "\n\n";
ECGlist.arr = (double *) malloc((i) * sizeof(double));
ECGlist.count = i;
for (i = 0; i < ECGlist.count; i++) {
ECGlist.arr[i] = ecgvector[i];
ofs << ecgvector[i];
ofs << "\n";
}

ofs.close();
ofs.clear();
LOG4CXX_DEBUG(logger, "decompress file and get DOUB_ARR in ECGlist...");
return ECGlist;
}

DOUB_ARR maindetect::readdate(string Fs) {

double _fs;
string ecgecg;
DOUB_ARR ECGlist;
ECGlist.count = 0;
_fs = (double) (atoi(Fs.c_str()));

DecompressFile decompressfile(filePath);//DecompressFile,then put in ecgecg
ecgecg = decompressfile.Decompress();
if (ecgecg == "0") {
LOG4CXX_ERROR(logger, "decompress file error...");//LSJ
return ECGlist;
} else {
LOG4CXX_DEBUG(logger, "decompress file and store in a string...");
}

vector<double> ecgvector;
string::size_type npos1 = 0;
unsigned int i = 0;
while (npos1 < ecgecg.size()) {//ecgecg.npos
unsigned char str = ecgecg.at(npos1);
ecgvector.push_back((double) (str));
npos1 = npos1 + 1;
i++;
}

ofstream ofs;
ofs.open("/tmp/ecgrawdata.txt", ostream::app);
//	std::cout << "ECGlist.count***ECGlist.count***" << i << "\n\n";
//	ECGlist.arr = (double *) malloc((i) * sizeof(double));
//	ECGlist.count = i;
//	for (i = 0; i < ECGlist.count; i++) {
//		ECGlist.arr[i] = ecgvector[i];
//		ofs << ecgvector[i];
//		ofs << "\n";
//	}


int j = 0;
DOUB_ARR v1list;
v1list.arr = (double*) malloc(
sizeof(double) * ((int) (ecgvector.size() / 1) + 100));//100000
v1list.count = 0;

if ((int) (_fs) == 250) {
for (i = 0; i < ecgvector.size() - 2; i++) {
if (ecgvector[i] == 35 && ecgvector[i + 1] == 35
&& ecgvector[i + 2] == 35 && ecgvector[i + 3] == 35
&& ecgvector[i + 4] == 35 && ecgvector[i + 5] == 35
&& ecgvector[i + 6] == 35 && ecgvector[i + 7] == 35
&& ecgvector[i + 8] == 35 && ecgvector[i + 9] == 35) {
i = i + 9;
} else {
v1list.arr[j] = 4096 - (ecgvector[i] * 256 + ecgvector[i + 1]);
if (v1list.arr[j] == 4096 - 8174 || v1list.arr[j] == 4096
- 60959)
v1list.arr[j] = 4096;
v1list.arr[j] = (int) ((v1list.arr[j] - 2000) / 3);
ofs << v1list.arr[j];
j = j + 1;
i = i + 1;
ofs << "\n";
}
}
} else {
for (i = 0; i < ecgvector.size() - 2; i++) {
v1list.arr[j] = ecgvector[i] - 128;
j = j + 1;
ofs << v1list.arr[j];
ofs << "\n";
}
}

v1list.count = j;

ofs.close();
ofs.clear();

return v1list;
}
**/
int maindetect::GET_NEWRannolist_AFTER(LONG_ARR *Rlist, LONG_ARR *RRlist,LONG_ARR *Rannolist, struct data_buffer *buf,double fs)
{//?????????????????????????е?????????
	int j = 0;
	int i = 0;
	unsigned k=0;
	vector<double> ecgsegment;
	double var_value = 0;
	double ecgmean = 0;
	double max = 0;
	double min = 0;

	int temp0;
	int temp1;

	temp0=300/5;
	temp1=3;

	for (j = 0; j < Rannolist->count - 1; j++)
	{
		if (Rannolist->arr[j] == 1 || Rannolist->arr[j] == 2)//???????????????????
		{
			if(Rlist->arr[j + 1]>Rlist->arr[j] + (int)(0.7 * fs))
			{

//(ANDROID_LOG_INFO, "GET_NEWRannolist_AFTER ", " ecgsegment.size()=%d ",ecgsegment.size());

				for (i = Rlist->arr[j] + (int)(0.4 * fs); i < Rlist->arr[j + 1] - (int)(0.3* fs); i++)//??????????????м????????????T???????????P??
				{
					ecgsegment.push_back(buf->orig00[i]);

				}

				//var_value=get_var(ecgsegment);
				max = ecgsegment[0];
				min = ecgsegment[0];

				for (k = 0; k < ecgsegment.size(); k++)
				{
					ecgmean += ecgsegment[k];
					if (max < ecgsegment[k])
						max = ecgsegment[k];
					if (min > ecgsegment[k])
						min = ecgsegment[k];
				}
				ecgmean = ecgmean / (ecgsegment.size());

				
				for (k = 0; k < ecgsegment.size(); k++)
				{
					var_value += (ecgsegment[k] - ecgmean) * (ecgsegment[k]- ecgmean);
				}
//(ANDROID_LOG_INFO, "GET_NEWRannolist_AFTER ", " @@ ecgsegment.size()= %d ",ecgsegment.size());
//(ANDROID_LOG_INFO, "GET_NEWRannolist_AFTER ", " @@ var_value()= %f ",var_value);

				var_value = sqrt(var_value / (ecgsegment.size()));


				if (/*(var_value > temp1||(max - min > 6))||*/(fabs(buf->orig00[Rlist->arr[j]])<6&&fabs(buf->orig00[Rlist->arr[j+1]])<6))
				{//??????????н??????????????????????????????????????????????ж?
/*
//(ANDROID_LOG_INFO, "GET_NEWRannolist_AFTER ", " var_value = %f ",var_value);

//(ANDROID_LOG_INFO, "GET_NEWRannolist_AFTER ", " temp1 = %d ",temp1);
//(ANDROID_LOG_INFO, "GET_NEWRannolist_AFTER ", " max = %f ",max);
//(ANDROID_LOG_INFO, "GET_NEWRannolist_AFTER ", " min = %f ",min);
//(ANDROID_LOG_INFO, "GET_NEWRannolist_AFTER ", " fabs(buf->orig00[Rlist->arr[j]] = %f ", fabs(buf->orig00[Rlist->arr[j]]));
//(ANDROID_LOG_INFO, "GET_NEWRannolist_AFTER ", " fabs(buf->orig00[Rlist->arr[j+1]]) = %f ", fabs(buf->orig00[Rlist->arr[j+1]]));*/
					if (Rannolist->arr[j] == 1)
						result.Arrest_Num--;
					else
						result.Missed_Num--;
					Rannolist->arr[j] = 0;
					if (j > 0)
						RRlist->arr[j] = RRlist->arr[j - 1];
					else
						RRlist->arr[j] = RRlist->arr[j + 1];
				}
				ecgsegment.clear();
			}
		}
	}
	return 0;
}
LONG_ARR maindetect::ECG_NO_NOISE2013(double *ecglistarr, long ecglistnum,double fs) 
{
	vector<double> sec_ecg;
	LONG_ARR noiselist;
	int i = 0;
	int j = 0;
	double temp = 0;
	double temp_l = 0;
	double temp_h = 0;
	int temp_num = 1;
	double m=0;
	int lensec = (int) (ecglistnum / fs / NOISE_TIME);//???????5?????
	int k_sec = 0;//????
	double sum_noise = 0;//?????????????????
	double meansec = 0;
	vector<double> sum_noisev;
	vector<double> meansecv;
	noiselist.arr = (long *) malloc((lensec) * sizeof(long));//5.17
	if (NULL == noiselist.arr) 
	{
		return noiselist;
	}

	for (i = 0; i < ecglistnum; i++) 
	{
		sec_ecg.push_back(ecglistarr[i]);
		sum_noise += (ecglistarr[i]);
		if (i == ((k_sec + 1) * fs * NOISE_TIME - 1)) 
		{
			sum_noise = sum_noise / fs / NOISE_TIME;
			for (j = 0; j < fs * NOISE_TIME; j++) 
			{
				meansec += fabs(sec_ecg[j] - sum_noise) * fabs(sec_ecg[j] - sum_noise);//? fabs(sec_ecg[j]-sum_noise)
			}
			meansec = sqrt(meansec / fs / NOISE_TIME);//? meansec/fs/NOISE_TIME

			sum_noisev.push_back(sum_noise);
			meansecv.push_back(meansec);

			sum_noise = 0;
			meansec = 0;
			sec_ecg.clear();

			k_sec++;
		}
	}
	/*
	if((int)(fs)==250)
	{
	for(i=0;i<meansecv.size();i++)
	{
	if(meansecv[i]>3&&meansecv[i]<150)
	{
	temp+=meansecv[i];
	temp_num++;
	}
	}

	}
	else
	{
	*/
	for (i = 0; i < (int) meansecv.size(); i++) 
	{
		if (meansecv[i] > 0.5 && meansecv[i] < 30) //?????????????????????????????κ?????????
		{
			temp += meansecv[i];
			temp_num++;
		}
	}
	//}

	temp /= temp_num;
	temp_l = temp / 3.5;
	temp_h = temp * 3;
	if (temp_l < 0.6)
		temp_l = 0.6;

	for (i = 0; i < (int) meansecv.size(); i++) 
	{
		if (meansecv[i] > temp_l && meansecv[i] < temp_h/*&&sum_noisev[i]>-1.5&&sum_noisev[i]<1.5*/) 
		{
			noiselist.arr[i] = 0;// sgwh  1
		} 
		else 
		{
			m=meansecv[i];
			noiselist.arr[i] = 1;// sgwh  1
		}
	}

	noiselist.count = lensec;
	for (i = 1; i < lensec - 1; i++)//if the  short normal data is surroudded by lots of abnormal data, drop the short segment data
	{//?????????????Σ??????????ж????????
		if ((noiselist.arr[i] == 0) && (noiselist.arr[i - 1] == 1)
			&& (noiselist.arr[i + 1] == 1 || noiselist.arr[i + 2] == 1)) 
		{
			noiselist.arr[i] = 1;// sgwh  1
		}
	}

	sum_noisev.clear();
	meansecv.clear();
	return noiselist;
}

LONG_ARR maindetect::ECG_NO_NOISE_A_New2013(LONG_ARR *noiselist5,double ecgsum, double fs, double *ecglistarr, long ecglistnum) //by dai
{
	int i = 0;
	int j = 0;
	vector<double> sec_ecg;
	vector<double> noise_A;
	LONG_ARR noiselist;

	int lensec = (int) (ecglistnum / fs / NOISE_TIME_A);//??????
	int k_sec = 0;//????
	double sum_noise = 0;//????????????????
	noiselist.arr = (long *) malloc((lensec) * sizeof(long));
	if (NULL == noiselist.arr) 
	{
		return noiselist;
	}

	int length = NOISE_TIME * (int) (fs);
	double tempvalue = 0;
	for (i = 0; i < noiselist5->count; i++) 
	{
		k_sec = 0;
		if (noiselist5->arr[i] != 1) 
		{
			for (j = 0; j < length + 1; j++) 
			{
				tempvalue = ecglistarr[i * length + j];
				sec_ecg.push_back(tempvalue);
				sum_noise += tempvalue * tempvalue;
				if (j == (k_sec + 1) * (int) (fs) * NOISE_TIME_A) 
				{
					sum_noise = sqrt(sum_noise / NOISE_TIME_A);
					noise_A.push_back(sum_noise);
					sum_noise = 0;
					sec_ecg.clear();
					k_sec++;
				}
			}
		} else 
		{
			for (j = 0; j < NOISE_TIME; j++)
				noise_A.push_back(0);
		}
	}

	double temp = 0;
	int temp_num = 1;
	for (i = 0; i < (int) noise_A.size(); i++) 
	{
		if (noise_A[i] > 0) 
		{
			temp += noise_A[i];
			temp_num++;
		}
	}
	temp /= temp_num;
	double m=0;

	for (i = 0; i < (int) noise_A.size(); i++) 
	{
		if (noise_A[i] > 5.0 * temp || noise_A[i] <= 0)
			noiselist.arr[i] = 1;//3
		else
			noiselist.arr[i] = 0;
	}

	for (i = noiselist5->count * NOISE_TIME; i < lensec; i++) 
	{
		noiselist.arr[i] = 0;//3
	}
	noiselist.count = lensec;
	noise_A.clear();

	return noiselist;
}

LONG_ARR maindetect::DROP_WRONG_RLIST2013(LONG_ARR *Rlist, LONG_ARR *noiselist,LONG_ARR *QRS_startlist, LONG_ARR *QRS_endlist, LONG_ARR *Rannolist,
struct data_buffer *buf, double fs, long RRmean, ecg_result *result) 
{
	vector<long> Rvector;//NEW
	vector<long> RRvector;//NEW
	vector<long> QRS_startvec;//NEW
	vector<long> QRS_endvec;//NEW
	vector<long> Rannovector;

	//	double RRsum = 0;
	//	int falgchao = 0;
	//	int chaopos = 0;
	//	int heartrate = 0;
	int ratehigh = 2000;
	int ratehighpos = 0;
	int ratelow = 0;
	int ratelowpos = 0;
	//	int segRRlong = 0;
	//	int segRRshort = 0;

	int j = 0;
	//	int R_s=0;
	//	int R_e=0;

	int Rsec = 0;//R[i] belonged to this section of noiselist
	int R1sec = 0;
	//	int R10sec=0;//before 0.3S R[i1] belonged to this section of noiselist
	int flag0 = 0;

	LONG_ARR new_RRlist;
	new_RRlist.arr = NULL;
	double RRmean_temp = RRmean;
	double Rvalue_temp = 0;

	int jj = 0;
	int i = 0;
	unsigned k = 0;
	double max = 0;
	double min = 0;
	int max_p = 0;
	int min_p = 0;
	int m = 0;
	int RRtemp = 0;

	int length = NOISE_TIME_A * (int) (fs);
	Rvector.push_back(Rlist->arr[0]);
	QRS_startvec.push_back(QRS_startlist->arr[0]);
	QRS_endvec.push_back(QRS_endlist->arr[0]);
	Rannovector.push_back(0);

	for (i = 1; i < Rlist->count; i++)//be in noise data segment,delete this R wave
	{
		if (noiselist->arr[(int) (Rlist->arr[i] / length)] == 0) 
		{//??????????????????
			Rvector.push_back(Rlist->arr[i]);
			QRS_startvec.push_back(QRS_startlist->arr[i]);
			QRS_endvec.push_back(QRS_endlist->arr[i]);
			Rannovector.push_back(0);
			RRtemp = (int) ((Rvector[Rvector.size() - 1]- Rvector[Rvector.size() - 2]) / fs * 1000);
			RRvector.push_back(RRtemp);
			//	m=Rvector.size();
			//every 10 RR get the RRmean_temp
			if (((RRvector.size()) % 10 == 0) && RRvector.size() >= 10) 
			{
				RRmean_temp = 0;
				for (jj = 1; jj < 10; jj++) 
				{
					RRmean_temp += RRvector[RRvector.size() - 1 - jj];
				}
				RRmean_temp = (RRmean_temp / 9.0);//why 19.the last one is not sure
			}

			//get the lowest and highest heartrate
			if (RRmean_temp > ratelow) 
			{
				ratelow = (int) RRmean_temp;
				ratelowpos = RRvector.size() - 5;
			} 
			else if (RRmean_temp < ratehigh) 
			{
				ratehigh = (int) RRmean_temp;
				ratehighpos = RRvector.size() - 5;
			}

			flag0 = 0;
/*
			if (RRtemp > 1000)//find this section has zero data or not
			{//????R???????????????????????Σ????????????????????2

				Rsec = (int) (Rvector[Rvector.size() - 2] / fs / NOISE_TIME_A);
				R1sec = (int) (Rvector[Rvector.size() - 1] / fs / NOISE_TIME_A);
				for (j = Rsec; j < R1sec; j++) 
				{
					if (noiselist->arr[j] == 1)//exist 0 data, the RR[i] equals RR[i-1]
					{
						RRvector[RRvector.size() - 1] = (int) RRmean_temp;
						RRtemp = (int) RRmean_temp;

						flag0 = 1;
						Rannovector[Rvector.size() - 1] = -2;
						Rannovector[Rvector.size() - 2] = -2;//-2 stands for there are noises nearby
						break;
					}
				}
			}
*/
			if ((RRtemp <= 1.2 * buf->temp_RT || RRtemp <= 300) && RRmean_temp> 500)//average heartrate<120??but R and R too near, need to delete one of them
			{//?????????????С????RT???????????????????????????T???ж??R???????
				if ((buf->temp_RS==1)||(RRtemp <= 1.15 * buf->temp_RT && RRtemp >= 0.85* buf->temp_RT && fabs(buf->orig00[Rlist->arr[i]])< 1.2 * fabs(buf->orig00[Rvector[Rvector.size() - 2]]))) 
				{//????1??ζ????????T??????????????????
					Rvector.erase(Rvector.begin() + Rvector.size() - 1);
					QRS_startvec.erase(QRS_startvec.begin() + QRS_startvec.size() - 1);
					QRS_endvec.erase(QRS_endvec.begin() + QRS_endvec.size() - 1);
					Rannovector.erase(Rannovector.begin() + Rannovector.size() - 1);
					RRvector.erase(RRvector.begin() + RRvector.size() - 1);

				} 
				else if (fabs(buf->orig00[Rlist->arr[i]]) > 1.2 * fabs(buf->orig00[Rvector[Rvector.size() - 2]])&&(buf->temp_RS==0)) //delete the R before
				{//????????????????????????????????

					Rvector.erase(Rvector.begin() + Rvector.size() - 2);
					QRS_startvec.erase(QRS_startvec.begin() + QRS_startvec.size() - 2);
					QRS_endvec.erase(QRS_endvec.begin() + QRS_endvec.size() - 2);
					Rannovector.erase(Rannovector.begin() + Rannovector.size() - 2);
					RRvector.erase(RRvector.begin() + RRvector.size() - 1);

					if (RRvector.size() > 0) 
					{
						if (Rannovector[Rvector.size() - 2] == -2)//if the before R is wrong wave
							RRvector[RRvector.size() - 1] = (int) RRmean_temp;
						else
							RRvector[RRvector.size() - 1]= (int) ((Rvector[Rvector.size() - 1]- Rvector[Rvector.size() - 2]) / fs* 1000);
					}
					//if the last wave is kept,and decide to drop this wave,but this wave is higher than last one, replace them.
				} 
				else 
				{
					Rvector.erase(Rvector.begin() + Rvector.size() - 1);
					QRS_startvec.erase(QRS_startvec.begin() + QRS_startvec.size() - 1);
					QRS_endvec.erase(QRS_endvec.begin() + QRS_endvec.size() - 1);
					Rannovector.erase(Rannovector.begin() + Rannovector.size() - 1);
					RRvector.erase(RRvector.begin() + RRvector.size() - 1);
					//if the last wave is kept,and decide to drop this wave,but this wave is lower than last one, delete it.
				}
			}

			if (RRtemp >= 1.6 * RRmean_temp && Rannovector[Rannovector.size()- 1] != -2) 
			{//??????????????????????????м??????????????
				max_p = Rvector[Rvector.size() - 2] + (int) (0.25 * fs);
				min_p = max_p;
				max = buf->orig00[max_p];
				min = max;
				for (m = Rvector[Rvector.size() - 2] + (int) (0.25 * fs);m< Rvector[Rvector.size() - 1] - (int) (0.15 * fs); m++) 
				{
					if (buf->orig00[m] > max) 
					{
						max = buf->orig00[m];
						max_p = m;
					}
					if (buf->orig00[m] < min) 
					{
						min = buf->orig00[m];
						min_p = m;
					}
				}

				if (Rvector.size() > 1000)
					Rvalue_temp = (buf->orig00[Rvector[Rvector.size() - 1]]+ buf->orig00[Rvector[Rvector.size() - 2]]
				+ buf->orig00[Rvector[Rvector.size() - 3]]+ buf->orig00[Rvector[Rvector.size() - 4]]) / 4.0;
				else
					Rvalue_temp = buf->temp_Rvalue;

				if (max > 0.65 * fabs(Rvalue_temp) || (max - min > 0.7* buf->temp_maxdiff && (max > -0.9 * min))) 
				{//???????д???????????????????????????????????????????????????????2??RR??????????????????
					if (RRtemp >= 2.6 * RRmean_temp)//may be missed lots R
					{
						/*Rannovector[Rvector.size() - 1] = -2;
						Rannovector[Rvector.size() - 2] = -2;//-2 stands for there are noises nearby
						RRvector[RRvector.size() - 1] = (int) RRmean_temp;*///20161111
					} 
					else if ((max_p - Rvector[Rvector.size() - 2]) > 0.4 * fs&& (Rvector[Rvector.size() - 1] - max_p > 0.25 * fs)) 
					{//???????????2??RR????????????????
						if (abs(min_p - max_p) > (int) (0.06 * fs)) 
						{//????????С????????????趨QRS????0.15??
							Rvector.insert(Rvector.begin() + Rvector.size() - 1, max_p);
							QRS_startvec.insert(QRS_startvec.begin() + QRS_startvec.size()- 1, max_p - (int) (0.03 * fs));
							QRS_endvec.insert(QRS_endvec.begin() + QRS_endvec.size() - 1,max_p + (int) (0.12 * fs));
							Rannovector.insert(Rannovector.begin() + Rannovector.size()- 1, 0);
							RRvector[RRvector.size() - 1] = (int) ((max_p- Rvector[Rvector.size() - 3]) / fs * 1000);

							RRvector.push_back((int) ((Rvector[Rvector.size() - 1] - max_p)/ fs * 1000));

						} 
						else 
						{
							Rvector.insert(Rvector.begin() + Rvector.size() - 1, max_p);
							QRS_startvec.insert(QRS_startvec.begin() + QRS_startvec.size()- 1, max_p - (int) (0.03 * fs));
							QRS_endvec.insert(QRS_endvec.begin() + QRS_endvec.size() - 1,max_p + (int) (0.03 * fs));
							Rannovector.insert(Rannovector.begin() + Rannovector.size()- 1, 0);
							RRvector[RRvector.size() - 1] = (int) ((max_p- Rvector[Rvector.size() - 3]) / fs * 1000);

							RRvector.push_back((int) ((Rvector[Rvector.size() - 1] - max_p)/ fs * 1000));
						}
					}

				} 
				else if (min < -0.65 * fabs(Rvalue_temp) || (max - min > 0.7* buf->temp_maxdiff)) 
				{//???????м??и????????????????????????R??
					if (RRtemp >= 2.6 * RRmean_temp)//may be missed lots R
					{
						Rannovector[Rvector.size() - 1] = -2;
						Rannovector[Rvector.size() - 2] = -2;//-2 stands for there are noises nearby
						RRvector[RRvector.size() - 1] = (int) RRmean_temp;

					} 
					else if ((min_p - Rvector[Rvector.size() - 2]) > 0.4 * fs&& (Rvector[Rvector.size() - 1] - min_p > 0.25 * fs)) 
					{
						if (abs(min_p - max_p) > (int) (0.06 * fs)) 
						{
							Rvector.insert(Rvector.begin() + Rvector.size() - 1, min_p);
							QRS_startvec.insert(QRS_startvec.begin() + QRS_startvec.size()- 1, min_p - (int) (0.03 * fs));
							QRS_endvec.insert(QRS_endvec.begin() + QRS_endvec.size() - 1,min_p + (int) (0.12 * fs));
							Rannovector.insert(Rannovector.begin() + Rannovector.size()- 1, 0);
							RRvector[RRvector.size() - 1] = (int) ((min_p- Rvector[Rvector.size() - 3]) / fs * 1000);
							RRvector.push_back((int) ((Rvector[Rvector.size() - 1] - min_p)/ fs * 1000));

						} 
						else 
						{
							Rvector.insert(Rvector.begin() + Rvector.size() - 1, min_p);
							QRS_startvec.insert(QRS_startvec.begin() + QRS_startvec.size()- 1, min_p - (int) (0.03 * fs));
							QRS_endvec.insert(QRS_endvec.begin() + QRS_endvec.size() - 1,min_p + (int) (0.03 * fs));
							Rannovector.insert(Rannovector.begin() + Rannovector.size()- 1, 0);
							RRvector[RRvector.size() - 1] = (int) ((min_p- Rvector[Rvector.size() - 3]) / fs * 1000);
							RRvector.push_back((int) ((Rvector[Rvector.size() - 1] - min_p)/ fs * 1000));
						}
					}
				}
			}
		}
	}
	Rannolist->arr = (long *) malloc((Rvector.size()) * sizeof(long));
	if (NULL == Rannolist->arr) 
	{
		return new_RRlist;
	}
	new_RRlist.arr = (long *) malloc((RRvector.size()) * sizeof(long));
	if (NULL == new_RRlist.arr) 
	{
		return new_RRlist;
	}

	for (k = 0; k < Rvector.size() - 1; k++) 
	{
		Rlist->arr[k] = Rvector[k];
		QRS_startlist->arr[k] = QRS_startvec[k];
		QRS_endlist->arr[k] = QRS_endvec[k];
		Rannolist->arr[k] = Rannovector[k];
		new_RRlist.arr[k] = RRvector[k];
	}
	Rlist->arr[k] = Rvector[k];
	QRS_startlist->arr[k] = QRS_startvec[k];
	QRS_endlist->arr[k] = QRS_endvec[k];
	Rannolist->arr[k] = Rannovector[k];

	Rlist->count = Rvector.size();
	QRS_startlist->count = Rvector.size();
	QRS_endlist->count = Rvector.size();
	Rannolist->count = Rvector.size();
	new_RRlist.count = Rvector.size() - 1;

	if(ratehigh!=0&&ratelow!=0)
	{
		result->Fastest_Beat = (int) (60000 / ratehigh);
		result->Fastest_Time = ratehighpos;
		result->Slowest_Beat = (int) (60000 / ratelow);
		result->Slowest_Time = ratelowpos;

	}
	else
	{
		result->Fastest_Beat = 0;
		result->Fastest_Time = 0;
		result->Slowest_Beat = 0;
		result->Slowest_Time = 0;
	}


	Rvector.clear();
	QRS_startvec.clear();
	QRS_endvec.clear();
	Rannovector.clear();
	RRvector.clear();

	return new_RRlist;
}
DOUB_ARR maindetect::ECG_NO_NOISE2_A(double *ecglistarr, long ecglistnum,double fs)//9.5
{//????????????????????????????????????????????????????50?????????????ü??????????????
	DOUB_ARR ECG_NOlist;
	double *y1list;
	double *y2list;
	//DOUB_ARR xlist;

	int y1_y2_cnt = 0;
	int y1_y2_index1 = 0;
	int y1_index2 = 0;
	int i = 0;

	ECG_NOlist.arr = (double *) malloc((ecglistnum) * sizeof(double));
	ECG_NOlist.count = 0;
	if (NULL == ECG_NOlist.arr) 
	{
		return ECG_NOlist;
	}

	if (ecglistnum > 2000)//??????????
	{
		if ((int) (fs) == 250) 
		{
			y1list = (double *) malloc((161) * sizeof(double));
			if (NULL == y1list) 
			{
				free(ECG_NOlist.arr);
				ECG_NOlist.arr = NULL;
				return ECG_NOlist;
			}
			y2list = (double *) malloc((161) * sizeof(double));
			if (NULL == y2list) 
			{
				free(ECG_NOlist.arr);
				ECG_NOlist.arr = NULL;
				return ECG_NOlist;
			}
			for (i = 0; i < 160; i++) //dai20130503
			{
				y1list[i] = 0;
				y2list[i] = 0;
				ecglistarr[i] = 0;
				ECG_NOlist.arr[i] = 0;
			}

			y1_y2_cnt = 160;
			for (i = 160; i < ecglistnum; i++) 
			{
				if (5 > y1_y2_cnt)
					y1_y2_index1 = y1_y2_cnt + 156;
				else
					y1_y2_index1 = y1_y2_cnt - 5;
				if (160 == y1_y2_cnt)
					y1_index2 = y1_y2_cnt - 160;
				else
					y1_index2 = y1_y2_cnt + 1;

				y1list[y1_y2_cnt] = ecglistarr[i] - ecglistarr[i - 160]+ y1list[y1_y2_index1];
				y2list[y1_y2_cnt] = y1list[y1_y2_cnt] - y1list[y1_index2]+ y2list[y1_y2_index1];
				ECG_NOlist.arr[i - 155] = ecglistarr[i - 155]- (int) (y2list[y1_y2_cnt] / 1024);

				if (160 == y1_y2_cnt)
					y1_y2_cnt = 0;
				else
					y1_y2_cnt++;
			}
		}

		else if ((int) (fs) == 500) 
		{
			y1list = (double *) malloc((321) * sizeof(double));
			if (NULL == y1list) 
			{
				free(ECG_NOlist.arr);
				ECG_NOlist.arr = NULL;
				return ECG_NOlist;
			}
			y2list = (double *) malloc((321) * sizeof(double));
			if (NULL == y2list) 
			{
				free(ECG_NOlist.arr);
				ECG_NOlist.arr = NULL;
				return ECG_NOlist;
			}
			for (i = 0; i < 320; i++) //dai20130503
			{
				y1list[i] = 0;
				y2list[i] = 0;
				ecglistarr[i] = 0;
				ECG_NOlist.arr[i] = 0;
			}

			y1_y2_cnt = 320;
			for (i = 320; i < ecglistnum; i++) 
			{
				if (10 > y1_y2_cnt)
					y1_y2_index1 = y1_y2_cnt + 311;
				else
					y1_y2_index1 = y1_y2_cnt - 10;
				if (320 == y1_y2_cnt)
					y1_index2 = y1_y2_cnt - 320;
				else
					y1_index2 = y1_y2_cnt + 1;

				y1list[y1_y2_cnt] = ecglistarr[i] - ecglistarr[i - 320]+ y1list[y1_y2_index1];
				y2list[y1_y2_cnt] = y1list[y1_y2_cnt] - y1list[y1_index2]+ y2list[y1_y2_index1];
				ECG_NOlist.arr[i - 310] = ecglistarr[i - 310]- (int) (y2list[y1_y2_cnt] / 1024);

				if (320 == y1_y2_cnt)
					y1_y2_cnt = 0;
				else
					y1_y2_cnt++;
			}
		} 
		else if ((int) (fs) == 150) 
		{
			y1list = (double *) malloc((91) * sizeof(double));
			if (NULL == y1list) 
			{
				free(ECG_NOlist.arr);
				ECG_NOlist.arr = NULL;
				return ECG_NOlist;
			}
			y2list = (double *) malloc((91) * sizeof(double));
			if (NULL == y2list) 
			{
				free(ECG_NOlist.arr);
				ECG_NOlist.arr = NULL;
				return ECG_NOlist;
			}
			for (i = 0; i < 90; i++) //dai20130503
			{
				y1list[i] = 0;
				y2list[i] = 0;
				ecglistarr[i] = 0;
				ECG_NOlist.arr[i] = 0;
			}

			y1_y2_cnt = 90;
			for (i = 90; i < ecglistnum; i++) 
			{
				if (3 > y1_y2_cnt)
					y1_y2_index1 = y1_y2_cnt + 88;
				else
					y1_y2_index1 = y1_y2_cnt - 3;
				if (90 == y1_y2_cnt)
					y1_index2 = y1_y2_cnt - 90;
				else
					y1_index2 = y1_y2_cnt + 1;

				y1list[y1_y2_cnt] = ecglistarr[i] - ecglistarr[i - 90]+ y1list[y1_y2_index1];
				y2list[y1_y2_cnt] = y1list[y1_y2_cnt] - y1list[y1_index2]+ y2list[y1_y2_index1];
				ECG_NOlist.arr[i - 87] = ecglistarr[i - 87]- (int) (y2list[y1_y2_cnt] / 900);

				if (90 == y1_y2_cnt)
					y1_y2_cnt = 0;
				else
					y1_y2_cnt++;
			}
		}

		else 
		{
			free(ECG_NOlist.arr);
			ECG_NOlist.arr = NULL;
		}

		for (i = 0; i < 320; i++) 
		{
			ECG_NOlist.arr[i] = 0;
		}

		ECG_NOlist.count = ecglistnum;

		if (y1list) 
		{
			free(y1list);
			y1list = NULL;
		}
		if (y2list) 
		{
			free(y2list);
			y2list = NULL;
		}

	}

	return ECG_NOlist;
}

/*get tht RRlist for HRV analyse;the number of RRlist is the same;just find the normal RR, use the nearby RR for the abnormal RR*/
LONG_ARR maindetect::get_PSD_RRlist(LONG_ARR *RRlist, LONG_ARR *PSD_Rlist,LONG_ARR *Rlist, LONG_ARR *Rannolist, double fs, LONG_ARR *noiselist_A)//???????5????????
{//
	long i = 0;
	int j = 0;
	int start = 0;

	LONG_ARR PSD_RRlist;
	PSD_RRlist.arr = (long *) malloc((2000) * sizeof(long));
	if (NULL == PSD_RRlist.arr) 
	{
		return PSD_RRlist;
	}
	PSD_RRlist.count = 0;

	PSD_Rlist->arr = (long *) malloc((2000) * sizeof(long));
	if (NULL == PSD_Rlist->arr) 
	{
		free(PSD_RRlist.arr);
		PSD_RRlist.arr = NULL;
		return PSD_RRlist;
	}
	PSD_Rlist->count = 0;

	while (i < noiselist_A->count - 320) 
	{
		for (j = 0; j < 300; j++) 
		{
			if (noiselist_A->arr[i + j] != 0)
				break;
		}

		if (j == 300) 
		{
			start = i;//??????300?????????????
			break;
		}
		i = i + j;
		i++;
	}

	j = 0;
	for (i = 0; i < Rlist->count-1; i++) 
	{
		if (Rlist->arr[i] >= start * valuefs && (Rlist->arr[i] <= (start + 300)* valuefs)) 
		{
			if ((Rannolist->arr[i] == 0 ||Rannolist->arr[i] == 6||Rannolist->arr[i] == 11)
				&&( Rannolist->arr[i + 1] == 0 || Rannolist->arr[i + 1] == 6 ||Rannolist->arr[i + 1] == 11))//normal,VT,WS belong to normal RR
			{//??????з????????????????????
				PSD_RRlist.arr[j] = RRlist->arr[i];
				PSD_RRlist.count++;
				PSD_Rlist->arr[j] = Rlist->arr[i];
				PSD_Rlist->count++;
				j++;
			}
		}

		if (Rlist->arr[i] > (start + 300) * valuefs) 
		{
			break;
		}

	}
	return PSD_RRlist;
}
LONG_ARR maindetect::get_PSD_RRlist_all(LONG_ARR *RRlist, LONG_ARR *Rannolist,double fs)//???????5????????
{
	long i = 0;
	long j = 0;
	LONG_ARR PSD_RRlist;
	PSD_RRlist.arr = (long *) malloc((RRlist->count) * sizeof(long));
	if (NULL == PSD_RRlist.arr) 
	{
		return PSD_RRlist;
	}
	PSD_RRlist.count = 0;

	for (i = 0; i < RRlist->count; i++) 
	{
		if ((Rannolist->arr[i] == 0 ||Rannolist->arr[i] == 6||Rannolist->arr[i] == 11)
			&&( Rannolist->arr[i + 1] == 0 || Rannolist->arr[i + 1] == 6 ||Rannolist->arr[i + 1] == 11))//normal,VT,WS belong to normal RR
		{//???????????????
			PSD_RRlist.arr[j] = RRlist->arr[i];
			j++;
		}
	}
	PSD_RRlist.count = j;
	return PSD_RRlist;
}

// do not use
double maindetect::get_var(vector<double> ecgvector)//
{
	unsigned int k = 0;
	double ecgmean = 0;
	double var_ecgmean = 0;
	for (k = 0; k < ecgvector.size(); k++) 
	{
		ecgmean += ecgvector[k];
	}
	ecgmean = ecgmean / (ecgvector.size());
	for (k = 0; k < ecgvector.size(); k++) 
	{
		var_ecgmean += (ecgvector[k] - ecgmean) * (ecgvector[k] - ecgmean);
	}
	var_ecgmean = sqrt(var_ecgmean / (ecgvector.size()));
	return var_ecgmean;
}

//get the template (the condition:Rlist->count>10)
int maindetect::GET_TEMPLATE_NEW(LONG_ARR *Rlist, LONG_ARR *RRlist,struct data_buffer *buf, double fs, long ecgnum, long RRmean) 
{//?????????,??峤???0.5??R???0.1??R????0.4??????????6??RR???????????
	int i = 0;
	//	int j = 0;
	int k = 0;
	unsigned m = 0;
	int flag = 0;
	double ecgmean = 0;
	double temp_ecgmean = 0;
	double max = 0;
	double min = 0;
	buf->temp_mean = 0;
	buf->temp_maxdiff = 0;
	double temp_Rvalue = 0;
	vector<double> template1;
	vector<double> template2;
	vector<double> template3;
	vector<double> template4;

	vector<int> FLAGRlist;
	int flagfinish = 0;

	//	int flag1=0;
	//	int flag2=0;

	for (i = 0; i < RRlist->count - 2; i++) 
	{
		if (RRlist->arr[i + 1] > 0.7 * RRlist->arr[i] && RRlist->arr[i + 1]< 1.3 * RRlist->arr[i]) 
		{
			if (RRlist->arr[i] > 0.8 * RRmean && RRlist->arr[i] < 1.3 * RRmean)
				FLAGRlist.push_back(1);
			else
				FLAGRlist.push_back(0);
		} 
		else
			FLAGRlist.push_back(-1);
	}
	i = 0;
	while (i < RRlist->count - 6)//find the normal segment(continue 5 R wave) to get the ecgmean
	{
		if ((FLAGRlist[i] == 1) && (FLAGRlist[i + 1] == 1) && (FLAGRlist[i + 2]== 1) && (FLAGRlist[i + 3] == 1) && (FLAGRlist[i + 4] == 1)
			&& (FLAGRlist[i + 5] == 1)) 
		{
			for (k = Rlist->arr[i + 1] - (int) (0.1 * fs); k< Rlist->arr[i + 1] + (int) (fs * 0.4); k++)//for avoid the R_pos-FS/2<0
			{
				template1.push_back(buf->orig00[k]);
			}

			for (k = Rlist->arr[i + 2] - (int) (0.1 * fs); k< Rlist->arr[i + 2] + (int) (fs * 0.4); k++)//for avoid the R_pos-FS/2<0
			{
				template2.push_back(buf->orig00[k]);
			}

			if (Rlist->arr[i + 3] + (int) (fs * 0.4) >= ecgnum) 
			{
				flag = 2;
				for (k = Rlist->arr[i + 2] - (int) (0.1 * fs); k < Rlist->arr[i+ 2] + (int) (fs * 0.4); k++)//for avoid the R_pos-FS/2<0
				{
					template3.push_back(buf->orig00[k]);
					template4.push_back(buf->orig00[k]);
				}
			}
			if ((Rlist->arr[i + 4] + (int) (fs * 0.4) >= ecgnum) && (flag != 2)) 
			{
				for (k = Rlist->arr[i + 3] - (int) (0.1 * fs); k < Rlist->arr[i+ 3] + (int) (fs * 0.4); k++)//for avoid the R_pos-FS/2<0
				{
					template3.push_back(buf->orig00[k]);
					template4.push_back(buf->orig00[k]);
				}

			}
			if (flag == 0) 
			{
				for (k = Rlist->arr[i + 3] - (int) (0.1 * fs); k < Rlist->arr[i+ 3] + (int) (fs * 0.4); k++)//for avoid the R_pos-FS/2<0
				{
					template3.push_back(buf->orig00[k]);
				}
				for (k = Rlist->arr[i + 4] - (int) (0.1 * fs); k < Rlist->arr[i+ 4] + (int) (fs * 0.4); k++)//for avoid the R_pos-FS/2<0
				{
					template4.push_back(buf->orig00[k]);
				}

			}
			flagfinish = 1;
			break;
		}
		i = i + 1;
	}

	if (flagfinish != 1) {
		for (k = Rlist->arr[2] - (int) (0.1 * fs); k < Rlist->arr[2]+ (int) (fs * 0.4); k++)//for avoid the R_pos-FS/2<0
		{
			template1.push_back(buf->orig00[k]);
		}

		for (k = Rlist->arr[3] - (int) (0.1 * fs); k < Rlist->arr[3]+ (int) (fs * 0.4); k++)//for avoid the R_pos-FS/2<0
		{
			template2.push_back(buf->orig00[k]);
		}
		for (k = Rlist->arr[4] - (int) (0.1 * fs); k < Rlist->arr[4]+ (int) (fs * 0.4); k++)//for avoid the R_pos-FS/2<0
		{
			template3.push_back(buf->orig00[k]);
		}
		for (k = Rlist->arr[5] - (int) (0.1 * fs); k < Rlist->arr[5]+ (int) (fs * 0.4); k++)//for avoid the R_pos-FS/2<0
		{
			template4.push_back(buf->orig00[k]);
		}
	}

	for (m = 0; m < template1.size(); m++) 
	{
		buf->plate_data.push_back((template1[m] + template2[m] + template3[m] + template4[m]) / 4);
	}

	max = (int) (0.2 * fs);//??R????0.1???????????????T???????λ??
	buf->temp_Tvalue = buf->plate_data[(int) max];//2012.5.7 shangguan
	for (m = (unsigned int) (0.2 * fs); m < (unsigned int) (0.46 * fs); m++) 
	{
		if (buf->temp_Tvalue < buf->plate_data[m]) 
		{
			buf->temp_Tvalue = buf->plate_data[m];
			max = m;
		}
	}
	min = (int) (0.1 * fs);//??R?????????С???????S???????λ??
	buf->temp_Svalue = buf->plate_data[(int) min];//2012.5.7 shangguan
	for (m = (unsigned int) (0.1 * fs); m < (unsigned int) (0.3 * fs); m++) {

		if (buf->temp_Svalue > buf->plate_data[m]) 
		{
			buf->temp_Svalue = buf->plate_data[m];
			min = m;
		}
	}

	ecgmean = 0;
	for (m = 0; m < template1.size(); m++) 
	{
		temp_ecgmean += (buf->plate_data[m] - ecgmean) * (buf->plate_data[m]- ecgmean);
	}
	temp_ecgmean = sqrt(temp_ecgmean / (template1.size()));//??????
	temp_Rvalue = buf->plate_data[(int) (0.1 * fs)];//R??????

	buf->temp_Rvalue = temp_Rvalue;
	buf->temp_mean = temp_ecgmean;//the square mean of a template
	buf->temp_RT = (long) ((max - (int) (0.1 * fs)) / fs * 1000);
	if (buf->temp_RT < 100)
		buf->temp_RT = 100;//2012.4.26
	if(fabs(buf->temp_Tvalue)>0.8*fabs(buf->temp_Rvalue))
		buf->temp_RS = 1;//(long) ((min - (int) (0.1 * fs)) / fs * 1000);T????????????????R??
	else
		buf->temp_RS=0;
	if (fabs(buf->temp_Svalue - buf->temp_Rvalue) > fabs(buf->temp_Rvalue))
		buf->temp_maxdiff = fabs(buf->temp_Svalue - buf->temp_Rvalue);//the hight of QRS wave, consider the R is towards down
	else
		buf->temp_maxdiff = fabs(buf->temp_Rvalue);

	template1.clear();
	template2.clear();
	template3.clear();
	template4.clear();
	FLAGRlist.clear();

	return flagfinish;//if return 0, it shows the rawecg data is bad
}

int maindetect::GET_NEWRanno(int Ranno) 
{
	switch (Ranno) 
	{
	case 1:
		result.Arrest_Num--;

		break;
	case 2:
		result.Missed_Num--;

		break;
	case 3:
		result.PVB--;

		break;
	case 4:
		result.PAB--;

		break;
	case 5:
		result.Insert_PVBnum--;

		break;
	case 6:
		result.VT--;

		break;
	case 7:
		result.Bigeminy_Num--;

		break;
	case 8:
		result.Trigeminy_Num--;

		break;
	}
	return 0;
}

int maindetect::GET_NEWRannolist_NEW2013(LONG_ARR *Rlist, LONG_ARR *RRlist,LONG_ARR *Rannolist, struct data_buffer *buf, double fs, long ecgnum,long RRmean, LONG_ARR *QRSlist) 
{
	//????·???RR???????????????????????????????ж??α??????
	vector<double> RR_list;
	vector<double> Rhigh_list;
	vector<double> datatwoR_list;
	double temp = 0;
	int maxp = 0;
	double max = 0;
	int minp = 0;
	double min = 0;
	int noisenum = 0;
	// double Rhigh=0;
	int Rchange=0;

	int i = 0;
	int j = 0;
	int chaosnum = 0;
	int normalnum = 0;

	int start = 0;
	int end = 0;
	while (i < Rlist->count) 
	{

		/****????max, min, ecgmean, square_mean, ecgdiff*****/
		if ((Rannolist->arr[i] == 3 || Rannolist->arr[i] == 4|| Rannolist->arr[i] == 5) && (i >= 6)&& (i < Rlist->count - 7)) {
			chaosnum = 0;
			normalnum = 0;
			noisenum = 0;
			j = i - 6;
			while (j < i + 6)//R??????6????????????????????????RR??????????????????????????????????緿?綪??
			{
				Rchange=0;
				if ((Rannolist->arr[j] == 0||Rannolist->arr[j] == -1) && (Rannolist->arr[j + 1] == 0||Rannolist->arr[j + 1] == -1)) 
				{
					RR_list.push_back(RRlist->arr[j]);
					Rhigh_list.push_back(buf->orig00[Rlist->arr[j]]-buf->ecgmean);
					normalnum++;
				}
				if (Rannolist->arr[j] == -2)//???????????????
					noisenum++;
				j++;
			}

			if (RR_list.size() > 1) 
			{
				for (j = 0; j < (int) RR_list.size() - 1; j++) 
				{
					if ((RR_list[j + 1] > 1.3 * RR_list[j]) || (RR_list[j] > 1.3 * RR_list[j + 1]))
						chaosnum++;
					if (Rhigh_list[j + 1] * Rhigh_list[j]<0)
						Rchange++;

				}

			}

			if ((chaosnum > 0 && result.flagAR != 1 && (normalnum == 10|| normalnum == 9||Rchange>1)) || (noisenum > 0)) 
			{
				GET_NEWRanno(Rannolist->arr[i]);//?9???????????????????????
				Rannolist->arr[i] = -1;
				result.Wrong_Num++;

			}
			RR_list.clear();
			Rhigh_list.clear();
		}

		if (Rannolist->arr[i] == 3 || Rannolist->arr[i] == 4) 
		{
			if (fabs(buf->orig00[Rlist->arr[i]]) < 10) 
			{//??????С?????
				start = Rlist->arr[i] - (int) (valuefs * 0.06);
				end = Rlist->arr[i] + (int) (valuefs * 0.1);

				max = buf->orig00[start];
				min = buf->orig00[start];
				for (j = start + 1; j < end; j++) 
				{
					if (max < buf->orig00[j])
						max = buf->orig00[j];
					if (min > buf->orig00[j])
						min = buf->orig00[j];
				}

				if ((max - min) < 10 && ((max - min) < 0.5 * fabs(buf->temp_maxdiff))) 
				{//???????С???????????ж??????
					if (Rannolist->arr[i] == 4) 
					{
						result.PAB--;
						GET_NEWRanno(Rannolist->arr[i - 1]);
						Rannolist->arr[i - 1] = 0;
						Rannolist->arr[i] = -1;
						result.Wrong_Num++;

						GET_NEWRanno(Rannolist->arr[i + 1]);
						Rannolist->arr[i + 1] = 0;
					} else 
					{
						result.PVB--;
						GET_NEWRanno(Rannolist->arr[i - 1]);
						Rannolist->arr[i - 1] = 0;
						Rannolist->arr[i] = -1;
						result.Wrong_Num++;

						GET_NEWRanno(Rannolist->arr[i + 1]);
						Rannolist->arr[i + 1] = 0;
					}
				}
			}

			if (Rannolist->arr[i] == 3 || Rannolist->arr[i] == 4) 
			{
				for (j = Rlist->arr[i - 1] + (int) (0.15 * valuefs); j< Rlist->arr[i + 1] - 0.2 * valuefs; j++) 
				{
					temp = (buf->orig00[j] + buf->orig00[j + 1] + buf->orig00[j + 2]) / 3.0;
					datatwoR_list.push_back(temp);
				}//??????????????????????????????

				if (datatwoR_list.size() > 0.3 * valuefs) {
					max = 0;
					maxp = 0;
					min = 0;
					minp = 0;
					//?????????С??С???????????????R??λ???????????????????????????????????
					for (j = 0; j < (int) datatwoR_list.size() - 2; j++) 
					{
						if (datatwoR_list[j] - datatwoR_list[j + 2] > max) 
						{
							max = datatwoR_list[j] - datatwoR_list[j + 2];
							maxp = j;
						}
						if (datatwoR_list[j] - datatwoR_list[j + 2] < min) 
						{
							min = datatwoR_list[j] - datatwoR_list[j + 2];
							maxp = j;
						}
					}//???????в??????????С?
					maxp = Rlist->arr[i - 1] + (int) (0.15 * valuefs) + maxp;
					minp = Rlist->arr[i - 1] + (int) (0.15 * valuefs) + minp;

					if (maxp < minp)
						maxp = minp;//?????????????????R??λ???

					if (maxp > Rlist->arr[i] + 0.06 * valuefs) //???????????λ?????????????????????????????????????ж???????
					{
						RRlist->arr[i - 1] = (long) ((maxp - Rlist->arr[i - 1]) / fs * 1000);
						RRlist->arr[i] = (long) ((Rlist->arr[i + 1] - maxp) / fs * 1000);
						if (Rannolist->arr[i] == 4) 
						{
							result.PAB--;
							GET_NEWRanno(Rannolist->arr[i - 1]);
							Rannolist->arr[i - 1] = 0;
							Rannolist->arr[i] = -1;
							result.Wrong_Num++;
						} else 
						{
							result.PVB--;
							GET_NEWRanno(Rannolist->arr[i - 1]);
							Rannolist->arr[i - 1] = 0;
							Rannolist->arr[i] = -1;
							result.Wrong_Num++;
						}
					}
				}
				datatwoR_list.clear();
			}
		}

		if (Rannolist->arr[i] == 5)//?????????? ????????????
		{
			/*
			start=Rlist->arr[i]-valuefs*0.1;
			end=Rlist->arr[i]+valuefs*0.1;

			max=buf->orig00[start] ;
			min=buf->orig00[start];
			for (j=start+1;j<end;j++)
			{
			if(max<buf->orig00[j])
			max=buf->orig00[j];
			if(min>buf->orig00[j])
			min=buf->orig00[j];
			}

			if((max-min)<10&&((max-min)<0.5*fabs(buf->orig00[Rlist->arr[i+1]]-buf->ecgmean))
			&&((max-min)<0.5*fabs(buf->orig00[Rlist->arr[i-1]]-buf->ecgmean)))
			{
			RRlist->arr[i - 1] = RRlist->arr[i - 1]+RRlist->arr[i];
			RRlist->arr[i] = RRlist->arr[i - 1];

			result.Insert_PVBnum--;
			Rannolist->arr[i] = -1;
			result.Wrong_Num++;
			}
			*/

			if (fabs(buf->orig00[Rlist->arr[i]]) < 10 && (fabs(buf->orig00[Rlist->arr[i]]) < 0.5 * fabs(buf->orig00[Rlist->arr[i + 1]])) && (fabs(buf->orig00[Rlist->arr[i]]) < 0.5 * fabs(buf->orig00[Rlist->arr[i - 1]]))) 
			{
				RRlist->arr[i - 1] = RRlist->arr[i - 1] + RRlist->arr[i];
				RRlist->arr[i] = RRlist->arr[i - 1];

				result.Insert_PVBnum--;
				Rannolist->arr[i] = -1;
				result.Wrong_Num++;
			}
		}
		i++;
	}
	return 0;
}

int maindetect::GETHRVTI(long *pr, int **RRhis, int count) 
{
	int maxRR = 0;
	int i = 0;
	int j = 0;
	while (i < count) 
	{
		if (pr[i] > maxRR)
			maxRR = pr[i];
		i = i + 1;
	}
	i = 0;
	int nump = (int) (maxRR / 7.8125) + 1;
	int *pp = new int[nump];
	*RRhis = pp;
	//	FILE *file = fopen("HISR_result.txt", "w"); //! "C:/ecg/psd_RR_result.txt"
	while (j < nump) 
	{
		i = 0;
		pp[j] = 0;
		while (i < count) 
		{
			if ((pr[i] > 7.8125 * j) && (pr[i] <= 7.8125 * (j + 1))) 
			{
				pp[j]++;

			}
			i = i + 1;
		}
		//		fprintf(file,"%d\t", pp[j]);
		j = j + 1;
	}
	//	fclose(file);
	return nump;
}

string maindetect::getrelative(int type) 
{
	//SG
	string typestring;
	switch (type) 
	{
	case 1:
		typestring = "SA";
		break;
	case 2:
		typestring = "MB";
		break;
	case 3:
		typestring = "VPB";
		break;
	case 4:
		typestring = "APB";
		break;
	case 5:
		typestring = "IVBP";
		break;
	case 6:
		typestring = "VT";
		break;
	case 7:
		typestring = "BG";
		break;
	case 8:
		typestring = "TRG";
		break;
	case 9:
		typestring = "ST";
		break;
	case 10:
		typestring = "SB";
		break;
	case 11://SG
		typestring = "WS";
		break;

	case 12://LSJ
		typestring = "AR";

	}
	return typestring;
}
int* maindetect::getposL(LONG_ARR *Rannolist, int abNum, int abtype,LONG_ARR *Rlist, double fs) 
{//SG
	int ll;
	int j = 0;
	int *abpos = new int[abNum];//improve
	for (ll = 0; (ll < Rannolist->count) && (j < abNum); ll++) 
	{
		if (Rannolist->arr[ll] == abtype) 
		{
			abpos[j] = ll;
			j++;
		}
	}
	return abpos;
}
int maindetect::findnextpos(LONG_ARR *Rannolist, long pos) 
{
	int ll;
	int nextpos = 0;
	for (ll = pos; ll < Rannolist->count; ll++) 
	{
		if (Rannolist->arr[ll] != 0 && Rannolist->arr[ll] != -1) 
		{
			nextpos = ll;
			break;
		}
	}
	return nextpos;

}
int maindetect::getAbecgseg(LONG_ARR Rannolist, double *orig00, long ecgnum,LONG_ARR *Rlist, int length, double sample) 
{//???????????????????洢??????????
	int ll;
	int nextpos = 0;
	int start = 0;
	int end = 0;
	int Abseg = 0;
	char spos[10];
	char stime[10];
	long pos = 0;
	string stypestring;
	string stypespos;
	string segstime;
	int ARpos = 5;

	struct AbECG *useAbEcg = new AbECG[Rannolist.count];
	result.AbECG = useAbEcg;
	if (result.flagAR > 0) 
	{
		Abseg++;
		start = storeAbecgfile(ARpos, orig00, ecgnum, Rlist, result.AbECG,length, Abseg - 1);
		pos = 0;
		pos = Rlist->arr[ARpos];//error pos = Rlist->arr[result.Fastest_Beat]----value
		sprintf(stime, "%ld", (long) (start / sample)); // error
		segstime = string(stime);
		result.AbECG->AbECGTime = segstime;

		sprintf(spos, "%ld", pos - start); // 10xss
		stypespos = string(spos);

		result.AbECG->AbECGType = "AR:" + stypespos;
		result.AbECG++;
	}
	if (result.Polycardia > 0) 
	{
		Abseg++;
		start = storeAbecgfile(result.Fastest_Time, orig00, ecgnum, Rlist,result.AbECG, length, Abseg - 1);
		pos = 0;
		pos = Rlist->arr[result.Fastest_Time];//error pos = Rlist->arr[result.Fastest_Beat]----value
		sprintf(stime, "%ld", (long) (start / sample)); // error
		segstime = string(stime);
		result.AbECG->AbECGTime = segstime;

		sprintf(spos, "%ld", pos - start); // 10xss
		stypespos = string(spos);

		result.AbECG->AbECGType = "ST:" + stypespos;
		result.AbECG++;
	}
	if (result.Bradycardia > 0) 
	{
		Abseg++;
		start = storeAbecgfile(result.Slowest_Time, orig00, ecgnum, Rlist,result.AbECG, length, Abseg - 1);
		pos = 0;
		pos = Rlist->arr[result.Slowest_Time];//error pos = Rlist->arr[result.Slowest_Beat]
		sprintf(stime, "%ld", (long) (start / sample)); // // error
		segstime = string(stime);
		result.AbECG->AbECGTime = segstime;

		sprintf(spos, "%ld", pos - start); // 10xss
		stypespos = string(spos);

		result.AbECG->AbECGType = "SB:" + stypespos;
		result.AbECG++;
	}

	for (ll = 0; ll < Rannolist.count; ll++) 
	{
		while (Rannolist.arr[ll] == 0 || Rannolist.arr[ll] == -1) 
		{
			ll++;
		}
		if ((Rannolist.arr[ll] != 0) && (ll < Rannolist.count)) 
		{
			Abseg++;
			start = storeAbecgfile(ll, orig00, ecgnum, Rlist, result.AbECG,length, Abseg - 1);

			end = start + length;
			if (end >= ecgnum)
				end = ecgnum - 1;

			//sprintf(stype, "%d", Rannolist.arr[ll]); // 10xss
			stypestring = getrelative(Rannolist.arr[ll]);
			sprintf(spos, "%ld", Rlist->arr[ll] - start); // 10xss
			stypespos = string(spos);

			sprintf(stime, "%ld", (long) (start / sample)); // // error
			segstime = string(stime);
			result.AbECG->AbECGTime = segstime;

			result.AbECG->AbECGType = stypestring + ":" + stypespos;

		}
		while (Rlist->arr[ll] < end - 100) 
		{
			nextpos = findnextpos(&Rannolist, ll + 1);
			if (nextpos == 0) 
			{
				result.AbECG++;
				break;
			}

			if (Rlist->arr[nextpos] < end - 100) 
			{
				//	abnum++;
				//sprintf(stype, "%d", Rannolist.arr[nextpos]); // 10xss
				//stypestring = string(stype);
				stypestring = getrelative(Rannolist.arr[ll]);
				sprintf(spos, "%ld", Rlist->arr[nextpos] - start); // 10xss
				stypespos = string(spos);
				result.AbECG->AbECGType = result.AbECG->AbECGType + ","
					+ stypestring + ":" + stypespos;
			} else 
			{
				//LOG4CXX_DEBUG(logger, "&&&&&&&&&&&there is  a abnomal seg &&&&&&&&&&&&&&&...");
				result.AbECG++;
				break;
			}
			ll = nextpos;
		}

	}
	result.AbECG = useAbEcg;
	result.AbECGNum = Abseg;
	return 0;
}

int maindetect::storeAbecgfile(int pos, double *orig00, long ecgnum,LONG_ARR *Rlist, struct AbECG *abECG, int length, int Abnum) 
{

	ofstream ofs;

	long ll;
	long realpos = 0;
	long start = 0;
	long end = 0;
	realpos = Rlist->arr[pos];
	if ((realpos - (int) (length / 2)) > 0) 
	{
		start = realpos - (int) (length / 2);
	} else
		start = 0;

	if ((realpos + (int) (length / 2)) < ecgnum) 
	{
		end = realpos + (int) (length / 2);
		if (start == 0 && ecgnum > length)
			end = length;//LSJ
	} else
		end = ecgnum - 1;

	char s[4];
	sprintf(s, "%d", Abnum); // 10xss

	std::string Abnumstring = std::string(s);

	if (abECG)
		abECG->AbECGfile = filePath + Abnumstring + std::string(".txt");//+ Abnumstring  +

	if (end > start) 
	{

		ofs.open(abECG->AbECGfile.c_str(), ostream::app);

		for (ll = start; ll < end; ll++) 
		{
			ofs << orig00[ll];
			ofs << "\n";
		}
		ofs.close();
	} else 
	{
		return -1;
	}

	return start;
}

///////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////


LONG_ARR maindetect::getQRSWIDTHlist(LONG_ARR *QRS_startlist,LONG_ARR *QRS_endlist, double fs)//
{//???QRS?????????С??80?????????80????
	long i = 0;
	LONG_ARR QRSlist;
	QRSlist.arr = (long *) malloc((QRS_startlist->count) * sizeof(long));
	if (NULL == QRSlist.arr) 
	{
		return QRSlist;
	}
	QRSlist.count = 0;

	for (i = 0; i < QRS_startlist->count; i++) 
	{
		if (QRS_endlist->arr[i] * QRS_startlist->arr[i] == 0) 
		{
			QRSlist.arr[i] = 100;//LSJ
		} else 
		{
			QRSlist.arr[i] = (long) ((QRS_endlist->arr[i]
			- QRS_startlist->arr[i]) / fs * 1000);//
		}
		if (QRSlist.arr[i] < 80)
			QRSlist.arr[i] = 80;
		QRSlist.count++;
	}

	return QRSlist;
}
double maindetect::getmean(LONG_ARR *list) 
{
	double mean = 0;
	long i = 0;
	double sum = 0;
	for (i = 0; i < list->count; i++) 
	{
		sum += list->arr[i];
	}
	if (i != 0) 
	{
		mean = sum / i;
	}
	return mean;
}
double maindetect::getRRmean(LONG_ARR *RRlist)//ecg_result
{//RR???????????????Σ???????RRmean???????????RR??????????????е????????????????????????????
	double RRmean = 0;
	long i = 0;
	int k = 0;
	double sum = 0;
	for (i = 0; i < RRlist->count; i++) 
	{
		if (RRlist->arr[i] > 350 && RRlist->arr[i] < 1700) 
		{
			sum += RRlist->arr[i];
			k++;
		}
	}

	if (k < RRlist->count / 2)//???????????????????????RR??????????????
	{
		sum = 0;
		k = 0;
		for (i = 0; i < RRlist->count; i++) //?????????
		{
			if (RRlist->arr[i] > 200 && RRlist->arr[i] < 4000) 
			{
				sum += RRlist->arr[i];
				k++;
			}
		}
	}
	if(k==0)
		RRmean=4000;
	else
		RRmean = sum / k;

	return RRmean;
}

//RR

int maindetect::getothers(LONG_ARR *RRlist, LONG_ARR *QRSlist,LONG_ARR *Rannolist, ecg_result *result, double pvpercent,
						  double papercent, long arrest_time, long VT_value, LONG_ARR *Rlist,struct data_buffer *buf) 
{//RRlistQRSlist
	int i, j;
	double RRmeannew = 0;

	int dropnum = 0;
	int pv = 0;
	int pa = 0;
	int insertnum = 0;
	int widenum = 0;//SG
	int erlianlv = 0;
	int sanlianlv = 0;
	int shisu = 0;
	int arrest = 0;

	for (i = 0; i < 8; i++) 
	{
		RRmeannew += RRlist->arr[i];
	}
	RRmeannew = RRmeannew / 8.0;

	for (i = 1; i < RRlist->count - 1; i++) 
	{
		if (i >= 7) 
		{
			RRmeannew = 0;
			for (j = 0; j < 8; j++) 
			{
				RRmeannew += RRlist->arr[i - j];
			}
			RRmeannew = RRmeannew / 8.0;
		}

//		__android_log_print(ANDROID_LOG_INFO, "getothers "," RRlist->arr = %d,    %d", RRlist->arr[i], arrest_time);


		if (RRlist->arr[i] < arrest_time)//is not arrest
		{
			if ((i >= 2) && (i + 7 < RRlist->count)) 
			{
				/****?????ж?????????VT****/
				if (RRlist->arr[i] < (60000.0 / VT_value) && RRlist->arr[i + 1]< (60000.0 / VT_value) 
					&& RRlist->arr[i + 2] < (60000.0/ VT_value) && QRSlist->arr[i] > 130 
					&& QRSlist->arr[i+ 1] > 130 && QRSlist->arr[i + 2] > 130
					&& Rannolist->arr[i] != -2 && Rannolist->arr[i + 1]!= -2&& Rannolist->arr[i + 2] != -2 ) 
				{//?????qrs??????ж?????????????????????ж??????
					if (fabs(buf->orig00[Rlist->arr[i]] - buf->ecgmean) > 15&&fabs(buf->orig00[Rlist->arr[i+1]] - buf->ecgmean) > 15
						&&fabs(buf->orig00[Rlist->arr[i+1]] - buf->ecgmean) > 15
						&&fabs(buf->orig00[Rlist->arr[i]] - buf->ecgmean) > 0.8* fabs(buf->orig00[Rlist->arr[i - 1]]- buf->ecgmean) 
						&& fabs(buf->orig00[Rlist->arr[i + 1]] - buf->ecgmean)> 0.8 * fabs(buf->orig00[Rlist->arr[i - 1]]- buf->ecgmean)
						&& fabs(buf->orig00[Rlist->arr[i + 2]] - buf->ecgmean)> 0.8 * fabs(buf->orig00[Rlist->arr[i - 1]]- buf->ecgmean) 
						&& fabs(buf->orig00[Rlist->arr[i - 1]] - buf->ecgmean) > 6)//2012.3.23
					{
						shisu++;
						Rannolist->arr[i] = 6;
						if (Rannolist->arr[i + 1] != 1)//new sg
						{
							shisu++;
							Rannolist->arr[i + 1] = 6;
						}
						if (Rannolist->arr[i + 2] != 1)//new sg
						{
							shisu++;
							Rannolist->arr[i + 2] = 6;
						}
					}
					i = i + 2;//LSJ

				} //qrs width takes the value 0.13 for the noise

				/****?ж???????????****/
				else if (QRSlist->arr[i] > 125 && QRSlist->arr[i + 1] <120
					&& QRSlist->arr[i + 2] > 125 && QRSlist->arr[i + 3]<= 120
					&& QRSlist->arr[i + 4] > 125 && QRSlist->arr[i + 5] <= 120 
					&& Rannolist->arr[i] != -2 && Rannolist->arr[i + 1] != -2 
					&& Rannolist->arr[i + 2]!= -2 && Rannolist->arr[i + 3] != -2		
					&& Rannolist->arr[i + 4] != -2 && Rannolist->arr[i + 5]!= -2
					&&(RRlist->arr[i - 1] < (1 - pvpercent) * RRmeannew)
					&& (RRlist->arr[i + 1] < (1 - pvpercent)* RRmeannew)
					&& (RRlist->arr[i + 3] < (1- pvpercent) * RRmeannew)
					&& (RRlist->arr[i] > (1+ pvpercent) * RRmeannew) 
					&& (RRlist->arr[i + 2]> (1 + pvpercent) * RRmeannew)
					&& (RRlist->arr[i+ 4] > (1 + pvpercent) * RRmeannew))

				{
					erlianlv++;
					Rannolist->arr[i] = 7;
					if (Rannolist->arr[i + 2] != 1)//new sg
					{
						erlianlv++;
						Rannolist->arr[i + 2] = 7;
					}
					if (Rannolist->arr[i + 4] != 1)//new sg
					{
						erlianlv++;
						Rannolist->arr[i + 4] = 7;
					}
					i = i + 5;
					//if (erlianlv == 1)
					//	erlianlvpos = i;
				}

				/****?ж???????????****/
				else if (QRSlist->arr[i] > 125 && QRSlist->arr[i + 1] <= 120
					&& QRSlist->arr[i + 2] <= 120 && QRSlist->arr[i + 3]> 125 
					&& QRSlist->arr[i + 4] <= 120 && QRSlist->arr[i+ 5] <= 120 
					&& QRSlist->arr[i + 6] > 125&& QRSlist->arr[i + 7] <= 120 
					&& QRSlist->arr[i + 8] <= 120 && Rannolist->arr[i] != -2 
					&&(RRlist->arr[i + 2] < (1 - pvpercent) * RRmeannew)
					&& (RRlist->arr[i + 1] < 1.1 * RRmeannew)&& (RRlist->arr[i + 1] > 0.9 * RRmeannew)
					&& (RRlist->arr[i + 5] < (1 - pvpercent)* RRmeannew) 
					&& (RRlist->arr[i + 4] < 1.1* RRmeannew) && (RRlist->arr[i + 4] > 0.9* RRmeannew) 
					&& (RRlist->arr[i + 3] > (1+ pvpercent) * RRmeannew) 
					&& (RRlist->arr[i + 6]> (1 + pvpercent) * RRmeannew)
					&& Rannolist->arr[i+ 1] != -2 && Rannolist->arr[i + 2] != -2
					&& Rannolist->arr[i + 3] != -2 && Rannolist->arr[i + 4]!= -2 
					&& Rannolist->arr[i + 5] != -2&& Rannolist->arr[i + 6] != -2 
					&& Rannolist->arr[i + 7]!= -2 && Rannolist->arr[i + 8] != -2)

				{

					sanlianlv++;
					Rannolist->arr[i] = 8;
					if (Rannolist->arr[i + 3] != 1)//new sg
					{
						sanlianlv++;
						Rannolist->arr[i + 3] = 8;
					}
					if (Rannolist->arr[i + 6] != 1)//new sg
					{
						sanlianlv++;
						Rannolist->arr[i + 6] = 8;
					}
					i = i + 8;
				}
				/****?ж???????????????粫****/
				else if ((QRSlist->arr[i] >80)&&(QRSlist->arr[i]>1.25*QRSlist->arr[i-1]) &&(QRSlist->arr[i-1] < 120) 
					&& (abs(RRlist->arr[i - 1] + RRlist->arr[i]- RRlist->arr[i - 2]) < 0.3* RRlist->arr[i - 2] )
					&& (abs(RRlist->arr[i - 1] + RRlist->arr[i]- RRlist->arr[i + 1]) < 0.3* RRlist->arr[i + 1])//???????
					&& (fabs(buf->orig00[Rlist->arr[i]] - buf->ecgmean)>8 )
					&& (Rannolist->arr[i - 1] != -2 )&&( Rannolist->arr[i - 2]!= -2 )&& (Rannolist->arr[i] != -2) 
					&& (Rannolist->arr[i+ 1] != -2)) 
				{//???????????????????????
					insertnum++;
					Rannolist->arr[i] = 5;
					i = i + 1;
				}
				/****?ж??????????????????粫****/
				else if ((RRlist->arr[i - 1] < (1 - pvpercent) * RRlist->arr[i- 2]) 
					&& (RRlist->arr[i] < (1 - pvpercent) * RRmeannew)
					&& (RRlist->arr[i + 1] > (1 + pvpercent) * RRmeannew)
					&& (RRlist->arr[i + 1] > (1 + pvpercent)* RRlist->arr[i + 2]) 
					&& Rannolist->arr[i - 1]!= -2&& Rannolist->arr[i - 2] != -2 	
					&& Rannolist->arr[i] != -2 && Rannolist->arr[i + 1]!= -2 
					&& Rannolist->arr[i + 2] != -2) //new
				{
					if (QRSlist->arr[i - 1] < 120 && QRSlist->arr[i] >= 120
						&& QRSlist->arr[i + 1] >= 120 && QRSlist->arr[i + 2]< 120) 
					{

						pv++;
						Rannolist->arr[i] = 3;
						i++;
						if (Rannolist->arr[i] != 1)//new sg
						{
							pv++;
							Rannolist->arr[i] = 3;
						}
						i = i + 1;
					} 
					else if (QRSlist->arr[i - 1] < 120 && QRSlist->arr[i]< 120 && QRSlist->arr[i + 1] < 120
						&& QRSlist->arr[i + 2] < 120 && (RRlist->arr[i - 1]< (1 - papercent) * RRlist->arr[i - 2])
						&&((buf->orig00[Rlist->arr[i]]- buf->ecgmean)* (buf->orig00[Rlist->arr[i + 1]]- buf->ecgmean) > 0)) 
					{
						pa++;
						Rannolist->arr[i] = 4;
						i++;
						if (Rannolist->arr[i] != 1)//new sg
						{
							pa++;
							Rannolist->arr[i] = 4;
						}
						i = i + 1;
					}

				}
				/****?ж???????????????粫****/
				else if (RRlist->arr[i - 1] < (1 - pvpercent) * RRmeannew
					&& (RRlist->arr[i] > (1 + pvpercent) * RRlist->arr[i- 1]) 
					&& (RRlist->arr[i - 1] < (1 - pvpercent) *RRlist->arr[i- 2]) 
					&& Rannolist->arr[i] != -2 && Rannolist->arr[i- 1] != -2) 
				{
					if (QRSlist->arr[i] >= 120 )//20130507
					{
						if((RRlist->arr[i] > (1 + pvpercent) * RRmeannew)&&(fabs(buf->orig00[Rlist->arr[i]] - buf->ecgmean) >10))
						{//new shangguan
							pv++;
							Rannolist->arr[i] = 3;
							i = i + 1;
						}
					}
					else if(QRSlist->arr[i] < 120 )
					{

						if ((RRlist->arr[i] > (1 + pvpercent) * RRmeannew)
							&&(buf->orig00[Rlist->arr[i]] - buf->ecgmean)* (buf->orig00[Rlist->arr[i - 1]]- buf->ecgmean) < 0
							&& (buf->orig00[Rlist->arr[i]]- buf->ecgmean)* (buf->orig00[Rlist->arr[i + 1]]- buf->ecgmean) < 0
							&&(fabs(buf->orig00[Rlist->arr[i]] - buf->ecgmean) >10)) 
						{ //???????????????粫
							pv++;
							Rannolist->arr[i] = 3;
							i = i + 1;
						} 
						else if(RRlist->arr[i - 1] < (1 - papercent) * RRmeannew
							&& (RRlist->arr[i] > (1 + papercent) * RRlist->arr[i- 1])
							&&(buf->orig00[Rlist->arr[i]] - buf->ecgmean)* (buf->orig00[Rlist->arr[i - 1]]- buf->ecgmean)>0)
						{
							pa++;
							Rannolist->arr[i] = 4;
							i = i + 1;
						}


					}
				}

				/*
				if ((RRlist->arr[i] > (1 + pvpercent) * RRmeannew)
				&& fabs(buf->orig00[Rlist->arr[i]] - buf->ecgmean)
				< 1.3 * fabs(
				buf->orig00[Rlist->arr[i - 1]]
				- buf->ecgmean)
				&& (buf->orig00[Rlist->arr[i - 1]]
				- buf->ecgmean)
				* (buf->orig00[Rlist->arr[i]]
				- buf->ecgmean) > 0 && fabs(
				buf->orig00[Rlist->arr[i]] - buf->ecgmean) < 15) //?????仯???????????????????ж??????
				{//new shangguan
				pa++;
				Rannolist->arr[i] = 4;
				i = i + 1;
				} else if ((RRlist->arr[i] > (1 + pvpercent)
				* RRmeannew) && (fabs(
				buf->orig00[Rlist->arr[i]] - buf->ecgmean)
				> 0.5 * fabs(
				buf->orig00[Rlist->arr[i - 1]]
				- buf->ecgmean))) //improve new sg
				{//new shangguan
				pv++;
				Rannolist->arr[i] = 3;
				i = i + 1;
				}

				} else {
				if ((RRlist->arr[i] > ((1 + pvpercent) * RRmeannew))
				&& (RRlist->arr[i] > RRlist->arr[i + 1])
				&& (RRlist->arr[i] > RRlist->arr[i - 2])
				&& (QRSlist->arr[i - 1] < 120)
				&& (RRlist->arr[i - 1] < ((1 - pvpercent)
				* RRlist->arr[i - 2])) && fabs(
				buf->orig00[Rlist->arr[i]] - buf->ecgmean)
				> 0.5 * fabs(
				buf->orig00[Rlist->arr[i - 1]]
				- buf->ecgmean))//new shangguan

				{
				if ((buf->orig00[Rlist->arr[i]] - buf->ecgmean)
				* (buf->orig00[Rlist->arr[i - 1]]
				- buf->ecgmean) < 0
				&& (buf->orig00[Rlist->arr[i]]
				- buf->ecgmean)
				* (buf->orig00[Rlist->arr[i + 1]]
				- buf->ecgmean) < 0) { //???????????????粫
				pv++;
				Rannolist->arr[i] = 3;
				i = i + 1;
				} else {//???????μ???????粫
				pa++;
				Rannolist->arr[i] = 4;
				i = i + 1;
				}
				}
				}

				}*/
				/****?ж????????****/
				else if ((abs(RRlist->arr[i] - 2 * RRmeannew) < 0.4 * RRmeannew)
					&& (abs(RRlist->arr[i] - 2 * RRlist->arr[i - 1]) < 0.2* RRlist->arr[i - 1]) 
					&& (abs(RRlist->arr[i] - 2 * RRlist->arr[i + 1]) < 0.2* RRlist->arr[i + 1] 
				&& Rannolist->arr[i - 1] != -2&& Rannolist->arr[i] != -2 && Rannolist->arr[i + 1]!= -2)) 
				{
					if (RRlist->arr[i] < arrest_time) 
					{
						dropnum++;
						Rannolist->arr[i] = 2;
					}
				}
				/****?ж???????****/
				/*
				else if (       wideflag == 0 && QRSlist->arr[i] > 120
				&& QRSlist->arr[i + 1] > 120 && QRSlist->arr[i + 2]> 120
				&& QRSlist->arr[i + 3] > 120 && QRSlist->arr[i+ 4] > 120
				&& QRSlist->arr[i + 5] > 120&& QRSlist->arr[i + 6] > 120
				&& QRSlist->arr[i + 7]> 120   &&
				Rannolist->arr[i]!=-2&&
				Rannolist->arr[i+1]!=-2&&
				Rannolist->arr[i+2]!=-2&&
				Rannolist->arr[i+3]!=-2&&
				Rannolist->arr[i+4]!=-2&&
				Rannolist->arr[i+5]!=-2&&
				Rannolist->arr[i+6]!=-2&&
				Rannolist->arr[i+7]!=-2)
				{
				widenum++;
				Rannolist->arr[i] = 11;
				wideflag = 1;
				}
				*/

			} // end of ' if ((i >= 2) && (i + 7 < RRlist->count)) '
			else 
			{
				if (RRlist->arr[i - 1] < (1 - pvpercent) * RRmeannew) 
				{
					if (QRSlist->arr[i] > 120) 
					{
						if ((RRlist->arr[i] > (1 + pvpercent) * RRmeannew)&& (RRlist->arr[i] > ((1 + pvpercent)* RRlist->arr[i - 1]))) //improve new sg
						{
							pv++;
							Rannolist->arr[i] = 3;
							i = i + 1;
						}
					} 
					else 
					{
						if (RRlist->arr[i] > ((1 + pvpercent) * RRmeannew - 20)) 
						{
							pa++;
							Rannolist->arr[i] = 4;
							i = i + 1;
						}
					}
				} 
				else if ((abs(RRlist->arr[i] - 2 * RRmeannew) < 0.4* RRmeannew) 
					&& (abs(RRlist->arr[i] - 2 * RRlist->arr[i - 1]) < 0.2* RRlist->arr[i - 1]) 
					&& (abs(RRlist->arr[i] - 2 * RRlist->arr[i + 1]) < 0.2* RRlist->arr[i + 1])) 
				{
					if (RRlist->arr[i] < arrest_time) 
					{
						dropnum++;
						Rannolist->arr[i] = 2;
					}
				} 
				else if (i + 2 < RRlist->count) 
				{
					if (RRlist->arr[i] < (60000.0 / VT_value) && RRlist->arr[i+ 1] < (60000.0 / VT_value) && RRlist->arr[i + 2]< (60000.0 / VT_value) 
						&& QRSlist->arr[i] > 130&& QRSlist->arr[i + 1] > 130 && QRSlist->arr[i + 2]> 130) 
					{
						shisu++;
						Rannolist->arr[i] = 6;
						if (Rannolist->arr[i + 1] != 1)//new sg
						{
							shisu++;
							Rannolist->arr[i + 1] = 6;
						}

						if (Rannolist->arr[i + 2] != 1)//new sg
						{
							shisu++;
							Rannolist->arr[i + 2] = 6;
						}
						i = i + 2;//LSJ
					}//qrs width takes the value 0.13 for the noise
				}
			}
		} // end of ' if (RRlist->arr[i] < arrest_time) '
		else 
		{
			if (Rannolist->arr[i] != -2)
		{
				Rannolist->arr[i] = 1;
				//(ANDROID_LOG_INFO, "getothers "," Rannolist->arr = %d,    %d", RRlist->arr[i], arrest);
				arrest++;
			}
		}
	} // end of ' for (i = 1; i < RRlist->count - 1; i++) '


	result->PAB = pa;
	result->PVB = pv;
	result->Insert_PVBnum = insertnum;
	result->Missed_Num = dropnum;
	result->Wide_Num = widenum;//SG
	result->Bigeminy_Num = erlianlv;
	result->Trigeminy_Num = sanlianlv;
	result->VT = shisu;
	result->Arrest_Num = arrest;
	return 0;
}
////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////
int maindetect::fabsint(int a) 
{

	if (a >= 0)
		return a;
	else
		return -a;
}

int maindetect::pre_process_data(double **values, long num) 
{
	double *t;
	long l, w;

	/* because at the moment only a boxcar-filter is available, we do not need to check method setting */
	t = (double *) malloc(sizeof(double) * num);
	if (NULL == t) 
	{
		return -1;
	}

	w = 2;
	for (l = 0; l < (w - 1); l++)
		t[l] = (*values)[l];
	for (l = (w - 1); l < num; l++) 
	{
		long m;
		double s = 0.0;
		for (m = 0; m < w; m++)
			s += (*values)[l - m];
		t[l] = s / w;
	}
	free(*values);
	*values = t;

	return 0;
} /* pre_process_data() */
//include getdata,interpolate.
int maindetect::process_values(LONG_ARR *RRlist, LONG_ARR *Rlist,double **value, double samplerate_orig, double samplerate,long *real_num) 
{//??????????
	long l;
	*real_num = (long) (RRlist->count);

	double *pos = (double *) malloc(sizeof(double) * RRlist->count);
	if (NULL == pos) 
	{
		return -1;
	}

	*value = (double *) malloc(sizeof(double) * RRlist->count);
	if (NULL == value) 
	{
		return -1;
	}
	for (l = 0; l < RRlist->count; l++) 
	{
		(pos)[l] = (long) (Rlist->arr[l]) / samplerate_orig;//
		(*value)[l] = (long) (RRlist->arr[l]);
	}

	long num_i, idx_after;
	double *val_i, *pos_i;
	double range, pos_add, pos_before, pos_after, val_before, val_after,curr_pos;

	if ((samplerate <= 0.0) || (*real_num < 2))
		return -1;

	range = (pos)[*real_num - 1] - (pos)[0]; /* range is in seconds */
	num_i = (long) (range * samplerate);
	val_i = (double *) malloc(sizeof(double) * num_i);
	if (NULL == val_i) 
	{
		return -1;
	}
	pos_i = (double *) malloc(sizeof(double) * num_i);
	if (NULL == pos_i) 
	{
		return -1;
	}

	pos_add = 1 / samplerate;
	idx_after = 1;
	pos_before = (pos)[0];
	pos_after = (pos)[1];
	val_before = (*value)[0];
	val_after = (*value)[1];
	curr_pos = pos_before;
	for (l = 0; l < num_i; l++) 
	{
		double dist, slope;

		while (curr_pos > pos_after) 
		{
			idx_after++;
			if (idx_after >= *real_num)
				break;

			pos_before = (pos)[idx_after - 1];
			pos_after = (pos)[idx_after];
			val_before = (*value)[idx_after - 1];
			val_after = (*value)[idx_after];
		}
		if (idx_after >= *real_num)
			break;

		dist = curr_pos - pos_before;
		slope = (val_after - val_before) / (pos_after - pos_before);
		val_i[l] = val_before + slope * dist;
		pos_i[l] = curr_pos;
		curr_pos += pos_add;
	}

	*real_num = l;
	free(*value);
	free(pos);
	free(pos_i);
	*value = val_i;
	//*pos = pos_i;
	pre_process_data(value, *real_num);

	return 0;
} /* interpolate_values() */

LONG_ARR maindetect::getRRlist(LONG_ARR *Rlist, double fs)//
{
	long i = 0;
	LONG_ARR RRlist;
	RRlist.arr = (long *) malloc((Rlist->count - 1) * sizeof(long));
	if (NULL == RRlist.arr) 
	{
		return RRlist;
	}
	RRlist.count = 0;

	for (i = 0; i < Rlist->count - 1; i++) 
	{
		RRlist.arr[i]= (long) ((Rlist->arr[i + 1] - Rlist->arr[i]) / fs * 1000);//
		RRlist.count++;
//		__android_log_print(ANDROID_LOG_INFO, "getRRlist "," RRlist->arr = %d  %d", RRlist.arr[i], i);

	}

	return RRlist;
}

int maindetect::getAR_high(LONG_ARR *RRlist, LONG_ARR *Rannolist, double RRmean)//LSJ ???????????
{//????RR?????????????????????????RR????????????????ж?????????????????з???????
	long i = 0;
	LONG_ARR HRVlist;

	HRVlist.arr = (long *) malloc((RRlist->count - 1) * sizeof(long));
	
	HRVlist.count = 0;

	if (NULL == HRVlist.arr) 
	{
		return -1;
	}

	double HRVmean = 0;
	long HRVABnum = 0;
	int flagSA = 0;

	for (i = 0; i < RRlist->count - 1; i++) 
	{
		HRVlist.arr[i] = RRlist->arr[i + 1] - RRlist->arr[i];//
		HRVlist.count++;
	}
	for (i = 1; i < HRVlist.count; i++) 
	{
		if (abs(HRVlist.arr[i]) < 2000) 
		{
			if ((Rannolist->arr[i + 2] == 0 || Rannolist->arr[i + 2] == 4)
				&& (Rannolist->arr[i + 1] == 0) && (Rannolist->arr[i] == 0
				|| Rannolist->arr[i] == 4) && (Rannolist->arr[i - 1] == 0|| Rannolist->arr[i - 1] == 4)) 
			{
				HRVABnum = HRVABnum + 1;
				HRVmean += abs(HRVlist.arr[i]);
			}
		}
	}
	if(HRVABnum!=0)
		HRVmean /= HRVABnum;
	if (HRVmean > 0.10 * RRmean && HRVABnum > 5)
		flagSA = 1;

	free(HRVlist.arr);
	HRVlist.arr = NULL;

	return flagSA;
}

int maindetect::find_peaks(struct data_buffer *buf, double *sig_use,long start, long num, double threshold, double area_filt,
struct peak_buffer **peaks, long *num_peaks, long *morph_type,long ms30, int allow_look_before, int allow_look_after) 
{
	int ret = 0;
	int *flag = NULL;
	struct peak_buffer *p_temp = NULL;
	long l, m, idx, start_use, num_use;
	double max;
	int look_begin;

	if ((buf == NULL) || (sig_use == NULL) || (peaks == NULL) || (num_peaks== NULL) || (morph_type == NULL))
		return -1;

	*num_peaks = 0;
	start_use = start;
	num_use = num;

	if (allow_look_before) 
	{
		for (l = start_use; l >= 0; l--) 
		{
			if (fabs(sig_use[l]) <= threshold)
				break;
			if ((sig_use[l + 1] >= threshold) && (sig_use[l] <= threshold))
				break;
			if ((sig_use[l + 1] <= threshold) && (sig_use[l] >= threshold))
				break;
			start_use--;
			num_use++;
		}
	}
	if (allow_look_after) 
	{
		for (l = (start_use + num_use); l < buf->num_data; l++) 
		{
			if (fabs(sig_use[l]) <= threshold)
				break;
			if ((sig_use[l - 1] >= threshold) && (sig_use[l] <= threshold))
				break;
			if ((sig_use[l - 1] <= threshold) && (sig_use[l] >= threshold))
				break;
		}
		num_use = l - start_use + 1;

	}

	/* TODO: check why num_use can be negative */
	if (num_use > 0) 
	{
		flag = (int *) calloc(num_use, sizeof(int));
		if (!flag) 
		{
			printf("Not Enough Memory!\n");
			return 0;
		}

		for (l = 0; l < num_use; l++) 
		{
			if (sig_use[start_use + l] > threshold)
				flag[l] = 1;
			if (sig_use[start_use + l] < -threshold)
				flag[l] = -1;
		}
	}

	look_begin = 1;
	for (l = 1; l < num_use; l++)//
	{
		//SG &&(flag[l]!=0)
		if (flag[l] == flag[l - 1])
			continue;
		if (look_begin)//
		{
			if (flag[l] != 0)//SG
			{
				(*num_peaks)++;
				(*peaks) = (peak_buffer *) realloc(*peaks,sizeof(struct peak_buffer) * (*num_peaks));
				(*peaks)[*num_peaks - 1].start = l + start_use;//
				look_begin = 0;
			}
		} 
		else 
		{
			if (flag[l - 1] != 0)//SG
			{
				(*peaks)[*num_peaks - 1].end = l - 1 + start_use;//

				(*peaks)[*num_peaks - 1].amp= sig_use[(*peaks)[*num_peaks - 1].start];
				(*peaks)[*num_peaks - 1].idx = (*peaks)[*num_peaks - 1].start;
				for (m = ((*peaks)[*num_peaks - 1].start + 1); m < (l+ start_use); m++)//
				{
					if ((flag[l - 1] > 0) && (sig_use[m] > (*peaks)[*num_peaks- 1].amp)) 
					{
						(*peaks)[*num_peaks - 1].amp = sig_use[m];
						(*peaks)[*num_peaks - 1].idx = m;
					}
					if ((flag[l - 1] < 0) && (sig_use[m] < (*peaks)[*num_peaks- 1].amp)) 
					{
						(*peaks)[*num_peaks - 1].amp = sig_use[m];
						(*peaks)[*num_peaks - 1].idx = m;
					}
				}
			}

			/* check if we have a fast change (from one peak directly to the next one) */
			if (fabsint(flag[l - 1] - flag[l]) == 2) 
			{
				(*num_peaks)++;
				(*peaks) = (peak_buffer *) realloc(*peaks,sizeof(struct peak_buffer) * (*num_peaks));
				(*peaks)[*num_peaks - 1].start = l + start_use;
				look_begin = 0;
			} 
			else
				look_begin = 1;
		}
	}
	//************%%%%%%%%%%%%%%%%%%%%%%find the all the peaks
	/* check if a not finished peak is at the end; if yes, ignore it */
	if (look_begin == 0)
		(*num_peaks)--;

	if (flag)
		free(flag);
	//	if (debug) fprintf(stderr, "get peaks: found peaks = %ld\n", *num_peaks);

	if (*peaks == NULL) 
	{
		*num_peaks = 0;
		return 0;
	}

	if (*num_peaks >= 4) 
	{
		max = fabs((*peaks)[0].amp);
		idx = 0;
		for (l = 1; l < (*num_peaks); l++) 
		{
			if (fabs((*peaks)[l].amp) > max) 
			{
				max = fabs((*peaks)[l].amp);
				idx = l;
			}
		}

		for (l = idx + 1; l < (*num_peaks); l++) 
		{
			if ((*peaks)[l].idx - (*peaks)[l - 1].idx > 4 * ms30)//LSJ
			{
				*num_peaks = l;
				break;
			}
		}
		for (l = idx - 1; l >= 0; l--) 
		{
			if (-(*peaks)[l].idx + (*peaks)[l + 1].idx > 4 * ms30) 
			{
				*num_peaks -= (l + 1);
				memmove((*peaks), (*peaks) + l + 1,sizeof(struct peak_buffer) * (*num_peaks));
				break;
			}
		}
	}

	double sum4peak = 0;
	if (*num_peaks > 4) 
	{
		max = fabs((*peaks)[0].amp);
		idx = 0;
		for (l = 0; l < (*num_peaks) - 3; l++) 
		{
			sum4peak = fabs((*peaks)[l].amp) + fabs((*peaks)[l + 1].amp)+ fabs((*peaks)[l + 2].amp) + fabs((*peaks)[l + 3].amp);
			if (sum4peak > max) 
			{
				max = sum4peak;
				idx = l;
			}
		}
		memmove((*peaks), (*peaks) + idx, sizeof(struct peak_buffer) * 4);
		*num_peaks = 4;
	}

	/* get order of peaks */
	*morph_type = 0;
	for (l = 0; l < *num_peaks; l++)//21
	{
		if (l > 0)
			(*morph_type) *= 10;
		if ((*peaks)[l].amp > 0)
			(*morph_type) += 2;
		else
			(*morph_type) += 1;
	}

	if (p_temp)
		free(p_temp);

	return ret;
} /* get_peaks() */

int maindetect::get_peaks(struct data_buffer *buf, double *sig_use, long start,long num, double threshold, double area_filt,
struct peak_buffer **peaks, long *num_peaks, long *morph_type,/* long force_morph_type,*/long ms30, int allow_look_before, int allow_look_after) 
{
	int ret;
	//long num_peaks_force, *peak_positive;
	static int runs = 0; /* TODO: implement more save way to count iterations */
	//double threshold2, area_filt2;

	if (runs > 30)
		return 0;
	ret = find_peaks(buf, sig_use, start, num, threshold, area_filt, peaks,num_peaks, morph_type, ms30, allow_look_before, allow_look_after);
	return ret;
}
int maindetect::get_qrs_complex(double lastR, struct data_buffer *buf,long *curr_pos,/* int ch_idx,*/
								long ms100, long ms50, long ms30, /*long force_type,*/long *QRS_START,
								long *QRS_END, int noise) 
{//???R??????λ??
	int ret = 0;
	long l, m, start_pos, end_pos, pos;
	double threshold;
	struct peak_buffer *peaks;
	long num_peaks, morph_type;
	double *sig_use;
	long max_pos = 0;
	long min_pos = 0;

	/* select area where we look for the QRS complex */
	pos = *curr_pos;
	start_pos = (pos - buf->data_offset) - 4 * ms30;
	if (start_pos < 0)
		start_pos = 0;
	end_pos = (pos - buf->data_offset) + 2 * ms100;

	if (end_pos >= buf->num_data)
		end_pos = buf->num_data - 1;//LSJ


	/* s0 is better than s1 because when in the R or S wave is a notch(),
	this is seen as the end of the wave */
	sig_use = buf->s1;

	/* calculate the threshold */
	threshold = fabs(sig_use[start_pos]);
	for (l = start_pos; l <= end_pos; l++) 
	{
		if (fabs(sig_use[l]) > threshold)
			threshold = fabs(sig_use[l]);
	}
	if (noise == 0)//LSJ
		threshold *= 0.25;//SG0.25
	else
		threshold *= 0.4;//SG0.4

	/* get the peaks */
	peaks = NULL;

	get_peaks(buf, sig_use, start_pos, (end_pos - start_pos + 1), threshold,
		0.0, &peaks, &num_peaks, &morph_type, /*force_type,*/ms30, 1, 1);

	if (num_peaks <= 0) 
	{
		free(peaks);
		return -1;
	}

	/* and now look for the peak values in the original signal */

	double max_raw = buf->orig[peaks[0].start];

	double min_raw = buf->orig[peaks[0].start];

	max_pos = peaks[0].start;//LSJ
	min_pos = peaks[0].start;

	for (m = peaks[0].start; m <= peaks[num_peaks - 1].end; m++) 
	{
		if (buf->orig[m] > max_raw) 
		{
			max_raw = buf->orig[m];
			max_pos = m;

		}
		if (buf->orig[m] < min_raw) 
		{
			min_raw = buf->orig[m];
			min_pos = m;
		}
	}

	/*
	if (fabs((double)(*curr_pos-min_pos))<fabs((double)(*curr_pos-max_pos))&&(fabs((double)(*curr_pos-min_pos))<30))
	{
	*curr_pos = min_pos + buf->data_offset;
	}
	else if(fabs((double)(*curr_pos-min_pos))>=fabs((double)(*curr_pos-max_pos))&&(fabs((double)(*curr_pos-max_pos))<30))
	{
	*curr_pos = max_pos + buf->data_offset;
	}
	*/
	//LSJ
//???R??λ???????????????С???????
	if(((fabs(max_raw-buf->ecgmean)<6)&&(fabs(buf->ecgmean - min_raw)>2*fabs(max_raw-buf->ecgmean)))||(max_raw<buf->ecgmean)||((max_pos>min_pos+0.01*valuefs)&&(fabs(min_raw-buf->ecgmean)>0.6*fabs(max_raw-buf->ecgmean))&&(fabs(max_raw-buf->ecgmean)>0.6*fabs(buf->ecgmean - min_raw))))
		*curr_pos = min_pos + buf->data_offset;
	else 
		*curr_pos = max_pos + buf->data_offset;
	/*
	if (lastR < 0)//????????
	{
	if (max_raw - buf->ecgmean > 15)
	*curr_pos = max_pos + buf->data_offset;

	else if (((buf->ecgmean - min_raw) > -0.65 * lastR) && (fabs(
	buf->ecgmean - min_raw) > 15))
	*curr_pos = min_pos + buf->data_offset;

	else

	{
	if (fabs(
	(double) (buf->orig[*curr_pos - buf->data_offset] - min_raw))
	< fabs(
	(double) (buf->orig00[*curr_pos - buf->data_offset]
	- max_raw)) && (fabs(
	(double) (*curr_pos - buf->data_offset - min_pos)) < 30)) {
	if (fabs(min_raw - buf->ecgmean) > 1.2 * fabs(
	max_raw - buf->ecgmean))
	*curr_pos = min_pos + buf->data_offset;
	else
	*curr_pos = max_pos + buf->data_offset;

	} else if (fabs(
	(double) (buf->orig[*curr_pos - buf->data_offset] - min_raw))
	>= fabs(
	(double) (buf->orig[*curr_pos - buf->data_offset]
	- max_raw)) && (fabs(
	(double) (*curr_pos - buf->data_offset - max_pos)) < 30)) {
	*curr_pos = max_pos + buf->data_offset;
	}

	}

	} else if (lastR > 0) {
	if ((((max_raw - buf->ecgmean) > 0.65 * lastR) && (max_raw
	- buf->ecgmean > 5) && max_pos < min_pos) || (max_raw
	- buf->ecgmean > 15))
	*curr_pos = max_pos + buf->data_offset;
	else

	{
	if (fabs(
	(double) (buf->orig[*curr_pos - buf->data_offset] - min_raw))
	< fabs(
	(double) (buf->orig00[*curr_pos - buf->data_offset]
	- max_raw)) && (fabs(
	(double) (*curr_pos - buf->data_offset - min_pos)) < 30)) {
	if (fabs(min_raw - buf->ecgmean) > 1.2 * fabs(
	max_raw - buf->ecgmean))
	*curr_pos = min_pos + buf->data_offset;
	else
	*curr_pos = max_pos + buf->data_offset;

	} else if (fabs(
	(double) (buf->orig[*curr_pos - buf->data_offset] - min_raw))
	>= fabs(
	(double) (buf->orig[*curr_pos - buf->data_offset]
	- max_raw)) && (fabs(
	(double) (*curr_pos - buf->data_offset - max_pos)) < 30)) {
	*curr_pos = max_pos + buf->data_offset;
	}
	}
	} else {
	if (fabs((double) (buf->orig[*curr_pos - buf->data_offset] - min_raw))
	< fabs(
	(double) (buf->orig00[*curr_pos - buf->data_offset]
	- max_raw)) && (fabs(
	(double) (*curr_pos - buf->data_offset - min_pos)) < 30)) {
	if (fabs(min_raw - buf->ecgmean) > 1.2 * fabs(
	max_raw - buf->ecgmean))
	*curr_pos = min_pos + buf->data_offset;
	else
	*curr_pos = max_pos + buf->data_offset;
	} else if (fabs(
	(double) (buf->orig[*curr_pos - buf->data_offset] - min_raw))
	>= fabs(
	(double) (buf->orig[*curr_pos - buf->data_offset]
	- max_raw)) && (fabs(
	(double) (*curr_pos - buf->data_offset - max_pos)) < 30)) {
	*curr_pos = max_pos + buf->data_offset;
	}
	}
	*/
	//SG
	threshold = (0.8 * threshold);
	*QRS_START = peaks[0].start + buf->data_offset;
	for (l = peaks[0].start; l >= peaks[0].start - 30 && peaks[0].start > 43; l--) 
	{
		if (fabs(sig_use[l]) < threshold && fabs(sig_use[l - 1]) < threshold
			&& fabs(sig_use[l - 3]) < threshold && fabs(sig_use[l - 5])< threshold && fabs(sig_use[l - 8]) < threshold 
			&& fabs(sig_use[l - 12]) < threshold) 
		{
			*QRS_START = l + buf->data_offset;
			break;
		}
	}

	*QRS_END = peaks[num_peaks - 1].end + buf->data_offset;
	for (l = peaks[num_peaks - 1].end; l <= peaks[num_peaks - 1].end + 30
		&& peaks[num_peaks - 1].end < buf->num_data - 13; l++) 
	{
		if (fabs(sig_use[l]) < threshold && fabs(sig_use[l + 1]) < threshold
			&& fabs(sig_use[l + 3]) < threshold && fabs(sig_use[l + 5])
			< threshold && fabs(sig_use[l + 8]) < threshold && fabs(sig_use[l + 12]) < threshold) 
		{
			*QRS_END = l + buf->data_offset;
			break;
		}
	}

	//	*QRS_START = peaks[0].start + buf->data_offset;
	//
	//	*QRS_END = peaks[num_peaks - 1].end + buf->data_offset;
	free(peaks);
	return ret;
} /* get_qrs_complex() */

/*---------------------------------------------------------------*/
/* Design FIR filter using window method. Hamming window is used */
/* If sucess, return a point to the filter coefficient array,    */
/* otherwise, return NULL. Calling program should release the    */
/* allocated memory in this subroutine                           */
/*                                                               */
/*                                                               */
/*  Suppose sampling rate is 2 Hz                                */
/*                                                               */
/*  Len : filter length, should be ODD and Len>=3                */
/*  CutLow : low cutoff, when lowpass, CutLow = 0.0              */
/*  CutHigh: high cutoff, when highpass, CutHigh = 1.0           */
/*  when bandpass,    0.0 < CutLow < CutHigh < 1.0               */
/*                                                               */
/*  example:                                                     */
/*      Coef = fir_dsgn(127, 0.3, 0.8);                          */
/*   return a bandpass filter                                    */
/*---------------------------------------------------------------*/
int maindetect::fir_filter_design(long order, double cut_low, double cut_high,double **b, long *num) 
{
	double sum, temp;
	int coef_num, half_len, i;

	/*---------------------------------------------*/
	/* adjust the number of coefficients to be ODD */
	/*---------------------------------------------*/
	coef_num = order;
	if (order % 2 == 0) 
	{
		coef_num++;
	}
	*num = coef_num;
	half_len = (coef_num - 1) / 2;

	/*----------------------------------------------------*/
	/* Allocate memory for coefficients if length changed */
	/*----------------------------------------------------*/
	if (b == NULL)
		return -1;
	*b = (double *) malloc(sizeof(double) * coef_num);

	/*----------------*/
	/* Lowpass filter */
	/*----------------*/
	if ((cut_low == 0.0) && (cut_high < 1.0)) 
	{
		(*b)[half_len] = cut_high;
		for (i = 1; i <= half_len; i++) 
		{
			temp = PI * i;
			(*b)[half_len + i] = sin(cut_high * temp) / temp;
			(*b)[half_len - i] = (*b)[half_len + i];
		}

		/*---------------------------*/
		/* multiplying with a window */
		/*---------------------------*/
		temp = 2.0 * PI / (coef_num - 1.0);
		sum = 0.0;
		for (i = 0; i < coef_num; i++) 
		{
			(*b)[i] *= (0.54 - 0.46 * cos(temp * i));
			sum += (*b)[i];
		}

		/*---------------------*/
		/* Normalize GAIN to 1 */
		/*---------------------*/
		for (i = 0; i < coef_num; i++)
			(*b)[i] /= fabs(sum);

		return 0;
	} /* if Lowpass */

	/*-----------------*/
	/* Highpass filter */
	/*-----------------*/
	if ((cut_low > 0.0) && (cut_high == 1.0)) 
	{
		(*b)[half_len] = cut_low;
		for (i = 1; i <= half_len; i++) 
		{
			temp = PI * i;
			(*b)[half_len + i] = sin(cut_low * temp) / temp;
			(*b)[half_len - i] = (*b)[half_len + i];
		}

		/*---------------------------*/
		/* multiplying with a window */
		/*---------------------------*/
		temp = 2.0 * PI / (coef_num - 1.0);
		sum = 0.0;
		for (i = 0; i < coef_num; i++) 
		{
			(*b)[i] *= -(0.54 - 0.46 * cos(temp * i));
			if (i % 2 == 0)
				sum += (*b)[i]; /* poly(-1), even +, odd -*/
			else
				sum -= (*b)[i];
		}

		(*b)[half_len] += 1;
		sum += 1;

		/*---------------------*/
		/* Normalize GAIN to 1 */
		/*---------------------*/
		for (i = 0; i < coef_num; i++)
			(*b)[i] /= fabs(sum);

		return 0;
	} /* if HighPass */

	/*-----------------*/
	/* Bandpass filter */
	/*-----------------*/
	if ((cut_low > 0.0) && (cut_high < 1.0) && (cut_low < cut_high)) 
	{
		(*b)[half_len] = cut_high - cut_low;
		for (i = 1; i <= half_len; i++) 
		{
			temp = PI * i;
			(*b)[half_len + i] = 2.0 * sin((cut_high - cut_low) / 2.0 * temp)
				* cos((cut_high + cut_low) / 2.0 * temp) / temp;
			(*b)[half_len - i] = (*b)[half_len + i];
		}

		/*---------------------------*/
		/* multiplying with a window */
		/*---------------------------*/
		temp = 2.0 * PI / (coef_num - 1.0);
		sum = 0.0;
		for (i = 0; i < coef_num; i++) 
		{

			(*b)[i] *= (0.54 - 0.46 * cos(temp * i));
			sum += (*b)[i];
		}

		/*---------------------*/
		/* Normalize GAIN to 1 */
		/*---------------------*/
		for (i = 0; i < coef_num; i++)
			(*b)[i] /= fabs(sum);

		return 0;

	} /* if */

	/*-----------------*/
	/* Bandstop filter */
	/*-----------------*/
	if ((cut_low > 0.0) && (cut_high < 1.0) && (cut_low > cut_high)) 
	{
		(*b)[half_len] = cut_low - cut_high;
		for (i = 1; i <= half_len; i++) 
		{
			temp = PI * i;
			(*b)[half_len + i] = 2.0 * sin((cut_low - cut_high) / 2.0 * temp)* cos((cut_high + cut_low) / 2.0 * temp) / temp;
			(*b)[half_len - i] = (*b)[half_len + i];
		}

		/*---------------------------*/
		/* multiplying with a window */
		/*---------------------------*/
		temp = 2.0 * PI / (coef_num - 1.0);
		sum = 0.0;
		for (i = 0; i < coef_num; i++) 
		{
			(*b)[i] *= -(0.54 - 0.46 * cos(temp * i));
			sum += (*b)[i];
		}

		(*b)[half_len] += 1;
		sum += 1;

		/*---------------------*/
		/* Normalize GAIN to 1 */
		/*---------------------*/
		for (i = 0; i < coef_num; i++)
			(*b)[i] /= fabs(sum);

		return 0;
	}

	return -1;
} /* fir_filter_design() */

int maindetect::prepare_data_access(long do_interpolation, struct ecg_info *ci,struct data_buffer *buf)//13
{
	long temp = 0;
	if (do_interpolation && (ci->samplerate_orig < 500)) 
	{
		temp = (long) (ci->samplerate_orig) / 10;
		if (((ci->samplerate_orig / 10.0) - (double) temp) != 0)
			ci->interp_factor = 512 / (long) (ci->samplerate_orig);
		else
			ci->interp_factor = 500 / (long) (ci->samplerate_orig);
		ci->samplerate = ci->samplerate_orig * (double) (ci->interp_factor);
	}

	temp = (long) (ci->samplerate * 0.1);
	ci->ms100 = temp;
	if ((temp - (double) ci->ms100) >= 0.5)
		ci->ms100++;
	temp = (long) (ci->samplerate * 0.05);
	ci->ms50 = temp;
	if ((temp - (double) ci->ms50) >= 0.5)
		ci->ms50++;
	temp = (long) (ci->samplerate * 0.03);
	ci->ms30 = temp;
	if ((temp - (double) ci->ms30) >= 0.5)
		ci->ms30++;
	temp = (long) (ci->samplerate * 0.01);
	ci->ms10 = temp;
	if ((temp - (double) ci->ms10) >= 0.5)
		ci->ms10++;

	ci->s5 = (long) (5.0 * ci->samplerate);

	buf->orig = (double*) malloc(sizeof(double) * BUFFER_SIZE * ci->interp_factor);
	if (NULL == buf->orig) 
	{
		return -1;
	}
	buf->f0 = (double *) malloc(sizeof(double) * BUFFER_SIZE * ci->interp_factor);
	if (NULL == buf->f0) 
	{
		return -1;
	}
	buf->f1 = (double *) malloc(sizeof(double) * BUFFER_SIZE * ci->interp_factor);
	if (NULL == buf->f1) 
	{
		return -1;
	}
	buf->s1 = (double *) malloc(sizeof(double) * BUFFER_SIZE * ci->interp_factor);
	if (NULL == buf->s1) 
	{
		return -1;
	}

	return 0;
} /* prepare_data_access() */

int maindetect::filter(double *b, double *a, long order, double *data,long num_samples, int direction) 
{
	long l, m, curr, add;
	double *xv, *yv;
	double sum_a, sum_b;

	xv = (double *) calloc(order, sizeof(double));
	if (NULL == xv)
		return 0;
	yv = (double *) calloc(order, sizeof(double));
	if (NULL == yv)
		return 0;

	if (direction == 0) 
	{
		for (l = 0; l < order; l++)
			xv[l] = yv[l] = data[0];

		curr = 0;
		add = 1;
	} 
	else 
	{
		for (l = 0; l < order; l++)
			xv[l] = yv[l] = data[num_samples - 1];

		curr = num_samples - 1;
		add = -1;
	}

	for (l = 0; l < num_samples; l++) 
	{
		for (m = order - 1; m > 0; m--) 
		{
			xv[m] = xv[m - 1];
			yv[m] = yv[m - 1];
		}
		xv[0] = data[curr];

		sum_a = sum_b = 0.0;
		for (m = 0; m < order; m++) 
		{
			if (a && (m > 0))
				sum_a += (yv[m] * a[m]);
			sum_b += (xv[m] * b[m]);
		}
		yv[0] = sum_a + sum_b;

		data[curr] = yv[0];

		curr += add;
	}

	if (xv)
		free(xv);
	if (yv)
		free(yv);

	return 1;
} /* filter() */

int maindetect::filtfilt(double *b, double *a, long order, double *data,long num_samples) 
{
	int ret;

	if ((ret = filter(b, a, order, data, num_samples, 0)) != 1)
		return ret;

	if ((ret = filter(b, a, order, data, num_samples, 1)) != 1)
		return ret;

	return 1;
} /* filtfilt() */

int maindetect::interp(double *in, double *out, long num_samples, long factor) 
{
	int ret;
	long l;
	double *b = NULL;
	long num = 0;

	if ((in == NULL) || (out == NULL) || (num_samples <= 0) || (factor <= 0))
		return -1;
	if (factor == 1) 
	{
		memcpy(out, in, sizeof(double) * num_samples);
		return 0;
	}

	ret = fir_filter_design(2 * factor + 1, 0.0, 0.5 / factor, &b, &num);//???????????
	if (ret != 0)
		return ret;

	memset(out, 0, sizeof(double) * num_samples * factor);
	for (l = 0; l < num_samples; l++)
		out[l * factor] = (double) factor * in[l];

	ret = filtfilt(b, NULL, num, out, (num_samples * factor));

	free(b);

	return ret;
} /* interp() */
//LSJ
long maindetect::get_data_new(/*rec_handle rh, long ch,*/long ch_pos,
struct data_buffer *buf, long num_to_read, long interp_factor,double gain, int M_WIDTH, double H_HIGHT) 
{//???????????????????????任
	long l, num_read;
	double mean = 0.0;

	int ll = 0;
	long start = 0;
	num_read = num_to_read / interp_factor;
	memset((buf->orig), 0, BUFFER_SIZE * interp_factor);
	start = (long) (ch_pos / interp_factor);

	for (l = 0; l < num_read; l++) 
	{
		buf->orig[l] = buf->orig00[start];//LSJ
		start = start + 1;
		mean += buf->orig[l];
	}
	mean /= (double) num_read;
	buf->ecgmean = mean;
	if (buf->ecgmean > 20 || buf->ecgmean < -20)
		buf->ecgmean = 0;

	buf->num_data = num_read;
	if (num_read <= 0)
		return 0;
	/*
	if (interp_factor != 1) {
	double *buf_temp;

	buf_temp = (double *) malloc(sizeof(double) * num_read);
	memcpy(buf_temp, buf->orig, sizeof(double) * num_read);
	interp(buf_temp, buf->orig, num_read, interp_factor);

	num_read *= interp_factor;
	buf->num_data *= interp_factor;
	free(buf_temp);
	}
	*/
	double *Kvector = (double *) malloc(sizeof(double) * M_WIDTH);
	/*
	for(l=0;l<(M_WIDTH+1)/2;l++)
	{
	Kvector[l]=2*H_HIGHT/(M_WIDTH-1)*l;
	}
	for(l=(M_WIDTH+1)/2;l<M_WIDTH;l++)
	{
	Kvector[l]=-2*H_HIGHT/(M_WIDTH-1)*l+2*H_HIGHT;
	}
	*/
	Kvector[0] = 0.0;
	Kvector[1] = 50.0;//
	Kvector[2] = 100.0;//100.0
	Kvector[3] = 50.0;//
	Kvector[4] = 0.0;

	memcpy(buf->f0, buf->orig, sizeof(double) * num_read);
	memcpy(buf->f1, buf->orig, sizeof(double) * num_read);
	double fmin = 0;
	double fnew = 0;
	double fmax = 0;

	int j = 0;
	for (l = 0; l < num_read - M_WIDTH; l++) 
	{
		j = 0;
		fmin = buf->orig[l + j] - Kvector[j];
		for (j = 1; j < M_WIDTH; j++) 
		{
			fnew = buf->orig[l + j] - Kvector[j];
			if (fnew < fmin)
				fmin = fnew;
		}
		buf->f0[l] = fmin;

	}
	for (l = num_read - M_WIDTH; l < num_read; l++) 
	{
		buf->f0[l] = buf->orig[l] - 100;
	}
	//??????????

	for (l = 0; l < num_read - M_WIDTH; l++) 
	{
		j = 0;
		fmax = buf->f0[l + j] + Kvector[j];
		for (j = 1; j < M_WIDTH; j++) 
		{
			fnew = buf->f0[l + j] + Kvector[j];
			if (fnew > fmax)
				fmax = fnew;
		}
		buf->f1[l] = fmax;

	}
	for (l = num_read - M_WIDTH; l < num_read; l++) 
	{
		buf->f1[l] = buf->orig[l];
	}
	//???????????

	buf->s1mean = 0;
	for (ll = 0; ll < num_read; ll++) 
	{
		buf->s1[ll] = buf->orig[ll] - buf->f1[ll];
		buf->s1mean = buf->s1mean + fabs(buf->s1[ll]);
	}
	buf->s1mean = buf->s1mean / num_read;//NEW

	free(Kvector);//2012.3.7
	Kvector = NULL;

	return num_read;
}

long maindetect::look_for_next_beat(double *data, long num_data, long pos,double threshold, long blanktime, long ms30) 
{
	long next_beat = -1;
	long curr_pos = pos;
	long curr_blank = blanktime;
	long state_prev, state, last_peak_idx, last_peak;

	state = 0;
	last_peak_idx = pos;
	last_peak = 0;
	while (curr_pos < num_data) 
	{
		curr_blank--;
		curr_pos++;

		state_prev = state;
		if (data[curr_pos] > threshold)
			state = 1;
		else if (data[curr_pos] < -threshold)
			state = -1;
		else
			state = 0;

		if ((state == 0) && (state_prev != 0)) 
		{
			last_peak_idx = curr_pos - 1;
			last_peak = state_prev;
		}

		if ((state_prev == state) || (state == 0))
			continue;

		if (last_peak == state)
			continue;

		if ((curr_pos - last_peak_idx) > ms30) 
		{
			last_peak = state;
			last_peak_idx = curr_pos;
			continue;
		}

		if (curr_blank > 0)
			continue;

		next_beat = curr_pos;
		break;
	}

	return next_beat;
}
////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////
double maindetect::get_min(double *values, long num, long *pos) 
{
	long l, p;
	double min;

	min = values[0];
	p = 0;
	for (l = 1; l < num; l++) 
	{
		if (values[l] < min) 
		{
			min = values[l];
			p = l;
		}
	}
	if (pos)
		*pos = p;

	return min;
} /* get_min() */
double maindetect::get_max(double *values, long num, long *pos) 
{
	long l, p;
	double max;

	max = values[0];
	p = 0;
	for (l = 1; l < num; l++) 
	{
		if (values[l] > max) 
		{
			max = values[l];
			p = l;
		}
	}
	if (pos)
		*pos = p;

	return max;
} /* get_max() */

double maindetect::mean(double *values, long num) 
{
	long l;
	double mean = 0.0;

	for (l = 0; l < num; l++)
		mean += values[l];
	mean /= (double) num;

	return mean;
}

int maindetect::remove_mean(double * v, long n) 
{
	double m;
	long l;

	m = mean(v, n);
	for (l = 0; l < n; l++) 
	{
		v[l] -= m;
	}
	return 0;
}

int maindetect::histogram(double *values, long num, long **hist,long *hist_start, long *hist_size, int bin) 
{
	long l, min, max;

	if (bin <= 0)
		return -1;

	min = (long) (get_min(values, num, NULL));
	min -= (abs(min) % bin);
	max = (long) (get_max(values, num, NULL));
	max += (abs(max) % bin);

	*hist = NULL;
	*hist_size = (max - min) / bin;
	if (*hist_size <= 0)
		return 0;
	(*hist_size)++;

	*hist_start = min;
	*hist = (long *) calloc(sizeof(long), (*hist_size));

	for (l = 0; l < num; l++) 
	{
		long idx = ((long) values[l] - min);
		idx /= bin;
		if ((idx >= 0) && (idx < *hist_size))
			(*hist)[idx]++;
	}

	return 0;
} /* histogram */

double maindetect::stddev(double *values, long num) 
{
	long l;
	double s = 0.0;
	double m = mean(values, num);

	for (l = 0; l < num; l++) 
	{
		double t = values[l] - m;
		s += (t * t);
	}
	s /= (double) num;
	s = sqrt(s);

	return s;
} /* variance() */

double maindetect::calc_sdnn(LONG_ARR *RRlist) 
{
	long l;
	long num;
	double *v;
	num = RRlist->count;

	v = (double *) malloc(sizeof(double) * num);
	if (NULL == v)
		return -1;
	for (l = 0; l < num; l++)
		v[l] = RRlist->arr[l];

	double ret = stddev(v, num);
	free(v);
	v = NULL;
	return ret;
} /* calc_sdnn() */

double maindetect::calc_pnn50(LONG_ARR *RRlist) 
{
	long l, cnt;
	double *v;
	//long *hist;
	//long hist_start, hist_size;
	long num50 = 0;
	double r = 0;
	long num;
	num = RRlist->count;

	v = (double *) malloc(sizeof(double) * num);
	if (NULL == v)
		return -1;

	cnt = 0;
	for (l = 1; l < num; l++) 
	{
		v[cnt] = abs(RRlist->arr[l] - RRlist->arr[l - 1]);
		cnt++;
	}

	for (l = 0; l < cnt; l++)
	{
		if (v[l] >= 50)
			num50++;
	}

	r = ((double) num50 / (double) cnt) * 100.0;

	if (v)
		free(v);
	return r;
} /* calc_pnn50() */

double maindetect::calc_rmssd(LONG_ARR *RRlist) 
{
	long l, cnt;
	double *v;
	long num;
	num = RRlist->count;
	double r = 0;

	v = (double *) malloc(sizeof(double) * num);
	if (NULL == v)
		return -1;

	cnt = 0;
	for (l = 1; l < num; l++) 
	{
		double t;
		t = RRlist->arr[l] - RRlist->arr[l - 1];
		v[cnt] = t * t;
		cnt++;
	}
	r = sqrt(mean(v, cnt));
	free(v);
	return r;
} /* calc_rmssd() */

double maindetect::calc_hrvi(LONG_ARR *RRlist) 
{
	long l, max_pos;
	double *v, *hist_d;
	long *hist;
	long hist_start, hist_size;
	double scale;

	long num;
	num = RRlist->count;

	double r = 0;

	/* "scale" rri because hrvi-values are based on NN interval
	values with a binning of 7.8125 (128Hz samplerate) (see
	HRV Guidelines in Europaen Heart Journal (1996) 17, 354-381;
	on page 356 and 357); rr-intervals are in milliseconds */
	scale = 128.0 / 1000.0;

	v = (double *) malloc(sizeof(double) * num);
	if (NULL == v)
		return -1;

	for (l = 0; l < num; l++) 
	{
		v[l] = (RRlist->arr[l]) * scale;
		if ((v[l] - (long) v[l]) >= 0.5)
			v[l] += 1.0;
	}

	if (histogram(v, num, &hist, &hist_start, &hist_size, 1) != 0) 
	{
		free(v);
		return 0;
	}
	if (hist_size <= 0) 
	{
		free(v);
		free(hist);
		return 0;
	}

	/* copy histogram to double-array because get_max() needs a double-array
	(TODO: decide if histogram returns double-hist or add get_max_long()) */
	hist_d = (double *) malloc(sizeof(double) * hist_size);
	for (l = 0; l < hist_size; l++)
		hist_d[l] = hist[l];

	get_max(hist_d, hist_size, &max_pos);

	if (hist[max_pos] > 0) 
	{
		r = (double) num / hist[max_pos];
		//	ra_value_set_double(res, r);
	}

	free(v);
	free(hist);
	free(hist_d);
	return r;
} /* calc_hrvi() */

int maindetect::calc_poincare(LONG_ARR *RRlist, double *SD1, double *SD2) 
{
	long l, cnt;
	double *x, *y, *a;
	double mean_rri;
	long num;
	num = RRlist->count;

	x = (double *) malloc(sizeof(double) * num);
	if (NULL == x)
		return -1;
	y = (double *) malloc(sizeof(double) * num);
	if (NULL == y)
		return -1;

	cnt = 0;
	/*
	for (l = opt->poincare_lag; l < num; l++)
	{
	// only use successive rr-intervals
	if ((b[l].idx - b[l - opt->poincare_lag].idx) > opt->poincare_lag)
	continue;

	x[cnt] = b[l - opt->poincare_lag].rri;
	y[cnt] = b[l].rri;

	cnt++;
	}
	*/
	for (l = 1; l < num; l++) 
	{
		x[cnt] = RRlist->arr[l - 1];
		y[cnt] = RRlist->arr[l];
		cnt++;
	}

	/* calc SD1 */
	a = (double *) malloc(sizeof(double) * cnt);
	if (NULL == a)
		return -1;

	for (l = 0; l < cnt; l++) 
	{
		double t = y[l] - x[l];
		a[l] = sqrt((t * t) / 2.0);
	}
	*SD1 = stddev(a, cnt);

	/* calc SD2 */
	mean_rri = mean(x, cnt);
	for (l = 0; l < cnt; l++) 
	{
		double t = y[l] - (-x[l] + 2.0 * mean_rri);
		a[l] = sqrt((t * t) / 2.0);
	}
	*SD2 = stddev(a, cnt);

	free(a);
	free(x);
	free(y);

	return 0;
} /* calc_poincare() */
long calc_idx_from_freq(double samplefreq, long n_sample, double freq) 
{
	double freq_step;
	long idx;

	freq_step = samplefreq / (double) n_sample;
	idx = (long) ((freq / freq_step) + 0.5);

	return idx;
} /* calc_idx_from_freq() */
double maindetect::calc_power(double start, double end, double sample_dist_ms,DOUB_ARR *axislist, long n) 
{
	long start_idx, end_idx, l;
	double sum;
	double freq_step;
	/* don't use first value because start < x <= end */
	start_idx = calc_idx_from_freq((1000.0 / sample_dist_ms), n * 2, start) + 1;
	end_idx = calc_idx_from_freq((1000.0 / sample_dist_ms), n * 2, end);
	if (end_idx > n)
		end_idx = n;
	freq_step = (1000.0 / sample_dist_ms) / ((double) n * 2.0);
	sum = 0.0;

	for (l = start_idx; l <= end_idx; l++)
		sum += axislist->arr[l];
	sum *= freq_step;

	return sum;
} /* calc_power() */

void maindetect::window_hanning(double *v, long n, double *power) 
{
	long l;
	long n2 = n / 2;

	v[n - 1] = 0.0;

	*power = 0.0;
	for (l = -n2; l < n2; l++) 
	{
		v[l + n2] = 0.5 + 0.5 * cos(PI * (double) l / (double) n2);
		*power += (v[l + n2] * v[l + n2]);
	}
	*power /= (double) n;
} /* window_hanning() */

int maindetect::window_data(double *v, long n,/* char *window,*/double *w_power) 
{
	double *w;
	long l;

	w = (double *) malloc(sizeof(double) * n);
	memset(w, 0, sizeof(double) * n);

	*w_power = 1.0;
	window_hanning(w, n, w_power);

	/* because at the moment only a boxcar-filter is available, we do not need to check method setting */
	for (l = 0; l < n; l++) 
	{
		v[l] *= w[l];
	}
	free(w);
	return 0;
}

int maindetect::calc_fft(double *data, long n, complex *out) 
{
	int ret;
	long l;
	double *data_real, *data_complex;

	ret = 0;

	data_real = (double *) calloc(n, sizeof(double));
	if (NULL == data_real)
		return -1;
	data_complex = (double *) calloc(n, sizeof(double));
	if (NULL == data_complex)
		return -1;

	for (l = 0; l < n; l++)
		data_real[l] = data[l];

	ret = fft_sing(data_real, data_complex, n, n, n, 1);

	for (l = 0; l < (n / 2 + 1); l++) 
	{
		out[l].r = data_real[l];
		out[l].i = data_complex[l];
	}

	free(data_real);
	free(data_complex);

	return ret;
}

DOUB_ARR maindetect::calc_periodogram(double *values, long n,double samplefreq,/* double **spec,*/long *n_spec/*, int rm_mean, char *window*/) 
{
	long n_fft, l;
	double w_power = 1.0;
	complex *out = NULL;
	double *v_use = NULL;
	DOUB_ARR speclist;
	speclist.arr = NULL;
	double *v = NULL;
	v = (double *) calloc(n, sizeof(double));
	if (NULL == v)
		return speclist;

	for (l = 0; l < n; l++) 
	{
		v[l] = (double) (values[l]);
	}

	remove_mean(v, n);

	window_data(v, n,/* window,*/&w_power);

	if (*n_spec > n)
		n_fft = *n_spec;
	else
		n_fft = n;
	v_use = (double *) calloc(n_fft, sizeof(double));
	if (NULL == v_use)
		return speclist;
	memcpy(v_use, v, sizeof(double) * n);

	out = (complex *) malloc(sizeof(complex) * n_fft);
	if (NULL == out)
		return speclist;
	memset(out, 0, sizeof(complex) * n_fft);

	calc_fft(v_use, n_fft, out);

	if (((n_fft / 2) % 2) == 1)
		*n_spec = (n_fft + 1) / 2;
	else
		*n_spec = (n_fft / 2);

	speclist.arr = (double *) malloc((*n_spec) * sizeof(double));
	if (NULL == speclist.arr)
		return speclist;

	speclist.count = *n_spec;

	for (l = 0; l < (*n_spec); l++) 
	{
		/* correct spectrum regarding window-power and number of samples */
		speclist.arr[l] = (pow(out[l].r, 2.0) + pow(out[l].i, 2.0)) / (w_power * (double) n);
		if ((l != 0) && (l != (*n_spec - 1)))
			speclist.arr[l] *= 2.0;
		speclist.arr[l] /= samplefreq;
	}

	if (out)
		free(out);
	if (v_use)
		free(v_use);
	if (v) 
	{
		free(v);
		v = NULL;
	}

	return speclist;
} /* calc_periodogram() */

void maindetect::getQRSlist(LONG_ARR *Rlist, LONG_ARR *QRS_startlist,LONG_ARR *QRS_endlist, struct ecg_info *ci, struct data_buffer *buf) 
{

	int index_thi = 1;
	double m=0;
	long posR = 0;

	double lastR = 0;
	int num_read = 0;
	long ch_pos = 0;
	long curr_pos;
	long curr_pos_use = 0;
	long end_pos = 0;
	long l = 0;
	long blanktime = 0;
	long get_next_th = 0;
	int state_prev = 0;
	int state = 0;
	int last_peak = 0;
	long last_peak_idx = 0;
	long pos_offset = 0;
	//int ch_idx=0;

	long QRS_START = 0;
	long QRS_END = 0;

	long beat_range = 0;
	//LSJ
	double th_s1 = 0;//the biggest
	//	double th_s1_old = 0;//last time th_s1,for avoiding the hop
	//	double th_s2_old = 0;//last time th_s2
	double th_s2 = 0;
	double th_s1_m = 0;//the second biggest
	double th_s2_m = 0;

	double th_mean = 0;
	int noise = 0;//LSJ
	int ret = 0;

	long debug_temp1 = 0;
	long debug_temp2 = 0;
	//	long debug_temp3=0;

	double fs = ci->samplerate;
	int RR_downlimit = (int) (0.4 * fs);
	int RR_uplimit = (int) (1.5 * fs);
	int QR_len = (int) (0.1 * fs); //QR length
	int RT_len = (int) (0.15 * fs); //RT length
	int QT_len = QR_len + RT_len + 1; //QRST length
	int QRST_step = 1; // step length for cancelling QRST complex
	long Rnum_used = 8; //???????RR?????QRST???????????
	long valid_Rnum = 0;
	int RR_intral = 0;
	int RR_mean = 0;
	int QR_mean = 0;
	int RS_mean = 0;
	long data_start = 0;
	long data_end = 0;
	double MeanSquSum_error = 0;
	double MeanSquSum_error_Template = 0; //QRST????MeanSquSum_error?
	int Q_location = -1;
	double QRS_detec_thresh = 0.5; //????????????????R???????
	double temp_RR = 0;
	double temp_QR = 0;
	double temp_RS = 0;
	int k = 0;

	//	int curr_pos_1=0;

	double *temp_data;
	int dataNum = 0;
	int R_ptr = 0;
	double *QR_buffer;
	double *RS_buffer;
	double *RR_buffer;
	double *QRST_Template;
	double *QRST_buffer;
	int buffer_flag = 1; //???????????????λ 1??????????????

	QR_buffer = (double *) malloc(sizeof(double) * Rnum_used);
	RS_buffer = (double *) malloc(sizeof(double) * Rnum_used);
	RR_buffer = (double *) malloc(sizeof(double) * Rnum_used);
	QRST_buffer = (double *) malloc(sizeof(double) * (Rnum_used * QT_len));
	QRST_Template = (double *) malloc(sizeof(double) * QT_len);
	if ((NULL == RR_buffer) && (NULL == QRST_Template) && (NULL== QRST_Template)) //?????????????????????????
		buffer_flag = -1;

	beat_range = (long) (0.2 * ci->samplerate);//opt->min_beat_distance=0.2
	curr_pos = -1;
	blanktime = 0;
	state = state_prev = last_peak = 0;
	last_peak_idx = 0;
	get_next_th = 0;

	curr_pos = pos_offset * ci->interp_factor;
	end_pos = ci->num_samples * ci->interp_factor;//

	curr_pos = -1;

	if (curr_pos < -1)
		curr_pos = 0;

	ch_pos = curr_pos;
	Rlist->count = 0;
	QRS_startlist->count = 0;
	QRS_endlist->count = 0;

	Rlist->arr = (long *) malloc(((long) (ci->num_samples / ci->samplerate * 6)) * sizeof(long));//*5300/
	if (NULL == Rlist->arr)
		return;
	QRS_startlist->arr = (long *) malloc(((long) (ci->num_samples / ci->samplerate * 6)) * sizeof(long));
	if (NULL == QRS_startlist->arr)
		return;
	QRS_endlist->arr = (long *) malloc(((long) (ci->num_samples / ci->samplerate * 6)) * sizeof(long));
	if (NULL == QRS_endlist->arr)
		return;

	while (curr_pos < end_pos - 4) 
	{
		if (blanktime > 0)
			blanktime--;

		curr_pos++;

		if (curr_pos >= ch_pos) 
		{
			long num_to_read;
			long read_start = curr_pos;

			read_start -= (long) (ci->samplerate);
			if (read_start < 0)
				read_start = 0;

			num_to_read = BUFFER_SIZE;
			if ((end_pos - read_start) < num_to_read) 
			{
				num_to_read = end_pos - read_start;

			}
			if (num_to_read < ci->samplerate)
				break;
			//LSJ
			int M_WIDTH = 5;//5  sgwh
			double H_HIGHT = 100;//100  sgwh
			num_read = get_data_new(read_start, buf, num_to_read,ci->interp_factor, ci->gain, M_WIDTH, H_HIGHT);
			if (num_read <= ci->samplerate)
				break;
			buf->data_offset = read_start;
			ch_pos = read_start + num_read - (long)(ci->samplerate);

			if (num_to_read < BUFFER_SIZE)//getdata,
			{
				ch_pos = read_start + num_read;
			}

			get_next_th = 0;
		}

		get_next_th--;

		//	if (get_next_th <= 0)   //  ?????????    dai
		if (0 == (int) (curr_pos % ci->s5)) 
		{
			index_thi = (int) (curr_pos / ci->s5);
			//		while(index_thi<=buf->noiselist.count&&buf->noiselist.arr[index_thi-1]!=0)   //??????????????????????
/*			while ((index_thi + 1 <= buf->noiselist.count)&& (buf->noiselist.arr[index_thi] != 0))
			{
				curr_pos += ci->s5;
				if (curr_pos > ch_pos - 1) 
				{
					curr_pos = ch_pos - 1;
					index_thi++;
					break;
				}
				index_thi++;

			}*/
			if (curr_pos != ch_pos - 1) 
			{
				//		index_thi++;      //dai
				long start, num;

				start = curr_pos - buf->data_offset;
				if (start < 0)
					start = 0;
				num = ci->s5;
				if ((start + num) > buf->num_data)
					num = buf->num_data - start;

				th_s1 = 0.0;//+
				th_s2 = 0.0;//-
				th_s1_m = 0.0;
				th_s2_m = 0.0;
				for (l = start; l < (start + num); l++) 
				{
					//LSJ
					if (buf->s1[l] > th_s1_m)
						th_s1_m = buf->s1[l];
					if (buf->s1[l] < th_s1_m && buf->s1[l] > th_s1)
						th_s1 = buf->s1[l];
					if (buf->s1[l] < th_s2_m)
						th_s2_m = buf->s1[l];
					if (buf->s1[l] > th_s2_m && buf->s1[l] < th_s2)
						th_s2 = buf->s1[l];

				}

				th_mean = 0;
				int jjj = 0;
				for (l = start; l < (start + num); l++) 
				{
					//LSJ
					jjj = l;
					while (buf->s1[l] < 0.25 * th_s2_m || buf->s1[l] > 0.25* th_s1_m) 
					{
						l++;

					}
					if (jjj != l)
						th_mean += 1;
				}
				noise = 0;
				if (((th_mean > num * 0.1)&&(num==ci->s5)) || ((th_s1 < 5.0) && (th_s2 > -5.0)&&(num==ci->s5)))//??Щ???????????????
				{

					noise = 1;
				} else 
				{
					th_s1 = 0.26 * th_s1;//0.26

					th_s2 = 0.26 * th_s2;
				}
				//LSJ,find the second biggest

				get_next_th = ci->s5;
			}
		} // end of " if (get_next_th <= 0) "
		if (curr_pos != (ch_pos - 1) && (index_thi < buf->noiselist.count)) 
		{
			if (noise == 1) 
			{
				buf->noiselist.arr[index_thi] = 1;
				curr_pos += ci->s5 - 1;
				get_next_th = 0;//???5????????????????????????Σ?????
				noise = 0;

			} else 
			{
				state_prev = state;
				if (buf->s1[curr_pos - buf->data_offset] > th_s1
					&& buf->s1[curr_pos - buf->data_offset + 1] > th_s1
					/*&& buf->s1[curr_pos - buf->data_offset + 2] > th_s1&&buf->s1[curr_pos - buf->data_offset+3] > th_s1&&buf->s1[curr_pos - buf->data_offset+4] > th_s1*/)//LSJ
					state = 1;
				else if (buf->s1[curr_pos - buf->data_offset] < th_s2
					&& buf->s1[curr_pos - buf->data_offset + 1] < th_s2
					/*&& buf->s1[curr_pos - buf->data_offset + 2] < th_s2*/)//LSJ
					state = -1;
				else
					state = 0;

				if ((state == 0) && (state_prev != 0)) 
				{
					last_peak_idx = curr_pos - 1;
					last_peak = state_prev;
				}

				if ((state_prev == state) || (state == 0))
					continue;

				if (last_peak == state || last_peak == 0)//LSJ
					continue;

				if ((curr_pos - last_peak_idx) > ci->ms30 * 3.5) 
				{//LSJ.two peaks have long distance
					last_peak = state;
					last_peak_idx = curr_pos;
					continue;
				}

				if (blanktime > 0)
					continue;

				curr_pos_use = curr_pos;///////////////


				ret = 0;

				if (Rlist->count == 0) 
				{
					lastR = 0;
					Rlist->arr[Rlist->count] = curr_pos_use;
					ret = get_qrs_complex(lastR, buf, &curr_pos_use, ci->ms100,ci->ms50, ci->ms30, &QRS_START, &QRS_END, noise);
					Rlist->arr[Rlist->count] = curr_pos_use;//R
					QRS_startlist->arr[Rlist->count] = QRS_START;
					QRS_endlist->arr[Rlist->count] = QRS_END;

					Rlist->count++;
				} else 
				{

					posR = Rlist->arr[Rlist->count - 1];//
					lastR = buf->orig00[posR] - buf->ecgmean;//20130508

					ret = get_qrs_complex(lastR, buf, &curr_pos_use,ci->ms100, ci->ms50, ci->ms30, &QRS_START,&QRS_END, noise);

					if ((posR + beat_range) < curr_pos_use) 
					{
						Rlist->arr[Rlist->count] = curr_pos_use;
						//LOG4CXX_DEBUG(logger, "ecg detect----get a R wave position...");

						//LOG4CXX_DEBUG(logger, "ecg detect----after get a R position;get Q wave start position and S wave end position...");

						//if(curr_pos_use-posR>beat_range)//2012.2.8
						{
							Rlist->arr[Rlist->count] = curr_pos_use;
							QRS_startlist->arr[Rlist->count] = QRS_START;
							QRS_endlist->arr[Rlist->count] = QRS_END;
							Rlist->count++;
						}
					}
					else if ((posR - beat_range) > curr_pos_use)
					{
						Rlist->count--;
					}
					else if ((posR + beat_range) > curr_pos_use)//SG
					{

						//LOG4CXX_DEBUG(logger, "ecg detect----after get a R position;get Q wave start position and S wave end position...");
						if (fabs(buf->orig00[curr_pos_use ]) > 3.0* fabs(buf->orig00[posR ]))//erro
						{
							Rlist->count--;
							Rlist->arr[Rlist->count] = curr_pos_use;
							QRS_startlist->arr[Rlist->count] = QRS_START;
							QRS_endlist->arr[Rlist->count] = QRS_END;
							Rlist->count++;
						}
					}
				}
				blanktime = (int)(2.3 * ci->ms100);//SG
			}
		}
	}

	if ((end_pos - Rlist->arr[Rlist->count - 1]) < (long) (ci->samplerate_orig/ 2))//
		Rlist->count--;
	QRS_startlist->count = Rlist->count;
	QRS_endlist->count = Rlist->count;
	//	LOG4CXX_DEBUG(logger, "ecg detect----free some resources...");
	free(buf->orig);
	free(buf->f0);
	free(buf->f1);
	free(buf->s1);

	//! chenbk
	buf->orig = NULL;
	buf->f0 = NULL;
	buf->f1 = NULL;
	buf->s1 = NULL;

	if (QR_buffer) 
	{
		free(QR_buffer);
		QR_buffer = NULL;
	}
	if (RS_buffer) 
	{
		free(RS_buffer);
		RS_buffer = NULL;
	}
	if (RR_buffer) 
	{
		free(RR_buffer);
		RR_buffer = NULL;
	}
	if (QRST_Template) 
	{
		free(QRST_Template);
		QRST_Template = NULL;
	}
	if (QRST_buffer) 
	{
		free(QRST_buffer);
		QRST_buffer = NULL;
	}

}
void maindetect::getposL_perHour(long ECG_Num, int fs,ECG_Diagnose_resultAll ECG_Diagnose_resultTotal) 
{
	int count = 0;
	int i = 0;
	int k = 0;
	int pt = 0;

	int pvperhour = 0;

	long HeartNum; //????????

	long PAB_Num = 0; //?????粫????
	long PVB_Num = 0; // ?????粫????
	int Insert_PVB_Num = 0; //?????????????
	int Bigeminy_Num = 0; //?????????
	int Trigeminy_Num = 0; // ?????????
	int Arrest_Num = 0; // ???????
	int Missed_Num = 0; //52 ???????
	int VT_Num = 0; //??????????????

	int NonNoise_num = 0;
	double RRmean = 0;
	int R_count = 0;
	LONG_ARR RRlist_ptr;
	int group_num = 0; //???????????С???

	int truetime = 0;

	ECG_Diagnose_resultPerHour *Diagnose_resultPerHour; //定义的返回值

	group_num = ECG_Num / (3600 * fs); //确定小时数
	if (0 != ECG_Num % (3600 * fs))
		group_num += 1;

	for (i = 0; i < ECG_Diagnose_resultTotal.Noiselist.count; i++) 
	{
		if (ECG_Diagnose_resultTotal.Noiselist.arr[i] == 0)
			truetime++;
	}
	if (truetime != 0)
		pvperhour = (int) ((ECG_Diagnose_resultTotal.Bigeminy_Num
		+ ECG_Diagnose_resultTotal.Trigeminy_Num+ ECG_Diagnose_resultTotal.PVB_Num
		+ ECG_Diagnose_resultTotal.Insert_PVB_Num) / truetime * 60);//平均每分钟室早数目

	Diagnose_resultPerHour = (ECG_Diagnose_resultPerHour *) malloc(group_num * sizeof(ECG_Diagnose_resultPerHour)); //申请内存空间
	if (NULL == Diagnose_resultPerHour) //申请空间失败，返回
	{
		result.Diagnose_resultPerHourList.arr = NULL;
		result.Diagnose_resultPerHourList.count = 0;
		return;
	}

	for (i = 0; i < group_num; i++) //?????Diagnose_resultPerHour
	{
		(Diagnose_resultPerHour + i)->Abnormal_HeartNum = 0;
		(Diagnose_resultPerHour + i)->Arrest_Num = 0;
		(Diagnose_resultPerHour + i)->Bigeminy_Num = 0;
		(Diagnose_resultPerHour + i)->HeartNum = 0;
		(Diagnose_resultPerHour + i)->HeartRate = 0;
		(Diagnose_resultPerHour + i)->Insert_PVB_Num = 0;
		(Diagnose_resultPerHour + i)->Missed_Num = 0;
		(Diagnose_resultPerHour + i)->PAB_Num = 0;
		(Diagnose_resultPerHour + i)->PVB_Num = 0;
		(Diagnose_resultPerHour + i)->Trigeminy_Num = 0;
		(Diagnose_resultPerHour + i)->Valid_Sample_duration = 0;
		(Diagnose_resultPerHour + i)->VT_Num = 0;
	}

	for (i = 0; i < group_num - 1; i++) // ???Valid_Sample_duration
	{
		NonNoise_num = 0;
		for (k = 0; k < 3600; k++) //  Noiselist????????1s??????С?3600s
		{
			if (0 == ECG_Diagnose_resultTotal.Noiselist.arr[i * 3600 + k])
				NonNoise_num++;
		}
		(Diagnose_resultPerHour + i)->Valid_Sample_duration = NonNoise_num;
	}
	if ((group_num - 1) * 3600 <= ECG_Diagnose_resultTotal.Noiselist.count) 
	{
		NonNoise_num = 0;
		for (k = (group_num - 1) * 3600; k< ECG_Diagnose_resultTotal.Noiselist.count; k++) 
		{
			if (0 == ECG_Diagnose_resultTotal.Noiselist.arr[k])
				NonNoise_num++;
		}
		(Diagnose_resultPerHour + group_num - 1)->Valid_Sample_duration = NonNoise_num;
	}

	count = 0; // ???HeartNum
	HeartNum = 0;
	for (i = 0; i < ECG_Diagnose_resultTotal.Rlist.count; i++) 
	{
		if (ECG_Diagnose_resultTotal.Rlist.arr[i] < (count + 1) * 3600 * fs) // Rlist?????????????????λ
			HeartNum++;
		else 
		{
			if (count <= group_num - 1) 
			{
				(Diagnose_resultPerHour + count)->HeartNum = HeartNum;
				HeartNum = 1;
				count++;
			} else
				//?д???
				break;
		}
	}
	if ((i == ECG_Diagnose_resultTotal.Rlist.count) && (count <= group_num - 1))
		(Diagnose_resultPerHour + count)->HeartNum = HeartNum;

	count = 0; // ???HeartRate
	if (ECG_Diagnose_resultTotal.RRlist.count + 1!= ECG_Diagnose_resultTotal.Rlist.count) // Rlist ??RRlist???????????????????
	{
		result.Diagnose_resultPerHourList.arr = NULL;
		result.Diagnose_resultPerHourList.count = 0;
		return;
	} 
	else 
	{
		pt = 0;
		for (i = 0; i < group_num; i++) 
		{
			RRlist_ptr.arr = &(ECG_Diagnose_resultTotal.RRlist.arr[pt]);
			RRlist_ptr.count = (Diagnose_resultPerHour + i)->HeartNum - 1;
			RRmean = getRRmean(&RRlist_ptr);
			R_count = (Diagnose_resultPerHour + i)->HeartNum;
			if (RRmean > 0)
				(Diagnose_resultPerHour + i)->HeartRate = (long) (60000/ RRmean);
			else 
			{
				if (R_count > 1)
					(Diagnose_resultPerHour + i)->HeartRate = (long) ((R_count- 1)/ ((double) (ECG_Diagnose_resultTotal.RRlist.arr[pt+ R_count - 1]
				- ECG_Diagnose_resultTotal.RRlist.arr[pt])/ fs) * 60);
				else
					(Diagnose_resultPerHour + i)->HeartRate = 0;
			}
			pt += (Diagnose_resultPerHour + i)->HeartNum;
		}
	}

	count = 0; // ???Arrest_Num
	Arrest_Num = 0;
	for (i = 0; i < ECG_Diagnose_resultTotal.Arrest_Num; i++) 
	{
		for (count = 0; count < group_num; count++) 
		{
			if ((ECG_Diagnose_resultTotal.Rlist.arr[ECG_Diagnose_resultTotal.Arrest_posL[i]]>= (count) * 3600 * fs)
				&& (ECG_Diagnose_resultTotal.Rlist.arr[ECG_Diagnose_resultTotal.Arrest_posL[i]]< (count + 1) * 3600 * fs))

				(Diagnose_resultPerHour + count)->Arrest_Num= (Diagnose_resultPerHour + count)->Arrest_Num + 1;
		}

	}

	count = 0; // ???Missed_Num
	Missed_Num = 0;
	for (i = 0; i < ECG_Diagnose_resultTotal.Missed_Num; i++) 
	{
		for (count = 0; count < group_num; count++) 
		{
			if ((ECG_Diagnose_resultTotal.Rlist.arr[ECG_Diagnose_resultTotal.Missed_posL[i]]>= (count) * 3600 * fs)
				&& (ECG_Diagnose_resultTotal.Rlist.arr[ECG_Diagnose_resultTotal.Missed_posL[i]]<(count + 1) * 3600 * fs))

				(Diagnose_resultPerHour + count)->Missed_Num= (Diagnose_resultPerHour + count)->Missed_Num + 1;
		}

	}

	count = 0; //???PAB_Num
	PAB_Num = 0;
	for (i = 0; i < ECG_Diagnose_resultTotal.PAB_Num; i++) 
	{

		for (count = 0; count < group_num; count++) 
		{
			if ((ECG_Diagnose_resultTotal.Rlist.arr[ECG_Diagnose_resultTotal.PABposL[i]]>= (count) * 3600 * fs)
				&& (ECG_Diagnose_resultTotal.Rlist.arr[ECG_Diagnose_resultTotal.PABposL[i]]< (count + 1) * 3600 * fs))

				(Diagnose_resultPerHour + count)->PAB_Num
				= (Diagnose_resultPerHour + count)->PAB_Num + 1;
		}

	}

	count = 0; //???PVB_Num
	PVB_Num = 0;
	for (i = 0; i < ECG_Diagnose_resultTotal.PVB_Num; i++) 
	{
		for (count = 0; count < group_num; count++) 
		{
			if ((ECG_Diagnose_resultTotal.Rlist.arr[ECG_Diagnose_resultTotal.PVBposL[i]]>= (count) * 3600 * fs)
				&& (ECG_Diagnose_resultTotal.Rlist.arr[ECG_Diagnose_resultTotal.PVBposL[i]]< (count + 1) * 3600 * fs))

				(Diagnose_resultPerHour + count)->PVB_Num= (Diagnose_resultPerHour + count)->PVB_Num + 1;
		}

	}

	count = 0; //???Insert_PVB_Num
	Insert_PVB_Num = 0;
	for (i = 0; i < ECG_Diagnose_resultTotal.Insert_PVB_Num; i++) 
	{
		for (count = 0; count < group_num; count++) 
		{
			if ((ECG_Diagnose_resultTotal.Rlist.arr[ECG_Diagnose_resultTotal.Insert_PVBposL[i]]>= (count) * 3600 * fs)
				&& (ECG_Diagnose_resultTotal.Rlist.arr[ECG_Diagnose_resultTotal.Insert_PVBposL[i]]< (count + 1) * 3600 * fs))

				(Diagnose_resultPerHour + count)->Insert_PVB_Num= (Diagnose_resultPerHour + count)->Insert_PVB_Num + 1;
		}

	}

	count = 0; //???VT_Num
	VT_Num = 0;
	for (i = 0; i < ECG_Diagnose_resultTotal.VT_Num; i++) 
	{
		for (count = 0; count < group_num; count++) 
		{
			if ((ECG_Diagnose_resultTotal.Rlist.arr[ECG_Diagnose_resultTotal.VT_posL[i]]>= (count) * 3600 * fs)
				&& (ECG_Diagnose_resultTotal.Rlist.arr[ECG_Diagnose_resultTotal.VT_posL[i]]< (count + 1) * 3600 * fs))

				(Diagnose_resultPerHour + count)->VT_Num= (Diagnose_resultPerHour + count)->VT_Num + 1;
		}
	}

	count = 0; //???Bigeminy_Num
	Bigeminy_Num = 0;
	for (i = 0; i < ECG_Diagnose_resultTotal.Bigeminy_Num; i++) 
	{
		for (count = 0; count < group_num; count++) 
		{
			if ((ECG_Diagnose_resultTotal.Rlist.arr[ECG_Diagnose_resultTotal.Bigeminy_posL[i]]>= (count) * 3600 * fs)
				&& (ECG_Diagnose_resultTotal.Rlist.arr[ECG_Diagnose_resultTotal.Bigeminy_posL[i]]< (count + 1) * 3600 * fs))

				(Diagnose_resultPerHour + count)->Bigeminy_Num= (Diagnose_resultPerHour + count)->Bigeminy_Num + 1;
		}

	}

	count = 0; //???Trigeminy_Num
	Trigeminy_Num = 0;
	for (i = 0; i < ECG_Diagnose_resultTotal.Trigeminy_Num; i++) 
	{
		for (count = 0; count < group_num; count++) 
		{
			if ((ECG_Diagnose_resultTotal.Rlist.arr[ECG_Diagnose_resultTotal.Trigeminy_posL[i]]>= (count) * 3600 * fs)
				&& (ECG_Diagnose_resultTotal.Rlist.arr[ECG_Diagnose_resultTotal.Trigeminy_posL[i]]< (count + 1) * 3600 * fs))

				(Diagnose_resultPerHour + count)->Trigeminy_Num = (Diagnose_resultPerHour + count)->Trigeminy_Num + 1;
		}

	}

	for (i = 0; i < group_num; i++) //????Abnormal_HeartNum
	{
		(Diagnose_resultPerHour + i)->Abnormal_HeartNum
			= (Diagnose_resultPerHour + i)->Arrest_Num
			+ (Diagnose_resultPerHour + i)->Bigeminy_Num
			+ (Diagnose_resultPerHour + i)->Insert_PVB_Num
			+ (Diagnose_resultPerHour + i)->Missed_Num
			+ (Diagnose_resultPerHour + i)->PAB_Num
			+ (Diagnose_resultPerHour + i)->PVB_Num
			+ (Diagnose_resultPerHour + i)->Trigeminy_Num
			+ (Diagnose_resultPerHour + i)->VT_Num;
	}

	result.Diagnose_resultPerHourList.arr = Diagnose_resultPerHour;
	result.Diagnose_resultPerHourList.count = group_num;
	result.PVBPerHour = pvperhour;

}
void maindetect::Cancel_QRST(double *QRST_Template, int TemLenth, double *data,
							 int dataNum, int step, double *MeanSquSum_error, int *Q_location) //dai huhe ????
{
	vector<double> MeanSquSum_errorBuffer;
	int i = 0;
	int k = 0;
	int p = 0;
	int temp_int = 0;
	vector<double> temp;
	double temp_double = 0;
	double *temp_double_ptr;

	MeanSquSum_errorBuffer.clear();

//	//(ANDROID_LOG_INFO, "Cancel_QRST","Cancel_QRST 1  TemLenth=%d   dataNume=%d      step= %d ",TemLenth, dataNum, step);

	for (i = 0; i < dataNum; i = i + step) 
	{
		if (i + TemLenth > dataNum)
			break;
		else 
		{

			for (k = 0; k < TemLenth; k++) 
			{
				temp.push_back(data[i + k] - QRST_Template[k]);
			}
			temp_double_ptr = (double *) malloc(sizeof(double) * TemLenth);
			for (p = 0; p < TemLenth; p++)
				temp_double_ptr[p] = temp[p];
			temp_double = calcu_MeanSquSum(temp_double_ptr, TemLenth);
			MeanSquSum_errorBuffer.push_back(temp_double);
			free(temp_double_ptr);
			temp_double_ptr = NULL;
			temp.clear();
		}
	} // end of " for ( i=0;i<dataNum;i=i+step ) "


	if (MeanSquSum_errorBuffer.size() > 0) 
	{
		temp_double = MeanSquSum_errorBuffer[0];
		temp_int = 0;
		for (i = 1; i < (int) MeanSquSum_errorBuffer.size(); i++) 
		{
			if (MeanSquSum_errorBuffer[i] < temp_double) 
			{
				temp_int = i;
				temp_double = MeanSquSum_errorBuffer[i];
			}
		}

		*MeanSquSum_error = temp_double;
		*Q_location = temp_int * step;
	} 
	else 
	{

		*MeanSquSum_error = NULL;
		*Q_location = -1;
	}
	MeanSquSum_errorBuffer.clear();

}

/*****??????????????????????*****/
double maindetect::calcu_MeanSquSum(double *data, int dataNum) //dai huhe ????
{
	double MeanSquSum = 0;
	double temp = 0;
	double sum = 0;
	int k = 0;

	sum = 0;
	for (k = 0; k < dataNum; k++) 
	{
		sum = sum + data[k];
	}
	temp = (double) sum / dataNum;

	MeanSquSum = 0;
	for (k = 0; k < dataNum; k++) 
	{
		MeanSquSum = MeanSquSum + pow(data[k] - temp, 2);
	}
	MeanSquSum = MeanSquSum / dataNum;
	return MeanSquSum;
}

/*****?????????????QRST??壬??R????????е???*****/
int maindetect::calcu_QRST_TP(double *QRST_buffer, int buffer_len,
							  int beat_num, int QT_len, double *QRST_TP) 
{
	int i = 0;
	int k = 0;
	if (buffer_len != QT_len * beat_num)
		return -1;

	for (i = 0; i < QT_len; i = i + 1) 
	{
		QRST_TP[i] = 0;
		for (k = 0; k < beat_num; k = k + 1) 
		{
			QRST_TP[i] += QRST_buffer[i + k * QT_len];
		}
		QRST_TP[i] /= beat_num;
	}
	return 0;

}

int maindetect::Get_QRST_Template(LONG_ARR *Rlist, LONG_ARR *RRlist,
struct data_buffer *buf, double fs, long ecgnum, long RRmean, int N,double *ecgsum) // dai huhe

{ /***** ?????????????QRST???******/
	int i = 0;
	//int j = 0;
	int k = 0;
	int start_index = 0;
	//	int flag = 0;
	int start = 0;
	int end = 0;
	int beat_Num = 0; //?????????????Ч??????
	int flagfinish = 0; //?????????????????? ,1:???; 0:δ???.
	int TempLength = 0;
	int TempLength_front = 0;

	int m = 0;
	double ecgmean = 0;
	double temp_ecgmean = 0;
	double max = 0;
	double min = 0;
	double Temp_u1 = 0.1;
	double Temp_u2 = 0.4;
	double temp_double = 0;

	buf->temp_mean = 0;
	buf->temp_maxdiff = 0;
	double temp_Rvalue = 0;
	double *temp_double_ptr;
	//	double temp_max=0;

	temp_double_ptr = NULL;

	vector<int> FLAGRlist;
	//	vector<double> QRST_meanSquError;
	//	vector<double> QRST_error_buffer;
//	//(ANDROID_LOG_INFO, "Get_QRST_Template","%s"," 1       Get_QRST_Template");

	TempLength = (int) (Temp_u1 * fs) + (int) (Temp_u2 * fs) + 1;
	TempLength_front = (int) (Temp_u1 * fs);

	for (i = 0; i < RRlist->count - 2; i++) 
	{
		if (RRlist->arr[i + 1] > 0.6 * RRlist->arr[i] && RRlist->arr[i + 1]< 1.5 * RRlist->arr[i]) 
		{
			if (RRlist->arr[i] > 0.8 * RRmean && RRlist->arr[i] < 1.3 * RRmean)
				FLAGRlist.push_back(1);
			else
				FLAGRlist.push_back(0);
		} 
		else
			FLAGRlist.push_back(-1);
	}
//	//(ANDROID_LOG_INFO, "Get_QRST_Template","%s"," 2       Get_QRST_Template");

	i = 0;
	flagfinish = 0;
	while (i < RRlist->count - N) //?????????????????N????????????????
	{
		for (k = i; k < i + N; k++) 
		{
			if ((1 != FLAGRlist[k]) && (0 != FLAGRlist[k]))
				break;
		}
		if (k == i + N) 
		{
			start_index = i;
			flagfinish = 1;
			break;
		}

		i++;
	}
//	//(ANDROID_LOG_INFO, "Get_QRST_Template","%s"," Get_QRST_Template 3       ");

	start = start_index;
	if (Rlist->arr[start_index] - (int) Temp_u1 * fs < 0) //检查首部是否溢出
		start = start_index + 1;
	end = start_index + N;
	if (Rlist->arr[end] + (int) Temp_u2 * fs > ecgnum) //检查尾部是否溢出
	{
		for (i = end; i >= start; i--) 
		{
			if (Rlist->arr[i] + (int) Temp_u2 * fs < ecgnum)
				break;
		}
		end = i;
	}

	beat_Num = end - start + 1;
	if (1 == beat_Num)
		return -1; //未能获取模板和1s正常心电信号的均平方和

	if (end > Rlist->count)
	{
		end = Rlist->count;
	}
	for (k = 0; k < TempLength; k++) //计算模板
	{
		temp_double = 0;
		for (i = start; i < end; i++) 
		{
			temp_double = temp_double + buf->orig00[Rlist->arr[i] + k- TempLength_front];
		}
		temp_double = temp_double / beat_Num;
		buf->plate_data.push_back(temp_double);
	}

	for (k = Rlist->arr[start]; k <= Rlist->arr[end-1]; k++) //计算均平方和
	{
		*ecgsum += buf->orig00[k] * buf->orig00[k];
	}
	*ecgsum = sqrt(*ecgsum * fs / (Rlist->arr[end] - Rlist->arr[start] + 1)); //1s正常心电信号的均平方和


	max = (int) (0.2 * fs);//the position
	buf->temp_Tvalue = buf->plate_data[(int) max];//2012.5.7 shangguan
	for (m = (int) (0.2 * fs); m < (int) (0.46 * fs); m++) 
	{
		if (buf->temp_Tvalue < buf->plate_data[m]) 
		{
			buf->temp_Tvalue = buf->plate_data[m];
			max = m;
		}
	}
	min = (int) (0.1 * fs);
	buf->temp_Svalue = buf->plate_data[(int) min];//2012.5.7 shangguan
	for (m = (int) (0.1 * fs); m < (int) (0.3 * fs); m++) 
	{
		if (buf->temp_Svalue > buf->plate_data[m]) 
		{
			buf->temp_Svalue = buf->plate_data[m];
			min = m;
		}
	}

	ecgmean = 0;
	for (m = 0; m < (int) buf->plate_data.size(); m++) 
	{
		temp_ecgmean += (buf->plate_data[m] - ecgmean) * (buf->plate_data[m]- ecgmean);
	}
	temp_ecgmean = sqrt(temp_ecgmean / (buf->plate_data.size()));
	temp_Rvalue = buf->plate_data[(int) (0.1 * fs)];

	buf->temp_Rvalue = temp_Rvalue;
	buf->temp_mean = temp_ecgmean;//the square mean of a template
	buf->temp_RT = (long) ((max - (int) (0.1 * fs)) / fs * 1000);
	if (buf->temp_RT < 100)
		buf->temp_RT = 100;//2012.4.26
	if(fabs(buf->temp_Tvalue)>0.8*fabs(buf->temp_Rvalue))
		buf->temp_RS = 1;//(long) ((min - (int) (0.1 * fs)) / fs * 1000);
	else
		buf->temp_RS=0;
	if (fabs(buf->temp_Svalue - buf->temp_Rvalue) > fabs(buf->temp_Rvalue))
		buf->temp_maxdiff = fabs(buf->temp_Svalue - buf->temp_Rvalue);//the hight of QRS wave, consider the R is towards down
	else
		buf->temp_maxdiff = fabs(buf->temp_Rvalue);

	return flagfinish;//if return 0, it shows the rawecg data is bad; if return1, the  raw ecg is good
}
QRS_TEMP maindetect::CreateQRSTempForRecAbnorlBeat_A(DOUB_ARR *ECG_data,LONG_ARR *RRlist, LONG_ARR *Rlist, long AbBeat_index, double fs,
													 int beat_num, int RRmean, long *QRS_start) //dai
{

	int i = 0;
	int k = 0;
	int start_index = 0;
	int end_index = 0;
	int start = 0;
	int end = 0;
	int flagfinish = 0;
	double temp_double = 0;

	int QR_len = (int) (QR_len_global * fs);
	int RS_len = (int) (RS_len_global * fs);
	int QRS_len = QR_len + RS_len + 1;

	vector<int> FLAGRlist;
	QRS_TEMP QRS_temlate;

	QRS_temlate.RR_mean = 0;
	QRS_temlate.QR_len = QR_len;
	QRS_temlate.QRS_len = QRS_len;
	QRS_temlate.arr = (double *) malloc(sizeof(double) * QRS_len);
	if (NULL == QRS_temlate.arr) 
	{
		return QRS_temlate; //申请内存失败，直接返回
	}

	for (i = 0; i < RRlist->count - 2; i++) 
	{
		if (RRlist->arr[i + 1] > 0.6 * RRlist->arr[i] && RRlist->arr[i + 1]< 1.5 * RRlist->arr[i]) {
			if (RRlist->arr[i] > 0.8 * RRmean && RRlist->arr[i] < 1.3 * RRmean)
				FLAGRlist.push_back(1);
			else
				FLAGRlist.push_back(0);
		} 
		else
			FLAGRlist.push_back(-1);
	}
	FLAGRlist.push_back(-1);

	i = AbBeat_index + 1;
	flagfinish = 0;
	while (i < RRlist->count - beat_num - 2) //向后找到符合条件的连续beat_num心拍心电信号计算模板
	{
		for (k = i; k < i + beat_num; k++) 
		{
			if ((1 != FLAGRlist[k]) && (0 != FLAGRlist[k]))
				break;
		}
		if (k == i + beat_num) 
		{
			start_index = i;
			flagfinish = 1;
			break;
		}
		i++;
	}

	if (0 == flagfinish) 
	{
		QRS_temlate.arr = NULL;
		return QRS_temlate; //未找到规则的R波序列, 直接返回
	}

	end_index = start_index + beat_num - 1;
	start = Rlist->arr[start_index];
	if (start - QR_len < 0) //检查首部是否溢出
		start_index = start_index + 1;

	end = Rlist->arr[end_index];
	if (end + RS_len > ECG_data->count) //检查尾部是否溢出
	{
		for (i = end_index; i >= start_index; i--) 
		{
			end = Rlist->arr[i];
			if (end + RS_len < ECG_data->count)
				break;
		}
		end_index = i;
	}

	beat_num = end_index - start_index + 1;
	if (1 == beat_num) 
	{
		QRS_temlate.arr = NULL;
		return QRS_temlate; //δ????????1s?????????????????
	}

	for (k = 0; k < QRS_len; k++) //???????
	{
		temp_double = 0;
		for (i = start_index; i < end_index; i++) 
		{
			temp_double = temp_double + ECG_data->arr[Rlist->arr[i] - QR_len+ k];
		}
		temp_double = temp_double / beat_num;
		QRS_temlate.arr[k] = temp_double;
	}

	temp_double = 0;
	for (i = start_index; i < end_index - 1; i++) 
	{
		temp_double += Rlist->arr[i + 1] - Rlist->arr[i];
	}
	QRS_temlate.RR_mean = (int) (temp_double / (beat_num - 1));
	QRS_temlate.RR_mean = QRS_temlate.RR_mean * 1000 / (int) fs;

	*QRS_start = start_index;
	return QRS_temlate;

}

/*****???????????????????????????QRS???*****/
QRS_TEMP maindetect::CreateQRSTempForRecAbnorlBeat(DOUB_ARR *ECG_data,
												   LONG_ARR *RRlist, LONG_ARR *Rlist, long AbBeat_index, double fs,
												   int beat_num, int RRmean) //dai
{

	int i = 0;
	int k = 0;
	int start_index = 0;
	int end_index = 0;
	int start = 0;
	int end = 0;
	int flagfinish = 0;
	double temp_double = 0;

	int QR_len = (int) (0.1 * fs);
	int RS_len = (int) (0.1 * fs);
	int QRS_len = QR_len + RS_len + 1;

	vector<int> FLAGRlist;
	QRS_TEMP QRS_temlate;

	QRS_temlate.RR_mean = 0;
	QRS_temlate.QR_len = QR_len;
	QRS_temlate.QRS_len = QRS_len;
	QRS_temlate.arr = (double *) malloc(sizeof(double) * QRS_len);
	if (NULL == QRS_temlate.arr) 
	{
		return QRS_temlate; //?????????????????
	}

	for (i = 0; i < RRlist->count - 2; i++) 
	{
		if (RRlist->arr[i + 1] > 0.6 * RRlist->arr[i] && RRlist->arr[i + 1]< 1.5 * RRlist->arr[i]) 
		{
			if (RRlist->arr[i] > 0.8 * RRmean && RRlist->arr[i] < 1.3 * RRmean)
				FLAGRlist.push_back(1);
			else
				FLAGRlist.push_back(0);
		} else
			FLAGRlist.push_back(-1);
	}
	FLAGRlist.push_back(-1);

	i = AbBeat_index + 1;
	flagfinish = 0;
	while (i < RRlist->count - beat_num - 2) //????????????????????beat_num????????????????
	{
		for (k = i; k < i + beat_num; k++) 
		{
			if ((1 != FLAGRlist[k]) && (0 != FLAGRlist[k]))
				break;
		}
		if (k == i + beat_num) 
		{
			start_index = i;
			flagfinish = 1;
			break;
		}
		i++;
	}

	if ((0 == flagfinish) && (i < (int) FLAGRlist.size())) //???δ???????????????????beat_num????????????????????
	{
		i = AbBeat_index - 1;
		while (i > beat_num) 
		{
			for (k = i; k > i - beat_num; k--) 
			{
				if ((1 != FLAGRlist[k]) && (0 != FLAGRlist[k]))
					break;
			}
			if (k == i - beat_num) 
			{
				start_index = i - beat_num + 1;
				flagfinish = 1;
				break;
			}
			i--;
		}
	}

	if (0 == flagfinish) 
	{
		QRS_temlate.arr = NULL;
		return QRS_temlate; //δ????????R??????, ??????
	}

	end_index = start_index + beat_num - 1;
	start = Rlist->arr[start_index];
	if (start - QR_len < 0) //????????????
		start_index = start_index + 1;

	end = Rlist->arr[end_index];
	if (end + RS_len > ECG_data->count) //???β????????
	{
		for (i = end_index; i >= start_index; i--) 
		{
			end = Rlist->arr[i];
			if (end + RS_len < ECG_data->count)
				break;
		}
		end_index = i;
	}

	beat_num = end_index - start_index + 1;
	if (1 == beat_num) 
	{
		QRS_temlate.arr = NULL;
		return QRS_temlate; //δ????????1s?????????????????
	}

	for (k = 0; k < QRS_len; k++) //???????
	{
		temp_double = 0;
		for (i = start_index; i < end_index; i++) 
		{
			temp_double = temp_double + ECG_data->arr[Rlist->arr[i] - QR_len+ k];
		}
		temp_double = temp_double / beat_num;
		QRS_temlate.arr[k] = temp_double;
	}

	temp_double = 0;
	for (i = start_index; i < end_index - 1; i++) 
	{
		temp_double += Rlist->arr[i + 1] - Rlist->arr[i];
	}
	QRS_temlate.RR_mean = (int) (temp_double / (beat_num - 1));
	QRS_temlate.RR_mean = QRS_temlate.RR_mean * 1000 / (int) fs;

	return QRS_temlate;

}

int maindetect::ReDiagnoseAbnomalBeat(DOUB_ARR *ECG_data, LONG_ARR *RRlist,
									  LONG_ARR *Rlist, LONG_ARR *Rannolist, double fs, ecg_info *ci,
									  int RRmean, LONG_ARR *Noise_Anno) //dai
{
	int i = 0;
	int k = 0;
	int j = 0;
	int anno_index = 0;
	int beat_num = 10; // beat number used for constructing QRS template
	long temp_start = 0;
	long temp_end = 0;
	double temp_max = 0;
	double template_max = 0;

	double thresh_coff = 1.0; // thresh value for determining real QRS  complex

	double thresh_coff_AB_MB = 0.5; // thresh value for determining real QRS  complex, for APB and MB cases

	double *temp_double_ptr = NULL;
	double MeanSquSum_Temlate = 0;
	double MeanSquSum_error = 0;
	int Q_location = 0;
	int dataNum = 0;
	int Cancel_step = 1;
	int Cancel_start = 0;
	int Cancel_end = 0;

	int search_on = 0;
	int search_off = 0;

	long noise_anno_start = 0;
	long noise_anno_end = 0;

	long Template_Start = 0; // ??????QRST???????

	int count1_PAB = 0; //?????????
	int count2_PAB = 0;
	int count3_PAB = 0;
	//	int count4_PAB=0;

	int count1_PVB = 0; //?????????
	int count2_PVB = 0;
	int count3_PVB = 0;
	//	int count4_PVB=0;

	QRS_TEMP QRS_Template;
	QRS_TEMP QRS_Template2; //临时存放QRS模板

	QRS_Template.arr = NULL;
	QRS_Template2.arr = NULL;

	int RR_mean = 0;

	QRS_Template = CreateQRSTempForRecAbnorlBeat_A(ECG_data, RRlist, Rlist, 0,
		fs, beat_num, RRmean, &Template_Start);
	if (NULL != QRS_Template2.arr)
		MeanSquSum_Temlate = calcu_MeanSquSum(QRS_Template.arr,
		QRS_Template.QRS_len);

	for (i = 0; i < Rannolist->count; i++) 
	{

		if ((Rannolist->arr[i]!=0&&Rannolist->arr[i]!=-1&&Rannolist->arr[i]!=-2)&&Rlist->arr[i] - Rlist->arr[Template_Start] > 300 * (int) fs) //???????????????λ?ó???20?????????????
		{
			QRS_Template2 = CreateQRSTempForRecAbnorlBeat_A(ECG_data, RRlist,
				Rlist, i, fs, beat_num, RRmean, &Template_Start);
			if (NULL != QRS_Template2.arr) //正常获得模板，则更新QRS模板
			{
				QRS_Template.arr = QRS_Template2.arr;
				QRS_Template.QR_len = QRS_Template2.QR_len;
				QRS_Template.QRS_len = QRS_Template2.QRS_len;
				QRS_Template.RR_mean = QRS_Template2.RR_mean;
				MeanSquSum_Temlate = calcu_MeanSquSum(QRS_Template.arr,QRS_Template.QRS_len);
			}

		}
//		//(ANDROID_LOG_INFO, "ReDiagnoseAbnomalBeat","ggss count= %d  val =%d",Rannolist->count, Rannolist->arr[i]);

		if (6 == Rannolist->arr[i]) 
		{
			search_on = i - 2;
			if (search_on < 0)
				search_on = 0;
			search_off = i + 2;
			if (search_off > Rannolist->count - 1)
				search_off = Rannolist->count - 1;
			for (k = search_on; k + 2 <= search_off; k++) 
			{
				if ((6 == Rannolist->arr[k]) && (6 == Rannolist->arr[k + 1])&& (6 == Rannolist->arr[k + 2]))
					break;
			}
			if (k + 2 > search_off) // ???????????????ж??????????????????????
				Rannolist->arr[i] = 0;
			else {
				//??????????????
				noise_anno_start = (long) (Rlist->arr[k] / ((int) fs* NOISE_TIME_A));
				noise_anno_end = (long) (Rlist->arr[k + 2] / ((int) fs* NOISE_TIME_A));
				if ((noise_anno_start <= Noise_Anno->count - 1)
					&& (noise_anno_end <= Noise_Anno->count - 1)) 
				{
					for (j = noise_anno_start; j <= noise_anno_end; j++) 
					{
						if (1 == Noise_Anno->arr[j])
							break;
					}
					if (j <= noise_anno_end) 
					{
						Rannolist->arr[k] = 0;
						Rannolist->arr[k + 1] = 0;
						Rannolist->arr[k + 2] = 0;
						continue; // ???????????????????????
					}
				}

				//	QRS_Template=CreateQRSTempForRecAbnorlBeat( ECG_data, RRlist, Rlist, k , fs, beat_num, RRmean)  ;
				if (NULL != QRS_Template.arr) 
				{
					//				MeanSquSum_Temlate=calcu_MeanSquSum( QRS_Template.arr, QRS_Template.QRS_len);
					for (anno_index = k; anno_index <= k + 2; anno_index++) // ????????
					{
						if (Rlist->arr[anno_index] - (int) (QR_len_global * fs)>= 0)
							Cancel_start = Rlist->arr[anno_index]- (int) (QR_len_global * fs);
						else
							Cancel_start = 0;
						if (Rlist->arr[anno_index] + (int) (RS_len_global * fs)< ECG_data->count)
							Cancel_end = Rlist->arr[anno_index]+ (int) (RS_len_global * fs);
						else
							Cancel_end = ECG_data->count - 1;

						temp_double_ptr = &(ECG_data->arr[Cancel_start]);
						dataNum = Cancel_end - Cancel_start + 1;
						Cancel_QRST(QRS_Template.arr, QRS_Template.QRS_len,
							temp_double_ptr, dataNum, Cancel_step,
							&MeanSquSum_error, &Q_location);
						if ((Q_location >= 0) && (MeanSquSum_error< (thresh_coff+0.3 )* MeanSquSum_Temlate)) // ??????QRS?????????????
						{
							Rannolist->arr[k] = 0;
							Rannolist->arr[k + 1] = 0;
							Rannolist->arr[k + 2] = 0;
							break;
						}
					} //  end  of 'for ( anno_index=k; anno_index<=k+2;  anno_index++)'

				} // end of " if( NULL!=QRS_Template.arr ) "
				/*
				else 
				{
				Rannolist->arr[k] = 0;
				Rannolist->arr[k + 1] = 0;
				Rannolist->arr[k + 2] = 0;
				}
				*/
				i = k + 2;
			}

		} //  end of ' if( 6==Rannolist->arr[i] )  //室性心动过速的再判断 '


		///PVB的再判断
		else if ((3 == Rannolist->arr[i]) && (i > 0) && (i < Rannolist->count- 1)) 
		{
			//检测是否有噪声区
			noise_anno_start = (long) (Rlist->arr[i - 1] / ((int) fs* NOISE_TIME_A));
			noise_anno_end = (long) (Rlist->arr[i + 1] / ((int) fs* NOISE_TIME_A));
			if ((noise_anno_start <= Noise_Anno->count - 1) && (noise_anno_end
				<= Noise_Anno->count - 1)) 
			{
				for (j = noise_anno_start; j <= noise_anno_end; j++) 
				{
					if (1 == Noise_Anno->arr[j])
						break;
				}
				if (j <= noise_anno_end) 
				{
					Rannolist->arr[i] = 0;
					count1_PVB++;
					continue; // 若有噪声，则跳出本次循环
				}
			}

			anno_index = i;
			//		QRS_Template=CreateQRSTempForRecAbnorlBeat( ECG_data, RRlist, Rlist, i , fs, beat_num, RRmean)  ;
			if (NULL != QRS_Template.arr) // succeed to construct QRS template
			{

				anno_index = i - 1;
				if (3 != Rannolist->arr[anno_index]) //检测前一心怕的QRS波是否匹配
				{
					if (Rlist->arr[anno_index] - (int) (QR_len_global * fs)>= 0)
						Cancel_start = Rlist->arr[anno_index]- (int) (QR_len_global * fs);
					else
						Cancel_start = 0;
					if (Rlist->arr[anno_index] + (int) (RS_len_global * fs)< ECG_data->count)
						Cancel_end = Rlist->arr[anno_index]+ (int) (RS_len_global * fs);
					else
						Cancel_end = ECG_data->count - 1;
					temp_double_ptr = &(ECG_data->arr[Cancel_start]);
					dataNum = Cancel_end - Cancel_start + 1;
					Cancel_QRST(QRS_Template.arr, QRS_Template.QRS_len,
						temp_double_ptr, dataNum, Cancel_step,
						&MeanSquSum_error, &Q_location);
					if (Q_location >= 0) 
					{
						if (MeanSquSum_error > thresh_coff * MeanSquSum_Temlate) 
						{
							Rannolist->arr[i] = 0;
							count2_PVB++;

							continue;
						}
					}
				}

				anno_index = i + 1;
				if (3 != Rannolist->arr[anno_index]) //检测后一心怕的QRS波是否匹配
				{
					if (Rlist->arr[anno_index] - (int) (QR_len_global * fs)>= 0)
						Cancel_start = Rlist->arr[anno_index]- (int) (QR_len_global * fs);
					else
						Cancel_start = 0;
					if (Rlist->arr[anno_index] + (int) (RS_len_global * fs)< ECG_data->count)
						Cancel_end = Rlist->arr[anno_index]+ (int) (RS_len_global * fs);
					else
						Cancel_end = ECG_data->count - 1;
					temp_double_ptr = &(ECG_data->arr[Cancel_start]);
					dataNum = Cancel_end - Cancel_start + 1;
					Cancel_QRST(QRS_Template.arr, QRS_Template.QRS_len,
						temp_double_ptr, dataNum, Cancel_step,
						&MeanSquSum_error, &Q_location);
					if (Q_location >= 0) 
					{
						if (MeanSquSum_error > thresh_coff * MeanSquSum_Temlate) 
						{
							Rannolist->arr[i] = 0;
							count3_PVB++;

							continue;
						}
					}
				}


				anno_index = i;//new added 2013.7.10
				if (3 == Rannolist->arr[anno_index]) //检测后一心怕的QRS波是否匹配
				{
					if (Rlist->arr[anno_index] - (int) (QR_len_global * fs)>= 0)
						Cancel_start = Rlist->arr[anno_index]- (int) (QR_len_global * fs);
					else
						Cancel_start = 0;
					if (Rlist->arr[anno_index] + (int) (RS_len_global * fs)< ECG_data->count)
						Cancel_end = Rlist->arr[anno_index]+ (int) (RS_len_global * fs);
					else
						Cancel_end = ECG_data->count - 1;
					temp_double_ptr = &(ECG_data->arr[Cancel_start]);
					dataNum = Cancel_end - Cancel_start + 1;
					Cancel_QRST(QRS_Template.arr, QRS_Template.QRS_len,
						temp_double_ptr, dataNum, Cancel_step,
						&MeanSquSum_error, &Q_location);
					if (Q_location >= 0) 
					{
						if (MeanSquSum_error < thresh_coff * MeanSquSum_Temlate) 
						{
							Rannolist->arr[i] = 4;
							continue;
						}
					}
				}


			} // end of ' if( NULL!=QRS_Template.arr ) '
			/*
			else
			Rannolist->arr[i] = 0;
			*/

		}

		//PAB的再判断
		else if ((result.flagAR==0)&&(4 == Rannolist->arr[i]) && (i > 0) && (i < Rannolist->count- 1)) 
		{
			//??????????????
			noise_anno_start = (long) (Rlist->arr[i - 1] / ((int) fs* NOISE_TIME_A));
			noise_anno_end = (long) (Rlist->arr[i + 1] / ((int) fs* NOISE_TIME_A));
			if ((noise_anno_start <= Noise_Anno->count - 1) && (noise_anno_end
				<= Noise_Anno->count - 1)) {
					for (j = noise_anno_start; j <= noise_anno_end; j++) 
					{
						if (1 == Noise_Anno->arr[j])
							break;
					}
					if (j <= noise_anno_end) 
					{
						Rannolist->arr[i] = 0;
						count1_PAB++;
						continue; // ???????????????????????
					}
			}

			anno_index = i;
			//		QRS_Template=CreateQRSTempForRecAbnorlBeat( ECG_data, RRlist, Rlist, i , fs, beat_num, RRmean)  ;
			if (NULL != QRS_Template.arr) // succeed to construct QRS template
			{

				anno_index = i - 1;
				if (4 != Rannolist->arr[anno_index]) //????????μ?QRS????????
				{
					if (Rlist->arr[anno_index] - (int) (QR_len_global * fs)>= 0)
						Cancel_start = Rlist->arr[anno_index]- (int) (QR_len_global * fs);
					else
						Cancel_start = 0;
					if (Rlist->arr[anno_index] + (int) (RS_len_global * fs)< ECG_data->count)
						Cancel_end = Rlist->arr[anno_index]+ (int) (RS_len_global * fs);
					else
						Cancel_end = ECG_data->count - 1;
					temp_double_ptr = &(ECG_data->arr[Cancel_start]);
					dataNum = Cancel_end - Cancel_start + 1;
					Cancel_QRST(QRS_Template.arr, QRS_Template.QRS_len,
						temp_double_ptr, dataNum, Cancel_step,
						&MeanSquSum_error, &Q_location);
					if (Q_location >= 0) 
					{
						if (MeanSquSum_error > thresh_coff * MeanSquSum_Temlate) 
						{
							Rannolist->arr[i] = 0;
							count2_PAB++;

							continue;
						}
					}
				}

				anno_index = i + 1;
				if (4 != Rannolist->arr[anno_index]) //????????μ?QRS????????
				{
					if (Rlist->arr[anno_index] - (int) (QR_len_global * fs)>= 0)
						Cancel_start = Rlist->arr[anno_index]
					- (int) (QR_len_global * fs);
					else
						Cancel_start = 0;
					if (Rlist->arr[anno_index] + (int) (RS_len_global * fs)< ECG_data->count)
						Cancel_end = Rlist->arr[anno_index]
					+ (int) (RS_len_global * fs);
					else
						Cancel_end = ECG_data->count - 1;
					temp_double_ptr = &(ECG_data->arr[Cancel_start]);
					dataNum = Cancel_end - Cancel_start + 1;
					Cancel_QRST(QRS_Template.arr, QRS_Template.QRS_len,
						temp_double_ptr, dataNum, Cancel_step,
						&MeanSquSum_error, &Q_location);
					if (Q_location >= 0) 
					{
						if (MeanSquSum_error > thresh_coff * MeanSquSum_Temlate) 
						{
							Rannolist->arr[i] = 0;
							count3_PAB++;

							continue;
						}
					}
				}

				anno_index = i ;
				if (4 == Rannolist->arr[anno_index]) //????????μ?QRS????????
				{
					if (Rlist->arr[anno_index] - (int) (QR_len_global * fs)>= 0)
						Cancel_start = Rlist->arr[anno_index]
					- (int) (QR_len_global * fs);
					else
						Cancel_start = 0;
					if (Rlist->arr[anno_index] + (int) (RS_len_global * fs)< ECG_data->count)
						Cancel_end = Rlist->arr[anno_index]
					+ (int) (RS_len_global * fs);
					else
						Cancel_end = ECG_data->count - 1;
					temp_double_ptr = &(ECG_data->arr[Cancel_start]);
					dataNum = Cancel_end - Cancel_start + 1;
					Cancel_QRST(QRS_Template.arr, QRS_Template.QRS_len,
						temp_double_ptr, dataNum, Cancel_step,
						&MeanSquSum_error, &Q_location);
					if (Q_location >= 0) 
					{
						if (MeanSquSum_error > thresh_coff * MeanSquSum_Temlate) 
						{
							Rannolist->arr[i] = 3;

							continue;
						}
					}
				}

			} // end of ' if( NULL!=QRS_Template.arr ) '
			/*
			else
			Rannolist->arr[i] = 0;
			*/

		} // end of ' if( (4==Rannolist->arr[i]) && (i>0) )     '


		//α??????ж???ж?α????????????????μ????
		else if ((-1 == Rannolist->arr[i]) && (i > 0) && (i < Rannolist->count- 1)) 
		{
//			//(ANDROID_LOG_INFO, "ReDiagnoseAbnomalBeat","ggss1 count= %d  val =%d",Rannolist->count, Rannolist->arr[i]);

			//??????????????
			noise_anno_start = (long) (Rlist->arr[i - 1] / ((int) fs* NOISE_TIME_A));
			noise_anno_end = (long) (Rlist->arr[i + 1] / ((int) fs* NOISE_TIME_A));
			if ((noise_anno_start <= Noise_Anno->count - 1) && (noise_anno_end
				<= Noise_Anno->count - 1)) 
			{
				for (j = noise_anno_start; j <= noise_anno_end; j++) 
				{
					if (1 == Noise_Anno->arr[j])
						break;
				}
				if (j <= noise_anno_end) 
				{
					Rannolist->arr[i] = 0;
					count1_PAB++;
					continue; // ???????????????????????
				}
			}
//			//(ANDROID_LOG_INFO, "ReDiagnoseAbnomalBeat","ggss2 count= %d  val =%d",Rannolist->count, Rannolist->arr[i]);

			anno_index = i - 1;

			if (NULL != QRS_Template.arr)
			{
				if (0== Rannolist->arr[anno_index]) //????????μ?QRS????????
				{

					if (Rlist->arr[anno_index] - (int) (QR_len_global * fs)>= 0)
						Cancel_start = Rlist->arr[anno_index]- (int) (QR_len_global * fs);
					else
						Cancel_start = 0;
					if (Rlist->arr[anno_index] + (int) (RS_len_global * fs)< ECG_data->count)
						Cancel_end = Rlist->arr[anno_index]+ (int) (RS_len_global * fs);
					else
						Cancel_end = ECG_data->count - 1;
					temp_double_ptr = &(ECG_data->arr[Cancel_start]);

					dataNum = Cancel_end - Cancel_start + 1;

					Cancel_QRST(QRS_Template.arr, QRS_Template.QRS_len,
						temp_double_ptr, dataNum, Cancel_step,
						&MeanSquSum_error, &Q_location);
					if (Q_location >= 0)
					{
					if (MeanSquSum_error < 0.1 * MeanSquSum_Temlate) //前一个是正常心电波 ，则判断下一个是否是正常心电波
						{

							anno_index = i + 1;
						if (0 == Rannolist->arr[anno_index]) //检测后一心怕的QRS波是否匹配
							{
								if (Rlist->arr[anno_index] - (int) (QR_len_global * fs)>= 0)
									Cancel_start = Rlist->arr[anno_index]- (int) (QR_len_global * fs);
								else
									Cancel_start = 0;
								if (Rlist->arr[anno_index] + (int) (RS_len_global * fs)< ECG_data->count)
									Cancel_end = Rlist->arr[anno_index]+ (int) (RS_len_global * fs);
								else
									Cancel_end = ECG_data->count - 1;
								temp_double_ptr = &(ECG_data->arr[Cancel_start]);
								dataNum = Cancel_end - Cancel_start + 1;
								Cancel_QRST(QRS_Template.arr, QRS_Template.QRS_len,
									temp_double_ptr, dataNum, Cancel_step,
									&MeanSquSum_error, &Q_location);
								if (Q_location >= 0)
								{
									if (MeanSquSum_error < 0.1 * MeanSquSum_Temlate)
									{
										anno_index = i;
										//		QRS_Template=CreateQRSTempForRecAbnorlBeat( ECG_data, RRlist, Rlist, i , fs, beat_num, RRmean)  ;
										if (NULL != QRS_Template.arr) // succeed to construct QRS template
										{
											if (Rlist->arr[anno_index] - (int) (QR_len_global * fs)>= 0)
												Cancel_start = Rlist->arr[anno_index]- (int) (QR_len_global * fs);
											else
												Cancel_start = 0;
											if (Rlist->arr[anno_index] + (int) (RS_len_global * fs)< ECG_data->count)
												Cancel_end = Rlist->arr[anno_index]+ (int) (RS_len_global * fs);
											else
												Cancel_end = ECG_data->count - 1;
											temp_double_ptr = &(ECG_data->arr[Cancel_start]);
											dataNum = Cancel_end - Cancel_start + 1;
											Cancel_QRST(QRS_Template.arr, QRS_Template.QRS_len,
												temp_double_ptr, dataNum, Cancel_step,
												&MeanSquSum_error, &Q_location);
											if (Q_location >= 0)
											{
												if (MeanSquSum_error < 0.1 * MeanSquSum_Temlate)
												{
													Rannolist->arr[i] = 4;

													continue;
												}
											}
										}

									}
								}
							}

						}
					}
				}
             }
		}		

		//IPVB?????ж?
		else if ((5 == Rannolist->arr[i]) && (i > 0) && (i < Rannolist->count- 1)) 
		{
			//??????????????
			noise_anno_start = (long) (Rlist->arr[i - 1] / ((int) fs* NOISE_TIME_A));
			noise_anno_end = (long) (Rlist->arr[i + 1] / ((int) fs* NOISE_TIME_A));
			if ((noise_anno_start <= Noise_Anno->count - 1) && (noise_anno_end
				<= Noise_Anno->count - 1)) 
			{
				for (j = noise_anno_start; j <= noise_anno_end; j++) 
				{
					if (1 == Noise_Anno->arr[j])
						break;
				}
				if (j <= noise_anno_end) 
				{
					Rannolist->arr[i] = 0;
					continue; // ???????????????????????
				}
			}

			if (NULL != QRS_Template.arr) // succeed to construct QRS template
			{
				//			MeanSquSum_Temlate=calcu_MeanSquSum( QRS_Template.arr, QRS_Template.QRS_len);
				anno_index = i;//new added 2013.7.10
				if (5 == Rannolist->arr[anno_index]) //????????μ?QRS????????
				{
					if (Rlist->arr[anno_index] - (int) (QR_len_global * fs)>= 0)
						Cancel_start = Rlist->arr[anno_index]- (int) (QR_len_global * fs);
					else
						Cancel_start = 0;
					if (Rlist->arr[anno_index] + (int) (RS_len_global * fs)< ECG_data->count)
						Cancel_end = Rlist->arr[anno_index]+ (int) (RS_len_global * fs);
					else
						Cancel_end = ECG_data->count - 1;
					temp_double_ptr = &(ECG_data->arr[Cancel_start]);
					dataNum = Cancel_end - Cancel_start + 1;
					Cancel_QRST(QRS_Template.arr, QRS_Template.QRS_len,
						temp_double_ptr, dataNum, Cancel_step,
						&MeanSquSum_error, &Q_location);
					if (Q_location >= 0) 
					{
						if (MeanSquSum_error < thresh_coff * MeanSquSum_Temlate) 
						{
							Rannolist->arr[i] = 0;
							continue;
						}
					}
				}

				anno_index = i - 1;
				if (5 != Rannolist->arr[anno_index]) //????????μ?QRS????????
				{
					if (Rlist->arr[anno_index] - (int) (QR_len_global * fs)>= 0)
						Cancel_start = Rlist->arr[anno_index]- (int) (QR_len_global * fs);
					else
						Cancel_start = 0;
					if (Rlist->arr[anno_index] + (int) (RS_len_global * fs)< ECG_data->count)
						Cancel_end = Rlist->arr[anno_index]+ (int) (RS_len_global * fs);
					else
						Cancel_end = ECG_data->count - 1;
					temp_double_ptr = &(ECG_data->arr[Cancel_start]);
					dataNum = Cancel_end - Cancel_start + 1;
					Cancel_QRST(QRS_Template.arr, QRS_Template.QRS_len,
						temp_double_ptr, dataNum, Cancel_step,
						&MeanSquSum_error, &Q_location);
					if (Q_location >= 0) {
						if (MeanSquSum_error > thresh_coff * MeanSquSum_Temlate) 
						{
							Rannolist->arr[i] = 0;

							continue;
						}
					}
				}

				anno_index = i + 1;
				if (5 != Rannolist->arr[anno_index]) //????????μ?QRS????????
				{
					if (Rlist->arr[anno_index] - (int) (QR_len_global * fs)>= 0)
						Cancel_start = Rlist->arr[anno_index]- (int) (QR_len_global * fs);
					else
						Cancel_start = 0;
					if (Rlist->arr[anno_index] + (int) (RS_len_global * fs)< ECG_data->count)
						Cancel_end = Rlist->arr[anno_index]+ (int) (RS_len_global * fs);
					else
						Cancel_end = ECG_data->count - 1;
					temp_double_ptr = &(ECG_data->arr[Cancel_start]);
					dataNum = Cancel_end - Cancel_start + 1;
					Cancel_QRST(QRS_Template.arr, QRS_Template.QRS_len,
						temp_double_ptr, dataNum, Cancel_step,
						&MeanSquSum_error, &Q_location);
					if (Q_location >= 0) {
						if (MeanSquSum_error > thresh_coff * MeanSquSum_Temlate) 
						{
							Rannolist->arr[i] = 0;

							continue;
						}
					}
				}

			} // end of ' if( NULL!=QRS_Template.arr ) '
			/*
			else
			Rannolist->arr[i] = 0;
			*/
		} // end of " else if( (5==Rannolist->arr[i]) && (i>0) && (i<Rannolist->count-1) )   "

		//??????????ж?
		else if ((7 == Rannolist->arr[i]) && (i > 0) && (i < Rannolist->count
			- 5)) {
				//??????????????
				noise_anno_start = (long) (Rlist->arr[i - 1] / ((int) fs
					* NOISE_TIME_A));
				noise_anno_end = (long) (Rlist->arr[i + 5] / ((int) fs
					* NOISE_TIME_A));
				if ((noise_anno_start <= Noise_Anno->count - 1) && (noise_anno_end
					<= Noise_Anno->count - 1)) {
						for (j = noise_anno_start; j <= noise_anno_end; j++) {
							if (1 == Noise_Anno->arr[j])
								break;
						}
						if (j <= noise_anno_end) {
							Rannolist->arr[i] = 0;
							if (7 == Rannolist->arr[i + 2])
								Rannolist->arr[i + 2] = 0;
							if (7 == Rannolist->arr[i + 4])
								Rannolist->arr[i + 4] = 0;
							continue; // ???????????????????????
						}
				}

				//		QRS_Template=CreateQRSTempForRecAbnorlBeat( ECG_data, RRlist, Rlist, i , fs, beat_num, RRmean)  ;
				RR_mean = QRS_Template.RR_mean;
				if (NULL != QRS_Template.arr) // succeed to construct QRS template
				{
					//				MeanSquSum_Temlate=calcu_MeanSquSum( QRS_Template.arr, QRS_Template.QRS_len);
					for (anno_index = i - 1; anno_index <= i + 5; anno_index
						= anno_index + 2) // ????????
					{
						if (Rlist->arr[anno_index] - (int) (QR_len_global * fs)
							>= 0)
							Cancel_start = Rlist->arr[anno_index]
						- (int) (QR_len_global * fs);
						else
							Cancel_start = 0;
						if (Rlist->arr[anno_index] + (int) (RS_len_global * fs)
							< ECG_data->count)
							Cancel_end = Rlist->arr[anno_index]
						+ (int) (RS_len_global * fs);
						else
							Cancel_end = ECG_data->count - 1;

						temp_double_ptr = &(ECG_data->arr[Cancel_start]);
						dataNum = Cancel_end - Cancel_start + 1;
						Cancel_QRST(QRS_Template.arr, QRS_Template.QRS_len,
							temp_double_ptr, dataNum, Cancel_step,
							&MeanSquSum_error, &Q_location);
						if ((Q_location >= 0) && (MeanSquSum_error > thresh_coff
							* MeanSquSum_Temlate)) // ??????QRS?????????????
						{
							Rannolist->arr[i] = 0;
							if (7 == Rannolist->arr[i + 2])
								Rannolist->arr[i + 2] = 0;
							if (7 == Rannolist->arr[i + 4])
								Rannolist->arr[i + 4] = 0;
							break;
						}
					} //  end  of ' for ( anno_index=i-1; anno_index<=i+5;  anno_index++)  // ???????? '
					if (anno_index > i + 5) //QRS???????????RR????
					{
						if (RRlist->arr[i - 1] > (1 - ci->pvpercent) * RRmean
							|| RRlist->arr[i] < (1 + ci->pvpercent) * RRmean
							|| RRlist->arr[i + 1] > (1 - ci->pvpercent)
							* RRmean || RRlist->arr[i + 2] < (1
							+ ci->pvpercent) * RRmean || RRlist->arr[i + 3]
							> (1 - ci->pvpercent) * RRmean
								|| RRlist->arr[i + 4] < (1 + ci->pvpercent)
								* RRmean) {
									if (RRlist->arr[i - 1] <= (1 - ci->papercent) * RRmean
										&& RRlist->arr[i] >= (1 + ci->papercent)
										* RRmean)
										Rannolist->arr[i] = 4;
									else
										Rannolist->arr[i] = 0;
									if (RRlist->arr[i + 1] <= (1 - ci->papercent) * RRmean
										&& RRlist->arr[i + 2] >= (1 + ci->papercent)
										* RRmean)
										Rannolist->arr[i + 2] = 4;
									else
										Rannolist->arr[i + 2] = 0;
									if (RRlist->arr[i + 3] <= (1 - ci->papercent) * RRmean
										&& RRlist->arr[i + 4] >= (1 + ci->papercent)
										* RRmean)
										Rannolist->arr[i + 4] = 4;
									else
										Rannolist->arr[i + 4] = 0;
							}

					} // end of " if( anno_index>i+5 )  //QRS???????????RR???? "

				} // end of " if( NULL!=QRS_Template.arr )  // succeed to construct QRS template "
				/*else {
				Rannolist->arr[i] = 0;
				if (7 == Rannolist->arr[i + 2])
				Rannolist->arr[i + 2] = 0;
				if (7 == Rannolist->arr[i + 4])
				Rannolist->arr[i + 4] = 0;
				}
				*/

				i = i + 5;
		} // end of ' if( (7==Rannolist->arr[i]) && (i>0) && (i<Rannolist->count-5) ) '
		/*
		//??????????ж?
		else if ((8 == Rannolist->arr[i]) && (i < Rannolist->count - 7)) {
		//??????????????
		noise_anno_start = (long) (Rlist->arr[i]
		/ ((int) fs * NOISE_TIME_A));
		noise_anno_end = (long) (Rlist->arr[i + 7] / ((int) fs
		* NOISE_TIME_A));
		if ((noise_anno_start <= Noise_Anno->count - 1) && (noise_anno_end
		<= Noise_Anno->count - 1)) {
		for (j = noise_anno_start; j <= noise_anno_end; j++) {
		if (1 == Noise_Anno->arr[j])
		break;
		}
		if (j <= noise_anno_end) {
		Rannolist->arr[i] = 0;
		if (7 == Rannolist->arr[i + 2])
		Rannolist->arr[i + 3] = 0;
		if (7 == Rannolist->arr[i + 4])
		Rannolist->arr[i + 6] = 0;
		continue; // ???????????????????????
		}
		}

		//		QRS_Template=CreateQRSTempForRecAbnorlBeat( ECG_data, RRlist, Rlist, i , fs, beat_num, RRmean)  ;
		RR_mean = QRS_Template.RR_mean;
		if (NULL != QRS_Template.arr) // succeed to construct QRS template
		{
		//				MeanSquSum_Temlate=calcu_MeanSquSum( QRS_Template.arr, QRS_Template.QRS_len);
		for (anno_index = i; anno_index <= i + 7; anno_index++) // ????????
		{
		if ((anno_index == i) || (anno_index == i + 3)
		|| (anno_index == i + 6)) //??Щ????QRS??????????????貨?α??
		continue;

		if (Rlist->arr[anno_index] - (int) (QR_len_global * fs)
		>= 0)
		Cancel_start = Rlist->arr[anno_index]
		- (int) (QR_len_global * fs);
		else
		Cancel_start = 0;
		if (Rlist->arr[anno_index] + (int) (RS_len_global * fs)
		< ECG_data->count)
		Cancel_end = Rlist->arr[anno_index]
		+ (int) (RS_len_global * fs);
		else
		Cancel_end = ECG_data->count - 1;

		temp_double_ptr = &(ECG_data->arr[Cancel_start]);
		dataNum = Cancel_end - Cancel_start + 1;
		Cancel_QRST(QRS_Template.arr, QRS_Template.QRS_len,
		temp_double_ptr, dataNum, Cancel_step,
		&MeanSquSum_error, &Q_location);
		if ((Q_location >= 0) && (MeanSquSum_error > thresh_coff
		* MeanSquSum_Temlate)) // ??????QRS?????????????
		{
		Rannolist->arr[i] = 0;
		if (7 == Rannolist->arr[i + 3])
		Rannolist->arr[i + 3] = 0;
		if (7 == Rannolist->arr[i + 6])
		Rannolist->arr[i + 6] = 0;
		break;
		}
		} //  end  of 'for ( anno_index=k; anno_index<=k+2;  anno_index++)'
		if (anno_index > i + 7) //QRS???????????RR????
		{
		if (RRlist->arr[i + 1] < 0.9 * RRmean || RRlist->arr[i + 1]
		< 1.1 * RRmean && RRlist->arr[i + 2] > (1
		- ci->pvpercent) * RRmean || RRlist->arr[i + 3]
		< (1 + ci->pvpercent) * RRmean
		&& RRlist->arr[i + 4] < 0.9 * RRmean
		|| RRlist->arr[i + 4] < 1.1 * RRmean
		&& RRlist->arr[i + 5] > (1 - ci->pvpercent)
		* RRmean || RRlist->arr[i + 6] < (1
		+ ci->pvpercent) * RRmean) {
		Rannolist->arr[i] = 0;
		if (RRlist->arr[i + 2] <= (1 - ci->papercent) * RRmean
		&& RRlist->arr[i + 3] >= (1 + ci->papercent)
		* RRmean)
		Rannolist->arr[i + 3] = 4;
		else
		Rannolist->arr[i + 3] = 0;
		if (RRlist->arr[i + 5] <= (1 - ci->papercent) * RRmean
		&& RRlist->arr[i + 6] >= (1 + ci->papercent)
		* RRmean)
		Rannolist->arr[i + 6] = 4;
		else
		Rannolist->arr[i + 6] = 0;
		}

		} // end of " if( anno_index>i+5 )  //QRS???????????RR???? "

		} // end of "  if( NULL!=QRS_Template.arr )   "
		else {
		Rannolist->arr[i] = 0;
		if (7 == Rannolist->arr[i + 3])
		Rannolist->arr[i + 3] = 0;
		if (7 == Rannolist->arr[i + 6])
		Rannolist->arr[i + 6] = 0;
		}
		i = i + 7;
		} // end of ' if( (8==Rannolist->arr[i]) && (i<Rannolist->count-7) )   '
		*/
		//????????ж?
		else if (2 == Rannolist->arr[i]) 
		{
			if (i < Rannolist->count - 2) 
			{
				//??????????????
				noise_anno_start = (long) (Rlist->arr[i] / ((int) fs* NOISE_TIME_A));
				noise_anno_end = (long) (Rlist->arr[i + 1] / ((int) fs* NOISE_TIME_A));
				if ((noise_anno_start <= Noise_Anno->count - 1)&& (noise_anno_end <= Noise_Anno->count - 1)) 
				{
					for (j = noise_anno_start; j <= noise_anno_end; j++) 
					{
						if (1 == Noise_Anno->arr[j])
							break;
					}
					if (j <= noise_anno_end) 
					{
						Rannolist->arr[i] = 0;
						continue; // ???????????????????????
					}
				}

				//			QRS_Template=CreateQRSTempForRecAbnorlBeat( ECG_data, RRlist, Rlist, i , fs, beat_num, RRmean)  ;
				if (NULL != QRS_Template.arr) // succeed to construct QRS template
				{
					//					MeanSquSum_Temlate=calcu_MeanSquSum( QRS_Template.arr, QRS_Template.QRS_len);
					for (anno_index = i; anno_index <= i + 1; anno_index++) // ????????
					{
						if (NULL != QRS_Template.arr) // succeed to construct QRS template
						{

							if (Rlist->arr[anno_index] - (int) (QR_len_global* fs) >= 0)
								Cancel_start = Rlist->arr[anno_index]- (int) (QR_len_global * fs);
							else
								Cancel_start = 0;
							if (Rlist->arr[anno_index] + (int) (RS_len_global* fs) < ECG_data->count)
								Cancel_end = Rlist->arr[anno_index]+ (int) (RS_len_global * fs);
							else
								Cancel_end = ECG_data->count - 1;

							temp_double_ptr = &(ECG_data->arr[Cancel_start]);
							dataNum = Cancel_end - Cancel_start + 1;
							Cancel_QRST(QRS_Template.arr, QRS_Template.QRS_len,
								temp_double_ptr, dataNum, Cancel_step,
								&MeanSquSum_error, &Q_location);
							if ((Q_location >= 0) && (MeanSquSum_error> thresh_coff_AB_MB * MeanSquSum_Temlate)) // ??????QRS?????????????
							{
								Rannolist->arr[i] = 0;
								break;
							}
						}

					} //  end  of 'for ( anno_index=k; anno_index<=k+2;  anno_index++)'
					if (anno_index > i + 1) //QRS????????
					{
						//????????????????
						temp_start = Rlist->arr[i] - (int) (0.1 * fs);
						if (temp_start < 0)
							temp_start = 0;
						temp_end = Rlist->arr[i] + (int) (0.2 * fs);
						if (temp_end > ECG_data->count - 1)
							temp_end = ECG_data->count - 1;
						temp_max = fabs(ECG_data->arr[temp_start]);
						for (j = temp_start; j <= temp_end; j++) 
						{
							if (fabs(ECG_data->arr[j]) > temp_max)
								temp_max = fabs(ECG_data->arr[j]);
						}
						template_max = QRS_Template.arr[0];
						for (j = 1; j < QRS_Template.QRS_len; j++) 
						{
							if (fabs(QRS_Template.arr[j]) > template_max)
								template_max = fabs(QRS_Template.arr[j]);
						}
						if (template_max < temp_max) //???С??
							temp_max = template_max;

						//????????????????г????????
						temp_start = Rlist->arr[i] + (int) (0.2 * fs);
						temp_end = Rlist->arr[i + 1] - (int) (0.2 * fs);
						if (temp_end <= temp_start)
							Rannolist->arr[i] = 0;
						else 
						{
							for (j = temp_start; j <= temp_end; j++) 
							{
								if (fabs(ECG_data->arr[j]) > 0.35 * temp_max)
									break;
							}
							if (j <= temp_end)
								Rannolist->arr[i] = 0;
						}

					}
				} //  end of " if( NULL!=QRS_Template.arr )  // succeed to construct QRS template "
				/*else 
				{
				Rannolist->arr[i] = 0;
				RRlist->arr[i] = RRlist->arr[i - 1];
				}*/

			} // end of " if( i<Rannolist->count-2 ) "
			else 
			{
				Rannolist->arr[i] = 0;
				RRlist->arr[i] = RRlist->arr[i - 1];
			}

		}
#if 0
		//????????ж?
		else if (1 == Rannolist->arr[i]) 
		{
			//??????????????
			noise_anno_start = (long) (Rlist->arr[i]/ ((int) fs * NOISE_TIME_A));
			
		/*	__android_log_print(ANDROID_LOG_INFO, "noise_anno_start","  noise_anno_start  %d", noise_anno_start);
			__android_log_print(ANDROID_LOG_INFO, "noise_anno_start","  Noise_Anno->count  %d", Noise_Anno->count);
				
			if ((noise_anno_start <= Noise_Anno->count - 1)) 
			{
				if (1 == Noise_Anno->arr[noise_anno_start]) 
				{
					Rannolist->arr[i] = 0;
					continue; // ???????????????????????
				}
			}
*///20161111
			//			QRS_Template=CreateQRSTempForRecAbnorlBeat( ECG_data, RRlist, Rlist, i , fs, beat_num, RRmean)  ;
			anno_index = i;
			if (NULL != QRS_Template.arr) // succeed to construct QRS template
			{
				//				MeanSquSum_Temlate=calcu_MeanSquSum( QRS_Template.arr, QRS_Template.QRS_len);
				if (Rlist->arr[anno_index] - (int) (QR_len_global * fs) >= 0)
					Cancel_start = Rlist->arr[anno_index]- (int) (QR_len_global * fs);
				else
					Cancel_start = 0;
				if (Rlist->arr[anno_index] + (int) (RS_len_global * fs)< ECG_data->count)
					Cancel_end = Rlist->arr[anno_index] + (int) (RS_len_global* fs);
				else
					Cancel_end = ECG_data->count - 1;

				temp_double_ptr = &(ECG_data->arr[Cancel_start]);
				dataNum = Cancel_end - Cancel_start + 1;
				Cancel_QRST(QRS_Template.arr, QRS_Template.QRS_len,
					temp_double_ptr, dataNum, Cancel_step,
					&MeanSquSum_error, &Q_location);
				if ((Q_location >= 0) && (MeanSquSum_error > thresh_coff_AB_MB* MeanSquSum_Temlate)) // ??????QRS?????????????
				{
					Rannolist->arr[i] = 0;
				} 
				else if (MeanSquSum_error <= thresh_coff * MeanSquSum_Temlate) 
				{
					//????????????????
					temp_start = Rlist->arr[i] - (int) (0.1 * fs);
					if (temp_start < 0)
						temp_start = 0;
					temp_end = Rlist->arr[i] + (int) (0.2 * fs);
					if (temp_end > ECG_data->count - 1)
						temp_end = ECG_data->count - 1;
					temp_max = fabs(ECG_data->arr[temp_start]);
					for (j = temp_start; j <= temp_end; j++) 
					{
						if (fabs(ECG_data->arr[j]) > temp_max)
							temp_max = fabs(ECG_data->arr[j]);
					}
					template_max = QRS_Template.arr[0];
					for (j = 1; j < QRS_Template.QRS_len; j++) 
					{
						if (fabs(QRS_Template.arr[j]) > template_max)
							template_max = fabs(QRS_Template.arr[j]);
					}
					if (template_max < temp_max) //???С??
						temp_max = template_max;

					//????????????????г????????
					temp_start = Rlist->arr[i] + (int) (0.5 * fs);
					if (i >= Rlist->count - 1)
						temp_end = ECG_data->count - 1;
					else
						temp_end = Rlist->arr[i + 1] - (int) (0.2 * fs);
					if (temp_end <= temp_start)
						Rannolist->arr[i] = 0;
					else 
					{
						for (j = temp_start; j <= temp_end; j++) 
						{
							if (fabs(ECG_data->arr[j]) > 0.5 * temp_max)
								break;
						}
						if (j <= temp_end)
							Rannolist->arr[i] = 0;
					}
				} // end of " else if( MeanSquSum_error<=thresh_coff*MeanSquSum_Temlate ) "


			} // end of " if( NULL!=QRS_Template.arr )  // succeed to construct QRS template "
			/*else
			Rannolist->arr[i] = 0;*/
		} // end of "if( 1==Rannolist->arr[i] )  "

#endif

		//WB?????ж?
		else if ((11 == Rannolist->arr[i]) && (i > 0) && (i < Rannolist->count- 7)) 
		{
			//??????????????
			noise_anno_start = (long) (Rlist->arr[i - 1] / ((int) fs* NOISE_TIME_A));
			noise_anno_end = (long) (Rlist->arr[i + 7] / ((int) fs* NOISE_TIME_A));
			if ((noise_anno_start <= Noise_Anno->count - 1) && (noise_anno_end<= Noise_Anno->count - 1)) {
				for (j = noise_anno_start; j <= noise_anno_end; j++) 
				{
					if (1 == Noise_Anno->arr[j])
						break;
				}
				if (j <= noise_anno_end) 
				{
					Rannolist->arr[i] = 0;
					continue; // ???????????????????????
				}
			}

		} // end of " else if( (11==Rannolist->arr[i]) && (i>0) && (i<Rannolist->count-7) )   "

	} // end of ' for ( i=0; i<Rannolist->count; i++ ) '

	//(ANDROID_LOG_INFO, "ReDiagnoseAbnomalBeat","%s"," ggss         3  ");

	if (QRS_Template.arr) 
	{
		free(QRS_Template.arr);
		QRS_Template.arr = NULL;
	}

	result.PAB = 0;
	result.PVB = 0;
	result.Insert_PVBnum = 0;
	result.Missed_Num = 0;
	result.Wide_Num = 0;
	result.Bigeminy_Num = 0;
	result.Trigeminy_Num = 0;
	result.VT = 0;
	result.Arrest_Num = 0;
	result.Wrong_Num = 0;

	for (i = 0; i < Rannolist->count; i++) 
	{
		switch (Rannolist->arr[i]) 
		{
		case -1:
			result.Wrong_Num++;
			break;
		case 1:
			result.Arrest_Num++;
			break;
		case 2:
			result.Missed_Num++;
			break;
		case 3:
			result.PVB++;
			break;
		case 4:
			result.PAB++;
			break;
		case 5:
			result.Insert_PVBnum++;
			break;
		case 6:
			result.VT++;
			break;
		case 7:
			result.Bigeminy_Num++;
			break;
		case 8:
			result.Trigeminy_Num++;
			break;
		case 9:
			//typestring = "ST";
			break;
		case 10:
			//typestring = "SB";
			break;
		case 11:
			result.Wide_Num++;
			break;
		case 12:
			//typestring = "AR";
			break;
		}
	}

	return 0;
}
int maindetect::GETLONGRR(LONG_ARR *new_RRlist, LONG_ARR *Rannolist) 
{
	int i = 0;
	int longRR = 0;

	for (i = 0; i < new_RRlist->count; i++) 
	{
		if (new_RRlist->arr[i] > (valuesa * 1000) && Rannolist->arr[i] == 1)
			longRR = new_RRlist->arr[i];

	}
	return longRR;
}
int maindetect::GETWIDEWAVE(struct data_buffer *buf, LONG_ARR *QRSlist,
							LONG_ARR *Rlist, LONG_ARR *noiselist_A, int Rnumneed, int QRSwide,
							double percent, LONG_ARR *Rannolist) 
{
	int i = 0;
	int j = 0;
	int k = 0;
	int flag = 1;//?????????
	int wide_temp = 0;
	int widenum = 0;
	int startnois = 0;
	int endnois = 0;
	for (i = 0; i < QRSlist->count - Rnumneed; i++) 
	{
		wide_temp = 0;

		for (j = 0; j < Rnumneed; j++) 
		{
			if ((QRSlist->arr[i + j] > QRSwide)&&(fabs(buf->orig00[Rlist->arr[i + j]])>6))
				wide_temp++;

		}
		if (wide_temp > percent * Rnumneed) 
		{
			startnois = (int) (Rlist->arr[i] / valuefs);
			endnois = (int) (Rlist->arr[i + Rnumneed - 1] / valuefs);

			for (k = startnois; k < endnois; k++) 
			{
				if (noiselist_A->arr[k] == 1) 
				{
					flag = 0;//?????м??????????
					break;
				}
			}
			if (flag == 1) 
			{
				for (j = 0; j < Rnumneed; j++) 
				{
					if (Rannolist->arr[i + j] == 0 && buf->temp_maxdiff > 6
						&& QRSlist->arr[i + j] > QRSwide) 
					{
						Rannolist->arr[i + j] = 11;
						widenum = 1;
						break;
					}
				}
			}

			if (widenum == 1)
				break;
		}
	}
	return widenum;
}
int maindetect::GETTRUETIMEL(LONG_ARR *noiselist_A) 
{
	int timeall = 0;
	int i = 0;
	for (i = 0; i < noiselist_A->count; i++) 
	{
		timeall += noiselist_A->arr[i];
	}
	timeall = noiselist_A->count - timeall;
	return timeall;
}

/*
void maindetect::GETDAYNIGHT(LONG_ARR *Rlist,LONG_ARR *RRlist)
{
int i=0;
int timehour=(int)(Rlist->arr[Rlist->count-1]/(valuefs*3600));
long sum_day=0;
int day_r=0;
long sum_night=0;
int night_r=0;
if(start_hour>=6&&start_hour<=22)//6??22?????????
{
for (i=0;i<Rlist->count-1;i++)
{
if((int)(Rlist->arr[i]/(valuefs*3600))<=(22-start_hour))
{
sum_day+=RRlist->arr[i];
day_r++;
}
else
{
sum_night+=RRlist->arr[i];
night_r++;
}
}

}
else if(start_hour<6)
{
if(timehour+start_hour<=6)//?????0??6?????????????????
{
sum_day=0;
}
for (i=0;i<Rlist->count-1;i++)
{
sum_night+=RRlist->arr[i];
night_r++;
}

}
else//?????22????????????
{
if(timehour+start_hour<=30)//?????????
{
sum_day=0;
}
else
{
for (i=0;i<Rlist->count-1;i++)
{
if((int)(Rlist->arr[i]/(valuefs*3600))<=(30-start_hour))
{
sum_night+=RRlist->arr[i];
night_r++;
}
else
{
sum_day+=RRlist->arr[i];
day_r++;
}
}

}

}
if(night_r!=0)
sum_night=(int)(60000.0/(sum_night/(double)night_r));
else
sum_night=0;
if(day_r!=0)
sum_day=(int)(60000.0/(sum_day/(double)day_r));
else
sum_day=0;

result.Dayheartrate=sum_day;
result.Nightheartrate=sum_night;


}

*/
int maindetect::GETPVBPERMIN(LONG_ARR *Rlist, LONG_ARR *Rannolist, int number) 
{
	int i = 0;
	int pvb5num = 0;
	vector<int> pvbpos;

	for (i = 0; i < Rlist->count; i++) 
	{
		if (Rannolist->arr[i] == 3 || Rannolist->arr[i] == 5) 
		{
			pvbpos.push_back(Rlist->arr[i]);
		}

	}

	if (result.PVB + result.Insert_PVBnum > 5) 
	{
		for (i = 0; i < (int) pvbpos.size() - 5; i ++) 
		{
			if (pvbpos[i + 5] - pvbpos[i] < valuefs * 60)
				pvb5num++;
		}

	} 
	else 
	{
		return 0;
	}

	if (pvb5num > number)
		return 1;
	else
		return 0;

}
void maindetect::GETguohuansuTIME(LONG_ARR *RRlist, LONG_ARR *Rannolist)
{
	//20161101 yly 增加了过速和过缓的位置标记及个数，修正了判断规则
	int guosutime = 0;
	int guohuantime = 0;
	int i = 0;
	int guosuNum = 0;//20161101
	int guohuanNum = 0;//20161101

	for (i = 1; i < RRlist->count - 1; i++) 
	{
		if (RRlist->arr[i - 1] >= 60000.0/valuesb && RRlist->arr[i] >= 60000.0/valuesb
			&& RRlist->arr[i + 1] >= 60000.0/valuesb) 
		{
			guohuantime += RRlist->arr[i];//yly 20161101 原guosutime
			//(ANDROID_LOG_INFO, "GETguohuansuTIME","i=%d Rannolist  %d , %d, %d",i,Rannolist->arr[i],Rannolist->arr[i-1], Rannolist->arr[i+1]);
			if (Rannolist->arr[i - 1] ==0 && Rannolist->arr[i] ==0
			&& Rannolist->arr[i + 1] ==0)
			{
				Rannolist->arr[i-1] = 12;
				Rannolist->arr[i] = 12;
				Rannolist->arr[i+1] = 12;
				guohuanNum ++;

				//(ANDROID_LOG_INFO, "GETguohuansuTIME","xxxx  Rannolist  %d",Rannolist->arr[i]);

		  }
		  else if(Rannolist->arr[i-1] == 12 && Rannolist->arr[i] == 12 && Rannolist->arr[i+1] == 0)
		  {
		  	Rannolist->arr[i+1] = 12;
		  }
		}
		if (RRlist->arr[i - 1] <= 60000.0/valuesu && RRlist->arr[i] <= 60000.0/valuesu
			&& RRlist->arr[i + 1] <= 60000.0/valuesu) 
		{
			guosutime += RRlist->arr[i];//yly 20161101 原guohuantime
			if (Rannolist->arr[i - 1] ==0 && Rannolist->arr[i] ==0
			&& Rannolist->arr[i + 1] ==0)
			{
			Rannolist->arr[i-1] = 13;
			Rannolist->arr[i] = 13;
			Rannolist->arr[i+1] = 13;
			guosuNum ++;
		  }
		  else if(Rannolist->arr[i-1] == 13 && Rannolist->arr[i] == 13 && Rannolist->arr[i+1] == 0)
		  {
		  	Rannolist->arr[i+1] = 13;
		  }
		}
	}
	result.guosutime = (int) (guosutime / 1000);
	result.guohuantime = (int) (guohuantime / 1000);
	result.guosuNum = guosuNum;     //过整数量
	result.guohuanNum = guohuanNum;     //过缓数量

	//(ANDROID_LOG_INFO, "GETguohuansuTIME"," guosuNum  %d",result.Polycardia);
	//(ANDROID_LOG_INFO, "GETguohuansuTIME"," guosuNum  %d",guosuNum);
	//(ANDROID_LOG_INFO, "GETguohuansuTIME"," guohuanNum  %d",result.Polycardia);
	//(ANDROID_LOG_INFO, "GETguohuansuTIME"," guohuanNum  %d",guohuanNum);
}


struct ecg_result maindetect::getecgresult(double *orig00, long ecgnum, int Fs, int GainK)
{
	ECG_Diagnose_resultAll  ECG_Diagnose_resultTotal;  // dai  20120906: ECG analisis results per hour
	double Noml_ECG_MeanSquSum=0;    // mean square sum of 1s normal ECG, used for identifying noise segments

	ofstream ofs;
	struct ecg_info ci;
	struct data_buffer buf;

	result.AbECGNum = 0;//
	result.AnalysisOk = 0;
	result.Arrest_Num = 0;
	result.Bigeminy_Num = 0;
	result.Bradycardia = 0;
	result.Fastest_Beat = 0;
	result.Fastest_Time = 0;
	result.HF = 0;
	result.HFLevel = 0;//0 represent nornal; 1 represent high;-1 represent low
	result.HRVI = 0;
	result.HRVILevel = 0;
	result.HeartNum = 0;
	result.HeartRate = 0;
	result.HRLevel = 0;
	result.ImageNum = 0;
	result.Insert_PVBnum = 0;
	result.iCount = 0;
	result.LF = 0;
	result.LFLevel = 0;
	result.LF_HF_Ratio = 0;
	result.LHRLevel = 0;
	result.Missed_Num = 0;
	result.Wide_Num = 0;

	result.PVBPerHour=0;
	result.longRR=0;//??RR?????????????????
	result.turetime=0;//??Ч???
	result.Dayheartrate=0;
	result.Nightheartrate=0;
	result.guohuantime=0;
	result.guosutime=0;

	result.PAB = 0;
	result.PNN50 = 0;
	result.PNN50Level = 0;
	result.PSDfile = "";
	result.PSDfileID = "";
	result.PVB = 0;
	result.Polycardia = 0;
	result.RMSSD = 0;
	result.RMSSDLevel = 0;
	result.RRfile = "";
	result.RRfileID = "";
	result.SD1 = 0;
	result.SD2 = 0;
	result.SDNN = 0;
	result.SDNNLevel = 0;
	result.TimeLength = 0;
	result.Slowest_Beat = 0;
	result.Slowest_Time = 0;
	result.TP = 0;
	result.TPLevel = 0;
	result.Trigeminy_Num = 0;
	result.VLF = 0;
	result.VLFLevel = 0;
	result.VT = 0;
	result.ECGResult = 0;
	result.flagAR = 0;//LSJ
	result.Wrong_Num = 0;

	wideflag = 0;

	//! chenbk
	result.AbECG = NULL;
	result.Arrest_posL = NULL;
	result.Missed_posL = NULL;
	result.PVBposL = NULL;
	result.PABposL = NULL;
	result.Insert_PVBposL = NULL;
	result.VT_posL = NULL;
	result.Bigeminy_posL = NULL;
	result.Trigeminy_posL = NULL;
	result.Wide_posL = NULL;

	result.axislist.arr=NULL;
	result.d2list.arr=NULL;
	result.noiselist_A.arr=NULL;
	//result.noiselist.arr=NULL;
	result.Rannolist.arr=NULL;
	result.Rlist.arr=NULL;
	result.RRlist.arr=NULL;
	result.QRSlist.arr=NULL;
	result.speclist.arr=NULL;
	result.Diagnose_resultPerHourList.arr=NULL;

	buf.num_data=0;//???????????
	buf.data_offset=0;//?????????????
	buf.orig=NULL;//??ζ??????????
	buf.orig00=NULL;//???е???????
	buf.f0=NULL;
	buf.f1=NULL;
	buf.s1=NULL;//????R???????????
	//buf.noiselist.count=0;
	//buf.noiselist.arr=NULL;
	buf.noiselist_A.count=0;//2012.3.7
	buf.noiselist_A.arr=NULL;
	buf.ecgmean=0;//LSJ
	buf.s1mean=0;//s1??????
	buf.temp_mean=0;//??????????????
	buf.temp_maxdiff=0;//??????????С???
	buf.temp_Rvalue=0;
	//	memset(&buf, 0, sizeof(struct data_buffer));//?????2012.1.30
	memset(&ci, 0, sizeof(struct ecg_info));

	int do_interpolation = 0;
	int ret = 0;
	int flagabnormal=1;//when get the template, a method to know the quality of wave 
	long l = 0;

	LONG_ARR Rlist;
	LONG_ARR PSD_RRlist;
	LONG_ARR PSD_RRlist_psd;
	LONG_ARR PSD_Rlist;
	LONG_ARR Rannolist;//SG
	LONG_ARR QRS_startlist;
	LONG_ARR QRS_endlist;
	LONG_ARR QRSlist;
	LONG_ARR RRlist;
	//	LONG_ARR new_RRlist;
	LONG_ARR RRlistImg;  // for HRV plot in TV

	double SD1;
	double SD2;

	//(ANDROID_LOG_INFO, "TAGNNNN","%s"," hello   1   XXXXXXXXXXXXXXXXXXXXXXXXXxxx");

	ci.samplerate_orig = (double) (Fs);
	ci.samplerate = ci.samplerate_orig;//SG
	ci.interp_factor = 1;
	ci.gain = (double) (GainK);
	ci.hearthigh = (int)valuesu;
	ci.heartlow = (int)valuesb;
	ci.heartneed = 10;//
	ci.papercent = valuepa/100.0;
	ci.pvpercent = valuepv/100.0;
	ci.arrest_time =(int)(valuesa*1000);
	ci.VT_value = (int)valuevt;//SG
	double RRmean = 0;

	//(ANDROID_LOG_INFO, "ci.samplerate", "ci.samplerate=  %d", (int)(ci.samplerate));

	int storelength = (int) (ci.samplerate_orig * 6);//abmomal store 1200 points,?????洢6????????

	ret = prepare_data_access(do_interpolation, &ci, &buf);
	if (ret != 0)
	{
		return result;
	}

	ci.num_samples = ecgnum;//get the ecgdata raw number
	result.TimeLength = (long) (ci.num_samples / ci.samplerate_orig);//get the data length(s)

	//////////////////////////////////
	//??????????
    struct timeval base_start, base_end;
    float base_time;
    gettimeofday(&base_start, NULL);
	/////////////////////////////////////////
	buf.d2list =ECG_NO_NOISE2_A(orig00, ci.num_samples,ci.samplerate_orig);//??????????
	///////////////////////////////////////////////////////////////////
	gettimeofday(&base_end, NULL);
	base_time = (base_end.tv_sec - base_start.tv_sec) + (base_end.tv_usec - base_start.tv_usec)/1000000.0;
    cout <<"??????????" << base_time << "??" << endl;
    ///////////////////////////////////////////
	if (NULL==buf.d2list.arr)
	{
		result.AnalysisOk = 1;
		return result;
	}
	buf.orig00=buf.d2list.arr;
	//??????????
    struct timeval noise_start, noise_end;
    float noise_time;
    gettimeofday(&noise_start, NULL);
	/////////////////////////////////////////
	buf.noiselist=ECG_NO_NOISE2013(buf.orig00, ci.num_samples,ci.samplerate_orig);  //???????5s ????
	///////////////////////////////////////////////////////////////////
	gettimeofday(&noise_end, NULL);
	noise_time = (noise_end.tv_sec - noise_start.tv_sec) + (noise_end.tv_usec - noise_start.tv_usec)/1000000.0;
    cout <<"ECG??????????" << noise_time << "??" << endl;
    ///////////////////////////////////////////

	if (NULL==buf.noiselist.arr)
	{
		free(buf.d2list.arr);
		result.AnalysisOk = 1;

		return result;
	}	


	//?????
    struct timeval detect_start, detect_end;
    float detect_time;
    gettimeofday(&detect_start, NULL);
	/////////////////////////////////////////
	getQRSlist(&Rlist, &QRS_startlist, &QRS_endlist, &ci, &buf);//get the R,Q,S position

	//(ANDROID_LOG_INFO, "TAGNNNN","%s"," hello   2   XXXXXXXXXXXXXXXXXXXXXXXXXxxx");
	///////////////////////////////////////////////////////////////////
	gettimeofday(&detect_end, NULL);
	detect_time = (detect_end.tv_sec - detect_start.tv_sec) + (detect_end.tv_usec - detect_start.tv_usec)/1000000.0;
    cout <<"QRS?????" << detect_time << "??" << endl;
    ///////////////////////////////////////////
	if (Rlist.count <= 10)    // R wave number is too small to diagnose, so just return directly 
	{
		if(NULL!=Rlist.arr)
			free(Rlist.arr);
		if(NULL!=QRS_startlist.arr)
			free(QRS_startlist.arr);
		if(NULL!=QRS_endlist.arr)
			free(QRS_endlist.arr);
		free(buf.noiselist.arr);
		free(buf.d2list.arr);
		result.AnalysisOk = 1;
		result.RRlist.count = 0;
		//(ANDROID_LOG_INFO, "TAGNNNN","%s"," hello   21   XXXXXXXXXXXXXXXXXXXXXXXXXxxx");
		//(ANDROID_LOG_INFO, "TAGNNNN","count  %d",  Rlist.count);
		return result;
	}
	else
	{
		//????????
		struct timeval abnormal_start, abnormal_end;
		float abnormal_time;
		gettimeofday(&abnormal_start, NULL);
		/////////////////////////////////////////
		//(ANDROID_LOG_INFO, "TAGNNNN","%s"," hello   22   XXXXXXXXXXXXXXXXXXXXXXXXXxxx");

		RRlist = getRRlist(&Rlist, ci.samplerate_orig);//get the RRlist for the first time
		if(NULL==RRlist.arr)
		{
			result.AnalysisOk = 1;
			return result;
		}
		//(ANDROID_LOG_INFO, "TAGNNNN","%s"," hello   22  1  XXXXXXXXXXXXXXXXXXXXXXXXXxxx");

		RRmean = getRRmean(&RRlist);//??????????RR????????????????μ????????????
		//(ANDROID_LOG_INFO, "TAGNNNN","%s"," hello   22  2  XXXXXXXXXXXXXXXXXXXXXXXXXxxx");

		flagabnormal=Get_QRST_Template(&Rlist, &RRlist, &buf, ci.samplerate_orig, ci.num_samples,RRmean, 20 , &Noml_ECG_MeanSquSum);  // ???QRST??壬dai huhe

		//(ANDROID_LOG_INFO, "xxxxxxxx1 "," RRlist->arr[24] = %d ", RRlist.arr[24]);
		//(ANDROID_LOG_INFO, "xxxxxxxx1 "," RRlist->arr[25] = %d ", RRlist.arr[25]);
		//(ANDROID_LOG_INFO, "xxxxxxxx1 "," RRlist->arr[26] = %d ", RRlist.arr[26]);

		//(ANDROID_LOG_INFO, "TAGNNNN","%s"," hello   22  3  XXXXXXXXXXXXXXXXXXXXXXXXXxxx");

		if( 1!=flagabnormal ) // if Get_QRST_Template fails, then use GET_TEMPLATE_NEW
		{
			//(ANDROID_LOG_INFO, "TAGNNNN","%s"," hello   22  4  XXXXXXXXXXXXXXXXXXXXXXXXXxxx");
			flagabnormal = GET_TEMPLATE_NEW(&Rlist, &RRlist, &buf, ci.samplerate_orig, ci.num_samples,RRmean);//find the template of the normal beat,ret=0,the data is bad.
			Noml_ECG_MeanSquSum=300;  //default value
		}

		//(ANDROID_LOG_INFO, "xxxxxxxx2 "," RRlist->arr[24] = %d ", RRlist.arr[24]);
		//(ANDROID_LOG_INFO, "xxxxxxxx2 "," RRlist->arr[25] = %d ", RRlist.arr[25]);
		//(ANDROID_LOG_INFO, "xxxxxxxx2 "," RRlist->arr[26] = %d ", RRlist.arr[26]);

		//(ANDROID_LOG_INFO, "TAGNNNN","%s"," hello   23   XXXXXXXXXXXXXXXXXXXXXXXXXxxx");
		buf.noiselist_A=ECG_NO_NOISE_A_New2013( &buf.noiselist, Noml_ECG_MeanSquSum, ci.samplerate_orig, buf.d2list.arr, buf.d2list.count);  //added by Dai 20121023,get the noise through 1s data
		if(NULL==buf.noiselist_A.arr)
		{
			result.AnalysisOk = 1;
			return result;
		}
		//(ANDROID_LOG_INFO, "TAGNNNN","%s"," hello   24   XXXXXXXXXXXXXXXXXXXXXXXXXxxx");
/*
		for(int k = 0; k < buf.noiselist_A.count; k++)
		{
			buf.noiselist_A.arr[k] = 0;
		}
		//RRlist1.
*/
		free(RRlist.arr);
		RRlist.arr = NULL;
		RRlist=DROP_WRONG_RLIST2013(&Rlist,&buf.noiselist_A, &QRS_startlist,&QRS_endlist,&Rannolist, &buf,ci.samplerate_orig,RRmean, &result);//??????????????????ζ?RR?????????????????


		//RRlist = getRRlist(&Rlist, ci.samplerate_orig);//get the RRlist for the first time
		if(NULL==RRlist.arr)
		{
			result.AnalysisOk = 1;
			return result;
		}
		//(ANDROID_LOG_INFO, "TAGNNNN","%s"," hello   25   XXXXXXXXXXXXXXXXXXXXXXXXXxxx");

//		__android_log_print(ANDROID_LOG_INFO, "xxxxxxxx3 "," RRlist->arr[24] = %d ", RRlist.arr[24]);
//		__android_log_print(ANDROID_LOG_INFO, "xxxxxxxx3 "," RRlist->arr[25] = %d ", RRlist.arr[25]);
//		__android_log_print(ANDROID_LOG_INFO, "xxxxxxxx3 "," RRlist->arr[26] = %d ", RRlist.arr[26]);
		/*
		//9.5 ????????????μ???????????
		Rannolist.arr = (long *) malloc((Rlist.count) * sizeof(long));
		Rannolist.count = Rlist.count;
		memset(Rannolist.arr, 0, Rlist.count);
		int ll;

		for (ll = 0; ll < Rannolist.count; ll++)
		{
		Rannolist.arr[ll] = 0;
		}

		*/
		QRSlist = getQRSWIDTHlist(&QRS_startlist, &QRS_endlist, ci.samplerate_orig);//get the QRSwidth
		if(NULL==QRSlist.arr)
		{
			result.AnalysisOk = 1;
			return result;
		}
		//(ANDROID_LOG_INFO, "TAGNNNN","%s"," hello   26   XXXXXXXXXXXXXXXXXXXXXXXXXxxx");
		ret = getothers(&RRlist, &QRSlist, &Rannolist, &result, ci.pvpercent, ci.papercent, ci.arrest_time, ci.VT_value, &Rlist, &buf);	//design the feature of beat???????????з???
		RRlistImg=RRlist;

		//RRlistImg=gethighlowheart_New(&new_RRlist, &Rlist, ci.heartneed, ci.samplerate_orig, &result,  (int)RRmean );    // added by dai 20121023

		result.flagAR = getAR_high(&RRlist, &Rannolist, RRmean);//?ж???????????????????????????????
		ret = GET_NEWRannolist_NEW2013(&Rlist,&RRlist, &Rannolist, &buf, ci.samplerate_orig, ci.num_samples,RRmean,&QRSlist);  //???????????ж????
		ret = GET_NEWRannolist_NEW2013(&Rlist,&RRlist, &Rannolist, &buf, ci.samplerate_orig, ci.num_samples,RRmean,&QRSlist);  //????????????????????????
		
    //(ANDROID_LOG_INFO, "DROP_WRONG_RLIST2013 "," 0result.Arrest_Num = %d ",result.Arrest_Num);
    //(ANDROID_LOG_INFO, "DROP_WRONG_RLIST2013 "," result.Missed_Num = %d ",result.Missed_Num);
		if (result.Missed_Num > 0 || result.Arrest_Num > 0)
		{
			ret = GET_NEWRannolist_AFTER(&Rlist, &RRlist, &Rannolist, &buf,ci.samplerate_orig);//make sure the missed beat and arrest beat????????????????????????????
			//(ANDROID_LOG_INFO, "DROP_WRONG_RLIST2013 "," 00result.Arrest_Num = %d ",result.Arrest_Num);
		}
		//(ANDROID_LOG_INFO, "TAGNNNN","%s"," hello   27   XXXXXXXXXXXXXXXXXXXXXXXXXxxx");
		
			//(ANDROID_LOG_INFO, "DROP_WRONG_RLIST2013 "," 000result.Arrest_Num = %d ",result.Arrest_Num);

		ReDiagnoseAbnomalBeat( &(buf.d2list), &RRlist, &Rlist , &Rannolist, ci.samplerate_orig, &ci,  (int)RRmean, &buf.noiselist_A ); //????????????????????????????????????


			//(ANDROID_LOG_INFO, "DROP_WRONG_RLIST2013 "," 111RRlist->arr[i%d] = %d ", 51, RRlist.arr[51]);
			//(ANDROID_LOG_INFO, "DROP_WRONG_RLIST2013 "," result.Arrest_Num = %d ",result.Arrest_Num);


		//(ANDROID_LOG_INFO, "TAGNNNN","%s"," hello   27  1 XXXXXXXXXXXXXXXXXXXXXXXXXxxx");

		PSD_RRlist_psd= get_PSD_RRlist(&RRlist,&PSD_Rlist,&Rlist, &Rannolist,ci.samplerate_orig,&buf.noiselist_A);//???????5????????????????HRV????

		//(ANDROID_LOG_INFO, "TAGNNNN","%s"," hello   27  2 XXXXXXXXXXXXXXXXXXXXXXXXXxxx");

		PSD_RRlist=get_PSD_RRlist_all(&RRlist, &Rannolist,ci.samplerate_orig);//???????????з???????RR????????з?????????HRV????
		//(ANDROID_LOG_INFO, "TAGNNNN","%s"," hello   27  3 XXXXXXXXXXXXXXXXXXXXXXXXXxxx");

		result.longRR=GETLONGRR(&RRlist,&Rannolist);//??????????????￡?????????
		//(ANDROID_LOG_INFO, "TAGNNNN","%s"," hello   27  4 XXXXXXXXXXXXXXXXXXXXXXXXXxxx");
		result.turetime=GETTRUETIMEL(&buf.noiselist_A);//?????Ч???????????
		//(ANDROID_LOG_INFO, "TAGNNNN","%s"," hello   27  5 XXXXXXXXXXXXXXXXXXXXXXXXXxxx");
		result.Wide_Num=GETWIDEWAVE(&buf,&QRSlist,&Rlist,&buf.noiselist_A,150,120,0.75,&Rannolist);//?ж???????????????β?
		//(ANDROID_LOG_INFO, "TAGNNNN","%s"," hello   27  6 XXXXXXXXXXXXXXXXXXXXXXXXXxxx");
		result.PVBPerHour=GETPVBPERMIN(&Rlist, &Rannolist,10);//?ж??????????????????????5????????1??????????
		GETguohuansuTIME(&RRlist, &Rannolist);//????????????????????????????￡?????????????????????
		//		GETDAYNIGHT(&Rlist,&new_RRlist);
		////////////////////******************************
		//(ANDROID_LOG_INFO, "TAGNNNN","%s"," hello   28   XXXXXXXXXXXXXXXXXXXXXXXXXxxx");
		if(result.flagAR==-1)
		{
			return result;
		}
		///////////////////////////////////////////////////
		if (result.Fastest_Beat > ci.hearthigh)
			result.Polycardia = 1;
		if (result.Slowest_Beat < ci.heartlow)
			result.Bradycardia = 1;//sg
//		result.Fastest_Time = (int) (Rlist.arr[result.Fastest_Time]/ ci.samplerate_orig);
//		result.Slowest_Time = (int) (Rlist.arr[result.Slowest_Time]/ ci.samplerate_orig);
		////////////////////////////////////////////////
		/*
		int abtype_num = (result.Polycardia != 0) + (result.Bradycardia != 0)
		+ (result.Bigeminy_Num != 0) + (result.Trigeminy_Num != 0)
		+ (result.Arrest_Num != 0) + (result.Missed_Num != 0)
		+ (result.PVB != 0) + (result.PAB != 0) + (result.VT != 0)
		+ (result.Wide_Num != 0) + (result.flagAR != 0)+(result.Insert_PVBnum!=0);
		*/
		////////////////////////////////////////////////////
		///////////////////////////////////////////////////
		//(ANDROID_LOG_INFO, "TAGNNNN","%s"," hello   29   XXXXXXXXXXXXXXXXXXXXXXXXXxxx");
		//(ANDROID_LOG_INFO, "DROP_WRONG_RLIST2013 "," 1result.Arrest_Num = %d ",result.Arrest_Num);
		if (result.Polycardia + result.Bradycardia + result.Arrest_Num
			+ result.Missed_Num + result.PVB + result.PAB
			+ result.Insert_PVBnum + result.VT + result.Bigeminy_Num
			+ result.Trigeminy_Num + result.Wide_Num + result.flagAR > 0)
		{//?????????????
			result.ECGResult = 1;

			int abtype = 0;

			if (result.Arrest_Num > 0)
			{
				abtype = 1;
				result.Arrest_posL = getposL(&Rannolist, result.Arrest_Num,
					abtype, &Rlist, ci.samplerate_orig);//????????λ???????

			}
			if (result.Missed_Num > 0)
			{
				abtype = 2;
				result.Missed_posL = getposL(&Rannolist, result.Missed_Num,
					abtype, &Rlist, ci.samplerate_orig);
			}
			if (result.Wide_Num > 0)
			{//SG
				abtype = 11;
				result.Wide_posL = getposL(&Rannolist, result.Wide_Num, abtype,
					&Rlist, ci.samplerate_orig);
			}

			if (result.PVB > 0)
			{
				abtype = 3;
				result.PVBposL = getposL(&Rannolist, result.PVB, abtype,
					&Rlist, ci.samplerate_orig);
			}
			if (result.PAB > 0)
			{
				abtype = 4;
				result.PABposL = getposL(&Rannolist, result.PAB, abtype,
					&Rlist, ci.samplerate_orig);

			}
			if (result.Insert_PVBnum > 0)
			{
				abtype = 5;
				result.Insert_PVBposL = getposL(&Rannolist,
					result.Insert_PVBnum, abtype, &Rlist,
					ci.samplerate_orig);

			}
			if (result.VT > 0)
			{
				abtype = 6;
				result.VT_posL = getposL(&Rannolist, result.VT, abtype, &Rlist,
					ci.samplerate_orig);
			}
			if (result.Bigeminy_Num > 0)
			{
				abtype = 7;
				result.Bigeminy_posL = getposL(&Rannolist, result.Bigeminy_Num,
					abtype, &Rlist, ci.samplerate_orig);
			}

			if (result.Trigeminy_Num > 0)
			{
				abtype = 8;
				result.Trigeminy_posL = getposL(&Rannolist,
					result.Trigeminy_Num, abtype, &Rlist,
					ci.samplerate_orig);
			}
			if (result.guosuNum > 0)  //过速
			{
				abtype = 13;
				result.guosu_posL = getposL(&Rannolist,
								result.guosuNum, abtype, &Rlist,
								ci.samplerate_orig);
				for(int i=0; i<result.guosuNum; i++)
				{
					//(ANDROID_LOG_INFO, "SignallibR getecgResult Polycardia ","%d",result.guosu_posL[i]);
				}
			}

			if (result.guohuanNum > 0)
			{
				abtype = 12;
				result.guohuan_posL = getposL(&Rannolist,
								result.guohuanNum, abtype, &Rlist,
								ci.samplerate_orig);
			}

		}
		else
		{
			result.ECGResult = 0;
		}

		result.HeartNum = Rlist.count;//

//(ANDROID_LOG_INFO, "TAGNNNN","%s"," hello   3   XXXXXXXXXXXXXXXXXXXXXXXXXxxx");

		long i = 0;
		double sumRR = 0;
		if(NULL!=RRlist.arr)//20161115
		{
			for (i = 0; i < RRlist.count; i++)
			{		
				sumRR += RRlist.arr[i];
			}
			RRmean = sumRR / RRlist.count;
		}

		if (RRmean > 0)
		{
			result.HeartRate = (long) (60000 / RRmean);//
		}
		else
		{
			result.HeartRate = (long) ((Rlist.count - 1)
				/ ((double) (Rlist.arr[Rlist.count - 1] - Rlist.arr[0])
				/ ci.samplerate) * 60);

		}
		if (result.HeartRate > ci.hearthigh)
		{
			result.HRLevel = 1;
		}
		else if (result.HeartRate < ci.heartlow)
		{
			result.HRLevel = -1;
		}
		else
		{
			result.HRLevel = 0;
		}

//(ANDROID_LOG_INFO, "TAGNNNN","%s"," hello   4   XXXXXXXXXXXXXXXXXXXXXXXXXxxx");

		////////////////////////////////
		if(NULL!=PSD_RRlist.arr)
		{
			result.SDNN = calc_sdnn(&PSD_RRlist);
			result.SDNN = get2double(result.SDNN);

			if (result.SDNN > SDNNStd_H)
			{
				result.SDNNLevel = 1;
			}
			else if (result.SDNN < SDNNStd_L)
			{
				result.SDNNLevel = -1;
			}
			else
			{
				result.SDNNLevel = 0;
			}
			result.HRVI = calc_hrvi(&PSD_RRlist);
			result.HRVI = get2double(result.HRVI);

			if (result.HRVI > HRVIStd_H)
			{
				result.HRVILevel = 1;
			}
			else if (result.HRVI < HRVIStd_L)
			{
				result.HRVILevel = -1;
			}
			else
			{
				result.HRVILevel = 0;
			}
			result.PNN50 = calc_pnn50(&PSD_RRlist);
			result.PNN50 = get2double(result.PNN50);

			if (result.PNN50 > PNN50Std_H)
			{
				result.PNN50Level = 1;
			}
			else if (result.PNN50 < PNN50Std_L)
			{
				result.PNN50Level = -1;
			}
			else
			{
				result.PNN50Level = 0;
			}
			result.RMSSD = calc_rmssd(&PSD_RRlist);
			result.RMSSD = get2double(result.RMSSD);

			if (result.RMSSD > RMSSDStd_H)
			{
				result.RMSSDLevel = 1;
			}
			else if (result.RMSSD < RMSSDStd_L)
			{
				result.RMSSDLevel = -1;
			}
			else
			{
				result.RMSSDLevel = 0;
			}
			ret = calc_poincare(&PSD_RRlist, &SD1, &SD2);
			result.SD1 = get2double(SD1);
			result.SD2 = get2double(SD2);
		}

//(ANDROID_LOG_INFO, "TAGNNNN","%s"," hello   5   XXXXXXXXXXXXXXXXXXXXXXXXXxxx");

		result.iCount = (long) (ecgnum / ci.samplerate_orig / 40) + 1;
		result.ImageNum = 3 + result.iCount + result.AbECGNum;//return the painting num  sg need change(need the wrong ecg data)

		long n_spec = 0;
		DOUB_ARR speclist;
		DOUB_ARR axislist;
		speclist.arr=NULL;
		axislist.arr=NULL;
		speclist.count = 0;
		axislist.count = 0;
		//sg refine the psd method
		double usesample = 1000.0 / EQUIDIST_MS;
		if(PSD_RRlist_psd.count>200)
		{
			double *values;
			long real_num = 0;

			ret = process_values(&PSD_RRlist_psd, &PSD_Rlist, &values, ci.samplerate_orig,usesample, &real_num);
			speclist= calc_periodogram(values, real_num, usesample, &n_spec);//PSD
			axislist.arr = (double *) malloc((n_spec) * sizeof(double));
			axislist.count = n_spec;
			if(ret==-1 || NULL==axislist.arr )//??治??
			{
				return result;
			}

			long storelengthpsd = 0;//SGSG
			int flagfirst = 0;
			double curr_freq;
			double freq_step;
			curr_freq = 0;
			freq_step = usesample / (double) (n_spec * 2);//SGSG keep the axis length is 1
			for (l = 0; l < n_spec; l++)
			{
				axislist.arr[l] = curr_freq;
				curr_freq += freq_step;
				if ((curr_freq > 1.0) && (flagfirst == 0))//SGSG
				{
					storelengthpsd = l;
					flagfirst = 1;
				}
			}
			//sg

			result.TP = calc_power(TOTAL_POWER_START, TOTAL_POWER_END, EQUIDIST_MS,
				&speclist, n_spec);

			free(values);
			result.TP = get2double(result.TP);
			if (result.TP > TPStd_H)
			{
				result.TPLevel = 1;
			}
			else if (result.TP < TPStd_L)
			{
				result.TPLevel = -1;
			}
			else
			{
				result.TPLevel = 0;
			}

			result.LF
				= calc_power(LF_START, LF_END, EQUIDIST_MS, &speclist, n_spec);
			result.LF = get2double(result.LF);
			if (result.LF > LFStd_H)
			{
				result.LFLevel = 1;
			}
			else if (result.LF < LFStd_L)
			{
				result.LFLevel = -1;
			}
			else
			{
				result.LFLevel = 0;
			}

			result.HF
				= calc_power(HF_START, HF_END, EQUIDIST_MS, &speclist, n_spec);
			result.HF = get2double(result.HF);
			if (result.HF > HFStd_H)
			{
				result.HFLevel = 1;
			}
			else if (result.HF < HFStd_L)
			{
				result.HFLevel = -1;
			}
			else
			{
				result.HFLevel = 0;
			}

			result.VLF = calc_power(VLF_START, VLF_END, EQUIDIST_MS, &speclist,
				n_spec);
			result.VLF = get2double(result.VLF);
			if (result.VLF > VLFStd_H)
			{
				result.VLFLevel = 1;
			}
			else if (result.VLF < VLFStd_L)
			{
				result.VLFLevel = -1;
			}
			else
			{
				result.VLFLevel = 0;
			}

			result.LF_HF_Ratio = result.LF / result.HF;
			result.LF_HF_Ratio = get2double(result.LF_HF_Ratio);
			if (result.LF_HF_Ratio > LF_HF_RatioStd_H)
			{
				result.LHRLevel = 1;
			}
			else if (result.LF_HF_Ratio < LF_HF_RatioStd_L)
			{
				result.LHRLevel = -1;
			}
			else
			{
				result.LHRLevel = 0;
			}

		}

//(ANDROID_LOG_INFO, "TAGNNNN","%s"," hello   6   XXXXXXXXXXXXXXXXXXXXXXXXXxxx");

		result.RRfile = filePath + "RR.txt";
		result.PSDfile = filePath + "PSD.txt";
		////////////output to file
		/*
		ofs.open("E:\\ECGRR.txt", ostream::app);
		for (ll = 0; ll < Rlist.count; ll++)
		{
		ofs <<Rlist.arr[ll];
		ofs << "\n";
		ofs <<Rlist.arr[ll];
		ofs << "\n";
		ofs <<Rlist.arr[ll];
		ofs <<Rlist.arr[ll];
		ofs <<Rlist.arr[ll];
		ofs << "\n";
		}
		ofs.close();


		int ll=0;
		ofs.open("RLIST2", ostream::app);  

		for (ll = 0; ll < Rlist.count; ll++)
		{
		ofs << Rlist.arr[ll];
		ofs << "\n";
		}
		ofs.close();

		ofs.open("PSDLIST2", ostream::app);
		for (ll = 0; ll < PSD_RRlist.count; ll++)
		{
		ofs << PSD_RRlist.arr[ll];
		ofs << "\n";
		}
		ofs.close();

		/*		for (ll = 0; ll < RRlistImg.count; ll++)
		{
		ofs << RRlistImg.arr[ll];
		ofs << "\n";
		}
		ofs.close();   

		ofs.open(result.PSDfile.c_str(), ostream::app);

		for (ll = 0; ll < storelengthpsd; ll++)
		{//SGSG
		ofs << axislist.arr[ll];
		ofs << "\n";
		}
		for (ll = 0; ll < storelengthpsd; ll++)
		{
		ofs << speclist.arr[ll];
		ofs << "\n";
		}
		ofs.close();

		ofs.clear();

		std::cout << "RR :" << "\n\n";
		for (int i = 0; i < new_RRlist.count; i++)
		{
		//std::cout << ((QRS_endlist.arr[i]-QRS_startlist.arr[i])/400.0) << "\t";
		std::cout << (long) ((new_RRlist.arr[i])) << "\t";
		}
		*/

		//(ANDROID_LOG_INFO, "TAGNNNN","%s"," hello   6  1 XXXXXXXXXXXXXXXXXXXXXXXXXxxx");
		ECG_Diagnose_resultTotal.Arrest_Num=result.Arrest_Num;
		ECG_Diagnose_resultTotal.Arrest_posL=result.Arrest_posL;
		ECG_Diagnose_resultTotal.Missed_Num=result.Missed_Num;
		ECG_Diagnose_resultTotal.Missed_posL=result.Missed_posL;
		ECG_Diagnose_resultTotal.PAB_Num=result.PAB;
		ECG_Diagnose_resultTotal.PABposL=result.PABposL;
		ECG_Diagnose_resultTotal.PVB_Num=result.PVB;
		ECG_Diagnose_resultTotal.PVBposL=result.PVBposL;
		ECG_Diagnose_resultTotal.Bigeminy_Num=result.Bigeminy_Num;
		ECG_Diagnose_resultTotal.Bigeminy_posL=result.Bigeminy_posL;
		ECG_Diagnose_resultTotal.Trigeminy_Num=result.Trigeminy_Num;
		ECG_Diagnose_resultTotal.Trigeminy_posL=result.Trigeminy_posL;
		ECG_Diagnose_resultTotal.Insert_PVB_Num=result.Insert_PVBnum;
		ECG_Diagnose_resultTotal.Insert_PVBposL=result.Insert_PVBposL;
		ECG_Diagnose_resultTotal.VT_Num=result.VT;
		ECG_Diagnose_resultTotal.VT_posL=result.VT_posL;
		ECG_Diagnose_resultTotal.Noiselist=buf.noiselist_A;
		ECG_Diagnose_resultTotal.Rlist=Rlist;
		ECG_Diagnose_resultTotal.RRlist=RRlist;//2013  PSD_RRlist
		//(ANDROID_LOG_INFO, "TAGNNNN","%s"," hello   6  2 XXXXXXXXXXXXXXXXXXXXXXXXXxxx");
		//(ANDROID_LOG_INFO, "TAGNNNN","%s"," hello   6  2 XXXXXXXXXXXXXXXXXXXXXXXXXxxx");
		getposL_perHour(  ecgnum, (int) ci.samplerate_orig,  ECG_Diagnose_resultTotal  );  

		//(ANDROID_LOG_INFO, "TAGNNNN","%s"," hello   6  2  1 XXXXXXXXXXXXXXXXXXXXXXXXXxxx");

		result.Rlist= Rlist;
		result.RRlist=RRlist;  
		result.RRlistImg=RRlistImg;   //added by dai, for better display HRV in TV
		//(ANDROID_LOG_INFO, "TAGNNNN","%s"," hello   6  2  2 XXXXXXXXXXXXXXXXXXXXXXXXXxxx");
		result.Rannolist=Rannolist;
		//result.Qlist=QRS_startlist;
		//result.Slist=QRS_endlist;
		result.QRSlist=QRSlist;
		//result.noiselist=buf.noiselist;
		result.noiselist_A=buf.noiselist_A;
		//(ANDROID_LOG_INFO, "TAGNNNN","%s"," hello   6  2  2 XXXXXXXXXXXXXXXXXXXXXXXXXxxx");
		result.d2list=buf.d2list;
		result.axislist=axislist;
		result.speclist=speclist;
		//(ANDROID_LOG_INFO, "TAGNNNN","%s"," hello   6  3 XXXXXXXXXXXXXXXXXXXXXXXXXxxx");

		free(QRS_startlist.arr);
		QRS_startlist.arr=NULL;
		free(QRS_endlist.arr);
		QRS_endlist.arr=NULL;
		free(PSD_RRlist.arr);
		//(ANDROID_LOG_INFO, "TAGNNNN","%s"," hello   6  4 XXXXXXXXXXXXXXXXXXXXXXXXXxxx");
		PSD_RRlist.arr=NULL;
		free(PSD_Rlist.arr);
		PSD_Rlist.arr=NULL;
		free(PSD_RRlist_psd.arr);
		PSD_RRlist_psd.arr=NULL;
		free(buf.noiselist.arr);
		buf.noiselist.arr=NULL;
		//(ANDROID_LOG_INFO, "TAGNNNN","%s"," hello   6  5 XXXXXXXXXXXXXXXXXXXXXXXXXxxx");
		/*
		if(PSD_RRlist_psd.count>200)
		{
		free(speclist.arr);
		speclist.arr=NULL;
		free(axislist.arr);
		axislist.arr=NULL;
		}
		*/
		///////////////////////////////////////////////////////////////////
//(ANDROID_LOG_INFO, "TAGNNNN","%s"," hello   7   XXXXXXXXXXXXXXXXXXXXXXXXXxxx");
		
		gettimeofday(&abnormal_end, NULL);
		abnormal_time = (abnormal_end.tv_sec - abnormal_start.tv_sec) + (abnormal_end.tv_usec - abnormal_start.tv_usec)/1000000.0;
		cout <<"????????" << abnormal_time << "??" << endl;
		
		///////////////////////////////////////////
	}
	
	//(ANDROID_LOG_INFO, "TAGNNNN","%s"," hello   8   XXXXXXXXXXXXXXXXXXXXXXXXXxxx");

//	result->Arrest_Num = arrest;

	//(ANDROID_LOG_INFO, "TAGNNNN","%s"," hello   8   XXXXXXXXXXXXXXXXXXXXXXXXXxxx");

	//(ANDROID_LOG_INFO, "result->Arrest_Num", "%d", result.Arrest_Num);

	return result;
}


//-----------    心率计算    ---------------------------------
static double fly0;
double flx0[23];

double a[] = { 0.0008, 0.0025, 0.0057, 0.0109, 0.0183, 0.0280,
			0.0393, 0.0513, 0.0629, 0.0724, 0.0788, 0.0810, 0.0788, 0.0724,
			0.0629, 0.0513, 0.0393, 0.0280, 0.0183, 0.0109, 0.0057, 0.0025,
			0.0008 };
int fir(int d) {
		int i;

			for (i = 0; i < 22; i++)
				flx0[22 - i] = flx0[21 - i];
			flx0[0] = d;
			fly0 = 0;
			for (i = 0; i < 23; i++)
				fly0 += a[i] * flx0[i];

		return (int) fly0;
	}

int* zrGetRRList(vector<int> *R){
        int n = R->size();
        if(n <= 1)
        	return NULL;
        int *RRlist = new int[n - 1];
        for(int i = 0; i < n - 1; i++)
            RRlist[i] = (*R)[i + 1] - (*R)[i];
        return RRlist;
    }

int findCenter(int* data, int len){
		int* sumDistance = new int[len];
		for(int i = 0; i < len; i++){
			int temp = 0;
			for(int j = 0; j < len; j++){
				temp += abs(data[i] - data[j]);
			}
			sumDistance[i] = temp;
		}

		int centerPos = 0;
		int centerVal = sumDistance[0];
		for(int i = 1; i < len; i++){
			if(sumDistance[i] < centerVal){
				centerVal = sumDistance[i];
				centerPos = i;
			}
		}
		delete[] sumDistance;
		return data[centerPos];
	}

int preCenterRR = 0;
int countEcgRate(int ecg[], int len, int s_rate) {
    int result;
    int datasum = 0;
//    try {
        for (int i = 0; i < len; i++) {
          //  ecg[i] = fir(ecg[i]);
          //  datasum += abs(ecg[i] - 1810);
//            printf("%d\n",ecg[i]);
        }
      /* datasum /= len; //Ω‚æˆ ◊ﬂª˘œﬂ ±œ‘ æ–ƒ¬ ÷µ Œ Ã‚   »°∆Ωæ˘
        if (datasum < 10)
        {
            result = 0;
            return result;
        }*/

        vector<int> R;

        int * soc = new int[len];
        int * diff = new int[len];

        for(int j = 0; j < len; j++);
 //           cout << "ecg[" << j << "] = " << ecg[j] << endl;

        diff[0] = 0;
        diff[1] = 0;
//        printf("diffecg\n");
        for (int j = 2; j < len - 2; j++) {
            diff[j] = (ecg[j - 2] - 2 * ecg[j] + ecg[j + 2]);
            
 //           printf("%d\n",diff[j]);
        }
        diff[len - 1] = 0;
        diff[len - 2] = 0;

        for(int j = 0; j < len; j++);
 //           cout << "diff[" << j << "] = " << diff[j] << endl;

        int num = len / (int)(s_rate*1.0f);//yly 20161013‘≠1s
        int * min = new int[num];
        
        for (int i = 0; i < num; i++) {
            min[i] = diff[s_rate * i];
            for (int j = 0; j < (int)(s_rate*1.0f); j++) {
                if (min[i] > diff[s_rate * i + j])
                    min[i] = diff[s_rate * i + j];
            }
        }
        
        float * threshold = new float[num];
        for (int j = 0; j < num; j++)
        {
            threshold[j] = (float)((min[j]) * 0.35);
 //           printf("thd%f\n",threshold[j]);
        }
        
        int n = 0;
        for (int i = 0; i < num; i++) {
            for (int j = 0; j < s_rate && (s_rate * i + j) < len - 3; j++) {
                if (diff[s_rate * i + j] > threshold[i] && diff[s_rate * i + j + 1] > threshold[i] && diff[s_rate * i + j + 2] <= threshold[i]
                    && diff[s_rate * i + j + 3] <= threshold[i])
                    soc[n++] = s_rate * i + j;
            }
        }
        for (int i = 0; i < n; i++) {
            int p = soc[i];
            int res = diff[p];
            int beg = p - 5;
            if(beg < 0)
                beg = 0;
            int end = p + 5;
            if(end >= len)
                end = len - 1;
            for(int j = beg; j < end; j++){
                if(diff[j] < res){
                    p = j;
                    res = diff[j];
                }
            }
            R.push_back(p);
        }

        //2017年9月仲任更新1
        cout << "before delete" << endl;

		for(int j = 0; j < n; j++){
            cout << "Rpos" << j << " = " << R[j] << " diff = " << diff[R[j]];
            if(j < n - 1)
                cout << " RR = " <<  R[j + 1] - R[j] << endl;
            else
                cout << endl;
		}

        cout << "first delete" << endl;
		for(int j = 0; j < n - 1; j++){
		//	if((*R)[j + 1] - (*R)[j] < 100){
            if(R[j + 1] - R[j] < 5){
				if(abs(diff[R[j]]) > abs(diff[R[j + 1]])){
					R.erase(R.begin() + j + 1);
					n--;
					j--;
				}else{
					R.erase(R.begin() + j);
					n--;
					j--;
				}
			}
		}

		for(int j = 0; j < n; j++){
            cout << "Rpos" << j << " = " << R[j] << " diff = " << diff[R[j]];
            if(j < n - 1)
                cout << " RR = " <<  R[j + 1] - R[j] << endl;
            else
                cout << endl;
		}

		if(n < 2){
			if(NULL != soc)
			{
				delete[] soc;
			    soc =NULL;
			}
			if(NULL != diff)
			{
			    delete[] diff;
			    diff =NULL;
			}
			if(NULL != min)
			{
			    delete[] min;
			    min =NULL;
			}
			if (NULL != threshold) {
			       delete [] threshold;
			       threshold = NULL;
			}
			return 0;
		}

        cout << "second delete" << endl;
        for(int i = 0; i < n - 1; i++){
            if(R[i + 1] - R[i] < (60 * s_rate / 300)){
                float transA = abs(diff[R[i]]);
                float transB = abs(diff[R[i + 1]]);
                float ratio = transA / transB;
                if(ratio >= 0.9f && ratio < 1.1f ){
                    if(i == 0){
                        R.erase(R.begin() + i + 1);
                        n--;
                        i--;
                    }else{
                        int RRmean = (R[i] - R[0]) / i;
                        if( (R[i] - R[i - 1]) < (int)(0.75 * RRmean)){
                            R.erase(R.begin() + i);
                            n--;
                            i--;
                        }else{
                            R.erase(R.begin() + i + 1);
                            n--;
                            i--;
                        }

                    }


                }else{
                    if(transA < transB){
                        R.erase(R.begin() + i);
                        n--;
                        i--;
                    }else{
                        R.erase(R.begin() + i + 1);
                        n--;
                        i--;
                    }
                }
            }
        }
        for(int j = 0; j < n; j++){
            cout << "Rpos" << j << " = " << R[j] << " diff = " << diff[R[j]];
            if(j < n - 1)
                cout << " RR = " <<  R[j + 1] - R[j] << endl;
            else
                cout << endl;
		}

        if (n<2){
                    if(NULL != soc)
                    {
                        delete[] soc;
                        soc =NULL;
                    }
                    if(NULL != diff)
                    {
                        delete[] diff;
                        diff =NULL;
                    }
                    if(NULL != min)
                    {
                        delete[] min;
                        min =NULL;
                    }
                    if (NULL != threshold) {
                        delete [] threshold;
                        threshold = NULL;
                    }
        			return 0;
        }
        int* tempRRList = zrGetRRList(&R);
        if(tempRRList == NULL){
        	if(NULL != soc)
        	                    {
        	                        delete[] soc;
        	                        soc =NULL;
        	                    }
        	                    if(NULL != diff)
        	                    {
        	                        delete[] diff;
        	                        diff =NULL;
        	                    }
        	                    if(NULL != min)
        	                    {
        	                        delete[] min;
        	                        min =NULL;
        	                    }
        	                    if (NULL != threshold) {
        	                        delete [] threshold;
        	                        threshold = NULL;
        	                    }
        	        			return 0;
        }
		int centerRR = findCenter(tempRRList, R.size() - 1);
        cout << "centerRR = " << centerRR << " preCenterRR = " << preCenterRR << endl;
		if(preCenterRR != 0)
            centerRR = (centerRR + preCenterRR) / 2;
        cout << "third delete" << endl;
        for(int j = 1; j < n - 1; j++){
            if(R[j + 1] - R[j - 1] < (int)(1.5f * centerRR)){
                int a = diff[R[j - 1]];
                int b = diff[R[j]];
                int c = diff[R[j + 1]];

                if(b < a && b < c){
                    R.erase(R.begin() + j);
                    n--;
                    j--;
                }

                /*
                if(a < b){
                    if(a < c){
                        R->erase(R->begin() + j - 1);
                        n--;
                        j--;
                    }else{
                        R->erase(R->begin() + j + 1);
                        n--;
                        j--;
                    }
                }else{
                    if(b < c){
                        R->erase(R->begin() + j);
                        n--;
                        j--;
                    }else{
                        R->erase(R->begin() + j + 1);
                        n--;
                        j--;
                    }
                }
                */
            }
        }

        for(int j = 0; j < n; j++){
            cout << "Rpos" << j << " = " << R[j] << " diff = " << diff[R[j]];
            if(j < n - 1)
                cout << " RR = " <<  R[j + 1] - R[j] << endl;
            else
                cout << endl;
		}

        int thresh = (int)(1.8 * centerRR) - 2;

        cout << "centerRR = " << centerRR << " thresh = " << thresh << endl;

        for(int j = 0; j < n - 1; j++){
            int temp = R[j + 1] - R[j];
            if(temp > thresh){
                float ratio = (float)temp / centerRR;
                int beg = R[j] + temp / ratio - (int)(0.2 * centerRR);
                int end = R[j] + temp / ratio + (int)(0.2 * centerRR);
                if(beg < 0)
                    beg = 0;
                if(end > len)
                    end = len;

                int min_diff = diff[beg];
                int min_pos = beg;
                for(int k = beg + 1; k < end; k++){
                    if(diff[k] < min_diff){
                        min_pos = k;
                        min_diff = diff[k];
                    }
                }

                if( min_pos > R[j] && min_pos < R[j + 1]){
                    if((min_pos - R[j]) < (s_rate / 5) || (R[j + 1] - min_pos ) < (s_rate / 5))
                        continue;
                    R.insert(R.begin() + j + 1, min_pos);
                    j--;
                    n++;
                }
            }
        }
        delete[] tempRRList;
        tempRRList = zrGetRRList(&R);
		preCenterRR = findCenter(tempRRList, R.size() - 1);
		delete[] tempRRList;

        for(int i = 0; i < n; i++){
            soc[i] = R[i];
        }
        R.clear();
		for (int i = 0; i < n; i++) {
            int p = soc[i];
            int res = ecg[p];
            R.push_back(p);
            for (int j = p - 5; j < p + 5 && p > 5 && j < len; j++) {
                if (res < ecg[j]) {
                    res = ecg[j];
                    R[R.size() - 1] = j;

                }
            }
        }


        //2017年8月仲任更新
        /*
        logOut += "Start erase Rnum = " + toStr(n) + "\n";
        for(int j = 0; j < n - 1; j++){
            if((R[j + 1] - R[j]) < (60 * s_rate / 300)){
                if(ecg[R[j + 1]] > ecg[R[j]]){
                    R.erase(R.begin() + j);
                    n--;
                    j--;
                }else{
                    R.erase(R.begin() + j + 1);
                    n--;
                    j--;
                }
            }
        }
        logOut += "End erase Rnum = " + toStr(n) + "\n";
        logOut += "Start add Rnum = " + toStr(n) + "\n";
        int *tempRRList = getRRlist(&R);
        if(tempRRList == NULL)
            return 0;

        int centerRR = findCenter(tempRRList, R.size() - 1);
        //int thresh = 2 * centerRR - 36;
        int thresh = (int)(1.8 * centerRR) - 2;
        cout << "centerRR = " << centerRR << " thresh = " << thresh << endl;

        for(int j = 0; j < n - 1; j++){
            int temp = R[j + 1] - R[j];
            if(temp > thresh){
                float ratio = (float)temp / centerRR;
                int beg = R[j] + temp / ratio - (int)(0.2 * centerRR);
                int end = R[j] + temp / ratio + (int)(0.2 * centerRR);
                if(beg < 0)
                    beg = 0;
                if(end > len)
                    end = len;

                int min_diff = diff[beg];
                int min_pos = beg;
                for(int k = beg + 1; k < end; k++){
                    if(diff[k] < min_diff){
                        min_pos = k;
                        min_diff = diff[k];
                    }
                }
                beg = min_pos - (int)(0.03125 * centerRR);
                end = min_pos + (int)(0.03125 * centerRR);
                if(beg < 0)
                    beg = 0;
                if(end > len)
                    end = len;
                int max_ecg = ecg[beg];
                int max_pos = beg;
                for(int k = beg + 1; k < end; k++){
                    if(ecg[k] > max_ecg){
                        max_pos = k;
                        max_ecg = ecg[k];
                    }
                }

                if( max_pos > R[j] && max_pos < R[j + 1]){
                    if((max_pos - R[j]) < (s_rate / 5) || (R[j + 1] - max_pos ) < (s_rate / 5))
                        continue;
                    R.insert(R.begin() + j + 1, max_pos);
                    j--;
                    n++;
                }
            }
        }
        logOut += "End add Rnum = " + toStr(n) + "\n";
        delete[] tempRRList;
        */

        //2017年8月仲任更新前旧版
        /*
        for (int j = 0; j < n - 1; j++) {
            if ((R[j + 1] - R[j]) < (s_rate / 5)) {
                if (ecg[R[j + 1]] > ecg[R[j]]) {
                    R.erase(R.begin() + j);
                    n--;
                    j--;
                }
                else {
                    R.erase(R.begin() + j + 1);
                    n--;
                }
            }
            else if ((R[j + 1] - R[j]) > (s_rate * 2)) {
                int res = diff[R[j] + 100];
                int pos = R[j] + 100;
                for (int t = R[j] + 100; t < (R[j + 1] - 100); t++) {
                    if (res < diff[t]) {
                        res = diff[t];
                        pos = t;
                    }
                }
                res = ecg[pos];
                int p_pos = pos;
                for (int t = pos - 5; t < pos + 5; t++) {
                    if (res < ecg[t]) {
                        res = ecg[t];
                        p_pos = t;
                    }
                }
                if(ecg[p_pos]>0.5*ecg[R[j]] || ecg[p_pos]>0.5*ecg[R[j+1]])
                 {  //防止导联脱落时强行插入心博
                 	R.insert(R.begin() + j+1, p_pos);
                //R.add(j + 1, p_pos);
                  n++;
                  j++;
                 }
            }
        }
        */
        int minRR=2000;
        int maxRR = 0;
        int minpos = 0;
        int maxpos = 0;


        if (n<2){
            
            if(NULL != soc)
            {
                delete[] soc;
                soc =NULL;
            }
            if(NULL != diff)
            {
                delete[] diff;
                diff =NULL;
            }
            if(NULL != min)
            {
                delete[] min;
                min =NULL;
            }
            if (NULL != threshold) {
                delete [] threshold;
                threshold = NULL;
            }
			return 0;
        }
        
        int *RR = new int[n - 1];
        for (int j = 0; j < n - 1; j++) {
            RR[j] = R[j + 1] - R[j];
            if(RR[j] > maxRR)
            {
                maxRR = RR[j];
                maxpos = j;
            }
            if(RR[j] < minRR)
            {
                minRR = RR[j];
                minpos = j;
            }
 //           printf("rr:%d",RR[j]);
        }

        int size = n - 1;
        int sum = R[n - 1] - R[0];
        if(size > 2){
            sum -= maxRR;
            sum -= minRR;
            size -= 2;
        }
        int avel = sum / size;

        /*
        for (int j = 0; j < size; j++) {
            if(j != maxpos && j!= minpos && size > 2)
            {
            sum = sum + RR[j];
            }
            else if(size <=2)
                sum += RR[j];
        }

        int avel = sum/size;
        if(size > 2)
            avel = sum / (size-2);
        */
        int rate = 60 * s_rate / avel;
        result = rate;
        if (rate > 40 && rate < 300) {
            // ‘≠ º…Ë÷√Œ™£®40£¨150£© ∏ƒŒ™ £®40£¨240£© –ﬁ∏ƒ 2016.10.11
            result = rate;
        }
        else {
            result = 0;
        }
        
        if(NULL != soc)
        {
            delete[] soc;
            soc =NULL;
        }
        if(NULL != diff)
        {
            delete[] diff;
            diff =NULL;
        }
        if(NULL != min)
        {
            delete[] min;
            min =NULL;
        }
        if(NULL != RR)
        {
            delete[] RR;
            RR =NULL;
        }
        if (NULL != threshold) {
            delete [] threshold;
            threshold = NULL;
        }
        
        
//    }
//    catch (...) {
 //       result = 0;
//    }
    
 
 
    
    return result;
}


//struct rslt
//{	int state,stepcount;};


//-----------    计步算法    ---------------------------------
#define MAX 60000 //最大数据长度
#define G 4096 //量化重力加速度
#define PI 3.1415926
#define FFT_N 512
#define Rev_N  1800
#define S_R  Rev_N/6
#define fs 26     //采样频率
#define AmpDif  650 //

int lines=0;   //lines加速度数据长度 index代表重力轴 A为滤波频率 m/n为计步时记录零点位置
struct rslt result;
struct peakdet {unsigned int *index; float *value; unsigned int peakcount;};
int sn;
float ff,wf,av1=0,av2=0,av3=0,data1[MAX],data2[MAX],data3[MAX],data[MAX];
//struct peakdet peak;
//struct peakdet valley;



/****************************************************************************************
//巴特沃斯低通滤波器
*  参数说明  fc 截止频率
*             fs1    采样率
*     N     (1=<N<=3)  阶数
*     *x    传入的待滤波数组
*双线性法基于巴特沃斯的数字滤波器
****************************************************************************************/

void biliner(int fc,int N,int fs1,float *x,int len, char dmod)
{
 //定义变量
 long i=0;
 float w,wc,t,y[MAX];//MAX是3000个点
 //转化为数字角频率
 w=2*PI*fc/fs1;
 //预畸变
 wc=2*fs1*tan(w/2);
 //去归一化影响
 t=2*fs1/wc;
 switch(N)
 {
  /*一阶情况*/
    case 1:
    //Hs=1/(p+1);
    y[0]=x[0]/(1+t);
    for(i=1;i<MAX;i++)
     y[i]=(x[i]+x[i-1]-(1-t)*y[i-1])/(1+t);
    break;
    /*二阶情况*/
   case 2:
    //Hs=1/(p*p+1.414*p+1);
    y[0]=x[0]/(t*t+1.414*t+1);
    y[1]=(x[1]+2*x[0]-(2-2*t*t)*y[0])/(t*t+1.414*t+1);
    for(i=2;i<MAX;i++)
     y[i]=(x[i]+2*x[i-1]+x[i-2]-(2-2*t*t)*y[i-1]-(1-1.414*t+t*t)*y[i-2])/(t*t+1.414*t+1);
    break;
    /*三阶*/
   case 3:
    y[0]=x[0]/(t*t*t+2*t*t+2*t+1);
    y[1]=(x[1]+3*x[0]-(3-3*t*t*t-2*t*t+2*t)*y[0])/(t*t*t+2*t*t+2*t+1);
    y[2]=(x[2]+3*x[1]+3*x[0]-(3-3*t*t*t-2*t*t+2*t)*y[1]-(3*t*t*t-2*t*t-2*t+3)*y[0])/(t*t*t+2*t*t+2*t+1);

	for(i=3;i<len;i++)
     y[i]=(x[i]+3*x[i-1]+3*x[i-2]+x[i-3]-(3-3*t*t*t-2*t*t+2*t)*y[i-1]-(3*t*t*t-2*t*t-2*t+3)*y[i-2]-(1-t*t*t+2*t*t-2*t)*y[i-3])/(t*t*t+2*t*t+2*t+1);


    break;
   default:return ;break;
    }
 for(i=0;i<len;i++)
  x[i]=y[i];
 return;
}
struct peakdet fpeak(float* vector,float delta,int len)
{
     struct peakdet peak;
	 struct peakdet valley;
	int flag;
	int minpos, maxpos;
	float data_max, data_min,thisdata;
	data_max=vector[0];
	data_min=vector[0];
	flag=1;
	peak.peakcount=0;
	peak.index=new unsigned int[MAX];
	peak.value=new float[MAX];
	valley.index=new unsigned int[MAX];
	valley.value=new float[MAX];
	int n=0;
	int m=0;
	for (int i=0;i<len;i++)
	{
		thisdata= vector[i];
		if (thisdata>data_max)
		{
			data_max = thisdata;
			maxpos=i;
		}
		if(thisdata<data_min)
		{
			data_min=thisdata;
			minpos=i;
		}

		if(flag==1)
		{
			if(thisdata<data_max-delta)
			{
				peak.value[n]=data_max;
				peak.index[n] =maxpos;
				n++;
				peak.peakcount++;
				data_min=thisdata;
				minpos=i;
			}
		   flag=0;
		}
		else
		{
			if(thisdata>data_min+delta)
			{
				valley.value[m]=data_min;
				valley.index[m]= minpos;
				m++;
				data_max=thisdata;
				maxpos=i;
				flag=1;
			}


		}

	}
	//delete [] peak.index;
	//delete [] peak.value;
	//delete [] valley.index;
	//delete [] valley.value;

	return peak;
}

struct rslt pedomain(unsigned char *dat,int len)
{   //***************************************************
  int i,i1,i2,i3, n=0;
  int peakNum;
  unsigned int dif;
  float diff;
  struct peakdet findpeak;
  float Ttime;
  float stepf;
//  findpeak.index=new unsigned int[MAX];
//  findpeak.value=new float[MAX];

	i1=0;i2=0;i3=0;

	sn=len;
	lines=sn/2/3;

	Ttime = lines/fs;
	for(i=0;i<sn;i=i+2)
	{
		if(((i+1)/2)%3==1)
		{
			if(dat[i]>127)
			{
			data1[i1]=float(dat[i]*256+dat[i+1]-65536);
			i1++;
			}
			else
			{
			data1[i1]=float(dat[i]*256+dat[i+1]);
			i1++;
			}
			//printf("i1=%d\n",i1);
		}
		else if(((i+1)/2)%3==2)
		{
			if(dat[i]>127)
			{
			data2[i2]=float(dat[i]*256+dat[i+1]-65536);
			i2++;
			}
			else
			{
			data2[i2]=float(dat[i]*256+dat[i+1]);
			i2++;
			}
		}
		else if(((i+1)/2)%3==0)
		{
			if(dat[i]>127)
			{
			data3[i3]=float(dat[i]*256+dat[i+1]-65536);
			i3++;
			}
			else
			{
			data3[i3]=float(dat[i]*256+dat[i+1]);
			i3++;
			}

		}
	}
	for(i=0;i<lines;i++)
	{
	data[i]=sqrt(data1[i]*data1[i]+data2[i]*data2[i]+data3[i]*data3[i]);
	}
	//biliner(5,3,26,data,lines,mode);
	findpeak = fpeak(data,AmpDif,lines);


 peakNum = findpeak.peakcount;
 for(int j=1;j<findpeak.peakcount;j++)
 {
	 dif=findpeak.index[j]-findpeak.index[j-1];
    if ((dif<5)||(dif>30) )
	  peakNum--;
 }
 result.stepcount = peakNum;
 stepf= peakNum/Ttime;
 if (stepf==0||peakNum<=3)
	 result.state=0;//Rest
 else if((peakNum>3) && (stepf>0) && (stepf<=2))
	 result.state=1;//walking
 else if(stepf>2)
	 result.state=2;//Running
 delete [] findpeak.index;
 delete [] findpeak.value;

   return result;
}




float kcal(int sex,int hr,int age,float weight,float time)
{
	float K;
	if(sex==1)
		K=(-55.0969+0.6309*hr+0.1988*weight+0.2017*age)/4.184*time;   //time µ¥Î» ·ÖÖÓ
	else
		K=(-20.4022+0.4472*hr-0.1263*weight+0.074*age)/4.184*time;
	return K;
}


void maindetect::releaseecgresult()
{
	//!
	if (result.AbECG != 0)
	{
		delete[] result.AbECG;
		result.AbECG = NULL;
	}
	if (result.Arrest_posL)
	{
		delete[] result.Arrest_posL;
		result.Arrest_posL = NULL;
	}
	if (result.Missed_posL)
	{
		delete[] result.Missed_posL;
		result.Missed_posL = NULL;
	}
	if (result.PVBposL)
	{
		delete[] result.PVBposL;
		result.PVBposL = NULL;
	}
	if (result.PABposL)
	{
		delete[] result.PABposL;
		result.PABposL = NULL;
	}
	if (result.Insert_PVBposL)
	{
		delete[] result.Insert_PVBposL;
		result.Insert_PVBposL = NULL;
	}
	if (result.VT_posL)
	{
		delete[] result.VT_posL;
		result.VT_posL = NULL;
	}
	if (result.Bigeminy_posL)
	{
		delete[] result.Bigeminy_posL;
		result.Bigeminy_posL = NULL;
	}
	if (result.Trigeminy_posL)
	{
		delete[] result.Trigeminy_posL;
		result.Trigeminy_posL = NULL;
	}
	if (result.Wide_posL)
	{
		delete[] result.Wide_posL;
		result.Wide_posL = NULL;
	}
	if (result.Diagnose_resultPerHourList.arr)
	{
		free( result.Diagnose_resultPerHourList.arr );
		result.Diagnose_resultPerHourList.arr = NULL;
	}

}
