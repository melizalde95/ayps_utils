//
// Created by morrigan on 2/7/18.
//

#ifndef DISTPIPELINEFWK_SERIAL_H
#define DISTPIPELINEFWK_SERIAL_H

#include <string>
#include <thread>
#include <mutex>
#include <list>

#include <boost/asio.hpp>
#include <boost/thread.hpp>

#include "base_source.hpp"

struct SerialOutPkt : public BaseMessage{
    // empty constructor
    SerialOutPkt(){}

    // copy constructor
    SerialOutPkt(const SerialOutPkt& pkt) : BaseMessage(pkt), line{pkt.line} {}

    // this client works in text mode, each text line is a data packet
    std::string line;
};

class SerialPortSRC : public BaseSource<SerialOutPkt>{
    using tPtrSerialPort = boost::shared_ptr<boost::asio::serial_port>;
    using tErrCode = boost::system::error_code;

public:
    using tBase = BaseSource<SerialOutPkt>;
    using tPtrIn = tBase::tPtrIn;
    using tPtrOut = std::shared_ptr<SerialOutPkt>;

    SerialPortSRC(std::string dev_name, size_t baud_rate) :
            tBase(nullptr, QUEUE_POLICY::DROP, dev_name), dev_name{dev_name}, baud_rate{baud_rate} {}

protected:
    virtual void main_loop(){
        // asio service and it's thread live in this main only
        boost::asio::io_service io_service;

        // try to open serial port
        tErrCode ec;
        port = tPtrSerialPort(new boost::asio::serial_port(io_service));
        port->open(dev_name.c_str(), ec);
        if (ec) {
            std::cout << "port>open() failed for "
                      << dev_name << ": " << ec.message() << std::endl;
            return;
        }

        // configure port
        port->set_option(boost::asio::serial_port_base::baud_rate(9600));
        port->set_option(boost::asio::serial_port_base::character_size(8));

        // start acquisition thread
        std::thread t(boost::bind(&boost::asio::io_service::run, &io_service));
        async_read_some();

        // main loop of this source thread
        // this loop is not blocked with mutex signal so it can run continuously
        while(1){
            // wait for stop message
            tPtrIn curr_in = pull_msg(false);
            if(curr_in && curr_in->cmd == MSG_CMD::STOP) break;

            //todo: deadlock sometimes?!?!?!
            asio_async_mtx.lock();
            while(!lines.empty()){
                //send data to the next processing node
                std::shared_ptr<SerialOutPkt> pkt(new SerialOutPkt);
                pkt->line = lines.front(); //todo: move!
                lines.pop_front();
                if(next){
                    next->put(move(pkt),pol);
                }else{
                    pkt.reset();
                }
            }
            asio_async_mtx.unlock();

            std::this_thread::sleep_for(std::chrono::milliseconds(20));
        }

        // close port and join with acquisition thread
        asio_async_mtx.lock();
        if (port) {
            port->cancel();
            port->close();
            port.reset();
        }
        asio_async_mtx.unlock();

        io_service.stop();
        io_service.reset();
        if(t.joinable()) t.join();
    }

private:

    void async_read_some(){
        if (!port || !port->is_open()) return;
        port->async_read_some(
                boost::asio::buffer(read_buf_raw, 1024),
                boost::bind(
                        &on_receive,
                        boost::asio::placeholders::error,
                        boost::asio::placeholders::bytes_transferred,
                        this));
    }

    static void on_receive(const boost::system::error_code& ec, size_t bytes_transferred, SerialPortSRC* p_src){
        std::unique_lock<std::mutex> look(p_src->asio_async_mtx);

        if (!p_src->port || !p_src->port->is_open()) return;

        if (ec) {
            p_src->async_read_some();
            return;
        }

        for (unsigned int i = 0; i < bytes_transferred; ++i) {
            char c = p_src->read_buf_raw[i];

            if((c == '\n' || c== '\r') ) {
                if(!p_src->curr_line.empty()) {
                    p_src->lines.push_back(std::string(p_src->curr_line));
                    p_src->curr_line.clear();
                }
                continue;
            }

            p_src->curr_line.push_back(c);
        }

        p_src->async_read_some();
    }


private:
    std::string dev_name;
    size_t baud_rate;

    // serial port to be opened by asio using dev_name in constructor
    tPtrSerialPort port;

    // plain buffer that is filled with data portions no longer than 1024
    char read_buf_raw[1024];

    // needed to sync data access from additional asynchronous acquisition thread
    // todo: how to access this mutex from asio thread?
    std::mutex asio_async_mtx;

    std::list<std::string> lines;
    std::string curr_line;
};

#endif //DISTPIPELINEFWK_SERIAL_H
