#pragma comment(lib,"Dll_feituoguan.lib")
//采用模板方式的dll，__declspec(dllimport) double MAX(double x, double y);和double MAX(double x, double y);是相同的。
__declspec(dllimport) double MAX(double x, double y);
__declspec(dllimport) double MIN(double x, double y);
__declspec(dllimport) double ND(double x);
__declspec(dllimport) double CND(double x);
__declspec(dllimport) int sgn(double x);
__declspec(dllimport) double CBND(double a, double b, double rho);
__declspec(dllimport) double BlackScholes(char CallPutFlag, double S, double X, double T, double r, double v);
__declspec(dllimport) double Merton73(char CallPutFlag, double S, double X, double T, double r, double q, double v);
__declspec(dllimport) double Black76(char CallPutFlag, double F, double X, double T, double r, double v);
__declspec(dllimport) double GarmanKolhagen(char CallPutFlag, double S, double X, double T, double r, double rf, double v);
__declspec(dllimport) double GBlackScholes(char CallPutFlag, double S, double X, double T, double r, double b, double v);
__declspec(dllimport) double GDelta(char CallPutFlag, double S, double X, double T, double r, double b, double v);
__declspec(dllimport) double GGamma(double S, double X, double T, double r, double b, double v);
__declspec(dllimport) double GTheta(char CallPutFlag, double S, double X, double T, double r, double b, double v);
__declspec(dllimport) double GVega(double S, double X, double T, double r, double b, double v);
__declspec(dllimport) double ImpVol(char CallOrPut, double S, double K, double T, double r, double q, double OptionValue);
