#include "road_network.h"

#include <iostream>
#include <cstring>

using namespace std;
using namespace road_network;

int main(int argc, char** argv)
{
    bool json = false;
    if (argc > 1)
    {
        if (strcmp(argv[1], "-json") == 0)
            json = true;
        else
        {
            cerr << "Syntax: " << argv[0] << " [-json]" << endl;
            exit(0);
        }
    }
    // read graph
    Graph g;
    read_graph(g, std::cin);
    vector<Edge> redundant_edges;
    g.get_redundant_edges(redundant_edges);
    for (Edge e : redundant_edges)
        g.remove_edge(e.a, e.b);
    vector<Neighbor> closest;
    g.contract(closest);
#ifdef NDEBUG
    srand(time(nullptr));
    g.randomize();
#endif
    // construct index
    vector<CutIndex> ci;
    g.create_cut_index(ci, 0.2);
    ContractionIndex con_index(ci, closest);
    // write index
    json ? con_index.write_json(std::cout) : con_index.write(std::cout);
    return 0;
}
