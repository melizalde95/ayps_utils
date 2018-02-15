//
// Created by Dr. Yevgeniy Kolokoltsev on 1/31/17.
//

/*
 * The DistPipelineFWK is a small framework that is aimed to parallel
 * the subsequent stages of the information processing chain on a multi core
 * systems. Each signal block (or slice) received from it's source can
 * require a subsequent application of a number of routines that we call filters
 * here. When a new signal block arrive, the other one can be found in one
 * of different processing stages. As long as multi core CPUs permit to process
 * more than one computation at the same moment, we can use all computational
 * resources of a CPU by creating more than one parallel threads.
 *
 * In this example we demonstrate the basic functionality of DistPipelineFWK framework.
 * First we define a meaningful packet data structure MyMsg that contains a "signal" block.
 * Here, for simplicity, the signal is presented by just one value "val", and the
 * same packets are used between any pair of processing nodes in a chain. However,
 * there is no limitations for the signal representation. Any packet structure can be used
 * between any pair of subsequent processing nodes.
 *
 * Here we filter the initial packet data "val" by adding a 100 to it. This filter
 * lives in it's own thread and works in parallel with the other nodes. Finally we
 * print each packet data in the device node, that is a final point in this simple
 * processing chain.
 */

#include <chrono>

#include "base_source.hpp"
#include "base_filter.hpp"

// it is permitted to use namespaces in a *.cpp files, however it
// is a not recommended practice in *.h or *.hpp files
using namespace std;

/*
 * There can be any data that is processed within a pipeline. This
 * data can change from one node to another, so it is a common practice
 * to define the data structures to be passed between any pair of nodes.
 *
 * In this simple example we work with just one custom data struct MyMsg.
 * The other common structs are defined in the data_packet_types.h file.
 * Each message that is passed between two threads shell have a copy constructor.
 * It is used in a generic packet manipulations inside a framework.
 *
 * The next structure in a typical example of any data packet (message).
 */

// shell be derived from BaseMessage, and if it is not the compilation assert message appear
struct MyMsg : public BaseMessage{
    // empty constructor, required to create new messages
    MyMsg(){}

    // copy constructor, required for message copying,
    // please note the call to base class constructor, it is not empty
    MyMsg(const MyMsg& msg) : BaseMessage(msg){
        val = msg.val;
    }

    // any meaningful data fields
    double val;
};

// the source produce a MyMsg in response to each AQUIRE message received
// (see main function)
using tSource = BaseSource<MyMsg>;

// the filter modifies one MyMsg producing another MyMsg
using tFilter = BaseFilter<MyMsg,MyMsg>;

// device node prints out the data of MyMsg
using tDevice = BaseNode<MyMsg>;

/*
 * This src_proc function will be called automatically in the main_loop of the source thread.
 *
 * The use of global variables such as "int i = 0;" below is a not recommended practice.
 * In the case when a source needs for any context data (that can be stored with a
 * source object), there shell be created a new source class derived from the BaseSource
 * or a BaseNode (see other examples).
 */
int i = 0;
shared_ptr<MyMsg> src_proc(){
    auto msg = shared_ptr<MyMsg>(new MyMsg);
    msg->val = i++;

    cout << "sent val: " << msg->val << endl;
    return msg;
}

/*
 * Each time when the "filter" node thread receive a new message
 * it apply a user defined algorithm "filter_proc" that modify the message data.
 *
 * In the case when filter output packet type is not the same as it's input,
 * the new packet shell be created explicitly inside of this function.
 * This case is illustrated in the other examples.
 */
shared_ptr<MyMsg> filter_proc(shared_ptr<MyMsg>&& in){
    in->val += 100;
    cout << "filtered" << endl;
    return in;
}

/*
 * The device is typically placed at the end of the processing chain.
 * Usually it is used to show the results. It can be an oscilloscope,
 * a printing routine (as in here), etc. However, it can also send a signal
 * to the outside world, for example - to the ALSA driver, or a to the
 * Digital to Analog Converter (DAC).
 *
 * Another useful possibility is to create a server device that would
 * send a preprocessed signal to any other signal processing software,
 * like a LabView.
 */
bool dev_proc(shared_ptr<MyMsg>&& msg){
    cout << "val = " << msg->val << endl;
    return true;
}

int main(int argc, char** argv){
    /*
     * It is required to create all nodes in a dynamic memory. Each node can be
     * accessed via it's shared pointer container that is an automatic dynamic
     * memory garbage collector.
     *
     * //todo: use weak pointers for next nodes
     *
     * Also, the node process shell be started, and the unique ID (UID) number
     * shell be assigned to each node. These UID's are used for command messages
     * passing between the nodes that is illustrated in subsequent examples.
     *
     * To automate node creation and destruction routines the NodeFactory
     * class was developed, see node_factory.h for details. This is a singleton
     * class, that has just one object.
     *
     * The NodeFactory::create used below is a template object
     * factory function. This function has a variadic parameters that shell coincide
     * with one of the valid constructors of the node to be created.
     * The node type is specified in the function template argument.
     *
     * The NodeFactory::create function is the only function permitted to create
     * new nodes. Direct instantiation of any node is forbidden by a protected
     * constructors and it is impossible to create nodes without NodeFactory.
     */

    // create and start all nodes
    auto src =    NodeFactory::create<tSource>(src_proc, QUEUE_POLICY::WAIT);
    auto filter = NodeFactory::create<tFilter>(filter_proc, QUEUE_POLICY::WAIT);
    auto dev =    NodeFactory::create<tDevice>(dev_proc);

    // specify processing chain
    src->set_target(filter);
    filter->set_target(dev);

    //send some AQUIRE messages to the source, each of these messages will produce a single
    //call of src_proc
    for(int i = 0; i < 10; i++)
        src->put(MSG_CMD::ACQUIRE, QUEUE_POLICY::WAIT);


    /*
     * In this example nodes are killed in a random order exactly after the last AQUIRE
     * message was sent to "src" node. So, in any program run, the input queue
     * of "src" will be full of AQUIRE messages. The last message to "src" node is a STOP
     * message, produced by NodeFactory destructor. The same destructor sends STOP
     * command to all other node threads and joins their threads with the main
     * function thread.
     *
     * What we would see in the program output depends on the STOP command
     * positions in the "filter" and "dev" input queues. For example, if a "STOP"
     * command is sent to all before the "src" starts to invoke it's src_proc function,
     * the "filter" and "dev" threads will simply ignore all messages sent by "src" and no
     * other output will be produced. The other limiting case is when a STOP command
     * arrive to "dev" after it's queue is filled by filtered messages. In this
     * case we will see the result of 10 dev_proc invocations. All the other cases
     * lie in between these two and can be observed in a series of this program runs.
     *
     * To observe the limiting case when all queues was finished it's job just in time
     * you can uncomment the next line.
     */
    this_thread::sleep_for(chrono::milliseconds(100));

    return 0;
}