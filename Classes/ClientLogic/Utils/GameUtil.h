//
//  GameUtil.h
//  srpg3
//
//  Created by ff on 14-5-13.
//
//

#ifndef __srpg3__GameUtil__
#define __srpg3__GameUtil__

#include <iostream>
template <class T>
class Singleton
{
public:
    static T* instance()
    {
//        if(!_instance)
//        {
//            
//        }
//        return _instance;
        if( 0== _instance.get())
        {
            _instance.reset(new T());
        }
//        unlockpt(_instance);
        return _instance.get();

    };
    
public:
    Singleton(void){};
    ~Singleton(void){};
    
private:
    Singleton(const Singleton&){};
    Singleton & operator= (const Singleton &){};
    
public:
    static std::auto_ptr<T> _instance;
//    static T *_instance;
};

#define DECLARE_SINGLETON_CLASS( type ) \
friend class auto_ptr< type >;\
friend class Singleton< type >;

template <class T>
std::auto_ptr<T> Singleton<T>::_instance;

class Util : public Singleton<Util>{
    
    
public:
    
};

#endif /* defined(__srpg3__GameUtil__) */
