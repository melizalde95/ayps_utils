//
// Created by morrigan on 2/4/18.
//

#ifndef DISTPIPELINEFWK_COMMAND_NODE_H
#define DISTPIPELINEFWK_COMMAND_NODE_H

enum class MSG_CMD{ACQUIRE, STOP, NONE, USER};
enum class QUEUE_POLICY{WAIT, DROP};

class NodeFactory;
class ICloneable;

struct CommandNode{
    virtual void start() = 0;
    virtual void stop() = 0;
    virtual bool put(MSG_CMD, QUEUE_POLICY, std::shared_ptr<ICloneable>&& ) = 0;

    // used to down-cast pointers from CommandNode* to ConcreteNode*
    virtual ~CommandNode() {};

protected:
    unsigned int uid;

private:
    friend class NodeFactory;
    void set_uid(unsigned int uid){this->uid = uid;}

public:
    unsigned int get_uid(){return uid;}
};

#endif //DISTPIPELINEFWK_COMMAND_NODE_H
