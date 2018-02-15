//
// Created by morrigan on 17/12/17.
//

#ifndef DISTPIPELINEFWK_DATA_PACKET_TYPES_H
#define DISTPIPELINEFWK_DATA_PACKET_TYPES_H

#include <memory>
#include <exception>
#include <vector>

#include "cmd_data_types.h"

/*
 * todo: describe clearly why to define a copy and move
 * todo: constructors, what are the rules for classes that derive
 * todo: any of these...
 */

struct BaseMessage{
    /*
     * An empty constructor, the message fields has to be initialized
     * in the new object manually.
     */
    BaseMessage(){}

    /*
     * Simplified constructor for command messages.
     */
    BaseMessage(MSG_CMD cmd) : cmd{cmd} {}

    /*
     * The tBaseMessage and all derived classes has to
     * implement the copy constructor. This constructor will help to avoid
     * code duplication. Just DO NOT FORGET to call parent
     * constructor as usual.
     */
    BaseMessage(const BaseMessage& msg){
        this->cmd = msg.cmd;
        this->user_data = msg.user_data ? msg.user_data->clone() : nullptr;
    }

    /*
     * A command attached to a message. See cmd_data_types.h for
     * details.
     */
    MSG_CMD cmd = MSG_CMD::NONE;

    /*
     * Usage specific data object attached to a command.
     */
    std::shared_ptr<ICloneable> user_data = nullptr;
};

struct RealSignalPkt : public BaseMessage{
    //empty constructor
    RealSignalPkt(){};

    //copy constructor
    RealSignalPkt(const RealSignalPkt& msg) : BaseMessage(msg){
        this->data = msg.data;
    };

    // signal data
    std::vector<double> data;
};


struct ComplexSignalPkt : public BaseMessage{
    //empty constructor
    ComplexSignalPkt(){}

    //copy constructor
    ComplexSignalPkt(const ComplexSignalPkt& msg) : BaseMessage(msg){
        this->data = msg.data;
    }

    //the C-style complex number array: [ReImReImReIm....]
    //it's size is 2*N
    std::vector<double> data;
};

#endif //DISTPIPELINEFWK_DATA_PACKET_TYPES_H