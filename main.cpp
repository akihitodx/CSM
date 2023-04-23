#include <iostream>
#include "tools.h"
#include "alg.h"
#include <fstream>
#include <assert.h>
int main() {
    string path = "../querySet";
    Graph *p = new Graph();
    p->readGraph(path);
    p->printGraph();




}
