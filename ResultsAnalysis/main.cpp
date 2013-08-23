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
#include <gmpxx.h>
using namespace std;

double log2(mpz_class l) {
    mpf_class r = l;
    mpf_class t, t1 = l;
    int y = 1;
    mpf_class resp;
    do {
        mpf_sqrt(t.get_mpf_t(), t1.get_mpf_t());
        y *= 2;
        t1 = t;
    } while (t > 2);
    resp = y * log2(t.get_d());
    return resp.get_d();
}
//struct result {
//    double result;
//    double time;
//    int nc;
//    int np;
//};

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

    double getRunningTime() {
        double temp = getMaxResult();
        double resp;
        for (int i = 1; i < resultSet.size(); i++) {
            if (resultSet[i].time <= 3600) {
                temp = resultSet[i].result;
                resp = resultSet[i].time;
            } else {
                return 3600;
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

void AnaliseCplex() {
    string path = "../../HCImpCplex/results/";
    string type[3] = {".lds", ".bfs", ".dfs"};
    string typeform[3] = {"\\textit{ILDS}", "\\textit{BFS}", "\\textit{DFS}"};

    vector<double> etav, tauv;
    for (int i = 10; i < 100; i += 10) {
        //        cout << type[k] << endl;
        double etam = 0;
        double taum = 0;
        for (int k = 1; k <= 100; k++) {
            char buf[1000];
            sprintf(buf, "inst-%05d-%03d", i, k);
            string middle = buf;
            string fullname = path + middle;
            fullname += ".cplex";
            ifstream file(fullname.c_str());
            int tmp = 0;
            if (file.is_open()) {
                string buf1;
                result t;
                do {
                    file.getline(buf, 1000);
                    buf1 = buf;
                } while ((tmp = buf1.find_first_of("@#$%")) == buf1.npos);

                buf1 = buf1.substr(5, buf1.size() - 5);
                sscanf(buf1.c_str(), "%le;%lg", &t.result, &t.time);
                file.close();
                if (t.result < 0) {
                    t.result = -t.result;
                }
                etam += log2(t.result + 1);
                taum += t.time;
            }
        }
        cout << i << "&" << etam / 100 << "&" << taum / 100 << "\\\\\\hline" << endl;
    }
}

void AnaliseALgorithms() {
    string path = "../results/";
    string type[3] = {".lds", ".bfs", ".dfs"};
    string typeform[3] = {"\\textit{ILDS}", "\\textit{BFS}", "\\textit{DFS}"};

    vector<double> etav, tauv;
    for (int i = 10; i < 100; i += 10) {
        double etam = 0;
        double taum = 0;
        for (int j = 0; j < 3; j++) {
            etam = 0;
            taum = 0;
            for (int k = 1; k <= 100; k++) {
                results All;
                char buf[1000];
                sprintf(buf, "inst-%05d-%03d", i, k);
                string middle = buf;
                string fullname = path + middle;
                fullname += type[j];
                ifstream file(fullname.c_str());
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
                        All.resultSet.push_back(t);
                    }
                }

                etam += All.getMinResult();
                taum += All.getRunningTime();
            }
            cout << "&"<< etam / 100 << "&" << taum / 100 ;
        }
        cout << endl;
    }
}

//int main(int argc, char** argv) {
//    AnaliseALgorithms();
//    return 0;
//}
int partition( int a[], int l, int r) {
   int pivot, i, j, t;
   pivot = a[l];
   i = l; j = r+1;
		
   while( 1)
   {
   	do ++i; while( a[i] <= pivot && i <= r );
   	do --j; while( a[j] > pivot );
   	if( i >= j ) break;
   	t = a[i]; a[i] = a[j]; a[j] = t;
   }
   t = a[l]; a[l] = a[j]; a[j] = t;
   return j;
}
void quickSort( int a[], int l, int r)
{
   int j;

   if( l < r ) 
   {
   	// divide and conquer
        j = partition( a, l, r);
       quickSort( a, l, j-1);
       quickSort( a, j+1, r);
   }
	
}
int main() 
{
	int a[] = { 7, 12, 1, -2, 0, 15, 4, 11, 9};

	int i;
	printf("\n\nUnsorted array is:  ");
	for(i = 0; i < 9; ++i)
		printf(" %d ", a[i]);

	quickSort( a, 0, 8);

	printf("\n\nSorted array is:  ");
	for(i = 0; i < 9; ++i)
		printf(" %d ", a[i]);
        return 0;

}







