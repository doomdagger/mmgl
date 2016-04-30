//
// Final Project for COMS 4998: C++ Library Design
// Author: He Li(hl2918), Haoxiang Xu(hx2185), Wangda Zhang(zwd)
//

#ifndef MMGL_EXCEPTION_H
#define MMGL_EXCEPTION_H

#include <exception>
#include <string>

namespace mmgl {

class MMGLException: public std::exception {
private:
    std::string _M_msg;

public:
    /** Takes a character string describing the error.  */
    explicit
    MMGLException(const std::string& arg): _M_msg{arg} {}

    /** Returns a C-style character string describing the general cause of
     *  the current error (the same string passed to the ctor).  */
    virtual const char* what() const throw()
    {
        return _M_msg.c_str();
    }
};

class FileException : public MMGLException {
public:
    /** Takes a character string describing the error.  */
    explicit
    FileException(const std::string& arg): MMGLException{arg} {}
};

class RenderException : public MMGLException {
public:
    /** Takes a character string describing the error.  */
    explicit
    RenderException(const std::string& arg): MMGLException{arg} {}
};

}

#endif //MMGL_EXCEPTION_H
