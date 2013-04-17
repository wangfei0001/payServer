#ifndef BASE_H
#define BASE_H

#include <string.h>

template <typename T> class singleton
{
private:
    singleton(){};

    static T *m_pInstance;

protected:


public:
    static T *getInstance(){
//        if (NULL == m_pInstance){
//            m_pInstance = new singleton;
//        }
        return m_pInstance;
    }

};

template <typename T> T* singleton<T>::m_pInstance = NULL;


#endif // BASE_H
