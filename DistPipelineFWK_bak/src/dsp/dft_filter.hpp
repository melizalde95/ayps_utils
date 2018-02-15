//
// Created by morrigan on 17/12/17.
//

#ifndef DISTPIPELINEFWK_FILTER_FFT_H
#define DISTPIPELINEFWK_FILTER_FFT_H

#include <vector>
#include <memory>

#include "data_packet_types.h"
#include "base_filter.hpp"
#include "dft.h"

template<typename tIn, typename tOut>
class DFTFilter : public BaseFilter<tIn, tOut>, public DFT{
    static_assert(std::is_base_of<RealSignalPkt, tIn>(),
                  "tIn shell be derived from RealSignalPkt class");
    static_assert(std::is_base_of<ComplexSignalPkt, tOut>(),
                  "tOut shell be derived from ComplexSignalPkt class");

public:
    using tBase = BaseFilter<tIn, tOut>;
    using tPtrOut = typename tBase::tPtrOut;
    using tPtrIn = typename tBase::tPtrIn;

protected:
    friend class NodeFactory;
    DFTFilter(QUEUE_POLICY pol = QUEUE_POLICY::DROP, std::string name = "DFTFilter"):
            tBase(nullptr, pol, name){}

    virtual tPtrOut internal_filter(tPtrIn&& msg){
        auto N = msg->data.size();
        if(!is_initialized(N, REAL)) initialize(N, REAL);

        tPtrOut out_msg(new typename tPtrOut::element_type);
        dft(msg->data);
        out_msg->data = std::move(msg->data);

        return out_msg;
    }
};

#endif //DISTPIPELINEFWK_FILTER_FFT_H

