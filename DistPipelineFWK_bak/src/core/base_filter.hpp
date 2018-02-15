//
// Created by morrigan on 13/01/18.
//

#ifndef DISTPIPELINEFWK_BASE_FILTER_H
#define DISTPIPELINEFWK_BASE_FILTER_H

#include "base_node.hpp"

//************************FILTER***********************
template<typename tIn, typename tOut>
class BaseFilter : public BaseNode<tIn>{
    static_assert(std::is_base_of<BaseMessage, tOut>(),
                  "tOut shell be derived from BaseMessage class");

public:
    using tBase = BaseNode<tIn>;
    using tPtrIn = std::shared_ptr<tIn>;
    using tPtrOut = std::shared_ptr<tOut>;
    using tPtrNext = std::shared_ptr<BaseNode<tOut>>;

protected:
    friend class NodeFactory;
    BaseFilter(std::function<tPtrOut(tPtrIn&&)> func_filter,
               QUEUE_POLICY pol = QUEUE_POLICY::DROP, std::string name = "BaseFilter"):
            tBase(name),
            external_filter(func_filter),
            pol(pol) {}

protected:
    virtual bool process_usr_msg(tPtrIn&& msg){
        if(next){
            if(external_filter)
                return next->put(external_filter(move(msg)), pol);
            return next->put(internal_filter(move(msg)), pol);
        }else{
            std::cerr << tBase::name << " warning: broken pipe detected" << std::endl;
            return false;
        }
    };

public:
    void set_target(tPtrNext target){next = target;}

protected:
    std::function<tPtrOut(tPtrIn&&)> external_filter;
    virtual tPtrOut internal_filter(tPtrIn&&){return nullptr;}

protected:
    tPtrNext next;
    QUEUE_POLICY pol;
};

#endif //DISTPIPELINEFWK_BASE_FILTER_H
