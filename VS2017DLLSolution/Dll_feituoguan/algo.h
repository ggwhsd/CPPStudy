#pragma once
//使用了模块定义文件创建dll
double MAX(double x, double y);
double MIN(double x, double y);
double ND(double x);
double CND(double x);
int sgn(double x);
double CBND(double a, double b, double rho);
double BlackScholes(char CallPutFlag, double S, double X, double T, double r, double v);
double Merton73(char CallPutFlag, double S, double X, double T, double r, double q, double v);
double Black76(char CallPutFlag, double F, double X, double T, double r, double v);
double GarmanKolhagen(char CallPutFlag, double S, double X, double T, double r, double rf, double v);
double GBlackScholes(char CallPutFlag, double S, double X, double T, double r, double b, double v);
double GDelta(char CallPutFlag, double S, double X, double T, double r, double b, double v);
double GGamma(double S, double X, double T, double r, double b, double v);
double GTheta(char CallPutFlag, double S, double X, double T, double r, double b, double v);
double GVega(double S, double X, double T, double r, double b, double v);
double ImpVol(char CallOrPut, double S, double K, double T, double r, double q, double OptionValue);
