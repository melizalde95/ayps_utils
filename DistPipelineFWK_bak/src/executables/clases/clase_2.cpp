//
// Created by morrigan on 2/7/18.
//

#include <iostream>
#include <vector>
#include "serial_port_src.hpp"

using namespace std;
std::vector<double> stat_time;

using tSource = SerialPortSRC;
using tDevice = BaseNode<SerialOutPkt>;

bool dev_proc(shared_ptr<SerialOutPkt>&& msg){
    cout << "rcv: " << msg->line << endl;
    //double secondValue=stod(msg->line.c_str());
    //cout<<secondValue<<endl;
    //stat_time.push_back(secondValue);
    cout<<stat_time.size()<<endl;
    return true;
}

int main(){

    auto src =    NodeFactory::create<tSource>("/dev/ttyACM0", 9600);
    auto dev =    NodeFactory::create<tDevice>(dev_proc, "ConsoleDevice");

    src->set_target(dev);

    std::this_thread::sleep_for(chrono::seconds(20));
    double sum=0;
    int N=0;
    for (int i=50;i<stat_time.size()-1;i++){
        sum+=stat_time[i]-stat_time[i-1];
        N++;
    }

    cout<<sum/N<<"us"<<endl;

    return 0;
}

