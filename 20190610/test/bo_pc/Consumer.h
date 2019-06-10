#pragma once
namespace wd{
class TaskQueue;

class Consumer
{
public:

    void get(TaskQueue &taskQueue);
};
}
