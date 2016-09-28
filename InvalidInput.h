#ifndef INVALIDINPUT_H
#define INVALIDINPUT_H

class InvalidInput
{
public:
    InvalidInput(const char* in_ptr): msg_ptr (in_ptr){}
    const char* const msg_ptr;
private:
    InvalidInput();
};

#endif