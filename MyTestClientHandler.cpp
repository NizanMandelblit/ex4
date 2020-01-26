//
// Created by nizan on 14/01/2020.
//

#include <unistd.h>
#include "MyTestClientHandler.h"
#include "Problem.h"
#include "CasheManager.h"
#include "Solver.h"
#include "OA.h"
#include <algorithm>
#include <sstream>
#include <thread>
#include <strings.h>

using namespace std;


void readFromClient(int socket) {


}


void MyTestClientHandler::handleClient(int socket) {
    //reading from client
    Problem *problem = new Problem();
    string solution;
    char buffer[100000] = {0};
    bzero(buffer, 100000);
    int numOfComma = 0;
    int firstTime = 1;
    string delimiter = "\n";
    string token;
    string s = "";

    // m2.lock();
    while (1) {
        bzero(buffer, 100000);
        read(socket, buffer, 100000);
        if ((buffer != NULL) && (buffer[0] == '\0')) {
            continue;
        }
        s += buffer;
        s.erase(std::remove(s.begin(), s.end(), '\r'), s.end());
        size_t pos = 0;
        while ((pos = s.find(delimiter)) != string::npos) {
            token = s.substr(0, pos);
            if (token == "end\r\n" || token == "end\n" || token == "end\r" || token == "end") {
                break;
            }
            token.erase(std::remove(token.begin(), token.end(), '\n'), token.end());
            numOfComma = std::count(token.begin(), token.end(), ',');
            if (numOfComma > 1) {
                problem->insertLine(token);
            } else if (numOfComma == 1) {
                if (firstTime) {
                    firstTime = 0;
                    problem->insertToState();
                    problem->insertStartPoint(token);
                } else {
                    problem->insertEndPoint(token);
                }
            }
            s.erase(0, pos + delimiter.length());
        }
        if (token == "end\r\n" || token == "end\n" || token == "end\r" || token == "end") {
            break;
        }
        // token = "";
    }

    //m2.unlock();
/*
CasheManager<Problem*,string>* cm;

   cm=new CasheManager<Problem*,string> ();

   if (cm->count(problem)){
       solution=cm->get(problem);
   }else{
       Solver<Problem*,string> *so;
       so=new OA<Problem*,string>();
       solution=so->solve(problem);
       cm->insert(problem,solution);
   }*/
    Solver<Problem, string> *so;
    so = new OA<Problem, string>();
    solution = so->solve(problem);
    send(socket, solution.c_str(), solution.size(), 0);
    cout << solution << endl;
    return;;
}


MyTestClientHandler::~MyTestClientHandler() {

}
