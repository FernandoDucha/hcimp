/* 
 * File:   main.cpp
 * Author: fordem
 *
 * Created on July 5, 2013, 11:58 AM
 */

#include <cstdlib>
#include <vector>
#include <string>
#include <string.h>
#include <vector>
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <math.h>

using namespace std;

struct result {
    double result;
    double time;
    int nc;
    int np;
};

struct results {
    vector<result> resultSet;

    double getMaxResult() {
        return resultSet[0].result;
    }

    double getMinResult() {
        double temp = getMaxResult();
        for (int i = 1; i < resultSet.size(); i++) {
            if (resultSet[i].time < 3600) {
                temp = resultSet[i].result;
            } else if (resultSet[i].time == 3600) {
                if (temp < resultSet[i].result) {
                    return resultSet[i].time;
                }
            }
        }
        return temp;
    }

    double getMinResultTime() {
        double temp = getMaxResult();
        double resp;
        for (int i = 1; i < resultSet.size(); i++) {
            if (resultSet[i].time < 3600) {
                temp = resultSet[i].result;
                resp = resultSet[i].time;
            } else if (resultSet[i].time == 3600) {
                if (temp < resultSet[i].result) {
                    return resultSet[i].time;
                }
            }
        }
        return resp;
    }
};

struct AllInstances {
    vector<results> resultSet;
};

/*
 * 
 */
int tempIncrement(int temp, double time) {
    if (time <= 10) {
        switch (temp) {
            case 0:
                return temp + 1;
                break;
        }
    } else if (time <= 100) {
        switch (temp) {
            case 0:
            {
                return temp + 2;
                break;
            }
            case 1:
            {
                return temp + 1;
                break;
            }
        }
    } else if (time <= 1000) {
        switch (temp) {
            case 0:
            {
                return temp + 3;
                break;
            }
            case 1:
            {
                return temp + 2;
                break;
            }
            case 2:
            {
                return temp + 1;
                break;
            }
        }
    } else if (time <= 3600) {
        switch (temp) {
            case 0:
            {
                return temp + 4;
                break;
            }
            case 1:
            {
                return temp + 3;
                break;
            }
            case 2:
            {
                return temp + 2;
                break;
            }
            case 3:
            {
                return temp + 1;
                break;
            }
        }
    }
    return temp;
}

int accInit(double ** acc) {
    for (int i = 0; i < 100; i++) {
        for (int j = 0; j < 5; j++) {
            acc[i][j] = 0;
        }
    }
}

void accFillGaps(double ** vec) {
    for (int i = 0; i < 100; i++) {
        for (int j = 0; j < 5; j++) {
            if ((vec[i][j] <= 0.1)&&(j == 0)) {
                vec[i][j] = vec[i][j + 1];
            } else if (vec[i][j] <= 0.1) {
                vec[i][j] = vec[i][j - 1];
            }
        }
    }
}

void accSum(double * lhs, double ** rhs) {
    for (int i = 0; i < 100; i++) {
        for (int j = 0; j < 5; j++) {
            lhs[j] += rhs[i][j];
        }
    }
}

int main(int argc, char** argv) {
    string path = "../results/";
    string type[3] = {".lds", ".bfs", ".dfs"};
    string typeform[3] = {"\\textit{ILDS}", "\\textit{BFS}", "\\textit{DFS}"};

    vector<double> etav, tauv;

    //    double * acumulado = new double[5];
    //    for (int i = 0; i < 5; i++) {
    //        acumulado[i] = 0;
    //    }
    //    double ** resinter = new double*[100];
    //    for (int i = 0; i < 100; i++) {
    //        resinter[i] = new double[5];
    //    }
    //   
    for (int i = 100; i <= 1000; i += 100) {
        //        cout << type[k] << endl;
        cout << i;
        for (int k = 0; k < 3; k++) {
            //            AllInstances insts;
            double eta = 0;
            double etal = 0;
            double tau = 0;
            double delta = 0;
            //            accInit(resinter);
            //            for (int i = 0; i < 5; i++) {
            //                acumulado[i] = 0;
            //            }
            //            for (int j = 1; j <= 100; j++) {
            char buf[100];
            sprintf(buf, "hard%04d.dat", i);
            string middle = buf;
            string fullname = path + middle;
            fullname += type[k].c_str();
            ifstream file(fullname.c_str());
            results All;
            int tmp = 0;
            if (file.is_open()) {
                while (true) {
                    result t;
                    char pontvirgula;
                    file.getline(buf, 300);
                    string buf1 = buf;
                    if (buf1.find_first_of(";") == buf1.npos)break;
                    if (buf1[buf1.length() - 1] != '#' && buf1[buf1.length() - 1] != '$') {
                        sscanf(buf1.c_str(), "%lg;%lg;%d;%d", &t.result, &t.time, &t.nc, &t.np);
                    } else if (buf1[buf1.length() - 1] == '#') {
                        sscanf(buf1.c_str(), "%lg;%lg;%d;%d#", &t.result, &t.time, &t.nc, &t.np);
                    } else if (buf1[buf1.length() - 1] == '$') {
                        sscanf(buf1.c_str(), "%lg;%lg;%d;%d$", &t.result, &t.time, &t.nc, &t.np);
                    }

                    //                        if (t.time <= 1) {
                    //                            //                            tmp=(t.time<=1)?tmp:tmp++;
                    //                            resinter[j - 1][tmp] = t.result;
                    //                        } else if (t.time <= 10) {
                    //                            tmp = tempIncrement(tmp, t.time);
                    //                            resinter[j - 1][tmp] = t.result;
                    //                        } else if (t.time <= 100) {
                    //                            tmp = tempIncrement(tmp, t.time);
                    //                            resinter[j - 1][tmp] = t.result;
                    //                        } else if (t.time <= 1000) {
                    //                            tmp = tempIncrement(tmp, t.time);
                    //                            resinter[j - 1][tmp] = t.result;
                    //                        } else if (t.time <= 3600) {
                    //                            tmp = tempIncrement(tmp, t.time);
                    //                            resinter[j - 1][tmp] = t.result;
                    //                        }
                    //file>>t.result>>pontvirgula>>t.time>>pontvirgula>>t.nc>>pontvirgula>>t.np;
                    if (t.time <= 3600) {
                        All.resultSet.push_back(t);
                    } else {
                        break;
                    }
                }
            }
            //                accFillGaps(resinter);
            //                if (i == 800 && k == 1) {
            //                    for (int p = 0; p<4;p++){
            //                        if(resinter[j-1][p]<resinter[j-1][p+1]){
            //                            cout<<endl;
            //                        }
            //                    }
            //                }
            eta = All.getMinResult();
            etav.push_back(All.getMinResult());
            tau = All.getMinResultTime();
            cout << "&" << eta<<"&"<<3600;

            tauv.push_back(All.getMinResultTime());
            etal = All.getMaxResult();
            //                eta += All.getMinResult();
            //                etav.push_back(All.getMinResult());
            //                tau += All.getMinResultTime();
            //                tauv.push_back(All.getMinResultTime());
            //                etal += All.getMaxResult();
            //            insts.resultSet.push_back(All);
            //            }
            //            accSum(acumulado, resinter);
            double etam = eta / 100;
            double taum = tau / 100;
            delta = (etal / 100 - etam) / (tau / 100);

            eta = 0;
            tau = 0;
            for (int l = 0; l < 1; l++) {
                double tempeta = etav.at(l);
                double temptau = tauv.at(l);
                eta += pow(tempeta - etam, 2);
                tau += pow(temptau - taum, 2);
            }
            eta = sqrt(eta / 99);
            tau = sqrt(tau / 99);
            //            cout << i << "&" << etam << "&" << eta << "&" << taum << "&" << tau << "&" << delta << "\\\\\\hline" << endl;
            //            cout << "&" << typeform[k] << "&" << etal / 100 << "&" << acumulado[0] / 100 << "&" << acumulado[1] / 100 << "&" << acumulado[2] / 100 << "&" << acumulado[3] / 100 << "&" << acumulado[4] / 100 << "\\\\\\hline" << endl;
            etav.clear();
            tauv.clear();
            //        }

            //        cout << endl;
        }
        cout << "\\\\\\hline" << endl;
    }
    return 0;

}
