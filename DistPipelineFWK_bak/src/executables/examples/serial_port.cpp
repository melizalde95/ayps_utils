//
// Created by morrigan on 2/7/18.
//

#include <iostream>
#include <vector>
#include <fstream>

#include "serial_port_src.hpp"

using namespace std;
std::vector<double> stat_time;

using tSource = SerialPortSRC;
using tDevice = BaseNode<SerialOutPkt>;

bool dev_proc(shared_ptr<SerialOutPkt>&& msg){

    ofstream raw_data;

    //if (raw_data.is_open()) {
        //raw_data << msg -> line << endl;
    //es open("ruta de guardado y archivo de guardado")
    raw_data.open("/home/cuau/Documentos/raw_data.txt",std::ios_base::app);
    raw_data << msg->line << endl;
        //out << "dentro de if";
        //raw_data.close();
    //} else {
    //    cout << "no se puede abrir archivo";
    //}
    //cout << "rcv: " << msg->line << endl;

    return true;
}

int main(){

    auto src =    NodeFactory::create<tSource>("/dev/ttyACM0", 9600);
    auto dev =    NodeFactory::create<tDevice>(dev_proc, "ConsoleDevice");

    src->set_target(dev);

    std::this_thread::sleep_for(chrono::seconds(5));

    return 0;
}

